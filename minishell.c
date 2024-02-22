/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:25 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/10 16:32:00 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 		This function shows the leaks of the main function
 * 
 */
void	ft_leaks(void)
{
	system("leaks -q minishell");
}

/* static int	firstson(t_ms *data, int *pip, t_list_e *envp)
{
	if (ft_search(data, data->command[0]) == 1)
		return (1);
	dup2(data->fdin, STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	close(pip[1]);
	execve(data->wanted, data->command, envp);
	return (0);
}

static int	secondson(t_ms *data, int *pip, t_list_e *envp)
{
	if (ft_search(data, data->command[0]) == 1)
		return (1);
	data->fdout = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	close(pip[1]);
	dup2(data->fdout, STDOUT_FILENO);
	execve(data->wanted, data->command, envp);
	return (0);
}

int	ft_mother(t_ms *data, int *pip, t_list_e *envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (firstson(data, pip, envp) == 1)
			return (1);
	}
	else if (pid < 0)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (secondson(data, pip, envp) == 1)
			return (1);
	}
	else if (pid < 0)
		return (1);
	return (0);
}
 */
void	minishell(t_ms *ms)
{
	int		times;
	int		status;
	t_token	*toks;
	int		pip[2];

	//int		times;
	//int		status;
	if (DEBUG)
	{
		printf("DEBUG: Variables de entorno:\n");	
		//ft_print_env(ms->envp);
	}
	//times = 0;
	//status = TRUE;
	while (TRUE)
	{
		ms->line = readline("minishell_V0.9$ ");
/* 		times++;
		if (times == 100)
			status = FALSE; */
		if (ms->line == NULL)
		{
			ft_printf("Linea NULL\n");//despues solo /n
			break ;
		}
		add_history(ms->line);	// así agregamos las líneas en blanco al historial
		if (ft_blank_line(ms->line))
		{
			free(ms->line);
			continue ;
		}
		ft_parser(ms);
		ft_nump(ms);
		toks = ms->tokens;
		//status = ft_executor(ms);
		if (DEBUG)
			printf("DEBUG: Ejecuto el comando: #%s#\n", ms->tokens->token);
/* 		if (ft_mother(ms, pip, ms->env) == 1)
			return ; */
		//wait(&status);
		//ft_executor(ms, ms->tokens);	//ejecutar hijos mientras haya pipes, mirar pipex a ver si se puede adaptar facilmente
		if (ft_pipe(ms) != 0)
			perror("pipe sale mal");
		/* while(toks->next && toks->type != PIPE)
			toks = toks->next; */
		//printf("toks es %s\n", toks->token);
		ms->num_pipes = 0;
		ft_free_toks(ms);
	}
	/*DEBUG
	printf("DESPUÉS:\n");
	ft_print_env_lst(ms->env);
	FIN DEBUG*/
}

/* 		while(toks->next && toks->type != PIPE)
			toks = toks->next;
		//printf("son y token %s\n", toks->next->token);
 		if (toks->type == PIPE && toks->next)
		{
			printf("son y token %s\n", toks->next->token);
			son(ms, toks->next);
			puts("pasa");
			//last_son(ms);
			//ft_executor(ms, toks->next);
		} */

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	atexit(ft_leaks);
	if (!ft_check_args(argc))
		ft_usage();
	else
	{
		if (DEBUG)
			printf("DEBUG: Voy a iniciar\n");
		ft_init_data(&ms, argv, envp);
		minishell(&ms);
		ft_free(&ms, EXIT_SUCCESS);
	}
	
	return (0);
}