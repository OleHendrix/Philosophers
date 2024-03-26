/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohendrix <ohendrix@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 17:03:51 by ohendrix      #+#    #+#                 */
/*   Updated: 2024/03/26 17:43:57 by ohendrix      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# include "Libft/libft.h"

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					forkid;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				mealscount;
	bool			full;
	long			lastmealtime;
	int				philocount;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	int				limitmeals;
	int				end_simulation;
	t_fork			*leftfork;
	t_fork			*rightfork;
	pthread_t		idthread;
	t_data			*data;
	pthread_mutex_t	updatemeal;
}	t_philo;

typedef struct s_data
{
	int				philocount;
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	int				limitmeals;
	bool			ready;
	long			start_simulation;
	bool			end_simulation;
	int				threadsrunning;
	t_fork			*forks;
	t_philo			*philosophers;
	pthread_mutex_t	datamutex;
	pthread_mutex_t	write;
}	t_data;

int		ft_checkinput(char **argv, int argc);
int		ft_initialize(t_data *data, int argc, char **argv);
int		ft_alloc(t_data *data);
int		ft_initforks(t_data *data);
int		ft_initphilos(t_data *data);
long	get_time(void);
void	write_bool(pthread_mutex_t *mtx, bool *dest, bool value);
bool	read_bool(pthread_mutex_t *mtx, bool *value);
void	write_long(pthread_mutex_t *mtx, long *dest, long value);
long	read_long(pthread_mutex_t *mtx, long *value);
void	ft_clean(t_data *data);
int		ft_init(t_data *data, int argc, char **argv);
int		ft_initthreads(t_data *data);
int		ft_jointhreads(t_data *data, pthread_t observer);
void	ft_eat(t_philo *philo);
void	*routine(void *philo2);
void	*handleone(void *philo2);
void	observing(void *data2);
int		destroyforks(t_data *data, int i, int k);
long	ft_atol(const char *nptr);
long	get_time(void);
void	ft_action(int philo_id, char *action, t_data *data);
int		ft_usleep(size_t milliseconds);
void	waitallthreads(t_data *data);
bool	allrun(pthread_mutex_t *mtx, int *threads, int philocount);
void	increaselong(pthread_mutex_t *mtx, int *value);
bool	philodied(t_philo philo);

#endif
