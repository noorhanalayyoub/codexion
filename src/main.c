/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:42:16 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:42:19 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_args(char **argv)
{
	int	return_value;

	return_value = parsing_args(argv);
	if (return_value == FAILURE)
	{
		fprintf(stderr, "invalid number\n");
		return (1);
	}
	if (strcmp(argv[8], "fifo") && strcmp(argv[8], "edf"))
	{
		fprintf(stderr, "invalid scheduler\n");
		return (1);
	}
	if (atoi(argv[1]) == 0)
	{
		fprintf(stderr, "number of coders cant be zero\n");
		return (1);
	}
	if (atoi(argv[6]) == 0)
	{
		fprintf(stderr, "number of compiles cant be zero\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		fprintf(stderr,
			"number of command line arguments must be exactly 8\n"
			"usage:/.codexion number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown scheduler");
		return (1);
	}
	if (check_args(argv))
		return (1);
	simulate(argv);
}
