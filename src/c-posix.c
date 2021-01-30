#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define invalid_dir(str) (str[0] == '.'  && (str[1] == '\0' || (str[1] == '.' && str[2] == '\0')))

/*void recurse(const char *name, void (*callback)(struct dirent *))*/
void recurse(char *name, void (*callback)(char *))
{
    DIR *cur;
    struct dirent *entry = NULL;

    if (!(cur = opendir(name))) return;

    //char path[1024];
    //memcpy(path, name, sizeof path);
    //size_t offset; while (path[

    while ((entry = readdir(cur))) {
        if (invalid_dir(entry->d_name)) continue;
        size_t offset = snprintf(path, sizeof path, "%s", name); // OPT: prolly faster with a raw loop
        callback(path);
        if (entry->d_type == DT_DIR) {
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); // https://stackoverflow.com/a/8438663
            recurse(path, callback);
        }
    }
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
    recurse(".", print);

    return 0;
}

