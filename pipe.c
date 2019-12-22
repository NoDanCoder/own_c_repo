#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <math.h> 

typedef struct nums{
    int a;
    int b;
    int check;
} nums;

void parent( int com[], nums opr )
{
    for (int i = 0; i < 10; i++)
    {
        opr.a = pow(2, i), opr.b = pow(2, i), opr.check = 0;
        printf("cuanto da %d + %d? hijo?\n", opr.a, opr.b);
        write(com[1], &opr, sizeof(opr));
        sleep(1);
        read(com[0], &opr, sizeof(opr));
    }
    close(com[1]);
    wait(NULL);
}

void child( int com[], nums opr )
{
    for (int i = 0; i < 10; i++)
    {
        read(com[0], &opr, sizeof(opr));
        printf("it's %d dad :)\n", opr.a + opr.b);
        opr.check = 1;
        write(com[1], &opr, sizeof(opr));
        sleep(1);
    }
    close(com[1]);
}

int main()
{
    nums opr;
    int com[2];
    
    if ( !pipe(com) )
        if ( fork() )
            parent( com, opr );
        else
            child( com, opr );

    return 0;
}
