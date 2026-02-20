/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:25:35 by adkhan            #+#    #+#             */
/*   Updated: 2025/11/05 14:10:45 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_set(const char *set, char *char_arr)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (char_arr[(int)set[i]] == 0)
			char_arr[(int)set[i]] = 1;
		i++;
	}
}

static size_t	find_start(const char *s1, char *char_arr)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (char_arr[(int)s1[i]] == 1)
			i++;
		else
			break ;
	}
	return (i);
}

static size_t	find_end(const char *s1, char *char_arr)
{
	int	i;

	i = ft_strlen(s1);
	i--;
	while (i > 0)
	{
		if (char_arr[(int)s1[i]] == 1)
			i--;
		else
			break ;
	}
	return (i + 1);
}

static char	*trimmed_str(const char *s1, size_t start, size_t len)
{
	char	*res;

	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (len == 0)
		res[0] = '\0';
	else
		ft_strlcpy(res, (s1 + start), (len + 1));
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;
	size_t	len;
	char	char_arr[128];

	ft_memset(char_arr, 0, sizeof(char_arr));
	if (!s1 || !set)
		return (NULL);
	set_set(set, char_arr);
	start = find_start(s1, char_arr);
	end = find_end(s1, char_arr);
	if (start < end)
	{
		len = end - start;
		res = trimmed_str(s1, start, len);
	}
	else
	{
		len = 0;
		res = trimmed_str(s1, start, len);
	}
	return (res);
}
