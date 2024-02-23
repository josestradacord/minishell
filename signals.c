/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:26:38 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/23 19:50:13 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	*act_signal;

/*int	ft_get_signal(void)
{
	int	get_sig;

	get_sig = *act_signal;
	return (get_sig);
}*/

void	ft_signal_manager(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		//rl_on_new_line();
		//if (!ft_get_signal())
		//	rl_redisplay();
	}
}

void	ft_signals(void)
{
	struct sigaction	ign_sig;

	ign_sig.sa_handler = SIG_IGN;
	sigemptyset(&ign_sig.sa_mask);
	ign_sig.sa_flags = 0;
	sigaction(SIGQUIT, &ign_sig, NULL);
	signal(SIGINT, ft_signal_manager);
}

/*void	ft_set_signal(int s)
{
	static int	active_signal;

	active_signal = s;
	act_signal = &active_signal;
}*/
