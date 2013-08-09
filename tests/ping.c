#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, const char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s nping\n", getprogname());
        return 1;
    }

    int n = atoi(argv[1]);
    int i;
    for (i = 0; i < n; i++) {
        printf("PING\n");
        fflush(stdout);

        char buf[8192];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            abort();
        }
        size_t len = strlen(buf);
        buf[len - 1] = '\0';
        if (strcmp(buf, "PONG") != 0) {
            abort();
        }
        fprintf(stderr, "%s\n", buf);
    }

    return 0;
}

/**
 * vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4
 */
