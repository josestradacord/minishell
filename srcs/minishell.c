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

int	ft_pipe(t_ms *ms)
{
	t_token	*temp;

	if (ft_enter(ms) == 1)
		temp = ms->tokens->next;
	else
		temp = ms->tokens;
	ms->status = 0;
	if (ms->num_pipes > 0)
		ft_family(ms, temp);
	else if (ms->num_pipes == 0)
	{
		ms->command = ft_create_command(temp);
		if (ms->command[0] == NULL)
			return (0);
		if (ft_strnstr("echo exit cd pwd env unset export", ms->command[0], 33))
		{
			ms->status = ft_builtins(ms);
			ft_free_command(ms);
		}
		else
			last_son(ms);
	}
	unlink(".tmp");
	return (0);
}

void	minishell(t_ms *ms)
{
	while (TRUE)
	{
		ms->line = readline("minishell_V1.0$ ");
		if (ms->line == NULL)
			ft_control_d();
		add_history(ms->line);
		if (!ft_check_line(ms->line))
		{
			free(ms->line);
			ms->status = 258;
			continue ;
		}
		if (ft_blank_line(ms->line))
		{
			free(ms->line);
			continue ;
		}
		ft_parser(ms);
		ft_nump(ms);
		if (ft_pipe(ms) != 0)
			perror("pipe sale mal");
		ft_free_toks(ms);
	}
	return ;
}

//atexit(ft_leaks);
int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	if (!ft_check_args(argc))
		ft_usage();
	else
	{
		ft_bzero(&ms, sizeof(ms));
		ft_init_data(&ms, argv, envp);
		minishell(&ms);
		ft_free(&ms, EXIT_SUCCESS);
	}
	return (0);
}
