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
	if (DEBUG)
		printf("DEBUG: Obteniendo el comando ft_new_cmd(). Comando: #%s#\n", cmd);
	new = (t_cmd *) malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->cmd = cmd;
	//free(cmd);
	if (DEBUG)
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
	if (DEBUG)
		printf("DEBUG: Obteniendo el comando. La linea es: %s, posición: %d\n", ms->line, ini);
	while (ms->line[end] && ms->line[end] != ' ')
		end++;
	if (DEBUG)
		printf("DEBUG: Posición final: %d\n", end);
	ft_new_cmd(ms, ini, end);
	//ms->cmds->cmd = ft_substr(ms->line, (*p), index - (*p));
	if (DEBUG)
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
	if (ft_strchr(SEPCHAR, c) == FALSE)
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
	if (DEBUG)
		printf("DEBUG: Obteniendo el token en ft_new_token(). Comando token: #%s#\n", token);
	new_t = (t_token *) malloc(sizeof(t_token));
	if (!new_t)
		return ;
	new_t->token = token;
	if (DEBUG)
		printf("DEBUG: Comando (en ms): #%s#\n", new_t->token);
	//new_t->type = NOQUOTE;
	new_t->prev = NULL;
	new_t->next = NULL;
	if (!ms->tokens)
	{
		if (DEBUG)
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
	if (DEBUG)
		printf("DEBUG: Saliendo de ft_new_token()\n");
}

int		ft_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	else
		return (FALSE);
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
	while (ms->line[i] && !ft_is_quote(ms->line[i]) && !ft_is_token(ms->line[i]))
		i++;
	if (i > s)
		ft_new_token(ms, s, i);
	*index = i;
	if (DEBUG)
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

void	ft_token_type(t_ms *ms)
{
	t_token	*node;
	size_t	len;

	node = ms->tokens;
	while (node)
	{
		len = ft_strlen(node->token);
		if (node->token[0] == '\"' && len > 0 && node->token[len - 1] == '\"')
			node->type = DBLQUOTE;
		else if (node->token[0] == '\'' && len > 0 && node->token[len - 1] == '\'')
			node->type = SNGQUOTE;
		else if (node->token[0] == '>' && node->token[1] == '>')
			node->type = OUTREDIR_A;
		else if (node->token[0] == '>')
			node->type = OUTREDIR;
		else if (node->token[0] == '<' && node->token[1] == '<')
			node->type = HEREDOC;
		else if (node->token[0] == '<')
			node->type = INPREDIR;
		else if (node->token[0] == '|')
			node->type = PIPE;
		else
			node->type = NOQUOTE;
		node = node->next;
	}
}

void	ft_parse_tokens(t_ms *ms)
{
	int	start;
	int	end;

	end = 0;
	while (ms->line[end])
	{
		start = end;
		if (ms->line[end] == '\"')
			ft_dbl_quote(ms, &start, &end, ms->line[end]);
		else if (ms->line[end] == '\'')
			ft_simp_quote(ms, &start, &end, ms->line[end]);
		else if (ft_strchr(TOKSTR, ms->line[end]))
			ft_redir_pipe_node(ms, &start, &end, ms->line[end]);
		else
			ft_normal_tok(ms, &start, &end);
	}
	ft_token_type(ms);
}

void	ft_print_tok_list(t_ms *ms)
{
	t_token	*aux;
	int		index;

	aux = ms->tokens;
	index = 1;
	while (aux)
	{
		printf("DEBUG. Token nº %d\nType:\t%d\nValue:\t#%s#\n\n", index, aux->type, aux->token);
		index++;
		aux = aux->next;
	}
}

void	ft_noquote(t_token *tok)
{
	size_t	len;
	char	*str;

	if (DEBUG)
		printf("DEBUG. Antes de quitar comillas: #%s#\n", tok->token);
	len = ft_strlen(tok->token);
	str = (char *) malloc(sizeof(char) * (len - 1));
	if (!str)
		return ;
	len = 0;
	while (tok->token[len])
	{
		str[len] = tok->token[len + 1];
		len++;
	}
	str[len - 2] = '\0';
	free(tok->token);
	tok->token = str;
	if (DEBUG)
		printf("DEBUG. Después de quitar comillas: #%s#\n", tok->token);
	
}

void	ft_change_tok(t_token *tok, int s, int e, char *val, size_t len_val)
{
	char	*new_t;
	int		index1;
	int		index2;
	size_t	len_tok;
	
	index1 = 0;
	index2 = 0;
	if (val == NULL)
		val = "";
	len_tok = ft_strlen(tok->token);
	new_t = (char *) malloc(sizeof(char) * (len_tok - (e - s) + len_val + 1));
	if (!new_t)
		return ;
	while (index2 < s)
		new_t[index1++] = tok->token[index2++];
	index2 = 0;
	while (val[index2])
		new_t[index1++] = val[index2++];
	index2 = e;
	while (tok->token[index2])
		new_t[index1++] = tok->token[index2++];
	new_t[index1] = '\0';
	free(tok->token);
	tok->token = new_t;
}

void	ft_expand(t_ms *ms, t_token *tok)
{
	int		start;
	int		end;
	char	*name;
	char	*value;

	start = 0;
	while (tok->token[start] && tok->token[start] != '$')
		start++;
	if (tok->token[start] == '$')
	{
		start++;
		end = start;
		while (tok->token[end] && !ft_strchr(ENVCHARS, tok->token[end]))
			end++;
		name = ft_substr(tok->token, start, end - start);
		value = ft_get_env_value(name, ms);
		if (DEBUG)
			printf("DEBUG: Encontrada variable de entorno #%s# con valor #%s#\n", name, value);
		ft_change_tok(tok, start - 1, end, value, ft_strlen(value));
		free(name);
		free(value);
	}
}

void	ft_find_vars(t_ms *ms)
{
	t_token	*node;

	if (DEBUG)
		printf("DEBUG. Dentro de ft_find_vars()\n");
	node = ms->tokens;
	while (node)
	{
		if (node->type == SNGQUOTE || node->type == DBLQUOTE)
			ft_noquote(node);
		if ((node->type == NOQUOTE || node->type == DBLQUOTE) 
				&& ft_strchr(node->token, '$'))
		{
			if (DEBUG)
				printf("DEBUG. Encontrada variable de entorno.\n");
			ft_expand(ms, node);
		}
		node = node->next;
	}
}

void	ft_parser(t_ms *ms)
{
	if (DEBUG)
		ft_printf("\nDEBUG: Dentro del parser. La linea es: #%s#\n", ms->line);
	if (DEBUG)
		ft_print_tok_list(ms);
	ft_parse_tokens(ms);
	ft_find_vars(ms);
	
	if (DEBUG)
		ft_print_tok_list(ms);
	//ft_parse_cmds(ms);
}