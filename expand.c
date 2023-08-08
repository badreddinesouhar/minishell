/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:03:23 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/04 00:13:03 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	print_error(char *str, char *new)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(new);
}

int	check_export2(char *new, char *str, int i)
{
	if (!((new[i] >= 'a' && new[i] <= 'z') || (new[i] >= 'A' && new[i] <= 'Z'))
		&& new[i] != '_')
	{
		print_error(str, new);
		return (0);
	}
	return (1);
}

int	check_export(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (0);
	new = ft_substr(str, 0, i);
	i = 0;
	if (!check_export2(new, str, i))
		return (0);
	i = 1;
	while (new[i])
	{
		if (!ft_isalnum(new[i]) && new[i] != '_')
		{
			print_error(str, new);
			return (0);
		}
		i++;
	}
	free(new);
	return (1);
}

void	expand(char *str, int *start, char **env)
{
	char	*new;
	char	*new2;
	int		end;
	int		i;

	i = -1;
	end = *start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	new = ft_substr(str, *start, end - *start);
	while (env[++i])
	{
		new2 = ft_substr(env[i], 0, ft_strlen(new));
		if (!ft_strcmp(new, new2))
		{
			free(new);
			new = ft_strdup(env[i], ft_strlen(new) + 1);
			write(1, new, ft_strlen(new));
			free(new2);
		}
	}
	free(new);
	*start = end;
}

void	assign_elements(int *count, char *arr, int *j, char **env)
{
	char	*str;

	*count = 0;
	str = cut_str(arr);
	*j = is_env_exist(str, env);
	free(str);
}
