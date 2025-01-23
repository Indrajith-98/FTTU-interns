from components.database import DatabaseManager

def main():
    db = DatabaseManager()

    while True:
        print("\n--- Book Manager ---\n")
        print("1. Add User")
        print("2. Add Book for User")
        print("3. View Books by User")
        print("4. Update Book Progress")
        print("5. View Book Details")
        print("6. List All Books")
        print("7. List All Users with Their Books")
        print("0. Exit")

        choice = input("Enter your choice: ")
        if choice == "1":
            username = input("Enter Username: ")
            try:
                user_id = db.add_user(username)
                print(f"User {username} added successfully! (User ID: {user_id})")
            except ValueError as e:
                print(e)

        elif choice == "2":
            username = input("Enter Username: ")
            user = db.get_user(username)
            if not user:
                print("User not found! Please add the user first.")
                continue

            title = input("Enter Book Title: ")
            total_pages = int(input("Enter Total Pages: "))
            book_id = db.add_book(user.user_id, title, total_pages)
            print(f"Book '{title}' added successfully! (Book ID: {book_id})")

        elif choice == "3":
            username = input("Enter Username: ")
            user = db.get_user(username)
            if not user:
                print("User not found!")
                continue

            books = db.get_books_by_user(user.user_id)
            if books:
                print(f"\nBooks for {username}:")
                for book in books:
                    print(book)
            else:
                print("No books found for this user.")

        elif choice == "4":
            book_id = int(input("Enter Book ID: "))
            pages_read = int(input("Enter Number of Pages Read: "))
            try:
                db.update_book_progress(book_id, pages_read)
                print("Book progress updated successfully!")
            except ValueError as e:
                print(e)

        elif choice == "5":
            book_id = int(input("Enter Book ID: "))
            try:
                book = db.get_book_details(book_id)
                print(f"Book Details: {book}")
            except ValueError as e:
                print(e)

        elif choice == "6":
            books = db.list_all_books()
            print("\nAll Books in the System:")
            for book in books:
                print(
                    f"Book ID: {book['book_id']}, Title: {book['title']}, Total Pages: {book['total_pages']}, "
                    f"Current Page: {book['current_page']}, User: {book['username']}"
                )

        elif choice == "7":
            users = db.list_all_users_with_books()
            print("\nAll Users and Their Books:")
            for user_id, data in users.items():
                print(f"User: {data['username']}")
                for book in data["books"]:
                    print(
                        f"  Book ID: {book['book_id']}, Title: {book['title']}, "
                        f"Current Page: {book['current_page']}/{book['total_pages']}"
                    )

        elif choice == "0":
            print("Exiting the program.")
            break

        else:
            print("\nInvalid choice! Please try again.")

if __name__ == "__main__":
    main()
