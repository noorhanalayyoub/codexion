#include "codexion.h"

void	*idk_yet(void *arg)
{
	printf("function idk yet\n");
	return (NULL);
}

void	init_config(char **args, t_config *config)
{
	config->number_of_coders = ft_atoi(args[1]);
	config->time_to_burnout = ft_atoi(args[2]);
	config->time_to_compile = ft_atoi(args[3]);
	config->time_to_debug = ft_atoi(args[4]);
	config->time_to_refactor = ft_atoi(args[5]);
	config->number_of_compiles_required = ft_atoi(args[6]);
	config->dongle_cooldown = ft_atoi(args[7]);
	config->scheduler = args[8];
}

int	init_coders(t_config *config)
{
	pthread_t	*threads;
	int			i;

	threads = malloc((config->number_of_coders)* sizeof(pthread_t));
	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_create(threads + i, NULL, idk_yet(NULL), NULL))
		{
			printf("error creating a thread\n");
			return (-1);
		}
	}
}
