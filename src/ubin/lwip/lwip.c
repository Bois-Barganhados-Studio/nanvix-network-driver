#include <stdio.h>
#include <lwip/init.h>


int main(){
    printf("LWIP starting ... \n");
    lwip_init();
    printf("LWIP started! \n");
    printf("Test passed! \n");
    return 0;
}