/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmengouc <bmengouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:59:50 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/01 20:59:53 by bmengouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**split_func(char **array, int i, char **new, char **env)
{
	int	j;

	j = -1;
	new = malloc(sizeof(char *) * (ft_strlen_array(env) + 2));
	while (env[++j])
		new[j] = ft_strdup(env[j], 0);
	new[j++] = ft_strdup(array[i], 0);
	new[j] = 0;
	free_array(env);
	env = malloc(sizeof(char *) * (ft_strlen_array(new) + 1));
	j = -1;
	while (new[++j])
		env[j] = ft_strdup(new[j], 0);
	env[j] = 0;
	free_array(new);
	return (env);
}

char	**add_elements(char **env, char **array, int i)
{
	char	**new;
	int		j;
	int		count;

	new = NULL;
	i = -1;
	while (++i < ft_strlen_array(array))
	{
		assign_elements(&count, array[i], &j, env);
		if (j > -1 && ft_strchr(array[i], '='))
		{
			while (count < j)
				count++;
			free(env[count]);
			env[count] = ft_strdup(array[i], 0);
		}
		else
		{
			if (check_export(array[i]))
				env = split_func(array, i, new, env);
		}
	}
	return (env);
}

char	**add_elements2(char **env, char **array, int i)
{
	char	**new;
	int		j;
	int		count;

	new = NULL;
	i = 0;
	while (++i < ft_strlen_array(array))
	{
		assign_elements(&count, array[i], &j, env);
		if (j > -1)
		{
			if (ft_strchr(array[i], '='))
			{
				while (count < j)
					count++;
				free(env[count]);
				env[count] = ft_strdup(array[i], 0);
			}
		}
		else
			env = split_func(array, i, new, env);
	}
	return (env);
}

char	**split_func2(char **new, char **env, int j)
{
	int	pos;
	int	k;

	k = 0;
	pos = j;
	j = -1;
	new = malloc(sizeof(char *) * (ft_strlen_array(env)));
	while (env[++j])
	{
		if (j != pos)
			new[k++] = ft_strdup(env[j], 0);
	}
	new[k] = 0;
	free_array(env);
	env = malloc(sizeof(char *) * (ft_strlen_array(new) + 1));
	j = -1;
	while (new[++j])
		env[j] = ft_strdup(new[j], 0);
	free_array(new);
	env[j] = 0;
	return (env);
}

char	**remove_elements(char **env, char **array, int i)
{
	int		j;
	char	**new;

	i = 0;
	new = NULL;
	while (++i < ft_strlen_array(array))
	{
		j = is_env_exist(array[i], env);
		if (j > -1)
			env = split_func2(new, env, j);
	}
	return (env);
}
