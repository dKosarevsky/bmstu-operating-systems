#include <stdio.h>
#include <unistd.h>
#include<stack>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
#include <malloc.h>
#include <cstdlib>

using namespace std;

struct ElementTree{
    char* parent;
    char* name;
    int level;
} ;

#define MAX_LENGTH_NAME_FILE 256
#define MAX_LENGTH_PATH 4096
#define INDENT 5
#define ROOT  "/home/ilyaps/bmstu/os/lr3_treedir/tree_dir/dir_root/"

#define ERR_CHDIR 1

int main() {
    DIR *dp;
    struct dirent *dirp;
    struct stat statbuf;

    struct ElementTree head;
    head.name = (char *) ".";
    head.level = 0;

    head.parent = (char *) malloc (MAX_LENGTH_PATH * sizeof(char));
    head.parent[0] = '\0';
    strcat(head.parent , ROOT);

    printf("\nStart program for directory:\n%s\n" , head.parent);

    stack<ElementTree> stack;
    stack.push(head);


    do {
        head = stack.top();
        stack.pop();

        char* p = (char*) malloc (MAX_LENGTH_NAME_FILE * sizeof(char));
        p[0] = '\0';
        strcat(p, head.parent);
        strcat(p, "/");
        strcat(p, head.name);

        if (chdir(p) < 0) {
            exit(ERR_CHDIR);
        }
        free(p);

        if ((dp = opendir(".")) == NULL ) {
            printf("directory is not accessible");
            free(head.parent);
            continue;
        }

        printf("%*s%s\n", head.level * INDENT, "-(D) ", head.name);
        head.level++ ;

        while ((dirp = readdir(dp)) != NULL) {
            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
//                    printf("%*s%s\n", head.level, "(D)", dirp->d_name);
                continue;
            }

            if (lstat(dirp->d_name, &statbuf) < 0) {
                printf("error call lstat");
                continue;
            }

            if (S_ISDIR(statbuf.st_mode) == 0) {
                printf("%*s%s\t[%ld b]\n", head.level * INDENT, "-(F) ", dirp->d_name, statbuf.st_size);
                continue;
            }

            struct ElementTree new_el;
            new_el.name = (char *) dirp->d_name;
            new_el.level = head.level;

            new_el.parent = (char *) malloc(MAX_LENGTH_PATH * sizeof(char));
            new_el.parent[0] = '\0';
            strcat(new_el.parent, head.parent);
            strcat(new_el.parent, "/");
            strcat(new_el.parent, head.name);

            stack.push(new_el);
        }

        free(head.parent);
    } while(!stack.empty());

    return 0;
}

