/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouhar <bsouhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:14:34 by bsouhar           #+#    #+#             */
/*   Updated: 2023/08/03 23:17:34 by bsouhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	num_of_pipes(t_parser *arg)
{
	int	count;

	count = 0;
	while (arg)
	{
		if (arg->type == 1)
			count++;
		arg = arg->next;
	}
	return (count);
}

void	modify_files(t_parser *command)
{
	int	fd;

	fd = 0;
	if (command->type == 2)
	{
		fd = open(command->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (command->type == 3)
	{
		fd = open(command->content, O_RDONLY, 0644);
		dup2(fd, STDIN_FILENO);
	}
	else if (command->type == 4)
	{
		fd = open(command->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (command->type == 5)
	{
		fd = open("/tmp/aad", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		unlink("/tmp/aad");
	}
	close(fd);
}

void	create_child_proc(t_main_var *var, int i)
{
	if (i > 0)
	{
		dup2(var->pipes[i - 1][0], STDIN_FILENO);
		close(var->pipes[i - 1][0]);
	}
	if (i < var->num_command - 1)
	{
		dup2(var->pipes[i][1], STDOUT_FILENO);
		close(var->pipes[i][1]);
	}
	close_pipes(var->pipes, var->num_command);
	if (var->args->type == 0)
		create_child_proc2(var);
}

void	execute_part_1(t_main_var *var, int i)
{
	signal(SIGINT, SIG_IGN);
	open_herdoc(var->args, var);
	var->pids[i] = fork();
	if (var->pids[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		create_child_proc(var, i);
		g_exit_status = 0;
		exit(g_exit_status);
	}
	else if (var->pids[i] < 0)
	{
		perror("fork");
		exit(1);
	}
}

void	execute_multiple_cmd(t_main_var *var)
{
	int			i;
	t_parser	*tmp;

	tmp = var->args;
	init_1(var, &i, &var->num_command);
	var->pids = malloc(var->num_command * sizeof(pid_t));
	create_pipes(var->pipes, var->num_command);
	while (++i < var->num_command)
	{
		execute_part_1(var, i);
		var->args = var->args->next;
		while (var->args && var->args->type > 0)
			var->args = var->args->next;
	}
	close_pipes(var->pipes, var->num_command);
	i = -1;
	while (++i < var->num_command)
		waitpid(var->pids[i], &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	var->args = tmp;
	handle_signals();
	free(var->pids);
}
