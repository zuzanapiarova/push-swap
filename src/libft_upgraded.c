/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_upgraded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:52:29 by zpiarova          #+#    #+#             */
/*   Updated: 2024/10/01 20:22:25 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ft_stackadd_back(t_stack *stack, t_node *new_node)
{
	t_node	*temp;

	if (!stack || !new_node)
		return ;
	if (stack->head == NULL)
		stack->head = new_node;
	else
	{
		temp = stack->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_node	*ft_stacknew(int value)
{
	t_node	*result;

	result = (t_node *)malloc(sizeof(t_node));
	if (!result)
		return (NULL);
	result->value = value;
	result->next = NULL;
	return (result);
}

t_node	*ft_stacklast(t_stack *s)
{
	t_node	*temp;

	if (!s)
		return (NULL);
	temp = s->head;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	index_stack(t_stack *s)
{
	t_node	*temp;
	int		index;

	index = 0;
	temp = s->head;
	while (temp)
	{
		temp->i = index;
		temp = temp->next;
		index++;
	}
}

void	ft_stackclear(t_stack *s)
{
	t_node	*current_el;
	t_node	*temp;

	if (!s || !s->head)
		return ;
	current_el = s->head;
	while (current_el)
	{
		temp = current_el->next;
		free(current_el);
		current_el = temp;
	}
	s->head = NULL;
}
