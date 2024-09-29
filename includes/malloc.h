/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamella <anamella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 04:05:47 by anamella          #+#    #+#             */
/*   Updated: 2024/09/10 18:55:25 by anamella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_malloc
{
	void			*data;
	struct s_malloc	*next;
}	t_malloc;

t_malloc	*new_data(void *new, t_malloc *data);
void		add_data(t_malloc *new, t_malloc **data);
void		*ft_malloc(size_t size, t_malloc **tmp);
void		ft_free_malloc(t_malloc *data, int exit_code);

#endif