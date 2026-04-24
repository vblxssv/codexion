/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 21:31:29 by vborysov          #+#    #+#             */
/*   Updated: 2026/04/25 00:55:24 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "args.h"

static void	fn_init_args(t_args	*args)
{
	args->number_of_coders = -1;
	args->time_to_burnout = -1;
	args->time_to_compile = -1;
	args->time_to_debug = -1;
	args->time_to_refactor = -1;
	args->number_of_compiles_required = -1;
	args->dongle_cooldown = -1;
	args->scheduler = NULL;
}

static bool	fn_is_number(const char	*str)
{
	long	result;
	int		i;

	if (!str || str[0] == '\0')
		return (false);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (false);
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

static bool	fn_is_scheduler(const char	*str)
{
	return (strcmp(str, "FIFO") == 0 || strcmp(str, "EDF") == 0);
}

static bool	fn_fill_numeric(t_args	*args, char	*flag, char	*val)
{
	if (!fn_is_number(val))
		return (false);
	if (strcmp(flag, "--coders") == 0)
		args->number_of_coders = atoi(val);
	else if (strcmp(flag, "--burnout") == 0)
		args->time_to_burnout = atoi(val);
	else if (strcmp(flag, "--compile") == 0)
		args->time_to_compile = atoi(val);
	else if (strcmp(flag, "--debug") == 0)
		args->time_to_debug = atoi(val);
	else if (strcmp(flag, "--refactor") == 0)
		args->time_to_refactor = atoi(val);
	else if (strcmp(flag, "--compiles") == 0)
		args->number_of_compiles_required = atoi(val);
	else if (strcmp(flag, "--dongle") == 0)
		args->dongle_cooldown = atoi(val);
	else
		return (false);
	return (true);
}

bool	fn_parse_args(int argc, char	**argv, t_args	*args)
{
	int	i;

	if (argc != 17)
		return (false);
	fn_init_args(args);
	i = 1;
	while (i < argc)
	{
		if (strcmp(argv[i], "--scheduler") == 0)
		{
			if (!fn_is_scheduler(argv[i + 1]))
				return (false);
			args->scheduler = argv[i + 1];
		}
		else if (!fn_fill_numeric(args, argv[i], argv[i + 1]))
			return (false);
		i += 2;
	}
	if (args->number_of_coders == -1 || args->time_to_burnout == -1
		|| args->time_to_compile == -1 || args->time_to_debug == -1
		|| args->time_to_refactor == -1
		|| args->number_of_compiles_required == -1
		|| args->dongle_cooldown == -1 || args->scheduler == NULL)
		return (false);
	return (true);
}
