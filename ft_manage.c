/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 12:05:55 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/17 12:05:56 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_manage_str(t_pf *s)
{
	int c;
	int w;

	c = s->i;
	w = s->width;
	if (s->width != 0)
		while (w-- > 0)
		{
			if ((c + w) > BUFF_SIZE)
				ft_buf_print(s);
			if (s->flags & 4)
				s->buf[c++] = '0';
			else
				s->buf[c++] = ' ';
		}
}

void	ft_mng_nb3(t_pf *s, uintmax_t b, uintmax_t n)
{
	if ((s->flags & 8 && (n != 0 || ((s->type == 'o' || s->type == 'O')
	&& s->prec != -1))) || s->type == 'p')
	{
		if (s->type == 'o' || s->type == 'O')
		{
			ft_buf_add_numb(s, '0');
			s->width--;
			if (s->prec != -1 && s->prec != 0)
				s->prec--;
		}
		if (s->type == 'x' || s->type == 'X' || s->type == 'p')
			ft_buf_add_numb(s, '0');
		if (s->type == 'x' || s->type == 'p')
			ft_buf_add_numb(s, 'x');
		if (s->type == 'X')
			ft_buf_add_numb(s, 'X');
		if (s->type == 'x' || s->type == 'X' || s->type == 'p')
			s->width -= 2;
		if (s->type == 'o' || s->type == 'O')
			s->width -= 1;
	}
	while ((s->flags & 4 && s->width-- > (int)b && s->prec == -1 &&
	!(s->flags & 2)) || (s->prec != -1 && (uintmax_t)s->prec > b++))
		ft_buf_add_numb(s, '0');
}

void	ft_mng_nb2(t_pf *s, uintmax_t b, uintmax_t n)
{
	if (s->flags & 16 && (s->type == 'd' || s->type == 'D' || s->type == 'i')
	&& !(s->flags & 1) && (s->sign != '-'))
	{
		s->width--;
		ft_buf_add_numb(s, ' ');
	}
	if ((s->type == 'd' || s->type == 'D' || s->type == 'i') && (s->sign == '-'
	|| (s->flags & 1)))
		ft_buf_add_numb(s, s->sign);
	ft_mng_nb3(s, b, n);
}

void	ft_mng_nb1(t_pf *s, uintmax_t b, uintmax_t n)
{
	int o;

	o = 0;
	if ((s->type == 'd' || s->type == 'D' || s->type == 'i') &&
	(s->sign == '-' || (s->flags & 1)))
		s->width -= 1;
	if ((!(s->flags & 2)) && s->width != 0 &&
	(!(s->flags & 4) || s->prec != -1))
	{
		o = s->width - b;
		if (s->flags & 16)
			o--;
		if (b == 10 && s->i > 0 && s->buf[s->i - 1] != '-' && (s->flags & 1))
			o--;
		if (s->flags & 8 && (s->type == 'o' || s->type == 'O'))
			o--;
		if ((s->flags & 8 && (s->type == 'x' || s->type == 'X'))
		|| s->type == 'p')
			o -= 2;
		if (s->prec != -1 && s->prec > (int)b)
			o -= s->prec - b;
		if (o > 0)
			s->i += o;
	}
	ft_mng_nb2(s, b, n);
}

void	ft_manage_numb(t_pf *s, uintmax_t b, uintmax_t n)
{
	int c;
	int w;

	c = s->i;
	w = s->width;
	if (s->width != 0)
		while (w-- > 0)
		{
			if ((c + w) > BUFF_SIZE)
				ft_buf_print(s);
			s->buf[c++] = ' ';
		}
	ft_mng_nb1(s, b, n);
}
