/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:02:04 by ebansse           #+#    #+#             */
/*   Updated: 2024/11/17 19:36:10 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

char	*ft_nbr_base(unsigned long long n, char *base);
void	ft_putchar(unsigned char c, size_t *len);
void	ft_putstr(char *s, size_t *len);
void	ft_putnbr(int nb, size_t *len);
void	ft_putuint(unsigned int num, size_t *len);
void	ft_putptr(void *ptr, size_t *len);
void	ft_puthex(unsigned int num, char *base, size_t *len);
int		ft_printf(const char *str, ...);

#endif