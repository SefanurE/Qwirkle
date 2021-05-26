#ifndef ASSIGN1_TILECODES_H
#define ASSIGN1_TILECODES_H

// Colours
#define RED    'R'
#define ORANGE 'O'
#define YELLOW 'Y'
#define GREEN  'G'
#define BLUE   'B'
#define PURPLE 'P'
#define COLOURS_COUNT 6

// Colour Escape Codes
#define RED_ESCAPE "\u001b[31m"
#define ORANGE_ESCAPE "\033[48;5;000;38;5;202m"
#define YELLOW_ESCAPE "\033[48;5;000;38;5;226m"
#define GREEN_ESCAPE "\u001b[32m"
#define BLUE_ESCAPE "\u001b[34m"
#define PURPLE_ESCAPE "\u001b[35m"
#define RESET_ESCAPE "\u001b[0m"

// Shapes
#define CIRCLE    1
#define STAR_4    2
#define DIAMOND   3
#define SQUARE    4
#define STAR_6    5
#define CLOVER    6
#define SHAPES_COUNT 6


#endif // ASSIGN1_TILECODES_H
