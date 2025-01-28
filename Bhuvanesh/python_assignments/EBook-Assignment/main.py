from book import Book
from user import User
from admin import Admin
from user_auth import UserAuth

def Operations(user_id):
    while(True):
        print("1.Add a book to your Checklist\n2.Read the pre-existing book\n3.Exit")
        Choice=int(input())
        if Choice==1:
            user=User(user_id)
            user.display_books()
            book=Book()
            book.display_books()
            book_name=input("Enter the book name")
            book_page=int(input("Enter the current page intitially it is good to enter 0"))
            book.add_book_to_user(user_id, book_name, book_page)
        elif Choice==2:
            user=User(user_id)
            user.display_books()
            book=Book()
            book_name=input("Enter the book name you are going to read")
            if (book.is_book_in_user_books(user_id,book_name)):
                while(True):
                    print("If you want to change the page please enter the page no if you want to change the book please press 10000")
                    page_no=int(input())
                    if (page_no==10000):
                        break
                    book=Book()
                    book.add_book_to_user(user_id, book_name, page_no)
            
        else:
            break

        


while True:
    print("Welcome to the Ebook Management system please Enter your role \n1.Admin\n2.User\n3.Exit")
    role=int(input())
    if role==1:
        print("Enter Your password")
        Admin_Password=input()
        if Admin_Password=="HelloWorld":
            print("Logged in successfully")
            print("You have only one operation of Adding the book")
            Book_Count=int(input("Enter the number of books you are going to add "))
            admin = Admin()
            books_to_insert = []
            for i in range(0,Book_Count):
                Book_Detail=(input("Enter the Book Name "),int(input("Enter the Page Numbers ")))
                books_to_insert.append(Book_Detail)
            admin.load_books(books_to_insert)
            admin.close_connection()
    elif role==2:
        print("If you are a existing user then press 1 else press 2")
        User_info=int(input())
        if User_info==2:
            auth = UserAuth()
            User_id=input("Enter the user_id ")
            User_Name=input("Enter your username ")
            Password=input("Enter your password ")
            auth.register_user(User_id, User_Name, Password)
            Operations(User_id)
        else:
            auth = UserAuth()
            user_id = auth.authenticate_user(int(input("Enter the user_id ")), input("Enter the password "))
            if user_id:
                print(f"User authenticated with ID: {user_id}")
                Operations(user_id)
            else:
                print("Login failed")
    else:
        break
        
        