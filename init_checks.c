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
	ft_putstr_fd("\033[32;1mW E L C O M E  T O  M I N I S H E L L\n\033[0m", STDOUT_FILENO);
}

void	ft_init_data(t_ms *ms, char **argv, char **envp)
{
	(void) argv;
	ms->tokens = NULL;
	ms->num_pipes = 0;
	ms->status = 0;
	ms->line = NULL;
	ms->wanted = NULL;
	ms->rout = ft_routes(envp);
	ft_welcome_msg();
	ft_copy_envp(ms, envp);
	ft_copy_env2lst(ms, envp);
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