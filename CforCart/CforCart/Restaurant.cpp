#define _CRT_SECURE_NO_WARNINGS


#include "headers.h"
#include<fstream>
#include<string.h>

char restaurants[20][20] = { "1.txt", "2.txt", "3.txt"};
//using LINUX it is possible to simply read a directory and store all the contents which represent the restaurants information

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

Item* add_item(Item *items, int itemid, char* name, int price){
	Item* new_item = (Item*)malloc(sizeof(Item));
	new_item->itemid = itemid;
	new_item->item = (char*)malloc(sizeof(char) * 30);
	strcpy(new_item->item, name);
	new_item->price = price;

	new_item->next = items;
	return new_item;
}

Restaurant* get_restaurant_info(int count){
	
	char *restaurant_file = restaurants[count - 1]; //get the file corresponding to the restaurant
	
	FILE *r = fopen(restaurant_file, "r");
	char *name = (char*)malloc(sizeof(char) * 30);
	fscanf(r, "Restaurant: %s\n", name);

	Restaurant *rest = (Restaurant*)malloc(sizeof(Restaurant));
	rest->name = (char*)malloc(sizeof(char) * 30);
	rest->items = NULL;
	strcpy(rest->name, name);

	char *item_name = (char*)malloc(sizeof(char) * 30);
	int price, itemid;

	while (fscanf(r, "%d %s %d\n", &itemid, item_name, &price) != -1){
		rest->items = add_item(rest->items, itemid, item_name, price);
	}

	return rest;

}