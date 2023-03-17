/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:10:54 by rastie            #+#    #+#             */
/*   Updated: 2023/03/13 15:10:15 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	void_do_nothing(void *data)
{
	(void)data;
}

int	int_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int	int_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	**list_to_array(t_list *lst)
{
	void	**result;
	void	**temp;
	t_list	*next;

	if (!lst)
		return (NULL);
	if (!lst->content || !(*(char *)lst->content))
		return (ft_lstclear(&lst, &free), NULL);
	temp = malloc((ft_lstsize(lst) + 1) * sizeof(void *));
	if (!temp)
		return (NULL);
	result = temp;
	while (lst)
	{
		*temp = lst->content;
		temp++;
		next = lst->next;
		ft_lstdelone(lst, &void_do_nothing);
		lst = next;
	}
	*temp = NULL;
	return (result);
}

char	**get_map(char *filename)
{
	int		file;
	t_list	*result;
	char	*line;

	if (!filename)
		return (NULL);
	if (strcmp(strrchr(filename, '.'), ".ber"))
	{
		errno = 22;
		return (perror("Verifier l'extension du fichier"), NULL);
	}
	file = open(filename, O_RDONLY);
	if (file < 0)
		return (perror("Erreur d'ouverture du fichier"), NULL);
	result = NULL;
	line = (char *)1;
	while (line)
	{
		line = get_next_line(file);
		ft_lstadd_back(&result, ft_lstnew(ft_strtrim(line, "\n")));
		free(line);
	}
	close(file);
	return ((char **)list_to_array(result));
}
