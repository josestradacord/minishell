/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:25 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/05 20:32:38 by joestrad         ###   ########.fr       */
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

	/*DEBUG
	printf("ANTES:\n");	
	ft_print_env(envp);
	FIN DEBUG*/
	times = 0;
	status = TRUE;
	while (status)
	{
		ms->line = readline("minishell_V0.6$ ");
		times++;
		if (times == 3)
			status = FALSE;
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
		
		printf("DEBUG: Ejecuto el comando: #%s#\n", ms->cmds->cmd);
		ft_executor(ms);
		ft_free_cmds(ms);
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
		//ms = (t_ms *) malloc(sizeof(t_ms));
		//ms->tokens = (t_token *) malloc(sizeof(t_token));
		//ms->cmds = (t_cmd *) malloc(sizeof(t_cmd));
		ft_init_data(&ms, argv, envp);
		minishell(&ms);
		ft_free(&ms, EXIT_SUCCESS);
	}
	
	return (0);
}
