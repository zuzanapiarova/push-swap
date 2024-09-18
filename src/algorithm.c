/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:40:11 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/09/18 18:45:38 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// find the closest predecessor to node n in stack s
// a. while (temp->value > n->value)
// --> first while loop here finds first smaller value
t_node	*find_predecessor(t_node *n, t_stack *s)
{
	t_node	*temp;
	int		delta;
	t_node	*predecessor;

	if (!s->head)
		return (NULL);
	temp = s->head;
	while (temp->value > n->value)
		temp = temp->next;
	if (temp->value < n->value)
	{
		delta = n->value - temp->value;
		predecessor = temp;
	}
	temp = temp->next;
	while (temp)
	{
		if (n->value - temp->value < delta && temp->value < n->value)
		{
			predecessor = temp;
			delta = n->value - temp->value;
		}
		temp = temp->next;
	}
	return (predecessor);
}

// find the successor(closest bigger element) to node n in stack s
// a. while (temp && temp->value < n->value)
// --> first while loop here finds first bigger value than our element
t_node	*find_successor(t_node *n, t_stack *s)
{
	t_node	*temp;
	int		delta;
	t_node	*successor;

	if (!s->head)
		return (NULL);
	temp = s->head;
	while (temp && temp->value < n->value)
	{
		if (temp->next == NULL)
			return (NULL);
		temp = temp->next;
	}
	if (temp->value > n->value)
	{
		delta = temp->value - n->value;
		successor = temp;
	}
	temp = temp->next;
	while (temp)
	{
		if (temp->value - n->value < delta && temp->value > n->value)
		{
			successor = temp;
			delta = temp->value - n->value;
		}
		temp = temp->next;
	}
	return (successor);
}

// B is filled in separate partitions, each sorted descending
// if added element is new min/max, we put it above the biggest number in b
// for other elements, we add it above its predecessor - closest smaller element
void	fill_b(t_stack *a, t_stack *b)
{
	int		operation;
	t_node	*predecessor;

	pb(a, b);
	pb(a, b);
	while (a->size > 3)
	{
		if (a->first->value > b->max->value || a->first->value < b->min->value)
		{
			operation = select_r_or_rr(b->max, b);
			while (b->first != b->max)
			{
				if (operation == 1)
					rb(b);
				else if (operation == 2)
					rrb(b);
			}
		}
		else
		{
			predecessor = find_predecessor(a->head, b);
			operation = select_r_or_rr(predecessor, b);
			while (b->first != predecessor)
			{
				if (operation == 1)
					rb(b);
				else
					rrb(b);
			}
		}
		pb(a, b);
	}
}

// when this function starts, a has 3 already sorted elements
// b has multiple sorted descending blocks, that may not be in order
// a. if (successor && a->head != b->head + 1)
// --> this puts the closest bigger element to top so we can pa to the top in correct order
void	back_to_a(t_stack *a, t_stack *b)
{
	int		operation;
	t_node	*successor;

	while (b->size > 0)
	{
		successor = find_successor(b->head, a);
		if (successor && a->head != b->head + 1)
		{
			operation = select_r_or_rr(successor, a);
			while (a->first != successor)
			{
				if (operation == 1)
					ra(a);
				else
					rra(a);
			}
		}
		else
		{
			operation = select_r_or_rr(a->min, a);
			while (a->first != a->min)
			{
				if (operation == 1)
					ra(a);
				else
					rra(a);
			}
		}
		pa(a, b);
	}
	if (a->min->i - a->first->i < a->last->i - a->max->i) // find distance from a->first and a->min
	{
		while (a->first != a->min) // number of elements that need to go to the end are smaller so we ra
			ra(a);
	}
	else
	{
		while (a->last != a->max) // number of elements that need to go to the end is bigger so we rra from back
			rra(a);
	}
}

void	algorithm(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2) // we know this case is not sorted because before we checked if the list is sorted
	{
		if (!is_sorted(a) && a->size == 2)
			ra(a);
	}
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
	{
		pb(a, b);
		sort_three(a);
	}
	else if (a->size == 5)
	{
		pb(a, b);
		pb(a, b);
		sort_three(a);
	}
	else
	{
		fill_b(a, b);
		sort_three(a);
	}
	back_to_a(a, b);
}
