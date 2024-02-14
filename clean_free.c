/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:07 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/12 20:21:41 by joestrad         ###   ########.fr       */
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

void	ft_free_toks(t_ms *ms)
{
	t_token	*node;

	ft_printf("DEBUG: Empiezo a liberar ft_free_toks()\n");
	node = ms->tokens;
	while (node)
	{
		free(node->token);
		node = node->next;
	}
	if (ms->tokens)
		free(ms->tokens);
	ms->tokens = NULL;
}

void	ft_free_command(t_ms *ms)
{
	int	index;

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

	ft_printf("DEBUG: Empiezo a liberar ft_free_cmds()\n");
	if (ms->line)
		free(ms->line);
	node = ms->cmds;
	while (node)
	{
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
	ft_printf("DEBUG: Empiezo a liberar ft_free()\n");
	rl_clear_history();
	ft_printf("DEBUG: Libero env\n");
	ft_lste_clear(&ms->env, free);
	ft_free_envp(ms);
	ft_printf("DEBUG: Liberado env\n");
	/*ft_printf("DEBUG: Libero cmds\n");
	if (ms->cmds)
	{
		ft_printf("DEBUG: Empiezo a liberar comandos\n");
		ft_free_cmds(ms);
	}
	//free(ms);
	ft_printf("DEBUG: Liberado cmds\n");*/
	exit(exit_code);
}

// void	ft_free_kk(t_ms *ms)
// {
// 	ft_printf("DEBUG: Empiezo a liberar ft_free()\n");
// 	if (ms->env)
// 	{
// 		ft_printf("DEBUG: Libero env\n");
// 		ft_lste_clear(&ms->env, free);
// 		ft_free_envp(ms);
// 		ft_printf("DEBUG: Liberado env\n");
// 	}
// 	if (ms->line)
// 	{
// 		ft_printf("DEBUG: Libero line #%s# %p\n", ms->line, ms->line);
// 		free(ms->line);
// 		ft_printf("DEBUG: Liberado line\n");
// 	}
// 	//free(ms->tokens);

// 	if (ms->tokens)
// 	{
// 		ft_printf("DEBUG: Libero tokens\n");
// 		ft_free_toks(ms);
// 		ft_printf("DEBUG: Liberado tokens\n");
// 	}

// 	/*
// 	ft_printf("DEBUG: Intento liberar name: #%s# punt: #%p#\n", ms->cmd->name, &ms->cmd->name);
// 	if (ms->cmd->name)
// 	{
// 		ft_printf("DEBUG: Libero name: %s\n", ms->cmd->name);
// 		free(ms->cmd->name);
// 		ms->cmd->name = NULL;
// 		ft_printf("DEBUG: Liberado name\n");
// 	}
// 	ft_printf("DEBUG: Intento liberar args\n");
// 	if (ms->cmd->args)
// 	{
// 		ft_printf("DEBUG: Libero args\n");
// 		ft_lstclear(&ms->cmd->args, free);
// 		ft_printf("DEBUG: Liberado args\n");
// 	}
// 	ft_printf("DEBUG: Liberado args (fuera del if)\n");
// 	ft_printf("DEBUG: Comando: #%p#\n", &ms->cmd);
// 	if (ms->cmd)
// 	{
// 		ft_printf("DEBUG: Comando no nulo\n");
// 		free(ms->cmd);
// 		ft_printf("DEBUG: Liberado comando no nulo\n");
// 	}
// 	*/
// 	//free(ms);
// 	//
// 	//ft_lste_clear(&ms->env, free);
// 	//free(ms->cmd->name);
// 	//ft_lstclear(&ms->cmd->args, free);
	
// 	//free(ms->cmd);
	
// 	/*if (ms)
// 	{
// 		ft_printf("DEBUG: Libero ms\n");
// 		free(ms);
// 		ft_printf("DEBUG: Liberado ms\n");
// 	}*/

// 	//free(ms);
// }
