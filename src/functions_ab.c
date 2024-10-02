/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_ab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:50:31 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/02 17:43:31 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// swaps two first elements of the stack and
// i++ before increases index of previous head
// i-- after decreases index of new head
void	ss_helper(t_stack *s)
{
	t_node	*temp1;
	t_node	*temp2;

	s->head->i++;
	if (s->head && s->head->next)
	{
		temp1 = s->head;
		temp2 = s->head->next;
		temp1->next = temp2->next;
		temp2->next = temp1;
		s->head = temp2;
		s->first = s->head;
		if (temp1->next == NULL)
			s->last = temp1;
	}
	s->head->i--;
}

// ss : sa and sb at the same time.
void	ss(t_stack *a, t_stack *b)
{
	ft_putstr_fd("ss\n", 1);
	ss_helper(a);
	ss_helper(b);
}

// rr : ra and rb at the same time.
void	rr(t_stack *a, t_stack *b)
{
	t_node	*temp1;
	t_node	*temp2;

	ft_putstr_fd("rr\n", 1);
	if (a->head && a->head->next)
	{
		temp1 = a->head;
		a->head = a->head->next;
		temp1->next = NULL;
		ft_stackadd_back(a, temp1);
		a->first = a->head;
		a->last = temp1;
	}
	if (b->head && b->head->next)
	{
		temp2 = b->head;
		b->head = b->head->next;
		temp2->next = NULL;
		ft_stackadd_back(b, temp2);
		b->first = b->head;
		b->last = temp2;
	}
	index_stack(a);
	index_stack(b);
}

// find the element that will become the last element after we rrr
// set last element to be the one after it and then brng it before head
// new last becomes last by having NULL as its next
// update the first, last, min, max values
void	rrr_helper(t_stack *s)
{
	t_node	*new_last1;
	t_node	*last1;

	if (s->head && s->head->next)
	{
		new_last1 = s->head;
		while (new_last1->next->next != NULL)
			new_last1 = new_last1->next;
		last1 = new_last1->next;
		new_last1->next = NULL;
		last1->next = s->head;
		s->head = last1;
		s->first = s->head;
		s->last = new_last1;
	}
}

// rrr : rra and rrb at the same time.
void	rrr(t_stack *a, t_stack *b)
{
	ft_putstr_fd("rrr\n", 1);
	rrr_helper(a);
	rrr_helper(b);
	index_stack(a);
	index_stack(b);
}
