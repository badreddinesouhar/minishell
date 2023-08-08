/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:48:37 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/06 15:48:39 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_split(t_split *vars)
{
	t_split	*current;
	t_split	*next;

	current = vars;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		current->data = NULL;
		free(current);
		current = next;
	}
	vars = NULL;
}

void	ft_free_split(t_split *split)
{
	t_split	*lst;
	t_split	*prev;

	lst = split;
	prev = lst;
	while (lst)
	{
		free(prev->data);
		prev->data = NULL;
		free(prev);
		lst = lst->next;
		prev = lst;
	}
}

void	free_t_vars(t_vars *vars)
{
	t_vars	*current;
	t_vars	*next;

	current = vars;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		current->data = NULL;
		free(current);
		current = next;
	}
	vars = NULL;
}

void	free_t_parser(t_parser *parser)
{
	t_parser	*current;
	t_parser	*next;

	current = parser;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		current->content = NULL;
		free(current);
		current = next;
	}
	parser = NULL;
}
