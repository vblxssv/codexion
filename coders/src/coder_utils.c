/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:28:01 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 14:33:58 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

t_request	ft_make_request(t_coder	*coder)
{
	t_request	req;

	req.coder_id = coder->id;
	req.arrival_time = ft_get_relative_time(coder->ctx->start_time);
	req.deadline = coder->deadline;
	return (req);
}

void	ft_add_compiles(t_coder	*coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->mutex);
}

unsigned int	ft_get_compiles(t_coder	*coder)
{
	unsigned int	res;

	pthread_mutex_lock(&coder->mutex);
	res = coder->compiles;
	pthread_mutex_unlock(&coder->mutex);
	return (res);
}

void	ft_wake_up(t_coder	*coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->can_work = true;
	pthread_cond_broadcast(&coder->cond);
	pthread_mutex_unlock(&coder->mutex);
}
