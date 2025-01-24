import tkinter as tk
from tkinter import ttk, messagebox
from components.database import DatabaseManager
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s', filename='logs/gui.log', filemode='a')

class BookManagementApp:
    def __init__(self, root):
        self.db = DatabaseManager()
        self.root = root
        self.root.title("eBOOK MANAGEMENT APPLICATION")
        self.root.geometry("800x600")

        logging.info("Application started.")
        
        header = tk.Label(root, text="📚 Book Management System", font=("Arial", 20, "bold"), fg="blue")
        header.pack(pady=10)

        nav_frame = tk.Frame(root)
        nav_frame.pack(side=tk.LEFT, fill=tk.Y, padx=10)

        nav_buttons = [
            ("➕ Add User", self.show_add_user),
            ("📘 Add Book", self.show_add_book),
            ("📖 Start Reading", self.show_start_reading),
            ("✏️ Update Progress", self.show_update_progress),
            ("🔍 View Status", self.show_view_status),
            ("📋 List All Books", self.list_all_books),
            ("👥 List All Users & Books", self.list_all_users_with_books),
        ]

        for text, command in nav_buttons:
            btn = tk.Button(nav_frame, text=text, width=25, command=command, bg="lightblue", font=("Arial", 12))
            btn.pack(pady=5)

        self.content_frame = tk.Frame(root, bg="white", relief=tk.SUNKEN, bd=2)
        self.content_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=10, pady=10)

        self.clear_content()
        self.show_welcome_message()

    def clear_content(self):
        for widget in self.content_frame.winfo_children():
            widget.destroy()

    def show_welcome_message(self):
        welcome_label = tk.Label(
            self.content_frame,
            text="Welcome to the Book Management System!\nCheck sidebar to explore functionalities.",
            font=("Arial", 16),
            justify=tk.CENTER,
            wraplength=400,
        )
        welcome_label.pack(expand=True)

    def show_add_user(self):
        self.clear_content()
        tk.Label(self.content_frame, text="Add New User", font=("Arial", 16, "bold")).pack(pady=10)

        tk.Label(self.content_frame, text="Username:", font=("Arial", 12)).pack(pady=5)
        username_entry = tk.Entry(self.content_frame, font=("Arial", 12))
        username_entry.pack(pady=5)

        def add_user_action():
            username = username_entry.get().strip()
            if not username:
                messagebox.showerror("Error", "Username cannot be empty!")
                return
            try:
                user_id = self.db.add_user(username)
                messagebox.showinfo("Success", f"User '{username}' added successfully! (User ID: {user_id})")
                username_entry.delete(0, tk.END)
                logging.info(f"User '{username}' added with User ID: {user_id}")
            except ValueError as e:
                messagebox.showerror("Error", str(e))
                logging.error(f"Error adding user '{username}': {e}")

        submit_btn = tk.Button(self.content_frame, text="Add User", font=("Arial", 12), command=add_user_action, bg="green", fg="white")
        submit_btn.pack(pady=10)

    def show_add_book(self):
        self.clear_content()
        tk.Label(self.content_frame, text="Add New Book", font=("Arial", 16, "bold")).pack(pady=10)

        tk.Label(self.content_frame, text="Book Title:", font=("Arial", 12)).pack(pady=5)
        title_entry = tk.Entry(self.content_frame, font=("Arial", 12))
        title_entry.pack(pady=5)

        tk.Label(self.content_frame, text="Total Pages:", font=("Arial", 12)).pack(pady=5)
        pages_entry = tk.Entry(self.content_frame, font=("Arial", 12))
        pages_entry.pack(pady=5)

        def add_book_action():
            title = title_entry.get().strip()
            total_pages = pages_entry.get().strip()
            if not title or not total_pages.isdigit() or int(total_pages) <= 0:
                messagebox.showerror("Error", "Please enter valid book details!")
                return
            total_pages = int(total_pages)
            self.db.add_book(title, total_pages)
            messagebox.showinfo("Success", f"Book '{title}' added successfully!")
            title_entry.delete(0, tk.END)
            pages_entry.delete(0, tk.END)
            logging.info(f"Book '{title}' added with {total_pages} pages.")

        submit_btn = tk.Button(self.content_frame, text="Add Book", font=("Arial", 12), command=add_book_action, bg="green", fg="white")
        submit_btn.pack(pady=10)

    def show_start_reading(self):
        self.clear_content()
        tk.Label(self.content_frame, text="Start Reading a Book", font=("Arial", 16, "bold")).pack(pady=10)

        users = [user[1] for user in self.db.list_all_users()]
        books = [book[1] for book in self.db.list_all_books()]

        tk.Label(self.content_frame, text="Select User:", font=("Arial", 12)).pack(pady=5)
        user_var = tk.StringVar(value="Select a User")
        user_menu = ttk.Combobox(self.content_frame, textvariable=user_var, values=users, state="readonly")
        user_menu.pack(pady=5)

        tk.Label(self.content_frame, text="Select Book:", font=("Arial", 12)).pack(pady=5)
        book_var = tk.StringVar(value="Select a Book")
        book_menu = ttk.Combobox(self.content_frame, textvariable=book_var, values=books, state="readonly")
        book_menu.pack(pady=5)

        def start_reading_action():
            username = user_var.get()
            book_title = book_var.get()
            if username == "Select a User" or book_title == "Select a Book":
                messagebox.showerror("Error", "Please select both a user and a book!")
                return
            user = self.db.get_user(username)
            book = self.db.get_book(book_title)
            try:
                self.db.add_user_book(user[0], book[0])
                messagebox.showinfo("Success", f"User '{username}' started reading '{book_title}'.")
                logging.info(f"User '{username}' started reading '{book_title}'.")
            except ValueError as e:
                messagebox.showerror("Error", str(e))
                logging.error(f"Error starting reading for user '{username}': {e}")

        submit_btn = tk.Button(self.content_frame, text="Start Reading", font=("Arial", 12), command=start_reading_action, bg="green", fg="white")
        submit_btn.pack(pady=10)

    def show_view_status(self):
        self.clear_content()
        tk.Label(self.content_frame, text="View Reading Status", font=("Arial", 16, "bold")).pack(pady=10)

        users = [user for user in self.db.list_all_users_with_books().keys()]
        books = [book[1] for book in self.db.list_all_books()]

        tk.Label(self.content_frame, text="Select User:", font=("Arial", 12)).pack(pady=5)
        user_var = tk.StringVar(value="Select a User")
        user_menu = ttk.Combobox(self.content_frame, textvariable=user_var, values=users, state="readonly")
        user_menu.pack(pady=5)

        tk.Label(self.content_frame, text="Select Book:", font=("Arial", 12)).pack(pady=5)
        book_var = tk.StringVar(value="Select a Book")
        book_menu = ttk.Combobox(self.content_frame, textvariable=book_var, values=books, state="readonly")
        book_menu.pack(pady=5)

        def view_status_action():
            username = user_var.get()
            book_title = book_var.get()
            if username == "Select a User" or book_title == "Select a Book":
                messagebox.showerror("Error", "Please select both a user and a book!")
                return
            user = self.db.get_user(username)
            book = self.db.get_book(book_title)
            reading_status = self.db.get_reading_status(user[0], book[0])
            if reading_status:
                messagebox.showinfo("Reading Status", f"User: {username}\nBook: {book_title}\nPages Read: {reading_status[1]}/{reading_status[2]}")
            else:
                messagebox.showinfo("Reading Status", f"User '{username}' has not started reading '{book_title}'.")
            logging.info(f"Viewing status for user '{username}' in book '{book_title}'.")

        submit_btn = tk.Button(self.content_frame, text="View Status", font=("Arial", 12), command=view_status_action, bg="blue", fg="white")
        submit_btn.pack(pady=10)

    def list_all_books(self):
        self.clear_content()
        tk.Label(self.content_frame, text="List of All Books", font=("Arial", 16, "bold")).pack(pady=10)

        books = self.db.list_all_books()
        if not books:
            tk.Label(self.content_frame, text="No books found!", font=("Arial", 12)).pack(pady=10)
            logging.info("No books found.")
            return

        for book in books:
            tk.Label(self.content_frame, text=f"📘 {book[1]} - {book[2]} pages", font=("Arial", 12)).pack(anchor="w", padx=20)

    def list_all_users_with_books(self):
        self.clear_content()
        tk.Label(self.content_frame, text="List of All Users & Their Books", font=("Arial", 16, "bold")).pack(pady=10)

        user_books = self.db.list_all_users_with_books()

        if not user_books:
            tk.Label(self.content_frame, text="No users or books found!", font=("Arial", 12)).pack(pady=10)
            logging.info("No users or books found.")
            return

        for user, books in user_books.items():
            user_label = tk.Label(self.content_frame, text=f"👤 {user}:", font=("Arial", 12, "bold"))
            user_label.pack(anchor="w", padx=20)

            if not books:  
                tk.Label(self.content_frame, text="   No books.", font=("Arial", 12)).pack(anchor="w", padx=40)
            else:
                for book in books:
                    book_title = book["title"]
                    current_page = book["current_page"]
                    total_pages = book["total_pages"]
                    book_info = f"   📘 {book_title} - Page {current_page} of {total_pages}"
                    tk.Label(self.content_frame, text=book_info, font=("Arial", 12)).pack(anchor="w", padx=40)

    def show_update_progress(self):
        self.clear_content()
        tk.Label(self.content_frame, text="Update Reading Progress", font=("Arial", 16, "bold")).pack(pady=10)

        users = [user for user in self.db.list_all_users_with_books().keys()]
        books = [book[1] for book in self.db.list_all_books()]

        tk.Label(self.content_frame, text="Select User:", font=("Arial", 12)).pack(pady=5)
        user_var = tk.StringVar(value="Select a User")
        user_menu = ttk.Combobox(self.content_frame, textvariable=user_var, values=users, state="readonly")
        user_menu.pack(pady=5)

        tk.Label(self.content_frame, text="Select Book:", font=("Arial", 12)).pack(pady=5)
        book_var = tk.StringVar(value="Select a Book")
        book_menu = ttk.Combobox(self.content_frame, textvariable=book_var, values=books, state="readonly")
        book_menu.pack(pady=5)

        tk.Label(self.content_frame, text="How many more pages did you read:", font=("Arial", 12)).pack(pady=5)
        pages_entry = tk.Entry(self.content_frame, font=("Arial", 12))
        pages_entry.pack(pady=5)

        def update_progress_action():
            username = user_var.get()
            book_title = book_var.get()
            pages_read = pages_entry.get().strip()

            if username == "Select a User" or book_title == "Select a Book" or not pages_read.isdigit():
                messagebox.showerror("Error", "Please provide valid inputs!")
                return

            user = self.db.get_user(username)
            book = self.db.get_book(book_title)
            pages_read = int(pages_read)

            try:
                self.db.update_progress(user[0], book[0], pages_read)
                messagebox.showinfo("Success", f"Updated reading progress for '{username}' in '{book_title}'.")
                logging.info(f"Updated reading progress for '{username}' in '{book_title}'.")
            except ValueError as e:
                messagebox.showerror("Error", str(e))
                logging.error(f"Error updating progress for '{username}' in '{book_title}': {e}")
        
        submit_btn = tk.Button(self.content_frame, text="Update Progress", font=("Arial", 12), command=update_progress_action, bg="blue", fg="white")
        submit_btn.pack(pady=10)


if __name__ == "__main__":
    root = tk.Tk()
    app = BookManagementApp(root)
    root.mainloop()
