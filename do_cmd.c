#include "./include/parser.h"


int parents(t_tree_node *root, pid_t pid, int prevfd, int *pipefd)
{
    root -> word_list -> command_pid = pid;
    if (prevfd == 0)
    {
        prevfd = pipefd[0];
        close(pipefd[1]);
        return(prevfd);
    }
    else
    {
        close(prevfd);
        prevfd = pipefd[0];
        close(pipefd[1]);
        return(prevfd);
    }
}

void    last_parents(t_tree_node *root, pid_t pid, int prevfd)
{
    root -> word_list -> command_pid = pid;
    close(prevfd);
}

void    child_wait(t_tree_node *root, t_tree_node *first_command)
{
    root = first_command;
    while(true)
    {
        if (root -> prev == NULL ||(root -> prev -> prev == NULL && root != root -> prev -> left))
        {
            waitpid(root -> word_list -> command_pid, &wstatus, 0);
            break ;
        }
        else
        {
            waitpid(root ->word_list -> command_pid, &wstatus, 0); 
            if (root == first_command)
                root = root -> prev -> right;
            else
                root = root -> prev -> prev -> right;
        }
    }
    return ;
}

int do_command(t_tree_node *root, int prevfd)
{
    pid_t   pid;
    char    **separgv;
    char    *path;
    int     pipefd[2];

    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        if (prevfd != 0)
        {
            dup2(prevfd, 0);
            close (prevfd);
        }
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        root ->word_list = redirect_check(root -> word_list);
        separgv = ft_split(str_to_command(root), ' ');
        path = get_path(separgv[0]);
        execve(path, separgv, environ);
    }
    return (parents(root, pid, prevfd, pipefd));
}

void    do_last_command(t_tree_node *root, int prevfd)
{
    char    **separgv;
    char    *path;
    pid_t   pid;

    pid = fork();
    if (pid == 0)
    {
        if (prevfd != 0)
        {
            dup2(prevfd, 0);
            close (prevfd);
        }
        root -> word_list = redirect_check(root -> word_list);
        separgv = ft_split(str_to_command(root), ' ');
        path = get_path(separgv[0]);
        execve(path, separgv, environ);
    }
    else
        last_parents(root, pid, prevfd);
}