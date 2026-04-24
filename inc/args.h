/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vborysov <vborysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 21:07:05 by vborysov          #+#    #+#             */
/*   Updated: 2026/04/25 00:55:19 by vborysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H
# include <stdbool.h>

typedef struct s_args
{
	int		number_of_coders; // --coders
	int		time_to_burnout; // --burnout
	int		time_to_compile; // --compile
	int		time_to_debug; // --debug
	int		time_to_refactor; // --refactor
	int		number_of_compiles_required; // --compiles
	int		dongle_cooldown; // --dongle
	char	*scheduler; // --scheduler
}				t_args;

bool	fn_parse_args(int argc, char	**argv, t_args	*args);

#endif
