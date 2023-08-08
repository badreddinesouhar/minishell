/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:49:42 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/06 15:49:45 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_init_part1(t_main_var *var)
{
	int	i;
	int	j;

	i = -1;
	while (var->help->argv[++i])
	{
		j = -1;
		var->help->argv[i] = get_expand(var->help->argv[i], var->env,
				var->join4);
		if (var->help->argv[i])
		{
			var->split2 = ft_split2(var->help->argv[i], ' ');
			while (var->split2[++j])
			{
				var->tmp = ft_strdup(var->split2[j], 0);
				free(var->split2[j]);
				var->split2[j] = skip_quotes(var->tmp);
				free(var->tmp);
				var->tmp = NULL;
			}
			add_to_parser(&var->splits, var->split2);
		}
	}
}

int	ft_init_part2(t_main_var *var)
{
	var->help->paths = get_env_paths(var->env);
	if (!var->help->paths)
	{
		free(var->str);
		var->str = NULL;
		return (-2);
	}
	var->i = is_file_exist(var->help->paths, var->help->argv[0]);
	if (var->i != -2)
	{
		var->path = ft_strjoin(var->help->paths[var->i], "/");
		var->str = remove_quotes(var->help->argv[0]);
		free(var->help->argv[0]);
		var->help->argv[0] = NULL;
		var->help->argv[0] = ft_strjoin(var->path, var->str);
		free(var->path);
		free(var->str);
		var->str = NULL;
		free_array(var->help->paths);
		var->help->paths = NULL;
		return (var->i);
	}
	return (-2);
}

int	ft_init(t_main_var *var)
{
	var->i = 0;
	var->splits = NULL;
	var->help->argv = ft_split2(var->args->content, ' ');
	var->str = ft_strdup(var->help->argv[0], 0);
	ft_init_part1(var);
	free_array(var->help->argv);
	var->help->argv = add_to_arg(var->splits, var->help->argv);
	free_split(var->splits);
	if (is_built_ins(var->str))
	{
		free(var->str);
		var->str = NULL;
		return (-1);
	}
	else
	{
		free(var->str);
		var->str = NULL;
		if (var->help->argv[0] && !ft_strchr(var->help->argv[0], '/'))
			var->i = ft_init_part2(var);
	}
	return (var->i);
}

void	built_ins2(t_main_var *var, char *home)
{
	if (!ft_strcmp(var->help->argv[0], "unset"))
	{
		var->env = remove_elements(var->env, var->help->argv, var->i);
		var->exprt = remove_elements(var->exprt, var->help->argv, var->i);
	}
	else
	{
		home = get_home(var->env);
		cd(var->help, var->pwd, home, var->env);
	}
}

void	init_1(t_main_var *var, int *i, int *noc)
{
	signal(SIGINT, SIG_IGN);
	*i = -1;
	var->nop = num_of_pipes(var->args);
	*noc = var->nop + 1;
}
