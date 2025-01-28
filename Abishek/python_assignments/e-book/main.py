import sqlite3

class DatabaseManager:
    def __init__(self, db_name="ebook_app.db"):
        self.connection = sqlite3.connect(db_name)
        self.cursor = self.connection.cursor()
        self.create_tables()

    def create_tables(self):
        # Create Users table
        self.cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )''')

        # Create Books table
        self.cursor.execute('''
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT UNIQUE NOT NULL,
            author TEXT NOT NULL,
            total_pages INTEGER NOT NULL,
            readers_count INTEGER DEFAULT 0
        )''')

        # Create Reading Progress table
        self.cursor.execute('''
        CREATE TABLE IF NOT EXISTS reading_progress (
            user_id INTEGER NOT NULL,
            book_id INTEGER NOT NULL,
            current_page INTEGER NOT NULL,
            current_topic TEXT NOT NULL,
            PRIMARY KEY (user_id, book_id),
            FOREIGN KEY (user_id) REFERENCES users(id),
            FOREIGN KEY (book_id) REFERENCES books(id)
        )''')
        self.connection.commit()

    def execute_query(self, query, params=()):
        self.cursor.execute(query, params)
        self.connection.commit()

    def fetch_one(self, query, params=()):
        self.cursor.execute(query, params)
        return self.cursor.fetchone()

    def fetch_all(self, query, params=()):
        self.cursor.execute(query, params)
        return self.cursor.fetchall()

    def close(self):
        self.connection.close()

class Book:
    def __init__(self, db):
        self.db = db

    def add_book(self, title, author, total_pages):
        query = "INSERT INTO books (title, author, total_pages) VALUES (?, ?, ?)"
        self.db.execute_query(query, (title, author, total_pages))

    def list_books(self):
        return self.db.fetch_all("SELECT * FROM books")

    def update_readers_count(self, book_id, increment=True):
        query = "UPDATE books SET readers_count = readers_count + ? WHERE id = ?"
        self.db.execute_query(query, (1 if increment else -1, book_id))

class User:
    def __init__(self, db):
        self.db = db

    def register(self, username, password):
        try:
            query = "INSERT INTO users (username, password) VALUES (?, ?)"
            self.db.execute_query(query, (username, password))
            print("User registered successfully!")
        except sqlite3.IntegrityError:
            print("Username already exists. Please choose a different username.")

    def login(self, username, password):
        query = "SELECT * FROM users WHERE username = ? AND password = ?"
        user = self.db.fetch_one(query, (username, password))
        return user

    def update_reading_progress(self, user_id, book_id, page, topic):
        # Check if progress exists
        query = "SELECT * FROM reading_progress WHERE user_id = ? AND book_id = ?"
        progress = self.db.fetch_one(query, (user_id, book_id))

        if progress:
            # Update existing progress
            query = "UPDATE reading_progress SET current_page = ?, current_topic = ? WHERE user_id = ? AND book_id = ?"
            self.db.execute_query(query, (page, topic, user_id, book_id))
        else:
            # Insert new progress
            query = "INSERT INTO reading_progress (user_id, book_id, current_page, current_topic) VALUES (?, ?, ?, ?)"
            self.db.execute_query(query, (user_id, book_id, page, topic))

    def get_book_progress(self, user_id, book_id):
        query = "SELECT current_page, current_topic FROM reading_progress WHERE user_id = ? AND book_id = ?"
        return self.db.fetch_one(query, (user_id, book_id))

# Main program logic
def main():
    db = DatabaseManager()
    book_manager = Book(db)
    user_manager = User(db)

    while True:
        print("\n" + "=" * 30)
        print("      Welcome to the E-Book App      ")
        print("=" * 30)
        print("\n1. Register")
        print("2. Login")
        print("3. Add Book (Admin)")
        print("4. Exit")
        print("=" * 30)
        choice = input("Choose an option: ")

        if choice == "1":
            print("\n--- Register ---")
            username = input("Enter a username: ")
            password = input("Enter a password: ")
            user_manager.register(username, password)

        elif choice == "2":
            print("\n--- Login ---")
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            user = user_manager.login(username, password)

            if user:
                print(f"\nWelcome back, {username}!")
                user_id = user[0]
                while True:
                    print("\n" + "-" * 30)
                    print("      User Dashboard      ")
                    print("-" * 30)
                    print("\n1. View Books")
                    print("2. Read a Book")
                    print("3. Logout")
                    print("-" * 30)
                    user_choice = input("Choose an option: ")

                    if user_choice == "1":
                        print("\n--- Available Books ---")
                        books = book_manager.list_books()
                        if books:
                            for book in books:
                                print(f"{book[0]}. {book[1]} by {book[2]} "
                                      f"({book[3]} pages, {book[4]} readers)")
                        else:
                            print("No books available.")

                    elif user_choice == "2":
                        print("\n--- Read a Book ---")
                        try:
                            book_id = int(input("Enter the Book ID to read: "))
                        except ValueError:
                            print("Invalid input. Please enter a valid Book ID.")
                            continue

                        book = db.fetch_one("SELECT * FROM books WHERE id = ?", (book_id,))

                        if book:
                            book_manager.update_readers_count(book_id, increment=True)
                            progress = user_manager.get_book_progress(user_id, book_id)

                            if progress:
                                page, topic = progress
                                print(f"\nResuming {book[1]} from page {page}: {topic}")
                            else:
                                page, topic = 1, "Introduction"
                                user_manager.update_reading_progress(user_id, book_id, page, topic)

                            while True:
                                print("\n" + "-" * 30)
                                print(f"Reading {book[1]} by {book[2]}")
                                print(f"Page {page}: {topic}")
                                print("-" * 30)
                                print("1. Next Page")
                                print("2. Exit Book")
                                print("-" * 30)
                                action = input("Choose an action: ")

                                if action == "1":
                                    page += 1
                                    topic = f"Topic {page}"  # Example topic update
                                    if page > book[3]:
                                        print("\nEnd of the book!")
                                        break
                                    user_manager.update_reading_progress(user_id, book_id, page, topic)

                                elif action == "2":
                                    print("\nExiting the book.")
                                    break

                        else:
                            print("Book not found!")

                    elif user_choice == "3":
                        print("\nLogging out...")
                        break

            else:
                print("\nInvalid username or password.")

        elif choice == "3":
            print("\n--- Add Book (Admin) ---")
            admin_password = input("Enter admin password: ")
            if admin_password == ADMIN_PASSWORD:
                title = input("Enter the book title: ")
                author = input("Enter the author's name: ")
                try:
                    total_pages = int(input("Enter the total number of pages: "))
                except ValueError:
                    print("Invalid input. Please enter a number for total pages.")
                    continue

                try:
                    book_manager.add_book(title, author, total_pages)
                    print(f"\nBook '{title}' added successfully!")
                except sqlite3.IntegrityError:
                    print("A book with this title already exists.")
            else:
                print("\nInvalid admin password. Access denied.")

        elif choice == "4":
            print("\nGoodbye!")
            db.close()
            break

        else:
            print("\nInvalid choice. Please choose a valid option.")

if __name__ == "__main__":

    ADMIN_PASSWORD = "admin123"
    main()