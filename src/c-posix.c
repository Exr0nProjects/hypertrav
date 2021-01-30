#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define invalid_dir(str) (str[0] == '.'  && (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')))

//// https://stackoverflow.com/a/3437484
//#define min(a,b) \
//   ({ __typeof__ (a) _a = (a); \
//       __typeof__ (b) _b = (b); \
//     _a < _b ? _a : _b; })

void recurse(char path[], size_t nlen, size_t nmax, int (*callback)(const char *))
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path)))
        return;

    path[nlen++] = '/';

    while ((entry = readdir(dir)) != NULL) {
        // don't run on invalid directories (. or ..)
        if (invalid_dir(entry->d_name)) continue;

        // append entry to current path
        size_t n=0; for (; entry->d_name[n]; ++n)
            path[nlen+n] = entry->d_name[n];
        path[nlen+n] = 0;

        // call the callback
        callback(path);

        // recurse directories
        if (entry->d_type == DT_DIR)
            recurse(path, nlen+n, nmax, callback);
    }
    closedir(dir);
}

//void print(struct dirent *entry)
//{
//    puts(entry->d_name);
//}
size_t counter;
int print(const char *s)
{
    ++counter;
    //return puts(s);
    return 0;
}

int main(int argc, const char**argv) {

    char path[1<<16] = ".";
    if (argc > 1) memcpy(path, argv[1], strlen(argv[1]));
    recurse(path, strlen(path), sizeof(path), print);

    printf("total = %lu\n", counter);

    return 0;
}

