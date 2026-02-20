/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adkhan <adkhan@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:34:54 by adkhan            #+#    #+#             */
/*   Updated: 2026/02/20 18:04:22 by adkhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// linked list
typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

t_stack				*stack_new(int value, int index);
void				stack_add_back(t_stack **stack, t_stack *new_node);
void				free_stack(t_stack **stack);
int					get_stack_size(t_stack *stack);

// input
int					is_valid_syntax(char *str);
long				ft_atol(const char *str);
char				**parse_input(int ac, char **av);
int					arr_len(char **arr);
int					*get_numbers(char **str_nums);
void				pre_sort_int_arr(int *arr, int size);
int					check_duplicates(int *arr, int size);
char				**free_array(char **arr, int count);

// init stack a
void				init_stack_a(t_stack **a, int ac, char **av);

// swap
void				swap(t_stack **stack);
void				sa(t_stack **a);
void				sb(t_stack **b);
void				ss(t_stack **a, t_stack **b);

// push
void				push(t_stack **src, t_stack **dest);
void				pa(t_stack **a, t_stack **b);
void				pb(t_stack **b, t_stack **a);

// rotate
void				rotate(t_stack **stack);
void				ra(t_stack **a);
void				rb(t_stack **b);
void				rr(t_stack **a, t_stack **b);

// reverse_rotate
void				reverse_rotate(t_stack **stack);
void				rra(t_stack **a);
void				rrb(t_stack **b);
void				rrr(t_stack **a, t_stack **b);

// sorting
void				sort_three(t_stack **a);
void				init_nodes(t_stack *a, t_stack *b);
int					get_lowest_index_pos(t_stack **a);
int					is_sorted(t_stack *stack);
void				sort(t_stack **a, t_stack **b);
t_stack				*get_min_node(t_stack *stack);
void				move_to_top(t_stack **stack, t_stack *target_node,
						char stack_name);
void				push_init(t_stack **a, t_stack **b);
void				sort(t_stack **a, t_stack **b);
void				min_on_top(t_stack **a);

// Turk_sort_utils
void				set_current_pos(t_stack *stack);
int					get_min_index_pos(t_stack *a);
void				get_cost(t_stack **a, t_stack **b);
void				set_target_pos(t_stack **a, t_stack **b);

// do_move
void				do_move(t_stack **a, t_stack **b);

// finder_utils
t_stack				*get_cheapest_cost(t_stack *b);

// error
void				exit_error(t_stack **a, char **str_nums);

#endif