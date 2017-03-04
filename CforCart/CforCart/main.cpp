#define _CRT_SECURE_NO_WARNINGS

#include "headers.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Item{
	int itemid;
	char *item;
	int price;
	Item *next;
};

struct Restaurant{
	char *name;
	Item *items;
};


char *username = NULL;

void run_app(){
	int choice;
	char *password, *success, not_empty;
	Restaurant* rest; 
	Item *selected = NULL;

	do{
		username = get_session();
		if (username != NULL)
			choice = 1;
		else
			choice = screen_one();
		
		switch (choice){
			case 1:
				username = login();
				if (username == NULL){
					printf("Login failed\n");
					break;
				}
				else{
					do{
						choice = screen_two(username);
						switch (choice){

						case 1:
							choice = screen_three();
							rest = get_restaurant_info(choice);
							choice = screen_four(rest);
							while (1){
								if (choice == -1)
									break;
								selected = rest->items;
								while (selected->next != NULL && selected->itemid != choice){
									selected = selected->next;
								}
								if (selected->next != NULL)
									break;
								choice = screen_four(rest);
							}
							if (choice == -1)
								break;

							int quantity;
							printf("\tEnter quantity: ");
							scanf("%d", &quantity);
							while (quantity < 1){
								printf("\tEnter quantity: ");
								scanf("%d", &quantity);
							}
							add_to_cart(username, selected, quantity, rest->name);
							printf("\tItem %d added to cart, Checkout from the previous menu\n", choice);
							break;
						case 2:
							not_empty = display_cart(username);
							if (!not_empty)
								break;
							char c;
							fflush(stdin);
							do{
								printf("Do you want to checkout?(Y/N) ");
								scanf("%c", &c);
								
							} while (c != 'Y' && c != 'N');
							if (c == 'Y')
								checkout(username);
							break;
						case 3:
							display_log(username);
							break;
						case 4:
							logout();
							break;
						case 5:
							break;
						}
					} while (choice != 4);
				}
				break;
			case 2:
				register_user();
				break;
			case 3:
				printf("Registered users: %d\n", get_user_count());
				break;
			case 4:
				exit(0);
		}

	} while (1);

	getchar();
}


int main(){
	
	run_app();
	return 0;
}