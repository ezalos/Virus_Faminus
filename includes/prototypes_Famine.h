#ifndef PROTOTYPES_FAMINE_H
# define PROTOTYPES_FAMINE_H

uint8_t		*access_file(char *file, ssize_t *size);
int8_t		check_elf_header(uint8_t *content, size_t size);
int8_t		is_secure_access(uint64_t file_size,
			uint64_t offset,
			uint64_t access_size);
int			main(int ac, char **av);

#endif