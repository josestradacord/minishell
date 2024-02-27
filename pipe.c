/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestradac <jestradac@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:45:00 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/27 23:19:09 by jestradac        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* void	ft_temp(char *wtd, int fdin)
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
} */

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

int	ft_search(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->rout[++i])
	{
		ms->wanted = ft_strjoin(ms->rout[i], ms->command[0]);
		if (access(ms->wanted, 0) == 0)
			return (0);
	}
	return (1);
}

int	ft_cmd(t_ms * ms)
{
	if (ft_search(ms) == 0)
		return (execve(ms->wanted, ms->command, ms->envp));
	return (1);
}

int	last_son(t_ms *ms)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		ms->fdout = 0;
		if (ms->fdout != 0)
		{
			dup2(ms->fdout, STDOUT_FILENO);
			close(ms->fdout);
		}
		else
			dup2(1, ms->fd[0][1]);
		dup2(ms->fd[0][0], STDIN_FILENO);
		ft_cmd(ms);
		exit (0);
	}
	else if (pid < 0)
		return (1);
	else
		waitpid(pid, &status, 0);
	return (0);
}

void	ft_first(t_ms *ms, t_token *first)
{
	int	status;

	pipe(ms->fd[ms->status]);
	ms->child_pid = fork();
	if (ms->child_pid == 0)
	{
		dup2(ms->fd[ms->status][1], STDOUT_FILENO);
		close(ms->fd[ms->status][1]);
		close(ms->fd[ms->status][0]);
		ms->command = ft_create_command(first);
		if (ft_strnstr("echo pwd env unset export", ms->command[0], 25) != 0)
		{	
			ft_builtins(ms);
			ft_free_command(ms);
		}
		else
			ft_cmd(ms);
		exit (0);
	}
	close(ms->fd[ms->status][1]);
	waitpid(ms->child_pid, &status, 0);
}

void	ft_mid(t_ms *ms, t_token *mid)
{
	int	status;

	pipe(ms->fd[ms->status]);
	ms->child_pid = fork();
	if (ms->child_pid == 0)
	{
		dup2(ms->fd[ms->status - 1][0], STDIN_FILENO);
		dup2(ms->fd[ms->status][1], STDOUT_FILENO);
		close(ms->fd[ms->status - 1][0]);
		close(ms->fd[ms->status][0]);
		close(ms->fd[ms->status][1]);
		ms->command = ft_create_command(mid);
		if (ft_strnstr("echo pwd env unset export", ms->command[0], 25) != 0)
		{
			ft_builtins(ms);
			ft_free_command(ms);
		}
		else
			ft_cmd(ms);
		exit (0);
	}
	waitpid(ms->child_pid, &status, 0);
	close(ms->fd[ms->status][1]);
	close(ms->fd[ms->status - 1][0]);
}

void	ft_last(t_ms *ms, t_token *last)
{
	int	status;

	ms->child_pid = fork();
	if (ms->child_pid == 0)
	{
		dup2 (STDOUT_FILENO, ms->fd[ms->status][1]);
		dup2(ms->fd[ms->status][0], STDIN_FILENO);
		close(ms->fd[ms->status][1]);
		close(ms->fd[ms->status][0]);
		ms->command = ft_create_command(last);
		if (ft_strnstr("echo pwd env unset export", ms->command[0], 25) != 0)
		{
			ft_builtins(ms);
			ft_free_command(ms);
		}
		else
			ft_cmd(ms);
	}
	close(ms->fd[ms->status][1]);
	close(ms->fd[ms->status][0]);
	waitpid(ms->child_pid, &status, 0);
}

void	ft_family(t_ms *ms, t_token *temp)
{
	ft_first(ms, temp);
	ms->num_pipes--;
	if (ms->child_pid < 0)
		exit (1);
	while (ms->num_pipes > 0)
	{
		if (temp->type == PIPE && ms->num_pipes > 0)
		{
			ms->status++;
			if (ms->wanted)
				free (ms->wanted);
			ft_mid(ms, temp->next);
			ms->num_pipes--;
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	while (temp->type != PIPE)
		temp = temp->next;
	ft_last(ms, temp->next);
}

int	ft_pipe2(t_ms *ms)
{
	//int		i;
	//int		end;
	t_token	*temp;
	//int		status;

	temp = ms->tokens;
	ms->status = 0;
	if (ms->num_pipes > 0)
	{
		ft_family(ms, temp);
	}
	else if (ms->num_pipes == 0)
	{
		if (DEBUG)
			printf("%sDEBUG:%s Entrando al ejecutor.\n", BLUE, RESET);
		ms->command = ft_create_command(temp);
		if (ft_strnstr("echo exit cd pwd env unset export", ms->command[0], 33))
		{
			ft_builtins(ms);
			ft_free_command(ms);
		}
		else
			last_son(ms);
	}
	return (0);
}