/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:25:47 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/27 23:35:17 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static bool	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(2, ":is_all_digit: Null Ptr\n", 25);
		return (false);
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

int	l_z(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (!str)
	{
		write(2, ":l_z: Null Ptr\n", 16);
		return (false);
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[j])
		j++;
	len = j - i;
	return (len);
}

bool	fits(long nbr)
{
	if (nbr > INT_MAX || nbr < INT_MIN || nbr == 0)
		return (false);
	else
		return (true);
}

bool	is_valid(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_all_digit(av[i]) || l_z(av[i]) > 11 || !fits(ft_atoi(av[i])))
			return (false);
		i++;
	}
	return (true);
}
