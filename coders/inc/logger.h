/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:45:29 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/11 22:09:51 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H
# include <stdio.h>
# include "time_utils.h"
# include "coder.h"

typedef struct s_coder	t_coder;

void	ft_log(t_coder	*coder, char	*msg);

#endif