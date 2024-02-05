/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:38 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/05 18:47:40 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_ms *ms, int file_i, int file_o, int p)
{
	(void)	p;
	(void)	file_i;
	(void)	file_o;
	int	status;

	ms->child_pid = fork();
	if (ms->child_pid < 0)
		perror(ms->cmds->cmd);
	else if (ms->child_pid == 0)
	{
		if(execve(ms->cmds->cmd, ft_split(ms->cmds->cmd,' '), ms->envp) == -1)
			perror(ms->cmds->cmd);
		ft_free(ms, EXIT_FAILURE);
	}
	else
	{
		waitpid(ms->child_pid, &status, WUNTRACED);
		
	}
}


void	ft_executor(t_ms *ms)
{
	int	fd_pipe[2];
	int	fd_in;
	int	index_pipe;

	fd_in = STDIN_FILENO;
	index_pipe = 0;
	while (index_pipe <= ms->num_pipes)
	{
		if (pipe(fd_pipe) == -1)
			perror("pipe");
		if (index_pipe == ms->num_pipes)
		{
			ft_exec_cmd(ms, fd_in, STDOUT_FILENO, index_pipe);
		}
		else
		{
			ft_exec_cmd(ms, fd_in, fd_pipe[1], index_pipe);
		}
		close(fd_pipe[1]);
		index_pipe++;
	}
}


/*
int	ft_executor(t_ms *ms)
{
	if (!ft_strncmp(ms->cmd->name, "echo", 4))
	{
		return (ft_echo(ms));
	}
	else if (!ft_strncmp(ms->cmd->name, "exit", 4))
	{
		ft_printf("DEBUG: Saliendo, comando exit\n");
		return (ft_exit(ms));
	}
	else
	{
		ft_printf("minishell: %s: command not found\n", ms->cmd->name);
		return (TRUE);
	}
}

*/