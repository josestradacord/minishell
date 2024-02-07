/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:50:40 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/10/20 19:50:57 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u(unsigned int nbr, char *base)
{
	long	n;
	int		res;

	n = nbr;
	res = 0;
	if (n >= 10)
		res += ft_putnbr(n / 10, base);
	write(1, &base[n % 10], 1);
	res++;
	return (res);
}
