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

#include "minishell.h"

/* void	ft_error(int i)		//no se usa actualmente
{
	if (i == 0)
		write(2, "ERROR\nWrong number of arguments\n", 32);
	if (i == 1)
		write(2, "ERROR\nIncorrect infile\n", 23);
	if (i == 2)
		write(2, "ERROR\nOrder not found\n", 22);
	if (i == 3)
		write(2, "ERROR\nFailed creating child\n", 28);
} */

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

	perror("ultimo hijo");
	pid = fork();
	if (pid == 0)
	{
		perror("en hijo");
		if (ms->fdin > 0)
		{
			dup2(ms->fdin, STDIN_FILENO);
			close(ms->fdin);
		}
		if (ft_out(ms) == 2)
		{
			perror("entra");
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
		waitpid(pid, &status, 0);
	}
	return (0);
}
