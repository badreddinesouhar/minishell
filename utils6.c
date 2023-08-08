/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:25:56 by bmengouc          #+#    #+#             */
/*   Updated: 2023/08/04 11:06:54 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2", fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 0 && n <= 9)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

char	*get_home(char **env)
{
	char	*new;
	int		len;
	int		i;

	i = -1;
	while (env[++i])
	{
		new = ft_substr(env[i], 0, ft_strlen("HOME"));
		len = ft_strlen(new);
		if (new && !ft_strcmp("HOME", new) && env[i][len] == '=')
		{
			free(new);
			new = ft_strdup(env[i], len + 1);
			return (new);
		}
		free(new);
	}
	return (NULL);
}

void	print(char *s, int bit)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (!bit)
	{
		ft_putstr_fd(":  No such file or directory\n", 2);
		g_exit_status = 1;
	}
	else
	{
		ft_putstr_fd(":  Permission denied\n", 2);
		g_exit_status = 1;
	}
}
