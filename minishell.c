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
		ms->line = readline("minishell_V0.7$ ");
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
		//status = ft_executor(ms);

		if (DEBUG)
			printf("DEBUG: Ejecuto el comando: #%s#\n", ms->tokens->token);
		ft_cmd(ms, ms->tokens->token); //added by Gabriel 18/02/24
		ft_pipe(ms);
		//ft_executor(ms);
		//ft_echo(ms);
		//ft_free_cmds(ms);
		ft_free_toks(ms);
	}
	/*DEBUG
	printf("DESPUÉS:\n");
	ft_print_env_lst(ms->env);
	FIN DEBUG*/
}

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