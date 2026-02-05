/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_lhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:18:19 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/03 11:50:36 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_lhex(t_buffer *buffer, va_list args)
{
	unsigned int	num;

	num = (unsigned int)va_arg(args, unsigned int);
	return (snprintf_puthex(buffer, num, sizeof(num), 'x'));
}
