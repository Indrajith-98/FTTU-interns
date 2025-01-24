import sqlite3

class EBook:
    def __init__(self, db_name="ebook_library.db"):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self._create_tables()

    def _create_tables(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS books (
                book_id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                total_pages INTEGER NOT NULL
            )
        ''')
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS reading_status (
                status_id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER NOT NULL,
                book_id INTEGER NOT NULL,
                current_page INTEGER NOT NULL,
                current_topic TEXT NOT NULL,
                FOREIGN KEY (user_id) REFERENCES users(user_id),
                FOREIGN KEY (book_id) REFERENCES books(book_id)
            )
        ''')
        self.conn.commit()

    def add_book(self, title, total_pages):
        self.cursor.execute(
            "INSERT INTO books (title, total_pages) VALUES (?, ?)", 
            (title, total_pages)
        )
        self.conn.commit()

    def delete_book(self, book_id):
        self.cursor.execute("DELETE FROM books WHERE book_id = ?", (book_id,))
        self.conn.commit()

    def start_reading(self, user_id, book_id, start_page, start_topic):
        self.cursor.execute(
            "INSERT INTO reading_status (user_id, book_id, current_page, current_topic) VALUES (?, ?, ?, ?)",
            (user_id, book_id, start_page, start_topic)
        )
        self.conn.commit()

    def update_page(self, user_id, book_id, new_page, new_topic):
        self.cursor.execute(
            "UPDATE reading_status SET current_page = ?, current_topic = ? WHERE user_id = ? AND book_id = ?",
            (new_page, new_topic, user_id, book_id)
        )
        self.conn.commit()

    def get_reading_status(self, user_id, book_id):
        self.cursor.execute(
            """
            SELECT users.name, books.title, reading_status.current_page, reading_status.current_topic
            FROM reading_status
            JOIN users ON reading_status.user_id = users.user_id
            JOIN books ON reading_status.book_id = books.book_id
            WHERE reading_status.user_id = ? AND reading_status.book_id = ?
            """,
            (user_id, book_id)
        )
        return self.cursor.fetchone()

    def close(self):
        self.conn.close()
