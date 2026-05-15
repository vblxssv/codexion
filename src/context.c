/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:16:52 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 14:41:58 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <stdlib.h>
#include <string.h>

void	ft_run_simulation(t_context	*ctx)
{
	int	i;

	ctx->start_time = ft_get_current_time();
	i = 0;
	while (i < ctx->args.number_of_coders)
	{
		pthread_create(&ctx->coders[i].thread, NULL,
			ft_live_life, &ctx->coders[i]);
		++i;
	}
	pthread_create(&ctx->scheduler_thread, NULL, ft_scheduler_routine, ctx);
	pthread_create(&ctx->monitor_thread, NULL, ft_monitor_routine, ctx);
}

void	ft_wait_simulation(t_context	*ctx)
{
	int	i;

	pthread_join(ctx->monitor_thread, NULL);
	ft_set_running(ctx, false);
	i = 0;
	while (i < ctx->args.number_of_coders)
	{
		ft_wake_up(&ctx->coders[i]);
		++i;
	}
	i = 0;
	while (i < ctx->args.number_of_coders)
	{
		pthread_join(ctx->coders[i].thread, NULL);
		++i;
	}
	pthread_join(ctx->scheduler_thread, NULL);
}

bool	ft_get_running(t_context	*ctx)
{
	bool	res;

	pthread_mutex_lock(&ctx->state_mutex);
	res = ctx->is_running;
	pthread_mutex_unlock(&ctx->state_mutex);
	return (res);
}

void	ft_set_running(t_context	*ctx, bool irsng)
{
	pthread_mutex_lock(&ctx->state_mutex);
	ctx->is_running = irsng;
	pthread_mutex_unlock(&ctx->state_mutex);
}
