// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   binary_tree.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/18 22:55:00 by clovell           #+#    #+#             */
// /*   Updated: 2024/03/18 23:06:53 by clovell          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
// #include <stddef.h>
// typedef struct s_btree	t_btree;

// typedef union u_any
// {
// 	void			*p;
// 	float			f;
// 	double			d;
// 	int				i;
// 	long long int	i;
// 	char			c;
// } t_any;

// struct	s_btree
// {
// 	void	*data;
// 	t_any	any;

// 	t_btree	*left;
// 	t_btree	*right;
// };

// t_btree	*btree_new(void *data, t_any value);

// void	btree_insert_min(t_btree	**head, void *data, float value)
// {
// 	if (head == NULL)
// 	{
// 		head = btree_new(data, (t_any){.f = value});
// 		return ;
// 	}
// 	if ((*head)->any > value)
// 	{
		
// 	}
// }