/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hnodedetach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:31:37 by joaolive          #+#    #+#             */
/*   Updated: 2026/01/27 17:53:02 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hnode	*ft_hnodedetach(t_hnode **node)
{
	t_hnode	*target;

	if (!node || !*node)
		return (NULL);
	target = *node;
	*node = target->next;
	target->next = NULL;
	return (target);
}
