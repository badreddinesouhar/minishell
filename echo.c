/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:57:56 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/03 22:51:00 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	echo2(t_helper *help, int i, int j, char **env)
{
	(void)env;
	while (help->argv[++i])
	{
		j = 0;
		ft_putstr_fd(help->argv[i], 1);
		if (i < ft_strlen_array(help->argv) - 1)
			write(1, " ", 1);
	}
}

int	check_option(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && !s[i + 1])
		return (0);
	if (s[i] == '-')
		i++;
	else
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_helper *help, char **env)
{
	int	i;
	int	check;
	int	j;

	check = 0;
	i = 1;
	j = 0;
	if (ft_strlen_array(help->argv) == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	if (check_option(help->argv[i]))
	{
		check = 1;
		while (help->argv[i] && check_option(help->argv[i]))
			i++;
	}
	i--;
	echo2(help, i, j, env);
	g_exit_status = 0;
	if (!check)
		write(1, "\n", 1);
}

int	check(t_vars *head)
{
	if (!head)
		return (1);
	if (!ft_strcmp(head->data, "|") || !ft_strcmp(head->data, ">")
		|| !ft_strcmp(head->data, "<") || !ft_strcmp(head->data, ">>")
		|| !ft_strcmp(head->data, "<<"))
		return (1);
	return (0);
}

int	check2(t_vars *head)
{
	if (!head || !head->data)
		return (0);
	if (!head->data)
		return (0);
	if ((!ft_strcmp(head->data, ">") || !ft_strcmp(head->data, "<")
			|| !ft_strcmp(head->data, ">>") || !ft_strcmp(head->data, "<<")))
		return (1);
	return (0);
}
