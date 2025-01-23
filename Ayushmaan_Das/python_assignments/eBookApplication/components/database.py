import sqlite3


class DatabaseManager:
    def __init__(self, database_name="books.db"):
        self.conn = sqlite3.connect(database_name)
        self.create_tables()

    def create_tables(self):
        """Create the tables if they don't exist."""
        users_table = """
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE
        );
        """

        books_table = """
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            total_pages INTEGER NOT NULL
        );
        """

        user_books_table = """
        CREATE TABLE IF NOT EXISTS user_books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            book_id INTEGER NOT NULL,
            current_page INTEGER DEFAULT 0,
            FOREIGN KEY (user_id) REFERENCES users (id),
            FOREIGN KEY (book_id) REFERENCES books (id),
            UNIQUE (user_id, book_id)
        );
        """

        self.conn.execute(users_table)
        self.conn.execute(books_table)
        self.conn.execute(user_books_table)
        self.conn.commit()

    # ---- User Methods ----
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
        return result if result else None

    # ---- Book Methods ----
    def add_book(self, title, total_pages):
        """Add a new book."""
        query = "INSERT INTO books (title, total_pages) VALUES (?, ?);"
        cursor = self.conn.cursor()
        cursor.execute(query, (title, total_pages))
        self.conn.commit()
        return cursor.lastrowid

    def get_book(self, title):
        """Retrieve a book by title."""
        query = "SELECT id, title, total_pages FROM books WHERE title = ?;"
        cursor = self.conn.cursor()
        cursor.execute(query, (title,))
        result = cursor.fetchone()
        return result if result else None

    # ---- User-Book Methods ----
    def add_user_book(self, user_id, book_id):
        """Associate a user with a book and start tracking progress."""
        query = "INSERT INTO user_books (user_id, book_id) VALUES (?, ?);"
        cursor = self.conn.cursor()
        try:
            cursor.execute(query, (user_id, book_id))
            self.conn.commit()
            return cursor.lastrowid
        except sqlite3.IntegrityError:
            raise ValueError("User is already reading this book.")

    def update_progress(self, user_id, book_id, pages_read):
        """Update the progress for a user on a specific book."""
        query = """
        SELECT current_page, total_pages
        FROM user_books
        JOIN books ON user_books.book_id = books.id
        WHERE user_books.user_id = ? AND user_books.book_id = ?;
        """
        cursor = self.conn.cursor()
        cursor.execute(query, (user_id, book_id))
        result = cursor.fetchone()

        if not result:
            raise ValueError("User is not reading this book.")

        current_page, total_pages = result
        new_page = current_page + pages_read

        if new_page > total_pages:
            raise ValueError("Pages read cannot exceed total pages.")

        update_query = "UPDATE user_books SET current_page = ? WHERE user_id = ? AND book_id = ?;"
        cursor.execute(update_query, (new_page, user_id, book_id))
        self.conn.commit()

    def get_user_book_status(self, user_id, book_id):
        """Get the current status of a book being read by a user."""
        query = """
        SELECT books.title, books.total_pages, user_books.current_page
        FROM user_books
        JOIN books ON user_books.book_id = books.id
        WHERE user_books.user_id = ? AND user_books.book_id = ?;
        """
        cursor = self.conn.cursor()
        cursor.execute(query, (user_id, book_id))
        result = cursor.fetchone()
        if not result:
            raise ValueError("User is not reading this book.")
        return {
            "title": result[0],
            "total_pages": result[1],
            "current_page": result[2],
        }

    def list_all_books(self):
        """Retrieve all books in the system."""
        query = "SELECT id, title, total_pages FROM books;"
        cursor = self.conn.cursor()
        cursor.execute(query)
        return cursor.fetchall()

    def list_all_users_with_books(self):
        """Retrieve all users along with their books and progress."""
        query = """
        SELECT users.username, books.title, user_books.current_page, books.total_pages
        FROM user_books
        JOIN users ON user_books.user_id = users.id
        JOIN books ON user_books.book_id = books.id
        ORDER BY users.username;
        """
        cursor = self.conn.cursor()
        cursor.execute(query)
        rows = cursor.fetchall()
        result = {}
        for row in rows:
            username, book_title, current_page, total_pages = row
            if username not in result:
                result[username] = []
            result[username].append({
                "title": book_title,
                "current_page": current_page,
                "total_pages": total_pages,
            })
        return result

    def __del__(self):
        self.conn.close()
