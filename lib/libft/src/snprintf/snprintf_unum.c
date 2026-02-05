/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_unum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:10:34 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:31:16 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_unum(t_buffer *buffer, va_list args)
{
	char			*str_num;
	unsigned int	num;

	num = (unsigned int )va_arg(args, unsigned int);
	str_num = ft_utoa(num);
	if (!str_num)
		return (1);
	snprintf_putstr(buffer, str_num);
	free(str_num);
	return (0);
}
