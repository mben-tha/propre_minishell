/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:41:05 by mehdi             #+#    #+#             */
/*   Updated: 2025/06/26 13:42:54 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		len_clean_space(char *str);
void	len_clean_space2(char *str, int *i, int *len);
char    *clean_space(char *str);
void	clean_space2(char *str, char *res, int *i, int *j);
void	clean_space3(char *str, int *i);
int		is_double_operator(char *str);

char    *clean_space(char *str)
{
    char    *res;
    int     i;
    int     j;

    j = 0;
    i = 0;
    res = malloc(sizeof(char) * (len_clean_space(str) + 1));
    if (!res)
        return (NULL);
    clean_space3(str, &i);
    while (str[i])
    {
        if (str[i] == ' ')
        {
            while (str[i] == ' ')
                i++;
            if (!str[i])
                break ;
            res[j++] = ' ';
        }
		else
			clean_space2(str, res, &i, &j);
    }
    res[j] = '\0';
    return res;
}

void	clean_space3(char *str, int *i)
{
    while (str[*i] == ' ')
        (*i)++;
}

void	clean_space2(char *str, char *res, int *i, int *j)
{
	if (is_double_operator(&str[*i]))
	{
		if (*i != 0 && str[*i-1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = str[*i];
		res[(*j)++] = str[*i];
		if (str[*i+2] && str[*i+2] != ' ')
			res[(*j)++] = ' ';
		*i += 2;
	}
	else if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		if (*i != 0 && str[*i-1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = str[*i];
		if (str[*i+1] && str[*i+1] != ' ')
			res[(*j)++] = ' ';
		(*i)++;
	}
	else
	{
		res[(*j)++] = str[*i];
		(*i)++;
	}
}

int len_clean_space(char *str)
{
    int i;
    int len;

    len = 0;
    i = 0;
    while (str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            while (str[i] == ' ')
                i++;
            if (!str[i])
                return len;
            len++;
        }
        else
			len_clean_space2(str, &i, &len);
    }
    return len;
}

void	len_clean_space2(char *str, int *i, int *len)
{
	if (is_double_operator(&str[*i]))
	{
		if (*i != 0 && str[*i-1] != ' ')
	        (*len)++;
		if (str[*i+2] && str[*i+2] != ' ')
            (*len)++;
		*i += 2;
		*len += 2;
	}
    else if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
    {
        if (*i != 0 && str[*i-1] != ' ')
            (*len)++;
        if (str[*i+1] && str[*i+1] != ' ')
            (*len)++;
        (*i)++;
        (*len)++;
    }
	else
    {
    	(*i)++;
    	(*len)++;
	}
}

int is_double_operator(char *str)
{
    return ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'));
}

int main(int ac, char **av)
{
    char *test;

    test = clean_space(av[1]);
    printf("[%s]\n", test);
	free(test);

    // printf("%dY\n", len_clean_space(av[1]));
}
