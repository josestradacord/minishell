/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:46:57 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/10/20 19:47:13 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int i, char *base)
{
	long	n;
	int		res;

	n = i;
	res = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		res++;
	}
	if (n >= 10)
		res += ft_putnbr(n / 10, base);
	write(1, &base[n % 10], 1);
	res++;
	return (res);
}
