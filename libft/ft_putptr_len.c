/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:18:51 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printp_hexa(__UINTPTR_TYPE__ n, int *len)
{
	char	*hexa;

	hexa = HEXA_MIN;
	write(1, &hexa[n], 1);
	(*len)++;
}

static void	ft_puthexap_len(__UINTPTR_TYPE__ n, char c, int *len)
{
	if (n < 16)
		ft_printp_hexa(n, len);
	else
	{
		ft_puthexap_len(n / 16, c, len);
		ft_printp_hexa(n % 16, len);
	}
}

void	ft_putptr_len(__UINTPTR_TYPE__ p, int *len)
{
	write(1, "0x", 2);
	(*len) += 2;
	ft_puthexap_len(p, 'x', len);
}
