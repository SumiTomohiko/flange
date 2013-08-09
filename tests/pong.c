#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
    char buf[8192];
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        size_t len = strlen(buf);
        buf[len - 1] = '\0';
        if (strcmp(buf, "PING") != 0) {
            abort();
        }
        fprintf(stderr, "%s\n", buf);

        printf("PONG\n");
        fflush(stdout);
    }

    return 0;
}

/**
 * vim: tabstop=4 shiftwidth=4 expandtab softtabstop=4
 */
