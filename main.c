#include "./include/parser.h"
#include <stdio.h>

// t_global_data data

char	*type_to_char(int token_type)
{
	if (token_type == WORD)
		return ("WORD");
	else if (token_type == PIPE)
		return ("PIPE");
	else if (token_type == WRITE)
		return ("WRITE");
	else if (token_type == READ)
		return ("READ");
	else if (token_type == END)
		return ("END");
	else if (token_type == APPEND)
		return ("APPEND");
	else if (token_type == HEREDOC)
		return ("HEREDOC");
	/* else if (token_type == SEMICOLON) */
	/* 	return ("SEMICOLON"); */
	/* else if (token_type == AND) */
	/* 	return ("OR"); */
	/* else if (token_type == OR) */
	/* 	return ("OR"); */
	else
		return ("Error");
}

size_t	print_words(t_words *words)
{
	size_t	size;
	
	size = 0;
	while (words != NULL && words->token_type != END)
	{
		printf("[%s]", words->word);
		if (words->next->token_type != END)
			printf(" -> ");
		words = words->next;
		size++;
	}
	printf("\n");
	return (size);
}

void	print_tree(t_tree_node *node)
{
	if (node != NULL)
	{
		print_tree(node->left);
		printf("%12s : ", type_to_char(node->node_type));
		print_words(node->word_list);
		print_tree(node->right);
	}
}

int	main (int argc, char **argv)
{
	t_words		*words;
	t_tree_node	*root;

	if (argc == 1)
	{
		printf("argc = 1\n");
		return (1);
	}
	// printf("enter str -> %s\n", argv[1]);
	words = lexical_analysis(argv[1]);
	// if (check_not_close_quotation(words))
	// {
		// printf("Error not close quote\n");
		// return (1);
	// }
	root = create_tree(words);
	// if (root != NULL)
	// 	print_tree(root);
	// printf("%s\n", str_to_command(root));
	// printf("%p\n", root -> prev);
	command_loop(root);
	return (0);
}

