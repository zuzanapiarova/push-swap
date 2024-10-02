/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:45 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/02 17:16:27 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one or no elements.
void	sb(t_stack *b)
{
	t_node	*temp1;
	t_node	*temp2;

	ft_putstr_fd("sb\n", 1);
	b->head->i++;
	if (b->head && b->head->next)
	{
		temp1 = b->head;
		temp2 = b->head->next;
		temp1->next = temp2->next;
		temp2->next = temp1;
		b->head = temp2;
		b->first = b->head;
		if (temp1->next == NULL)
			b->last = temp1;
	}
	b->head->i--;
}

// pb (push b): Take the first element at the top of a and
// put it at the top of b. Do nothing if a is empty.
void	pb(t_stack *a, t_stack *b)
{
	t_node	*temp;

	ft_putstr_fd("pb\n", 1);
	if (a->head)
	{
		temp = a->head;
		a->head = a->head->next;
		temp->next = b->head;
		b->head = temp;
		b->size += 1;
		a->size -= 1;
		a->first = a->head;
		if (a->head == NULL)
			a->last = NULL;
		find_values(b);
	}
	index_stack(a);
}

// rb (rotate b): Shift up all elements of stack b by 1.
// The first element becomes the last one.
void	rb(t_stack *b)
{
	t_node	*temp;

	ft_putstr_fd("rb\n", 1);
	if (b->head && b->head->next)
	{
		temp = b->head;
		b->head = b->head->next;
		temp->next = NULL;
		ft_stackadd_back(b, temp);
		b->first = b->head;
		b->last = temp;
	}
	index_stack(b);
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1.
// The last element becomes the first one.
void	rrb(t_stack *b)
{
	t_node	*new_last;
	t_node	*last;

	ft_putstr_fd("rrb\n", 1);
	if (b->head && b->head->next)
	{
		new_last = b->head;
		while (new_last->next->next != NULL)
			new_last = new_last->next;
		last = new_last->next;
		new_last->next = NULL;
		last->next = b->head;
		b->head = last;
		b->first = b->head;
		b->last = new_last;
	}
	index_stack(b);
}
