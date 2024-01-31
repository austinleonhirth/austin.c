/*
    Austin Leonhirth's personal c library
    Created: 1/22/2024

    austin.c
    "make" to build
    "make update" to add newest version into /bin
*/

#include <stdio.h>
#include <stdlib.h>
#include "count_change.c"
#include "thegame.c"
#include "slots.c"
#include "grapher.c"
#include <stdbool.h>

/* colors */
#define ANSI_COLOR_GREY1 "\x1b[38;5;242m"
#define ANSI_COLOR_GREY2 "\x1b[38;5;250m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* version */
#define v_color "\x1b[38;5;27m"
#define VERSION v_color"1.1"ANSI_COLOR_RESET

/* formatting */
#define FEATURE_COLOR "\x1b[38;5;153m"
#define COUNTER_COLOR "\x1b[38;5;27m"
#define INDENT ANSI_COLOR_RESET"  ㄴ"FEATURE_COLOR
#define SELECTION_F ""
#define INFO "["ANSI_COLOR_GREY1"INFO"ANSI_COLOR_RESET"] "

#define SELECTION_LINE SELECTION_F"Select "COUNTER_COLOR"number"ANSI_COLOR_RESET" > "

/* struct feature 
    holds the name of the feature and the function to call
*/
struct feature{
    char *name;
    void (*function)(void);
};

/* list of features (MODULAR; APPEND AS NECESSARY) */
struct feature features[] = {
     {"count_change",   count_change_f},
     {"the_gameington", thegame_f},
     {"slots",          slots_f},
     {"grapher_test",   graph_f}
};


/* main 
    allows the user to select a feature to run from the list of features
*/
int main(int argc, char *argv[])
{
    /* if a feature is not specified, list and allow the user to choose */
    if(argc == 1){
        printf("+----------------------------------+\n");
        printf("◾Welcome to Austin's Program ["VERSION"]\n"ANSI_COLOR_RESET);
        printf("  Features:\n");

        bool again = true;
        repeat:
        /* Feature List */
        int listSize = sizeof(features)/sizeof(features[0]);
        for(int i = 0; i < listSize; i++){
            printf(INDENT"%s "COUNTER_COLOR"%d\n", features[i].name, i+1);
        }
        printf(ANSI_COLOR_RESET"\n");

        /* Feature Selection */
        int feature;
        printf(SELECTION_LINE);
        while(scanf("%d", &feature) != 1 || feature < 1 || feature > sizeof(features)/sizeof(features[0])){
            printf("Invalid input\n"SELECTION_LINE);
            while(getchar() != '\n');
        }
        /* Feature begin*/
        printf(INFO"Entering "FEATURE_COLOR"%s"ANSI_COLOR_RESET"...\n", features[feature-1].name);
        features[feature-1].function();

        /* Feature end */
        printf("  Features:\n");
        if(again){goto repeat;}

        /* program end */
    }

    //TODO
    printf("\nFeature selection from command line not yet implemented :)\n\n");
    return 1;
    
}
