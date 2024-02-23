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
		ft_printf("%sDEBUG:%s Empiezo a liberar ft_free_tok_list()\n", BLUE, RESET);
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
		ft_printf("%sDEBUG:%s Empiezo a liberar ft_free_toks()\n", BLUE, RESET);
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
	free(ms->wanted);
	free(ms->command);
}

/*void	ft_free_cmds(t_ms *ms)
{
	t_cmd	*node;

	if (DEBUG)
		ft_printf("DEBUG: Empiezo a liberar ft_free_cmds()\n");
	//if (ms->line)
		//free(ms->line);
	node = ms->cmds;
	while (node)
	{
		if (DEBUG)
			ft_printf("%s%sDEBUG:%s%s Libero comando: #%s#%s\n", BOLD, BLUE, RESET, BLUE, RESET, ms->cmds->cmd);
		free(node->cmd);
		node = node->next;
	}
	if (ms->cmds)
		free(ms->cmds);
	ft_free_command(ms);
}*/

void	ft_free(t_ms *ms, int exit_code)
{
	if (DEBUG)
		ft_printf("%sDEBUG:%s Empiezo a liberar ft_free()\n", BLUE, RESET);
	rl_clear_history();
	if (DEBUG)
		ft_printf("%sDEBUG:%s Libero env\n", BLUE, RESET);
	ft_lste_clear(ms->env, free);
	ft_free_envp(ms);
	if (DEBUG)
		ft_printf("%sDEBUG:%s Liberado env\n", BLUE, RESET);
	if (DEBUG)
		ft_printf("%sDEBUG:%s Libero lista de tokens\n", BLUE, RESET);
	ft_free_toks(ms);
	if (DEBUG)
		ft_printf("%sDEBUG:%s Liberada lista de tokens\n", BLUE, RESET);
	if (DEBUG)
		ft_printf("%sDEBUG:%s Libero comandos\n", BLUE, RESET);
	ft_free_command(ms);
	if (DEBUG)
		ft_printf("%sDEBUG:%s Liberado comandos\n", BLUE, RESET);
	exit(exit_code);
}