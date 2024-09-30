/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:26 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/30 15:11:16 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	check_duplicates(int value, t_stack *s)
{
	t_node	*current;

	current = s->head;
	while (current)
	{
		if (current->value == value)
		{
			ft_putstr_fd("Duplicates\n", 2);
			ft_stackclear(s);
			exit(EXIT_SUCCESS);
		}
		else
			current = current->next;
	}
}

// iterate stack until node  is bigger than next node, or we come to end
// if the node we finish at is the last one, list is sorted, else not
bool	is_sorted(t_stack *a)
{
	t_node	*node;

	node = a->head;
	while (node && node->next && node->value < node->next->value)
		node = node->next;
	return (!node -> next);
}

void	find_values(t_stack *s)
{
	t_node	*temp;

	if (!s)
		return ;
	s->first = s->head;
	s->min = s->head;
	s->max = s->head;
	temp = s->head;
	while (temp->next != NULL)
	{
		if (temp->value > s->max->value)
			s->max = temp;
		if (temp->value < s->min->value)
			s->min = temp;
		temp = temp->next;
	}
	s->last = temp;
	if (temp->value > s->max->value)
		s->max = temp;
	if (temp->value < s->min->value)
		s->min = temp;
	index_stack(s);
}

// performs that operation to get given element to top which is cheaper
void do_r_or_rr(t_node *n, t_stack *s)
{
	int	operation;

	if (n->i <= s->size / 2)
		operation = 1;
	else
		operation = 2;
	while (s->first != n)
	{
		if (operation == 1)
			ra(s);
		else
			rra(s);
	}
}

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
