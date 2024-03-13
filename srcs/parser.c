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

#include "../include/minishell.h"

void	ft_print_tok_list(t_token *tok)
{
	t_token	*aux;
	int		index;

	aux = tok;
	index = 1;
	while (aux)
	{
		index++;
		aux = aux->next;
	}
}

void	ft_change_tok(t_token *tok, int s, int e, char *val)
{
	char	*new_t;
	int		index1;
	int		index2;

	index1 = 0;
	index2 = 0;
	if (val == NULL)
		val = "";
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
		if (ft_strncmp(name, "?", ft_strlen(name)) == 0)
			value = ft_itoa(ms->status);
		else
			value = ft_get_env_value(name, ms);
		ft_change_tok(tok, start - 1, end, value);
		free(name);
		free(value);
	}
}

void	ft_find_vars(t_ms *ms)
{
	t_token	*node;
	char	*str;

	node = ms->tokens;
	while (node)
	{
		if (node->type == SNGQUOTE || node->type == DBLQUOTE)
			ft_noquote(node);
		if ((node->type == NOQUOTE || node->type == DBLQUOTE)
			&& ft_strchr(node->token, '$'))
		{
			if (ft_strncmp(node->token, "$", ft_strlen(node->token)) == 0)
			{
				str = ft_strdup("$");
				free(node->token);
				node->token = str;
			}
			else
				ft_expand(ms, node);
		}
		node = node->next;
	}
}

void	ft_parser(t_ms *ms)
{
	ft_parse_tokens(ms);
	ft_find_vars(ms);
}
