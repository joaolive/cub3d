/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:26:55 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Removes the first node from the list and returns its content.
 *
 * Detaches the head node, frees its memory,
 * and returns the stored content.
 *
 * @param lst Pointer to the list.
 * @return Content of the removed node, or NULL if the list is empty or invalid.
 */
void	*ft_dlstpop_front(t_dlist *lst)
{
	t_dnode	*node;
	void	*content;

	if (!lst || !lst->head)
		return (NULL);
	node = ft_dlstdetach_node(lst, lst->head);
	if (!node)
		return (NULL);
	content = node->content;
	free(node);
	return (content);
}
