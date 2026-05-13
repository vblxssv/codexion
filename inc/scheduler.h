/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:53:07 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/09 20:48:17 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_H
# define SCHEDULER_H
# include <pthread.h>
# include "context.h"
# include <stdio.h>

void	*ft_scheduler_routine(void	*args);

#endif