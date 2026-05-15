/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:18:10 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/15 15:19:19 by vborysov         ###   ########.fr       */
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
