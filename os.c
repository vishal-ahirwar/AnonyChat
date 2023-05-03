#include<stdio.h>

int main()
{
    #ifdef _WIN32
    printf("microsoft windows os\n");
    #else
    printf("unix based os\n");
    #endif
    
    return 0;
}