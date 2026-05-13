/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:51:15 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 21:53:11 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H
# include <stdlib.h>
# include <pthread.h>
# include "dongle.h"
# include "context.h"
# include "time_utils.h"
# include <unistd.h>
# include "logger.h"

typedef enum e_state
{
	COMPILE,
	DEBUG,
	REFACTOR,
	IDLE
}	t_state;

typedef struct s_context	t_context;

typedef struct s_coder
{
	unsigned int	id;
	unsigned int	compiles;

	long long		deadline;
	bool			can_work;

	t_dongle		*left;
	t_dongle		*right;
	t_context		*ctx;

	t_state			state;

	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_coder;

t_coder		*ft_init_coders(t_context	*ctx);
void		ft_free_coders(t_coder	*coders);
t_request	ft_make_request(t_coder	*coder);
void		*ft_live_life(void *args);
void		ft_wake_up(t_coder	*coder);
void		ft_get_in_q(t_coder	*coder);

#endif