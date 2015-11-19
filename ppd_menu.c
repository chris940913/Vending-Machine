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

#include "ppd_menu.h"
/**
 * @file ppd_menu.c handles the initialised and management of the menu 
 * array
 **/

/**
 * @param menu the menu item array to initialise
 **/
void init_menu( struct menu_item* menu)
{
	int i;
	
	/* Create array of name in strct menu_item*/
	struct menu_item menus[]={
		{"1. Display Items",&display_items},{"2. Purchase Item",&purchase_item}, {"3. Save and Exit",&save_system}, {"4. Add Item",&add_item}, {"5.Remove Item",&remove_item},        {"6. Display Coins",&display_coins}, {"7. Reset Stock",&reset_stock},{"8. Reset Coins",&reset_coins},
	      {"9. Abort Program", &quit}
		
		};
	
	
	
	
	/* Assign the struct data*/
	for(i = 0; i < NUM_OF_OPTS; i ++){
		
		strcpy(menu[i].name, menus[i].name);
		
		menu[i].function= menus[i].function;
	}
	
	
	
	
	
}

void display_menu(struct menu_item * menu)
{
	int i;
		printf("Main Menu:\n");
	
	for (i=0; i< NUM_OF_OPTS; i++)
	{
		printf("%s\n", menu[i].name);
		if (menu[i].name == menu[2].name)
		{
			printf("Administrator-Only Menu: \n");
		}
	}
	printf("select your option(1-9) : \n");
}
