/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_spot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:47:04 by ezalos            #+#    #+#             */
/*   Updated: 2021/06/10 10:59:57 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int8_t		is_secure_access(uint64_t file_size, uint64_t offset, uint64_t access_size)
{
	if (offset + access_size < offset || offset + access_size > file_size)
		return (FALSE);
	return (TRUE);
}

int8_t		check_elf_header(uint8_t *content, size_t size)
{
	Elf64_Ehdr *ehdr;

	if (!is_secure_access(size, 0, sizeof(Elf64_Ehdr)))
		return (FAILURE); // TODO: check security
	ehdr = (Elf64_Ehdr *)content;
	if (memcmp(ehdr->e_ident, ELFMAG, 4) != 0)
		return (FAILURE); // TODO: check security
	if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
		return (FAILURE); // TODO: check security
	return (FAILURE);
	if (ehdr->e_ident[EI_DATA] != ELFDATA2LSB)
		return (FAILURE); // TODO: check security
	if ((((size_t)((Elf64_Ehdr *)content)->e_phentsize)
		* ((size_t)((Elf64_Ehdr *)content)->e_phnum)
		+ ((Elf64_Ehdr *)content)->e_phoff)
		> size)
		return (FAILURE); // TODO: check security
	return (SUCCESS);
}

Elf64_Phdr	*get_program_header(void *file, uint32_t index)
{
    Elf64_Ehdr *elf;
    Elf64_Phdr *phdr;

    elf = (Elf64_Ehdr *)file;
	phdr = (Elf64_Phdr *)((size_t)file + (size_t)elf->e_phoff + ((size_t)index * (size_t)elf->e_phentsize));

	if (index >= elf->e_phnum)
        phdr = NULL;

    return phdr;
}


Elf64_Phdr	*find_phdr(void *file, size_t file_size)
{
    Elf64_Phdr	*phdr;
	int			i;

	printf("%s\n", __func__);
	if (FAILURE == check_elf_header(file, file_size))
		return NULL;

	phdr = NULL;
	i = -1;
	while (++i < ((Elf64_Ehdr *)file)->e_phnum)
	{
		phdr = get_program_header(file, i);
		// check phdr not outside file
		if (phdr)
		{
			if (phdr->p_type == PT_LOAD)
				// && phdr->p_flags & flags = flags)
				if (phdr->p_filesz < phdr->p_memsz)
				{
					printf("Found phdr");
					return phdr;
				}
		}
	}
	return phdr;
	// for phdr in phdr_array:
	// 	if last_loadable:
	// 		best_phdr = phdr;
	// return best_phdr;
}
