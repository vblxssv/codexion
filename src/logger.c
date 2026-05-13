/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:49:29 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 21:52:18 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

void	ft_log(t_coder	*coder, char	*msg)
{
	long long	now;

	pthread_mutex_lock(&coder->ctx->state_mutex);
	now = ft_get_relative_time(coder->ctx->start_time);
	printf("%lld %i %s\n", now, coder->id, msg);
	pthread_mutex_unlock(&coder->ctx->state_mutex);
}
