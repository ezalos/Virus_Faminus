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

int			main(int ac, char **av)
{
	ssize_t size;
	uint8_t *content;

	printf("Hello World!\n");

	if (ac < 2)
	{
		printf("usage: %s path_to_file_to_infect\n", av[0]);
		return (FAILURE);
	}
	content = access_file(av[1], &size);
	if (!check_elf_header(content, size))
		return (FAILURE);
	printf("Wesh wesh !\n");
	return (0);
}
