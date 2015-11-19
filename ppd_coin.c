/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2015 Assignment #2
 * Full Name        : Yap Fui Yang
 * Student Number   : s3466760
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/
#include "ppd_coin.h"

 /**
  * @file ppd_coin.c implement functions here for managing coins in the
  * "cash register" contained in the @ref ppd_system struct.
  **/

  
enum denomination string_to_denom(char * denom){
	  
	   if (strcmp(denom, "1000") == 0) {
        return TEN_DOLLARS;}
		else if (strcmp(denom, "500") == 0) {
       return FIVE_DOLLARS;} 
	   else if (strcmp(denom, "200") == 0) {
       return TWO_DOLLARS;} 
	   else if (strcmp(denom, "100") == 0) {
       return ONE_DOLLAR;} 
	   if (strcmp(denom, "50") == 0) {
       return FIFTY_CENTS;} 
	   else if (strcmp(denom, "20") == 0) {
       return TWENTY_CENTS;} 
	   else if (strcmp(denom, "10") == 0) {
       return TEN_CENTS;}
	   else {
        return FIVE_CENTS; }
		
	  
	  
  }
  
  

  
  
  