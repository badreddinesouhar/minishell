/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:59:01 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/03 22:06:10 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	assign(int *i, int *j, char ***array, char *s)
{
	*array = malloc((ft_strlen(s) + 1) * sizeof(char *));
	*i = 0;
	*j = 0;
}

char	**fill_env(char **env)
{
	char	**new;
	int		i;

	i = -1;
	new = malloc(sizeof(char *) * (ft_strlen_array(env) + 1));
	while (env[++i])
		new[i] = ft_strdup(env[i], 0);
	new[i] = 0;
	return (new);
}

void	print_exprt(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=' || !env[i][j + 1])
			{
				print_export2(env[i], j);
				break ;
			}
		}
	}
}
