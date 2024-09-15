/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:26 by zpiarova          #+#    #+#             */
/*   Updated: 2024/09/16 00:38:15 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	check_duplicates(int value, t_node *n)
{
	t_node *current;

	current = n;
	while (current)
	{
		if (current->value == value)
		{
			ft_putstr_fd("Duplicates\n", 2);
			exit(EXIT_FAILURE);
			// TODO: FREE AND DELETE ENTIRE STACK
		}
		else
			current = current->next;
	}
}

bool	is_valid_arg(char *s)
{
	// rozdel na jednotlive cisla a potom atoi a pridaj do stacku
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (*s == 32 || ft_isdigit(*s))
	{
		i++;
		s++;
	}
	return (i == len);
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

void find_values(t_stack *s)
{
	t_node *temp;

	s->first = s->head;
	s->min = s->head;
	s->max = s->head;
	temp = s->head;
	while(temp->next != NULL)
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
// selects r or rr depending on which is faster to get the node n to top
int	select_r_or_rr(t_node *n, t_stack *s)
{
	int	operation;

	if (n->i <= s->size / 2)
		operation = 1; // r
	else
		operation = 2; // rr
	return (operation);
}

// finds node closest to our nodes value, if two nodes are both close, one smaller, one bigger, we keep the bigger one
t_node *find_closest_neighbor(t_node *n, t_stack *s)
{
	// NOT FINISHED !!!!!!!!!!!!!
	t_node *result;
	t_node *temp;
	int		delta;
	int		temp_delta;

	result = s->head;
	temp = s->head;
	delta = temp->value - n->value;
	if (delta < 0)
		delta *= -1;
	while (temp)
	{
		temp_delta = temp->value - n->value;
		if (temp_delta < 0)
			temp_delta *= -1;
		if (temp_delta < delta )
			result = temp;
		if (temp_delta == delta && temp->value > result->value)
			result = temp;
		temp = temp->next;
	}
	return (result);
}
