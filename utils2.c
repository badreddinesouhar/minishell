/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:16:10 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/03 23:59:54 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_file_exist(char **paths, char *cmd)
{
	int		i;
	char	*join1;
	char	*join2;

	i = 0;
	while (paths[i])
	{
		join1 = ft_strjoin(paths[i], "/");
		join2 = ft_strjoin(join1, cmd);
		free(join1);
		if ((access(join2, F_OK) == 0))
		{
			free(join2);
			return (i);
		}
		free(join2);
		i++;
	}
	return (-2);
}

char	**get_env_paths(char **env)
{
	char	*new;
	int		len;
	char	*new2;
	char	**re;
	int		i;

	i = -1;
	while (env[++i])
	{
		new = ft_substr(env[i], 0, ft_strlen("PATH"));
		len = ft_strlen(new);
		if (new && !ft_strcmp("PATH", new) && env[i][len] == '=')
		{
			new2 = ft_strdup(env[i], len + 1);
			free(new);
			re = ft_split2(new2, ':');
			free(new2);
			return (re);
		}
		free(new);
	}
	return (NULL);
}

int	ft_isalnum(char c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0'
			&& c <= '9'));
}

char	*ft_strcpy2(char *str, int *start)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*start] && str[*start] != ' ' && str[*start] != '\t'
		&& str[*start] != '\'' && str[*start] != '\"')
		dup[i++] = str[(*start)++];
	dup[i] = 0;
	return (dup);
}

char	*ft_strcpy3(char *str, int *start, char quote)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	dup[i++] = str[(*start)++];
	while (str[*start] && str[*start] != quote)
		dup[i++] = str[(*start)++];
	dup[i++] = str[(*start)++];
	dup[i] = 0;
	return (dup);
}
