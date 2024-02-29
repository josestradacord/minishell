/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:45:00 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/27 19:45:00 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first(t_ms *ms, t_token *first)
{
	int	status;

	pipe(ms->fd[ms->status]);
	ms->child_pid = fork();
	if (ms->child_pid == 0)
	{
		if (ms->fdin > 0)
		{
			dup2(ms->fdin, STDIN_FILENO);
			close(ms->fdin);
		}
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
	if (ms->fdin > 0)
		close(ms->fdin);
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
		if (ft_out(ms) == 2)
		{
			dup2(ms->fdout, STDOUT_FILENO);
			close(ms->fdout);
			close(ms->fd[ms->status][1]);
		}
		else
		{
			dup2 (STDOUT_FILENO, ms->fd[ms->status][1]);
			close(ms->fd[ms->status][1]);
		}
		dup2(ms->fd[ms->status][0], STDIN_FILENO);
		close(ms->fd[ms->status][0]);
		ms->command = ft_create_command(last);
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

void	ft_execmini(t_ms *ms)	//cambiar codigo para que no modifique valores y sea mas limpio todo
{
	t_list_e *temp;

	temp = ms->env;
	ms->command = malloc(sizeof(char *) * 2);
	ms->command[0] = ft_strdup("./minishell");
	ms->command[1] = NULL;
	while (ft_strncmp(temp->name, "PWD", 3))
		temp = temp->next;
	temp->value = ft_strjoin(temp->value, "/minishell");
	execve(temp->value, ms->command, ms->envp);
}

int	ft_pipe(t_ms *ms)
{
	int		i;
	int		end;
	t_token	*temp;
	int		status;

	if (ft_strncmp(ms->tokens->token, "./minishell", 11) == 0)
		ft_execmini(ms);
	if (ft_enter(ms) == 1)
		temp = ms->tokens->next;
	else
		temp = ms->tokens;
	ms->status = 0;
	if (ms->num_pipes > 0)
		ft_family(ms, temp);
	else if (ms->num_pipes == 0)
	{
		if (DEBUG)
			printf("%sDEBUG:%s Entrando al ejecutor.\n", BLUE, RESET);
		printf("temp es %s\n",temp->token);
		ms->command = ft_create_command(temp);
		printf("command es $%s$\n",ms->command[0]);
		if (ft_strnstr("echo exit cd pwd env unset export", ms->command[0], 33))
		{
			perror("builtin");
			ft_builtins(ms);
			ft_free_command(ms);
		}
		else
			last_son(ms);
	}
	unlink(".tmp");
	return (0);
}
