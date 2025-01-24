import sqlite3
import json

class User:
    def __init__(self, user_id):
        self.conn = sqlite3.connect('book_data.db')
        self.cursor = self.conn.cursor()
        self.user_id = user_id

    def get_books(self):
        self.cursor.execute('SELECT bookdetails FROM user_books WHERE user_id = ?', (self.user_id,))
        result = self.cursor.fetchone()

        if result:
            bookdetails = json.loads(result[0])  
            return bookdetails
        else:
            return {}
    def change_page(self, book_name, new_page_no):
        bookdetails = self.get_books()

        if book_name in bookdetails:
            bookdetails[book_name] = new_page_no
            self.cursor.execute('''
                UPDATE user_books
                SET bookdetails = ?
                WHERE user_id = ?
            ''', (json.dumps(bookdetails), self.user_id))
            self.conn.commit()
            print(f"Page number of '{book_name}' updated to {new_page_no}.")
        else:
            print(f"Book '{book_name}' not found in your collection.")

    def display_books(self):
        bookdetails = self.get_books()
        if bookdetails:
            print("Your Current Books:")
            for book, page_no in bookdetails.items():
                print(f"Book: {book}, Page No: {page_no}")
        else:
            print("You have no books in your collection.")

    def close_connection(self):
            self.conn.close()