/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpeek_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:42:31 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:55 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the content of the last node in the list.
 *
 * @param lst List to access.
 * @return Pointer to the last node's content, or NULL if the list is empty.
 */
void	*ft_dlstpeek_back(t_dlist *lst)
{
	if (!lst || !lst->tail)
		return (NULL);
	return (lst->tail->content);
}
