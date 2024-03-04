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
	if (DEBUG)
		perror("va a liberar comandos");
	//printf("libero comando %s\n", ms->command[0]);
	while (ms->command && ms->command[index])
	{
		if (DEBUG)
			printf("libero comando %s\n", ms->command[index]);
		free(ms->command[index]);
		index++;
	}
	if (DEBUG)
		perror("va a liberar wanted");
	if (ms->wanted)
		free(ms->wanted);
	if (DEBUG)
		perror("va a liberar command");
	if (ms->command)
		free(ms->command);
	if (DEBUG)
		perror("todo liberado");
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
			ft_printf("DEBUG: Libero comando: #%s#\n", ms->cmds->cmd);
		free(node->cmd);
		node = node->next;
	}
	if (ms->cmds)
		free(ms->cmds);
	ft_free_command(ms);
}*/

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
	if (DEBUG)
		ft_printf("DEBUG: Empiezo a liberar ft_free()\n");
	rl_clear_history();
	if (DEBUG)
		ft_printf("DEBUG: Libero env\n");
	ft_lste_clear(ms->env, free);
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
	ft_free_matrix(ms->rout);
	exit(exit_code);
}
