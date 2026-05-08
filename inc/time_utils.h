/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 21:41:24 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/07 21:46:40 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H
# include <stdlib.h>

long long	ft_get_current_time(void);
long long	ft_get_relative_time(long long start_time);

#endif
