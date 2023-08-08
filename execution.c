/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:14:31 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/04 12:30:25 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*skip_quotes3(char *join, char *new)
{
	char	*join2;

	join2 = ft_strdup(join, 0);
	free(join);
	join = ft_strjoin(join2, new);
	free(join2);
	free(new);
	return (join);
}

int	is_built_ins(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "unset") || !ft_strcmp(s,
			"env") || !ft_strcmp(s, "$?") || !ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

void	add_to_parser(t_split **split, char **data)
{
	t_split	*new;
	t_split	*last;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen_array(data);
	while (++i < len)
	{
		new = malloc(sizeof(t_split));
		new->data = ft_strdup(data[i], 0);
		new->next = NULL;
		if (!*split)
			*split = new;
		else
		{
			last = *split;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
	free_array(data);
}

char	**add_to_arg(t_split *split, char **array)
{
	int		i;
	int		count;
	t_split	*tmp;

	count = 0;
	tmp = split;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	i = 0;
	array = malloc(sizeof(char *) * (count + 1));
	while (split)
	{
		array[i] = ft_strdup(split->data, 0);
		split = split->next;
		i++;
	}
	array[i] = 0;
	return (array);
}

void	execute_one_cmd(t_main_var *var)
{
	int	i;

	var->help = malloc(sizeof(t_helper));
	i = ft_init(var);
	if (i == -1)
		built_ins(var);
	else
	{
		execve(var->help->argv[0], var->help->argv, var->env);
		expand2(var->help->argv[0]);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	exit(g_exit_status);
}
