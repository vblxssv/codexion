/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:58:19 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 21:23:53 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H
# include "args.h"
# include "coder.h"
# include "dongle.h"

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
}	t_context;

#endif