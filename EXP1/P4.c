#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   pid_t P2, P3, P4, P7, P8, P6, P5;

   // 1. Root Process (P1)
   printf("P1 (Root Process) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

   // Create child process P2
   P2 = fork();

   if (P2 < 0) {
      perror("Fork for P2 failed");
      return 1;
   }
   else if (P2 == 0) {
      // 2. Child Process (P2)
      printf("P2 (Child of P1) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

      // Create P3
      P3 = fork();
      if (P3 < 0) {
         perror("Fork for P3 failed");
         return 1;
      }
      else if (P3 == 0) {
         // 3. Child Process (P3)
         printf("P3 (Child of P2) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

         // Create P4
         P4 = fork();
         if (P4 < 0) {
            perror("Fork for P4 failed");
            return 1;
         }
         else if (P4 == 0) {
            // 4. Child Process (P4)
            printf("P4 (Child of P3) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

            // Create P7
            P7 = fork();
            if (P7 < 0) {
               perror("Fork for P7 failed");
               return 1;
            }
            else if (P7 == 0) {
               // 5. Child Process (P7)
               printf("P7 (Child of P4) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

               // P7 creates its left child: P8
               P8 = fork();
               if (P8 < 0) {
                  perror("Fork for P8 failed");
                  return 1;
               }
               else if (P8 == 0) {
                  // 6. Child Process (P8)
                  printf("P8 (Left Child of P7) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());
                  return 0; // P8 finishes execution
               }

               // P7 creates its right child: P6
               P6 = fork();
               if (P6 < 0) {
                  perror("Fork for P6 failed");
                  return 1;
               }
               else if (P6 == 0) {
                  // 7. Child Process (P6)
                  printf("P6 (Right Child of P7) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

                  // P6 creates its child: P5
                  P5 = fork();
                  if (P5 < 0) {
                     perror("Fork for P5 failed");
                     return 1;
                  }
                  else if (P5 == 0) {
                     // 8. Child Process (P5)
                     printf("P5 (Child of P6) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());
                     return 0; // P5 finishes execution
                  }
                  else {
                     // P6 waits for its child P5
                     wait(NULL);
                  }
                  return 0; // P6 finishes execution
               }

               // P7 waits for both of its direct children (P8 and P6) to finish
               wait(NULL);
               wait(NULL);
               return 0; // P7 finishes execution
            }
            else {
               // P4 waits for P7
               wait(NULL);
            }
            return 0; // P4 finishes execution
         }
         else {
            // P3 waits for P4
            wait(NULL);
         }
         return 0; // P3 finishes execution
      }
      else {
         // P2 waits for P3
         wait(NULL);
      }
      return 0; // P2 finishes execution
   }
   else {
      // P1 waits for P2
      wait(NULL);
   }

   return 0;
}
