/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:54:55 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/06 22:54:56 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_split_v2(int *idx, char **array, int j, char *s)
{
	char	*join;
	char	*join2;

	join = ft_strcpy3(s, idx, s[*idx]);
	join2 = ft_strdup(array[j], 0);
	free(array[j]);
	array[j] = ft_strjoin(join2, join);
	free(join);
	free(join2);
	if (s[*idx] && s[*idx] != ' '
		&& s[*idx] != '\t' && s[*idx] != '\'' && s[*idx] != '\"')
		array[j] = my_func2(idx, array[j], s, ' ');
}

void	free_helper2(t_helper *help)
{
	int	i;

	if (help->argv)
	{
		i = -1;
		while (help->argv[++i])
		{
			free(help->argv[i]);
			help->argv[i] = NULL;
		}
		free(help->argv);
		help->argv = NULL;
	}
	free(help);
	help = NULL;
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		j;

	if (start >= ft_strlen(s) || !s)
		return (ft_strdup("", 0));
	if (start + len <= ft_strlen(s))
		str = malloc(len + 1);
	else
		str = malloc(ft_strlen(s) - start + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i < start + len && s[i])
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}
