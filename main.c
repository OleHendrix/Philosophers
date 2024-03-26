/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olehendrix <olehendrix@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:56:54 by ohendrix          #+#    #+#             */
/*   Updated: 2024/03/26 23:58:53 by olehendrix       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_jointhreads(t_data *data, pthread_t observer)
{
	int	i;

	i = 0;
	while (i < data->philocount)
	{
		if (pthread_join(data->philosophers[i].idthread, NULL))
			return (1);
		i++;
	}
	write_bool(&data->datamutex, &data->end_simulation, true);
	if (pthread_join(observer, NULL))
		return (1);
	return (0);
}

int	ft_initthreads(t_data *data)
{
	int			i;
	pthread_t	observer;

	i = 0;
	if (data->philocount == 1)
	{
		if (pthread_create(&data->philosophers[i].idthread, NULL,
				(void *)handleone, &data->philosophers[i]))
			return (1);
	}
	else
	{
		while (i < data->philocount)
		{
			if (pthread_create(&data->philosophers[i].idthread, NULL,
					(void *)routine, &data->philosophers[i]))
				return (1);
			i++;
		}
	}
	if (pthread_create(&observer, NULL, (void *)observing, data))
		return (1);
	data->start_simulation = get_time();
	write_bool(&data->datamutex, &data->ready, true);
	return ((bool)ft_jointhreads(data, observer));
}

int	ft_init(t_data *data, int argc, char **argv)
{
	if (ft_initialize(data, argc, argv))
		return (1);
	if (ft_alloc(data))
		return (1);
	if (ft_initforks(data))
		return (1);
	if (ft_initphilos(data))
		return (1);
	if (ft_initthreads(data))
		return (2);
	return (0);
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philocount)
	{
		pthread_mutex_destroy(&data->philosophers[i].updatemeal);
		pthread_mutex_destroy(&data->philosophers[i].leftfork->fork);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->datamutex);
	free(data->forks);
	free(data->philosophers);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_checkinput(argv, argc))
		return (1);
	if (ft_init(&data, argc, argv) == 1)
		return (1);
	ft_clean(&data);
	return (0);
}
