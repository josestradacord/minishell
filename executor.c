/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:38 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/19 20:18:45 by joestrad         ###   ########.fr       */
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

/**
 * @brief 		Counts the number of tokens that must have the command line
 * 				it stops when it finds a PIPE
 * 
 * @param tok 
 * @return int 
 */
int	ft_count_tokens(t_token *tok)
{
	int		nbr;
	t_token	*aux;

	nbr = 0;
	aux = tok;
	while (aux && aux->type != PIPE)
	{
		if (aux->type <= DBLQUOTE && aux->type >= NOQUOTE)
			nbr++;
		aux = aux->next;
	}
	return (nbr);
}

char	**ft_create_command(t_token *toks)
{
	char	**res;
	int		index;

	if (DEBUG)
	{
		printf("DEBUG. Entrando a crear el comando.\nLista de tokens:\n");
		ft_print_tok_list(toks);
	}
	res = malloc(sizeof(char *) * ft_count_tokens(toks) + 1);
	index = 0;
	while (toks && toks->type != PIPE)
	{
		if (DEBUG)
			printf("DEBUG. Copio el token: #%s#\n", toks->token);
		if (toks->type <= DBLQUOTE && toks->type >= NOQUOTE)
			res[index] = ft_strdup(toks->token);
		index++;
		toks = toks->next;
	}
	if (DEBUG)
		printf("DEBUG. Fuera del bucle.\n");
	res[index] = NULL;
	return (res);
}

void	ft_executor(t_ms *ms)
{
	if (DEBUG)
		printf("DEBUG. Entrando al ejecutor.\n");
	ms->command = ft_create_command(ms->tokens);
	if (ft_strncmp("echo", ms->command[0], 4) == 0)
		ft_echo(ms);
	else if (ft_strncmp("exit", ms->command[0], 4) == 0)
		ft_exit(ms);
	ft_free_command(ms);
	if (DEBUG)
		printf("DEBUG. Saliendo del ejecutor.\n");
}
