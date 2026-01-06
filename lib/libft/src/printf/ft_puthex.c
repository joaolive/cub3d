/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:00:49 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:18:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long long num, size_t size_in_bytes, char specifier)
{
	unsigned long long			digit;
	char						*hex_chars;
	int							started;
	int							i;
	int							count;

	if (specifier == 'x')
		hex_chars = "0123456789abcdef";
	else
		hex_chars = "0123456789ABCDEF";
	started = 0;
	i = (size_in_bytes * 2) - 1;
	count = 0;
	while (i >= 0)
	{
		digit = (num >> (i * 4)) & 0xF;
		if (digit != 0 || started || i == 0)
		{
			ft_putchar_fd(hex_chars[digit], 1);
			started = 1;
			count++;
		}
		i--;
	}
	return (count);
}
