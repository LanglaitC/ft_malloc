/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:11:50 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/02 15:32:41 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC
# define FT_MALLOC

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>

#define TINY    16
#define SMALL   128

typedef struct  s_alloc
{
    int         size;
    int         address;
    void        *next;
    void        *prev;
}               t_alloc;

void            free(void *ptr);
void            *malloc(size_t size);
void            *realloc(void *ptr, size_t size);
void            show_alloc_mem();

#endif