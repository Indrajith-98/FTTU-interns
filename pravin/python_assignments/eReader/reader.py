import os
from Operators.manage_users import UserManager
from Operators.handle_files import Book
from PyPDF2 import PdfReader


def list_books_in_folder(folder_path):
    """List all PDF files in the folder with their page count."""
    books = []
    for file in os.listdir(folder_path):
        if file.endswith(".pdf"):
            file_path = os.path.join(folder_path, file)
            try:
                reader = PdfReader(file_path)
                page_count = len(reader.pages)
                books.append((file, page_count))
            except Exception as e:
                print(f"Error reading {file}: {e}")
    return books

def main():
    # Initialize the database
    UserManager.init_db()

    print("Welcome to the E-Book Reader!")
    choice = input("Do you have an account? [y/n]: ").strip().lower()

    if choice == 'n':
        username = input("Enter your username: ").strip()
        password = input("Enter your password: ").strip()
        UserManager.register_user(username, password)
    elif choice == 'y':
        username = input("Enter your username: ").strip()
        password = input("Enter your password: ").strip()
        user_id = UserManager.authenticate_user(username, password)
        if not user_id:
            return
    else:
        print("Invalid choice.")
        return

    folder_path = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/python_assignments/eReader/BookRepo"
    books = list_books_in_folder(folder_path)
    if not books:
        print("No books found in the folder.")
        return

    print("\nAvailable Books:")
    for i, (book, pages) in enumerate(books, start=1):
        print(f"[{i}] {book}")

    try:
        choice = int(input("\nSelect a book by entering its number: ").strip())
        if choice < 1 or choice > len(books):
            print("Invalid selection. Exiting.")
            return
    except ValueError:
        print("Invalid input. Exiting.")
        return

    selected_book, page_count = books[choice - 1]
    book = Book(selected_book, page_count)
    book.load_book(username)

    while True:
        book.display_progress()
        command = input("\nCommands: [n] Next Page, [p] Previous Page, [q] Quit: ").strip().lower()
        if command == 'n' and book.current_page < book.page_count:
            book.current_page += 1
        elif command == 'p' and book.current_page > 1:
            book.current_page -= 1
        elif command == 'q':
            book.update_progress()
            print("Progress saved. Goodbye!")
            break
        else:
            print("Invalid command. Try again.")

if __name__ == "__main__":
    main()
