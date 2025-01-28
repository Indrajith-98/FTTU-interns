import sqlite3
from books import Book
from users import User

def main():
    conn = sqlite3.connect('Ebook.db')
    cursor = conn.cursor()
    
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS users_table (
        userid INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL,
        password TEXT NOT NULL
    )
    ''')
    
    cursor.execute('''
    INSERT INTO users_table (username, password) VALUES ('admin', 'admin')
    ''')
    
    
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS reading_data_table (
        userid INTEGER,
        username TEXT NOT NULL,
        book_details TEXT NOT NULL,  -- Store book details as a JSON string
        FOREIGN KEY (userid) REFERENCES users(userid)
    )
    ''')
    
    
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS books_table (
        book_id INTEGER PRIMARY KEY AUTOINCREMENT,
        book_title TEXT NOT NULL,
        author TEXT NOT NULL,
        total_pages INTEGER NOT NULL
    )
    ''')
    
    logged_in_user = None
    
    while(True):
        input_choice = int(input("Enter your choice\n"
                                "1 to register\n"
                                "2 to login\n"
                                "3 to view all books\n"
                                "4 to add books (only admin)\n"
                                "5 to start reading a book\n"
                                "6 to view your history of book reading\n"
                                "7 to exit\n")
                           )
        
        if input_choice == 1:
            username = input("Enter username: ")
            if username == 'admin':
                print("Invalid username: can't use 'admin' as username\n")
                continue
            password = input("Enter password: ")
            user = User(username=username, password=password)
            user.register(cursor, conn)
            
        elif input_choice == 2:
            username = input("Enter username: ")
            password = input("Enter password: ")
            user = User(username=username, password=password)
            if user.login(cursor):
                logged_in_user = user
            else:
                print("Invalid username or password\n")
                continue
        
        elif input_choice == 3:
            book = Book()
            book.view_books(cursor)
            
        elif input_choice == 4:
            if not logged_in_user:
                print("Only admin can add books\n")
                continue
            elif logged_in_user.username != 'admin':
                print("Only admin can add books\n")
                continue
            
            book_title = input("Enter book title: ")
            author = input("Enter author: ")
            total_pages = int(input("Enter total pages: "))
            book = Book(book_title, author, total_pages)
            book.add_book(cursor, conn)
            
        elif input_choice == 5:
            if logged_in_user:
                book_id = int(input("Enter book id to read: "))
                page_number = int(input("Enter page number to start reading: "))
                logged_in_user.start_reading(cursor, conn, book_id, page_number)
            else:
                print("Please login first to read a book\n")
        
        elif input_choice == 6:
            if logged_in_user:
                logged_in_user.view_reading_history(cursor)
            else:
                print("Please login first to view your reading history\n")
            
        elif input_choice == 7:
            print("Goodbye. Come back soon!\n")
            break
        
        else:
            print("Invalid choice\n")
            
    conn.close()

if __name__ == '__main__':
    main()            
    
    
    
    

