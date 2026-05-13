/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:40:15 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 22:18:49 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include <stdio.h>

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
		coders[i].deadline = 0;
		coders[i].state = IDLE;
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

t_request	ft_make_request(t_coder	*coder)
{
	t_request	req;

	req.coder_id = coder->id;
	req.arrival_time = ft_get_relative_time(coder->ctx->start_time);
	req.deadline = coder->deadline;
	return (req);
}

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
	while (!coder->can_work && coder->ctx->is_running)
		pthread_cond_wait(&coder->cond, &coder->mutex);
	if (!coder->ctx->is_running)
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

void	*ft_live_life(void	*args)
{
	t_coder		*coder;
	t_context	*ctx;

	coder = (t_coder *)args;
	ctx = coder->ctx;
	while (!ctx->is_running)
		usleep(100);
	if (coder->id % 2 == 0)
		usleep(ctx->args.time_to_compile * 500);
	while (ctx->is_running)
    {
        ft_get_in_q(coder);
        if (!ft_wait_for_permission(coder))
            break ;
        ft_log(coder, "has taken a dongle");
        ft_log(coder, "has taken a dongle");
        ft_log(coder, "is compiling");
        usleep(ctx->args.time_to_compile * 1000);
        ft_release_dongles(coder);
        
        if (!ctx->is_running) break ;

        ft_log(coder, "is debugging");
        usleep(ctx->args.time_to_debug * 1000);
        
        if (!ctx->is_running) break ;

        ft_log(coder, "is refactoring");
        usleep(ctx->args.time_to_refactor * 1000);
    }
	return (NULL);
}

void	ft_wake_up(t_coder	*coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->can_work = true;
	pthread_cond_broadcast(&coder->cond);
	pthread_mutex_unlock(&coder->mutex);
}
