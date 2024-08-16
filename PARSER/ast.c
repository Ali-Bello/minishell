/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:31:22 by aderraj           #+#    #+#             */
/*   Updated: 2024/08/16 20:51:36 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *new_node(e_token token)
{
    t_node *new;

    new = malloc(sizeof(t_node));
    if (new)
    {
        new->tk_type = token;
        new->l_child = NULL;
        new->r_child = NULL;
    }
    return(new);
}

t_node *new_tree(t_node *l_child, t_node *r_child)
{
    t_node  *root;

    root = malloc(sizeof(t_node));
    if (!root)
        return (NULL);
    root->l_child = l_child;
    root->r_child = r_child;
    return (root);
}

