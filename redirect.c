#include "./include/parser.h"

t_words *delete_simplify(t_words *prev, t_words *head, t_words *sign)
{
    t_words *tmp;

    if (prev == head && head -> next == NULL)
    {
        free(prev -> next);
        free(prev);
        return (NULL);
    }
    else if (prev == sign)
    {
        tmp = prev -> next ->next;
        free(prev -> next);
        free(prev);
        return (tmp);
    }
    else
    {
        tmp = prev -> next;
        prev -> next = prev -> next -> next -> next;
        free(tmp -> next);
        free(tmp);
        return(head);
    }
}

t_words *do_redirect(t_words *prev,t_words *head,t_words *sign, t_words *filename)
{
    int fd;

    if (sign ->token_type == READ)
    {
        fd = open(filename -> word, O_RDONLY);
        if (fd < 0)
            write(2, "test\n", 5);
        dup2(fd, 0);
    }
    else
    {
        fd = open(filename -> word, O_RDWR || O_CREAT|| O_TRUNC);
        dup2(fd, 1);
    }
    close(fd);
    return(delete_simplify(prev, head, sign));
}

t_words *do_append(t_words *prev ,t_words *head, t_words *sign, t_words *filename)
{
    int fd;

    fd = open(filename -> word, O_APPEND);
    dup2(fd, 1);
    close(fd);
    return(delete_simplify(prev, head, sign));
}

t_words *redirect_check(t_words *head)
{
    t_words *head_tmp;
    t_words *prev;

    prev = head;
    head_tmp = head;
    while(head_tmp -> token_type != END)
    {
        if (head_tmp -> token_type == READ || head_tmp -> token_type == WRITE)
        {
            head = do_redirect(prev, head, head_tmp, head_tmp -> next);
            head_tmp = head;
        }
        else if (head_tmp -> token_type == APPEND)
        {
            head = do_append(prev, head, head_tmp, head_tmp -> next);
            head_tmp = head;
        }
        else
        {
            prev = head_tmp;
            head_tmp = head_tmp -> next;
        }
    }
    return(head);
}

// t_words *heredoc_check(t_words *head)
// {

// }