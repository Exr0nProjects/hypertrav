#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>

#define invalid_dir(str) (str[0] == '.'  && (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')))

#define MAX_BUF_LEN 4096

int (*callback)(const char *) = NULL;

int max_threads = 1;
atomic_int cur_threads = 0;

void launch_list_dir(char[], size_t);

void list_dir(char path[], size_t nlen)
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

        callback(path);

        // recurse directories
        if (entry->d_type == DT_DIR) {
			// if under max, launch a new thread
	        if (++cur_threads < max_threads) // not leq bc root thread isn't counted
		        launch_list_dir(path, nlen);
	        else // otherwise, recurse
				list_dir(path, nlen+n);
        }
    }
    closedir(dir);
}

void launch_list_dir(char path[], size_t nlen)
{
	char *newpath = (char *) malloc(MAX_BUF_LEN); // TODO: allocate only at beginning of program
	memcpy(newpath, path, MAX_BUF_LEN);
	list_dir(path, nlen);
	free(newpath);
}

int main(int argc, const char**argv) {
    callback = puts;

    char path[MAX_BUF_LEN] = ".";
    if (argc > 1) memcpy(path, argv[1], strlen(argv[1]));
    //     list_dir(path, strlen(path), sizeof(path), puts);
    launch_list_dir(path, strlen(path));

    return 0;
}
