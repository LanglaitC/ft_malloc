/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:45 by clanglai          #+#    #+#             */
/*   Updated: 2019/11/13 15:31:48 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *handle_large_chunk(size) {
        t_alloc *tmp;
        t_alloc *last;

        if (!global_info->large)
        {
            global_info->large = mmap(0, sizeof(t_info) + size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
            global_info->large->address = global_info->large + sizeof(t_info);
            return global_info->large->address;
        } else
        {
            tmp = global_info->large;
            while (tmp) {
                last = tmp;
                tmp = tmp->next;                
            }
            last->next = mmap(0, sizeof(t_info) + size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
            last->next->address = last->next + sizeof(t_info);
            last->next->size = size;
            return last->next->address;
        }
}

void    *allocate_memory(size_t size, t_alloc *start, t_zone_info info) {
    void    *start_ptr;
    t_alloc *last;
    t_alloc *tmp;
    
    tmp = start;
    last = start;
    start_ptr = info.start;
    while (tmp != NULL) {
        if (tmp->status == NOALLOC) {
            tmp->status = ALLOCATED;
            return tmp->address;
        }
        last = tmp;
        tmp = tmp->next;
    }
    last->next = last->address + sizeof(t_alloc) + size;
    tmp = last->next;
    tmp->address = tmp + sizeof(t_alloc);
    tmp->status = ALLOCATED;
    tmp->size = size;
    return tmp->address;
}

void    *malloc(size_t size) {
    global_info = get_info_variable(size);
    if (size < TINY) {
        return allocate_memory(TINY, global_info->small, global_info->small_info);
    } else if (size < SMALL) {
        return allocate_memory(SMALL, global_info->medium, global_info->medium_info);
    } else {
        return handle_large_chunk(size);
    }
    return mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}