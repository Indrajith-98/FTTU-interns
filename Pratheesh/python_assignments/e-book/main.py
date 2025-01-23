from ebook import EBook
from users import UserManager
from utils import view_users, view_books, view_reading_status

def main():
    ebook = EBook()
    user_manager = UserManager(ebook.conn)

    while True:
        print("\nWelcome to the E-Book Library!")
        print("1. Sign Up")
        print("2. Log In")
        print("3. View Database Tables")
        print("4. Add Admin")
        print("5. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            # Sign Up
            name = input("Enter your name: ")
            password = input("Enter your password: ")
            user_manager.sign_up(name, password)
            print("Sign-up successful! You can now log in.")

        elif choice == "2":
            # Log In
            name = input("Enter your name: ")
            password = input("Enter your password: ")
            user = user_manager.log_in(name, password)

            if user:
                if user["is_admin"]:
                    print(f"Welcome back, Admin {name}!")
                    while True:
                        print("\nAdmin Options:")
                        print("1. View Available Books")
                        print("2. Add Book")
                        print("3. Delete Book")
                        print("4. Log Out")
                        admin_choice = input("Enter your choice: ")

                        if admin_choice == "1":
                            view_books(ebook.cursor)

                        elif admin_choice == "2":
                            title = input("Enter book title: ")
                            total_pages = int(input("Enter total number of pages: "))
                            ebook.add_book(title, total_pages)
                            print(f"Book '{title}' added successfully!")

                        elif admin_choice == "3":
                            book_id = int(input("Enter the book ID to delete: "))
                            ebook.delete_book(book_id)
                            print(f"Book with ID {book_id} deleted successfully!")

                        elif admin_choice == "4":
                            print("Logged out successfully.")
                            break

                        else:
                            print("Invalid choice! Please try again.")

                else:
                    print(f"Welcome back, {name}!")
                    while True:
                        print("\nUser Options:")
                        print("1. View Available Books")
                        print("2. Start Reading")
                        print("3. Update Reading Status")
                        print("4. View Reading Status")
                        print("5. Log Out")
                        user_choice = input("Enter your choice: ")

                        if user_choice == "1":
                            view_books(ebook.cursor)

                        elif user_choice == "2":
                            book_id = int(input("Enter the book ID to start reading: "))
                            start_page = int(input("Enter starting page: "))
                            start_topic = input("Enter starting topic: ")
                            ebook.start_reading(user["user_id"], book_id, start_page, start_topic)
                            print("Started reading!")

                        elif user_choice == "3":
                            book_id = int(input("Enter the book ID you are reading: "))
                            new_page = int(input("Enter new page: "))
                            new_topic = input("Enter new topic: ")
                            ebook.update_page(user["user_id"], book_id, new_page, new_topic)
                            print("Reading status updated!")

                        elif user_choice == "4":
                            book_id = int(input("Enter the book ID: "))
                            status = ebook.get_reading_status(user["user_id"], book_id)
                            if status:
                                print(f"Reading Status: {status}")
                            else:
                                print("No reading status found for this book.")

                        elif user_choice == "5":
                            print("Logged out successfully.")
                            break

                        else:
                            print("Invalid choice! Please try again.")

            else:
                print("Invalid credentials! Please try again or sign up.")

        elif choice == "3":
            print("\nDatabase Tables:")
            view_users(ebook.cursor)
            view_books(ebook.cursor)
            view_reading_status(ebook.cursor)

        elif choice == "4":
            print("Add a New Admin")
            name = input("Enter admin name: ")
            password = input("Enter admin password: ")
            security_key = input("Enter the security key: ")
            user_manager.add_admin(name, password, security_key)

        elif choice == "5":
            print("Thank you for using the E-Book Library. Goodbye!")
            break

        else:
            print("Invalid choice! Please try again.")

    # Close the connection
    ebook.close()

if __name__ == "__main__":
    main()
