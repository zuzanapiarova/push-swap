/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:03:25 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/01 17:25:40 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// sa (swap a): Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one or no elements.
void	sa(t_stack *a)
{
	t_node	*temp1;
	t_node	*temp2;

	ft_putstr_fd("sa\n", 1);
	a->head->i++;
	if (a->head && a->head->next)
	{
		temp1 = a->head;
		temp2 = a->head->next;
		temp1->next = temp2->next;
		temp2->next = temp1;
		a->head = temp2;
		a->first = a->head;
		if (temp1->next == NULL)
			a->last = temp1;
	}
	a->head->i--;
}

// pa (push a): Take the first element at the top of b and
// put it at the top of a. Do nothing if b is empty.
void	pa(t_stack *a, t_stack *b)
{
	t_node	*temp;
	t_node	*current;

	ft_putstr_fd("pa\n", 1);
	if (b->head)
	{
		temp = b->head;
		b->head = b->head->next;
		temp->next = a->head;
		a->head = temp;
		a->size += 1;
		b->size -= 1;
		a->first = a->head;
		b->first = b->head;
		a->max = a->head;
		a->min = a->head;
		current = a->head;
		while (current != NULL)
		{
			if (current->value > a->max->value)
				a->max = current;
			if (current->value < a->min->value)
				a->min = current;
			current = current->next;
		}
		if (b->head == NULL)
			b->last = NULL;
		if (a->head->next == NULL)
			a->last = a->head;
	}
	index_stack(a);
	index_stack(b);
}

// ra (rotate a): Shift up all elements of stack a by 1.
// The first element becomes the last one.
void	ra(t_stack *a)
{
	t_node	*temp;

	ft_putstr_fd("ra\n", 1);
	if (a->head && a->head->next)
	{
		temp = a->head;
		a->head = a->head->next;
		temp->next = NULL;
		ft_stackadd_back(a, temp);
		a->first = a->head;
		a->last = temp;
	}
	index_stack(a);
}

// rra (reverse rotate a): Shift down all elements of stack a by 1.
// The last element becomes the first one.
void	rra(t_stack *a)
{
	t_node	*new_last;
	t_node	*last;

	ft_putstr_fd("rra\n", 1);
	if (a->head && a->head->next)
	{
		new_last = a->head;
		while (new_last->next->next != NULL)
			new_last = new_last->next;
		last = new_last->next;
		new_last->next = NULL;
		last->next = a->head;
		a->head = last;
		a->first = a->head;
		a->last = new_last;
	}
	index_stack(a);
}
