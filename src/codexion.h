#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
#include <stdbool.h>


typedef struct s_config	t_config;
typedef struct s_pq t_pq;


typedef enum e_dongle_state
{
	BUSY,
	FREE
} t_dongle_state;

typedef enum r_value
{
	SUCCESS,
	FAILURE
}						t_value;

typedef enum s_scheduler
{
	FIFO,
	EDF
}						t_scheduler;

typedef struct s_dongle
{   
    long long           released_at;
	int					state;
	int					cooldown;
	pthread_mutex_t		mutex;
	pthread_cond_t		dongle_cond;
	t_pq				*waiters;
}						t_dongle;

typedef struct s_coder
{
	int					time_to_burnout;
	int					number;
	int					compiles_left;
	long long           time_of_last_compile;
	pthread_t			thread;
	t_dongle			*left;
	t_dongle			*right;
	t_config			*config;
}						t_coder;

typedef struct s_config
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	t_scheduler			scheduler;
	long long           start_of_simulation;
	t_dongle			*dongles;
	t_coder				*coders;
	long long state_of_sim; // 1 for working
	pthread_mutex_t		simulation_mutex;
	pthread_mutex_t		print_mutex;
}						t_config;

typedef struct s_node
{
	int							value;
	size_t					    priority;
	size_t						ticket_id;
}								t_node;

typedef struct s_pq
{
	t_node				    *heap;
	size_t					capacity;
	size_t					count;
	size_t					ticket;
}							t_pq;

// interface
t_pq*					init_pq(size_t capacity);
void					free_pq(t_pq *pq);
bool					pq_is_empty(t_pq* pq);
bool					pq_insert(t_pq* pq, int value, size_t priority);
bool                    pq_pop(t_pq* pq, int* id);
int						pq_peek(t_pq *pq);
// helpers
void    				pq_sift_up(t_pq* pq);
void    				pq_sift_down(t_pq* pq);
int						parsing_args(char **args);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);
void					*init_config(char **args, t_config *config);
t_coder					*init_coders(t_config *config, t_dongle *dongles);
int						init_threads(t_config *config);
t_dongle				*init_dongles(t_config *config);
void					ft_putstr_fd(char *message, int fd);
long long				get_time_ms(void);
void					smart_sleep(t_coder *coder, long long time_in_ms);
void					*monitor(void *uncasted_config);
int						simulate(char **args);
int						check_sim_state(t_coder *coder);
void	                print_state(t_coder *coder, char *state);
t_value					request_dongle(t_coder *coder, t_dongle *dongle);
void					release_dongle(t_dongle *dongle);
void	cleanup_dongles(t_dongle *dongles, int number);
void	cleanup(t_config *config);

#endif
