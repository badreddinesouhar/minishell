/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:09:51 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/06 20:09:52 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_list(t_parser **parser_list, t_parser *new_node)
{
	t_parser	*last;

	if (!*parser_list)
		*parser_list = new_node;
	else
	{
		last = *parser_list;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

t_vars	*add_pipe(t_vars *tmp, t_vars **head, t_parser **parser_list)
{
	t_parser	*new_node;

	while (tmp)
	{
		if (tmp->data[0] == '|')
		{
			new_node = malloc(sizeof(t_parser));
			new_node->next = NULL;
			new_node->content = NULL;
			new_node->type = PIPE;
			add_list(parser_list, new_node);
			(*head) = tmp->next;
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_vars	*add_red_her(t_vars *tmp, t_parser **parser_list)
{
	t_parser	*new_node;

	while (tmp)
	{
		if (check2(tmp))
		{
			new_node = malloc(sizeof(t_parser));
			new_node->next = NULL;
			tmp = assign1(tmp, new_node);
			add_list(parser_list, new_node);
			if (tmp && tmp->data[0] == '|')
				return (tmp);
		}
		else if (tmp && tmp->data && tmp->data[0] == '|')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_vars	*add_cmd(t_vars *tmp, t_parser **parser_list)
{
	t_parser	*new_node;

	while (tmp)
	{
		if (!check2(tmp))
		{
			new_node = malloc(sizeof(t_parser));
			new_node->next = NULL;
			tmp = assign2(tmp, new_node);
			add_list(parser_list, new_node);
			if (tmp && tmp->data[0] == '|')
				return (tmp);
		}
		else
			tmp = tmp->next->next;
	}
	return (NULL);
}

char	*skip_quotes2(char *input, char quote, int *i, char *join)
{
	char	*new;

	quote = '\'';
	if (input[*i] == '\"')
		quote = '\"';
	while (input[*i] == quote)
		(*i)++;
	if (input[*i] == '\0')
	{
		if (join[0] == '\0')
		{
			free(join);
			join = ft_strdup(" ", 0);
			return (join);
		}
	}
	new = ft_strcpy4(input, i, quote);
	if (new)
		return (skip_quotes3(join, new));
	free(new);
	return (join);
}
