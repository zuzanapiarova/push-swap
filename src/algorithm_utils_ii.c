/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_utils_ii.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:14:11 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/01 20:21:02 by zpiarova         ###   ########.fr       */
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

	predecessor = NULL;
	if (!s->head)
		return (NULL);
	temp = s->head;
	while (temp->value > n->value)
		temp = temp->next;
	if (temp == NULL)
		return (NULL);
	if (temp->value < n->value)
		predecessor = temp;
	delta = n->value - predecessor->value;
	temp = temp->next;
	while (temp)
	{
		if (n->value - temp->value < delta && temp->value < n->value)
			predecessor = temp;
		delta = n->value - predecessor->value;
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

	successor = NULL;
	if (!s->head)
		return (NULL);
	temp = s->head;
	while (temp && temp->value < n->value)
		temp = temp->next;
	if (temp == NULL)
		return (NULL);
	if (temp->value > n->value)
		successor = temp;
	delta = successor->value - n->value;
	temp = temp->next;
	while (temp)
	{
		if (temp->value - n->value < delta && temp->value > n->value)
			successor = temp;
		delta = successor->value - n->value;
		temp = temp->next;
	}
	return (successor);
}

// perform all actions of cheapest operation to get elemets to top
void	perform_operation(t_stack *a, t_stack *b)
{
	while (a->ch->ra-- > 0)
		ra(a);
	while (a->ch->rb-- > 0)
		rb(b);
	while (a->ch->rr-- > 0)
		rr(a, b);
	while (a->ch->rra-- > 0)
		rra(a);
	while (a->ch->rrb-- > 0)
		rrb(b);
	while (a->ch->rrr-- > 0)
		rrr(a, b);
}

void	sort_three(t_stack *s)
{
	int	first;
	int	second;
	int	third;

	if (is_sorted(s))
		return ;
	first = s->head->value;
	second = s->head->next->value;
	third = s->head->next->next->value;
	if (first < second && second > third && first < third)
	{
		rra(s);
		sa(s);
	}
	else if (first < second && second > third && first > third)
		rra(s);
	else if (first > second && second < third && first > third)
		ra(s);
	else if (first > second && second < third && first < third)
		sa(s);
	else if (first > second && second > third && first > third)
	{
		sa(s);
		rra(s);
	}
}
