/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:24:43 by mehdi             #+#    #+#             */
/*   Updated: 2025/07/01 15:52:48 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_word	*split_node_word(char *str)
{
	char			**word;
	int				i;
	t_token_word	*head_word;
	t_token_word	*new_word;

	head_word = NULL;
	i = 0;
	word = ft_split_word(str);
	if (!word)
		return (NULL);
	while (word[i])
	{
		new_word = new_node_word(word[i]);
		if (!new_word)
			exit(1);
		add_back_word(&head_word, new_word);
		i++;
	}	
	// free_split(word);
	return (head_word);
}

t_token_word	*new_node_word(char *str)
{
	t_token_word	*new;

	new = malloc(sizeof(t_token_word));
	if (!new)
		return (NULL);
	new->word = str;
	new->expendable = 1;
	new->next = NULL;
	return (new);
}

t_token	*new_node(t_token_word *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = TOK_WORD;
	new->word = word;
	new->next = NULL;
	return (new);
}

void	fill_expand(t_token_word *token)
{
	t_token_word	*tmp;
	char			*str;

	tmp = token;
	while (tmp)
	{
		if (tmp->word[0] == '\'')
			tmp->expendable = 0;
		if (tmp->word[0] == '\'' || tmp->word[0] == '\"')
		{
			str = delete_quote(tmp->word);
			free(tmp->word);
			tmp->word = str;
		}
		tmp = tmp->next;
	}
}

char	*delete_quote(char *str)
{
	char	*line;
	int		i;
	int		j;
	
	i = 1;
	j = 0;
	line = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!line)
		return (NULL);
	while (str[i+1])
		line[j++] = str[i++];
	line[j] = '\0';
	return (line);
}