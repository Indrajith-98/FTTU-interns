from admin import Admin
from user import User
from utils import read_csv, write_csv, file_path

def display_books():
    books = read_csv(file_path("books.csv"))
    if not books:
        print("No books available.")
    else:
        print("\nAvailable Books:")
        for book in books:
            print(f"- {book['Book Name']} (Total Pages: {book['Total Pages']})")
    print("\n")

def signup():
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    users = read_csv(file_path("users.csv"))
    for user in users:
        if user["Username"] == username:
            print("Username already exists.")
            return
    users.append({"Username": username, "Password": password})
    write_csv(file_path("users.csv"), users)
    print("Sign-up successful.")

def login():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    users = read_csv(file_path("users.csv"))
    for user in users:
        if user["Username"] == username and user["Password"] == password:
            return username
    print("Invalid username or password.")
    return None

if __name__ == "__main__":
    while True:
        print("\nWelcome to E-Library")
        print("1. Login\n2. Sign-Up\n3. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            username = login()
            if username:
                if username == "admin":
                    admin = Admin()
                    while True:
                        print("\nAdmin Options:\n1. View All Users\n2. Update Book Details\n3. Display all books\n4. Logout")
                        admin_choice = input("Enter your choice: ")
                        if admin_choice == "1":
                            admin.view_all_users()
                        elif admin_choice == "2":
                            book_name = input("Enter book name: ")
                            total_pages = input("Enter total pages: ")
                            chapters = input("Enter chapters (comma-separated): ")
                            admin.update_book_details(book_name, total_pages, chapters)
                        elif admin_choice=="3":
                            display_books()
                        elif admin_choice == "4":
                            break
                        else:
                            print("Invalid choice.")
                else:
                    user = User(username)
                    while True:
                        print("\nUser Options:\n1. Select Book\n2. Turn Page\n3. View Progress\n4. Logout")
                        user_choice = input("Enter your choice: ")
                        if user_choice == "1":
                            display_books()
                            book_name = input("Enter book name: ")
                            user.select_book(book_name)
                        elif user_choice == "2":
                            user.turn_page()
                        elif user_choice == "3":
                            user.view_progress()
                        elif user_choice == "4":
                            break
                        else:
                            print("Invalid choice.")
        elif choice == "2":
            signup()
        elif choice == "3":
            print("Exiting E-Library.")
            break
        else:
            print("Invalid choice.")
