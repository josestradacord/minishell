/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestradac <jestradac@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:59 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/18 18:33:18 by jestradac        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_echo(t_ms *ms)
{
	int		index;
	
	//ms->command = ft_split(ms->tokens->token, ' ');
	ft_create_command(ms);
	index = 1;
	while (ms->command[index])
	{
		ft_putstr_fd(ms->command[index], STDOUT_FILENO);
		index++;
		if (ms->command[index])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_exit(t_ms *ms)
{
	int	index;

	index = 0;
	while (ms->command[index])
		index++;
	if (index == 1)
		ft_free(ms, EXIT_SUCCESS);
}
