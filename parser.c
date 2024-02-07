/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:57 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/07 21:00:19 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_cmd(t_ms *ms, int s, int e)
{
	t_cmd	*new;
	t_cmd	*tmp;
	char	*cmd;

	cmd = ft_substr(ms->line, s, e - s);
	printf("DEBUG: Obteniendo el comando ft_new_cmd(). Comando: #%s#\n", cmd);
	new = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->cmd = cmd;
	//free(cmd);
	printf("DEBUG: Comando: #%s#\n", new->cmd);
	new->next = NULL;
	if (!ms->cmds)
		ms->cmds = new;
	else
	{
		tmp = ms->cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_new_tkn(t_ms *ms, int s, int e)
{
	t_token	*new;
	t_token	*aux;
	char	*tkn;

	tkn = ft_substr(ms->line, s, e - s);
	printf("DEBUG: Obteniendo el token ft_new_tkn(). Token: #%s#\n", tkn);
	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = NOQUOTE;
	new->token = tkn;
	//free(tkn);
	printf("DEBUG: Token: #%s#\n", new->token);
	new->next = NULL;
	new->prev = NULL;
	if (!ms->tokens)
		ms->tokens = new;
	else
	{
		aux = ms->tokens;
		while (aux->next)
			aux = aux->next;
		new->prev = aux;
		aux->next = new;
	}
}

void	ft_getcmd(t_ms *ms)
{
	int	ini;
	int	end;

	ini = 0;
	end = ini;
	printf("DEBUG: Obteniendo el comando. La linea es: %s, posición: %d\n", ms->line, ini);
	while (ms->line[end] && ms->line[end] != ' ')
		end++;
	printf("DEBUG: Posición final: %d\n", end);
	ft_new_cmd(ms, ini, end);
	//ms->cmds->cmd = ft_substr(ms->line, (*p), index - (*p));
	printf("DEBUG: En ft_getcmd(), el comando es: %s\n", ms->cmds->cmd);
}

/* void	ft_parse_tokens(t_ms *ms)
{
	int	index1;
	int	index2;

	index1 = 0;
	while (ms->line[index1])
	{
		index2 = index1;
		if (ms->line[index1] == '\'')
			ft_simp_quote(ms, &index1, &index2, ms->line[index1]);
		else if (ms->line[index1] == '\"')
			ft_dbl_quote(ms, &index1, &index2, ms->line[index1]);
		else if (ft_strchr(TOKSTR, ms->line[index1]))
			ft_redir_pipe_node(ms, &index1, &index2, ms->line[index1]);
		else
			ft_normal_tok(ms, &index1, &index2);
	}
} */

void	ft_parser(t_ms *ms)
{
	ft_printf("DEBUG: Dentro del parser. La linea es: #%s#\n", ms->line);
	//ft_parse_tokens(ms);
	
	ft_getcmd(ms);
	
	//ft_printf("DEBUG: El comando es: %s\n", ms->cmds->cmd);
	//ft_getargs(ms, line, &pos);
	//ft_printf("DEBUG: El comando tiene %d argumentos\n", ft_lstsize(ms->cmd->args));
}