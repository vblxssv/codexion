/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:45:17 by vborysov          #+#    #+#             */
/*   Updated: 2026/04/25 00:55:21 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../inc/args.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (!fn_parse_args(argc, argv, &args))
	{
		printf("Error: Invalid or incomplete arguments\n");
		return (1);
	}
	printf("--- Configuration Loaded ---\n");
	printf("Coders     : %d\n", args.number_of_coders);
	printf("Burnout    : %d\n", args.time_to_burnout);
	printf("Compile    : %d\n", args.time_to_compile);
	printf("Debug      : %d\n", args.time_to_debug);
	printf("Refactor   : %d\n", args.time_to_refactor);
	printf("Compiles Req: %d\n", args.number_of_compiles_required);
	printf("Dongle CD  : %d\n", args.dongle_cooldown);
	printf("Scheduler  : %s\n", args.scheduler);
	printf("----------------------------\n");
	return (0);
}
