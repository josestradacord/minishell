/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:01:40 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/04 20:01:40 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_noquote(t_token *tok)
{
	size_t	len;
	size_t	index;
	char	*str;

	len = ft_strlen(tok->token);
	str = (char *) malloc(sizeof(char) * len);
	if (!str)
	{
		perror("malloc error");
		return ;
	}
	len = 1;
	index = 0;
	while (tok->token[len])
		str[index++] = tok->token[len++];
	str[index - 1] = '\0';
	free(tok->token);
	tok->token = str;
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
