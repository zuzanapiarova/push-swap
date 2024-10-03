/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:50:55 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/10/03 18:54:24 by zpiarova         ###   ########.fr       */
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
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	rr;
	int	rrr;
	int	count;
	int	rrcount;
	int	rrrcount;
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
	t_operation	*ch;
}				t_stack;

// MAIN
void	fill_a(t_stack *a, char *str);
void	fill_a_from_str(t_stack *a, char *str);

// algorithm
void	find_cheapest_operation(t_stack *a, t_stack *b);
void	set_insides(t_operation *c_o, t_operation *c_o_copy, t_stack *a);
void	fill_b(t_stack *a, t_stack *b);
void	back_to_a(t_stack *a, t_stack *b);
void	algorithm(t_stack *a, t_stack *b);

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

// utils
int		is_bigger_than_int(const char *num_str, int value);
int		is_only_spaces(char *str);
void	free_array(char **arr);

// stack utils i
t_node	*ft_stacknew(int value);
void	ft_stackadd_back(t_stack *stack, t_node *new_node);
t_node	*ft_stacklast(t_stack *s);
void	ft_stackclear(t_stack *s);
int		is_bigger_than_int(const char *num_str, int value);

// stack utils ii
int		has_duplicates(int value, t_stack *s);
bool	is_sorted(t_stack *a);
void	find_values(t_stack *s);
void	print_stack(t_stack *s);
void	index_stack(t_stack *s);

// algorithm utils i
int		calculate_rr(t_operation *op);
int		calculate_rrr(t_operation *op);
int		set_rr(t_operation *op, int ra, int rb, int rr);
int		set_rrr(t_operation *op, int rra, int rrb, int rrr);
void	do_r_or_rr(t_node *n, t_stack *s);

// algorithm utils ii
t_node	*find_predecessor(t_node *n, t_stack *s);
t_node	*find_successor(t_node *n, t_stack *s);
void	perform_operation(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);

#endif
