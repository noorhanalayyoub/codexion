#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_config t_config;

typedef enum r_value{
    SUCCESS,
    FAILURE
}t_value;

typedef enum s_scheduler{
    FIFO,
    EDF
}t_scheduler;

typedef struct s_dongle{
    int state;
    int cooldown;
    pthread_mutex_t mutex;
}t_dongle;

typedef struct s_coder{
    int time_to_burnout;
    int number;
    int compiles_left;
    int time_of_last_compile;
    pthread_t thread;
    t_dongle *left;
    t_dongle *right;
    t_config* config;
}t_coder;


typedef struct s_config{
int number_of_coders;
int time_to_burnout;
int time_to_compile;
int time_to_debug;
int time_to_refactor;
int number_of_compiles_required;
int dongle_cooldown;
t_scheduler scheduler;
int start_of_simulation;
t_dongle* dongles;
t_coder* coders;
int state_of_sim; // 1 for working 
pthread_mutex_t simulation_mutex;
}t_config;

int parsing_args(char **args);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void* init_config(char **args, t_config* config);
t_coder* init_coders(t_config* config, t_dongle* dongles);
int init_threads(t_config *config);
t_dongle* init_dongles(t_config *config);
void ft_putstr_fd(char *message, int fd);
long long get_time_ms(void);
void smart_sleep(t_coder* coder, long long time_in_ms);
void	*monitor(void *uncasted_config);
int simulate(char **args);

#endif
