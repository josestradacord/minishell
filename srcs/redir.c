/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:31:58 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/02/28 19:56:56 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_heredoc(char *str1, char *str2)
{
	if (str1 != NULL && ft_strncmp(str1, "", 1))
		free(str1);
	if (str2)
		free(str2);
}

void	ft_temp(t_ms *ms)
{
	//char	*str;
	char	*str2;
	int		i;

	i = 2;
	//str = "";
	write(1, "heredoc> ", 9);
	str2 = get_next_line(0);
	while (ms->tokens->token[i] <= ' ')
		i++;
	ms->wanted = ft_strdup(&ms->tokens->token[i]);
	while (ft_strncmp(str2, ms->wanted, ft_strlen(str2) - 1) != 0)
	{
		//str = ft_strjoin(str, str2);
		ft_putstr_fd(str2, ms->fdin);
		free(str2);
		write(1, "heredoc> ", 9);
		str2 = get_next_line(0);
	}
	if (ms->wanted)
	{
		free(ms->wanted);
		ms->wanted = NULL;
	}
	//write(ms->fdin, str, ft_strlen(str));
	//ft_free_heredoc(str, str2);
	free(str2);
}

int	here_doc(t_ms *ms)
{
	ms->fdin = open(".tmp", O_WRONLY | O_CREAT, 0644);
	ft_temp(ms);
	close(ms->fdin);
	ms->fdin = open(".tmp", O_RDONLY);
	return (0);
}

int	ft_enter(t_ms *ms)
{
	int		i;

	i = 1;
	if (ms->tokens->type == HEREDOC)
	{
		here_doc(ms);
		return (1);
	}
	if (ms->tokens->type == INPREDIR)
	{
		while (ms->tokens->token[i] <= ' ')
			i++;
		ms->fdin = open(&ms->tokens->token[i], O_RDONLY);
		return (1);
	}
	return (0);
}

int	ft_out(t_ms *ms)
{
	int		i;
	t_token	*tok;

	tok = ms->tokens;
	i = 1;
	while (tok->next && ms->tokens->type != OUTREDIR
		&& ms->tokens->type != OUTREDIR_A)
		tok = tok->next;
	if (tok->type == 14)
	{
		while (tok->token[i] <= ' ')
			i++;
		ms->fdout = open(&tok->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		return (2);
	}
	if (tok->type == OUTREDIR_A)
	{
		i++;
		while (tok->token[i] <= ' ')
			i++;
		ms->fdout = open(&tok->token[i], O_WRONLY | O_APPEND | O_CREAT, 0777);
		return (2);
	}
	return (0);
}
