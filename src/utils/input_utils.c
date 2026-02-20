/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:35:17 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:45:56 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

char	**free_array(char **arr, int count)
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

char	**parse_input(int ac, char **av)
{
	int		i;
	char	**result;
	int		j;

	i = 0;
	if (ac == 2)
		return (ft_split(av[1], ' '));
	i = 1;
	result = malloc(ac * sizeof(char *));
	if (!result)
		return (NULL);
	j = 0;
	while (i < ac)
	{
		result[j] = ft_strdup(av[i]);
		if (result[j] == NULL)
		{
			free_array(result, j);
			return (NULL);
		}
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	*get_numbers(char **str_nums)
{
	int		size;
	int		i;
	int		*num;
	long	number;

	i = 0;
	size = arr_len(str_nums);
	num = malloc(size * sizeof(int));
	if (!num)
		return (NULL);
	while (str_nums[i])
	{
		if (!(is_valid_syntax(str_nums[i])))
			return (free(num), NULL);
		number = ft_atol(str_nums[i]);
		if (number > INT_MAX || number < INT_MIN)
			return (free(num), NULL);
		else
			num[i] = (int)number;
		i++;
	}
	return (num);
}

void	pre_sort_int_arr(int *arr, int size)
{
	int	i;
	int	temp;
	int	min_index;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		min_index = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min_index])
				min_index = j;
			j++;
		}
		temp = arr[min_index];
		arr[min_index] = arr[i];
		arr[i] = temp;
		i++;
	}
}
