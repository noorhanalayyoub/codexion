#include "codexion.h"

int	check_sim_state(t_coder *coder)
{
	int	result;

	pthread_mutex_lock(&coder->config->simulation_mutex);
	result = coder->config->state_of_sim;
	pthread_mutex_unlock(&coder->config->simulation_mutex);
	return (result);
}
