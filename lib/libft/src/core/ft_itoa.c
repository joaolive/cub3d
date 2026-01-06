/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:23:13 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill_number_str(char *s, int size, int n)
{
	long	n_long;
	int		i;

	n_long = (long) n;
	i = size - 2;
	if (n_long < 0)
	{
		n_long *= -1;
		s[0] = '-';
	}
	while (n_long > 0)
	{
		s[i] = (n_long % 10) + '0';
		n_long /= 10;
		i--;
	}
}

static int	ft_count_digits(int n)
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

char	*ft_itoa(int n)
{
	char	*s;
	int		size;

	if (n == 0)
		return (ft_strdup("0"));
	size = ft_count_digits(n) + 1;
	if (n < 0)
		size++;
	s = ft_calloc(size, sizeof(char));
	if (!s)
		return (NULL);
	ft_fill_number_str(s, size, n);
	return (s);
}
