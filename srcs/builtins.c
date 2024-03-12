/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:47:59 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/11 16:58:31 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_nflag(char *str)
{
	int	index;

	index = 0;
	if (str[index++] != '-')
		return (FALSE);
	while (str[index])
	{
		if (str[index] != 'n')
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	ft_echo(t_ms *ms)
{
	int	index;
	int	n_flg;

	index = 1;
	n_flg = FALSE;
	if (ms->command[index])
		n_flg = ft_nflag(ms->command[index]);
	while (ms->command[index] && ft_nflag(ms->command[index]))
		index++;
	while (ms->command[index])
	{
		ft_putstr_fd(ms->command[index], STDOUT_FILENO);
		index++;
		if (ms->command[index])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n_flg)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	ft_isnbr(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	ft_exit_aux(t_ms *ms, char *cmd)
{
	if (ft_isnbr(cmd))
	{
		ft_putstr_fd(ms->command[0], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_free(ms, ft_atoi(cmd));
	}
	else
	{
		ft_putstr_fd("exit\nminishel: exit: ", STDOUT_FILENO);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
		ft_free(ms, 255);
	}
}

int	ft_exit(t_ms *ms)
{
	int	index;

	index = 0;
	while (ms->command[index])
		index++;
	if (index == 1)
	{
		ft_putstr_fd(ms->command[index - 1], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_free(ms, EXIT_SUCCESS);
	}
	else if (index == 2)
		ft_exit_aux(ms, ms->command[1]);
	else
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 0);
		ms->status = 1;
		return (1);
	}
	return (0);
}
