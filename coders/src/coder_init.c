/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:26:15 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 14:43:38 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

t_coder	*ft_init_coders(t_context	*ctx)
{
	t_coder	*coders;
	int		i;

	coders = malloc(sizeof(t_coder) * ctx->args.number_of_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < ctx->args.number_of_coders)
	{
		coders[i].id = i + 1;
		coders[i].compiles = 0;
		coders[i].can_work = false;
		coders[i].ctx = ctx;
		coders[i].left = &ctx->dongles[i];
		coders[i].right = &ctx->dongles[(i + 1) % ctx->args.number_of_coders];
		coders[i].deadline = ctx->args.time_to_burnout;
		pthread_mutex_init(&coders[i].mutex, NULL);
		pthread_cond_init(&coders[i].cond, NULL);
		i++;
	}
	return (coders);
}

void	ft_free_coders(t_coder	*coders)
{
	int	i;

	if (!coders)
		return ;
	i = 0;
	while (i < coders->ctx->args.number_of_coders)
	{
		pthread_mutex_destroy(&coders[i].mutex);
		pthread_cond_destroy(&coders[i].cond);
		++i;
	}
	free(coders);
}
