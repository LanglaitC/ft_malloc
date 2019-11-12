/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:23:45 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/07 15:25:40 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_info   *global_info;

static t_zone_info get_best_alloc_size_for_zone(int chunk_size) {
    int i;
    t_zone_info info;
    int pagesize;

    i = 0;
    pagesize = getpagesize();
    while (i < MIN_ALLOCATION_BY_ZONE) {
        i += pagesize / (chunk_size + sizeof(t_alloc));
        info.zone_size += pagesize;
    }
    info.chunk_number = i;
    return info;
}

static void allocate_zone(size_t size, t_zone_info zone_info) {
    if (size < TINY) {
        zone_info = get_best_alloc_size_for_zone(TINY);
    } else {
        zone_info = get_best_alloc_size_for_zone(SMALL);
    }
    zone_info.start = mmap(0, zone_info.zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

t_info  *get_info_variable(size_t size) {
    if (global_info == NULL) {
        global_info = mmap(0, sizeof(t_info), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    }
    if (size < TINY && !global_info->small) {
        allocate_zone(size, global_info->small_info);
    } else if (size >= TINY && size < SMALL && global_info->medium) {
        allocate_zone(size, global_info->medium_info);
    }
    return global_info;
}