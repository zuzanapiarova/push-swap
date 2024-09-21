/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:40:11 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/09/21 09:47:30 by zuzanapiaro      ###   ########.fr       */
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

void find_least_operations(t_stack *a, t_stack *b)
{
   t_operation c_o; //current operation - stores how many operations ra, rb, rra, rrb, rr, rrr it takes to get two corresponding elements to top of each stack
   t_node      *temp;
   t_node      *friend;
   int radup;
   int rbdup;
   int rradup;
   int rrbdup;

    temp = a->head;
    a->cheapest_o->count = a->size + b->size;
    // a->cheapest_o->ra = 0;
    // a->cheapest_o->rb = 0;
    // a->cheapest_o->rr = 0;
    // a->cheapest_o->rra = 0;
    // a->cheapest_o->rrb = 0;
    // a->cheapest_o->rrr = 0;
   while (temp) // calculate this for EVERY element from a
   {
       if (temp->value > b->max->value || temp->value < b->min->value)
           friend = b->max;
       else
           friend = find_predecessor(temp, b);
       c_o.ra = temp->i;
       c_o.rb = friend->i;
       c_o.rra = a->size - temp->i;
       c_o.rrb = b->size - friend->i;
        radup = c_o.ra;
        rbdup = c_o.rb;
        rradup = c_o.rra;
        rrbdup = c_o.rrb;
        // 0.
       if (c_o.ra == 0 && c_o.rb == 0) //we know it is cheapest because it takes 0 operations to get the elements to top
       {
           a->cheapest_o->ra = 0;
           a->cheapest_o->rb = 0;
           a->cheapest_o->rr = 0;
           a->cheapest_o->rra = 0;
           a->cheapest_o->rrb = 0;
           a->cheapest_o->rrr = 0;
           a->cheapest_o->count = 0;
           return ;
       }
       // try to get rr and set ra and rb accordingly
       else if ((c_o.ra > 0 && c_o.rb == 0) || (c_o.rb == 0 && c_o.ra > 0))
           c_o.rr = 0;
       else
       {
           if (c_o.ra < c_o.rb)
           {
               c_o.rr = c_o.ra;
               c_o.ra = 0;
               c_o.rb = c_o.rb - c_o.rr;
           }
           else if (c_o.ra > c_o.rb)
           {
               c_o.rr = c_o.rb;
               c_o.rb = 0;
               c_o.ra = c_o.ra - c_o.rr;
           }
           else
           {
               c_o.rr = c_o.ra;
               c_o.ra = 0;
               c_o.rb = 0;
           }
       }
       // try to get rrr and set rra and rrb accordingly
       if ((c_o.rra > 0 && c_o.rrb == 0) || (c_o.rrb == 0 && c_o.rra > 0))
           c_o.rrr = 0;
       else if (c_o.rra > 0 && c_o.rrb > 0)
       {
           if (c_o.rra < c_o.rrb)
           {
               c_o.rrr = c_o.rra;
               c_o.rra = 0;
               c_o.rrb = c_o.rrb - c_o.rrr;
           }
           else if (c_o.rra > c_o.rrb)
           {
               c_o.rrr = c_o.rrb;
               c_o.rrb = 0;
               c_o.rra = c_o.rra - c_o.rrr;
           }
           else
           {
               c_o.rrr = c_o.rra;
               c_o.rra = 0;
               c_o.rrb = 0;
           }
       }
       c_o.rrcount = c_o.ra + c_o.rb + c_o.rr;
       c_o.rrrcount = c_o.rra + c_o.rrb + c_o.rrr;
       // now compare if combinations ra+rrb and rb+rra do not take less operations than the count
       if (((radup + rrbdup) < c_o.rrcount) && ((radup + rrbdup) < c_o.rrrcount) && ((radup + rrbdup) < a->cheapest_o->count))
       {
            a->cheapest_o->ra = radup;
            a->cheapest_o->rb = 0;
            a->cheapest_o->rr = 0;
            a->cheapest_o->rra = 0;
            a->cheapest_o->rrb = rrbdup;
            a->cheapest_o->rrr = 0;
            a->cheapest_o->count = radup + rrbdup;
       }
        else if (((rbdup + rradup) < c_o.rrcount) && ((rbdup + rradup) < c_o.rrrcount) && ((rbdup + rradup) < a->cheapest_o->count))
       {
            a->cheapest_o->ra = 0;
            a->cheapest_o->rb = rbdup;
            a->cheapest_o->rr = 0;
            a->cheapest_o->rra = rradup;
            a->cheapest_o->rrb = 0;
            a->cheapest_o->rrr = 0;
            a->cheapest_o->count = rbdup + rradup;
       }
       // select which combination takes least operations
       else if (c_o.rrcount < c_o.rrrcount && c_o.rrcount < a->cheapest_o->count)
       {
           a->cheapest_o->ra = c_o.ra;
           a->cheapest_o->rb = c_o.rb;
           a->cheapest_o->rr = c_o.rr;
           a->cheapest_o->rra = 0;
           a->cheapest_o->rrb = 0;
           a->cheapest_o->rrr = 0;
           a->cheapest_o->count = c_o.rrcount;
       }
       else if (c_o.rrrcount < c_o.rrcount && c_o.rrrcount < a->cheapest_o->count)
       {
           a->cheapest_o->ra = 0;
           a->cheapest_o->rb = 0;
           a->cheapest_o->rr = 0;
           a->cheapest_o->rra = c_o.rra;
           a->cheapest_o->rrb = c_o.rrb;
           a->cheapest_o->rrr = c_o.rrr;
           a->cheapest_o->count = c_o.rrrcount;
       }
       //printf("el: %d, fr: %d, ra: %d, rb: %d, rr: %d, rra: %d. rrb: %d. rrr: %d\n", temp->value, friend->value, a->cheapest_o->ra, a->cheapest_o->rb, a->cheapest_o->rr, a->cheapest_o->rra, a->cheapest_o->rrb, a->cheapest_o->rrr);
       temp = temp->next;
   }
}

