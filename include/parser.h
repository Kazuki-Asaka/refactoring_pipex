#ifndef PARSER_H
#define PARSER_H

int	wstatus;
//  do not have to deal with "&()"
#define SPECIAL_CHAR " \t\n<>|;"
#define SPACE_CHAR " \t\n"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;
// typedef struct s_global_data
// {
// 	int	error_number;
// }	t_global_data;

typedef enum e_token_type
{
	END = 0,
	WORD,
	PIPE,
	READ,
	WRITE,
	APPEND,
	HEREDOC,
	COMMAND,
	/* SEMICOLON, */
	/* AND, */
	/* OR, */
}	t_token_type;

typedef struct s_words
{
	struct s_words	*next;
	t_token_type	token_type;
	char			*word;
	pid_t			command_pid;
}	t_words;

typedef struct s_tree_node
{
	t_token_type		node_type;
	t_words				*word_list;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

t_words		*lexical_analysis(char *str);

size_t		count_new_word_size(char *word);
size_t		count_word_size(char *str);
t_words		*change_str_to_words(char *str);
void		add_word_type(t_words *words);
bool		check_not_close_quotation(t_words *words);

/* ----------------- parser --------------------------- */

// t_tree_node	*create_tree(t_words *words);
void		add_node_type(t_tree_node *node);
// size_t	count_new_word_size(char *word);
// size_t	count_word_size(char *str);


// t_words *change_str_to_words(char *str);
// t_words	*del_word(t_words *word);
void	bundle_than_sign(t_words *words);

void	add_token_type(t_words *words);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* ----------------- parser --------------------------- */

t_tree_node	*create_tree(t_words *words);
bool		check_in_type(t_words *words, t_token_type word_type);

char *str_to_command(t_tree_node *root);


char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int 	ft_strchr ( const  char *s, int c);

char 		*str_to_command(t_tree_node *root);
t_tree_node *last_left_root(t_tree_node *root);
void   		 command_loop(t_tree_node *root);

int 	parents(t_tree_node *root,  pid_t pid, int prevfd, int *pipefd);
void    last_parents(t_tree_node *root, pid_t pid, int prevfd);
void    child_wait(t_tree_node *root, t_tree_node *first_command);
int 	do_command(t_tree_node *root, int prevfd);
void    do_last_command(t_tree_node *root, int prevfd);

char	*get_path(char *separgv);
char    *do_file_access(char *file);

t_words *delete_simplify(t_words *prev, t_words *head, t_words *sign);
t_words *do_redirect(t_words *prev,t_words *head,t_words *sign, t_words *filename);
t_words *do_append(t_words *prev ,t_words *head, t_words *sign, t_words *filename);
t_words *redirect_check(t_words *head);

#endif
