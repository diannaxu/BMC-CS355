//Cecilia Zhang, Cecilia Chen, Paprika Chen

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int main(void) {
    // a structure that contains the modes of the terminal
    // can be get by tcgetattr() and then changed by tcsetattr
    struct termios orig_termios, new_termios;
    char c;

    // Get the current terminal settings
    if (tcgetattr(STDIN_FILENO, &orig_termios) < 0) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Initialize the new setting as the original one, ready to be changed
    new_termios = orig_termios;

    // Modify the new settings to disable canonical mode and echo
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Apply the new settings from STDIN
    // TCSANOW means apply this change immediately
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) < 0) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    printf("Enter a character: ");

    // Read a single character
    if (read(STDIN_FILENO, &c, 1) < 0) {
        perror("read");
        // Attempt to restore the original settings before exiting
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
        exit(EXIT_FAILURE);
    }

    // Restore the original settings
    if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios) < 0) {
        perror("tcsetattr restore");
        exit(EXIT_FAILURE);
    }

    printf("\nYou entered: %c\n", c);

    return EXIT_SUCCESS;
}
