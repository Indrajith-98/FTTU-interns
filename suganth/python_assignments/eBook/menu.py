from book import Book
from user import User
from json_storage import load_books, save_books, load_users, save_users

BOOKS_FILE_PATH = 'books.json'

def show_menu():
    print("\nMenu:")
    print("1. Add Book")
    print("2. View Books")
    print("3. User Starts Reading")
    print("4. Update Book Page Number")
    print("5. Remove an User")
    print("6. Exit")

def add_book(books, file_path):
    title = input("Enter book title: ")
    total_pages = int(input("Enter total pages: "))
    book = Book(title, total_pages)
    books.append(book)
    save_books(file_path, books)
    print(f"Book '{title}' added successfully.")

def view_books(books, users):
    print("\nAvailable Books:")
    for idx, book in enumerate(books, start=1):
        if book.current_reader:
            user = next((u for u in users if u.username == book.current_reader), None)
            current_page = user.current_page if user else "N/A"
            print(f"{idx}. {book.title} (Reader: {book.current_reader}, Page: {current_page})")
        else:
            print(f"{idx}. {book.title} (Reader: No one)")

def user_starts_reading(books, users, books_file, users_file):
    print("\nSelect a Book to Read:")
    for idx, book in enumerate(books, start=1):
        if book.current_reader:
            continue
        print(f"{idx}. {book.title}")

    book_idx = int(input("Enter book number to read: ")) - 1
    username = input("Enter your username: ")

    if books[book_idx].current_reader is None:
        books[book_idx].current_reader = username
        user = User(username, books[book_idx].title)
        users.append(user)
        save_books(books_file, books)
        save_users(users_file, users)
        print(f"{username} is now reading '{books[book_idx].title}'.")
    else:
        print(f"Sorry, the book '{books[book_idx].title}' is already being read by {books[book_idx].current_reader}.")

def update_page_number(books, users, users_file):
    print("\nSelect a Book to Update Page Number:")
    for idx, book in enumerate(books, start=1):
        print(f"{idx}. {book.title} (Current Reader: {book.current_reader})")

    book_idx = int(input("Enter book number: ")) - 1
    username = input("Enter your username: ")

    user = next((u for u in users if u.username == username and u.book == books[book_idx].title), None)

    if user:
        print(f"Current book: '{books[book_idx].title}'")
        print(f"Current page: {user.current_page}")
        print(f"Current topic: {user.current_topic}")

        update_topic = input("Would you like to update the topic? (y/n): ").lower()
        if update_topic == 'y':
            new_topic = input("Enter new topic: ")
            user.update_topic(new_topic)  # Update user's current topic
            save_users(users_file, users)
            print(f"User's topic updated to '{new_topic}'.")

        current_page = int(input(f"Enter current page number (1 to {books[book_idx].total_pages}): "))
        if 1 <= current_page <= books[book_idx].total_pages:
            user.current_page = current_page
            save_users(users_file, users)
            print(f"Page number for '{books[book_idx].title}' updated to {current_page}.")
        else:
            print("Invalid page number.")
    else:
        print("You are not reading this book.")

def remove_user(books, users, users_file):
    print("\nSelect a User to Remove:")
    for idx, user in enumerate(users, start=1):
        print(f"{idx}. {user.username} (Currently Reading: {user.book}, Page: {user.current_page}, Topic: {user.current_topic})")

    user_idx = int(input("Enter user number to remove: ")) - 1
    username = users[user_idx].username
    user_book = users[user_idx].book

    # Remove user details from the users list
    users[user_idx].remove_user()
    users.pop(user_idx)  # Remove the user from the list

    # Set current_reader to None in the book
    for book in books:
        if book.title == user_book:
            book.remove_reader()

    # Save updated data to JSON
    save_books(BOOKS_FILE_PATH, books)
    save_users(users_file, users)

    print(f"User '{username}' has been removed and the book '{user_book}' is now available.")

