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

void		infect_dir(char *dir_path, uint8_t *start_virus)
{
	DIR				*dir;
	struct dirent	*dir_entry;
	int				fd;
	struct stat		stat;
	uint8_t			*mem_file;

	dir = opendir(dir_path);
	if (dir == NULL)
		return ;
	while ((dir_entry = readdir(dir)) != NULL)
	{
		if ((fd = open(dir_entry->d_name, O_RDWR)) == -1)
			continue ;
		if (fstat(fd, &stat) == -1)
			continue ;
		if (!S_ISREG(stat->st_mode))
			continue ;
		if ((mem_file = mmap(NULL,
				stat->st_size,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE,
				fd,
				0)) == MAP_FAILED)
			continue ;

		if ((mem_file = infect_file()) != NULL)
			save_file()

		// infect_file();// TODO handle munmap in infect_file
		// 	save_file(dir_entry->d_name, mem_file);
	}
}

int			main(int ac, char **av)
{
	(void)ac;
	(void)av;
	printf("Hello World!\n");
}
