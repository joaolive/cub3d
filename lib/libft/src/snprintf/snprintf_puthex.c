/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snprintf_puthex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:00:49 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/04 11:29:04 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	snprintf_puthex(t_buffer *buffer, unsigned long long num,
	size_t size_in_bytes, char specifier)
{
	unsigned long long			digit;
	char						*hex_chars;
	int							started;
	int							i;

	if (specifier == 'x')
		hex_chars = "0123456789abcdef";
	else
		hex_chars = "0123456789ABCDEF";
	started = 0;
	i = (size_in_bytes * 2) - 1;
	while (i >= 0)
	{
		digit = (num >> (i * 4)) & 0xF;
		if (digit != 0 || started || i == 0)
		{
			snprintf_putchar(buffer, hex_chars[digit]);
			started = 1;
		}
		i--;
	}
	return (0);
}
