/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:12:58 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbu_rec(unsigned int n, int *len)
{
	if (n > 9)
	{
		ft_printnbu_rec(n / 10, len);
		ft_putchar_len((n % 10) + 48, len);
	}
	else
		ft_putchar_len(n + 48, len);
}

void	ft_putnbru_len(unsigned int n, int *len)
{
	ft_printnbu_rec(n, len);
}
