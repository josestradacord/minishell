#include "minishell.h"

void	ft_error(int i)
{
	if (i == 0)
		write(2, "ERROR\nWrong number of arguments\n", 32);
	if (i == 1)
		write(2, "ERROR\nIncorrect infile\n", 23);
	if (i == 2)
		write(2, "ERROR\nOrder not found\n", 22);
	if (i == 3)
		write(2, "ERROR\nFailed creating child\n", 28);
}

char	**ft_routes(char **envp)
{
	int		i;
	int		k;
	char	*temp;
	char	**rout;

	i = 0;
	k = 0;
	temp = "";
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	rout = ft_split(envp[i], ':');
	temp = ft_strjoin(temp, &rout[0][5]);
	free(rout[0]);
	rout[0] = ft_strdup(temp);
	free(temp);
	while (rout[k])
	{
		temp = ft_strjoin(rout[k], "/");
		if (rout[k])
			free(rout[k]);
		rout[k] = ft_strdup(temp);
		free(temp);
		k++;
	}
	return (rout);
}

void	ft_temp(char *wtd, int fdin)
{
	char	*str;
	char	*str2;

	str = "";
	write(1, "heredoc> ", 9);
	str2 = get_next_line(0);
	while (ft_strncmp(str2, wtd, ft_strlen(str2) - 1))
	{
		write(1, "heredoc> ", 9);
		str = ft_strjoin(str, str2);
		str2 = get_next_line(0);
	}
	dup2(fdin, STDOUT_FILENO);
	ft_printf("%s", str);
}

/* int	here_doc(char *str, t_data *data, char *outfl)
{
	int	fdin;

	fdin = open(".tmp", O_WRONLY | O_CREAT, 0644);
	if (ft_search(data, outfl) == 1)
		data->fdout = open(outfl, O_WRONLY | O_CREAT | O_APPEND, 0777);
	ft_temp(str, fdin);
	close(fdin);
	fdin = open(".tmp", O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (3);
} */

/* int	here_doc(char *str, t_data *data, char *outfl)
{
	int	fdin;

	fdin = open(".tmp", O_WRONLY | O_CREAT, 0644);
	//ft_temp(str, fdin);
	close(fdin);
	fdin = open(".tmp", O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (3);
} */

/* int	ft_enter(t_ms *ms)
{
	int	i;
	int	fdin;

	if (!ft_strncmp(argv[1], "here_doc", 8))
		return (i = here_doc(argv[2], data, argv[argc - 1]));
	else
	{
		if (ft_search(data, argv[argc - 1]) == 1)	//si no existe el ultimo argv lo crea y mete el resultado
			data->fdout = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (ft_search(data, argv[1]) == 1)			//si el primer argv no es un comando es un archivo y lo lee
		{	
			fdin = open(argv[1], O_RDONLY, 0777);
			if (fdin < 0)
			{
				ft_error(1);
				ft_allfree(data);
				exit(1);
			}
			dup2(fdin, STDIN_FILENO);
			return (i = 2);
		}
		return (i = 1);
	}
} */

/* void	son(t_ms *ms)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_cmd(data, cmd, envp);
	}
	else if (pid < 0)
		ft_error(3);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
}*/

int	ft_search(t_ms *ms)
{
	int	i;

	i = -1;
	//ms->command = ft_split(cmd, ' ');	//commt doble char **	wanted char *
	while (ms->rout[++i])
	{
		ms->wanted = ft_strjoin(ms->rout[i], ms->command[0]);
		if (access(ms->wanted, 0) == 0)
			return (0);
	}
	return (1);
}

/* int	ft_cmd(t_ms *ms)
{
	int	pid;
	int	status;

	if (ft_search(ms) == 0)	//necesita hacer un hijo para no salirse
	{
		pid = fork();
		if (pid == 0)
			execve(ms->wanted, ms->command, ms->envp);
		else
		{
			waitpid(pid, &status, 0);
			return (0);
		}
	}
	//ft_error(2);
	return (0);
} */


int	ft_cmd(t_ms * ms)
{
	if (ft_search(ms) == 0)
		execve(ms->wanted, ms->command, ms->envp);
	return (1);
}

int	son(t_ms *ms, t_token *toks)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_executor(ms, toks);
	}
	else if (pid < 0)
		return (1);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
	return (0);
}

/* 	else if (pid < 0)
		ft_error(3); */

int	last_son(t_ms *ms, t_token *toks)
{
	int	pid;
	int	status;

	pid = fork();
	ms->fdout = 0;
	if (pid == 0)
	{
		if (ms->fdout != 0)
		{	
			dup2(ms->fdout, STDOUT_FILENO);
			close(ms->fdout);
		}
		else
			dup2(1, 1);
		ft_executor(ms, toks);
	}
	else if (pid < 0)
		return (1);
	else
		waitpid(pid, &status, 0);
	return (0);
}

int	ft_pipe(t_ms *ms)
{
	int		i;
	int		end;
	t_token	*temp;
	t_token	*first;
	int		status;

	temp = ms->tokens;
	first = ms->tokens;

 	//i = ft_enter(argc, argv, &data);    //cambiar para que coja el < y el <<
/* 	if(ft_search(ms) == 0)
		end = argc - 1;
	else
		end = argc - 2; */
	while (ms->num_pipes > 0)
	{
		if (temp->type == PIPE && ms->num_pipes > 0)
		{
			//printf("tok es %s\n", first->token);
			if (son(ms, first) == 1)
				exit (1);
			//wait(&status);
			ms->num_pipes--;
			first = temp->next;
		}
		temp = temp->next;
	}
	//printf("tok es %s\n", first->token);
	if (ms->num_pipes == 0)
		last_son(ms, first);	//saca linea NULL
	//wait(&status);
	//ft_executor(ms, first);	//se sale del programa
    //añadir algo para el > y el >>, usar else de ft_enter
	//unlink(".tmp");
	return (0);
}

/* 		while (ft_strncmp (temp->token, "|", 1) != 0) //mientras haya pipes
		{
			printf("Estoy en %s\n", temp->token);
 			if (temp->next->next != NULL && ft_search(ms) == 0)
			{
				temp = temp->next->next;
			}
			else
			{
				perror("Perror");
				break ;
			}	//comando no encontrado 
			//son(ms);
				temp = temp->next;
		}
		printf("Estoy en %s al salir\n", temp->token); */