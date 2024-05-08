/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:45:27 by labderra          #+#    #+#             */
/*   Updated: 2024/05/07 22:45:27 by labderra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

static int	print_nbr(int n, int *i)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*i += 11;
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		*i = print_nbr(-n, i) + 1;
	}
	else if (n > 9)
	{
		*i = print_nbr(n / 10, i) + 1;
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n % 10 + '0';
		write(1, &c, 1);
		*i = *i + 1;
	}
	return (*i);
}

static int	print_unbr(unsigned int n, int *i)
{
	char	c;

	if (n > 9)
	{
		*i = print_unbr(n / 10, i) + 1;
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n % 10 + '0';
		write(1, &c, 1);
		*i = *i + 1;
	}
	return (*i);
}

static int	print_hex(unsigned int n, int *i, char h)
{
	char	c;

	if (n > 15)
	{
 		*i = print_hex(n / 16, i, h) + 1;
		n = n % 16;
		if (n < 10)
			c = n + '0';
		else
			c = n + h - 10;
		write(1, &c, 1);
	}
	else
	{
		n = n % 16;
		if (n < 10)
			c = n + '0';
		else
			c = n + h - 10;
		write(1, &c, 1);
		(*i)++;
	}
	return (*i);
}

static int	print_str(char *s, int i)
{
	int	cnt;

	cnt = 0;
	while (s[cnt])
	{
		write(1, &s[cnt++], 1);
		i++;
	}
	return (i);
}

static int	print_char(int c, int i)
{
	unsigned char	aux;

	aux = (unsigned char)c;
	write(1, &aux, 1);
	return (i + 1);
}

static int	print_token(char const *s, va_list ap, int i)
{
	if (*s == '%')
		i = print_char('%', i);
	else if (*s == 'c')
		i = print_char(va_arg(ap, int), i);
	else if (*s == 's')
		i = print_str(va_arg(ap, char *), i);
	else if (*s == 'i' || *s == 'd')
		i = print_nbr(va_arg(ap, int), &i);
	else if (*s == 'u')
		i = print_unbr((unsigned int)va_arg(ap, unsigned int), &i);
	else if (*s == 'x' || *s == 'X')
		i = print_hex(va_arg(ap, unsigned int), &i, *s - 23);
	else if (*s == 'p')
	{
		write(1, "0x", 2);
		i = print_hex(va_arg(ap, unsigned int), &i, 'a') + 2;
	}
	else
		return (-1);
	return (i);
}

int	ft_printf(char const *s, ...)
{
	int		i;
	va_list	ap;

	i = 0;
	va_start(ap, s);
	while (i >= 0 && *s)
	{
		if (*s != '%')
		{
			write(1, s++, 1);
			i++;
		}
		else
		{
			i = print_token(++s, ap, i);
			s++;
		}
	}
	va_end(ap);
	return (i);
}
