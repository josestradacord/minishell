/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:07 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/09 15:40:44 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_envp(t_ms *ms)
{
	int	index;

	index = 0;
	while (ms->envp[index])
	{
		free(ms->envp[index]);
		index++;
	}
	free(ms->envp);
}

void	ft_free_toks(t_ms *ms)
{
	t_token	*node;

	if (ms->line)
		free(ms->line);
	if (ms->wanted)
		free(ms->wanted);
	node = ms->tokens;
	while (ms->tokens)
	{
		node = ms->tokens->next;
		if (ms->tokens->token)
			free(ms->tokens->token);
		if (ms->tokens)
			free(ms->tokens);
		ms->tokens = node;
	}
	ms->tokens = NULL;
}

void	ft_free_command(t_ms *ms)
{
	int	index;

	index = 0;
	while (ms->command && ms->command[index])
	{
		free(ms->command[index]);
		index++;
	}
	if (ms->wanted)
		free(ms->wanted);
	if (ms->command)
		free(ms->command);
	ms->command = NULL;
}

void	ft_free_matrix(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index])
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
}

void	ft_free(t_ms *ms, int exit_code)
{
	rl_clear_history();
	ft_lste_clear(ms->env, free);
	ft_free_envp(ms);
	ft_free_toks(ms);
	if (ms->command)
		ft_free_command(ms);
	ft_free_matrix(ms->rout);
	exit(exit_code);
}
