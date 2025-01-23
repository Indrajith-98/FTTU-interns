import sqlite3
from components.book import Book
from components.user import User


class DatabaseManager:
    def __init__(self, database_name="books.db"):
        self.conn = sqlite3.connect(database_name)
        self.create_tables()

    def create_tables(self):
        """Create the users and books tables if they don't exist."""
        user_table = """
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE
        );
        """

        book_table = """
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            total_pages INTEGER NOT NULL,
            current_page INTEGER DEFAULT 0,
            user_id INTEGER NOT NULL,
            FOREIGN KEY (user_id) REFERENCES users (id)
        );
        """

        self.conn.execute(user_table)
        self.conn.execute(book_table)
        self.conn.commit()

    def add_user(self, username):
        """Add a new user."""
        query = "INSERT INTO users (username) VALUES (?);"
        cursor = self.conn.cursor()
        try:
            cursor.execute(query, (username,))
            self.conn.commit()
            return cursor.lastrowid
        except sqlite3.IntegrityError:
            raise ValueError("Username already exists.")

    def get_user(self, username):
        """Retrieve a user by username."""
        query = "SELECT id, username FROM users WHERE username = ?;"
        cursor = self.conn.cursor()
        cursor.execute(query, (username,))
        result = cursor.fetchone()
        if result:
            return User(user_id=result[0], username=result[1])
        return None

    def add_book(self, user_id, title, total_pages):
        """Add a new book for a user."""
        query = """
        INSERT INTO books (title, total_pages, user_id) 
        VALUES (?, ?, ?);
        """
        cursor = self.conn.cursor()
        cursor.execute(query, (title, total_pages, user_id))
        self.conn.commit()
        return cursor.lastrowid

    def get_books_by_user(self, user_id):
        """Retrieve all books for a user."""
        query = """
        SELECT id, title, total_pages, current_page FROM books 
        WHERE user_id = ?;
        """
        cursor = self.conn.cursor()
        cursor.execute(query, (user_id,))
        rows = cursor.fetchall()
        return [
            Book(book_id=row[0], title=row[1], total_pages=row[2], current_page=row[3])
            for row in rows
        ]

    def get_book_details(self, book_id):
        """Retrieve details of a specific book."""
        query = """
        SELECT id, title, total_pages, current_page FROM books 
        WHERE id = ?;
        """
        cursor = self.conn.cursor()
        cursor.execute(query, (book_id,))
        row = cursor.fetchone()
        if row:
            return Book(book_id=row[0], title=row[1], total_pages=row[2], current_page=row[3])
        raise ValueError("Book not found.")

    def list_all_books(self):
        """Retrieve all books in the system."""
        query = """
        SELECT books.id, books.title, books.total_pages, books.current_page, users.username 
        FROM books
        JOIN users ON books.user_id = users.id;
        """
        cursor = self.conn.cursor()
        cursor.execute(query)
        rows = cursor.fetchall()
        return [
            {
                "book_id": row[0],
                "title": row[1],
                "total_pages": row[2],
                "current_page": row[3],
                "username": row[4],
            }
            for row in rows
        ]

    def list_all_users_with_books(self):
        """Retrieve all users along with their books."""
        query = """
        SELECT users.id, users.username, books.id, books.title, books.current_page, books.total_pages 
        FROM users
        LEFT JOIN books ON users.id = books.user_id
        ORDER BY users.id;
        """
        cursor = self.conn.cursor()
        cursor.execute(query)
        rows = cursor.fetchall()

        users = {}
        for row in rows:
            user_id = row[0]
            username = row[1]
            if user_id not in users:
                users[user_id] = {"username": username, "books": []}
            if row[2] is not None:  # If the user has books
                users[user_id]["books"].append(
                    {
                        "book_id": row[2],
                        "title": row[3],
                        "current_page": row[4],
                        "total_pages": row[5],
                    }
                )

        return users

    def update_book_progress(self, book_id, pages_read):
        """Update the progress of a book."""
        cursor = self.conn.cursor()

        query = "SELECT current_page, total_pages FROM books WHERE id = ?;"
        cursor.execute(query, (book_id,))
        result = cursor.fetchone()
        if not result:
            raise ValueError("Book not found.")

        current_page, total_pages = result
        new_page = current_page + pages_read
        if new_page > total_pages:
            raise ValueError("Pages read cannot exceed total pages.")

        update_query = """
        UPDATE books SET current_page = ? WHERE id = ?;
        """
        cursor.execute(update_query, (new_page, book_id))
        self.conn.commit()

    def __del__(self):
        self.conn.close()
