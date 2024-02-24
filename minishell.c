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
	int		pip[2];

	//int		times;
	//int		status;
	if (DEBUG)
	{
		printf("\033[36;1mDEBUG: Variables de entorno:\033[0m\n");	
		//ft_print_env(ms->envp);
	}
	//times = 0;
	//status = TRUE;
	while (TRUE)
	{
		//usleep(10000);
		//ft_bzero(ms->line,sizeof(char *));
		ms->line = readline("\033[33;1mminishell_V0.9$\033[0m ");
		//ms->line = ft_temp();
/* 		times++;
		if (times == 100)
			status = FALSE; */
		printf("%sline es %s%s\n", MAGENTA, ms->line, RESET);
/* 		if (ms->line == NULL)
			ms->line = ft_strdup("a"); */	//bucle de linea NULL
		if (ms->line == NULL)
		{
			//ft_printf("\n");
			ft_printf("%sLinea NULL%s\n", RED, RESET);//despues solo /n
			//perror ("Linea NULL");
			//exit (1);
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
		//status = ft_executor(ms);
		if (DEBUG)
			printf("%sDEBUG:%s Ejecuto el comando: #%s#\n", BLUE, RESET, ms->tokens->token);
		//ft_executor(ms, ms->tokens);	//ejecutar hijos mientras haya pipes, mirar pipex a ver si se puede adaptar facilmente
		if (ft_pipe(ms) != 0)
			perror("pipe sale mal");
		//ms->num_pipes = 0;
		ft_free_toks(ms);
	}
	return ;
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

	//atexit(ft_leaks);
	if (!ft_check_args(argc))
		ft_usage();
	else
	{
		if (DEBUG)
			printf("%sDEBUG:%s Voy a iniciar\n", BLUE, RESET);
		ft_bzero(&ms, sizeof(ms));
		ft_init_data(&ms, argv, envp);
		minishell(&ms);
		ft_free(&ms, EXIT_SUCCESS);
	}
	
	return (0);
}