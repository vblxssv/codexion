/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:43:31 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 15:38:59 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler.h"

static bool	ft_is_ready(t_coder	*coder)
{
	long long	now;
	t_request	left_req;
	t_request	right_req;

	now = ft_get_relative_time(coder->ctx->start_time);
	left_req = ft_peek(coder->left->queue);
	right_req = ft_peek(coder->right->queue);
	if (left_req.coder_id == coder->id
		&& right_req.coder_id == coder->id
		&& now >= coder->left->cooldown_until
		&& now >= coder->right->cooldown_until)
		return (true);
	return (false);
}

static void	ft_allow_work(t_coder	*coder)
{
	ft_pop(coder->left->queue);
	ft_pop(coder->right->queue);
	coder->left->cooldown_until = 2000000000000LL;
	coder->right->cooldown_until = 2000000000000LL;
	ft_wake_up(coder);
}

void	*ft_scheduler_routine(void	*args)
{
	t_context	*ctx;
	int			i;
	t_coder		*coder;

	ctx = (t_context *)args;
	while (ft_get_running(ctx))
	{
		i = 0;
		while (i < ctx->args.number_of_coders)
		{
			coder = &ctx->coders[i];
			ft_lock_pair(coder->left, coder->right);
			if (ft_is_ready(coder))
				ft_allow_work(coder);
			ft_unlock_pair(coder->left, coder->right);
			++i;
		}
		usleep(100);
	}
	return (NULL);
}
