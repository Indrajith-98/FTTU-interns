import sqlite3
from config import DB_PATH

class Book:
    def __init__(self, title, page_count=0):
        self.title = title
        self.page_count = page_count
        self.username = None
        self.current_page = 0

    def load_book(self, username):
        """Load a book for the user."""
        self.username = username
        with sqlite3.connect(DB_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT current_page FROM books WHERE title = ? AND username = ?", (self.title, self.username))
            result = cursor.fetchone()
            if result:
                self.current_page = result[0]
                print(f"Resuming {self.title} for {self.username} from page {self.current_page}")
            else:
                self.current_page = 1
                cursor.execute("INSERT OR IGNORE INTO books (title, username, current_page) VALUES (?, ?, ?)", 
                               (self.title, self.username, self.current_page))
                conn.commit()
                print(f"Started reading {self.title} by {self.username} from page 1")

    def update_progress(self):
        """Update the user's reading progress."""
        with sqlite3.connect(DB_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute("UPDATE books SET current_page = ? WHERE title = ? AND username = ?", 
                           (self.current_page, self.title, self.username))
            conn.commit()

    def display_progress(self):
        """Display the current progress."""
        print(f"Book: {self.title}")
        print(f"Username: {self.username}")
        print(f"Current Page: {self.current_page}/{self.page_count}")
