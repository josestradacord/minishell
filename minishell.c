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

	/*DEBUG
	printf("ANTES:\n");	
	ft_print_env(envp);
	FIN DEBUG*/
	times = 0;
	status = TRUE;
	while (status)
	{
		ms->line = readline("minishell_V0.7$ ");
		times++;
		if (times == 100)
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

		printf("DEBUG: Ejecuto el comando: #%s#\n", ms->tokens->token);
		ft_cmd(ms, ms->tokens->token); //added by Gabriel 18/02/24
		//ft_pipe(ms);
		//ft_executor(ms);
		//ft_echo(ms);
		ft_free_cmds(ms);
		//ft_free_toks(ms);
	}
	/*DEBUG
	printf("DESPUÉS:\n");
	ft_print_env_lst(ms->env);
	FIN DEBUG*/
}

/* void	minishell(t_ms *ms)
{
	int		times;
	int		status;

//	DEBUG
//	printf("ANTES:\n");	
//	ft_print_env(envp);
//	FIN DEBUG
	times = 0;
	status = TRUE;
	while (status)
	{
		ms->line = readline("minishell_V0.6$ ");
		times++;
		if (times == 100)		//se sale al  meter este numero de comannndo sean o no lineas en blancos
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

		//added by Gabriel 08/02/24
		ft_printf("\n\n---cmd es %s---\n\n", ms->cmds->cmd);
		if (!ft_strncmp(ms->cmds->cmd, "env", 3)) //trying to print env 
		{
			ft_print_env_lst(ms->env);
			//ft_print_env(ms->envp);
		}
		else if(!ft_strncmp(ms->cmds->cmd, "SYSTEMD_EXEC_PID", 16))
		{
			ft_lste_rm(ms->env, "SYSTEMD_EXEC_PID");
		}
		else if(!ft_strncmp(ms->cmds->cmd, "PATH", 4))
		{
			ft_lste_rm(ms->env, "PATH");
		}
		else if(!ft_strncmp(ms->cmds->cmd, "cd", 2))
		{
			char **dir = ft_split(ms->cmds->cmd, ' ');
			ft_printf("dir es%s\n", dir[1]);
			ft_cd(dir[1]);
		}
		else if(!ft_strncmp(ms->cmds->cmd, "LS_COLORS", 9))
		{
			ft_lste_rm(ms->env, "LS_COLORS");
		}
		else if(!ft_strncmp(ms->cmds->cmd, "exit", 4))
		{
			exit(0);
		}
		else if(!ft_strncmp(ms->cmds->cmd, "echo", 4))
		{
			char **str = ft_split(ms->cmds->cmd, ' ');
			ft_echo (str);
		}
		else if(!ft_strncmp(ms->cmds->cmd, "pwd", 3))
		{
			ft_pwd(ms);
		}
		else if(!ft_strncmp(ms->cmds->cmd, "export", 6))
		{
			ft_export(ms);
		}
		else
		{
			printf("DEBUG: Ejecuto el comando: #%s#\n", ms->cmds->cmd);
			ft_executor(ms);
		}
		//end add
		ft_free_cmds(ms);
	}
//	DEBUG
//	printf("DESPUÉS:\n");
//	ft_print_env_lst(ms->env);
//	FIN DEBUG
} */

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	//atexit(ft_leaks);
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
