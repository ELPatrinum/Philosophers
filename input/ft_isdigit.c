/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:25:47 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/17 13:58:20 by muel-bak         ###   ########.fr       */
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
	int i;

	i = 0;
	if (!str)
	{
		write(2, ":is_all_digit: Null Ptr\n", 25);
		return (false);
	}
	while(str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

bool	is_valid(char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!is_all_digit(av[i]))
			return (false);
		i++;
	}
	return (true);
}
