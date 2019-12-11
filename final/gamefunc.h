#ifndef GAMEFUNC_H
#define GAMEFUNC_H


#include "ir_uart.h"

//sets the state to display score
int toggle_score(int score_state);


//sends character choice
void game_send(char choice);


//receives character
char game_receive(void);


//determines outcome of round
char game_get_results(char mine, char you);


//switches character choice (increaseing) between P,R, and S
char game_incr_char(char mine);

//switches character choice (decreasing) between P,R, and S
char game_decr_char(char mine);

//checks if it is one of our game characters
int game_char(char character);

#endif
