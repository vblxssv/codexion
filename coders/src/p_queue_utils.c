/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:35:05 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 15:36:35 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_queue.h"

static bool	ft_is_higher(t_request a, t_request b, t_sched_mode mode)
{
	if (mode == MODE_EDF)
	{
		if (a.deadline != b.deadline)
			return (a.deadline < b.deadline);
		return (a.arrival_time < b.arrival_time);
	}
	return (a.arrival_time < b.arrival_time);
}

static void	ft_swap(t_request	*a, t_request	*b)
{
	t_request		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_shift_down(t_queue	*q, unsigned int i)
{
	unsigned int	left;
	unsigned int	right;
	unsigned int	best;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		best = i;
		if (left < q->size
			&& ft_is_higher(q->heap[left], q->heap[best], q->mode))
			best = left;
		if (right < q->size
			&& ft_is_higher(q->heap[right], q->heap[best], q->mode))
			best = right;
		if (best == i)
			break ;
		ft_swap(&q->heap[i], &q->heap[best]);
		i = best;
	}
}

void	ft_shift_up(t_queue	*q, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!ft_is_higher(q->heap[i], q->heap[parent], q->mode))
			break ;
		ft_swap(&q->heap[i], &q->heap[parent]);
		i = parent;
	}
}
