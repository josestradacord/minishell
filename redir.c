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

# include "minishell.h"



/* int	here_doc(char *str, t_data *data, char *outfl)
{
	int	fdin;

	fdin = open(".tmp", O_WRONLY | O_CREAT, 0644);
	if (ft_search(data, outfl) == 1)
		data->fdout = open(outfl, O_WRONLY | O_CREAT | O_APPEND, 0777);
	ft_temp(str, fdin);
	close(fdin);
	fdin = open(".tmp", O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (3);
} */

void	ft_temp(t_ms *ms)
{
	char	*str;
	char	*str2;
	int		i;

	i = 2;
	str = "";
	write(1, "heredoc> ", 9);
	str2 = get_next_line(0);
	while (ms->tokens->token[i] <= ' ')
		i++;
	ms->wanted = ft_strdup(&ms->tokens->token[i]);
	if (DEBUG)
		printf("wanted en heredoc es $%s$\n", ms->wanted);
	while (ft_strncmp(str2, ms->wanted, ft_strlen(str2) - 1))
	{
		write(1, "heredoc> ", 9);
		str = ft_strjoin(str, str2);
		str2 = get_next_line(0);
	}
	if (ms->wanted)
	{
		free(ms->wanted);
		ms->wanted = NULL;	
	}
	write(ms->fdin, str, ft_strlen(str));
	//dup2(ms->fdin, STDOUT_FILENO);
	//ft_printf("%s", str);
}

int	here_doc(t_ms *ms)
{
	ms->fdin = open(".tmp", O_WRONLY | O_CREAT, 0644);
	ft_temp(ms);
	close(ms->fdin);
	ms->fdin = open(".tmp", O_RDONLY);
	//close(ms->fdin);
	return (0);
}

int	ft_enter(t_ms *ms)
{
	int	i;
	int	fdin;
	t_token	*tok;

	tok = ms->tokens;
	i = 1;
	if (ms->tokens->type == 16)
	{
		here_doc(ms);
		return (1);
	}
	if (ms->tokens->type == 13)
	{
		while (ms->tokens->token[i] <= ' ')
			i++;
		ms->fdin = open(&ms->tokens->token[i], O_RDONLY);
		return (1);
	}
	while (tok->next && ms->tokens->type != 14)
		tok = tok->next;
	if (tok->type == 14)
	{
		while (tok->token[i] <= ' ')
			i++;
		ms->fdout = open(&tok->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		return (2);
	}
	return (0);
		//return (i = here_doc(argv[1], data, argv[argc - 1]));
/* 	else
	{
		if (ft_search(data, argv[argc - 1]) == 1)	//si no existe el ultimo argv lo crea y mete el resultado
			data->fdout = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (ft_search(data, argv[0]) == 1)			//si el primer argv no es un comando es un archivo y lo lee
		{	
			fdin = open(argv[0], O_RDONLY, 0777);
			if (fdin < 0)
			{
				ft_error(1);
				ft_allfree(data);
				exit(1);
			}
			dup2(fdin, STDIN_FILENO);
			return (i = 2);
		}
		return (i = 1);
	} */
}