#include "./include/parser.h"

char *str_to_command(t_tree_node *root)
{
    char    *command;
    t_words *tmp;

    tmp = root -> word_list;
    command = tmp -> word;
    tmp = tmp -> next;
    while (tmp != NULL && tmp->token_type != END)
    {
        command = ft_strjoin(command, " ");
        command = ft_strjoin(command, tmp -> word);
        tmp = tmp -> next;
    }
    return(command);
}

t_tree_node *last_left_root(t_tree_node *root)
{
    if (root == NULL)
        return (NULL);
    while(root -> left != NULL)
        root = root -> left;
    return(root);
}

void    command_loop(t_tree_node *root)
{
    t_tree_node *first_command;
    int         prevfd;

    prevfd = 0;
    root = last_left_root(root);
    first_command = root;
    while(true)
    {
        if (root -> prev == NULL ||(root -> prev -> prev == NULL && root != root -> prev -> left)) //コマンドが二つの時の条件分岐
        {
            do_last_command(root, prevfd);
            break ;
        }
        else
        {   
            prevfd = do_command(root, prevfd);
            if (root == first_command)
                root = root -> prev -> right;
            else
                root = root -> prev -> prev -> right;
        }
    }
    child_wait(root, first_command);
}