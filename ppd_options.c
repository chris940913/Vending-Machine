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

#include "ppd_options.h"

/**
 * @file ppd_options.c this is where you need to implement the main 
 * options for your program. You may however have the actual work done
 * in functions defined elsewhere. 
 * @note if there is an error you should handle it within the function
 * and not simply return FALSE unless it is a fatal error for the 
 * task at hand. You want people to use your software, afterall, and
 * badly behaving software doesn't get used.
 **/

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this particular function should never fail.
 **/
BOOLEAN display_items(struct ppd_system * system)
{
	struct ppd_node *curr;
	struct ppd_stock *data;
	
	if(system-> item_list-> count == 0)
	{
		printf("No items are found in this PPD.\n");
		return TRUE;
	}
	
	curr= system-> item_list-> head;
	
	printf("\n Items Menu\n");
	printf("--------------\n");
	printf("%s    |%s                                      |%s  |%s   ", "ID","Name","Available", "Price");
	printf("\n--------------------------------------------------------------------------\n");
	
	while(curr != NULL)
	{
		data = curr->data;
        printf("%-*s ", 1, data->id);
        printf("| %-*s ", 40, data->name);
        printf("| %-*u ", (int)strlen("Available"), data->on_hand);
        printf("| $%3u.%02u\n", data->price.dollars, data->price.cents);
		
		curr= curr->next;
	}
	putchar('\n');
	
    
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
BOOLEAN purchase_item(struct ppd_system * system)
{
    char input_id[10];
	char input_money[10];
	BOOLEAN read_id= FALSE;
	BOOLEAN paid = FALSE;
	struct ppd_stock *item= NULL;
	int amount;
	unsigned current;
	struct coin coins_entered[NUM_DENOMS];
	
	init_coins(coins_entered);
	
	printf("\nPurchase Item\n");
	printf("---------------\n");
	
	/* match user input id from system and print details + price*/
	while(!read_id)
	{
		printf("Please enter the id of the item you wish to purchase:\n");
	    get_string(input_id, INPUTLEN);
		
		if(match_input_id(system->item_list,input_id, &item))
		{
			read_id= TRUE;
			printf("You have selected %s - %s\n", item->name,item->desc);
			printf("This will cost you $%u.%02u.\n\n",
                            item->price.dollars, item->price.cents);
			amount= item->price.dollars*100 + item->price.cents;
		}
		else
		{
			printf("YOur input '%s' doesnt match with any item ID in system, please retype!\n",input_id);
		}
		
	}
	
	printf("Please hand over the money – type in the value of each note/coin in cents.\n");
	
	/*Collect money until it's fully paid*/
	while(!paid)
	{
		printf("You still need to give us $%d.%02d, insert money: ",amount / 100, amount % 100);
		get_string(input_money,INPUTLEN);
		/*convert the price string to unsigned int*/
		if(string_to_cents(input_money, &current))
		{
			amount-= current;
			
			
			add_denom_to_system(coins_entered,current,1);
			add_denom_to_system(system->cash_register,current,1);
			
			if(amount <=0)
			{
				paid=TRUE;
				printf("Thank you here is your %s\n", item->name);
				printf("Please come again soon\n");
				item->on_hand--;
			}
			
		}
		else if(string_to_unsigned(input_money, &current))
		{
			printf("Error $%u.%02u is not a valid denomination of money.\n", current/100, current %100);
		}
		else
		{
			printf("invalid input \n ");
		}
		
		
		
	}
	
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system)
{
    
    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/
BOOLEAN add_item(struct ppd_system * system)
{
	struct ppd_stock *new_item;
	char id[ID_LEN+1],name[N_LEN], desc[D_LEN];
	char price[P_LEN];
	char *dollars_string, *cents_string;
	unsigned dollars,cents;
	int default_on_hand = 20;
	
	 
	
	printf("---------\n");
	
	new_item = malloc(sizeof *new_item);
    memset(new_item, 0, sizeof *new_item);
	
	generate_id(id, system->item_list);
	
	strcpy(new_item->id,id);
	printf("This new meal item will have the Item id of %s.\n", id);
	
	printf("Enter the item name:\n");
	get_string(name,N_LEN);
	strcpy(new_item->name, name);
	
	printf("Enter item description\n");
	get_string(desc,D_LEN);
	strcpy(new_item->desc,desc);
	
	printf("\nEnter the price for this item\n");
	get_string(price,P_LEN);
	/*conver price to unsigned var*/
	dollars_string= strtok(price,".");
	cents_string= strtok(NULL,".");
	
	string_to_unsigned(dollars_string,&dollars);
	string_to_unsigned(cents_string, &cents);
	
	new_item->price.dollars= dollars;
	new_item->price.cents=cents;
	new_item->on_hand=default_on_hand;
	
	add_node_linkedList(system->item_list, new_item);
	
	printf("Item has been added to system\n");
	
	
    
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system)
{
    char input_id[ID_LEN+1];
	BOOLEAN valid_id= FALSE;
	struct ppd_stock deleted_item;
	
	while(!valid_id)
	{
	  printf("Enter the item id of the item to remove from the menu:\n");
	  get_string(input_id,ID_LEN);
	  if(delete_item(system->item_list, input_id, &deleted_item)){
		  valid_id=TRUE;
		  printf("\n %s , %s, %s has been removed from the system.\n", deleted_item.id, deleted_item.name, deleted_item.desc);
	  }
	  else{
		  printf("Invalid item id input\n");
	  }
	}
	
	
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_stock(struct ppd_system * system)
{
    struct ppd_node *node = system->item_list->head;
	
	while(node!= NULL)
	{
		if(node->data)
		node->data->on_hand= DEFAULT_ONHAND;
	node= node->next;
	}
	
	printf("Item has set to default counts.\n");
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_coins(struct ppd_system * system)
{
    struct coin *c =system->cash_register;
	unsigned coins;
	
	for(coins=0; coins< NUM_DENOMS; ++coins)
	{
		c[coins].count=DEFAULT_COIN;
	}
	printf("Coins has set to default count\n");
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
	
	int i;
	char coin_display[LEN_C_DISPLAY];
    printf("Coins Summary\n");
	printf("----------------------\n");
	printf("Denomination   |  Count\n");
	printf("-----------------------\n");
	
	
	for(i=NUM_DENOMS - 1; i >= 0; --i)
	{
		switch(system->cash_register[i].denom)
		{
			case FIVE_CENTS:
            strcpy(coin_display, "5 cents");
            break;
         case TEN_CENTS:
            strcpy(coin_display, "10 cents");
            break;
         case TWENTY_CENTS:
            strcpy(coin_display, "20 cents");
            break;
         case FIFTY_CENTS:
            strcpy(coin_display, "50 cents");
            break;
         case ONE_DOLLAR:
            strcpy(coin_display, "1 dollar");
            break;
         case TWO_DOLLARS:
            strcpy(coin_display, "2 dollar");
            break;
         case FIVE_DOLLARS:
            strcpy(coin_display, "5 dollar");
            break;
         case TEN_DOLLARS:
            strcpy(coin_display, "10 dollar");
            break;
			
		}
		printf("%-15s|%6d\n", coin_display, system->cash_register[i].count);
	}
	
	
    return TRUE;
}
BOOLEAN quit (struct ppd_system *system)
{
	printf("Exiting, all program data will not be save.\n");
	return TRUE;
}
