/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:18:48 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/12 13:18:49 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	ft_pow(uintmax_t b, uintmax_t p)
{
	if (p == 0)
		return (1);
	return (b * ft_pow(b, p - 1));
}

void		ft_s_base(t_pf *s, uintmax_t n, char *base)
{
	uintmax_t	b;
	uintmax_t	p;
	uintmax_t	h;

	h = n;
	p = 1;
	b = ft_strlen(base);
	while (n / ft_pow(b, p - 1) >= b)
		p++;
	ft_manage_numb(s, p, n);
	if (s->prec == 0 && n == 0)
		return ;
	while (1)
	{
		if (!p)
			break ;
		ft_buf_add_numb(s, base[n / ft_pow(b, p - 1)]);
		n = n - n / ft_pow(b, p - 1) * ft_pow(b, p - 1);
		p--;
	}
}

uintmax_t	ft_get_uint(t_pf *s, va_list val)
{
	if (s->type != 'p' && s->type != 'U' && s->type != 'O')
	{
		if (s->size[0] == '\0')
			return (va_arg(val, unsigned int));
		else if (ft_strcmp(s->size, "hh") == 0)
			return ((unsigned char)va_arg(val, unsigned int));
		else if (ft_strcmp(s->size, "h") == 0)
			return ((unsigned short)va_arg(val, unsigned int));
	}
	return (va_arg(val, uintmax_t));
}

intmax_t	ft_get_int(t_pf *s, va_list val)
{
	intmax_t n;

	if (s->size[0] == 'l' || s->size[0] == 'j'
	|| s->size[0] == 'z' || s->type == 'D')
		n = va_arg(val, intmax_t);
	else if (s->size[0] == 'h' && s->size[1] == 'h')
		n = (signed char)va_arg(val, int);
	else if (s->size[0] == 'h')
		n = (short)va_arg(val, int);
	else
		n = va_arg(val, int);
	if (n < 0)
	{
		s->sign = '-';
		n *= -1;
	}
	return (n);
}

void		ft_numb(t_pf *s, va_list val)
{
	if (s->type == 'd' || s->type == 'D' || s->type == 'i')
		ft_s_base(s, ft_get_int(s, val), "0123456789");
	else if (s->type == 'X')
		ft_s_base(s, ft_get_uint(s, val), "0123456789ABCDEF");
	else if (s->type == 'p' || s->type == 'x')
		ft_s_base(s, ft_get_uint(s, val), "0123456789abcdef");
	else if (s->type == 'u' || s->type == 'U')
		ft_s_base(s, ft_get_uint(s, val), "0123456789");
	else if (s->type == 'O' || s->type == 'o')
		ft_s_base(s, ft_get_uint(s, val), "01234567");
}
