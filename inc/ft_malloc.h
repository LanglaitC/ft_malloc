/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:11:50 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/14 15:32:50 by clanglai         ###   ########.fr       */
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
# define TINY_STATUS            0
# define TINY                   224
# define SMALL                  480
# define SMALL_STATUS           1
# define LARGE_STATUS           2
# define MIN_ALLOCATION_BY_ZONE 100
# define PAGESIZE               getpagesize()

typedef struct      s_zone_info
{
    int             chunk_number;
    int             zone_size;
    unsigned char   status;
}                   t_zone_info;

typedef struct  s_alloc
{
    void            *address;
    unsigned char   status;
    unsigned int    size;
    struct s_alloc  *next;
    struct s_alloc  *prev;
}               t_alloc;

typedef struct      s_zone
{
    t_alloc         *start;
    unsigned char   status;
    unsigned char   free_nbr;
    unsigned int    size;
    struct s_zone   *next;
    struct s_zone   *prev;
}                   t_zone;

typedef struct  s_info
{
    t_zone      *start;
    t_zone      *current;
}               t_info;

extern t_info   *g_info;

void            free(void *ptr);
void            *malloc(size_t size);
void            *realloc(void *ptr, size_t size);
void            show_alloc_mem(void);
void            ft_putadrr(int addr, char base[16]);
int             get_status(size_t size);
t_zone          *find_zone_in_list(void *ptr);
t_info          *get_info_variable();

#endif