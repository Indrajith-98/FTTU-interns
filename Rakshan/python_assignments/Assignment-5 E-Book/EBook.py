import json

class Book:
    def __init__(self, topic, total_pages, current_page=1):
        self.topic = topic
        self.total_pages = total_pages
        self.current_page = current_page

    def update_current_page(self, page_number):
        if 1 <= page_number <= self.total_pages:
            self.current_page = page_number
        else:
            print("Invalid page number. Please enter a valid page.")

    def to_dict(self):
        return {
            "topic": self.topic,
            "total_pages": self.total_pages,
            "current_page": self.current_page
        }

    @staticmethod
    def from_dict(data):
        return Book(data["topic"], data["total_pages"], data["current_page"])


class EBookApplication:
    STORAGE_FILE = "ebook_storage.json"

    def __init__(self):
        self.users = self.load_users()

    def load_users(self):
        try:
            with open(self.STORAGE_FILE, "r") as file:
                data = json.load(file)
                return {
                    username: {book_id: Book.from_dict(book_data) for book_id, book_data in books.items()} 
                    for username, books in data.items()
                }
        except (FileNotFoundError, json.JSONDecodeError):
            return {}

    def save_users(self):
        with open(self.STORAGE_FILE, "w") as file:
            json.dump({
                username: {book_id: book.to_dict() for book_id, book in books.items()} 
                for username, books in self.users.items()
            }, file, indent=4)

    def add_or_update_user(self, username, book_id, total_pages, topic, current_page=1):
        if username not in self.users:
            self.users[username] = {}
        if book_id in self.users[username]:
            print(f"Welcome back, {username}! Resuming your reading of '{topic}'.")
        else:
            print(f"Hello {username}, adding a new book '{topic}' for you.")
        self.users[username][book_id] = Book(topic, total_pages, current_page)
        self.save_users()

    def update_current_page(self, username, book_id, page_number):
        if username in self.users and book_id in self.users[username]:
            self.users[username][book_id].update_current_page(page_number)
            self.save_users()
            print(f"Page updated to {page_number} for '{self.users[username][book_id].topic}' by {username}.")
        else:
            print(f"No record found for {username} or book ID '{book_id}'. Please add the user or book first.")

    def get_user_books(self, username):
        if username in self.users:
            return {
                book_id: book.to_dict() for book_id, book in self.users[username].items()
            }
        else:
            return None

    def list_books(self, username):
        if username in self.users:
            print(f"Books for {username}:")
            for book_id, book in self.users[username].items():
                print(f"- Book ID: {book_id}, Topic: {book.topic}, Current Page: {book.current_page}, Total Pages: {book.total_pages}")
        else:
            print(f"No books found for {username}.")

# Example Usage
if __name__ == "__main__":
    app = EBookApplication()

    while True:
        print("\nE-Book Application")
        print("1. Add/Update Book for User")
        print("2. Update Current Page")
        print("3. View User's Books")
        print("4. List All Books for a User")
        print("5. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            username = input("Enter username: ")
            book_id = input("Enter book ID: ")
            total_pages = int(input("Enter total number of pages: "))
            topic = input("Enter topic: ")
            app.add_or_update_user(username, book_id, total_pages, topic)

        elif choice == "2":
            username = input("Enter username: ")
            book_id = input("Enter book ID: ")
            page_number = int(input("Enter current page number: "))
            app.update_current_page(username, book_id, page_number)

        elif choice == "3":
            username = input("Enter username: ")
            books = app.get_user_books(username)
            if books:
                print("\nUser's Books:")
                for book_id, info in books.items():
                    print(f"Book ID: {book_id}")
                    print(f"  Topic: {info['topic']}")
                    print(f"  Total Pages: {info['total_pages']}")
                    print(f"  Current Page: {info['current_page']}\n")
            else:
                print("No record found for this user.")

        elif choice == "4":
            username = input("Enter username: ")
            app.list_books(username)

        elif choice == "5":
            print("Exiting application. Goodbye!")
            break

        else:
            print("Invalid choice. Please try again.")
