#include "minishell.h"

int	ft_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	else
		return (FALSE);
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
	t_token	*new_tok;
	t_token	*aux;
	char	*token;

	token = ft_substr(ms->line, start, end - start);
	if (DEBUG)
		printf("DEBUG: Obteniendo el token en ft_new_token(). Comando token: #%s#\n", token);
	new_tok = (t_token *) malloc(sizeof(t_token));
	if (!new_tok)
		return ;
	new_tok->token = token;
	if (DEBUG)
		printf("DEBUG: Comando (en ms): #%s#\n", new_tok->token);
	new_tok->type = NOQUOTE;
	new_tok->prev = NULL;
	new_tok->next = NULL;
	if (!ms->tokens)
	{
		if (DEBUG)
			printf("DEBUG: Primer token de la lista\n");
		ms->tokens = new_tok;
	}
	else
	{
		aux = ms->tokens;
		while (aux->next)
			aux = aux->next;
		new_tok->prev = aux;
		aux->next = new_tok;
	}
	if (DEBUG)
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
	while (ms->line[i] && !ft_is_quote(ms->line[i])
		&& !ft_is_token(ms->line[i]))
		i++;
	if (i > s)
		ft_new_token(ms, s, i);
	*index = i;
	if (DEBUG)
		printf("DEBUG: Saliendo de ft_normal_tok()\n");
}

void	ft_token_type(t_ms *ms)
{
	t_token	*n;
	size_t	len;

	n = ms->tokens;
	while (n)
	{
		len = ft_strlen(n->token);
		if (n->token[0] == '\"' && len > 0 && n->token[len - 1] == '\"')
			n->type = DBLQUOTE;
		else if (n->token[0] == '\'' && len > 0 && n->token[len - 1] == '\'')
			n->type = SNGQUOTE;
		else if (n->token[0] == '>' && n->token[1] == '>')
			n->type = OUTREDIR_A;
		else if (n->token[0] == '>')
			n->type = OUTREDIR;
		else if (n->token[0] == '<' && n->token[1] == '<')
			n->type = HEREDOC;
		else if (n->token[0] == '<')
			n->type = INPREDIR;
		else if (n->token[0] == '|')
			n->type = PIPE;
		else
			n->type = NOQUOTE;
		n = n->next;
	}
}