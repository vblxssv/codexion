/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:41:32 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 14:42:43 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <string.h>

bool	ft_init_context(t_context *ctx, int argc, char **argv)
{
	memset(ctx, 0, sizeof(t_context));
	if (!ft_parse_args(argc, argv, &ctx->args))
		return (false);
	if (pthread_mutex_init(&ctx->state_mutex, NULL) != 0)
		return (false);
	ft_set_running(ctx, true);
	ctx->dongles = ft_init_dongles(ctx->args.number_of_coders,
			ctx->args.scheduler);
	if (!ctx->dongles)
	{
		pthread_mutex_destroy(&ctx->state_mutex);
		return (false);
	}
	ctx->coders = ft_init_coders(ctx);
	if (!ctx->coders)
	{
		ft_free_dongles(ctx->dongles, ctx->args.number_of_coders);
		pthread_mutex_destroy(&ctx->state_mutex);
		return (false);
	}
	return (true);
}

void	ft_free_context(t_context	*ctx)
{
	if (!ctx)
		return ;
	if (ctx->dongles)
		ft_free_dongles(ctx->dongles, ctx->args.number_of_coders);
	if (ctx->coders)
		ft_free_coders(ctx->coders);
	pthread_mutex_destroy(&ctx->state_mutex);
}
