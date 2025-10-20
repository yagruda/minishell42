#include <stdlib.h>
#include <string.h>
#include "executor.h"

#define REDIRECT_OUT 1

int init() {
    // Allocate t_cmd #1
    t_cmd *cmd1 = malloc(sizeof(t_cmd));
    cmd1->argv = malloc(sizeof(char *) * 3);
    cmd1->argv[0] = strdup("ls");
    cmd1->argv[1] = strdup("-la");
    cmd1->argv[2] = NULL;
    cmd1->redir = NULL;

    // Allocate t_cmd #2
    t_cmd *cmd2 = malloc(sizeof(t_cmd));
    cmd2->argv = malloc(sizeof(char *) * 3);
    cmd2->argv[0] = strdup("grep");
    cmd2->argv[1] = strdup("main");
    cmd2->argv[2] = NULL;

    // Allocate redirection for cmd2
    t_redir *redir = malloc(sizeof(t_redir));
    redir->type = REDIRECT_OUT;
    redir->file = strdup("out.txt");
    redir->next = NULL;

    cmd2->redir = redir;
    cmd2->next = NULL;

    // Link cmd1 → cmd2
    cmd1->next = cmd2;

    // Now cmd1 is the head of your pipeline
    // You can pass it to your executor logic

    return 0;
}