/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpeek_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:53:43 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the content of the node at the specified index.
 *
 * @param lst List to access.
 * @param index Index of the node (0-based).
 * @return Pointer to the node's content, or NULL if index is out of bounds.
 */
void	*ft_dlstpeek_at(t_dlist *lst, size_t index)
{
	if (!lst || index >= lst->size)
		return (NULL);
	return (ft_dlstget_node_at(lst, index)->content);
}
