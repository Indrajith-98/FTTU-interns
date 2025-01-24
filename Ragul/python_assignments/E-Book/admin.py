
from books import display_books

def admin_module(conn):
    while True:
        print("\n--- Admin Options ---")
        print("1. Add a Book")
        print("2. Delete a Book")
        print("3. View All Books")
        print("4. View Users")  # New option
        print("5. Exit")

        choice = input("Choose an option: ")

        if choice == '1':
            add_book(conn)
        elif choice == '2':
            delete_book(conn)
        elif choice == '3':
            display_books(conn)
        elif choice == '4':
            view_users(conn)  # Call the new function
        elif choice == '5':
            print("Exiting Admin Options...")
            break
        else:
            print("Invalid choice, please try again.")

def add_book(conn):
    title = input("Enter book title: ").strip()
    try:
        total_pages = int(input("Enter total number of pages: "))
        cursor = conn.cursor()
        cursor.execute('''
            INSERT INTO Books (Title, TotalPages)
            VALUES (?, ?)
        ''', (title, total_pages))
        conn.commit()
        print("Book added successfully!")
    except ValueError:
        print("Invalid input for total pages. Please enter a number.")

def delete_book(conn):
    display_books(conn)
    try:
        book_id = int(input("Enter the book ID to delete: "))
        cursor = conn.cursor()
        cursor.execute('DELETE FROM Books WHERE BookID = ?', (book_id,))
        conn.commit()
        print("Book deleted successfully!")
    except ValueError:
        print("Invalid input for book ID. Please enter a number.")

def view_users(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT Username, Password FROM Users")
    users = cursor.fetchall()

    if users:
        print("\n+------------------------+------------------------+")
        print("|       Username         |        Password        |")
        print("+------------------------+------------------------+")
        for user in users:
            print(f"| {user[0]:<22} | {user[1]:<22} |")
        print("+------------------------+------------------------+")
    else:
        print("\nNo users found in the database.")
