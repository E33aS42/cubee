/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esommier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:06:09 by esommier          #+#    #+#             */
/*   Updated: 2019/12/03 15:59:04 by esommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_strlen(char *s) //		printf("A\n");
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i != len + 1)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*res;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!(res))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - len1] != '\0')
	{
		res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char *s)
{
	char	*dupl;
	int		i;
	int		len;

	len = ft_strlen(s);
	dupl = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dupl))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dupl[i] = s[i];
		i++;
	}
	dupl[i] = '\0';
	return (dupl);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*res;
	int		k;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	i = start;
	j = 0;
	k = ft_strlen(s);
	while (s[i] != '\0' && i < len + start && start < k)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
