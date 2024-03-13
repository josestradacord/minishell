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

#include "../include/minishell.h"

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
				return (ft_putstr_fd(SYNTAXQUOT, STDOUT_FILENO), FALSE);
		}
		else if (line[index] == '\'')
		{
			index++;
			while (line[index] && line[index] != '\'')
				index++;
			if (line[index] == '\0')
				return (ft_putstr_fd(SYNTAXQUOT, STDOUT_FILENO), FALSE);
		}
		index++;
	}
	return (TRUE);
}

int	ft_check_redir_i(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '<')
		{
			index++;
			if (line[index] == '<')
				index++;
			while (line[index] && line[index] == ' ')
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
			index++;
			if (line[index] == '>')
				index++;
			while (line[index] && line[index] == ' ')
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

int	ft_check_pipes(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '|')
		{
			index++;
			while (line[index] && line[index] == ' ')
				index++;
			if (line[index] == '|')
			{
				ft_putstr_fd(SYNTAXPIPE, STDOUT_FILENO);
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
	if (!ft_strnstr(line, "echo", ft_strlen(line)))
	{
		check = check && ft_check_redir_i(line);
		check = check && ft_check_redir_o(line);
	}
	check = check && ft_check_pipes(line);
	return (check);
}
