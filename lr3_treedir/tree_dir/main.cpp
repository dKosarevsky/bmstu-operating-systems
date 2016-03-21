#include <stdio.h>
#include <unistd.h>
#include <stack>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

//отступ для красивого вывода на экран
#define INDENT 5

//откуда строить дерево
#define ROOT  "/home/ilyaps/bmstu/os/lr3_treedir/tree_dir/dir_root/"

//начальный уровень в дереве
#define START_LEVEL 0

#define CURRENT_DIR "."
#define PARENT_DIR ".."

#define ERR_NUM_CHDIR 1
#define ERR_INFO_CHDIR "error call CHDIR"

#define ERR_INFO_CALL_LSTAT "error call lstat"

#define DIR_IS_NOT_ASSESS "directory is not accessible"

struct ElementTree{
    char* name;
    int level;
} ;

int main() {
    //уровень в дереве, на котором мы находимся на текущей итерации
    int current_level = START_LEVEL;
    if (chdir(ROOT) < 0) {
        printf(ERR_INFO_CHDIR);
        exit(ERR_NUM_CHDIR);
    }
    printf("\nStart program for directory:\n%s\n" , ROOT);

    struct ElementTree head;
    head.name = (char *) CURRENT_DIR;
    head.level = 1;

    stack<ElementTree> stack;
    stack.push(head);

    do {
        head = stack.top();
        stack.pop();

        //на (count_level_up + 1) надо подняться по дереву в сторону корня
        int count_level_up = current_level - head.level;
        for (int i = 0; i <= count_level_up; ++i) {
            if (chdir(PARENT_DIR) < 0) {
                printf(ERR_INFO_CHDIR);
                exit(ERR_NUM_CHDIR);
            }
        }

        current_level = head.level;
        if (chdir(head.name) < 0) {
            printf(ERR_INFO_CHDIR);
            exit(ERR_NUM_CHDIR);
        }

        DIR *dp;
        if ((dp = opendir(CURRENT_DIR)) == NULL ) {
            printf(DIR_IS_NOT_ASSESS);
            continue;
        }

        //печатаем информацию о текущей папке
        printf("%*s%s\n", head.level * INDENT, "-(D) ", head.name);

        struct dirent *dirp;
        while ((dirp = readdir(dp)) != NULL) {
            if (strcmp(dirp->d_name, CURRENT_DIR) == 0 || strcmp(dirp->d_name, PARENT_DIR) == 0) {
                continue;
            }

            struct stat statbuf;
            if (lstat(dirp->d_name, &statbuf) < 0) {
                printf(ERR_INFO_CALL_LSTAT);
                continue;
            }

            if (S_ISDIR(statbuf.st_mode) == 0) {
                //печатаем информацию о текущем файле
                printf("%*s%s\n", (head.level + 1) * INDENT, "-(F) ", dirp->d_name);
                continue;
            }

            //если досюда дошла программа, то dirp - папка
            struct ElementTree new_el;
            new_el.name = (char *) dirp->d_name;
            new_el.level = head.level + 1;
            stack.push(new_el);
        }
    } while(!stack.empty());

    return 0;
}

