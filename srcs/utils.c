/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:23:45 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/07 14:43:47 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_info   *global_info;

static t_zone_info get_best_alloc_size_for_zone(int size, unsigned char status) {
    int i;
    t_zone_info info;
    int size_by_status[3];

    size_by_status[0] = TINY;
    size_by_status[1] = SMALL;
    size_by_status[2] = size;

    i = 0;
    info.status = status;
    if (info.status == LARGE_STATUS)
    {
        info.zone_size = size + sizeof(t_alloc);
        i++;
    } else
    {
        while (i < MIN_ALLOCATION_BY_ZONE) {
            i += PAGESIZE / (size_by_status[info.status] + sizeof(t_alloc));
            info.zone_size += PAGESIZE;
        }
    }
    info.chunk_number = i;
    return info;
}

void    insert_new_zone(t_zone *new) {
    t_zone *tmp;

    if (global_info->start == NULL) {
        global_info->start = new;
    } else {
        tmp = global_info->start;
        if (tmp->prev == NULL && (int)tmp < (int)new) {
            new->next = tmp;
            tmp->prev = new;
            global_info->start = new;
        }
        else {
            while (tmp != NULL && (int)tmp < (int)new && tmp->next) {
                tmp = tmp->next;
            }
            if (tmp != NULL && tmp < new) {
                tmp->prev->next = new;
                new->prev = tmp->prev;
                new->next = tmp;
                tmp->prev = new;
            } else {
                tmp->next = new;
                new->prev = tmp;
            }
        }
    }
}

static void allocate_zone(size_t size) {
    t_zone_info info;
    t_zone      *tmp;

    tmp = NULL;
    info = get_best_alloc_size_for_zone(size, GET_STATUS(size));
    if (global_info->start != NULL)
    {
        tmp = global_info->start;
        while (tmp != NULL)
        {
            if (tmp->status == info.status && tmp->free_nbr)
                break;
            tmp = tmp->next;
        }
    }
     if (tmp == NULL)
     {
        tmp = mmap(0, sizeof(t_zone) + info.zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        tmp->size = info.zone_size;
        tmp->status = info.status;
        tmp->free_nbr = info.chunk_number;
        tmp->start = (t_alloc*)(tmp + (sizeof(t_zone) / sizeof(t_zone)));
        tmp->start->status = NOALLOC;
        tmp->start->address = tmp->start + (sizeof(t_alloc) / sizeof(t_alloc));
        tmp->end = tmp + info.zone_size;
        insert_new_zone(tmp);
    }
    global_info->current = tmp;
}

t_info  *get_info_variable(size_t size) {
    if (global_info == NULL) {
        global_info = mmap(0, sizeof(t_info), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    }
    allocate_zone(size);
    return global_info;
}