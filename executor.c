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
		perror(ms->command[0]);
	else if (ms->child_pid == 0)
	{
		if (execve(ms->command[0], ms->command, ms->envp) == - 1)
			perror(ms->command[0]);
		ft_free(ms, EXIT_FAILURE);
	}
	else
	{
		waitpid(ms->child_pid, &status, WUNTRACED);
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

void		ft_builtins(t_ms *ms)
{
	if (DEBUG)
		printf("Es un builtin\n");
	if (ft_strncmp("echo", ms->command[0], 4) == 0)
		ft_echo(ms);
	else if (ft_strncmp("exit", ms->command[0], 4) == 0)
		ft_exit(ms);
	else if (ft_strncmp("cd", ms->command[0], 2) == 0)
		ft_cd(ms, ms->command[1]);
	else if (ft_strncmp("pwd", ms->command[0], 3) == 0)
		ft_pwd(ms);
	else if (ft_strncmp("env", ms->command[0], 3) == 0)
		ft_print_env_lst(ms->env);
	else if (ft_strncmp("unset", ms->command[0], 5) == 0)
		ft_lste_rm(ms->env, ms->command[1]);
	else if (ft_strncmp("export", ms->command[0], 6) == 0)
		ft_export(ms);
	//return (0);
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

/* void	ft_executor(t_ms *ms, t_token *toks)
{
	if (DEBUG)
		printf("DEBUG. Entrando al ejecutor.\n");
	ms->command = ft_create_command(toks);
	printf("command 0 es %s\n", ms->command[0]);
	if (ft_strnstr("echo exit cd pwd env unset export", ms->command[0], 33) != 0)
		ft_builtins(ms);
	else
		ft_cmd(ms);
		//ft_execute_command(ms);
	ft_free_command(ms);
	if (DEBUG)
		printf("DEBUG. Saliendo del ejecutor.\n");
	while(toks->next && toks->type != PIPE)
		toks = toks->next;
	if (toks->type == PIPE && toks->next)
	{
		printf("son y token %s\n", toks->next->token);
		son(ms, toks->next);
		puts("pasa");
		//last_son(ms);
		//ft_executor(ms, toks->next);
	}
	else if (toks->type == PIPE && !toks->next)
	{
		//son(ms);
		puts("last son");
		last_son(ms);
		//ft_executor(ms, toks);
	}
	return ;
} */

void	ft_nump(t_ms *ms)
{
	t_token *toks;

	toks = ms->tokens;
	while (toks)
	{
		if (toks->type == PIPE)
			ms->num_pipes++;
		toks = toks->next;
	}
	printf("%d num pipes\n", ms->num_pipes);
}

/* void	ft_executor(t_ms *ms, t_token *toks)
{

	//lo de abajo es porvisional
	if (DEBUG)
		printf("DEBUG. Entrando al ejecutor.\n");

	if (ft_strnstr("echo exit cd pwd env unset export", ms->command[0], 33) != 0)
		ft_builtins(ms);
	else
		ft_cmd(ms);
		//ft_execute_command(ms);
	ft_free_command(ms);
	if (DEBUG)
		printf("DEBUG. Saliendo del ejecutor.\n");
} */

void	ft_executor(t_ms *ms)	//original
{
	if (DEBUG)
		printf("DEBUG. Entrando al ejecutor.\n");
	ms->command = ft_create_command(ms->tokens);
	if (ft_strnstr("echo exit cd pwd env unset export", ms->command[0], 33) != 0)
		ft_builtins(ms);
	else
		ft_cmd(ms);
		//ft_execute_command(ms);
	ft_free_command(ms);
	if (DEBUG)
		printf("DEBUG. Saliendo del ejecutor.\n");
}