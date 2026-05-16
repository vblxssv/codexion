/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 21:41:24 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 21:24:49 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H
# include <stdlib.h>

long long	ft_get_current_time(void);
long long	ft_get_relative_time(long long start_time);

#endif