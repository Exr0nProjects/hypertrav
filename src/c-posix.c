#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define invalid_dir(str) (str[0] == '.'  && (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')))

void list_dir(char path[], size_t nlen, size_t nmax, int (*callback)(const char *))
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
            list_dir(path, nlen+n, nmax, callback);
    }
    closedir(dir);
}

int main(int argc, const char**argv) {

    char path[1<<16] = ".";
    if (argc > 1) memcpy(path, argv[1], strlen(argv[1]));
    list_dir(path, strlen(path), sizeof(path), puts);

    return 0;
}

