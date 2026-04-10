// C program to implement Random Snakes and Ladders Game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Roll dice
int roll_die()
{
    return rand() % 6 + 1;
}

// Global variables
int player_1 = 0, player_2 = 0;
int snakesAndLadders[101] = { 0 };
char sl_buf[20];

// Forward declarations
void print_board();
void print_square(int square);
void generate_snakes_ladders();
int movePlayer(int currentPlayer, int roll);



// Generate random snakes and ladders
void generate_snakes_ladders()
{
    int count = 0;

    // Generate 5 ladders
    while (count < 5) //The no of ladders can be changed by changing the value of 5
    {
        int start = rand() % 80 + 2;          // 2–81
        int end = start + (rand() % 20 + 5);  // climb 5–24

        if (end >= 100) continue;
        if (snakesAndLadders[start] != 0) continue;

        snakesAndLadders[start] = end - start;
        count++;
    }

    count = 0;

    // Generate 5 snakes
    while (count < 5) //The no of snakes can be changed by changing the value of 5
    {
        int start = rand() % 80 + 20;          // 20–99
        int end = start - (rand() % 20 + 5);   // go down 5–24

        if (end <= 1) continue;
        if (snakesAndLadders[start] != 0) continue;

        snakesAndLadders[start] = end - start;
        count++;
    }
}



// Print a single square
void print_square(int square)
{
    if (square == player_1)
        printf("*#P1*   ");
    else if (square == player_2)
        printf("*#P2*   ");
    else if (snakesAndLadders[square] > 0)
    {
        sprintf_s(sl_buf, sizeof(sl_buf), "%d(L)", square);
        printf("%-8s", sl_buf);
    }
    else if (snakesAndLadders[square] < 0)
    {
        sprintf_s(sl_buf, sizeof(sl_buf), "%d(S)", square);
        printf("%-8s", sl_buf);
    }
    else
        printf("%-8d", square);
}



// Print board in zig-zag format
void print_board()
{
    int leftToRight = 0;

    for (int row = 100; row >= 10; row -= 10)
    {
        if (leftToRight == 0)
        {
            for (int i = row; i > row - 10; i--)
                print_square(i);
        }
        else
        {
            for (int i = row - 9; i <= row; i++)
                print_square(i);
        }

        printf("\n\n");
        leftToRight = !leftToRight;
    }
}



// Move player
int movePlayer(int currentPlayer, int roll)
{
    int newPosition = currentPlayer + roll;

    if (newPosition > 100)
        return currentPlayer;

    if (snakesAndLadders[newPosition] != 0)
    {
        int jump = snakesAndLadders[newPosition];
        newPosition += jump;

        if (jump > 0)
            printf("Ladder! Climb up to %d\n", newPosition);
        else
            printf("Snake! Slide down to %d\n", newPosition);
    }

    return newPosition;
}



// Main function
int main()
{
    srand(time(0));

    generate_snakes_ladders();

    int currentPlayer = 1;
    int won = 0;
    char c;

    printf("===== Snake and Ladder Game =====\n\n");
    print_board();

    while (!won)
    {
        printf("\nPlayer %d, press Enter to roll the die...", currentPlayer);
        c= getchar();

        int roll = roll_die();
        printf("\nYou rolled a %d\n", roll);

        if (currentPlayer == 1)
        {
            player_1 = movePlayer(player_1, roll);
            printf("Player 1 is now at square %d\n\n", player_1);
            print_board();

            if (player_1 == 100)
            {
                printf("Player 1 wins!\n");
                won = 1;
            }
        }
        else
        {
            player_2 = movePlayer(player_2, roll);
            printf("Player 2 is now at square %d\n\n", player_2);
            print_board();

            if (player_2 == 100)
            {
                printf("Player 2 wins!\n");
                won = 1;
            }
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
