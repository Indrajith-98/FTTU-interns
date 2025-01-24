class Book:
    
    def __init__(self, book_title=None, author=None, total_pages=None):
        self.book_title = book_title
        self.author = author
        self.total_pages = total_pages
    
    def view_books(self, cursor):
        cursor.execute("SELECT * FROM books_table")
        books = cursor.fetchall()
        for book in books:
            print(f"Book ID: {book[0]}, Title: {book[1]}, Author: {book[2]}, Total Pages: {book[3]}")
        print("\n")
    
    def add_book(self, cursor, conn):
        cursor.execute("INSERT INTO books_table (book_title, author, total_pages) VALUES (?, ?, ?)", (self.book_title, self.author, self.total_pages))
        conn.commit()
        print("Book added successfully\n")
            
       