struct User;
struct Restaurant;
struct Item;

User* load_users();
void store_users(User*);
int get_user_count();
User* add_user(User* users, char* user_name, char* password, char *path);
char* login();
int register_user();
int logout();
Restaurant* get_restaurant_info(int count);
int display_cart(char *user);
void add_to_cart(char *user, Item *item, int quantity, char *restaurant_name);
void checkout(char*);
void display_log(char *user);
char* get_session();

int screen_one();
int screen_two(char*);
int screen_three();
int screen_four(Restaurant *rest);