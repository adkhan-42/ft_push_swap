/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:36:27 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/20 18:06:05 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	set_current_pos(t_stack *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		stack->pos = i;
		stack = stack->next;
		i++;
	}
}

void	set_target_pos(t_stack **a, t_stack **b)
{
	t_stack	*temp_a;
	t_stack	*temp_b;
	long	best_match;

	temp_b = *b;
	while (temp_b)
	{
		best_match = LONG_MAX;
		temp_a = *a;
		while (temp_a)
		{
			if (temp_a->index > temp_b->index && temp_a->index < best_match)
			{
				best_match = temp_a->index;
				temp_b->target_pos = temp_a->pos;
			}
			temp_a = temp_a->next;
		}
		if (best_match == LONG_MAX)
			temp_b->target_pos = get_min_index_pos(*a);
		temp_b = temp_b->next;
	}
}

void	get_cost(t_stack **a, t_stack **b)
{
	t_stack	*tmp_b;
	int		len_a;
	int		len_b;

	tmp_b = *b;
	len_a = get_stack_size(*a);
	len_b = get_stack_size(*b);
	while (tmp_b)
	{
		tmp_b->cost_b = tmp_b->pos;
		if (tmp_b->pos > len_b / 2)
			tmp_b->cost_b = (len_b - tmp_b->pos) * -1;
		tmp_b->cost_a = tmp_b->target_pos;
		if (tmp_b->target_pos > len_a / 2)
			tmp_b->cost_a = (len_a - tmp_b->target_pos) * -1;
		tmp_b = tmp_b->next;
	}
}
