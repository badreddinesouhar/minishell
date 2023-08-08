/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:53:05 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 20:53:08 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*cut_str(char *str)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, start, i - start));
}

void	print_array(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
}

int	is_env_exist(char *str, char **env)
{
	char	*s;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	while (env[++i])
	{
		s = ft_substr(env[i], 0, len);
		if (!ft_strcmp(s, str) && (env[i][len] == '=' || !env[i][len]))
		{
			free(s);
			return (i);
		}
		free(s);
	}
	return (-1);
}

int	pwd(t_helper *help, char *path, int fd)
{
	if (ft_strlen_array(help->argv) > 1)
		return (1);
	if (getcwd(path, 1024) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
	return (0);
}

void	built_ins(t_main_var *var)
{
	var->home = NULL;
	if (!ft_strcmp(var->help->argv[0], "env"))
		print_array(var->env);
	else if (!ft_strcmp(var->help->argv[0], "echo"))
		echo(var->help, var->env);
	else if (!ft_strcmp(var->help->argv[0], "pwd"))
		pwd(var->help, var->pwd, 1);
	else if (!ft_strcmp(var->help->argv[0], "export"))
	{
		if (ft_strlen_array(var->help->argv) == 1)
			print_exprt(var->exprt);
		else
		{
			var->env = add_elements(var->env, var->help->argv, var->i);
			var->exprt = add_elements2(var->exprt, var->help->argv, var->i);
		}
	}
	else if (!ft_strcmp(var->help->argv[0], "unset")
		|| !ft_strcmp(var->help->argv[0], "cd"))
		built_ins2(var, var->home);
	else if (!ft_strcmp(var->help->argv[0], "exit"))
		ft_exit(var->help->argv);
	else
		print_exit_status();
}
