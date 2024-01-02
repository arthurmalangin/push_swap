/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:46:54 by amalangi          #+#    #+#             */
/*   Updated: 2024/01/02 20:22:17 by amalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	stacksize(t_stack *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
int ft_abs(int n)
{
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}
int get_inferior_value(t_stack *stack, int value)
{
	while (stack)
	{
		if (stack->value < value)
			return stack->value;
		stack = stack->next;
	}
	return value;
}

int get_approach_value(t_stack *stack, int value)
{
    int closest_value = stack->value;
    int closest_difference = ft_abs(value - closest_value);
    stack = stack->next;

    while (stack)
	{
        int current_difference = ft_abs(value - stack->value);

        if (current_difference < closest_difference ||
            (current_difference == closest_difference && stack->value > closest_value)) 
		{
            closest_value = stack->value;
            closest_difference = current_difference;
        }

        stack = stack->next;
    }

    return closest_value;
}

int get_approach_inferior(t_stack *stack, int value)
{
	return (get_inferior_value(stack, get_approach_value(stack, value)));
}


void sort(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a == NULL || is_sorted(*stack_a))
		return;
	int min_b;
	int max_b;
	int min_a;
	int max_a;

	pb(stack_a, stack_b);
	pb(stack_a, stack_b);
	min_b = find_min(*stack_b);
	max_b = find_max(*stack_b);
	if ((*stack_b)->value == min_b)
	{
		rb(stack_b);
	}
	if (stacksize(*stack_a) == 3)
	{
		//ft_printf("stacksize 3\n");
		while (!is_sorted(*stack_a))
		{
			//ft_printf("stacksize 3 loop\n");
			max_a = find_max(*stack_a);
			min_a = find_min(*stack_a);
			if ((*stack_a)->value == max_a)
			{
				ra(stack_a);
				if (!is_sorted(*stack_a))
					sa(stack_a);
			}
			else if ((*stack_a)->value == min_a)
			{
				ra(stack_a);
			}
			else
			{
				sa(stack_a);
			}
		}
		ft_printf("stacksize 3 end\n");
		while (*stack_b)
		{
			ft_printf("stacksize 3 pb: %d %d\n", get_approach_value(*stack_a, (*stack_b)->value), (*stack_b)->value);
			if (get_approach_value(*stack_a, (*stack_b)->value) == (*stack_a)->value && (*stack_b)->value < find_max(*stack_a))
			{
				pa(stack_a, stack_b);
			}
			else if ((*stack_b)->value > find_max(*stack_a))
			{
				while ((*stack_a)->value != find_min(*stack_a))
					ra(stack_a);
				pa(stack_a, stack_b);	
			}
			else
			{
				ra(stack_a);
			}
		}
		while (!is_sorted(*stack_a))
			ra(stack_a);
		
	}
	// while (*stack_a)
	// {
	// 	if ((*stack_a)->value > max_b)
	// 	{
	// 		max_b = (*stack_a)->value;
	// 		pb(stack_a, stack_b);
	// 	}
	// 	else if ((*stack_a)->value < min_b)
	// 	{
	// 		min_b = (*stack_a)->value;
	// 		pb(stack_a, stack_b);
	// 		rb(stack_b);
	// 	}
	// 	else
	// 	{
	// 		ra(stack_a);
	// 		while (get_end_value(*stack_a) < max_b)
	// 		{
	// 			pa(stack_a, stack_b);
	// 			max_b = find_max(*stack_b);
	// 		}
	// 		rra(stack_a);
	// 		max_b = (*stack_a)->value;
	// 		pb(stack_a, stack_b);
	// 	}
	// }
	// while (*stack_b)
	// 	pa(stack_a, stack_b);
}

int get_end_value(t_stack *stack)
{
	while (stack->next)
		stack = stack->next;
	return stack->value;
}

int find_min(t_stack *stack)
{
	int min = stack->value;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return min;
}

int find_max(t_stack *stack)
{
	int max = stack->value;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return max;
}
