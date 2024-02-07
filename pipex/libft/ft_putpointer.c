/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:01:05 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/10/20 20:03:57 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpointer(unsigned long i, char *base)
{
	unsigned long	n;
	int				res;

	n = i;
	res = 0;
	if (n >= 16)
		res += ft_putpointer(n / 16, base);
	if (res == 0)
	{
		write(1, "0x", 2);
		res += 2;
	}
	write(1, &base[n % 16], 1);
	res++;
	return (res);
}
