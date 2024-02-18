/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joestrad <joestrad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:14:58 by joestrad          #+#    #+#             */
/*   Updated: 2023/12/01 19:21:38 by joestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_treat_format(va_list args, char const *str, int *i, int *l)
{
	if (str[*i] == '%')
		ft_putchar_len(str[*i], l);
	if (str[*i] == 'c')
		ft_putchar_len((char) va_arg(args, int), l);
	if (str[*i] == 'd' || str[*i] == 'i')
		ft_putnbr_len(va_arg(args, int), l);
	if (str[*i] == 's')
		ft_putstr_len(va_arg(args, char *), l);
	if (str[*i] == 'u')
		ft_putnbru_len(va_arg(args, unsigned int), l);
	if (str[*i] == 'x' || str[*i] == 'X')
		ft_puthexa_len(va_arg(args, unsigned int), str[*i], l);
	if (str[*i] == 'p')
		ft_putptr_len(va_arg(args, __UINTPTR_TYPE__), l);
}

int	ft_printf(char const *str, ...)
{
	int		index;
	int		len;
	va_list	args;

	index = 0;
	len = 0;
	va_start(args, str);
	while (str[index] != '\0')
	{
		if (str[index] == '%')
		{
			index++;
			ft_treat_format(args, str, &index, &len);
			index++;
		}
		else
		{
			ft_putchar_len(str[index], &len);
			index++;
		}
	}
	va_end(args);
	return (len);
}
