/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:14:23 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/04 12:29:18 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		g_exit_status;

void	ft_initialize(char ***env, char ***export, char **pwd, char **env1)
{
	*env = fill_env(env1);
	*export = fill_env(*env);
	*pwd = malloc(sizeof(char) * (1024 + 1));
}

int	check_main_args(t_main_var *var)
{
	if (!check_is_empty(var->input))
	{
		free(var->input);
		return (0);
	}
	if (check_quotes_and_add_to_list(var))
		return (0);
	if (!check_errors(var))
	{
		free_t_vars(var->head);
		free(var->input);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_main_var	var;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	ft_initialize(&var.env, &var.exprt, &var.pwd, env);
	while (1)
	{
		handle_signals();
		var.input = readline("my-minishell-3.2$ ");
		if (!var.input)
			exit(0);
		if (ft_strcmp(var.input, ""))
		{
			if (!check_main_args(&var))
				continue ;
			var.args = NULL;
			check_and_pass(var.head, &(var.args));
			creat_child(&var);
		}
		else
			free(var.input);
	}
	return (0);
}
