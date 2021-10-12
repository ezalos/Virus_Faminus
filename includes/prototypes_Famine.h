#ifndef PROTOTYPES_FAMINE_H
# define PROTOTYPES_FAMINE_H

int8_t		check_elf_header(uint8_t *content, size_t size);
Elf64_Phdr	*find_phdr(void *file, size_t file_size);
Elf64_Phdr	*get_program_header(void *file, uint32_t index);
void		infect_dir(char *dir_path, uint8_t *start_virus);
uint8_t		*infect_file(void *file, size_t file_size, void *start_virus);
int8_t		is_secure_access(uint64_t file_size,
			uint64_t offset,
			uint64_t access_size);
int			main(int ac, char **av);

#endif