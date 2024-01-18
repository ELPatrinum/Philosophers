/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:59:50 by muel-bak          #+#    #+#             */
/*   Updated: 2024/01/18 22:20:14 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

static int	print_error(void)
{
	printf(ANSI_COLOR_RED ERROR_MG ANSI_COLOR_RESET "\n");
	printf("\033[4;31m" ERROR_MG2 ANSI_COLOR_RESET "\n");
	return (1);
}

static int	print_help(void)
{
	printf(ANSI_COLOR_GREEN CORRECT_MG ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_GREEN CORRECT_MG2 ANSI_COLOR_RESET "\n");
	return (0);
}

int	error_(char *str)
{
	if (!str)
		return (print_error());
	if (!ft_strncmp(str, "-help", 5))
		return (print_help());
	else
		return (print_error());
}
