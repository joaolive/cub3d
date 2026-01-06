/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:50:07 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:18:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_print_num(va_list args)
{
	int	num;
	int	size;

	num = (int)va_arg(args, int);
	ft_putnbr_fd(num, 1);
	size = ft_count_digits(num);
	if (num < 0)
		size++;
	return (size);
}
