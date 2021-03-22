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

int max_threads = 2;
atomic_int cur_threads = 0;

struct PathState {
	char *path;
	size_t nlen;
};

int launch_list_dir(void*);

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
			//printf("cur_threads %d max_threads %d\n", cur_threads, max_threads);
	        if (++cur_threads < max_threads) { // not leq bc root thread isn't counted
		        struct PathState nxt;
				nxt.path = (char *) malloc(MAX_BUF_LEN); // TODO: allocate only at beginning of program
				memcpy(nxt.path, path, MAX_BUF_LEN);
				nxt.nlen = nlen+n;
				thrd_t thread;  // TODO: threads are freed when function returns
				thrd_create(&thread, launch_list_dir, &nxt);
	        }
	        else { // otherwise, recurse
				--cur_threads;
				list_dir(path, nlen+n);
	        }
        }
    }
    closedir(dir);
}

int launch_list_dir(void* data)
{
	char *path = ((struct PathState*)data)->path;
	size_t nlen = ((struct PathState*)data)->nlen;

	//printf("launching new thread\n");

	list_dir(path, nlen);

	//printf("thread finished\n");

	free(path);
	--cur_threads;

	return 0;
}

int main(int argc, const char**argv) {
    callback = puts;

    char path[MAX_BUF_LEN] = ".";
    if (argc > 1) memcpy(path, argv[1], strlen(argv[1]));
    list_dir(path, strlen(path));
    //launch_list_dir(path, strlen(path));

    return 0;
}
