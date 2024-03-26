/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getters.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohendrix <ohendrix@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 16:53:10 by ohendrix      #+#    #+#                 */
/*   Updated: 2024/03/21 16:56:02 by ohendrix      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_bool(pthread_mutex_t *mtx, bool *dest, bool value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

bool	read_bool(pthread_mutex_t *mtx, bool *value)
{
	bool	read;

	pthread_mutex_lock(mtx);
	read = *value;
	pthread_mutex_unlock(mtx);
	return (read);
}

void	write_long(pthread_mutex_t *mtx, long *dest, long value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

long	read_long(pthread_mutex_t *mtx, long *value)
{
	long	read;

	pthread_mutex_lock(mtx);
	read = *value;
	pthread_mutex_unlock(mtx);
	return (read);
}
