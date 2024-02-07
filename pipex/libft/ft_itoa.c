/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:36:18 by gpaez-ga          #+#    #+#             */
/*   Updated: 2023/10/20 19:58:45 by gpaez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ext(int num)
{
	int		i;
	long	nb;

	nb = num;
	i = 0;
	if (nb == 0)
		i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static char	*ft_putnbr_itoa(char *str, int i, int num)
{
	long	nb;

	nb = num;
	if (nb < 0)
		nb = -nb;
	str[i] = (nb % 10) + '0';
	if (i > 0)
		ft_putnbr_itoa(str, i - 1, nb / 10);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		j;
	long	i;

	i = n;
	j = ft_ext(i);
	res = malloc(sizeof(char) * (j + 1));
	if (res == NULL)
		return (NULL);
	ft_putnbr_itoa(res, j - 1, n);
	res[j] = '\0';
	if (i < 0)
		res[0] = '-';
	return (res);
}
