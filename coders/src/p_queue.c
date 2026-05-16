/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:57:20 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 14:39:06 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_queue.h"

void	ft_shift_down(t_queue *q, unsigned int i);
void	ft_shift_up(t_queue	*q, int i);

t_queue	*ft_create_queue(unsigned int capacity, t_sched_mode mode)
{
	t_queue	*q;

	if (capacity == 0)
		return (NULL);
	q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->capacity = capacity;
	q->mode = mode;
	q->heap = malloc(sizeof(t_request) * capacity);
	q->size = 0;
	if (!q->heap)
	{
		free(q);
		return (NULL);
	}
	return (q);
}

void	ft_delete_queue(t_queue	*q)
{
	if (!q)
		return ;
	if (q->heap)
		free(q->heap);
	free(q);
}

bool	ft_push(t_queue	*q, t_request req)
{
	if (!q || q->size >= q->capacity)
		return (false);
	q->heap[q->size] = req;
	ft_shift_up(q, q->size);
	q->size++;
	return (true);
}

t_request	ft_pop(t_queue	*q)
{
	t_request	root;

	if (q->size == 0)
		return ((t_request){0, 0, 0});
	root = q->heap[0];
	q->size--;
	if (q->size > 0)
	{
		q->heap[0] = q->heap[q->size];
		ft_shift_down(q, 0);
	}
	return (root);
}

t_request	ft_peek(t_queue *q)
{
	if (q && q->size > 0)
		return (q->heap[0]);
	return ((t_request){0});
}
