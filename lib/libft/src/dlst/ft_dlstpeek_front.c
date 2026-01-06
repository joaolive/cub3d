/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpeek_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:32:15 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the content of the first node in the list.
 *
 * @param lst List to access.
 * @return Pointer to the first node's content, or NULL if the list is empty.
 */
void	*ft_dlstpeek_front(t_dlist *lst)
{
	if (!lst || !lst->head)
		return (NULL);
	return (lst->head->content);
}
