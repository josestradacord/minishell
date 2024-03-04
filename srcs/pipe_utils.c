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
	int	i;
	char temp[100];

	i = -1;
	while (ms->rout[++i])
	{
		ms->wanted = ft_strjoin(ms->rout[i], ms->command[0]);
		if (access(ms->wanted, 0) == 0)
			return (0);
	}
	getcwd(temp, 100);
	ms->wanted = ft_strjoin(temp, &ms->command[0][1]);
	return (0);
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
		exit (0);
	}
	else if (pid < 0)
		return (1);
	else
	{
		if (ms->fdin > 0)
			close(ms->fdin);
		dup2(1, STDOUT_FILENO);
		ft_free_command(ms);
		waitpid(pid, &status, 0);
	}
	return (0);
}
