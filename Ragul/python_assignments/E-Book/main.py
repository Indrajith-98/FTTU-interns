import sqlite3
from admin import admin_module
from user import user_options

def main():
    conn = sqlite3.connect("data.db")
    cursor = conn.cursor()

    # Ensure the Users table exists
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Users (
            Username TEXT PRIMARY KEY,
            Password TEXT DEFAULT '1234'
        )
    ''')

    while True:
        print("\n--- Welcome to the E-Book Application! ---")
        print("1. Admin Login")
        print("2. User Login")
        print("3. Sign In (New User)")
        print("4. Exit")

        choice = input("Choose an option (1-4): ").strip()

        if choice == '1':  # Admin Login
            password = input("Enter admin password: ")
            if password == "1234":  # Hardcoded admin password
                admin_module(conn)
            else:
                print("Invalid password. Returning to the main menu.")
        
        elif choice == '2':  # User Login
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()

            cursor.execute("SELECT * FROM Users WHERE Username = ? AND Password = ?", (username, password))
            user_data = cursor.fetchone()

            if user_data:
                print(f"Welcome back, {username}!")
                user_options(conn, username)
            else:
                print("Invalid username or password. Please try again.")
        
        elif choice == '3':  # Sign In (New User)
            username = input("Choose a username: ").strip()
            password = input("Choose a password: ").strip()

            # Check if username already exists
            cursor.execute("SELECT * FROM Users WHERE Username = ?", (username,))
            if cursor.fetchone():
                print("Username already exists. Please try a different one.")
            else:
                cursor.execute("INSERT INTO Users (Username, Password) VALUES (?, ?)", (username, password))
                conn.commit()
                print(f"User {username} created successfully!")

        elif choice == '4':  # Exit
            print("Exiting the application. Goodbye!")
            break

        else:
            print("Invalid choice. Please enter a number between 1 and 4.")

    conn.close()

if __name__ == "__main__":
    main()
