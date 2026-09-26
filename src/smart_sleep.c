#include "codexion.h"

void	smart_sleep(t_coder *coder, long long time_in_ms)
{
	long long	time_in_micro;
	long long	started;

	time_in_micro = time_in_ms * 1000;
	started = get_time_ms();
	while (get_time_ms() - started < time_in_ms)
	{
		usleep(500); // usleep is jsut sleep in microseconds
		pthread_mutex_lock(&coder->config->simulation_mutex);
		if (!coder->config->state_of_sim)
		{
			pthread_mutex_unlock(&coder->config->simulation_mutex);
			return ;
		}
		pthread_mutex_unlock(&coder->config->simulation_mutex);
	}
}
