/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:51:22 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/06 15:51:23 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	quote_is_ended(char *input, int start, char quote)
{
	while (input[start])
	{
		if (input[start] == quote && input[start - 1] != '\\')
			return (1);
		start++;
	}
	return (0);
}

char	*remove_quotes(char *input)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i++;
		if (!input[i])
		{
			str[j] = 0;
			return (str);
		}
		str[j] = input[i];
		j++;
		i++;
	}
	str[j] = 0;
	return (str);
}

int	check_quotes(char *input, int i)
{
	char	quote;
	int		check;

	while (i < ft_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			check = 0;
			quote = '\'';
			if (input[i] == '\"')
				quote = '\"';
			while (++i < ft_strlen(input))
			{
				if (input[i] == quote && input[i - 1] != '\\')
				{
					check = 1;
					break ;
				}
			}
			if (!check)
				return (0);
		}
		i++;
	}
	return (1);
}
