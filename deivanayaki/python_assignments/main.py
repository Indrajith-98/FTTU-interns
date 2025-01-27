import re
import os
import pandas as pd
from user import User
from book import Book

def validate_email(email):
    regex = r'([A-Za-z0-9]+[.-_])*[A-Za-z0-9]+@[A-Za-z0-9-]+(\.[A-Z|a-z]{2,})+'
    if re.match(regex, email):
        return True
    else:
        return False

def validate_password(password):
    regex = r'^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[^\w])[A-Za-z\d\W]{8,}$'
    if re.match(regex, password):
        return True
    else:
        return False

def get_valid_email():
     email=""
     while True:
        email=input("EMAIL : ")
        if validate_email(email):
            return email
        print("INVALID MAIL ID!! PLEASE TRY AGAIN...")

def get_valid_password():
    password=""
    print("PASSWORD SHOULD CONTAIN 1-UPPERCASE & LOWERCASE LETTER, 1 DIGIT & SPCL CHAR AND MIN LENGTH 8")
    while True:
        password=input("PASSWORD : ")
        if validate_password(password):
            return password
        print("INVALID PASSWORD!! PLEASE TRY AGAIN")

def choose_genre():
    while True:
        genre_list = ["FICTION","NON-FICTION","MYSTERY","THRILLER","BIOGRAPHY","HORROR","FANTASY","ADVENTURE","COOKBOOKS","HISTORY"]
        print("1. FICTION\n2. NON-FICTION\n3. MYSTERY\n4. THRILLER\n5. BIOGRAPHY\n6. HORROR\n7. FANTASY\n8. ADVENTURE\n9. COOKBOOKS\n10. HISTORY")
        ch=int(input("CHOOSE BOOK GENRE : "))
        if 0<ch<11:
            return genre_list[ch-1]
        print("PLEASE CHOOSE VALID GENRE!!")


def store_user_data2backend(user):
    user_details = user.to_csv()
    user_df = pd.DataFrame([user_details], columns=['Name', 'Email', 'Password', 'Favorite_Genre'])
    if os.path.exists("backend/users.txt"):
        existing_df = pd.read_csv("backend/users.txt")
        updated_df = pd.concat([existing_df, user_df], ignore_index=True)
    else:
        updated_df = user_df
    updated_df.to_csv("backend/users.txt", index=False)
    print("Data stored successfully!!")

def store_book_data2backend(book):
    book_details = book.to_csv()
    book_df = pd.DataFrame([book_details], columns=['Name', 'Author', 'Genre', 'Total Pages','Book Topics'])
    if os.path.exists("backend/books.txt"):
        existing_df = pd.read_csv("backend/books.txt")
        updated_df = pd.concat([existing_df, book_df], ignore_index=True)
    else:
        updated_df = book_df
    updated_df.to_csv("backend/books.txt", index=False)
    print("Book Data stored successfully!!")

def already_registered(email):
    if os.path.exists("backend/users.txt"):
        users_df = pd.read_csv("backend/users.txt")
        if email in users_df['Email'].values:
            return True
        else:
            return False
    print("USER NOT FOUND!!")
    return False

def validate_login(email,password):
    if os.path.exists("backend/users.txt"):
        users_df = pd.read_csv("backend/users.txt")
        user_row = users_df[(users_df['Email'] == email) & (users_df['Password'] == password)]
        if not user_row.empty:
            return User(user_row.iloc[0]['Name'], user_row.iloc[0]['Email'], user_row.iloc[0]['Password'], user_row.iloc[0]['Favorite_Genre'])
        return None

def fetch_all_book_readers():
    if os.path.exists("backend/book_readers.txt"):
        df = pd.read_csv("backend/book_readers.txt")
        if df.empty:
            print("No records found.")
        else:
            for index, row in df.iterrows():
                print("-" * 40)
                print(f"Record {index + 1}:")
                print("-" * 40)
                print(f"User        : {row['User']}")
                print(f"Book        : {row['Book']}")
                print(f"Page Number : {row['Page Number']}")
                print(f"Topic       : {row['Topic']}")
                print(f"Status      : {row['Status']}")
                print("-" * 40)
        return
    print("book_readers.txt not found.")

def switch_to_admin_portal():
    pwd=input("ENTER ADMIN PORTAL PASSWORD : ")
    if(pwd=="2003"):
        while True:
            print("1. ADD NEW BOOKS\n2. VIEW USER READING DETAILS\n3. EXIT")
            ch=int(input("CHOOSE YOUR TASK : "))
            if ch==1:
                print("ENTER BASIC BOOK DETAILS")
                name=input("BOOK NAME : ")
                author=input("BOOK AUTHOR NAME : ")
                genre=choose_genre()
                total_pgs=int(input("TOTAL NO. OF PAGES : "))
                book_topics={}
                while True:
                    topic=input("ENTER TOPICS (e-exit) : ")
                    if topic!='e':
                        print("LOWER & UPPER PG LIMIT : ")
                        topic_pg_limit=list(map(int,input().split(',')))
                        book_topics[topic]=topic_pg_limit
                    else:
                        break
                book=Book(name,author,genre,total_pgs,book_topics)
                store_book_data2backend(book)
            elif ch==2:
                fetch_all_book_readers()
            else:
                return

