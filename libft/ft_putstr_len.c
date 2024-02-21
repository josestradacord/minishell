/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:14:27 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_len(char *s, int *len)
{
	size_t	l;

	if (!s)
	{
		l = 6;
		write(1, "(null)", l);
	}
	else
	{
		l = ft_strlen(s);
		write(1, s, l);
	}
	(*len) += l;
}
