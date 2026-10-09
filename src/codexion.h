/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalayyou <nalayyou@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:10:08 by nalayyou          #+#    #+#             */
/*   Updated: 2026/10/08 17:10:10 by nalayyou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config	t_config;
typedef struct s_pq		t_pq;

typedef enum e_dongle_state
{
	BUSY,
	FREE
}						t_dongle_state;

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

/*
** One dongle sits between two neighbouring coders.
** mutex   : protects state and released_at
** waiters : heap of coders waiting for this dongle,
**           only touched while holding config->table_mutex
*/
typedef struct s_dongle
{
	long long			released_at;
	int					state;
	int					cooldown;
	pthread_mutex_t		mutex;
	t_pq				*waiters;
}						t_dongle;

/*
** time_of_last_compile and compiles_left are shared with the monitor:
** always accessed under config->simulation_mutex.
*/
typedef struct s_coder
{
	int					time_to_burnout;
	int					number;
	int					compiles_left;
	long long			time_of_last_compile;
	pthread_t			thread;
	t_dongle			*left;
	t_dongle			*right;
	t_config			*config;
}						t_coder;

/*
** simulation_mutex : state_of_sim, coders' compile counters and timestamps
** print_mutex      : serializes every line written on stdout
** table_mutex/cond : dongle arbitration, coders sleep on table_cond until
**                    a dongle is released or a cooldown expires
*/
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
	long long			start_of_simulation;
	t_dongle			*dongles;
	t_coder				*coders;
	long long			state_of_sim;
	pthread_mutex_t		simulation_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		table_mutex;
	pthread_cond_t		table_cond;
}						t_config;

typedef struct s_node
{
	int					value;
	size_t				priority;
	size_t				ticket_id;
}						t_node;

/* min-heap ordered by (priority, ticket): ticket 0 is reserved */
typedef struct s_pq
{
	t_node				*heap;
	size_t				capacity;
	size_t				count;
	size_t				ticket;
}						t_pq;

/* main.c / parse.c */
int						parsing_args(char **args);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);

/* init_struct.c / cleanup.c */
void					*init_config(char **args, t_config *config);
int						init_table(t_config *config);
t_dongle				*init_dongles(t_config *config);
t_coder					*init_coders(t_config *config, t_dongle *dongles);
void					cleanup_dongles(t_dongle *dongles, int number);
void					cleanup(t_config *config);

/* simulation.c / monitor.c / check_sim_status.c */
int						simulate(char **args);
void					*monitor(void *uncasted_config);
int						check_sim_state(t_coder *coder);

/* compile.c / debug.c / refactor.c */
int						compile(t_coder *coder);
int						debug(t_coder *coder);
int						refactor(t_coder *coder);

/* dongle arbitration: server.c / wait.c / acquire.c / release.c */
long long				get_coder_priority(t_coder *coder);
bool					is_my_turn(t_coder *coder);
void					wait_turn(t_coder *coder);
t_value					acquire_dongles(t_coder *coder);
void					release_dongles(t_coder *coder);
void					wake_all_waiters(t_config *config);

/* priority queue: pq.c / pq_checks.c / pq_helpers.c */
t_pq					*init_pq(size_t capacity);
void					free_pq(t_pq *pq);
bool					pq_insert(t_pq *pq, int value, size_t priority);
bool					pq_pop(t_pq *pq, int *id);
bool					pq_remove(t_pq *pq, int value);
int						pq_peek(t_pq *pq);
bool					pq_is_empty(t_pq *pq);
void					pq_sift_up(t_pq *pq, size_t index);
void					pq_sift_down(t_pq *pq);

/* utils.c / print.c / smart_sleep.c */
long long				get_time_ms(void);
void					ft_putstr_fd(char *message, int fd);
void					print_state(t_coder *coder, char *state);
void					smart_sleep(t_coder *coder, long long time_in_ms);

#endif
