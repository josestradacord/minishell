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
		printf("DEBUG. Token nº %d\nType:\t%d\nValue:\t#%s#\n", index, aux->type, aux->token);
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
		printf("DEBUG. Después de quitar comillas: #%s#\n", tok->token);
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
		printf("DEBUG. Dentro de expand. Lista de tokens:\n");
		ft_print_tok_list(ms->tokens);
		printf("DEBUG. Dentro de expand. Token a expandir:\n");
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
		if (ft_strncmp(name, "?", ft_strlen(name)) == 0)//no probado
			value = ft_itoa(ms->status);
		else
			value = ft_get_env_value(name, ms);
		if (DEBUG)
			printf("DEBUG: Encontrada variable de entorno #%s# con valor #%s#\n", name, value);
		ft_change_tok(tok, start - 1, end, value);
		free(name);
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
		while ((node->type == NOQUOTE || node->type == DBLQUOTE)
			&& ft_strchr(node->token, '$'))
		{
			if (DEBUG)
				printf("DEBUG. Encontrada variable de entorno.\n");
			ft_expand(ms, node);
		}
		node = node->next;
	}
	if (DEBUG)
		printf("DEBUG. Saliendo de ft_find_vars()\n");
}

void	ft_parser(t_ms *ms)
{
	if (DEBUG)
		ft_printf("\nDEBUG: Dentro del parser. La linea es: #%s#\n", ms->line);
	if (DEBUG)
		ft_print_tok_list(ms->tokens);
	ft_parse_tokens(ms);
	ft_find_vars(ms);
	if (DEBUG)
		ft_print_tok_list(ms->tokens);
}