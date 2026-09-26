#include "codexion.h"

void	*idk_yet(void *arg)
{
	printf("function idk yet\n");
	return (NULL);
}

void	*init_config(char **args, t_config *config)
{
	config->number_of_coders = ft_atoi(args[1]);
	config->time_to_burnout = ft_atoi(args[2]);
	config->time_to_compile = ft_atoi(args[3]);
	config->time_to_debug = ft_atoi(args[4]);
	config->time_to_refactor = ft_atoi(args[5]);
	config->number_of_compiles_required = ft_atoi(args[6]);
	config->dongle_cooldown = ft_atoi(args[7]);
	if (!(strcmp(args[8], "fifo")))
		config->scheduler = FIFO;
	else
		config->scheduler = EDF;
	config->start_of_simulation = get_time_ms();
	config->state_of_sim = 1;
	if (pthread_mutex_init(&config->simulation_mutex, NULL))
	{
		printf("simulation_mutex initialization failed\n");
		return (NULL);
	}
	if (pthread_mutex_init(&config->print_mutex, NULL))
	{
		printf("print mutex initialization failed\n");
		return (NULL);
	}
	return (NULL);
}

t_coder	*init_coders(t_config *config, t_dongle *dongles)
{
	int		i;
	t_coder	*coders;

	i = 0;
	coders = malloc((config->number_of_coders) * sizeof(t_coder));
	if (coders == NULL)
		return (NULL);
	while (i < config->number_of_coders)
	{
		coders[i].number = i;
		coders[i].config = config;
		coders[i].time_to_burnout = config->time_to_burnout;
		coders[i].time_of_last_compile = config->start_of_simulation;
		coders[i].compiles_left = config->number_of_compiles_required;
		coders[i].left = &dongles[i];
		coders[i].right = &dongles[(i + 1) % config->number_of_coders];
		i++;
	}
	return (coders);
}

t_dongle	*init_dongles(t_config *config)
{
	int			i;
	t_dongle	*dongles;

	i = 0;
	dongles = malloc(sizeof(t_dongle) * config->number_of_coders);
	if (dongles == NULL)
		return (NULL);
	while (i < config->number_of_coders)
	{
		if (pthread_mutex_init(&dongles[i].mutex, NULL))
			return (NULL);
		dongles[i].state = 1;
		dongles[i].cooldown = config->dongle_cooldown;
		i++;
	}
	return (dongles);
}
