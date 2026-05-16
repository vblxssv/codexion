/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:58:19 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/14 16:51:37 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H
# include "args.h"
# include "coder.h"
# include "dongle.h"
# include "scheduler.h"
# include "monitor_r.h"
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_coder	t_coder;

typedef struct s_context
{
	t_args			args;
	t_dongle		*dongles;
	t_coder			*coders;

	long long		start_time;
	bool			is_running;
	pthread_mutex_t	state_mutex;

	pthread_t		scheduler_thread;
	pthread_t		monitor_thread;
}	t_context;

bool	ft_init_context(t_context *ctx, int argc, char **argv);
void	ft_free_context(t_context	*ctx);

bool	ft_get_running(t_context	*ctx);
void	ft_set_running(t_context	*ctx, bool irsng);

void	ft_run_simulation(t_context	*ctx);
void	ft_wait_simulation(t_context *ctx);

#endif