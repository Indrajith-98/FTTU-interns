import sqlite3
import hashlib
from config import DB_PATH

class UserManager:
    @staticmethod
    def init_db():
        """Initialize the database for storing user and book data."""
        with sqlite3.connect(DB_PATH) as conn:
            cursor = conn.cursor()
            # Create users table
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    password TEXT NOT NULL
                )
            """)
            # Create books table
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS books (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    title TEXT NOT NULL,
                    username TEXT NOT NULL,
                    current_page INTEGER NOT NULL,
                    UNIQUE(title, username)
                )
            """)
            conn.commit()

    @staticmethod
    def register_user(username, password):
        """Register a new user."""
        password_hash = hashlib.sha256(password.encode()).hexdigest()
        with sqlite3.connect(DB_PATH) as conn:
            cursor = conn.cursor()
            try:
                cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password_hash))
                conn.commit()
                print(f"User '{username}' registered successfully!")
            except sqlite3.IntegrityError:
                print(f"Username '{username}' is already taken.")

    @staticmethod
    def authenticate_user(username, password):
        """Authenticate a user."""
        password_hash = hashlib.sha256(password.encode()).hexdigest()
        with sqlite3.connect(DB_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT id FROM users WHERE username = ? AND password = ?", (username, password_hash))
            result = cursor.fetchone()
            if result:
                print(f"Welcome back, {username}!")
                return result[0]
            else:
                print("Invalid username or password.")
                return None
