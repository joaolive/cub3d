/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstget_node_at.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:55:35 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Retrieves the node at a given index in the list.
 *
 * Efficiently traverses from the head or tail depending on the index position.
 *
 * @param lst Pointer to the list.
 * @param index index Position of the node to retrieve (0-based).
 * @return Pointer to the node at the given index,
 * or NULL if index is out of bounds or list is NULL.
 */
t_dnode	*ft_dlstget_node_at(t_dlist *lst, size_t index)
{
	t_dnode	*current;
	size_t	i;

	if (!lst || index >= lst->size)
		return (NULL);
	if (index < lst->size / 2)
	{
		current = lst->head;
		i = 0;
		while (i++ < index)
			current = current->next;
	}
	else
	{
		current = lst->tail;
		i = lst->size - 1;
		while (i-- > index)
			current = current->prev;
	}
	return (current);
}
