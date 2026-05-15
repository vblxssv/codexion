/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:45:17 by vborysov          #+#    #+#             */
/*   Updated: 2026/05/14 16:38:43 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "time_utils.h"
#include "context.h"
#include "args.h"
#include "p_queue.h"
#include "dongle.h"
#include "scheduler.h"
#include "monitor_r.h"

int	main(int argc, char	**argv)
{
	t_context	context;

	if (!ft_init_context(&context, argc, argv))
	{
		printf("ERROR: Initialization context\n");
		return (1);
	}
	ft_run_simulation(&context);
	ft_wait_simulation(&context);
	ft_free_context(&context);
	return (0);
}
