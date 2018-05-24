/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:59:07 by ikotvits          #+#    #+#             */
/*   Updated: 2018/05/02 16:59:08 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"
# define BUFF_SIZE 100
# define N_STR "(null)"

typedef	struct	s_pf
{
	short	flags;
	int		prec;
	int		width;
	char	type;
	char	size[2];
	char	buf[BUFF_SIZE];
	int		i;
	int		sum;
	char	sign;
}				t_pf;

int				ft_printf(const char *format, ...);
void			ft_string(t_pf *s, va_list val);
void			ft_char(t_pf *s, va_list val);
void			ft_numb(t_pf *s, va_list val);
void			ft_buf_print(t_pf *s);
void			ft_manage_str(t_pf *s);
void			ft_buf_add_str(t_pf *s, unsigned char *str);
void			ft_buf_add_numb(t_pf *s, unsigned char symbol);
void			ft_unicode(t_pf *s, int uni);
void			ft_manage_numb(t_pf *s, uintmax_t b, uintmax_t n);

#endif
