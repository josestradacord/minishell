/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:09:39 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnb_rec(int n, int *len)
{
	if (n > 9)
	{
		ft_printnb_rec(n / 10, len);
		ft_putchar_len((n % 10) + 48, len);
	}
	else
		ft_putchar_len(n + 48, len);
}

void	ft_putnbr_len(int n, int *len)
{
	if (n < 0)
	{
		ft_putchar_len('-', len);
		if (n == MIN_INT)
		{
			ft_printnb_rec((-1) * (n / 10), len);
			ft_putchar_len((-1) * (n % 10) + 48, len);
		}
		else
			ft_printnb_rec((-1) * n, len);
	}
	else
		ft_printnb_rec(n, len);
}
