/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:54:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/23 07:17:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree  *create_tree_node(e_token type, u_token_data data)
{
    t_tree *node = (t_tree *)malloc(sizeof(t_tree));
    if (!node) return NULL;
    node->type = type;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_tree *convert_to_ast(t_list *list)
{
    t_tree *root = NULL;      // Root of the tree
    t_tree *current_cmd = NULL;  // Tracks the current command being processed
    t_tree *last_operator = NULL;  // Tracks the last logical operator node
    t_tree *last_pipe = NULL;  // Tracks the last pipe node

    while (list) {
        if (list->type == CMD) {
            // Create a command node
            t_tree *cmd_node = create_tree_node(CMD, list->data);
            current_cmd = cmd_node;
        } 
        else if (list->type == PIPE) {
            // Handle PIPE similar to previous function
            t_tree *pipe_node = create_tree_node(PIPE, list->data);

            if (!root) {
                pipe_node->left = current_cmd;
                root = pipe_node;
            } else if (last_pipe) {
                last_pipe->right = current_cmd;
                pipe_node->left = root;
                root = pipe_node;
            }

            last_pipe = pipe_node;  // Update last pipe
            current_cmd = NULL;  // Reset current command
        } 
        else if (list->type == AND || list->type == OR) {
            // Handle AND and OR logical operators
            t_tree *op_node = create_tree_node(list->type, list->data);

            if (!root) {
                // If this is the first operator, set root
                op_node->left = current_cmd;
                root = op_node;
            } else if (last_operator) {
                // Attach the last logical operation to the right of previous one
                last_operator->right = current_cmd;
                op_node->left = root;
                root = op_node;
            } else {
                // Attach current command to the left of the logical operator
                op_node->left = current_cmd;
                root = op_node;
            }

            last_operator = op_node;  // Update last operator
            current_cmd = NULL;  // Reset current command
        } 
        else if (list->type == PARENTHESIS)
        {
            // Handle parentheses by creating a subtree
            t_tree *subtree = convert_to_ast(list->sub_list);  // Recursively process the sub-list inside parentheses

            if (!current_cmd)
            {
                current_cmd = create_tree_node(PARENTHESIS, list->data);
                current_cmd->data.sub_tree = subtree;
            }
            else
            {
                // Nested parentheses, attach as subtree
                t_tree *paren_node = create_tree_node(PARENTHESIS, list->data);
                paren_node->data.sub_tree = subtree;
                current_cmd = paren_node;
            }
        }
        list = list->next;  // Move to the next token
    }

    // Attach the final command or node
    if (current_cmd && last_operator) {
        last_operator->right = current_cmd;  // Attach the last command to the last operator
    } else if (current_cmd && root) {
        root->right = current_cmd;  // Attach the last command to the root
    } else if (current_cmd && !root) {
        root = current_cmd;  // Set final command as root if no operators
    }

    return root;
}
