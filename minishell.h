/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:52:14 by aderraj           #+#    #+#             */
/*   Updated: 2024/08/16 20:08:49 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdlib.h>
#include <stdio.h>

typedef enum e_token
{
    VARIABLE,
    OPERATOR,
    EXPRESSION,
    WILDCARD
} e_token;

typedef struct s_node
{
    e_token tk_type;
    struct s_node *l_child;
    struct s_node *r_child;
} t_node;

#endif