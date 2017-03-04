#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include "headers.h"

struct Restaurant{
	char *name;
	Item *items;
};

struct Item{
	int itemid;
	char *item;
	int price;
	Item *next;
};

int screen_one(){
	int ch;

	do{
		printf("Welcome to praveen's food kangaroo app\n\n");
		printf("\t1. Login\n");
		printf("\t2. Register\n");
		printf("\t3. No: of Users\n");
		printf("\t4. Exit\n\tYour Choice:");
		scanf("%d", &ch);
	} while (ch != 1 && ch != 2 && ch != 3 && ch != 4);
	return ch;
}

int screen_two(char* username){
	int ch;

	do{
		printf("\nWelcome %s\n\n", username);
		printf("\t1. Restaurants\n");
		printf("\t2. Cart\n");
		printf("\t3. Past orders\n");
		printf("\t4. Logout\n\tYour Choice:");
		scanf("%d", &ch);
	} while (ch != 1 && ch != 2 && ch != 3 && ch != 4);
	return ch;
}

int screen_three(){
	int ch;

	do{
		printf("Restaurants: \n");
		printf("\t1. Agarwal Restaurant\n");
		printf("\t2. Kanhaiya Restaurant\n");
		printf("\t3. Ranveer Singh tiffins\n");
		printf("\t4. Go back\n\tYour Choice:");
		scanf("%d", &ch);
	} while (ch != 1 && ch != 2 && ch != 3 && ch != 4);
	return ch;
}

int screen_four(Restaurant *rest){
	int choice;
	printf("\nRestaurant: %s\n", rest->name);
	Item *items = rest->items;
	printf("\n\t  ID:               Item\t  Price\n\n");
	while (items->next != NULL){
		printf("\t%3d: %20s\t%4d\n", items->itemid, items->item, items->price);
		items = items->next;
	}
	printf("\t -1: Go to Menu\n\tType item ID to add to your cart, Your Choice:");
	scanf("%d", &choice);
	return choice;
}