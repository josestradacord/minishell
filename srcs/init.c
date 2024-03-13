/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:50:28 by gpaez-ga          #+#    #+#             */
/*   Updated: 2024/03/13 19:10:50 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	ft_putstr_fd("\033[32;1mWELCOME  TO  MINISHELL\033[0m\n", STDOUT_FILENO);
}

void	ft_init_data(t_ms *ms, char **argv, char **envp)
{
	(void) argv;
	ms->tokens = NULL;
	ms->num_pipes = 0;
	ms->status = 0;
	ms->line = NULL;
	ms->fdin = 0;
	ms->fdout = 0;
	ms->rout = ft_routes(envp);
	ft_copy_envp(ms, envp);
	ft_copy_env2lst(ms, envp);
	ft_signals();
	ft_shlvlup(ms);
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
