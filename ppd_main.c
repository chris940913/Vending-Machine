/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2015 Assignment #2
 * Full Name        :  Yap Fui Yang
 * Student Number   : s3466760
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

#include "ppd_main.h"
#include "ppd_menu.h"
#include "ppd_options.h"
#include "ppd_utility.h"

/**
 * @file ppd_main.c contains the main function implementation and any 
 * helper functions for main such as a display_usage() function.
 **/

/**
 * manages the running of the program, initialises data structures, loads
 * data and handles the processing of options. The bulk of this function
 * should simply be calling other functions to get the job done.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
	if(argc != ARGSNUMS)
	{
		fprintf(stderr,"Error : Invalid command line args!");
		 fprintf(stderr, "Usage: %s <s> <coinsfile>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	/* represents the data structures to manage the system */
	BOOLEAN quit= FALSE;
	struct menu_item menu[NUM_OF_OPTS];
    struct ppd_system system;
	int menu_choice;
	
	
    /* init the system */
	system_init(&system);

    /* load data */
	load_data(&system, argv[1],argv[2]);
	
	/* test if everything has been initialised correctly */

	if(!system_init(&system) || !load_data(&system, argv[1],argv[2]))
	{
		fprintf(stderr,"ERROR, QUTING PROGRAM NOW...");
		return EXIT_FAILURE;
	}

	
    /* initialise the menu system */
	
	init_menu(menu);
	
	/* loop, asking for options from the menu */
	do{
		display_menu(menu);
		
		get_integer(&menu_choice,LEN_USER_INPUT, MIN_OPT,MAX_OPT);
		
		menu[menu_choice-1].function(&system);
		
		if(menu_choice==3 || menu_choice== 9)
		{
			quit=TRUE;
		}
		
	}while(!quit);
	
	system_free(&system);
	
    return EXIT_SUCCESS;
}
