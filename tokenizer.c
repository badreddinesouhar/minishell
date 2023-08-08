/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:05:32 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 22:05:34 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_is_match(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	until_not_match(char *str, int start, char *set)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*ft_take(char *str, int *start, char c)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*start] && str[*start] == c)
		dup[i++] = str[(*start)++];
	dup[i] = 0;
	return (dup);
}

int	ft_token_part1(char **array, char *s, int j)
{
	if (s[0] == '\'' || s[0] == '\"')
	{
		array[j++] = ft_substr(s, 0, ft_strlen(s));
		array[j] = 0;
		return (1);
	}
	return (0);
}

char	**ft_token(char *s, char *set)
{
	int		i;
	int		start;
	int		j;
	char	**array;

	assign(&i, &j, &array, s);
	if (ft_token_part1(array, s, j))
		return (array);
	while (i < ft_strlen(s))
	{
		if (check_is_match(s[i], set))
		{
			array[j++] = ft_take(s, &i, s[i]);
			continue ;
		}
		else
		{
			start = i;
			array[j++] = ft_substr(s, start, until_not_match(s, start, set)
					- start);
			i = until_not_match(s, i, set);
		}
	}
	array[j] = 0;
	return (array);
}
