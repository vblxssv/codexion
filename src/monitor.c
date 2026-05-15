/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 22:03:43 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 15:28:42 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_r.h"

static bool	ft_check_death(t_coder	*coder, t_context	*ctx)
{
	long long	now;

	pthread_mutex_lock(&coder->mutex);
	now = ft_get_relative_time(ctx->start_time);
	if (now >= coder->deadline)
	{
		ft_log(coder, "burned out");
		ft_set_running(ctx, false);
		pthread_mutex_unlock(&coder->mutex);
		return (true);
	}
	pthread_mutex_unlock(&coder->mutex);
	return (false);
}

void	*ft_monitor_routine(void	*args)
{
	t_context	*ctx;
	int			i;
	bool		all_done;

	ctx = (t_context *)args;
	while (!ft_get_running(ctx))
		usleep(100);
	while (ft_get_running(ctx))
	{
		i = -1;
		all_done = true;
		while (++i < ctx->args.number_of_coders)
		{
			if (ft_check_death(&ctx->coders[i], ctx))
				return (NULL);
			if (ft_get_compiles(&ctx->coders[i])
				< (unsigned int)ctx->args.number_of_compiles_required)
				all_done = false;
		}
		if (all_done && ctx->args.number_of_compiles_required != -1)
			return (ft_set_running(ctx, false), NULL);
		usleep(500);
	}
	return (NULL);
}
