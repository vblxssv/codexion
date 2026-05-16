/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 21:13:29 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 21:23:16 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H
# include <pthread.h>
# include "p_queue.h"

typedef struct s_dongle
{
	pthread_mutex_t	dongle_mutex;

	long long		cooldown_until;
	t_queue			*queue;
}	t_dongle;

t_dongle	*ft_init_dongles(unsigned int amount, char	*mode);
void		ft_free_dongles(t_dongle	*dongles, unsigned int amount);
void		ft_get_dongle_order(t_dongle	*d1, t_dongle	*d2,
				t_dongle	**first, t_dongle	**second);
void		ft_lock_pair(t_dongle	*d1, t_dongle	*d2);
void		ft_unlock_pair(t_dongle	*d1, t_dongle	*d2);

#endif