/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:14:00 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/06 21:14:02 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*get_expand_v2(char *str, char *join2, char **env)
{
	int		j;
	char	*join;

	j = 0;
	while (str[j])
	{
		if (str[j] && str[j] == '$' && str[j + 1])
		{
			join = part_one(str, &j, env);
			if (join)
				join2 = get_expand_v4(join, join2);
		}
		else
		{
			join = ft_strdup(join2, 0);
			free(join2);
			if (join)
				join2 = ft_strjoin2(join, str[j]);
			free(join);
			j++;
		}
	}
	return (join2);
}

char	*get_expand_v3(char *join4, char *join2)
{
	char	*join;

	join = ft_strdup(join4, 0);
	free(join4);
	join4 = ft_strjoin(join, join2);
	free(join2);
	free(join);
	return (join4);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	free_helper(t_helper *help)
{
	int	i;

	i = -1;
	if (help)
	{
		if (help->paths)
		{
			while (help->paths[++i])
			{
				free(help->paths[i]);
				help->paths[i] = NULL;
			}
			free(help->paths);
			help->paths = NULL;
		}
		free_helper2(help);
	}
}

char	*ft_strcpy4(char *str, int *start, char quote)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*start] && str[*start] != quote)
		dup[i++] = str[(*start)++];
	(*start)++;
	dup[i] = 0;
	return (dup);
}
