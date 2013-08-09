#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void
pipe_or_die(int fds[2])
{
    if (pipe(fds) != 0) {
        err(1, "pipe(2) failed");
    }
}

static void
close_or_die(int d)
{
    if (close(d) != 0) {
        err(1, "close(2) failed: d=%d", d);
    }
}

static void
dup2_or_die(int oldd, int newd)
{
    if (dup2(oldd, newd) == -1) {
        err(1, "dup2(2) failed: oldd=%d, newd=%d", oldd, newd);
    }
}

struct lexer {
    const char* p;
    const char* pend;
};

static void
skip_whitespace(struct lexer* lexer)
{
    while ((*lexer->p != '\0') && (*lexer->p == ' ')) {
        lexer->p++;
    }
}

static void
copy_token(char* dest, const char* src)
{
    char* pdest = dest;
    const char* psrc = src;
    while ((*psrc != '\0') && (*psrc != ' ')) {
        *pdest = *psrc;
        pdest++;
        psrc++;
    }
    *pdest = '\0';
}

static char* args[32];

static char**
split_command(const char* cmd)
{
    struct lexer __lexer__;
    struct lexer* lexer = &__lexer__;
    lexer->p = cmd;
    lexer->pend = cmd + strlen(cmd);

    int i;
    for (i = 0; lexer->p < lexer->pend; i++) {
        skip_whitespace(lexer);

        char* buf = (char*)malloc(sizeof(char) * 256);
        copy_token(buf, lexer->p);
        args[i] = buf;
    }
    args[i] = NULL;

    return args;
}

#define R   0
#define W   1

static void
execute(const char* cmd, const int rpipe[2], const int wpipe[2])
{
    close_or_die(rpipe[W]);
    close_or_die(wpipe[R]);
    dup2_or_die(rpipe[R], fileno(stdin));
    dup2_or_die(wpipe[W], fileno(stdout));

    char** args = split_command(cmd);

    execvp(args[0], args);
    err(1, "cannot execute %s", args[0]);
}

int
main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "No command given.\n");
        exit(1);
    }

    int a2b[2];
    pipe_or_die(a2b);
    int b2a[2];
    pipe_or_die(b2a);

    pid_t pid = fork();
    switch (pid) {
    case -1:
        err(1, "fork(2) failed");
        break;
    case 0:
        execute(argv[1], b2a, a2b);
        break;
    default:
        break;
    }

    execute(argv[2], a2b, b2a);

    return 1;
}

/**
 * vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4
 */
