#include <avr/io.h>
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "gamefunc.h"
#include "gamedisp.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30
#define LOOP_RATE 1000
#define SCROLL_RATE 20

//store global variables
int SENT = 0;
int REC = 0;
int game_done = 0;


void reset_game(void)
//Resets game globals variables
{
    SENT = 0;
    REC = 0;
    game_done = 0;
}

void display_game_result(int game_done, int display_score, char outcome, int score, char mine)
{
    //display game result, score, or my character choice
    if ((game_done == 1) && (display_score == 0)) {
        char *long_result_text = "";
        if (outcome == 'W') {
            long_result_text = "Winner";
        } else if (outcome == 'L') {
            long_result_text = "Loser";
        } else {
            long_result_text = "Tie";
        }
        display_text(long_result_text, 1);
        reset_game();
        pacer_wait();
    } else if (display_score == 1) {
        display_character(score+48);
    } else {
        display_character(mine);
    }
}

int main (void)
{
    //initialise drivers
    system_init ();
    solid_text_init();
    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);

    //initialise score and characters
    char mine = 'P';
    char you = 'P';
    char outcome = 'T';

    int display_score = 0;
    int score = 0;

    //debugging led setup
    DDRC |= (1<<2);
    DDRD &= ~(1<<7);

    start_screen();

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        if(SENT == 0) {
            //change my characters
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                mine = game_incr_char(mine);
            }

            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                mine = game_decr_char(mine);
            }
        }

        //send my character to other board
        if(navswitch_down_p(NAVSWITCH_PUSH)) {
            game_send(mine);
            SENT = 1;
        }

        if (REC == 0) {
            PORTC &= ~(1<<2);
            //receive character from other board
            if(ir_uart_read_ready_p()) {
                you = game_receive();
                if (game_char(you)) {
                    //toggle led
                    PORTC |= (1<<2);
                    REC = 1;
                }
            }
        }
        if(game_done == 0) {
            //check if game is finished
            if((REC == 1) && (SENT == 1)) {
                game_done = 1;
                outcome = game_get_results(mine, you);
                if (outcome == 'W') {
                    score++;
                }
            }
        }

        display_game_result(game_done, display_score, outcome, score, mine);

        if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            //force game reset for when board receives rougue chars or doesnt reset properly
            reset_game();
        }

        //toggles display score
        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            display_score = toggle_score(display_score);
        }
    }
}

