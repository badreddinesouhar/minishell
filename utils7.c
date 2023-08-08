/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:39:51 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/04 09:41:10 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand3(char *str, int *start, char **env)
{
	char	*new;
	int		end;
	int		i;
	char	*new3;

	end = *start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_')
		&& str[end] != '$')
		end++;
	new = ft_substr(str, *start, end - *start);
	i = is_env_exist(new, env);
	if (i != -1)
		new3 = expand3_v2(new, i, env);
	else
	{
		free(new);
		*start = end;
		return (NULL);
	}
	*start = end;
	return (new3);
}

char	*part_two(int __unused exit_status, char *join, char *join2)
{
	char	*s;
	char	*str;

	str = ft_itoa(g_exit_status);
	join = ft_strdup(join2, 0);
	free(join2);
	join2 = ft_strjoin(join, str);
	s = ft_strdup(join2, 0);
	free(join2);
	free(join);
	free(str);
	return (s);
}

char	*part_one(char *string, int *j, char **env)
{
	char	*join;
	char	*join2;

	join2 = ft_strdup("", 0);
	join = NULL;
	while (string[*j] && string[*j] == '$' && string[(*j) + 1])
	{
		(*j)++;
		if (string[*j] == '?')
		{
			join2 = part_two(g_exit_status, join, join2);
			(*j)++;
		}
		else
			join2 = part_one_v2(string, j, env, join2);
	}
	return (join2);
}

void	expand2(char *argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
}

char	*get_expand(char *argv, char **env, char *join4)
{
	int		j;
	char	*join2;
	int		i;
	char	**array;

	array = ft_split3(argv);
	i = -1;
	join4 = ft_strdup("", 0);
	while (array[++i])
	{
		j = 0;
		join2 = ft_strdup("", 0);
		if (array[i][0] != '\'')
			join2 = get_expand_v2(array[i], join2, env);
		else
		{
			free(join2);
			join2 = ft_strdup(array[i], 0);
		}
		join4 = get_expand_v3(join4, join2);
	}
	free_array(array);
	free(argv);
	return (join4);
}
