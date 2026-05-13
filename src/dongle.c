/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 21:21:32 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 21:40:54 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"
#include <string.h>

static t_sched_mode	ft_get_mode(char	*mode)
{
	if (strcmp(mode, "edf") == 0)
		return (MODE_EDF);
	else if (strcmp(mode, "fifo") == 0)
		return (MODE_FIFO);
	return (MODE_FIFO);
}

t_dongle	*ft_init_dongles(unsigned int amount, char	*mode)
{
	t_dongle		*dongles;
	unsigned int	i;

	dongles = malloc(sizeof(t_dongle) * amount);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		dongles[i].cooldown_until = 0;
		dongles[i].queue = NULL;
		if (pthread_mutex_init(&dongles[i].dongle_mutex, NULL) != 0)
			return (ft_free_dongles(dongles, i), NULL);
		dongles[i].queue = ft_create_queue(10, ft_get_mode(mode));
		if (!dongles[i].queue)
			return (ft_free_dongles(dongles, i + 1), NULL);
		i++;
	}
	return (dongles);
}

void	ft_free_dongles(t_dongle	*dongles, unsigned int amount)
{
	unsigned int	i;

	if (!dongles)
		return ;
	i = 0;
	while (i < amount)
	{
		ft_delete_queue(dongles[i].queue);
		pthread_mutex_destroy(&dongles[i].dongle_mutex);
		++i;
	}
	free(dongles);
}

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
