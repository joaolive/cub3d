/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstget_node_index.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:12:28 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_dlstget_node_index(t_dlist *lst, t_dnode *node)
{
	t_dnode	*current;
	ssize_t	i;

	if (!lst || !lst->head || !node)
		return (-1);
	current = lst->head;
	i = 0;
	while (current)
	{
		if (current == node)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}
