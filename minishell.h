/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:52:14 by aderraj           #+#    #+#             */
/*   Updated: 2024/08/18 01:04:30 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdlib.h>
#include <stdio.h>

typedef struct s_redirection
{
    char *op;
    char *filename;
    struct s_redirection *next;    
} t_redirection;

typedef struct s_cmd
{
    char *cmd;
    char **arg;
    t_redirection *redirs;   
}   t_cmd;

typedef enum e_token
{
    GROUPING,
    LOGICAL_OPERATOR,
    PIPELINE,
    VARIABLE,
    COMMAND,
    WILDCARD,
    ASSIGNMENT
} e_token;

typedef struct s_node
{
    e_token tk_type;
    struct s_node *l_child;
    struct s_node *r_child;
} t_node;

#endif