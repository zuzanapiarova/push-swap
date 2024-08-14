/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:51:59 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/12 18:48:35 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// sa (swap a): Swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
void sa(t_stack *a)
{
	ft_putstr_fd(1, "sa\n");
	t_node	*temp1;
	t_node	*temp2;
	if (a->head && a->head->next)
	{
		temp1 = a->head;
		temp2 = a->head->next;
		temp1->next = temp2->next;  // First node now points to the third node
		temp2->next = temp1;        // Second node now points to the first node
		a->head = temp2;            // The head now points to the second node
	}
}
// sb (swap b): Swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements.
void sb(t_stack *b)
{
	ft_putstr_fd(1, "sb\n");
	t_node	*temp1;
	t_node	*temp2;
	if (b->head && b->head->next)
	{
		temp1 = b->head;
		temp2 = b->head->next;
		temp1->next = temp2->next;  // First node now points to the third node
		temp2->next = temp1;        // Second node now points to the first node
		b->head = temp2;            // The head now points to the second node
	}
}
// ss : sa and sb at the same time.
void ss(t_stack *a, t_stack *b)
{
	ft_putstr_fd(1, "ss\n");
	sa(a);
	sb(b);
}
// pa (push a): Take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
void pa(t_stack *a, t_stack *b)
{
	ft_putstr_fd(1, "pa\n");
	t_node *temp;

	if (b->head)
	{
		temp = b->head;           // Save the current head of b
		b->head = b->head->next;  // Move b's head to the next element

		temp->next = a->head;     // The old head of a becomes the next node after temp
		a->head = temp;           // Update a's head to the new node

		a->size += 1;             // Update the size of stack a
		b->size -= 1;             // Update the size of stack b
	}
}

// pb (push b): Take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
void pb(t_stack *a, t_stack *b)
{
	ft_putstr_fd(1, "pb\n");
	t_node *temp;

	if (a->head)
	{
		temp = a->head;           // Save the current head of b
		a->head = a->head->next;  // Move b's head to the next element

		temp->next = b->head;     // The old head of a becomes the next node after temp
		b->head = temp;           // Update a's head to the new node

		b->size += 1;             // Update the size of stack a
		a->size -= 1;             // Update the size of stack b
	}
}

// ra (rotate a): Shift up all elements of stack a by 1. The first element becomes the last one.
void ra(t_stack *a)
{
	ft_putstr_fd(1, "ra\n");
	t_node *temp;

	if (a->head && a->head->next)
	{
		temp = a->head;           // Save the current head of b
		a->head = a->head->next;  // Move b's head to the next element
		ft_lstadd_back(a, temp);
		temp->next = NULL;     // The old head of a becomes the next node after temp
	}
}
// rb (rotate b): Shift up all elements of stack b by 1. The first element becomes the last one.
void rb(t_stack *b)
{
	ft_putstr_fd(1, "rb\n");
	t_node *temp;

	if (b->head && b->head->next)
	{
		temp = b->head;           // Save the current head of b
		b->head = b->head->next;  // Move b's head to the next element
		ft_lstadd_back(b, temp);
		temp->next = NULL;     // The old head of a becomes the next node after temp
	}
}
// rr : ra and rb at the same time.
void rr(t_stack *a, t_stack *b)
{
	ft_putstr_fd(1, "rr\n");
	ra(a);
	rb(b);
}

// rra (reverse rotate a): Shift down all elements of stack a by 1. The last element becomes the first one.
void rra(t_stack *a)
{
	ft_putstr_fd(1, "rra\n");
	if (a->head && a->head->next)
	{
		t_node *new_last = a->head;
		while (new_last->next->next != NULL)
			new_last = new_last->next;
		t_node *last = new_last->next;
		new_last->next = NULL;
		last->next = a->head;
		a->head = last;
	}
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1. The last element becomes the first one.
void rrb(t_stack *b)
{
	ft_putstr_fd(1, "rrb\n");
	if (b->head && b->head->next)
	{
		t_node *new_last = b->head;
		while (new_last->next->next != NULL)
			new_last = new_last->next;
		t_node *last = new_last->next;
		new_last->next = NULL;
		last->next = b->head;
		b->head = last;
	}
}

// rrr : rra and rrb at the same time.
void rrr(t_stack *a, t_stack *b)
{
	ft_putstr_fd(1, "rrr\n");
	ra(a);
	rb(b);
}
