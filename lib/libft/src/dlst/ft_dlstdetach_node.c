/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdetach_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:45:07 by joaolive          #+#    #+#             */
/*   Updated: 2025/08/21 15:16:17 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Detaches a specific node from the list.
 *
 * Updates adjacent nodes and list pointers, decreases list size,
 * and returns the detached node with next and prev set to NULL.
 *
 * @param lst Pointer to the list.
 * @param node Pointer to the node to detach.
 * @return The detached node, or NULL if lst or node is NULL.
 */
t_dnode	*ft_dlstdetach_node(t_dlist *lst, t_dnode *node)
{
	if (!lst || !node)
		return (NULL);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (lst->head == node)
		lst->head = node->next;
	if (lst->tail == node)
		lst->tail = node->prev;
	lst->size--;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
