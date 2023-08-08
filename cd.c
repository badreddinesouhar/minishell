/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:56:00 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/04 00:24:19 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	my_func(char *str, char *pwd, char **env)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (chdir(str) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
		return (1);
	}
	if (getcwd(pwd, 1024 + 1) == NULL)
	{
		perror("getcwd() error");
		g_exit_status = 1;
		return (1);
	}
	update_pwd(env, pwd, oldpwd);
	g_exit_status = 0;
	return (0);
}

int	cd(t_helper *help, char *pwd, char *home, char **env)
{
	char	*str;

	str = NULL;
	if (ft_strlen_array(help->argv) == 1)
	{
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_exit_status = 1;
			return (1);
		}
		str = ft_strdup(home, 0);
	}
	else
		str = ft_strdup(help->argv[1], 0);
	free(home);
	if (my_func(str, pwd, env))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[i] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return (s1[i] - s2[j]);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	print_export2(char *s, int j)
{
	char	*s1;
	char	*s2;

	s1 = ft_substr(s, 0, j + 1);
	s2 = ft_strdup(s, j + 1);
	ft_putstr("declare -x ");
	write(1, s1, ft_strlen(s1));
	if (s[j] == '=')
		ft_putstr("\"");
	write(1, s2, ft_strlen(s2));
	if (s[j] == '=')
		ft_putstr("\"");
	ft_putstr("\n");
	free(s1);
	free(s2);
}
