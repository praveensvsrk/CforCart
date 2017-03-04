**BY: PRAVEEN SVSRK, MVGR**


**User login:**   
1. Sessions are maintained by creating a session file to store user's name. On logout, this file is emptied.  
2. If Session is still existing, user will not be prompted for login, he will be automatically logged in.  
3. Login fails on invalid credentials  
	
**User Registration:**   
1. Registration has both username and password length validation  
2. Registration fails if username already exists.  
	
**Restaurants:**  
1. Each restaurant has their own file that maintains List of items, with their IDs and prices  
	
**Cart:**  
1. Each user has their personalized cart.  
2. The cart stays intact over successive logins, up to the point where the user choses to checkout.   
3. User can check out by navigating to his cart, Total amount will also be shown.  
4. Cart is emptied upon checkout.  
	
**Transaction log (Past orders):**  
1. Upon every checkout, a log is maintained that tracks all past orders.   
2. Every user can view his personalized list of past orders, although all orders are logged into a single file.  
