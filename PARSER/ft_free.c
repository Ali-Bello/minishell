/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:59:22 by marvin            #+#    #+#             */
/*   Updated: 2024/10/24 10:40:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_data(t_cmd *data)
{
    t_redir *tmp;
    t_redir *tmp2;
    int i;

    free(data->cmd);
    i = 0;
    while (data->args && data->args[i])
    {
        free(data->args[i]);
        i++;
    }
    free(data->args);
    tmp = data->redirections;
    while (tmp)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->file);
        free(tmp2);
    }
}

void    free_list(t_list *list)
{
    t_list *tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free_data(&tmp->data);
        if (tmp->sub_list)
            free_list(tmp->sub_list);
        free(tmp->s);
        free(tmp);
    }
}

void    free_tree(t_tree *tree)
{
    if (!tree)
        return;
    if (tree->sub_tree)
        free_tree(tree->sub_tree);
    free(tree->left);
    free(tree->right);
    free(tree);
}