void perform_operations(t_stack *a, t_stack *b)
{
   while (a->cheapest_o->ra > 0)
   {
       ra(a);
       a->cheapest_o->ra--;
   }
   while (a->cheapest_o->rb > 0)
   {
       rb(b);
       a->cheapest_o->rb--;
   }
   while (a->cheapest_o->rr > 0)
   {
       rr(a, b);
       a->cheapest_o->rr--;
   }
   while (a->cheapest_o->rra > 0)
   {
       rra(a);
       a->cheapest_o->rra--;
   }
   while (a->cheapest_o->rrb > 0)
   {
       rrb(b);
       a->cheapest_o->rrb--;
   }
   while (a->cheapest_o->rrr > 0)
   {
       rrr(a, b);
       a->cheapest_o->rrr--;
   }
}

// B is filled in separate partitions, each sorted descending
// if added element is new min/max, we put it above the biggest number in b
// for other elements, we add it above its predecessor - closest smaller element
void    fill_b(t_stack *a, t_stack *b)
{
   pb(a, b);
   pb(a, b);
   while (a->size > 3)
   {
       find_least_operations(a, b);
       perform_operations(a, b);
       pb(a, b);
   }
}

// when this function starts, a has 3 already sorted elements
// b has multiple sorted descending blocks, that may not be in order
// a. if (successor && a->head != b->head + 1)
// --> this puts the closest bigger element to top so we can pa to the top in correct order
void    back_to_a(t_stack *a, t_stack *b)
{
   int     operation;
   t_node  *successor;

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

void    algorithm(t_stack *a, t_stack *b)
{
   if (is_sorted(a))
       return ;
   if (!is_sorted(a) && a->size == 2) // we know this case is not sorted because before we checked if the list is sorted
           ra(a);
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
