/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:11:50 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/13 13:24:04 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC
# define FT_MALLOC

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include "../libft/inc/libft.h"

# define NOALLOC                0
# define ALLOCATED              1
# define TINY                   64
# define SMALL                  128
# define MIN_ALLOCATION_BY_ZONE 100

typedef struct  s_zone_info
{
    int         chunk_number;
    int         zone_size;
    void        *start;
}               t_zone_info;

typedef struct  s_alloc
{
    void            *address;
    int             status;
    int             size;
    struct s_alloc  *next;
    struct t_alloc  *prev;
}               t_alloc;

typedef struct  s_info
{
    t_alloc     *small;
    t_zone_info small_info;
    t_alloc     *medium;
    t_zone_info medium_info;
    t_alloc     *large;
}               t_info;

extern t_info   *global_info;

void            free(void *ptr);
void            *malloc(size_t size);
void            *realloc(void *ptr, size_t size);
void            show_alloc_mem();
t_info          *get_info_variable();

#endif