/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohendrix <ohendrix@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:11:47 by ohendrix      #+#    #+#                 */
/*   Updated: 2024/03/22 15:12:01 by ohendrix      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waitallthreads(t_data *data)
{
	while (!read_bool(&data->datamutex, &data->ready))
		;
}

bool	allrun(pthread_mutex_t *mtx, int *threads, int philocount)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mtx);
	if (*threads == philocount)
		ret = true;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	increaselong(pthread_mutex_t *mtx, int *value)
{
	pthread_mutex_lock(mtx);
	(*value)++;
	pthread_mutex_unlock(mtx);
}

bool	philodied(t_philo philo)
{
	if ((get_time() - read_long(&philo.updatemeal, &philo.lastmealtime))
		> philo.timetodie)
		return (true);
	return (false);
}
