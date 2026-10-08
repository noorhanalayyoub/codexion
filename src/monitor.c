#include "codexion.h"

/* static void	wake_all_waiters(t_config *config)
{
	int	i;
 
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_mutex_lock(&config->dongles[i].mutex);
		pthread_cond_broadcast(&config->dongles[i].dongle_cond);
		pthread_mutex_unlock(&config->dongles[i].mutex);
		i++;
	}
}
*/
// claude suggested this fucntion , tested and code still fails
void	*monitor(void *uncasted_config)
{
	t_config	*config;
	int			all_compiled;
	int			i;

	config = (t_config *)uncasted_config;
	all_compiled = 1;
	while (1)
	{
		i = 0;
		all_compiled = 1;
		while (i < config->number_of_coders)
		{
			pthread_mutex_lock(&config->simulation_mutex);
			if (config->time_to_burnout <= get_time_ms()
				- config->coders[i].time_of_last_compile)
			{
				printf("coder %d burned out\n", i+1);
				config->state_of_sim = 0;
				pthread_mutex_unlock(&config->simulation_mutex);
				return (NULL);
			}
			if (config->coders[i].compiles_left)
				all_compiled = 0;
			i++;
			pthread_mutex_unlock(&config->simulation_mutex);
		}
		if (all_compiled)
		{
			pthread_mutex_lock(&config->simulation_mutex);
			config->state_of_sim = 0;
			pthread_mutex_unlock(&config->simulation_mutex);
//            wake_all_waiters(config);
			return (NULL);
		}
		usleep(1000); // changed this from sleeping 1000 seconds to 1ms
	}
}
