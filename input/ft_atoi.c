/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:50:57 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/17 13:53:57 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long	calc_result(long tmp, long result, char c, size_t sign)
{
	tmp = (result * 10) + (c - 48);
	if (tmp < result && sign == 1)
		return (-1);
	else if (tmp < result && sign == -1)
		return (0);
	return (tmp);
}

size_t	ft_atoi(const char *str)
{
	size_t		i;
	size_t		sign;
	long	result;
	long	tmp;

	i = 0;
	sign = 1;
	result = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = calc_result(tmp, result, str[i], sign);
		i++;
	}
	return (sign * result);
}
