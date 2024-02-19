/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:38 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/09 13:07:47 by gpaez-ga         ###   ########.fr       */
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


void	ft_execute_command(t_ms *ms)
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

void	ft_create_command(t_ms *ms)
{
	t_token	*node;
	char	*cmd;
	char	*cmd1;

	if (DEBUG)
	{
		printf("DEBUG. Entrando a crear el comando.\nLista de tokens:\n");
		ft_print_tok_list(ms);
	}
	cmd = NULL;
	node = ms->tokens;
	while (node && node->type <= DBLQUOTE)
	{
		if (DEBUG)
			printf("DEBUG. Copio el token: #%s#\n", node->token);
		cmd1 = ft_strdup(node->token);
		if (DEBUG)
			printf("DEBUG. Uno el token.\n");
		cmd1 = ft_strjoin(cmd1, " ");
		cmd = ft_strjoin(cmd, cmd1);
		free(cmd1);
		if (DEBUG)
			printf("DEBUG. Token unido: #%s#\n", cmd);
		node = node->next;
	}
	if (DEBUG)
	{
		printf("DEBUG. Fuera del bucle.\n");
		printf("DEBUG. Comando antes del split: #%s#\n", cmd);
	}
	ms->command = ft_split(cmd, ' ');
	free(cmd);
}

void	ft_executor(t_ms *ms)
{
	if (DEBUG)
		printf("DEBUG. Entrando al ejecutor.\n");
	ft_create_command(ms);
	if (ft_strncmp("echo", ms->command[0], 4) == 0)
		ft_echo(ms);
	else if (ft_strncmp("exit", ms->command[0], 4) == 0)
		ft_exit(ms);
	if (DEBUG)
		printf("DEBUG. Saliendo del ejecutor.\n");
}