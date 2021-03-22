#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>

#define invalid_dir(str) (str[0] == '.'  && (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')))

#define MAX_BUF_LEN 4096

atomic_int cur_threads = 0;

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

void launch_list_dir(char path[], size_t nlen, size_t nmax, int (*callback)(const char*))
{
	char *newpath = (char *) malloc(nmax); // TODO: allocate only at beginning of program
	memcpy(newpath, path, nmax);
	list_dir(path, nlen, nmax, callback);
	free(newpath);
}

int main(int argc, const char**argv) {
    char path[MAX_BUF_LEN] = ".";
    if (argc > 1) memcpy(path, argv[1], strlen(argv[1]));
    //     list_dir(path, strlen(path), sizeof(path), puts);
    launch_list_dir(path, strlen(path), sizeof(path), puts);

    return 0;
}
