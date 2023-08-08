/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:30:28 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/07 15:30:29 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	replace_line(char *str, char *oldpwd)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			i++;
			j = -1;
			while (oldpwd[++j])
				str[i++] = oldpwd[j];
			str[i] = 0;
			return ;
		}
	}
}

char	*get_oldpwd(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i])
	{
		if (str[i] == '=')
		{
			i++;
			while (str[i])
			{
				new[j] = str[i];
				i++;
				j++;
			}
			new[j] = 0;
			return (new);
		}
	}
	return (NULL);
}

void	update_pwd(char **env, char *pwd, char *oldpwd)
{
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		j = is_env_exist("PWD", env);
		if (j > -1)
		{
			oldpwd = get_oldpwd(env[j]);
			replace_line(env[j], pwd);
			break ;
		}
	}
	i = -1;
	while (env[++i])
	{
		j = is_env_exist("OLDPWD", env);
		if (j > -1)
		{
			replace_line(env[j], oldpwd);
			free(oldpwd);
			break ;
		}
	}
}