def fetch_books(fav_genre):
    books_df = pd.read_csv("backend/books.txt")
    books_df['Fav_Genre_Priority'] = books_df['Genre'].apply(lambda x: 1 if x == fav_genre else 0)
    sorted_books_df = books_df.sort_values(by='Fav_Genre_Priority', ascending=False).drop(columns=['Fav_Genre_Priority'])
    books = [
        Book(
            name=row['Name'], 
            author=row['Author'], 
            genre=row['Genre'], 
            total_pg=row['Total Pages'], 
            book_topics=eval(row['Book Topics'])  
        )
        for _, row in sorted_books_df.iterrows()
    ]
    return books

def get_topic_from_page(book, cur_pg_no):
    for topic, page_range in book.book_topics.items():
        min_page, max_page = page_range
        if min_page <= cur_pg_no <= max_page:
            return topic
    return None

def update_book_reader(current_user, selected_book, cur_pg_no):
    topic = get_topic_from_page(selected_book, cur_pg_no)
    if topic:
        record = {"User": [current_user.name],"Book": [selected_book.name],"Page Number": [cur_pg_no],"Topic": [topic],"Status":"Currently Reading"}
        reader_df = pd.DataFrame(record)
        updated_df=reader_df
        if os.path.exists("backend/book_readers.txt"):
            existing_df = pd.read_csv("backend/book_readers.txt")
            existing_record_idx = existing_df[(existing_df['User'] == current_user.name) & 
                                              (existing_df['Book'] == selected_book.name)].index
            if not existing_record_idx.empty:
                existing_df.loc[existing_record_idx, 'Status']="Currently Reading"
                existing_df.loc[existing_record_idx, 'Page Number'] = cur_pg_no
                existing_df.loc[existing_record_idx, 'Topic'] = topic
                existing_df.to_csv("backend/book_readers.txt", index=False)
                return
            else:
                updated_df = pd.concat([existing_df, reader_df], ignore_index=True)
        updated_df.to_csv("backend/book_readers.txt", index=False)

def get_cur_reading_pg(current_user,selected_book):
    if os.path.exists("backend/book_readers.txt"):
        existing_df = pd.read_csv("backend/book_readers.txt")
        existing_record_idx = existing_df[(existing_df['User'] == current_user.name) & 
                                              (existing_df['Book'] == selected_book.name)].index
        if not existing_record_idx.empty:
            page_number = existing_df.loc[existing_record_idx, 'Page Number'].values[0]
            return int(page_number)
    return 1

def book_closed(current_user,selected_book):
    if os.path.exists("backend/book_readers.txt"):
        existing_df = pd.read_csv("backend/book_readers.txt")
        existing_record_idx = existing_df[(existing_df['User'] == current_user.name) & 
                                              (existing_df['Book'] == selected_book.name)].index
        if not existing_record_idx.empty:
            existing_df.loc[existing_record_idx, 'Status'] = "Reading Closed"
            existing_df.to_csv("backend/book_readers.txt", index=False)

def main():
    print("WELCOME TO INSTABOOK!!")
    print("1. REGISTER\n2. LOGIN\n3. SWITCH TO ADMIN PORTAL\n")
    ch=int(input("CHOOSE YOUR CHOICE : "))
    current_user=None
    while(True):
        if ch==1:
            print("ENTER FOLLOWING DETAILS...")
            name=input("NAME : ")
            email=get_valid_email()
            password=get_valid_password()
            fav_genre=choose_genre()
            user = User(name,email,password,fav_genre)
            store_user_data2backend(user)
            print(user.register_msg())
            print("REDIRECTING TO LOGIN PAGE ...")
            ch=2
        elif ch==2:
            print("ENTER FOLLOWING DETAILS TO LOGIN ...")
            email=input("EMAIL : ") 
            if already_registered(email):
                password=input("PASSWORD : ")
                current_user=validate_login(email,password)
                if current_user is not None:
                    print(current_user.login_msg())
                    break
                else:
                    print("INVALID PASSWORD!! PLEASE TRY AGAIN!!")
            else:
                print("USER NOT FOUND!! PLEASE REGISTER!!")
        elif ch==3:
            switch_to_admin_portal()
            return
        
    while True:
        print("LET'S CHOOSE YOUR FAV BOOK TO READ ...")
        books = fetch_books(current_user.fav_genre)
        i=1
        for book in books:
            print("Book No.    :",i)
            print(book)
            i+=1
        bno=int(input("ENTER BOOK NO. TO READ : "))-1
        selected_book=books[bno]
        print("START READING THE BOOK...\n",selected_book,end=" ")
        cur_pg_no=get_cur_reading_pg(current_user,selected_book)
        if cur_pg_no!=1:
            print("FROM THE LAST PAGE (",cur_pg_no,") YOU READ")
        else:
            print("FROM THE FIRST PAGE")

        while True:
            update_book_reader(current_user,selected_book,cur_pg_no)
            print("1. NAVIGATE TO SPECIFIC PAGE\n2. PREV PAGE\n3. NEXT PAGE\n4. CLOSE THE BOOK")
            ch=int(input())
            if ch==1:
                cur_pg_no=int(input("PAGE NUMBER TO JUMP : "))
            elif ch==2 and cur_pg_no >= 1:
                cur_pg_no-=1
            elif ch==3 and cur_pg_no <= selected_book.total_pg:
                cur_pg_no+=1
            else:
                print("BOOK READING CLOSED!! READ AGAIN LATER!!")
                book_closed(current_user,selected_book)
                break
        exit=int(input("DO YOU WANT TO READ ANOTHER BOOK (1-YES/0-NO) ? "))
        if exit==0:
            break

main()
