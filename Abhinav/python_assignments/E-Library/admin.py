import csv
from utils import read_csv, write_csv, file_path

class Admin:
    def view_all_users(self):
        users = read_csv(file_path("user_progress.csv"))
        if not users:
            print("No user progress available.")
            return
        print("\nAll Users' Info:")
        for user in users:
            print(f"Username: {user['Username']}, Book: {user['Book Name']}, Total Pages: {user['Total Pages']}, Current Page: {user['Current Page']}, Chapter: {user['Chapter']}")

    def update_book_details(self, book_name, total_pages, chapters):
        books = read_csv(file_path("books.csv"))
        for book in books:
            if book["Book Name"] == book_name:
                book["Total Pages"] = total_pages
                book["Chapters"] = chapters
                write_csv(file_path("books.csv"), books)
                print(f"Updated details for {book_name}.")
                return
        books.append({"Book Name": book_name, "Total Pages": total_pages, "Chapters": chapters})
        write_csv(file_path("books.csv"), books)
        print(f"Added new book: {book_name}.")
