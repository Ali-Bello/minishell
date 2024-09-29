#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// int main() {
//     char *input;
//     int i = 0;
//     while ((input = readline("Enter command: ")) != NULL) {
//         if (input[0] != '\0') {
//             add_history(input);
//             printf("You entered: %s", input);
//         }
//         rl_redisplay();  // Refresh the display if needed
//         free(input);
//         if (i == 3)
//             rl_clear_history();
//         i++;
//     }

//     return 0;
// }

// int main() {
//     char *input;

//     while ((input = readline("Enter command: ")) != NULL) {
//         if (input[0] != '\0') {
//             add_history(input);
//             printf("You entered: %s", input);
//         }
        
//         // Print a message and update the display without disturbing the current input line
//         // printf("This is an external message!\n");
//        rl_on_new_line();  // Tell Readline we are now on a new line
//         //rl_redisplay();    // Redraw the input line

//         free(input);
//     }

//     return 0;
// }

// int main() {
//     char *input;

//     while ((input = readline("Enter command: ")) != NULL) {
//         if (strcmp(input, "anas") == 0) {
//             rl_replace_line("New replaced line!", 1); // Replace current input line
//             rl_redisplay(); // Redraw the line to reflect the changes
//         } else {
//             add_history(input);
//             printf("You entered: %s\n", input);
//         }
//         free(input);
//     }

//     return 0;
// }

// Function to replace the current input with a suggestion
void autocomplete(const char *suggestion) {
    rl_replace_line(suggestion, 1);  // Replace the current input with the suggestion
    rl_redisplay();                   // Redraw the line to show the new suggestion
}

int main() {
    char *input;

    // Main loop for accepting commands
    while (1) {
        input = readline("Enter command: ");

        if (input == NULL) {
            break;  // Exit if NULL input (Ctrl+D)
        }

        // If the user types "g" and presses Enter
        if (strcmp(input, "g") == 0) {
            autocomplete("git");  // Suggest "git" when "g" is entered
        } else {
            printf("You entered: %s\n", input);
        }

        free(input);  // Free the memory allocated for input
    }

    return 0;
}