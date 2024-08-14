/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:50:55 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/12 18:48:42 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

#define ERROR "Error\n"

//  read, write, malloc, free, exit
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <libc.h>

typedef struct s_node
{
	int		value;
	struct s_node	*next;

}				t_node;

typedef struct s_stack
{
	t_node	*head;
	int		size;
}				t_stack;

// main
void fill_a(t_stack *a, char *val);

// functions
void sa(t_stack *a);
void sb(t_stack *b);
void ss(t_stack *a, t_stack *b);
void pa(t_stack *a,t_stack *b);
void pb(t_stack *a, t_stack *b);
void ra(t_stack *a);
void rb(t_stack *b);
void rr(t_stack *a, t_stack *b);
void rra(t_stack *a);
void rrb(t_stack *b);
void rrr(t_stack *a, t_stack *b);

// utils
void	ft_putstr_fd(int fd, char *s);
t_node *ft_lstnew(int value);
void ft_lstadd_back(t_stack *stack, t_node *new);
int	ft_atoi(const char *nptr);
void print_stack(t_stack *n);
void	check_duplicates(int value, t_node *n);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
