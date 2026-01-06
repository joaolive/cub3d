/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:12:13 by joaolive          #+#    #+#             */
/*   Updated: 2025/09/14 09:17:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	ft_count_words(char const *s, char c)
{
	int	is_new_word;
	int	count_words;
	int	i;

	is_new_word = 1;
	count_words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			is_new_word = 1;
		if (s[i] != c && is_new_word)
		{
			is_new_word = 0;
			count_words++;
		}
		i++;
	}
	return (count_words);
}

static char	*ft_get_next_word(const char **s_aux, char c)
{
	const char	*word_start;
	char		*word;
	size_t		len;

	while (**s_aux && **s_aux == c)
		(*s_aux)++;
	word_start = *s_aux;
	len = 0;
	while ((*s_aux)[len] && (*s_aux)[len] != c)
		len++;
	if (len == 0)
		return (NULL);
	word = ft_substr(word_start, 0, len);
	*s_aux += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	const char	*s_aux;
	size_t		total_words;
	size_t		i;

	if (!s)
		return (NULL);
	total_words = ft_count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (total_words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	s_aux = s;
	while (i < total_words)
	{
		arr[i] = ft_get_next_word(&s_aux, c);
		if (!arr[i])
		{
			ft_free_arr(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
