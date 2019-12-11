/** @file   gamefunc.c
    @author C.Aubrey J. Rule
    @date   14/10/19
    @brief  game specific display functions.
*/

#ifndef GAMEDISP_H
#define GAMEDISP_H

#include "gamedisp.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"

void display_character(char character);

void scrolling_text_init(void);

void solid_text_init(void);

void display_text(char* string, int is_scrolling);

void start_screen(void);

#endif


