/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:45 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/12 15:49:08 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    allocate_memory(size_t size, t_alloc *start, t_zone_info info) {
    void    *start_ptr;
    t_alloc *last;
    
    last = start;
    start_ptr = info.start;
    while (start != NULL) {
        if (start->status == NOALLOC) {
            return start->address;
        }
        start_ptr = start->address + sizeof(t_alloc);
        start = start->next;
    }
    if (last == NULL) {
        last = info.start;
        last->address = info.start + sizeof(t_alloc);
        last->status = ALLOCATED;
        return start->address;
    }

}

void    *malloc(size_t size) {
    global_info = get_info_variable(size);
    if (size < TINY) {
        allocate_memory(size, global_info->small, global_info->small_info);
    } else if (size < SMALL) {
        allocate_memory(size, global_info->medium, global_info->medium_info);
    }
    return mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}