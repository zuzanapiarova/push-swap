/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:40:11 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/09/17 23:45:02 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void sort_two(t_stack *s)
{

    if (is_sorted(s))
       return ;
   if (s->size == 2)
       ra(s);
}

void sort_three(t_stack *s)
{
   int first;
   int second;
   int third;

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

// find the closest predecessor to node n in stack s
t_node *find_predecessor(t_node *n, t_stack *s)
{
    if(!s->head)
        return NULL;
           // finding predecessor(closest smaller element) to our a head --> getting it to top --> then pb - so new element is on top of its predecessor
           t_node *temp = s->head;
           int delta;
           t_node *predecessor;
           // find first smaller value
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
           return predecessor;
}

// find the successor(closest bigger element) to node n in stack s
t_node *find_successor(t_node *n, t_stack *s)
{
        if(!s->head)
            return NULL;
        t_node *temp = s->head;
           int delta;
           t_node *successor;

           // find first bigger value
           while (temp && temp->value < n->value)
           {
                if (temp->next == NULL)
                    return NULL;
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
           return successor;
}

// B is always filled in one or more separate partitions, each sorted in descending order
// we are adding elements form one to other partition to land in the correct spot to place pa node to correct position
void fill_b(t_stack *a, t_stack *b)
{
   pb(a, b);
   pb(a, b);
   while (a->size > 3)
   {
       // get the biggest value to top as the new max/min must be placed on top of current max
       if(a->first->value > b->max->value || a->first->value < b->min->value) // this condition works great
       {
           int operation = select_r_or_rr(b->max, b);
           while (b->first != b->max)
           {
               if (operation == 1)
                   rb(b);
               else
                   rrb(b);
           }
           pb(a, b);
       }
       //else place the element into its correct position by removing all other elements until its predecessor/successor and pb to top
       else
       {
        // now we always have to have predecessor because if it was the new min value (=without predecessor), we would handle it in the if case
           t_node *predecessor = find_predecessor(a->head, b);
           int operation = select_r_or_rr(predecessor, b);
           while (b->first != predecessor)
           {
               if (operation == 1)
                   rb(b);
               else
                   rrb(b);
           }
           pb(a, b);
       }
   }
}

// when this function starts, a has 3 already sorted elements
// b has multiple sorted descending blocks, that may not be in order
void back_to_a(t_stack *a, t_stack *b)
{
    // TODO NOW:
    // CANNOT DO PB-RRA   PB-RRA AS IT WILL ROTATE OUR STACK THE OTHER WAY
    //a. a is sorted block with no gaps - smaller than b block - we pb entire b block and then rra
    //b. a is sorted block with no gaps - bigger than b block - we just pb
    //c. a is sorted block, b is two blocks top smaller and bottom bigger than a - we just pb until we find element bigger than biggest a
    //d. a is sorted block, b is two blocks bottom smaller and top bigger than a - we pb until find element smaller than smallest a block node
    while(b->size > 0)
    {
        // SOMEWHERE IN THIS LOOP IS A SEGFAULT
        // this puts the closest bigger element to top so we can pa to the top in correct order
        // thus combining two sorted parts - ascending from
        t_node *successor = find_successor(b->head, a);
        if (successor && a->head != b->head + 1)
        {
            int operation = select_r_or_rr(successor, a);
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
            while (a->first != a->min)
                ra(a);
        }
        pa(a, b);
    }
   if (a->min == a->first)
        printf("list is probably sorted\n");
   // find distance from a->first and a->min
   else if (a->min->i - a->first->i < a->last->i - a->max->i)
   {
        // number of elements tat need to go to the end are smaller so we ra
        while (a->first != a->min)
            ra(a);
   }
   else
   {
        // number of elements that need to go to the end is bigger so we rra from back
        while (a->last != a->max)
            rra(a);
   }
   // find distance from a->last and a->max
}

void    algorithm(t_stack *a, t_stack *b)
{
   if (is_sorted(a))
   {
       ft_putstr_fd("A sorted, B empty. Finished.\n", 1);
       return ;
   }
   if (a->size == 2) // we know this case is not sorted because before we checked if the list is sorted
       sort_two(a);
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
   print_stack(a);
   print_stack(b);
   back_to_a(a, b);
}

// !!! does not work if smallest number is in the last 3 elements input, it will not sort it properly
