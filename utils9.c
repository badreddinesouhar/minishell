/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:15:49 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/04 10:45:59 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*my_func4(char *s, int *idx)
{
	int		start;
	char	*array;

	start = *idx;
	while (s[*idx] && s[*idx] != '\"' && s[*idx] != '\'' && s[*idx] != ' ')
		(*idx)++;
	array = ft_substr(s, start, (*idx) - start);
	return (array);
}

int	ft_count_words2(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != '\'' || s[i] != '\"')
		{
			count++;
			while ((s[i] != '\'' && s[i] != '\"') && s[i + 1])
				i++;
		}
		i++;
	}
	count /= 2;
	return (count);
}

void	ft_split3_v2(char *s, int *idx, int *j, char **array)
{
	char	*join;
	char	*join2;

	join = ft_strcpy3(s, idx, s[*idx]);
	join2 = ft_strdup(array[*j], 0);
	free(array[*j]);
	array[(*j)++] = ft_strjoin(join2, join);
	free(join);
	free(join2);
	if (s[*idx] && s[*idx] != ' ' && s[*idx] != '\'' && s[*idx] != '\"')
	{
		array[*j] = ft_strdup("", 0);
		free(array[*j]);
		join = my_func4(s, idx);
		array[*j] = ft_strdup(join, 0);
		free(join);
		(*j)++;
	}
}

char	**ft_split3(char *s)
{
	int		j;
	int		idx;
	char	**array;

	idx = 0;
	j = 0;
	array = malloc((ft_count_words2(s) + 3) * sizeof(char *));
	while (idx < ft_strlen(s))
	{
		array[j] = ft_strdup("", 0);
		if (s[idx] == '\'' || s[idx] == '\"')
			ft_split3_v2(s, &idx, &j, array);
		else
		{
			free(array[j]);
			array[j++] = my_func4(s, &idx);
		}
	}
	array[j] = 0;
	return (array);
}

char	*get_expand_v4(char *join, char *join2)
{
	char	*join3;

	join3 = ft_strdup(join2, 0);
	free(join2);
	join2 = ft_strjoin(join3, join);
	free(join3);
	free(join);
	return (join2);
}
