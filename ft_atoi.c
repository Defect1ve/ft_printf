/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 20:36:13 by ikotvits          #+#    #+#             */
/*   Updated: 2018/03/20 20:36:25 by ikotvits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	help(const char *str, int i)
{
	int k;

	k = i;
	while (*(str + k) != '\0')
		if (!(*(str + k++) >= '0' && *(str + k++) <= '9'))
			return (1);
	if (((ft_strlen(str + i) == 19 &&
	ft_strcmp("9223372036854775806", str + i) < 0)
	|| ft_strlen(str + i) > 19) && str[i - 1] != '-')
		return (-1);
	else if (((ft_strlen(str + i) == 19 &&
	ft_strcmp("9223372036854775807", str + i) < 0) || ft_strlen(str + i) > 19))
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	int i;
	int nb;
	int k;

	k = 0;
	i = 0;
	nb = 0;
	if (!*str)
		return (0);
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\t'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		k = i++;
	if (help(str, i) == -1 || help(str, i) == 0)
		return (help(str, i));
	while (str[i] > 47 && str[i] < 58)
		nb = nb * 10 + str[i++] - 48;
	if (str[k] == 45)
		nb *= -1;
	return (nb);
}
