import json

class User:
    def __init__(self, username, password):
        self.username = username
        self.password = password
        
    def register(self, cursor, conn):
        cursor.execute("INSERT INTO users_table (username, password) VALUES (?, ?)", (self.username, self.password))
        conn.commit()
        print("User registered successfully!\n")
        
    def login(self, cursor):
        cursor.execute("SELECT * FROM users_table WHERE username=? AND password=?", (self.username, self.password))
        user = cursor.fetchone()
        
        if user:
            self.user_id = user[0]
            print("User logged in successfully!\n")
            return True
        return False
        
    def start_reading(self, cursor, conn, book_id, page_number):
        cursor.execute("SELECT book_title, total_pages FROM books_table WHERE book_id=?", (book_id,))
        book = cursor.fetchone()
        
        if book and (page_number > book[1] or page_number < 1):
            print("Invalid page number\n")
            return
        
        if book:
            book_title = book[0]
            
            cursor.execute("SELECT book_details FROM reading_data_table WHERE userid=?", (self.user_id,))
            existing_books = cursor.fetchone()
            
            if existing_books:
                
                current_books = json.loads(existing_books[0])
                current_books[book_title] = page_number
                
                cursor.execute('''
                    UPDATE reading_data_table
                    SET book_details = ?
                    WHERE userid = ?
                ''', (json.dumps(current_books), self.user_id))
                
                conn.commit()
                print(f"Started reading book {book_id} at page {page_number}\n")
                
            else:
                cursor.execute("INSERT INTO reading_data_table (userid, username, book_details) VALUES (?, ?, ?)", (self.user_id, self.username, json.dumps({book_title: page_number})))
                print(f"Started reading book {book_id} at page {page_number}\n")
            
        else:
            print("Book not found\n")
        
    def view_reading_history(self, cursor):
        cursor.execute("SELECT book_details FROM reading_data_table WHERE userid=?", (self.user_id,))
        books = cursor.fetchone()
        if books:
            books = json.loads(books[0])
            for book in books:
                print(f"Book Title: {book}, Page Number: {books[book]}")
            print("\n")
        else:
            print("No books found in history\n")