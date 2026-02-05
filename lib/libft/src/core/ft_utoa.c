/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:23:13 by joaolive          #+#    #+#             */
/*   Updated: 2026/02/03 14:33:32 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill_number_str(char *s, int size, unsigned int n)
{
	int		i;

	i = size - 2;
	while (n > 0)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

static int	ft_count_digits(unsigned int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_utoa(unsigned int n)
{
	char	*s;
	int		size;

	if (n == 0)
		return (ft_strdup("0"));
	size = ft_count_digits(n) + 1;
	s = ft_calloc(size, sizeof(char));
	if (!s)
		return (NULL);
	ft_fill_number_str(s, size, n);
	return (s);
}
