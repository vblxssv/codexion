/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 22:03:43 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 22:27:47 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor_r.h"

void    *ft_monitor_routine(void *args)
{
    t_context   *ctx;
    int         i;
    long long   now;

    ctx = (t_context *)args;
    while (!ctx->is_running)
        usleep(100);
    while (ctx->is_running)
    {
        i = 0;
        while (i < ctx->args.number_of_coders)
        {
            pthread_mutex_lock(&ctx->coders[i].mutex);
            now = ft_get_relative_time(ctx->start_time);
            if (now >= ctx->coders[i].deadline)
            {
                ft_log(&ctx->coders[i], "burned out");
                pthread_mutex_lock(&ctx->state_mutex);
                ctx->is_running = false;
                pthread_mutex_unlock(&ctx->state_mutex);
                pthread_mutex_unlock(&ctx->coders[i].mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&ctx->coders[i].mutex);
            i++;
        }
        usleep(500);
    }
    return (NULL);
}

