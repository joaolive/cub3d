/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htabinsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:22:17 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/28 09:06:21 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nextprime(size_t n)
{
	if (n <= 2)
		return (2);
	if (n % 2 == 0)
		n++;
	while (!ft_isprime(n))
		n += 2;
	return (n);
}

int	ft_htabinsert(t_htab *tab, const char *key, void *value)
{
	t_hnode	**indirect;
	t_hnode	*new_node;
	size_t	idx;

	if (!tab || !key)
		return (1);
	if (tab->count >= (tab->size * 3) / 4)
		if (ft_htabresize(tab, ft_nextprime(tab->size * 2)))
			return (1);
	idx = ft_djb2(key) % tab->size;
	indirect = &tab->buckets[idx];
	while (*indirect)
	{
		if (ft_strcmp((char *)(*indirect)->key, (char *)key) == 0)
			return (-1);
		indirect = &(*indirect)->next;
	}
	new_node = ft_hnodenew(key, value);
	if (!new_node)
		return (1);
	*indirect = new_node;
	tab->count++;
	return (0);
}
