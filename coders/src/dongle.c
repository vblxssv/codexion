/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 21:21:32 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 15:18:31 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"
#include <string.h>

void	ft_get_dongle_order(t_dongle	*d1, t_dongle	*d2,
	t_dongle	**first, t_dongle	**second)
{
	if (d1 < d2)
	{
		*first = d1;
		*second = d2;
	}
	else
	{
		*first = d2;
		*second = d1;
	}
}

void	ft_lock_pair(t_dongle	*d1, t_dongle	*d2)
{
	t_dongle	*first;
	t_dongle	*second;

	ft_get_dongle_order(d1, d2, &first, &second);
	pthread_mutex_lock(&first->dongle_mutex);
	pthread_mutex_lock(&second->dongle_mutex);
}

void	ft_unlock_pair(t_dongle	*d1, t_dongle	*d2)
{
	pthread_mutex_unlock(&d1->dongle_mutex);
	pthread_mutex_unlock(&d2->dongle_mutex);
}
