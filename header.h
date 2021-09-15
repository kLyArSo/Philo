#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define N 100
#define SUCCESS 1
#define FAILURE 1
#define MIN_MEAL_REACHED 98
#define PHILOSOPHER_DEATH 100
#include <sys/time.h>

typedef struct  s_argv
{
    int number_of_philosophers;
    int number_of_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}               t_argv;


typedef struct  s_philo_data
{
    int philo_index;
    int philo_fork_1;
    int philo_fork_2;
    int meal_counter;
    int last_meal;
    int next_meal;
}               t_philo_data;

pthread_mutex_t         mutex;
pthread_mutex_t         lock;
pthread_mutex_t         *forks;
struct timeval          current_time;
struct timeval          start_time;
struct timeval          var;
t_argv                  *game_args;
int x;

void    join_the_bunch(pthread_t    *philosophers);
void    second_wave_deployment(pthread_t    *philosophers, t_philo_data *data);
void    first_wave_deployment(pthread_t *philosophers, t_philo_data  *data);
void    forks_init();
void    set_philo_data(t_philo_data *data, t_argv  *game_args);
void    *entry_point(void   *ptr);
void    set_game_info(t_argv  *game_args);
void    print_status(char *str, int x);