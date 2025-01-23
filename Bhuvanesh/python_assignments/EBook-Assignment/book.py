import sqlite3
import json

class Book:
    def __init__(self):
        self.conn = sqlite3.connect('book_data.db')
        self.cursor = self.conn.cursor()

    def display_books(self):
        self.cursor.execute('SELECT book_name, page_no FROM books')
        books = self.cursor.fetchall()

        if not books:
            print("No books available in the database.")
            return

        print("Books in the database:")
        for book_name, page_no in books:
            print(f"Book: {book_name}, Pages: {page_no}")

    def add_book_to_user(self, user_id, book_name, current_page):
        self.cursor.execute('SELECT page_no FROM books WHERE book_name = ?', (book_name,))
        book_data = self.cursor.fetchone()

        if not book_data:
            print(f"Book '{book_name}' not found in the book database.")
            return

        actual_page_limit = book_data[0]  

        if current_page > actual_page_limit:
            print(f"Warning: The current page number ({current_page}) exceeds the actual page limit of {actual_page_limit} for '{book_name}'.")
            user_response = input(f"Do you want to proceed with this page number? (yes/no): ").strip().lower()
            if user_response != 'yes':
                print("Page number update canceled.")
                return

        self.cursor.execute('SELECT bookdetails FROM user_books WHERE user_id = ?', (user_id,))
        existing_book_data = self.cursor.fetchone()

        if existing_book_data:
            bookdetails = json.loads(existing_book_data[0])
            if book_name in bookdetails:
                print(f"Warning: The book '{book_name}' is already in the system with {bookdetails[book_name]} pages.")
                user_response = input(f"Do you want to overwrite the page number with {current_page}? (yes/no): ").strip().lower()
                if user_response == 'yes':
                    bookdetails[book_name] = current_page
                    print(f"Book '{book_name}' page number updated to {current_page}.")
                else:
                    print(f"Book '{book_name}' was not updated.")
            else:
                bookdetails[book_name] = current_page
                print(f"Book '{book_name}' with {current_page} pages added.")
            self.cursor.execute(''' 
                UPDATE user_books
                SET bookdetails = ? 
                WHERE user_id = ? 
            ''', (json.dumps(bookdetails), user_id))
            self.conn.commit()
        else:
            bookdetails = {book_name: current_page}
            self.cursor.execute(''' 
                INSERT INTO user_books (user_id, bookdetails)
                VALUES (?, ?) 
            ''', (user_id, json.dumps(bookdetails)))
            self.conn.commit()
            print(f"Book '{book_name}' with {current_page} pages added to the reading list.")
    def is_book_in_user_books(self, user_id, book_name):
        self.cursor.execute('SELECT bookdetails FROM user_books WHERE user_id = ?', (user_id,))
        existing_book_data = self.cursor.fetchone()

        if existing_book_data:
            bookdetails = json.loads(existing_book_data[0])  
            if book_name in bookdetails:
                return True  
            else:
                return False  
        else:
            return False  


    def close_connection(self):
        self.conn.close()
