/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:53:52 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/17 19:41:19 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_pourcent(va_list va, char c, size_t *len)
{
	if (c == 'c')
		ft_putchar(va_arg(va, int), len);
	else if (c == 's')
		ft_putstr(va_arg(va, char *), len);
	else if (c == 'p')
		ft_putptr(va_arg(va, void *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(va, int), len);
	else if (c == 'u')
		ft_putuint(va_arg(va, unsigned int), len);
	else if (c == 'x')
		ft_puthex(va_arg(va, unsigned int), "0123456789abcdef", len);
	else if (c == 'X')
		ft_puthex(va_arg(va, unsigned int), "0123456789ABCDEF", len);
	else if (c == '%')
		ft_putchar('%', len);
}

int	ft_printf(const char *str, ...)
{
	va_list	va;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (!str)
		return (0);
	va_start(va, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			check_pourcent(va, str[i], &len);
		}
		else
			ft_putchar(str[i], &len);
		i++;
	}
	va_end(va);
	return (len);
}
