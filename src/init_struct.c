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
    if (!(strcmp(args[8],"fifo")))
            config->scheduler = FIFO;
    else
        config->scheduler = EDF;
    config->start_of_simulation = get the time!!
}

int init_threads(t_config *config)
{
	pthread_t	*threads;

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

int init_coders(t_config* config)
{   
    int i;
    i = 0; 
    t_coder *coders = malloc((config->number_of_coders)*sizeof(t_coder));
    while(i < config->number_of_coders)
    {
    coders[i].time_to_burnout = config->time_to_burnout;
    coders[i].time_of_last_compile = start of simulation;
    coders[i].compiles_left = config->number_of_compiles_required;

    }
} 
