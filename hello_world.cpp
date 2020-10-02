/* system header files */
#include <stdio.h>
#include <cstdlib>

int main(void){
    int cs = 107;
    if (cs == 107) {
        printf("Hello CS107!\n");
    }
    else {
        // for the purposes of checking CodeCov setup, this line never runs
        printf("This line will never run!");
    }

    return EXIT_SUCCESS;
}
