/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:05:53 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:31:02 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_ptr(t_buffer *buffer, va_list args)
{
	unsigned long long	ptr;

	ptr = va_arg(args, unsigned long long);
	if (!ptr || ptr == 0)
	{
		snprintf_putstr(buffer, "(nil)");
		return (0);
	}
	snprintf_putstr(buffer, "0x");
	return (snprintf_puthex(buffer, ptr, sizeof(unsigned long long), 'x'));
}
