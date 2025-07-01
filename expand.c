/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:06:51 by mehdi             #+#    #+#             */
/*   Updated: 2025/07/01 17:38:49 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_cpy_envp(char **envp)
{
	int		nb_line;
	char	**cpy;
	int		i;

	i = 0;
	nb_line = 0;
	while (envp[nb_line])
		nb_line++;
	cpy = malloc(sizeof(char *) * (nb_line + 1));
	if (!cpy)
		return (NULL);
	while (i < nb_line)
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			while (--i >= 0)
				free(cpy[i]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}


char	*ft_strdup(const char *s1)
{
	int		i;
	int		len_dest;
	char	*dest;

	i = 0;
	len_dest = ft_strlen(s1);
	dest = malloc((len_dest + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// char	*expand(char *str)
// {
	
// }