/** @file   gamefunc.c
    @author C.Aubrey J. Rule
    @date   14/10/19
    @brief  game specific display functions.
*/

#include "gamedisp.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30
#define LOOP_RATE 1000
#define SCROLL_RATE 30

void display_character(char character)
{
    /*Displays a single character for the purpose of displaying score
     * and choice*/
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void scrolling_text_init(void)
{
    /* Initialize tinygl text for scrolling */
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (SCROLL_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

void solid_text_init(void)
{
    /* Initialize tinygl text for not scrolling */
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
}

void display_text(char* string, int is_scrolling)
{
    /* Helper function for displaying text, either
        non scrolling or static scrolling based on second parameter */
    if (is_scrolling != 0) {
        scrolling_text_init();
    } else {
        solid_text_init();
    }

    tinygl_text (string);

    navswitch_update ();

    while (!navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
    }

    navswitch_update ();
}

void start_screen(void)
{
    /* Uses display_text for start screen **/
    display_text("PRESS BUTTON SOUTH TO START", 1);
    pacer_wait();
}

