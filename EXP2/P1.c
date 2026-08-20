#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 81

// Method 1: Count Vowels in a string

int count_vowels(const char *str) 
{
    int count = 0;
    
    for (int i = 0; str[i] != '\0'; i++) 
    {
        char ch = tolower((unsigned char)str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') count++;
    }
    return count;
}

// Method 2: Check if a string is a palindrome

int check_palindrome(const char *str) 
{
    int start = 0, end = strlen(str) - 1;
    if (end < 0) return 0;
    while (start < end) 
    {
        if (str[start++] != str[end--]) return 0;
    }
    return 1;
}

int main() {
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe initialization failed");
        return 1;
    }

    printf("P1 (Root Process) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

    // 1. Fork P2 (Child of P1)
    pid_t P2 = fork();
    if (P2 < 0) return perror("Fork P2 failed"), 1;

    if (P2 == 0) {
        printf("P2 (Child of P1) -> PID: %d, Parent PID: %d\n\n", getpid(), getppid());

        // 2. Fork P3 (Child of P2)
        pid_t P3 = fork();
        if (P3 < 0) return perror("Fork P3 failed"), 1;

        if (P3 == 0) {
            // --- P3 TASK ---
            close(pipe1[0]); close(pipe1[1]); close(pipe2[1]);
            char p3_str[BUFFER_SIZE];
            
            read(pipe2[0], p3_str, BUFFER_SIZE);
            close(pipe2[0]);

            printf("[P3] Received string: \"%s\"\n", p3_str);
            if (check_palindrome(p3_str)) printf("[P3] Result: The string IS a palindrome.\n\n");
            else printf("[P3] Result: The string IS NOT a palindrome.\n\n");
            return 0;
        }

        // --- P2 TASK ---
        close(pipe1[1]); close(pipe2[0]);
        char p2_str[BUFFER_SIZE];

        read(pipe1[0], p2_str, BUFFER_SIZE);
        close(pipe1[0]);

        printf("[P2] Received string. Number of vowels: %d\n\n", count_vowels(p2_str));

        write(pipe2[1], p2_str, strlen(p2_str) + 1);
        close(pipe2[1]);

        wait(NULL); // P2 waits for P3
        return 0;
    }

    // --- P1 TASK ---
    close(pipe1[0]); close(pipe2[0]); close(pipe2[1]);
    char input_str[BUFFER_SIZE];

    printf("[P1] Enter a string (max 80 chars): ");
    if (fgets(input_str, BUFFER_SIZE, stdin) != NULL) {
        input_str[strcspn(input_str, "\n")] = '\0';
    }

    write(pipe1[1], input_str, strlen(input_str) + 1);
    close(pipe1[1]);

    wait(NULL); // P1 waits for P2
    return 0;
}
