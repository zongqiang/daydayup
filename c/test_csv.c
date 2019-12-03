#include <stdlib.h>
#include <stdio.h>
#include <string.h>



static void chop(char *str)
{
    if (!str)
        return;

    // chop LF
    if (strlen(str) > 0 &&
        str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = '\0';

    // chop CR
    if (strlen(str) > 0 &&
        str[strlen(str)-1] == '\r')
        str[strlen(str)-1] = '\0';
}


static size_t csv_split(const char *str, const char *sep, char ***splitted, size_t *count)
{
    size_t cnt = 0;
    char **ptr = NULL;

    // null input pointer
    if (!str)
        return cnt;

    // empty input string
    if (strlen(str) == 0) {
        ptr = (char**)malloc(sizeof(char *));
        if (!ptr) {
            // error
            fprintf(stderr, "malloc error");
            return cnt;
        }
        ptr[cnt++] = strdup("");
        return cnt;
    }

    // default separator
    if (!sep || strlen(sep) == 0)
        sep = "\t";

    // process
    {
        const char *s = str;
        const char *p = s;
        size_t len = 1;

        while (1) {
            // met separator char
            if (strchr(sep, *p) || !*p) {
                if (p - s > 1 && *s == '"' && *(p-1) != '"') {
                    // separator char in quotation
                    // do nothing
                } else {
                    if (p == s) {
                        len = 1;
                    } else if (p - s > 1 && *s == '"' && *(p-1) == '"') {
                        len = p - s - 2 + 1;
                        ++s;
                    } else {
                        len = p - s + 1;
                        ++s;
                    }
                    ptr = (char**)realloc(ptr, sizeof(char *) * (cnt + 1));
                    ptr[cnt] = strncpy((char*)malloc(len), s, len - 1);
                    ptr[cnt++][len - 1] = '\0';
                    s = p + 1;
                }
                // end of string
                if (!*p)
                    break;
            }
            ++p;
        }
    }

    // output
    *splitted = ptr;
    *count = cnt;

    return cnt;
}

static void csv_free(char ***splitted, size_t count)
{
    size_t i;
    for (i = 0; i < count; ++i) {
        free((*splitted)[i]);
    }
    free(*splitted);
    *splitted = NULL;
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage %s a.txt\n", argv[0]);
        return 1;
    }

    FILE *fp = NULL;
    if (!(fp = fopen(argv[1], "r"))) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        return 2;
    }

    char buf[BUFSIZ];
    int lineno = 0;
    while (fgets(buf, sizeof(buf), fp)) {
        chop(buf);
        ++ lineno;

        char **splitted;
        size_t cnt;
        csv_split(buf, ",", &splitted, &cnt);
        printf("%s\n", buf);

        int i;
        for (i = 0; i < cnt; ++i) {
            printf("%d: %d: %s\n", lineno, i, splitted[i]);
        }

        csv_free(&splitted, cnt);
    }
    
    fclose(fp);
    return 0;
}
