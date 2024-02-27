/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:50 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/05 18:47:52 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_args(int n_arg)
{
	if (n_arg != 1)
		return (FALSE);
	return (TRUE);
}

void	ft_usage(void)
{
	printf("Usage ./minishell\n");
}

void	ft_welcome_msg(void)
{
	ft_putstr_fd("\033[32;1mW E L C O M E  T O  M I N I S H E L L\033[0m\n", STDOUT_FILENO);
}

void	ft_init_data(t_ms *ms, char **argv, char **envp)
{
	(void) argv;
	ms->tokens = NULL;
	ms->num_pipes = 0;
	ms->status = 0;
	ms->line = NULL;
	ms->rout = ft_routes(envp);
	ft_welcome_msg();
	ft_copy_envp(ms, envp);
	ft_copy_env2lst(ms, envp);
	ft_signals();
	ft_shlvlup(ms);
	//ft_set_signal(0);
}

int	ft_blank_line(char *line)
{
	size_t	len;
	size_t	index;

	len = ft_strlen(line);
	if (len == 0)
		return (TRUE);
	index = 0;
	while (line[index] && (line[index] == ' ' || line[index] == '\t'))
		index++;
	if (line[index] == '\0')
		return (TRUE);
	return (FALSE);
}

int	ft_check_quotes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '\"')
		{
			index++;
			while (line[index] && line[index] != '\"')
				index++;
			if (line[index] == '\0')
				return(ft_putstr_fd(SYNTAXQUOT, STDOUT_FILENO), FALSE);
		}
		else if (line[index] == '\'')
		{
			index++;
			while (line[index] && line[index] != '\'')
				index++;
			if (line[index] == '\0')
				return(ft_putstr_fd(SYNTAXQUOT, STDOUT_FILENO), FALSE);
		}
		index++;
	}
	return (TRUE);
}


int	ft_check_quotes_d(char *line)
{
	int	d_quot;
	int	s_quot;
	int	index;

	index = 0;
	d_quot = TRUE;
	s_quot = TRUE;
	while (line[index])
	{
		if (line[index] == '\"')
			if (d_quot)
				d_quot = FALSE;
			else
				d_quot = TRUE;
		else if (line[index] == '\'')
		{
			if (!d_quot)
				s_quot = TRUE;
			else
				s_quot = FALSE;
		}
		index++;
	}
	if (d_quot)
		return (TRUE);
	else
	{
		ft_putstr_fd(SYNTAXQUOT, STDOUT_FILENO);
		return (FALSE);
	}
}

int	ft_check_quotes_s(char *line)
{
	int	d_quot;
	int	s_quot;
	int	index;

	index = 0;
	d_quot = TRUE;
	s_quot = TRUE;
	while (line[index])
	{
		if (line[index] == '\'')
			if (s_quot)
				s_quot = FALSE;
			else
				s_quot = TRUE;
		else if (line[index] == '\"')
		{
			if (!s_quot)
				d_quot = TRUE;
			else
				d_quot = FALSE;
		}
		index++;
	}
	if (s_quot)
		return (TRUE);
	else
	{
		ft_putstr_fd(SYNTAXQUOT, STDOUT_FILENO);
		return (FALSE);
	}
}

int	ft_check_redir_i(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '<')
		{
			while (line[index] == ' ')
				index++;
			if (line[index] == '<')
			{
				ft_putstr_fd(SYNTAXIN_R, STDOUT_FILENO);
				return (FALSE);
			}
		}
		index++;
	}
	return (TRUE);
}

int	ft_check_redir_o(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '>')
		{
			while (line[index] == ' ')
				index++;
			if (line[index] == '>')
			{
				ft_putstr_fd(SYNTAXOU_R, STDOUT_FILENO);
				return (FALSE);
			}
		}
		index++;
	}
	return (TRUE);
}

int	ft_check_line(char *line)
{
	int	check;

	check = TRUE;
	check = check && ft_check_quotes(line);
	check = check && ft_check_redir_i(line);
	check = check && ft_check_redir_o(line);
	return (check);
}
