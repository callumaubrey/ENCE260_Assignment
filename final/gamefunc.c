/** @file   gamefunc.c
    @author C.Aubrey J. Rule
    @date   14/10/19
    @brief  Main game actions and processing.
*/

#include "ir_uart.h"
#include "gamefunc.h"


int toggle_score(int score_state)
/*toggles state to determine whether to display score*/
{
    if (score_state == 0) {
        score_state = 1;
    } else {
        score_state = 0;
    }
    return score_state;
}


void game_send(char choice)
/*sends the character choice to other board*/
{
    ir_uart_putc(choice);
}

int game_char(char character) {
    int is_char = 0;
    if ((character == 'P') || (character == 'R') || (character == 'S')) {
        is_char = 1;
    }
    return is_char;
}

char game_receive(void)
/*receives character from other board, returns character if it is R, P,
 * or S*/
{
    char  read = ir_uart_getc();
    char you = '\0';
    //update only if R, P, or S is received
    if(read == 'R' || read == 'S' || read == 'P') {
        you = read;
    }
    return you;
}

char game_get_results(char mine, char you)
/*Processes two characters and returns a game state character, W for win,
 * T for a tie, and L for a loss*/
{
    char outcome = '\0';
    if(((mine == 'P') && (you == 'R')) || ((mine == 'R') && (you == 'S')) || ((mine == 'S') && (you == 'P'))) {
        outcome = 'W';
    } else if(mine == you) {
        outcome = 'T';
    } else {
        outcome = 'L';
    }
    return outcome;
}


char game_incr_char(char mine)
/*changes character in the order P->R->S->P*/
{
    if (mine == 'P') {
        mine = 'R';
    } else if (mine == 'R') {
        mine = 'S';
    } else {
        mine = 'P';
    }
    return mine;
}

char game_decr_char(char mine)
/*changes character in the order S->R->P->S*/
{
    if (mine == 'P') {
        mine = 'S';
    } else if (mine == 'R') {
        mine = 'P';
    } else {
        mine = 'R';
    }
    return mine;
}
