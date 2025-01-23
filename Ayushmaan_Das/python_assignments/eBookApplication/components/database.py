import sqlite3
from components.book import Book

class DatabaseManager:
    def __init__(self, database_name="books.db"):
        self.database_name = database_name
        self.conn = sqlite3.connect(self.database_name)
        self.create_table()

    def create_table(self):
        """Create the books table if it doesn't exist."""
        query = """
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            topic TEXT NOT NULL,
            total_pages INTEGER NOT NULL,
            current_page INTEGER NOT NULL
        );
        """
        self.conn.execute(query)
        self.conn.commit()

    def add_or_update_book(self, book):
        """Add a new book or update the record for an existing user."""
        query = """
        INSERT INTO books (username, topic, total_pages, current_page)
        VALUES (?, ?, ?, ?)
        ON CONFLICT(username) DO UPDATE SET
            topic=excluded.topic,
            total_pages=excluded.total_pages,
            current_page=excluded.current_page;
        """
        self.conn.execute(query, (book.username, book.topic, book.total_pages, book.current_page))
        self.conn.commit()

    def get_book(self, username):
        """Retrieve a book record by username."""
        query = "SELECT username, topic, total_pages, current_page FROM books WHERE username = ?;"
        cursor = self.conn.cursor()
        cursor.execute(query, (username,))
        result = cursor.fetchone()

        if result:
            return Book(username=result[0], topic=result[1], total_pages=result[2], current_page=result[3])
        return None

    def delete_book(self, username):
        """Delete a book record by username."""
        query = "DELETE FROM books WHERE username = ?;"
        self.conn.execute(query, (username,))
        self.conn.commit()

    def list_all_books(self):
        """Retrieve all book records."""
        query = "SELECT username, topic, total_pages, current_page FROM books;"
        cursor = self.conn.cursor()
        cursor.execute(query)
        rows = cursor.fetchall()

        return [Book(username=row[0], topic=row[1], total_pages=row[2], current_page=row[3]) for row in rows]

    def __del__(self):
        self.conn.close()
