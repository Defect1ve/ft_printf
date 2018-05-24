/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:22:46 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/03 15:22:47 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_unicode(t_pf *s, int uni)
{
	unsigned char mass[4];

	ft_bzero(mass, 4);
	if (uni < 256)
		mass[0] = uni;
	else if (uni < 2048)
	{
		mass[1] = 128 | (uni % 64);
		mass[0] = 192 | (uni / 64);
	}
	else if (uni < 65536)
	{
		mass[2] = 128 | (uni % 64);
		mass[1] = 128 | (uni % 4096 / 64);
		mass[0] = 224 | (uni / 4096);
	}
	else if (uni < 1114113)
	{
		mass[3] = 128 | (uni % 64);
		mass[2] = 128 | (uni % 4096 / 64);
		mass[1] = 128 | (uni % 524287 / 4096);
		mass[0] = 240 | (uni / 524287);
	}
	if ((int)ft_strlen((char *)mass) <= s->prec)
		ft_buf_add_str(s, mass);
}

int				ft_str_len(int *c, t_pf *s)
{
	int sum;

	sum = 0;
	while (c && *c)
	{
		if (*c < 256 && (sum + 1 <= s->prec || s->prec == -1))
			sum += 1;
		else if (*c < 2048 && (sum + 2 <= s->prec || s->prec == -1))
			sum += 2;
		else if (*c < 65536 && (sum + 3 <= s->prec || s->prec == -1))
			sum += 3;
		else if (*c < 1114113 && (sum + 4 <= s->prec || s->prec == -1))
			sum += 4;
		else
			break ;
		c++;
	}
	return (sum);
}

void			ft_long_string(t_pf *s, va_list val)
{
	wchar_t			*c;
	size_t			len;

	c = va_arg(val, wchar_t *);
	if (!c)
	{
		s->prec = 6;
		ft_buf_add_str(s, NULL);
		return ;
	}
	len = ft_str_len(c, s);
	if (s->prec == -1 && c)
		s->prec = len;
	if ((!(s->flags & 2)) && s->width > s->prec && s->prec > (int)len)
		s->i += s->width - len;
	else if ((!(s->flags & 2)) && s->width > s->prec)
		s->i += s->width - s->prec;
	while (c && *c && s->prec > 0)
		ft_unicode(s, *c++);
}

void			ft_string(t_pf *s, va_list val)
{
	unsigned char	*str;
	size_t			len;

	ft_manage_str(s);
	if (s->type == 'S' || (s->type == 's' && s->size[0] == 'l'))
		ft_long_string(s, val);
	else if (s->type == 's')
	{
		str = va_arg(val, unsigned char *);
		if (str)
			len = ft_strlen((char *)str);
		if (s->prec == -1 && str)
			s->prec = len;
		if (s->prec == -1 && !str)
			s->prec = 6;
		if (!(s->flags & 2) && str && s->prec > (int)len && s->width > (int)len)
			s->i += s->width - len;
		else if (!(s->flags & 2) && s->width > s->prec)
			s->i += s->width - s->prec;
		ft_buf_add_str(s, str);
	}
}

void			ft_char(t_pf *s, va_list val)
{
	wchar_t			c;
	int				len;

	ft_manage_str(s);
	c = va_arg(val, wchar_t);
	if (s->type == 'C' || (s->type == 'c' && s->size[0] == 'l'))
	{
		len = ft_str_len(&c, s);
		if (s->prec == -1)
			s->prec = len;
		if (!(s->flags & 2) && s->width > len)
			s->i += s->width - s->prec;
		if (!c)
			s->buf[s->i++] = c;
		else
			ft_unicode(s, c);
	}
	else if (s->type == 'c')
	{
		if (s->prec == -1 || s->prec == 0)
			s->prec = 1;
		if (!(s->flags & 2) && s->width > 1)
			s->i += s->width - s->prec;
		s->buf[s->i++] = c;
	}
}
