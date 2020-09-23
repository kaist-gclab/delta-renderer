#include <cstdio>
#include <cstdlib>

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(-1);
}
