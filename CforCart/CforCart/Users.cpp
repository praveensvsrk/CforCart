#define _CRT_SECURE_NO_WARNINGS

#define USERS_FILE_PATH "users.txt"
#define USER_SESSION "session.txt"
#define LOG "transaction_log.txt"

#include "headers.h"
#include<fstream>
#include<string.h>

typedef struct User{
	char *user_name;
	char *password;
	struct User *next;
}User;

struct Item{
	int itemid;
	char *item;
	int price;
	Item *next;
};

User* load_users(){
	/* Loads users to avoid repetitive file reads on successive login/logouts */
	User *users = NULL;

	char *user_name = (char*)malloc(sizeof(char) * 30);
	char *password = (char*)malloc(sizeof(char) * 30);

	FILE *users_file = fopen(USERS_FILE_PATH, "r");

	if (!users_file){
		users_file = fopen(USERS_FILE_PATH, "w");
		fclose(users_file);
		return NULL;
	}
	while (fscanf(users_file, "Username:%s\nPassword:%s\n", user_name, password) != -1){
		User *new_user = (User*)malloc(sizeof(User));

		new_user->user_name = (char*)malloc(sizeof(char) * 30);
		new_user->password = (char*)malloc(sizeof(char) * 30);
		strcpy(new_user->user_name, user_name);
		strcpy(new_user->password, password);

		User *temp = users;
		users = new_user;
		new_user->next = temp;
	}
	fclose(users_file);
	free(user_name);
	free(password);
	return users;

}

User* add_user(User* users, char* user_name, char* password){
	/*Adds new user to the user file*/
	FILE *users_file = fopen(USERS_FILE_PATH, "a");
	if (!users_file){
		printf("Error opening Users file\n");
		exit(0);
	}
	
	User *new_user = (User*)malloc(sizeof(User));
	new_user->user_name = (char*)malloc(sizeof(char) * 30);
	new_user->password = (char*)malloc(sizeof(char) * 30);

	strcpy(new_user->user_name, user_name);
	strcpy(new_user->password, password);
	new_user->next = users;

	fprintf(users_file, "Username:%s\nPassword:%s\n", user_name, password);
	fclose(users_file);
	return new_user;
}

int get_user_count(){
	/*Gets total registered users in the service*/
	int count = 0;

	char *user_name = (char*)malloc(sizeof(char) * 30);
	char *password = (char*)malloc(sizeof(char) * 30);

	FILE *users_file = fopen(USERS_FILE_PATH, "r");
	if (!users_file){
		return 0;
	}
	while (fscanf(users_file, "Username:%s\nPassword:%s\n", user_name, password) != -1){
		count++;
	}
	fclose(users_file);
	free(user_name);
	free(password);
	return count;
}

char* get_session(){
	/*Returns current session*/
	FILE *session_file = fopen(USER_SESSION, "r");
	char *user_name = (char*)malloc(sizeof(char) * 30);
	if (session_file){
		if (fscanf(session_file, "Username:%s\n", user_name) != -1){
			fclose(session_file);
			return user_name;
		}
	}

	if (session_file)
		fclose(session_file);

	return NULL;

}

char* login(){
	/*Logs in the user*/
	char* user_name = get_session();
	if (user_name)
		return user_name;

	user_name = (char*)malloc(sizeof(char) * 30);
	char *password = (char*)malloc(sizeof(char) * 30);
	
	printf("Enter username: ");
	scanf("%s", user_name);
	printf("Enter password: ");
	scanf("%s", password);

	FILE *session_file;
	User *users = load_users();
	User *current_user = users;
	while (current_user != NULL){
		if (strcmp(current_user->user_name, user_name) == 0
			&& strcmp(current_user->password, password) == 0){
			session_file = fopen(USER_SESSION, "w");
			fprintf(session_file, "Username:%s\n", user_name);
			fclose(session_file);
			free(users);
			return user_name;
		}
		current_user = current_user->next;
	}
	return NULL;//invalid credentials
}

int is_existing(char *user_name){
	User *users = load_users();
	User *cur = users;
	while (cur != NULL){
		if (strcmp(cur->user_name, user_name) == 0)
			return 1;
		cur = cur->next;
	}
	return 0;
}

int register_user(){
	/*Validates and Registers the user*/
	char *user_name = (char*)malloc(sizeof(char) * 30);
	char *password = (char*)malloc(sizeof(char) * 30);
	
	while (1){
		printf("Enter username(8 <= len < 30): ");
		scanf("%s", user_name);
		if (strlen(user_name) >= 8 && strlen(user_name) < 30){
			int exists = is_existing(user_name);
			if (exists == 0)
				break;
			else{
				printf("Username already exists\n");
			}
		}

	}
	while (1){
		printf("Enter password(8 <= len < 30): ");
		scanf("%s", password);
		if (strlen(password) >= 8 && strlen(password) < 30){
			break;
		}
	}

	add_user(load_users(), user_name, password);
	free(user_name);
	free(password);
	return 1;
}

