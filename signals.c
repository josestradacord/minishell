/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:26:38 by joestrad          #+#    #+#             */
/*   Updated: 2024/02/27 19:20:43 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_controlc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signals(void)
{
	struct sigaction	ign_sig;
	struct termios		term;

	ign_sig.sa_handler = SIG_IGN;
	sigemptyset(&ign_sig.sa_mask);
	ign_sig.sa_flags = 0;
	sigaction(SIGQUIT, &ign_sig, NULL);
	signal(SIGINT, ft_signal_controlc);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

void	ft_control_d(void)
{
	rl_on_new_line();
	ft_putstr_fd("exit\n", 0);
	exit(0);
}

// ANTES
//static int	*act_signal;

/*int	ft_get_signal(void)
{
	int	get_sig;

	get_sig = *act_signal;
	return (get_sig);
}*/
/*void	ft_set_signal(int s)
{
	static int	active_signal;

	active_signal = s;
	act_signal = &active_signal;
}*/