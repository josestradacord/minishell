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
		ms->line = readline("\033[33;1mminishell_V0.9$\033[0m ");
		//ms->line = ft_temp();
		//printf("%sline es %s%s\n", MAGENTA, ms->line, RESET);
		if (ms->line == NULL)
		{
			//ft_printf("Linea NULL\n");//despues solo /n
			//break ;
			ft_control_d();
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
		ft_bzero(&ms, sizeof(ms)); // sin esto libera algo que no debe
		ft_init_data(&ms, argv, envp);
		minishell(&ms);
		ft_free(&ms, EXIT_SUCCESS);
	}
	return (0);
}