#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define invalid_dir(str) (str[0] == '.'  && (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')))

// https://stackoverflow.com/a/3437484
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/*void recurse(const char *name, void (*callback)(struct dirent *))*/
void recurse(char name[], size_t nlen, size_t nmax, int (*callback)(const char *))
{
    DIR *cur;
    struct dirent *entry = NULL;

    if (!(cur = opendir(name))) return;

    name[nlen++] = '/';
    name[nlen] = 0;

    //char path[1024];
    //memcpy(path, name, sizeof path);
    //size_t offset; while (path[

    while ((entry = readdir(cur))) {
        if (invalid_dir(entry->d_name)) continue;

 //       printf("processing '%s'\n", entry->d_name); 

        // memcpy(name+nlen+1, entry->d_name,
                 /*min(sizeof(name)-nlen-1, sizeof(entry->d_name)));*/

        size_t offset = snprintf(name+nlen, nmax-nlen, "%s", entry->d_name); // OPT: prolly faster with a raw loop

//        for (int i=0; name[i]; ++i) printf("%c", name[i]); printf("\n");

        callback(name);
//        if (!strcmp(name, "./testdir") && entry->d_type == DT_DIR)
//            getchar(),
//            fprintf(stderr, "entry %d should be %d\n", entry->d_type, DT_DIR);
        if (entry->d_type == DT_DIR && !strcmp(name, "./testdir")) {
            // snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); // https://stackoverflow.com/a/8438663
            fprintf(stderr, "name is '%50s', open would be %x\n", entry->d_name, opendir(name));
            recurse(name, nlen+offset, nmax, callback);
        }
    }
    closedir(cur);
}

void print(struct dirent *entry)
{
    puts(entry->d_name);
}

int main(int argc, const char**argv) {
    // from https://www.bfilipek.com/2019/04/dir-iterate.html
//    struct dirent *entry = NULL;
//    DIR *dp = NULL;
//
//    /*dp = opendir(argc > 1 ? argv[1] : ".");*/
//    dp = opendir(".");
//    if (dp != NULL) {
//        while ((entry = readdir(dp)))
//            printf("%s\n", entry->d_name);
//    }
//
//    closedir(dp);
    //recurse(".", print);
    char path[1<<16] = ".";
    recurse(path, strlen(path), sizeof(path), puts);

    return 0;
}

