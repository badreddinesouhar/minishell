/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:13:56 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 22:13:59 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_strlen(char *str)
{
	int	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s_join;
	int		idx1;
	int		idx2;

	if (!s1 || !s2)
		return (NULL);
	s_join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s_join)
		return (NULL);
	idx1 = 0;
	idx2 = 0;
	while (s1[idx1])
		s_join[idx2++] = s1[idx1++];
	idx1 = 0;
	while (s2[idx1])
		s_join[idx2++] = s2[idx1++];
	s_join[idx2] = 0;
	return (s_join);
}

char	*ft_strdup(char *str, int idx)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[idx])
		dup[i++] = str[idx++];
	dup[i] = 0;
	return (dup);
}

char	*ft_strdup2(char *str, int *idx)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*idx] && str[*idx] != '\'' && str[*idx] != '\"')
		dup[i++] = str[(*idx)++];
	dup[i] = 0;
	return (dup);
}

char	*ft_strcpy(char *str, int *start, char quote)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*start] && str[*start] != quote)
		dup[i++] = str[(*start)++];
	dup[i] = 0;
	return (dup);
}
