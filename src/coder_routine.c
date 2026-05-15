/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:40:15 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 15:30:53 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include <stdio.h>

void	ft_get_in_q(t_coder	*coder)
{
	t_request	req;

	req = ft_make_request(coder);
	ft_lock_pair(coder->left, coder->right);
	ft_push(coder->left->queue, req);
	ft_push(coder->right->queue, req);
	ft_unlock_pair(coder->left, coder->right);
}

static bool	ft_wait_for_permission(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	while (!coder->can_work && ft_get_running(coder->ctx))
		pthread_cond_wait(&coder->cond, &coder->mutex);
	if (!ft_get_running(coder->ctx))
	{
		pthread_mutex_unlock(&coder->mutex);
		return (false);
	}
	coder->can_work = false;
	coder->deadline = ft_get_relative_time(coder->ctx->start_time)
		+ coder->ctx->args.time_to_burnout;
	pthread_mutex_unlock(&coder->mutex);
	return (true);
}

static void	ft_release_dongles(t_coder	*coder)
{
	t_context	*ctx;

	ctx = coder->ctx;
	ft_lock_pair(coder->left, coder->right);
	coder->left->cooldown_until = ft_get_relative_time(ctx->start_time)
		+ ctx->args.dongle_cooldown;
	coder->right->cooldown_until = ft_get_relative_time(ctx->start_time)
		+ ctx->args.dongle_cooldown;
	ft_unlock_pair(coder->left, coder->right);
}

static void	ft_work_loop(t_coder	*coder, t_context	*ctx)
{
	ft_log(coder, "has taken a dongle");
	ft_log(coder, "has taken a dongle");
	ft_log(coder, "is compiling");
	usleep(ctx->args.time_to_compile * 1000);
	ft_add_compiles(coder);
	ft_release_dongles(coder);
	if (!ft_get_running(ctx))
		return ;
	ft_log(coder, "is debugging");
	usleep(ctx->args.time_to_debug * 1000);
	if (!ft_get_running(ctx))
		return ;
	ft_log(coder, "is refactoring");
	usleep(ctx->args.time_to_refactor * 1000);
}

void	*ft_live_life(void	*args)
{
	t_coder		*coder;
	t_context	*ctx;

	coder = (t_coder *)args;
	ctx = coder->ctx;
	while (!ft_get_running(ctx))
		usleep(100);
	if (coder->id % 2 == 0)
		usleep(ctx->args.time_to_compile * 500);
	while (ft_get_running(ctx))
	{
		ft_get_in_q(coder);
		if (!ft_wait_for_permission(coder))
			break ;
		ft_work_loop(coder, ctx);
	}
	return (NULL);
}
