# user_manager.py
import sqlite3
import hashlib

DB_PATH = "data/app.db"

def init_db():
    """Initializes the SQLite database."""
    with sqlite3.connect(DB_PATH) as conn:
        cursor = conn.cursor()
        cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
        """)
        cursor.execute("""
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            book_name TEXT NOT NULL,
            last_page INTEGER NOT NULL,
            UNIQUE(user_id, book_name),
            FOREIGN KEY (user_id) REFERENCES users (id)
        )
        """)
        conn.commit()


def hash_password(password):
    """Hashes a password for secure storage."""
    return hashlib.sha256(password.encode()).hexdigest()



def register_user(username, password):
    """Registers a new user."""
    with sqlite3.connect(DB_PATH) as conn:
        cursor = conn.cursor()
        try:
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", 
                           (username, hash_password(password)))
            conn.commit()
            print("User registered successfully!")
        except sqlite3.IntegrityError:
            print("Username already exists!")

def authenticate_user(username, password):
    """Authenticates an existing user."""
    with sqlite3.connect(DB_PATH) as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT id, password FROM users WHERE username = ?", (username,))
        result = cursor.fetchone()
        print(result)
        if result and result[1] == hash_password(password):
            print(f"Welcome back, {username}!")
            return result[0]  # Return user_id
        else:
            print("Invalid username or password.")
            return None

def update_last_read(user_id, book_name, last_page):
    """Updates the last read page for a user and book."""
    with sqlite3.connect(DB_PATH) as conn:
        cursor = conn.cursor()
        cursor.execute("""
        INSERT INTO books (user_id, book_name, last_page)
        VALUES (?, ?, ?)
        ON CONFLICT(user_id, book_name) DO UPDATE SET last_page = ?
        """, (user_id, book_name, last_page, last_page))
        conn.commit()


def get_last_read(user_id, book_name):
    """Retrieves the last read page for a user and book."""
    with sqlite3.connect(DB_PATH) as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT last_page FROM books WHERE user_id = ? AND book_name = ?", 
                       (user_id, book_name))
        result = cursor.fetchone()
        return result[0] if result else 0