/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:16:50 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_hexa(unsigned int n, char c, int *len)
{
	char	*hexa;

	if (c == 'x')
		hexa = HEXA_MIN;
	else
		hexa = HEXA_MAY;
	write(1, &hexa[n], 1);
	(*len)++;
}

void	ft_puthexa_len(unsigned int n, char c, int *len)
{
	if (n < 16)
		ft_print_hexa(n, c, len);
	else
	{
		ft_puthexa_len(n / 16, c, len);
		ft_print_hexa(n % 16, c, len);
	}
}
