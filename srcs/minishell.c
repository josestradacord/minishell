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

#include "../include/minishell.h"

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
	int		status;
	
	if (DEBUG)
		printf("\033[36;1mDEBUG: Variables de entorno:\033[0m\n");	
	while (TRUE)
	{
		ms->line = readline("\033[33;1mminishell_V1.0$\033[0m ");
		if (ms->line == NULL)
		{
			//ft_printf("\n");
			ft_control_d();
		}
		add_history(ms->line);
		if (!ft_check_line(ms->line))
		{
			free(ms->line);
			continue ;
		}
		if (ft_blank_line(ms->line))
		{
			free(ms->line);
			continue ;
		}
		ft_parser(ms);
		ft_nump(ms);
		if (DEBUG)
			printf("%sDEBUG:%s Ejecuto el comando: #%s#\n", BLUE, RESET, ms->tokens->token);
		if (ft_pipe(ms) != 0)
			perror("pipe sale mal");
		ms->num_pipes = 0;
		ms->fdin = 0;
		ft_free_toks(ms);
	}
	return ;
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
			printf("%sDEBUG:%s Voy a iniciar\n", BLUE, RESET);
		ft_bzero(&ms, sizeof(ms));
		ft_init_data(&ms, argv, envp);
		minishell(&ms);
		ft_free(&ms, EXIT_SUCCESS);
	}
	return (0);
}