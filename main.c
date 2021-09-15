#include "header.h"

void    *checker_meal(void    *ptr)
{
    t_philo_data    *data;
    int i;


    data = (t_philo_data *)ptr;
    while(1)
    {
        i = 0;
        while (i < game_args->number_of_philosophers)
        {
            if (data[i].meal_counter == game_args->number_of_times_each_philosopher_must_eat)
                i++;
            else
                break ;
        }
        if (i == game_args->number_of_philosophers)
            break ;
    }
    printf("MIN_MEAL_REACHED\nEND OF SIMULATION\n");
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&mutex);
    x = MIN_MEAL_REACHED;
    return (NULL);
}

void    *checker_death(void    *ptr)
{
    t_philo_data    *data;
    int             i;
    int             current_timestamp;

    data = (t_philo_data *)ptr;
    while(1)
    {
        i = 0;
        while (i < game_args->number_of_philosophers)
        {
            current_timestamp = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
                    - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
            if (current_timestamp < data[i].next_meal)
                i++;
            else
                break ;
        }
        if (i == game_args->number_of_philosophers)
            continue ;
        else
            break ;
    }
    print_status("died.\nEND OF SIMULATION", i);
    pthread_mutex_lock(&lock);
    pthread_mutex_lock(&mutex);
    x = PHILOSOPHER_DEATH;
    return (NULL);
}

void    checker_wave_deployment(t_philo_data    *data)
{
    pthread_t   min_meal;
    pthread_t   death;

    pthread_create(&min_meal, NULL, checker_meal, (void    *)data);
    pthread_create(&death, NULL, checker_death, (void    *)data);
    
}

int     main(int argc, char **argv)
{
    int i;
    pthread_t           *philosophers;
    t_philo_data        *data;
    int ret_value;
    i = 0;
    x = 0;
    gettimeofday(&start_time, NULL);
    game_args = malloc(sizeof(t_argv));
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&lock, NULL);
    if (!game_args)
        return (0);
    set_game_info(game_args);
    philosophers = malloc(game_args->number_of_philosophers * sizeof(pthread_t));
    forks = malloc(game_args->number_of_forks * sizeof(pthread_mutex_t));
    data = malloc(game_args->number_of_philosophers * sizeof(t_philo_data));
    if (!philosophers || !forks || !data)
        return (0);
    set_philo_data(data, game_args);
    forks_init();
    first_wave_deployment(philosophers, data);
    second_wave_deployment(philosophers, data);
    checker_wave_deployment(data);
    while(1)
    {
        if (x == PHILOSOPHER_DEATH || x == MIN_MEAL_REACHED)
            return (1);
    }
    //join_the_bunch(philosophers);
    //pthread_join(min_meal, NULL);
    //pthread_join(death, NULL);
    return (0);
}