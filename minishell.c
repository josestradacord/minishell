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
	ft_lste_clear(&ms->env, free);
	free(ms);
}

void	minishell(t_ms *ms, char **envp)
{
	char	*line;
	int		len;

	//DEBUG
	//printf("ANTES:\n");	
	//ft_print_env(envp);
	//FIN DEBUG
	ft_get_env(ms, envp);
	while (TRUE)
	{
		line = readline("minishell_V0.5>");
		len = ft_strlen(line);
		if ((len == 4) && !ft_strncmp(line, "exit", len))
			exit(1);
		if (len == 0)
			printf("%s", line);
		else
			printf("%s\n", line);
		free(line);
	}
	//DEBUG
	//printf("DESPUÉS:\n");
	//ft_print_env_lst(ms->env);
	//FIN DEBUG
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	//int		index;

	(void)	**argv;
	//index = 0;
	if (!ft_check_args(argc))
	{
		ft_usage();
	}
	else
	{
		ms = (t_ms *) malloc(sizeof(t_ms));
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
	atexit(ft_leaks);
	return (0);
}
