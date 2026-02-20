/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:35:07 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/18 19:40:39 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	*copy_array(int *source, int size)
{
	int	*dest;
	int	i;

	dest = malloc(size * sizeof(int));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}

static int	get_rank(int *sorted_arr, int target, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted_arr[i] == target)
			return (i);
		i++;
	}
	return (-1);
}

static int	*get_input_data(int ac, char **av, int *size)
{
	char	**str_nums;
	int		*raw_nums;

	str_nums = parse_input(ac, av);
	if (!str_nums)
		return (NULL);
	*size = arr_len(str_nums);
	raw_nums = get_numbers(str_nums);
	free_array(str_nums, *size);
	return (raw_nums);
}

static int	*create_sorted_check(int *raw, int size)
{
	int	*sorted;

	sorted = copy_array(raw, size);
	if (!sorted)
		return (NULL);
	pre_sort_int_arr(sorted, size);
	if (check_duplicates(sorted, size))
	{
		free(sorted);
		return (NULL);
	}
	return (sorted);
}

void	init_stack_a(t_stack **a, int ac, char **av)
{
	int	*raw;
	int	*sorted;
	int	size;
	int	i;

	raw = get_input_data(ac, av, &size);
	if (!raw)
		exit_error(NULL, NULL);
	sorted = create_sorted_check(raw, size);
	if (!sorted)
	{
		free(raw);
		exit_error(NULL, NULL);
	}
	i = 0;
	while (i < size)
	{
		stack_add_back(a, stack_new(raw[i], get_rank(sorted, raw[i], size)));
		i++;
	}
	free(raw);
	free(sorted);
}
