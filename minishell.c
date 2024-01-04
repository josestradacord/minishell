#include "minishell.h"

/**
 * @brief 		This function shows the leaks of the main function
 * 
 */
void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_free(t_ms *ms)
{
	//ft_printf("DEBUG: Empiezo a liberar\n");
	if (ms->env)
	{
		//ft_printf("DEBUG: Libero env\n");
		ft_lste_clear(&ms->env, free);
		//ft_printf("DEBUG: Liberado env\n");
	}
	//ft_printf("DEBUG: Intento liberar name\n");
	if (ms->cmd->name)
	{
		//ft_printf("DEBUG: Libero name\n");
		free(ms->cmd->name);
		//ft_printf("DEBUG: Liberado name\n");
	}
	//ft_printf("DEBUG: Intento liberar args\n");
	if (ms->cmd->args)
	{
		//ft_printf("DEBUG: Libero args\n");
		ft_lstclear(&ms->cmd->args, free);
		//ft_printf("DEBUG: Liberado args\n");
	}
	/*
	//ft_lste_clear(&ms->env, free);
	//free(ms->cmd->name);
	//ft_lstclear(&ms->cmd->args, free);
	
	free(ms->cmd);
	
	//free(ms);
	*/
}

void	ft_init_data(t_ms *ms)
{
	ms->cmd->name = NULL;
	ms->cmd->args = NULL;
	ms->cmd->next = NULL;
}

void	minishell(t_ms *ms, char **envp)
{
	char	*line;
	int		len;

	/*DEBUG
	printf("ANTES:\n");	
	ft_print_env(envp);
	FIN DEBUG*/
	ft_init_data(ms);
	ft_get_env(ms, envp);
	while (TRUE)
	{
		line = readline("minishell_V0.5>");
		//printf("He leido: #%s#", line);
		len = ft_strlen(line);
		if (line[0] != '\0')
		{
			add_history(line);
			ft_parser(ms, line);
			ft_echo(ms);
			// la salida del programa debe hacerse en otro
			//lugar: la función del parseo o la de ejecución
			if ((len == 4) && !ft_strncmp(line, "exit", len))
			{
				ft_free(ms);
				/*
				ft_lste_clear(&ms->env, free);
				free(ms->cmd->name);
				ft_lstclear(&ms->cmd->args, free);
				free(ms->cmd);
				*/
				free(line);
				exit(1);
			}

			//printf("%s\n", line); // quitar
		}
		//else
		//	printf("%s", line);
		ft_free(ms);
		free(line);
	}
	/*DEBUG
	//printf("DESPUÉS:\n");
	//ft_print_env_lst(ms->env);
	FIN DEBUG*/
	ft_free(ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	(void)	**argv;
	atexit(ft_leaks);
	if (!ft_check_args(argc))
		ft_usage();
	else
	{
		ms = (t_ms *) malloc(sizeof(t_ms));
		ms->cmd = (t_cmd *) malloc(sizeof(t_cmd));
		minishell(ms, envp);

		/*
		line = readline("minishell>");
		len = ft_strlen(line);
		if ((len == 0) || ((len == 4) && !ft_strncmp(line, "exit", len)))
		printf("%s\n", line);
		free(line);
		*/
		
		ft_free(ms);
	}
	return (0);
}
