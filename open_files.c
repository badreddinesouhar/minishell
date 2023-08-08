/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:27:21 by bmengouc          #+#    #+#             */
/*   Updated: 2023/07/31 21:27:35 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*herdoc(t_parser *head, t_main_var *var)
{
	char	*input;
	char	*her;
	char	*join;

	her = ft_strdup("", 0);
	input = readline("> ");
	while (input)
	{
		join = ft_strdup("", 0);
		if (!ft_strcmp(input, head->content))
		{
			free(join);
			free(input);
			return (her);
		}
		var->split = ft_split2(input, ' ');
		free(input);
		join = herdoc3(join, var);
		her = herdoc2(her, join);
		input = readline("> ");
	}
	free(input);
	return (her);
}

void	open_herdoc(t_parser *tmp, t_main_var *var)
{
	char	*her;
	int		fd;

	her = NULL;
	while (tmp)
	{
		if (tmp->type == 5)
		{
			her = herdoc(tmp, var);
			fd = open("/tmp/aad", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write(fd, her, ft_strlen(her));
			close(fd);
			free(her);
		}
		else if (tmp->type == 1)
			break ;
		tmp = tmp->next;
	}
}

int	red_out(char *s)
{
	if ((access(s, F_OK) == -1))
	{
		print(s, 0);
		return (0);
	}
	else if ((access(s, W_OK) == -1) || (access(s, R_OK) == -1))
	{
		print(s, 1);
		return (0);
	}
	return (1);
}

int	open_file(t_parser *head)
{
	int	fd;

	fd = 0;
	if (head->type == 2)
		fd = open(head->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (head->type == 3)
	{
		if (!red_out(head->content))
			return (0);
		fd = open(head->content, O_RDONLY, 0644);
	}
	else if (head->type == 4)
		fd = open(head->content, O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("");
		return (0);
	}
	close(fd);
	return (1);
}

int	open_files(t_parser *head)
{
	while (head)
	{
		if (head->type > 1 && head->type < 5)
		{
			if (!open_file(head))
				return (0);
		}
		else if (head->type == 1)
			break ;
		head = head->next;
	}
	return (1);
}
