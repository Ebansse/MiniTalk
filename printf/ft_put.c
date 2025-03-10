/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:50:00 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/21 15:58:00 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(unsigned char c, size_t *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr(char *s, size_t *len)
{
	int	i;

	i = -1;
	if (!s)
		s = "(null)";
	while (s[++i])
		ft_putchar(s[i], len);
}

void	ft_putnbr(int num, size_t *len)
{
	if (num == -2147483648)
	{
		ft_putnbr((num / 10), len);
		ft_putchar('8', len);
	}
	else if (num < 0)
	{
		ft_putchar('-', len);
		ft_putnbr(-num, len);
	}
	else
	{
		if (num > 9)
			ft_putnbr((num / 10), len);
		ft_putchar(('0' + num % 10), len);
	}
}

void	ft_putuint(unsigned int num, size_t *len)
{
	char	*str;

	str = ft_nbr_base(num, "0123456789");
	ft_putstr(str, len);
	free(str);
}

void	ft_putptr(void *ptr, size_t *len)
{
	unsigned long	ptr_adresse;
	char			*str;

	ptr_adresse = (unsigned long)ptr;
	if (!ptr)
	{
		ft_putstr("(nil)", len);
		return ;
	}
	str = ft_nbr_base(ptr_adresse, "0123456789abcdef");
	ft_putstr("0x", len);
	ft_putstr(str, len);
	free(str);
}
