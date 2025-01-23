from components.book import Book
from components.database import DatabaseManager

def main():
    db_manager = DatabaseManager()

    while True:
        print("\n--- Book Manager ---")
        print("1. Add/Update Book")
        print("2. Get Book Details")
        print("3. Delete Book")
        print("4. List All Books")
        print("5. Exit")

        choice = input("Enter your choice: ")
        if choice == "1":
            username = input("Enter Username: ")
            topic = input("Enter Book Topic: ")
            total_pages = int(input("Enter Total Pages: "))
            current_page = int(input("Enter Current Page: "))

            book = Book(username, topic, total_pages, current_page)
            db_manager.add_or_update_book(book)
            print(f"Book information for {username} updated successfully!")

        elif choice == "2":
            username = input("Enter Username to retrieve: ")
            book = db_manager.get_book(username)
            if book:
                print(f"Book Details: {book}")
            else:
                print("No book found for the given username!")

        elif choice == "3":
            username = input("Enter Username to delete: ")
            db_manager.delete_book(username)
            print(f"Book record for {username} deleted successfully!")

        elif choice == "4":
            books = db_manager.list_all_books()
            print("\nAll Books in the System:")
            for book in books:
                print(book)

        elif choice == "5":
            print("Exiting the program.")
            break

        else:
            print("Invalid choice! Please try again.")

if __name__ == "__main__":
    main()
