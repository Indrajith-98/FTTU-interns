import sqlite3

class Admin:
    def __init__(self):
        self.conn = sqlite3.connect('book_data.db')
        self.cursor = self.conn.cursor()

    def load_books(self, books):
        for book in books:
            book_name, page_no = book
            self.insert_book(book_name, page_no)

    def insert_book(self, book_name, page_no):
        try:
            self.cursor.execute('''
                INSERT INTO books (book_name, page_no)
                VALUES (?, ?)
            ''', (book_name, page_no))
            self.conn.commit()
            print(f"Book '{book_name}' with {page_no} pages added successfully!")
        except sqlite3.IntegrityError:
            print(f"Error: Book '{book_name}' already exists in the database.")

    def close_connection(self):
        self.conn.close()
