#include <stdio.h>
#include <unistd.h>


int main(void)
{
    while (1)
    {
        printf(" cyber_deamon : Surveillance active" );
        fflush(stdout);
        printf("\n");
	sleep(5);
    }
    return 0;
}
