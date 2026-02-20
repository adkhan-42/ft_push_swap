/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:22:48 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 16:08:44 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	state;
	int	i;
	int	wcount;

	state = 0;
	i = 0;
	wcount = 0;
	while (s[i])
	{
		if (s[i] != c && state == 0)
		{
			wcount++;
			state = 1;
		}
		else if (s[i] == c)
			state = 0;
		i++;
	}
	return (wcount);
}

static char	**free_array(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**fill_array(char **res, const char *s, char c, int wcount)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < wcount)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		res[j] = ft_substr(s, start, (i - start));
		if (!res[j])
		{
			free_array(res, j);
			return (NULL);
		}
		j++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = word_count(s, c);
	res = malloc((wcount + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	fill_array(res, s, c, wcount);
	return (res);
}
