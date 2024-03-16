/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:43:07 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/28 18:54:27 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_search(t_ms *ms)
{
	int			i;
	char		temp[100];
	t_list_e	*aux;

	i = -1;
	aux = ms->env;
	while (aux && ft_strncmp(aux->name, "PATH", 4))
		aux = aux->next;
	if (ms->command[0][0] == '/')
		ms->wanted = ft_strdup(ms->command[0]);
	else
	{
		while (ms->rout[++i] && aux != NULL)
		{
			ms->wanted = ft_strjoin(ms->rout[i], ms->command[0]);
			if (access(ms->wanted, F_OK) == 0)
				return (0);
			else
				free(ms->wanted);
		}
		getcwd(temp, 100);
		ms->wanted = ft_strjoin(temp, &ms->command[0][1]);
	}
	return (0);
}

int	ft_cmd(t_ms *ms)
{
	if (ft_search(ms) == 0)
		return (execve(ms->wanted, ms->command, ms->envp));
	return (1);
}

static void	ft_lastsonaux(t_ms *ms)
{
	if (ms->fdin > 0)
	{
		dup2(ms->fdin, STDIN_FILENO);
		close(ms->fdin);
	}
	if (ft_out(ms) == 2)
	{
		dup2 (ms->fdout, STDOUT_FILENO);
		close(ms->fdout);
	}
	else
		dup2(1, STDOUT_FILENO);
	ft_cmd(ms);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(ms->command[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	ms->status = 127;
	free(ms->wanted);
	exit (127);
}

int	last_son(t_ms *ms)
{
	int	pid;
	int	status;

	signal(SIGINT, ft_signal_ctrlc_son);
	pid = fork();
	if (pid == 0)
		ft_lastsonaux(ms);
	else if (pid < 0)
		return (1);
	else
	{
		if (ms->fdin > 0)
			close(ms->fdin);
		dup2(1, STDOUT_FILENO);
		ft_free_command(ms);
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED (status))
			ms->status = WEXITSTATUS(status);
		ft_signals();
	}
	return (0);
}
