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

uint8_t		*access_file(char *file, ssize_t *size)
{
	int fd;
	uint8_t	*content;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL); // TODO: check security
	if ((*size = lseek(fd, 0L, SEEK_END)) == -1)
	{
		close(fd);
		return (NULL); // TODO: check security
	}
	if ((content = (uint8_t *)mmap(0,
									(size_t)*size,
									PROT_READ | PROT_WRITE,
									MAP_PRIVATE,
									fd,
									0)) == MAP_FAILED)
	{
		close(fd);
		return (NULL); // TODO: check security
	}
	close(fd);
	return (content);
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
	return (SUCCESS);
}
