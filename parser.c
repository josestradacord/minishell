/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:48:57 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/10 15:53:25 by gpaez-ga         ###   ########.fr       */
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

void	ft_parse_cmds(t_ms *ms)
{
	int	index1;
	int	index2;

	index1 = 0;
	while (ms->line[index1])
	{
		index2 = index1;
		/*if (ms->line[index1] == '\'')
			ft_simp_quote(ms, &index1, &index2, ms->line[index1]);
		else if (ms->line[index1] == '\"')
			ft_dbl_quote(ms, &index1, &index2, ms->line[index1]);
		else if (ft_strchr(TOKSTR, ms->line[index1]))
			ft_redir_pipe_node(ms, &index1, &index2, ms->line[index1]);
		else*/
			//ft_normal_tok(ms, &index2, &index1);
	}
}


int	ft_is_token(char c)
{
	if (ft_strchr(TOKSTR, c) == FALSE)
		return (FALSE);
	else
		return (TRUE);
}

void	ft_new_token(t_ms *ms, int start, int end)
{
	t_token	*new_t;
	t_token	*aux;
	char	*token;

	token = ft_substr(ms->line, start, end - start);
	printf("DEBUG: Obteniendo el token en ft_new_token(). Comando token: #%s#\n", token);
	new_t = (t_token *) malloc(sizeof(t_token));
	if (!new_t)
		return ;
	new_t->token = token;
	printf("DEBUG: Comando (en ms): #%s#\n", new_t->token);
	new_t->type = NOQUOTE;
	new_t->prev = NULL;
	new_t->next = NULL;
	if (!ms->tokens)
	{
		printf("DEBUG: Primer token de la lista\n");
		ms->tokens = new_t;
	}
	else
	{
		aux = ms->tokens;
		while (aux->next)
			aux = aux->next;
		new_t->prev = aux;
		aux->next = new_t;
	}
	printf("DEBUG: Saliendo de ft_new_token()\n");
}


void	ft_normal_tok(t_ms *ms, int *start, int *index)
{
	int	s;
	int	i;

	i = *index;
	s = *start;
	while (ms->line[i] && ms->line[i] == ' ')
		i++;
	s = i;
	while (ms->line[i] && !ft_is_token(ms->line[i]))
		i++;
	if (i > s)
		ft_new_token(ms, s, i);
	*index = i;
	printf("DEBUG: Saliendo de ft_normal_tok()\n");
}

void	ft_simp_quote(t_ms *ms, int *start, int *end, char s_quot)
{
	int	s;
	int	e;

	s = *start;
	e = *end;
	e++;
	while (ms->line[e] && ms->line[e] != s_quot)
		e++;
	if (ms->line[e] == s_quot)
		e++;
	*end = e;
	ft_new_token(ms, s, e);
}

void	ft_dbl_quote(t_ms *ms, int *start, int *end, char s_quot)
{
	int	s;
	int	e;

	s = *start;
	e = *end;
	e++;
	while (ms->line[e] && ms->line[e] != s_quot)
		e++;
	if (ms->line[e] == s_quot)
		e++;
	*end = e;
	ft_new_token(ms, s, e);
}

void	ft_redir_pipe_node(t_ms *ms, int *start, int *end, char tok)
{
	int	s;
	int	e;

	s = *start;
	e = *end;
	e++;
	if (ms->line[e] == tok && tok != '|')
		e++;
	if (tok == '<' || tok == '>')
	{
		while (ms->line[e] == ' ')
			e++;
		while (ms->line[e] && ft_strchr(SEPCHAR, ms->line[e]) == 0)
			e++;
	}
	*end = e;
	ft_new_token(ms, s, e);
}

void	ft_parse_tokens(t_ms *ms)
{
	int	start;
	int	end;

	end = 0;
	while (ms->line[end])
	{
		start = end;
		if (ms->line[end] == '\'')
			ft_simp_quote(ms, &start, &end, ms->line[end]);
		else if (ms->line[end] == '\"')
			ft_dbl_quote(ms, &start, &end, ms->line[end]);
		else if (ft_strchr(TOKSTR, ms->line[end]))
			ft_redir_pipe_node(ms, &start, &end, ms->line[end]);
		else
			ft_normal_tok(ms, &start, &end);
	}
}

void	ft_print_tok_list(t_ms *ms)
{
	t_token	*aux;
	int		index;

	aux = ms->tokens;
	index = 1;
	while (aux)
	{
		printf("DEBUG. Token nº %d\nType:\t%d\nValue:\t%s\n\n", index, aux->type, aux->token);
		index++;
		aux = aux->next;
	}
}

void	ft_parser(t_ms *ms)
{
	ft_printf("\nDEBUG: Dentro del parser. La linea es: #%s#\n", ms->line);
	ft_print_tok_list(ms);
	ft_parse_tokens(ms);
	
	ft_print_tok_list(ms);
	//ft_parse_cmds(ms);
	
	//ft_printf("DEBUG: El comando es: %s\n", ms->cmds->cmd);
	//ft_getargs(ms, line, &pos);
	//ft_printf("DEBUG: El comando tiene %d argumentos\n", ft_lstsize(ms->cmd->args));
}
