typedef struct s_redir {
    int type;               // REDIRECT_IN, REDIRECT_OUT, etc.
    char *file;             // filename or heredoc delimiter
    struct s_redir *next;
} t_redir;

typedef struct s_cmd {
    char **argv;            // command arguments
    t_redir *redir;         // redirection list
    struct s_cmd *next;     // next command in pipeline
} t_cmd;

int init(void);