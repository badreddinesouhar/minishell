/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:15:30 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/04 09:53:08 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*assign1(t_vars *head, t_parser *new_node)
{
	if (!ft_strcmp(head->data, "|"))
		return (head);
	else
	{
		new_node->content = remove_quotes(head->next->data);
		if (!ft_strcmp(head->data, ">"))
			new_node->type = RI;
		else if (!ft_strcmp(head->data, "<"))
			new_node->type = RO;
		else if (!ft_strcmp(head->data, ">>"))
			new_node->type = RA;
		else if (!ft_strcmp(head->data, "<<"))
			new_node->type = RH;
		head = head->next;
	}
	return (head);
}

char	*skip_quotes(char *input)
{
	int		i;
	char	quote;
	char	*join;
	char	*join2;

	join = ft_strdup("", 0);
	i = 0;
	quote = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '\"')
			join = skip_quotes2(input, quote, &i, join);
		else
		{
			join2 = ft_strdup(join, 0);
			free(join);
			join = ft_strjoin2(join2, input[i++]);
			free(join2);
		}
	}
	return (join);
}

void	assing2_v2(t_vars *tmp, t_parser *new_node)
{
	char	*str;
	t_vars	*tmp2;

	str = ft_strjoin(new_node->content, tmp->data);
	free(new_node->content);
	free(tmp->data);
	tmp->data = NULL;
	new_node->content = ft_strdup(str, 0);
	free(str);
	tmp2 = tmp->next;
	while (tmp2 && check2(tmp2))
		tmp2 = tmp2->next->next;
	if (tmp2 && tmp2->data[0] != '|')
	{
		str = ft_strdup(new_node->content, 0);
		free(new_node->content);
		new_node->content = ft_strjoin(str, " ");
		free(str);
	}
}

t_vars	*assign2(t_vars *tmp, t_parser *new_node)
{
	new_node->content = ft_strdup("", 0);
	new_node->type = CMD;
	while (tmp)
	{
		while (tmp && check2(tmp))
			tmp = tmp->next->next;
		if (tmp)
		{
			if (tmp->data[0] != '|')
				assing2_v2(tmp, new_node);
			else
				return (tmp);
		}
		else
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	check_and_pass(t_vars *head, t_parser **parser_list)
{
	t_vars	*tmp;
	t_vars	*tmp2;

	tmp2 = head;
	tmp = head;
	while (tmp)
	{
		tmp = add_cmd(tmp, parser_list);
		tmp = head;
		tmp = add_red_her(tmp, parser_list);
		tmp = add_pipe(tmp, &head, parser_list);
	}
	free_t_vars(tmp2);
}
