/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpush_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:27:18 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds a new node with the given content at the end of the list.
 *
 * @param lst List to modify.
 * @param content Content to store in the new node.
 * @return 1 on success, 0 on error.
 */
int	ft_dlstpush_back(t_dlist *lst, void *content)
{
	t_dnode	*node;

	if (!lst)
		return (0);
	node = ft_dlstnew(content);
	if (!node)
		return (0);
	return (ft_dlstpush_node_back(lst, node));
}
