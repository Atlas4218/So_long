/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:10:25 by rastie            #+#    #+#             */
/*   Updated: 2023/01/10 14:40:14 by rastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	*ft_memset(void *s, int c, size_t n)
{
	void	*result;

	result = s;
	while (n > 0)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
		n--;
	}
	return (result);
}

void	*ft_calloc(size_t nbelem, size_t sizelem)
{
	void	*result;

	result = malloc (nbelem * sizelem);
	if (result)
		ft_memset(result, 0, nbelem * sizelem);
	return (result);
}

char	*gnl_get_endl(char *buff, int fd)
{
	char	*add;
	char	*temp;
	int		rread;

	if (!buff)
		return (NULL);
	while (!ft_strchr(buff, '\n'))
	{
		temp = buff;
		add = malloc(BUFFER_SIZE + 1, sizeof (char));
		rread = read(fd, add, BUFFER_SIZE);
		if (rread <= 0)
		{
			if (!*buff)
				return (free(temp), free(add), NULL);
			return (free(add), buff);
		}
		buff = ft_strljoin(temp, add, rread);
		free(temp);
		free(add);
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[256];
	char		*temp;
	char		*result;

	if (fd <= 2 && fd)
		return (NULL);
	if (!buff[fd])
		buff[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof (char));
	buff[fd] = gnl_get_endl(buff[fd], fd);
	if (!buff[fd])
		return (NULL);
	temp = buff[fd];
	if (!ft_strchr(buff[fd], '\n'))
	{
		result = ft_strdup(buff[fd]);
		buff[fd] = NULL;
		return (free(temp), result);
	}
	result = ft_substr(buff[fd], 0, ft_strchr(buff[fd], '\n') - buff[fd] + 1);
	buff[fd] = ft_strdup(ft_strchr(temp, '\n') + 1);
	return (free(temp), result);
}
