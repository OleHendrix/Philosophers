/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohendrix <ohendrix@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 16:56:12 by ohendrix      #+#    #+#                 */
/*   Updated: 2024/03/26 17:44:28 by ohendrix      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checkinput(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[2]) < ft_atoi(argv[3]) + ft_atoi(argv[4]))
		return (1);
	return (0);
}

int	ft_initialize(t_data *data, int argc, char **argv)
{
	data->philocount = ft_atoi(argv[1]);
	data->timetodie = ft_atol(argv[2]);
	data->timetoeat = ft_atol(argv[3]);
	data->timetosleep = ft_atol(argv[4]);
	if (argc == 6)
		data->limitmeals = ft_atoi(argv[5]);
	else
		data->limitmeals = -1;
	data->end_simulation = false;
	data->ready = false;
	data->threadsrunning = 0;
	if (pthread_mutex_init(&data->datamutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->write, NULL))
		return (pthread_mutex_destroy(&data->datamutex), 1);
	return (0);
}

int	ft_alloc(t_data *data)
{
	data->forks = malloc(data->philocount * sizeof(t_fork));
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->datamutex);
		pthread_mutex_destroy(&data->write);
		return (1);
	}
	data->philosophers = malloc(data->philocount * sizeof(t_philo));
	if (!data->philosophers)
	{
		pthread_mutex_destroy(&data->datamutex);
		pthread_mutex_destroy(&data->write);
		return (free(data->forks), 1);
	}
	return (0);
}

static void	assign_forks(t_philo *philo, t_fork *forks,
		int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philocount;
	philo->rightfork = &forks[(philo_position + 1) % philo_nbr];
	philo->leftfork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->rightfork = &forks[philo_position];
		philo->leftfork = &forks[(philo_position + 1) % philo_nbr];
	}	
}

int	ft_initforks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philocount)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (destroyforks(data, i, 0));
		data->forks[i].forkid = i;
		i++;
	}
	return (0);
}

int	ft_initphilos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philocount)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].mealscount = 0;
		data->philosophers[i].full = false;
		data->philosophers[i].data = data;
		data->philosophers[i].philocount = data->philocount;
		data->philosophers[i].timetodie = data->timetodie;
		data->philosophers[i].timetoeat = data->timetoeat;
		data->philosophers[i].timetosleep = data->timetosleep;
		data->philosophers[i].limitmeals = data->limitmeals;
		data->philosophers[i].end_simulation = 0;
		if (pthread_mutex_init(&data->philosophers[i].updatemeal, NULL))
			return (destroyforks(data, data->philocount, i));
		assign_forks(&data->philosophers[i], data->forks, i);
		i++;
	}
	return (0);
}