int logout(){
	/*Logs out and destroys session*/
	FILE *session_file = fopen(USER_SESSION, "w");
	fclose(session_file);
	return 1;
}

int display_cart(char *user){
	/*Displays current user's cart, returns 1 if cart is not empty*/
	char *cart_name = (char*)malloc(sizeof(char)*(strlen(user) + 10));
	strcpy(cart_name, user);
	strcat(cart_name, "_cart.txt");
	FILE* cart = fopen(cart_name, "r");
	if (!cart){
		free(cart_name);
		return 0;
	}
	Item *item = (Item*)malloc(sizeof(item));
	item->item = (char*)malloc(sizeof(char) * 30);
	printf("\nYour Cart:\n");
	int quantity, cost, total_cost=0;
	char *restaurant_name = (char*)malloc(sizeof(char)*30);
	while (fscanf(cart, "%d %s %d %d %d %s\n", &item->itemid, item->item, 
		&item->price, &quantity, &cost, restaurant_name) != -1){
		printf("%4d %20s %4d %3d %4d %20s\n", item->itemid, item->item, item->price,
			quantity, cost, restaurant_name);
		total_cost += cost;
	}
	
	fclose(cart);
	free(restaurant_name);
	free(item->item);
	free(cart_name);
	if (total_cost){
		printf("Total Amount: %d\n", total_cost);
		return 1;
	}
	return 0;
}

void add_to_cart(char *user, Item *item, int quantity, char *restaurant_name){
	/*Adds the item to user's cart*/
	char *cart_name = (char*)malloc(sizeof(char)*(strlen(user) + 10));
	strcpy(cart_name, user);
	strcat(cart_name, "_cart.txt");
	FILE* cart = fopen(cart_name, "a");
	fprintf(cart, "%d %s %d %d %d %s\n", item->itemid, item->item, item->price, quantity, item->price * quantity, restaurant_name);
	fclose(cart);
	free(cart_name);
}

void checkout(char *user){
	/*User checks out*/
	char *cart_name = (char*)malloc(sizeof(char)*(strlen(user) + 10));
	FILE *transaction_log = fopen(LOG, "a");

	strcpy(cart_name, user);
	strcat(cart_name, "_cart.txt");

	FILE* cart = fopen(cart_name, "r");
	Item *item = (Item*)malloc(sizeof(item));
	item->item = (char*)malloc(sizeof(char) * 30);
	printf("\nYour Cart:\n");

	int quantity, cost, total_cost = 0;
	char *restaurant_name = (char*)malloc(sizeof(char) * 30);
	fprintf(transaction_log, "User: %s\n", user);
	while (fscanf(cart, "%d %s %d %d %d %s\n", &item->itemid, item->item,
		&item->price, &quantity, &cost, restaurant_name) != -1){
		printf("%4d %20s %4d %3d %4d %20s\n", item->itemid, item->item, item->price,
			quantity, cost, restaurant_name);
		fprintf(transaction_log, "%d  %s  %d  %d  %d  %s\n", item->itemid, item->item, 
			item->price, quantity, cost, restaurant_name);
		total_cost += cost;
	}
	fprintf(transaction_log, "Amount: %d\n", total_cost);
	fclose(transaction_log);
	fclose(cart);
	cart = fopen(cart_name, "w");
	fclose(cart);

}

void display_log(char *user){
	/*Displays current user's cart*/
	FILE *transaction_log = fopen(LOG, "r");
	if (!transaction_log)
		return;
	char *log_user = (char*)malloc(sizeof(char) * 30);

	Item *item = (Item*)malloc(sizeof(item));
	item->item = (char*)malloc(sizeof(char) * 30);
	printf("\nPast Orders:\n");
	int quantity, cost, amount = 0;
	char *restaurant_name = (char*)malloc(sizeof(char) * 30);

	while (1){
		int retval = fscanf(transaction_log, "User: %s\n", log_user);
		if (retval != 1)
			break;
		if (strcmp(log_user, user) == 0){
			while (fscanf(transaction_log, "%d %s %d %d %d %s\n", &item->itemid, item->item,
				&item->price, &quantity, &cost, restaurant_name) == 6){
				printf("%4d %20s %4d %3d %4d %20s\n", item->itemid, item->item, item->price,
					quantity, cost, restaurant_name);
			}
			fscanf(transaction_log, "Amount: %d\n", &amount);
			printf("Amount: %d\n\n", amount);

		}
		else{
			while (fscanf(transaction_log, "%d %s %d %d %d %s\n", &item->itemid, item->item,
				&item->price, &quantity, &cost, restaurant_name) == 6);
			fscanf(transaction_log, "Amount: %d\n", &amount);

		}
	}

	free(restaurant_name);
	free(item->item);
}


