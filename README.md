BY: PRAVEEN SVSRK, MVGR  


User login:  
	Sessions are maintained by creating a session file to store user's name. On logout, this file is emptied.  
	If Session is still existing, user will not be prompted for login, he will be automatically logged in.  
	Login fails on invalid credentials  
	
User Registration:  
	Registration has both username and password length validation  
	Registration fails if username already exists.  
	
Restaurants:  
	Each restaurant has their own file that maintains List of items, with their IDs and prices  
	
Cart:  
	Each user has their personalized cart.  
	The cart stays intact over successive logins, up to the point where the user choses to checkout.   
	User can check out by navigating to his cart, Total amount will also be shown.  
	Cart is emptied upon checkout.  
	
Transaction log (Past orders):  
	Upon every checkout, a log is maintained that tracks all past orders.   
	Every user can view his personalized list of past orders, although all orders are logged into a single file.  
