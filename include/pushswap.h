/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:50:55 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/09/30 23:44:23 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

//  read, write, malloc, free, exit
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h" // do not forget to include the library header here

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	int				i;
}					t_node;

typedef struct s_operation
{
	int ra;
	int rb;
	int rra;
	int rrb;
	int rr;
	int rrr;
	int count;
	int rrcount;
	int rrrcount;
}			t_operation;

typedef struct s_stack
{
	t_node		*head;
	int			size;
	char		*name;
	t_node		*first;
	t_node		*last;
	t_node		*min;
	t_node		*max;
	t_operation	*cheapest_o;
}				t_stack;

// MAIN
void	init_stacks(t_stack *a, t_stack *b);
void	fill_a(t_stack *a, char *val);
void	fill_a_from_str(t_stack *a, char *str);
// and main

// algorithm
void	algorithm(t_stack *a, t_stack *b);
void	fill_b(t_stack *a, t_stack *b);
void	back_to_a(t_stack *a, t_stack *b);
void set_insides(t_operation *c_o, t_operation *c_o_copy, t_stack *a);

// functions
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

// upgraded libft functions
t_node	*ft_stacknew(int value);
void	ft_stackadd_back(t_stack *stack, t_node *new_node);
t_node	*ft_stacklast(t_stack *s);
void	index_stack(t_stack *s);
void	ft_stackclear(t_stack *s);
void	print_stack(t_stack *s);

// utils
void	check_duplicates(int value, t_stack *s);
bool	is_sorted(t_stack *a);
void	find_values(t_stack *s);
void	sort_three(t_stack *a);
void do_r_or_rr(t_node *n, t_stack *s);
int calculate_rr(t_operation *op);
int calculate_rrr(t_operation *op);
t_node	*find_predecessor(t_node *n, t_stack *s);
t_node	*find_successor(t_node *n, t_stack *s);

#endif
