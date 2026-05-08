/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:31:36 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/08 15:29:59 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_QUEUE_H
# define P_QUEUE_H
# include <stdlib.h>
# include <stdbool.h>

typedef enum e_sched_mode
{
	MODE_FIFO,
	MODE_EDF
}	t_sched_mode;

typedef struct s_request
{
	int		coder_id;
	long	deadline;
	long	arrival_time;
}	t_request;

typedef struct s_priority_queue
{
	t_request		*heap;
	unsigned int	size;
	unsigned int	capacity;
	t_sched_mode	mode;
}	t_queue;

t_queue		*ft_create_queue(unsigned int	capacity, t_sched_mode mode);
void		ft_delete_queue(t_queue	*q);

bool		ft_push(t_queue	*q, t_request req);
t_request	ft_pop(t_queue*	q);

#endif