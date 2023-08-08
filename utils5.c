/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:24:36 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 22:24:38 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getlen(int n)
{
	int	count;

	count = 1;
	if (n < 0)
		count++;
	while (n / 10)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_abs_val(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = ft_getlen(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = 0;
	if (n < 0)
		res[0] = '-';
	else if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		res[--len] = ft_abs_val(n % 10) + '0';
		n /= 10;
	}
	return (res);
}
