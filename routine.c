/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olehendrix <olehendrix@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:07:02 by ohendrix          #+#    #+#             */
/*   Updated: 2024/03/26 23:44:58 by olehendrix       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rightfork->fork);
	ft_action(philo->id, "has taken a fork", philo->data);
	pthread_mutex_lock(&philo->leftfork->fork);
	ft_action(philo->id, "has taken a fork", philo->data);
	write_long(&philo->updatemeal, &philo->lastmealtime, get_time());
	philo->mealscount++;
	ft_action(philo->id, "is eating", philo->data);
	ft_usleep(philo->timetoeat);
	if (philo->mealscount == philo->limitmeals)
		write_bool(&philo->updatemeal, &philo->full, true);
	pthread_mutex_unlock(&philo->leftfork->fork);
	pthread_mutex_unlock(&philo->rightfork->fork);
}

void	*routine(void *philo2)
{
	t_philo	*philo;

	philo = (t_philo *)philo2;
	waitallthreads(philo->data);
	write_long(&philo->updatemeal, &philo->lastmealtime, get_time());
	increaselong(&philo->data->datamutex, &philo->data->threadsrunning);
	if (philo->id % 2 == 0)
		ft_usleep(20);
	while (!read_bool(&philo->data->datamutex, &philo->data->end_simulation))
	{
		if (read_bool(&philo->updatemeal, &philo->full))
			break ;
		ft_eat(philo);
		ft_action(philo->id, "is sleeping", philo->data);
		ft_usleep(philo->timetosleep);
		ft_action(philo->id, "is thinking", philo->data);
	}
	return (NULL);
}

void	*handleone(void *philo2)
{
	t_philo	*philo;

	philo = (t_philo *)philo2;
	waitallthreads(philo->data);
	write_long(&philo->updatemeal, &philo->lastmealtime, get_time());
	increaselong(&philo->data->datamutex, &philo->data->threadsrunning);
	pthread_mutex_lock(&philo->leftfork->fork);
	ft_action(philo->id, "has taken a fork", philo->data);
	while (!read_bool(&philo->data->datamutex, &philo->data->end_simulation))
		ft_usleep(20);
	pthread_mutex_unlock(&philo->leftfork->fork);
	return (NULL);
}

void	observing(void *data2)
{
	t_data	*data;
	int		i;

	data = (t_data *)data2;
	while (!allrun(&data->datamutex, &data->threadsrunning, data->philocount))
		;
	while (!read_bool(&data->datamutex, &data->end_simulation))
	{
		i = 0;
		while (i < data->philocount)
		{
			if (!read_bool(&data->philosophers[i].updatemeal,
					&data->philosophers[i].full))
			{
				if (philodied(data->philosophers[i]))
				{
					write_bool(&data->datamutex, &data->end_simulation, true);
					ft_action(data->philosophers[i].id, "died", data);
					break ;
				}
			}
			i++;
		}
		usleep(5000);
	}
}

