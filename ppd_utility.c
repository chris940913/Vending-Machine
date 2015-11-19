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

#include "ppd_utility.h"
/**
 * @file ppd_utility.c contains implementations of important functions for
 * the system. If you are not sure where to implement a new function, 
 * here is probably a good spot.
 **/

void read_rest_of_line(void)
{
    int ch;
    /* keep retrieving characters from stdin until we
     * are at the end of the buffer
     */
    while(ch = getc(stdin), ch!='\n' && ch != EOF)
        ;
    /* reset error flags on stdin */
    clearerr(stdin);
}


/**
 * @param system a pointer to a @ref ppd_system struct that contains
 * all the data in the system we are manipulating
 * @param coins_name the name of the coins file
 * @param stock name the name of the stock file
 **/
BOOLEAN load_data(struct ppd_system * system ,  const char * stock_name, const char * coins_name)
{
	system->stock_file_name = stock_name;
	system->coin_file_name = coins_name;
	
	FILE *StockFP, *CashFP;
	int ch;
	enum field_type f_type;
	char stock[SLEN];
	int dollars, cents;
	float temp_cents;
	struct ppd_stock *item;
	BOOLEAN denom_update= TRUE;
	int cash_pos = NUM_DENOMS-1;
	enum denomination denom;
	char temp_denom[TEMPDENOM];
	char temp_coins[TEMPCOINS];
	
	/*load stock*/ 
	StockFP=fopen(system->stock_file_name,"r");
	
	/*keep looping until end of file*/
	while((ch=fgetc(StockFP)) != EOF)
	{
		int i =0;
		f_type=ID;
		
		item = malloc(sizeof(struct ppd_stock));
		
		while(TRUE){
			stock[i]=ch;
			
			if(ch=='|' || ch == '\n' || ch== EOF)
			{
				stock[i] = '\0';
				
				switch(f_type){
					case ID:
					strcpy(item->id, stock);
					break;
					
					case NAME:
					strcpy(item->name,stock);
					break;
					
					case DESC:
					strcpy(item->desc, stock);
					break;
					
					case ON_HAND:
					item->on_hand = atoi(stock);
					break;
					
					case PRICE:
					dollars = atoi(stock);
					temp_cents=atof(stock)-dollars;
					cents=(int)(temp_cents*100);
					item->price.dollars=dollars;
					item->price.cents=cents;
					break;
					
				}
				
				f_type++;
				i=0;
				
				
				
			}else{
				i++;}
			
			if(ch=='\n' || ch== EOF){break;}
			ch=fgetc(StockFP);
		}
		add_node_linkedList(system->item_list, item);
	}
	fclose(StockFP);
	
	
	/*load coins*/

	CashFP=fopen(system->coin_file_name,"r");
	if(!CashFP)
	{
		return FALSE;
	}
	
	while((ch=fgetc(CashFP))!= EOF){
		int i =0;
		denom_update=TRUE;
		
		while(ch != '\n'){
			if(ch==','){
				denom_update=FALSE;
				temp_denom[i]='\0';
				i=0;
			}else if(denom_update==TRUE){
				temp_denom[i]=ch;
				i++;
			}else{
				temp_coins[i]=ch;
				i++;
			}
			ch=fgetc(CashFP);
		}
		temp_coins[i]='\0';
		
		denom=string_to_denom(temp_denom);
		system->cash_register[cash_pos].denom= denom;
		system->cash_register[cash_pos].count= atoi(temp_coins);
		
		cash_pos--;
		
	}
	fclose(CashFP);
	
	       

    return TRUE;    
} 
	
	
	
   


/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/
BOOLEAN system_init(struct ppd_system * system)
{
	
	
	memset(system,0,sizeof *system);
	
	/* allocate memory for struct ppd_list, return false if fail*/
	system->item_list= malloc(sizeof *(system->item_list));
	if(!system->item_list)
	{
		return FALSE;
	}
	
	system->item_list->head= NULL;
	system->item_list->count= 0;
	
	/*init array of coins*/
	
	init_coins(system->cash_register);
	
    return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/
void system_free(struct ppd_system * system)
{
	struct ppd_node *node,*temp;
	
	node= system->item_list->head;
	temp=NULL;
	while(node!=NULL)
	{
		temp=node;
		node=node->next;
		free(temp->data);
		free(temp);
	}
	free(system->item_list);
	system->item_list=NULL;
	
	
}

/* add node to ppd linked list*/
BOOLEAN add_node_linkedList(struct ppd_list *list, struct ppd_stock *item){
	
	struct ppd_node *node, *prev, *curr;
	
	if(item ==NULL || list==NULL){
		return FALSE;
	}
	
	prev = NULL;
	curr=list->head;
	
	node=malloc(sizeof *node);
	if(!node)
	{
		printf("memory error");
		return FALSE;
	}
	
	memset (node, 0, sizeof *node);
	
	/*insert item to new node*/
	node ->data=item;
	
	while(curr!= NULL && strcmp(item->name, curr->data->name)>0 )
	{
		prev=curr;
		curr= curr->next;
	}
	
	node->next = curr;
	if(prev== NULL)
	{
		list->head= node;
	}
	else{
		prev->next= node;
	}
	list->count +=1;
		
	
	return TRUE;
}





/*Reference from lecture sample code @getIntger-basic.c  */
int get_integer(int *integer, int length, int min, int max)
{
	 int finished = FALSE;
    char tempString[30];
    int tempInteger = 0;
    char* endPtr;

    
    do {
        
        fgets(tempString, length + 2, stdin);

        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("Input was too long.\n");
            read_rest_of_line();

        } else {
			tempString[strlen(tempString) - 1] = '\0';
			
        tempInteger = (int) strtol(tempString, &endPtr, 10);
        
        
            if (strcmp(endPtr, "") != 0) {
                printf("Input was not numeric.\n");
      
            } else if (tempInteger < min || tempInteger > max) {
                printf("Input was not within range %d - %d.\n", min, max);
       
            } else {
                finished = TRUE;
            }
        }
    } while (finished == FALSE); 

	*integer = tempInteger;
   
    return TRUE;
}

