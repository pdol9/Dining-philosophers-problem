/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/09/15 18:00:47 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

int	args_validation(int ac, char *av[])
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf(" %s>> invalid number of arguments%s\n", RED, CLEAR);
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 0 || check_digit(av[i]))
		{
			printf(" %s>> invalid input%s\n", RED, CLEAR);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	r;

	i = 0;
	r = 0;
	sign = 1;
	while ((s[i] == ' ') || (s[i] <= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		r = r * 10 + (s[i++] - '0');
	return (sign * r);
}
