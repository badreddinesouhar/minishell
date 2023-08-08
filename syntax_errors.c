/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:04:29 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/04 00:14:17 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count(char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			j++;
		else
			return (j);
		i++;
	}
	return (j);
}

int	check_pipes(t_vars *vars)
{
	t_vars	*tmp;

	tmp = vars;
	if (vars->data[0] == '|')
		return (0);
	while (vars)
	{
		if (!vars->next)
		{
			if (vars->data[0] == '|')
				return (0);
		}
		vars = vars->next;
	}
	vars = tmp;
	while (vars)
	{
		if (count(vars->data, '|') > 1)
			return (0);
		vars = vars->next;
	}
	return (1);
}

int	check_red_in_out(t_vars *vars, char q)
{
	while (vars)
	{
		if (!vars->next)
		{
			if (vars->data[0] == q)
				return (0);
		}
		vars = vars->next;
	}
	return (1);
}

int	check_app_her(t_vars *vars, char *type, char c)
{
	t_vars	*tmp;

	tmp = vars;
	while (vars)
	{
		if (!vars->next)
		{
			if (!ft_strcmp(vars->data, type))
				return (0);
		}
		vars = vars->next;
	}
	vars = tmp;
	while (vars)
	{
		if (count(vars->data, c) > 2)
			return (0);
		vars = vars->next;
	}
	return (1);
}

int	check_errors(t_main_var *var)
{
	if (!check_pipes(var->head))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_exit_status = 258;
		add_history(var->input);
		return (0);
	}
	if (!check_app_her(var->head, ">>", '>') || !check_app_her(var->head, "<<",
			'<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `newline'\n", 2);
		g_exit_status = 258;
		add_history(var->input);
		return (0);
	}
	if (!check_red_in_out(var->head, '>') || !check_red_in_out(var->head, '<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `newline'\n", 2);
		g_exit_status = 258;
		add_history(var->input);
		return (0);
	}
	return (1);
}
