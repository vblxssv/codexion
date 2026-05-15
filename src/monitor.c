/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 22:03:43 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/14 19:12:36 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_r.h"

void	*ft_monitor_routine(void	*args)
{
	t_context	*ctx;
	int			i;
	long long	now;
	int			fully_compiled_coders;

	ctx = (t_context *)args;
	while (!ft_get_running(ctx))
		usleep(100);
	while (ft_get_running(ctx))
	{
		i = 0;
		fully_compiled_coders = 0;
		while (i < ctx->args.number_of_coders)
		{
			pthread_mutex_lock(&ctx->coders[i].mutex);
			now = ft_get_relative_time(ctx->start_time);
			if (now >= ctx->coders[i].deadline)
			{
				ft_log(&ctx->coders[i], "burned out");
				ft_set_running(ctx, false);
				pthread_mutex_unlock(&ctx->coders[i].mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&ctx->coders[i].mutex);
			if (ft_get_compiles(&ctx->coders[i])
				>= (unsigned int)ctx->args.number_of_compiles_required)
				fully_compiled_coders++;
			i++;
		}
		if (ctx->args.number_of_compiles_required > 0
			&& fully_compiled_coders == ctx->args.number_of_coders)
		{
			ft_set_running(ctx, false);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
