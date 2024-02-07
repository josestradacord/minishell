/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:49:13 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/10/20 19:49:30 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hexa(unsigned int i, char *base)
{
	unsigned long	n;
	int				res;

	n = i;
	res = 0;
	if (n >= 16)
		res += ft_putnbr_hexa(n / 16, base);
	write(1, &base[n % 16], 1);
	res++;
	return (res);
}
