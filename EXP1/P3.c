#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    pid_t P2, P3, P4, P6, P7, P8;

    // -------------------------------------------------------------
    // Root Process (P1)
    // -------------------------------------------------------------
    printf("P1 (Root Process)\n");
    printf("PID: %d\n", getpid());
    printf("Parent PID: %d\n\n", getppid());

    // -------------------------------------------------------------
    // Create Left Child (P2)
    // -------------------------------------------------------------
    P2 = fork();

    if(P2 < 0)
    {
        perror("First fork failed");
        return 1;
    }
    else if(P2 == 0)
    {
        printf("P2 (Child of P1)\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n\n", getppid());

        // Create P4
        P4 = fork();

        if(P4 < 0)
        {
            perror("Second fork failed");
            return 1;
        }
        else if(P4 == 0)
        {
            printf("P4 (Child of P2)\n");
            printf("PID: %d\n", getpid());
            printf("Parent PID: %d\n\n", getppid());

            // Create P6
            P6 = fork();

            if(P6 < 0)
            {
                perror("Third fork failed");
                return 1;
            }
            else if(P6 == 0)
            {
                printf("P6 (Child of P4)\n");
                printf("PID: %d\n", getpid());
                printf("Parent PID: %d\n\n", getppid());

                exit(0);
            }
            else
            {
                wait(NULL);
                exit(0);
            }
        }
        else
        {
            wait(NULL);
            exit(0);
        }
    }

    // Parent waits for P2
    wait(NULL);

    // -------------------------------------------------------------
    // Create Right Child (P3)
    // -------------------------------------------------------------
    P3 = fork();

    if(P3 < 0)
    {
        perror("Fourth fork failed");
        return 1;
    }
    else if(P3 == 0)
    {
        printf("P3 (Child of P1)\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n\n", getppid());

        // Create P7
        P7 = fork();

        if(P7 < 0)
        {
            perror("Fifth fork failed");
            return 1;
        }
        else if(P7 == 0)
        {
            printf("P7 (Child of P3)\n");
            printf("PID: %d\n", getpid());
            printf("Parent PID: %d\n\n", getppid());

            exit(0);
        }
        else
        {
            wait(NULL);

            // Create P8
            P8 = fork();

            if(P8 < 0)
            {
                perror("Sixth fork failed");
                return 1;
            }
            else if(P8 == 0)
            {
                printf("P8 (Child of P3)\n");
                printf("PID: %d\n", getpid());
                printf("Parent PID: %d\n\n", getppid());

                exit(0);
            }
            else
            {
                wait(NULL);
                exit(0);
            }
        }
    }
    else
    {
        wait(NULL);
    }

    return 0;
}
