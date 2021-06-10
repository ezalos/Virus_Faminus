/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2021/06/10 11:00:44 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include <sys/stat.h>
# include <fcntl.h>
# include <error.h>
# include <errno.h>
# include <stdio.h>
# include <inttypes.h>
# include <stdlib.h>
# include <elf.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>
# include <sys/mman.h>
# include <stdarg.h>

# define DEBUG		0

extern int debug_level;

# define SUCCESS	0
# define FAILURE	-1

# define TRUE		1
# define FALSE		0

// # include "libft.h"

/*
**	COLORS
*/

#define _RED "\x1b[31m"
#define _GREEN "\x1b[32m"
#define _BLUE "\x1b[34m"
#define _YELLOW "\x1b[33m"
#define _MAGENTA "\x1b[35m"
#define _CYAN "\x1b[36m"
#define _RESET "\x1b[0m"
#define _BROWN "\x1b[38;2;238;205;163m"
#define _PINK "\x1b[38;2;239;100;100m"
#define _PURPLE "\x1b[38;2;101;78;163m"
#define _ORANGE "\x1b[38;2;155;75;43m"
#define _TURQUOISE "\x1b[38;2;68;140;121m"
#define CU_RESET "\033[0;0H"
#define CU_LOAD "\033[u"
#define CU_SAVE "\033[s"
#define CL_SCREEN "\033[2J"

/*
**	PROTOTYPES
*/

# include "prototypes_Famine.h"

#endif
