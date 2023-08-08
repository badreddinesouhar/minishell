/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:01:07 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/04 11:15:50 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_count_words(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\t')
		{
			count++;
			while (s[i] != c && s[i] != '\t' && s[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}

char	*my_func2(int *idx, char *array, char *s, char c)
{
	char	*str;
	char	*str2;
	int		start;

	start = *idx;
	while (s[*idx] != c && s[*idx] != '\t'
		&& s[*idx] && s[*idx] != '\'' && s[*idx] != '\"')
		(*idx)++;
	str = ft_substr(s, start, (*idx) - start);
	str2 = ft_strdup(array, 0);
	free(array);
	array = ft_strjoin(str2, str);
	free(str);
	free(str2);
	return (array);
}

char	*my_func3(char *s, int *idx, char c)
{
	int		start;
	char	*array;
	char	quote;

	start = *idx;
	while (s[*idx] != c && s[*idx] != '\t' && s[*idx])
	{
		if (s[*idx] == '\"' || s[*idx] == '\'')
		{
			quote = '\'';
			if (s[*idx] == '\"')
				quote = '\"';
			(*idx)++;
			while (s[*idx] != quote)
				(*idx)++;
		}
		(*idx)++;
	}
	array = ft_substr(s, start, (*idx) - start);
	return (array);
}

char	**ft_split(char **array, char *s, char c, int idx)
{
	int		j;

	j = 0;
	array = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	while (idx < ft_strlen(s))
	{
		if (s[idx] == '\'' || s[idx] == '\"')
		{
			array[j] = ft_strdup("", 0);
			while (s[idx] && (s[idx] == '\'' || s[idx] == '\"'))
				ft_split_v2(&idx, array, j, s);
			j++;
		}
		else if (s[idx] != c && s[idx] != '\t')
			array[j++] = my_func3(s, &idx, c);
		idx++;
	}
	array[j] = 0;
	return (array);
}

char	**ft_split2(char *s, char c)
{
	int		j;
	int		idx;
	char	**array;

	idx = 0;
	j = 0;
	array = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	while (idx < ft_strlen(s))
	{
		array[j] = ft_strdup("", 0);
		if (s[idx] == '\'' || s[idx] == '\"')
		{
			while (s[idx] && (s[idx] == '\'' || s[idx] == '\"'))
				ft_split_v2(&idx, array, j, s);
			j++;
		}
		else if (s[idx] != c)
		{
			free (array[j]);
			array[j++] = my_func3(s, &idx, c);
		}
		idx++;
	}
	array[j] = 0;
	return (array);
}
