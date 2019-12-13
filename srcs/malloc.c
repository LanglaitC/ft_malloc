/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:14:45 by clanglai          #+#    #+#             */
/*   Updated: 2019/12/13 16:48:58 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void    *create_new_chunk(t_alloc *last, int size) {
    t_alloc *new;
    int     to_jump;

    if (last == NULL) {
        new = global_info->current->start;
        new->prev = NULL;
        new->next = NULL;
    } else {
        to_jump = (last->size < TINY ? TINY : SMALL) + sizeof(t_alloc);
        new = last + (to_jump / sizeof(t_alloc));
        last->next = new;
        new->prev = last;
    }
    new->size = size;
    new->address = new + (sizeof(t_alloc) / sizeof(t_alloc));
    new->status = ALLOCATED;
    return new->address;
}

void    *allocate_memory(size_t size) {
    t_alloc *new;
    t_alloc *tmp;
    t_alloc *last;

    global_info->current->free_nbr--;
    if (global_info->current->status == LARGE_STATUS) {
        new = global_info->current->start;
        new->size = size;
        new->status = ALLOCATED;
        new->address = new + (sizeof(t_alloc) / sizeof(t_alloc));
        return new->address;
    }
    tmp = global_info->current->start;
    last = tmp;
    while (tmp != NULL && tmp->status != NOALLOC) {
        last = tmp;
        tmp = tmp->next;
    }
    if (tmp != NULL) {
        tmp->status = ALLOCATED;
        tmp->size = size;
        return tmp->address;
    }
    return create_new_chunk(last, size);
}

void    *malloc(size_t size) {
    void*   result;

    ft_putstr("Start malloc\n");
    global_info = get_info_variable(size);
    result = allocate_memory(size);
    ft_putstr("End malloc\n");
    // show_alloc_mem();
    return result;
}