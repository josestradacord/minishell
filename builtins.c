/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:59 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/12 20:34:40 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_echo(t_ms *ms)
{
	int		index;
	
	ms->command = ft_split(ms->tokens->token, ' ');
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

/*int	ft_exit(t_ms *ms)
{
	(void)	*ms;
	return (FALSE);
}
*/
