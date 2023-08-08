/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:14:16 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/04 12:25:49 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_all(t_main_var *var)
{
	add_history(var->input);
	free(var->input);
	free_t_parser(var->args);
	free_helper(var->help);
}

void	creat_child(t_main_var *var)
{
	int	i;
	int	check;

	var->help = malloc(sizeof(t_helper));
	var->join4 = NULL;
	check = 0;
	if (open_files(var->args))
	{
		if (var->args && !var->args->next && (var->args->type > 1
				&& var->args->type < 5))
			check = 1;
		if (!check)
		{
			i = ft_init(var);
			if (i == -1 && !var->args->next)
				built_ins(var);
			else if (i > -1 || var->args->next || var->args->type >= 0)
				execute_multiple_cmd(var);
		}
	}
	free_all(var);
}

int	check_quotes_and_add_to_list(t_main_var *var)
{
	int	i;

	i = 0;
	var->head = NULL;
	if (check_quotes(var->input, i))
	{
		var->split = ft_split(var->split, var->input, ' ', i);
		while (var->split[i])
			ft_add_list(&var->head, var->split[i++]);
		free_array(var->split);
	}
	else
	{
		ft_putstr_fd("Error Unclosing quote!\n", 2);
		g_exit_status = 258;
		add_history(var->input);
		free(var->input);
		return (1);
	}
	return (0);
}

int	check_is_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && !(input[i] >= 9
				&& input[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

void	print_exit_status(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putnbr_fd(g_exit_status, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
}
