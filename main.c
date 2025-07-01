/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:53:09 by mehdi             #+#    #+#             */
/*   Updated: 2025/07/01 13:50:32 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}


int main(int ac, char **av)
{
	char	*input;
	char	*str;
	t_token	*head;

	head = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (quote_not_closed(input))
			free(input);
		else
		{
			str = clean_space(input);
			// printf("%s\n", str);
			// char	**res = ft_split(str);
			// while (*res)
			// 	printf("(%s)\n", *res++);
			free(input);
			tokenize_line(&head, str);
			print_tokens(head);
			ft_free_token(&head);
			free(str);
		}
	}
	return (0);
}

void	print(t_token *stack)
{
	while (stack)
	{
		printf("type : %d\n", stack->type);
		stack = stack->next;
	}
}

void print_tokens(t_token *token)
{
	while (token)
	{
		printf("Token type: %d\n", token->type);
		t_token_word *word = token->word;
		while (word)
		{
			printf("  Word: %s (expendable: %d)\n", word->word, word->expendable);
			word = word->next;
		}
		token = token->next;
	}
}


void	ft_free_token(t_token **token)
{
	t_token			*tmp;
	t_token_word	*tmp2;
	t_token_word	*word;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		word = tmp->word;
		while (word)
		{
			tmp2 = word;
			word = word->next;
			free(tmp2->word);
			free(tmp2);
		}
		free(tmp);
	}
	*token = NULL;
}
