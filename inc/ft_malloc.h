/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 09:42:54 by clanglai          #+#    #+#             */
/*   Updated: 2020/10/15 09:50:02 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <inttypes.h>

# define NOALLOC                0
# define ALLOCATED              1
# define TINY_STATUS            0
# define TINY                   512
# define SMALL                  1024
# define SMALL_STATUS           1
# define LARGE_STATUS           2
# define MIN_ALLOCATION_BY_ZONE 100

typedef struct		s_zone_info
{
	int				chunk_number;
	int				zone_size;
	unsigned char	status;
}					t_zone_info;

typedef struct		s_alloc
{
	unsigned char	status;
	unsigned int	size;
	struct s_alloc	*next;
}					t_alloc;

typedef struct		s_zone
{
	t_alloc			*start;
	unsigned int	status;
	unsigned int	free_size;
	unsigned int	size;
	unsigned int	chunk1;
	unsigned int	chunk2;
	unsigned int	chunk3;
	struct s_zone	*next;
	struct s_zone	*prev;
}					t_zone;

typedef struct		s_info
{
	t_zone			*start;
	t_zone			*current;
}					t_info;

extern t_info		*g_info;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem(void);
void				ft_putadrr(unsigned int addr, char base[16]);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putchar(char c);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
void				ft_bzero(void *s, size_t n);
int					get_status(size_t size);
t_zone				*find_zone_in_list(void *ptr);
t_info				*get_info_variable(size_t size);
void				*allocate_memory(size_t size);

#endif
