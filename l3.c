#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void tryOpenFile(const char* fileName) {
        FILE* file = NULL;
        file = fopen(fileName, "r");
        if (file == NULL) {
                perror("Can't open file");
                return;
        }
        printf("File opened successfully \n");


        const int FCLOSE_SUCCESS = 0;
        if (fclose(file) != FCLOSE_SUCCESS) {
                perror("Can't close file");
                return;
        }
}
//=======================
int main(int argc, char** argv) {


        printf("Real user ID: %ld,  effective user ID: %ld\n", getuid(), geteuid());

        const int ARGC_CORRECT = 2;
        if (argc != ARGC_CORRECT) {
                perror("Input  file name ");
                return EXIT_FAILURE;
        }

        printf("Trying to open the file: \n");

        tryOpenFile(argv[1]);

        const int SETUID_ERR = -1;
        uid_t uid = getuid();
        int setuidResult = setuid(uid); //sets the effective user ID
        if (setuidResult == SETUID_ERR) {
                perror("setuid error. Wrong id");
        }

        printf("After using setuid \n");
        printf("Real user ID %ld \n", getuid());
        printf("Effective user ID %ld \n", geteuid());

        printf("Trying to open the file: \n");
        tryOpenFile(argv[1]);

        return EXIT_SUCCESS;
}
