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

void	ft_print_tok_list(t_token *tok)
{
	t_token	*aux;
	int		index;

	aux = tok;
	index = 1;
	while (aux)
	{
		printf("%sDEBUG:%s Token nº %d\nType:\t%d\nValue:\t#%s#\n", BLUE, RESET , index, aux->type, aux->token);
		index++;
		aux = aux->next;
	}
}

void	ft_noquote(t_token *tok)
{
	size_t	len;
	char	*str;

	if (DEBUG)
		printf("%sDEBUG:%s Antes de quitar comillas: #%s#\n", BLUE, RESET , tok->token);
	len = ft_strlen(tok->token);
	str = (char *) malloc(sizeof(char) * (len - 1));
	if (!str)
	{
		perror("malloc error");
		return ;
	}
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
		printf("%sDEBUG:%s Después de quitar comillas: #%s#\n", BLUE, RESET , tok->token);
}

/*void	ft_change_tok(t_token *tok, int s, int e, char *val, size_t len_val)
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
}*/

void	ft_change_tok(t_token *tok, int s, int e, char *val)
{
	char	*new_t;
	int		index1;
	int		index2;

	index1 = 0;
	index2 = 0;
	if (val == NULL)
		val = "";
	//len_tok = ;
	new_t = (char *) malloc(sizeof(char) * (ft_strlen(tok->token) \
							- (e - s) + ft_strlen(val) + 1));
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

	if (DEBUG)
	{
		printf("%sDEBUG:%s Dentro de expand. Lista de tokens:\n", BLUE, RESET);
		ft_print_tok_list(ms->tokens);
		printf("%sDEBUG:%s Dentro de expand. Token a expandir:\n", BLUE, RESET);
		ft_print_tok_list(tok);

	}
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
			printf("%sDEBUG:%s Encontrada variable de entorno #%s# con valor #%s#\n", BLUE, RESET , name, value);
		ft_change_tok(tok, start - 1, end, value);
		free(name);
	}
}

/*void	ft_expand(t_ms *ms, t_token *tok)
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
}*/

void	ft_find_vars(t_ms *ms)
{
	t_token	*node;

	if (DEBUG)
		printf("%sDEBUG:%s Dentro de ft_find_vars()\n", BLUE, RESET);
	node = ms->tokens;
	while (node)
	{
		if (node->type == SNGQUOTE || node->type == DBLQUOTE)
			ft_noquote(node);
		while ((node->type == NOQUOTE || node->type == DBLQUOTE)
			&& ft_strchr(node->token, '$'))
		{
			if (DEBUG)
				printf("%sDEBUG:%s Encontrada variable de entorno.\n", BLUE, RESET);
			ft_expand(ms, node);
		}
		node = node->next;
	}
	if (DEBUG)
		printf("%sDEBUG:%s Saliendo de ft_find_vars()\n", BLUE, RESET);
}

void	ft_parser(t_ms *ms)
{
	if (DEBUG)
		ft_printf("\n%sDEBUG:%s Dentro del parser. La linea es: #%s#\n", BLUE, RESET , ms->line);
	if (DEBUG)
		ft_print_tok_list(ms->tokens);
	ft_parse_tokens(ms);
	ft_find_vars(ms);
	if (DEBUG)
		ft_print_tok_list(ms->tokens);
}