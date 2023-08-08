/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:08:18 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 21:08:20 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	get_type(char *data)
{
	if (!ft_strcmp(">", data))
		return (4);
	else if (!ft_strcmp(">>", data))
		return (5);
	else if (!ft_strcmp("|", data))
		return (3);
	else if (!ft_strcmp("<", data))
		return (6);
	else if (!ft_strcmp("<<", data))
		return (7);
	return (0);
}

int	get_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_add_list(t_vars **lst, char *data)
{
	int		i;
	char	**split;
	t_vars	*new;
	t_vars	*last;

	i = 0;
	split = NULL;
	split = ft_token(data, "|><>");
	i = 0;
	while (split[i])
	{
		new = malloc(sizeof(t_vars));
		new->data = ft_strdup(split[i++], 0);
		new->next = NULL;
		if (!*lst)
			*lst = new;
		else
		{
			last = *lst;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
	free_array(split);
}

char	*part_one_v2(char *string, int *j, char **env, char *join2)
{
	char	*str;
	char	*join;

	str = expand3(string, j, env);
	if (str)
	{
		join = ft_strdup(join2, 0);
		free(join2);
		join2 = ft_strjoin(join, str);
		free(join);
	}
	free(str);
	return (join2);
}

char	*herdoc2(char *her, char *input)
{
	char	*s;

	s = ft_strdup(her, 0);
	free(her);
	her = ft_strjoin(s, input);
	free(s);
	s = ft_strdup(her, 0);
	free(her);
	her = ft_strjoin(s, "\n");
	free(s);
	free(input);
	return (her);
}
