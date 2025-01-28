import csv
from utils import read_csv, write_csv, file_path

class User:
    def __init__(self, username):
        self.username = username

    def select_book(self, book_name):
        books = read_csv(file_path("books.csv"))
        for book in books:
            if book["Book Name"] == book_name:
                user_progress = read_csv(file_path("user_progress.csv"))
                for user in user_progress:
                    if user["Username"] == self.username:
                        user["Book Name"] = book_name
                        user["Total Pages"] = book["Total Pages"]
                        user["Current Page"] = "1"
                        user["Chapter"] = book["Chapters"].split(",")[0]
                        write_csv(file_path("user_progress.csv"), user_progress)
                        print(f"Started reading {book_name}.")
                        return
                user_progress.append({
                    "Username": self.username,
                    "Book Name": book_name,
                    "Total Pages": book["Total Pages"],
                    "Current Page": "1",
                    "Chapter": book["Chapters"].split(",")[0]
                })
                write_csv(file_path("user_progress.csv"), user_progress)
                print(f"Started reading {book_name}.")
                return
        print(f"Book {book_name} not found.")

    def turn_page(self):
        user_progress = read_csv(file_path("user_progress.csv"))
        for user in user_progress:
            if user["Username"] == self.username:
                current_page = int(user["Current Page"])
                total_pages = int(user["Total Pages"])
                if current_page < total_pages:
                    current_page += 1
                    user["Current Page"] = str(current_page)
                    chapters = read_csv(file_path("books.csv"))
                    for book in chapters:
                        if book["Book Name"] == user["Book Name"]:
                            user["Chapter"] = book["Chapters"].split(",")[current_page - 1]
                            break
                    write_csv(file_path("user_progress.csv"), user_progress)
                    print(f"Turned to page {current_page}.")
                else:
                    print("You are already at the last page.")
                return
        print("User progress not found.")

    def view_progress(self):
        user_progress = read_csv(file_path("user_progress.csv"))
        for user in user_progress:
            if user["Username"] == self.username:
                print(f"\nYour Reading Progress:\nBook: {user['Book Name']}, Total Pages: {user['Total Pages']}, Current Page: {user['Current Page']}, Chapter: {user['Chapter']}")
                return
        print("No progress found.")
