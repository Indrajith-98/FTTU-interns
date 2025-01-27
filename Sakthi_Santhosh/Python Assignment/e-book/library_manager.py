import json
from book import Book


class LibraryManager:
    """Manages a collection of books in the library."""

    def __init__(self, file_path="library_data.json"):
        self.file_path = file_path
        self.books = self.load_library()

    def load_library(self):
        """Load the library data from JSON."""
        try:
            with open(self.file_path, 'r') as file:
                data = json.load(file)
                return {
                    title: Book(**details) for title, details in data.get("books", {}).items()
                }
        except (FileNotFoundError, json.JSONDecodeError):
            return {}

    def save_library(self):
        """Save the library data to JSON."""
        data = {"books": {title: book.to_dict() for title, book in self.books.items()}}
        with open(self.file_path, 'w') as file:
            json.dump(data, file, indent=4)

    def display_books(self):
        """Display all books in the library."""
        if not self.books:
            print("The library is empty. Add some books first.")
        else:
            print("\n--- Library Books ---")
            for i, title in enumerate(self.books, 1):
                print(f"{i}. {title}")
            print("---------------------")

    def add_book(self):
        """Add a new book to the library."""
        title = input("Enter the book title: ")
        if title in self.books:
            print("A book with this title already exists in the library.")
            return
        author = input("Enter the author's name: ")
        total_pages = int(input("Enter the total number of pages: "))
        topic = input("Enter the topic/genre of the book: ")
        chapters = self.get_chapters()
        self.books[title] = Book(title, author, total_pages, topic, chapters)
        self.save_library()
        print(f"Book '{title}' added to the library.")

    def get_chapters(self):
        """Ask the user to input chapter names."""
        chapters = []
        num_chapters = int(input("Enter the number of chapters: "))
        for i in range(num_chapters):
            chapter = input(f"Enter the name of chapter {i + 1}: ")
            chapters.append(chapter)
        return chapters

    def select_book(self):
        """Allow the user to select a book from the library."""
        if not self.books:
            print("The library is empty. Add some books first.")
            return None
        self.display_books()
        choice = int(input("Select a book by number: "))
        book_titles = list(self.books.keys())
        if 1 <= choice <= len(book_titles):
            return self.books[book_titles[choice - 1]]
        else:
            print("Invalid choice.")
            return None
