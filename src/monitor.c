#include "codexion.h"

void	*monitor(void *uncasted_config)
{
	t_config	*config;
	int			all_compiled;
	int         i;

	config = (t_config *)uncasted_config;
	all_compiled = 1;
	while (1)
	{
		i = 0;
		all_compiled = 1;
		while (i < config->number_of_coders)
		{
			if (config->time_to_burnout <= get_time_ms()
				- config->coders[i].time_of_last_compile)
			{
				printf("coder %d burned out\n", i);
                pthread_mutex_lock(&config->simulation_mutex);
				config->state_of_sim = 0;
                pthread_mutex_unlock(&config->simulation_mutex);
				return (NULL);
			}
			if (config->coders[i].compiles_left)
				all_compiled = 0;
			i++;
		}
		if (all_compiled)
		{
            pthread_mutex_lock(&config->simulation_mutex);
			config->state_of_sim = 0;
            pthread_mutex_unlock(&config->simulation_mutex);
			return (NULL);
		}
	sleep(1000);
    }
}
