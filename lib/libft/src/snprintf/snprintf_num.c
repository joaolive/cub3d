/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:50:07 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:29:19 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_num(t_buffer *buffer, va_list args)
{
	char	*str_num;
	int		num;

	num = (int)va_arg(args, int);
	str_num = ft_itoa(num);
	if (!str_num)
		return (1);
	snprintf_putstr(buffer, str_num);
	free(str_num);
	return (0);
}