int get_string(char* string, unsigned length) 
{
   int finished = FALSE;
   char tempString[30];

  
   do
   {
      
      fgets(tempString, length + 2, stdin);

     
      if (tempString[strlen(tempString) - 1] != '\n')
      {
         printf("Input was too long.\n");
         read_rest_of_line();
      }
      else
      {
         finished = TRUE;
      }

   } while (finished == FALSE);

   tempString[strlen(tempString) - 1] = '\0';
   
  
   strcpy(string, tempString);

   return TRUE;
}
BOOLEAN match_input_id(struct ppd_list * list, char *id, struct ppd_stock **item){
	
	struct ppd_node *node = list->head;
	
	while(node != NULL && strcmp(id, node->data->id)!= 0)
	{
		node= node->next;
	}
	if(node == NULL)
	{
		
		return FALSE;
		
		
	}
	*item = node->data;
	return TRUE;
	
	
	
	
	
}

void init_coins(struct coin coins[])
{
    int i;
    
    for(i = 0; i < NUM_DENOMS; i++)
    {
        
        coins[i].denom = i;
        coins[i].count = 0;
    }
}


BOOLEAN add_denom_to_system(struct coin c[], unsigned denom, unsigned count)
  {
	  
	  switch(denom)
	  {
		  case 5:
		  add_coins(c, FIVE_CENTS,count);
		  break;
		  
		  case 10:
		  add_coins(c,TEN_CENTS,count);
		  break;
		  
		  case 20:
		  add_coins(c, TWENTY_CENTS,count);
		  break;
		  
		  case 50:
		  add_coins(c,FIFTY_CENTS,count);
		  break;
		  
		  case 100:
		  add_coins(c, ONE_DOLLAR,count);
		  break;
		  
		  case 200:
		  add_coins(c, TWO_DOLLARS,count);
		  break;
		  
		  case 500:
		  add_coins(c,FIVE_DOLLARS,count);
		  break;
		  
		  case 1000:
		  add_coins(c, TEN_DOLLARS, count);
		  default:
		  return FALSE;
		  
	  }
	  return TRUE;
	  
  }
  
void add_coins(struct coin c[], enum denomination denom, unsigned count){
	 
	 int i;
	 
	 for(i= 0; i < NUM_DENOMS; i ++)
	 {
		if(c[i].denom== denom)
		{
			c[i].count+= count;
		}
		 
	 }
	 
	 
 }
 
BOOLEAN string_to_cents(char *c_string, unsigned *cents){
	 
	 unsigned u_cents;
	 
	 if(!string_to_unsigned(c_string, &u_cents))
	 {
		 return FALSE;
	 }
	 
	 if(u_cents==5 || u_cents== 10 || u_cents== 20 || u_cents== 50|| u_cents==100
	 || u_cents==200 || u_cents== 500 || u_cents== 1000)
	 {
		 *cents= u_cents;
		 return TRUE;
	 }
	 return FALSE;
 }

BOOLEAN string_to_unsigned(char *s, unsigned *u)
 {
	 if(!is_unsigned(s))
	 {
		 return FALSE;
	 }
	 
	 *u=(unsigned)strtol(s, NULL,10);
	 return TRUE;
 }
 
BOOLEAN is_unsigned(char *s){
	 
	 int i;
	 char *end_ptr;
	 
	 i=(int)strtol(s,&end_ptr,10);
	 if(i<0||strcmp(end_ptr, "")!= 0)
	 {
		 return FALSE;
	 }
	 return TRUE;
 }
 
void generate_id(char *new_id, struct ppd_list *list){
	 struct ppd_node *node = list->head;
	 unsigned highest_id= 0;
	 unsigned current_id;
	 
	 while(node!= NULL)
	 {
		 string_to_unsigned((node->data->id)+1, &current_id);
		 
		 if(current_id> highest_id)
		 {
			 highest_id= current_id;
		 }
		 node=node->next;
	 }
	 sprintf(new_id, "I000%u",highest_id+1);
	 
	 
 }
 
BOOLEAN delete_item(struct ppd_list *list, char * id, struct ppd_stock*data){
	 
	 struct ppd_node * current= list->head, *prev = NULL;
	 
	 while(current)
	 {
		 
	 
	 /*compare if id is matched */
	    if(strcmp(current->data->id, id )== 0)
	      {
			  memcpy(data, current->data, sizeof(struct ppd_stock));
			  
			  
			  
			  if(list->head == current && !prev)
			  {
				  /*make head point to the next element*/
				  list->head = list->head->next;
				  
				  /*current is head so free the node which was head earlier*/
				  free(current -> data);
				  free(current);
				  
				  list-> count--;
				  return TRUE;
				  
			  }
			  else{
				  
				  prev->next = current->next;
				  
				  free(current->data);
				  free(current);
				  
				  list->count--;
                   return TRUE;				  
			  }
		 
	       }
		   else{
			   prev= current;
			   current= current->next;
			   
		   }
	 
	 
	 }
	 return FALSE;
	 
 }
 
 