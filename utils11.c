/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:19:38 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/07 12:19:39 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exit(char **av)
{
	int	len;

	len = ft_strlen_array(av);
	if (len == 1)
		exit(g_exit_status);
	else
	{
		if (len == 2 && is_digit(av[1]))
		{
			exit(ft_atoi(av[1]));
		}
		else if (len > 2 && is_digit(av[1]))
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return ;
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(255);
		}
	}
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	if (!*str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (sign * res);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (0);
		i++;
	}
	return (1);
}

void	create_child_proc2(t_main_var *var)
{
	t_parser	*tmp;

	tmp = var->args->next;
	while (tmp)
	{
		if (tmp->type > 1)
			modify_files(tmp);
		else if (tmp->type == 1)
			break ;
		tmp = tmp->next;
	}
	execute_one_cmd(var);
}
