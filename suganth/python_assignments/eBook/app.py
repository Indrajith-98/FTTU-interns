from json_storage import load_books, load_users
from menu import show_menu, add_book, view_books, user_starts_reading, update_page_number, remove_user

BOOKS_FILE_PATH = 'books.json'
USERS_FILE_PATH = 'users.json'

def main():
    books = load_books(BOOKS_FILE_PATH)
    users = load_users(USERS_FILE_PATH)

    while True:
        show_menu()
        choice = input("Enter your choice: ")

        if choice == "1":
            add_book(books, BOOKS_FILE_PATH)
        elif choice == "2":
            view_books(books, users)
        elif choice == "3":
            user_starts_reading(books, users, BOOKS_FILE_PATH, USERS_FILE_PATH)
        elif choice == "4":
            update_page_number(books, users, USERS_FILE_PATH)
        elif choice == "5":
            remove_user(books, users, USERS_FILE_PATH)
        elif choice == "6":
            print("Exiting program.")
            break
        else:
            print("Invalid choice, try again.")

if __name__ == "__main__":
    main()
