/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:18:55 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 22:18:57 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_strlen_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	num_of_commands(t_parser *arg)
{
	int	count;

	count = 0;
	while (arg)
	{
		if (arg->content)
			count++;
		arg = arg->next;
	}
	return (count);
}

void	create_pipes(int pipes[][2], int num_commands)
{
	int	i;

	i = -1;
	while (++i < num_commands - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_pipes(int pipes[][2], int num_commands)
{
	int	i;

	i = -1;
	while (++i < num_commands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

char	*ft_strjoin2(char *str, char c)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	new[i + 1] = 0;
	return (new);
}
