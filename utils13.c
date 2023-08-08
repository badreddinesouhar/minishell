/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 05:41:56 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/08 05:41:57 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*get_expand2(char *argv, char **env, char *join4)
{
	int		j;
	char	*join2;
	int		i;
	char	**array;

	array = ft_split3(argv);
	i = -1;
	join4 = ft_strdup("", 0);
	while (array[++i])
	{
		j = 0;
		join2 = ft_strdup("", 0);
		join2 = get_expand_v2(array[i], join2, env);
		join4 = get_expand_v3(join4, join2);
	}
	free_array(array);
	return (join4);
}

char	*herdoc3(char *join, t_main_var *var)
{
	char	*input;
	char	*join2;
	int		i;

	i = -1;
	while (var->split[++i])
	{
		input = get_expand2(var->split[i], var->env, var->join4);
		join2 = ft_strdup(join, 0);
		free(join);
		join = ft_strjoin(join2, input);
		free(input);
		free(join2);
		join2 = ft_strdup(join, 0);
		if (i < ft_strlen_array(var->split) - 1)
		{
			free(join);
			join = ft_strjoin(join2, " ");
		}
		free(join2);
	}
	free_array(var->split);
	return (join);
}

void	assign_rosting(int *i, int *j, int *flg)
{
	*i = 0;
	*j = 0;
	*flg = 0;
}

char	*rostring(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		flg;

	new = malloc(ft_strlen(str) + 1);
	assign_rosting(&i, &j, &flg);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			flg = 1;
		if (!(str[i] == ' ' || str[i] == '\t'))
		{
			if (flg)
				new[j++] = ' ';
			flg = 0;
			new[j++] = str[i];
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*expand3_v2(char *new, int i, char **env)
{
	int		len;
	char	*new3;

	len = ft_strlen(new) + 1;
	free(new);
	new = ft_strdup(env[i], len);
	new3 = rostring(new);
	free(new);
	return (new3);
}
