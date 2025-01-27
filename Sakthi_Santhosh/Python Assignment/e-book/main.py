from library_manager import LibraryManager


def main():
    """Main menu for the Library Management System."""
    library = LibraryManager()

    while True:
        print("\n--- Main Menu ---")
        print("1. Library Menu")
        print("2. Book Menu")
        print("3. Exit")
        choice = input("Enter your choice (1-3): ")

        if choice == "1":
            library_menu(library)
        elif choice == "2":
            book_menu(library)
        elif choice == "3":
            print("Exiting the application. Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")


def library_menu(library):
    """Menu for library management."""
    while True:
        print("\n--- Library Menu ---")
        print("1. Display All Books")
        print("2. Add a Book")
        print("3. Back to Main Menu")
        choice = input("Enter your choice (1-3): ")

        if choice == "1":
            library.display_books()
        elif choice == "2":
            library.add_book()
        elif choice == "3":
            break
        else:
            print("Invalid choice. Please try again.")


def book_menu(library):
    """Menu for book-specific operations."""
    book = library.select_book()
    if not book:
        return

    while True:
        print(f"\n--- Book Menu ({book.title}) ---")
        print("1. Add a User")
        print("2. Update User Progress")
        print("3. Display Users and Progress")
        print("4. Back to Main Menu")
        choice = input("Enter your choice (1-4): ")

        if choice == "1":
            book.add_user()
            library.save_library()
        elif choice == "2":
            book.update_user_progress()
            library.save_library()
        elif choice == "3":
            book.display_users()
        elif choice == "4":
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()
