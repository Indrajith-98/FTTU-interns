from Library.utils.book import Book
from Library.utils.user import User
import atexit
import os
import json

# Initialize the data structure to store user and book data
library_data = {"users": [], "books": []}

# Load existing data if it exists
if not os.path.exists("Library"):
    os.makedirs("Library")
data_file = "Library/data.json"
if os.path.exists(data_file):
    with open(data_file, "r") as file:
        library_data = json.load(file)


# Function to save data on program exit
def on_exit():
    print("Exiting the program...")
    with open(data_file, "w") as file:
        json.dump(library_data, file, indent=4)
    print(f"Data successfully saved to {data_file}")


atexit.register(on_exit)


# Main program logic
def main():
    while True:
        print("\n--- Library Management ---")
        print("1. Add a user")
        print("2. Add a book")
        print("3. Assign a book to a user")
        print("4. Turn a page")
        print("5. Get book status")
        print("6. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            username = input("Enter the user's name: ")
            user = User(username)
            library_data["users"].append(
                {"name": username, "current_page": 0, "current_book": None}
            )
            print(f"User {username} added.")

        elif choice == "2":
            title = input("Enter the book title: ")
            total_pages = int(input("Enter the total number of pages: "))
            book = Book(title=title, total_pages=total_pages)
            library_data["books"].append(
                {
                    "title": title,
                    "total_pages": total_pages,
                    "current_page": 0,
                    "assigned_user": None,
                }
            )
            print(f"Book '{title}' added.")

        elif choice == "3":
            username = input("Enter the user's name: ")
            book_title = input("Enter the book title: ")
            user = next(
                (u for u in library_data["users"] if u["name"] == username), None
            )
            book = next(
                (b for b in library_data["books"] if b["title"] == book_title), None
            )
            if user and book:
                book["assigned_user"] = username
                user["current_book"] = book_title
                print(f"Book '{book_title}' assigned to user '{username}'.")
            else:
                print("User or book not found.")

        elif choice == "4":
            username = input("Enter the user's name: ")
            user = next(
                (u for u in library_data["users"] if u["name"] == username), None
            )
            if user and user["current_book"]:
                book = next(
                    (
                        b
                        for b in library_data["books"]
                        if b["title"] == user["current_book"]
                    ),
                    None,
                )
                if book:
                    pages = int(input("Enter the number of pages to turn: "))
                    new_page = min(book["current_page"] + pages, book["total_pages"])
                    book["current_page"] = new_page
                    user["current_page"] = new_page
                    print(
                        f"User '{username}' is now on page {new_page} of book '{book['title']}'."
                    )
                else:
                    print("No book is currently assigned to the user.")
            else:
                print("User not found or no book assigned.")

        elif choice == "5":
            book_title = input("Enter the book title: ")
            book = next(
                (b for b in library_data["books"] if b["title"] == book_title), None
            )
            if book:
                assigned_user = book["assigned_user"] or "None"
                print(f"Book '{book_title}':")
                print(f"- Total Pages: {book['total_pages']}")
                print(f"- Current Page: {book['current_page']}")
                print(f"- Assigned to: {assigned_user}")
            else:
                print("Book not found.")

        elif choice == "6":
            print("Goodbye!")
            break

        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()
