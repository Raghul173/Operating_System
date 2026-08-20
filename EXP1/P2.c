#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
   int n, sum = 0;
   pid_t P2, P3;

   printf("Enter the limit: ");
   scanf("%d", &n);

   int numbers[n];

   for(int i = 0; i < n; i++)
   {
      printf("Enter number %d: ", i + 1);
      scanf("%d", &numbers[i]);
   }

   // -------------------------------------------------------------
   // 1. Create and Execute Left Child (P2)
   // -------------------------------------------------------------
   P2 = fork();

   if(P2 < 0)
   {
      perror("First fork failed");
      return 1;
   }
   else if(P2 == 0) // Inside Left Child (P2)
   {
      printf("\nP2 (Left child of P1 - Handles Odd Numbers) \n");
      printf("PID: %d \n", getpid());
      printf("Parent PID: %d \n", getppid());

      int sum_odd = 0;
      for(int i = 0; i < n; i++)
      {
         if(numbers[i] % 2 != 0)
         {
            sum_odd += numbers[i];
         }
      }
      printf("Sum of odd numbers: %d \n", sum_odd);
      exit(0); // Terminate P2 immediately
   }

   // PARENT (P1) WAITS FOR P2 TO FINISH BEFORE DOING ANYTHING ELSE
   wait(NULL);

   // -------------------------------------------------------------
   // 2. Create and Execute Right Child (P3)
   // -------------------------------------------------------------
   P3 = fork();

   if(P3 < 0)
   {
      perror("Second fork failed");
      return 1;
   }
   else if(P3 == 0) // Inside Right Child (P3)
   {
      printf("\nP3 (Right child of P1 - Handles Even Numbers) \n");
      printf("PID: %d \n", getpid());
      printf("Parent PID: %d \n", getppid());

      int sum_even = 0;
      for(int i = 0; i < n; i++)
      {
         if(numbers[i] % 2 == 0)
         {
            sum_even += numbers[i];
         }
      }
      printf("Sum of even numbers: %d \n", sum_even);
      exit(0); // Terminate P3 immediately
   }

   // PARENT (P1) WAITS FOR P3 TO FINISH
   wait(NULL);

   // -------------------------------------------------------------
   // 3. Parent Process (P1) Execution
   // -------------------------------------------------------------
   printf("\nP1 (Root Process - Handles Total Sum) \n");
   printf("PID: %d \n", getpid());
   printf("Parent PID: %d \n", getppid());

   for(int i = 0; i < n; i++)
   {
      sum += numbers[i];
   }
   printf("Total sum of %d numbers is: %d \n", n, sum);

   return 0;
}
