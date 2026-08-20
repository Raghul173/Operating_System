#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
   pid_t P2,P3;

   // Root process(P1)
   printf("P1 (Root Process) \n");
   printf("PID: %d \n", getpid());
   printf("Parent PID: %d \n\n", getppid());

   // Create child process P2
   P2 = fork();

   if(P2 < 0)
   {
      perror("Fork failed.");
      return 1;
   }

   else if(P2 == 0)
   {
      // Child Process(P2)
      printf("P2 (Child of P1) \n");
      printf("PID: %d \n", getpid());
      printf("Parent PID: %d \n\n", getppid());

      // Create P3
      P3 = fork();
      if(P3 < 0)
      {
         perror("Second fork failed");
         return 1;
      }
      else if(P3 == 0)
      {
         // Child process P3
         printf("P3 (Child of P2) \n");
         printf("PID: %d \n", getpid());
         printf("Parent PID: %d \n\n", getppid());
      }
      else
      {
         // P2 waits for P3
         wait(NULL);
      }
   }
   else
   {
      // P1 waits for P2
      wait(NULL);
   }
   return 0;
}
