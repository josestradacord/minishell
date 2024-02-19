/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:07 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/19 20:53:00 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_free_tok_list(t_token *toks)
{
	t_token	*node;

	if (DEBUG)
		ft_printf("DEBUG: Empiezo a liberar ft_free_tok_list()\n");
	node = toks;
	while (toks)
	{
		node = toks->next;
		free(toks->token);
		free(toks);
		toks = node;
	}
}

void	ft_free_toks(t_ms *ms)
{
	t_token	*node;

	if (DEBUG)
		ft_printf("DEBUG: Empiezo a liberar ft_free_toks()\n");
	if (ms->line)
		free(ms->line);
	node = ms->tokens;
	ft_free_tok_list(node);
	ms->tokens = NULL;
}

void	ft_free_command(t_ms *ms)
{
	int	index;

	/*if (ms->line)
		free(ms->line);*/
	index = 0;
	while (ms->command[index])
	{
		free(ms->command[index]);
		index++;
	}
	free(ms->command);
}

void	ft_free_cmds(t_ms *ms)
{
	t_cmd	*node;

	if (DEBUG)
		ft_printf("DEBUG: Empiezo a liberar ft_free_cmds()\n");
	/*if (ms->line)
		free(ms->line);*/
	node = ms->cmds;
	while (node)
	{
		if (DEBUG)
			ft_printf("DEBUG: Libero comando: #%s#\n", ms->cmds->cmd);
		free(node->cmd);
		node = node->next;
	}
	if (ms->cmds)
		free(ms->cmds);
	ft_free_command(ms);
}

void	ft_free(t_ms *ms, int exit_code)
{
	if (DEBUG)
		ft_printf("DEBUG: Empiezo a liberar ft_free()\n");
	rl_clear_history();
	if (DEBUG)
		ft_printf("DEBUG: Libero env\n");
	ft_lste_clear(&ms->env, free);
	ft_free_envp(ms);
	if (DEBUG)
		ft_printf("DEBUG: Liberado env\n");
	if (DEBUG)
		ft_printf("DEBUG: Libero lista de tokens\n");
	ft_free_toks(ms);
	if (DEBUG)
		ft_printf("DEBUG: Liberada lista de tokens\n");
	if (DEBUG)
		ft_printf("DEBUG: Libero comandos\n");
	ft_free_command(ms);
	if (DEBUG)
		ft_printf("DEBUG: Liberado comandos\n");
	exit(exit_code);
}
