/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohendrix <ohendrix@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:11:08 by ohendrix      #+#    #+#                 */
/*   Updated: 2024/03/21 17:11:43 by ohendrix      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroyforks(t_data *data, int i, int k)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->forks[j].fork);
		j++;
	}
	if (k != 0)
	{
		j = 0;
		while (j < k)
		{
			pthread_mutex_destroy(&data->philosophers[j].updatemeal);
			j++;
		}
	}
	pthread_mutex_destroy(&data->datamutex);
	pthread_mutex_destroy(&data->write);
	free(data->forks);
	free(data->philosophers);
	return (1);
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		k;
	long	nb;

	i = 0;
	k = 0;
	nb = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			k++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	if (k == 1)
		nb = -nb;
	return (nb);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_action(int philo_id, char *action, t_data *data)
{
	long			timestamp;

	timestamp = get_time() - data->start_simulation;
	pthread_mutex_lock(&data->write);
	printf("%ld %d %s\n", timestamp, philo_id, action);
	pthread_mutex_unlock(&data->write);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(300);
	return (0);
}
