
from books import display_books

def user_options(conn, username):
    while True:
        print("\n--- User Options ---")
        print("1. Show All Books")
        print("2. Select a Book and Continue Reading")
        print("3. View Progress")
        print("4. Exit")
        choice = input("Choose an option: ")

        if choice == '1':
            display_books(conn)  # Show all books
        elif choice == '2':
            display_books(conn)
            book_id = int(input("Enter the book ID to select: "))
            cursor = conn.cursor()

            # Check if the user has progress for the selected book
            cursor.execute('SELECT CurrentPage, Topic FROM BookInfo WHERE Username = ? AND BookID = ?', (username, book_id))
            progress = cursor.fetchone()

            if progress:
                current_page, topic = progress
                print(f"Continuing from your last progress:")
                print(f"Current Page: {current_page}, Topic: {topic}")
            else:
                print("No progress found for this book. Starting fresh.")
                current_page = 1  # Default to page 1
                topic = ""

            # Prompt for updates to current page and topic
            print(f"Book selected. Total pages are in the database.")
            while True:
                try:
                    new_page = int(input(f"Enter the page number you're currently on (starting from {current_page}): "))
                    if new_page >= current_page:
                        current_page = new_page
                        break
                    else:
                        print("You can't go back to a previous page!")
                except ValueError:
                    print("Invalid input. Please enter a valid page number.")

            topic = input("Enter the topic you're currently reading: ").strip()

            # Update or insert progress
            cursor.execute('''
                REPLACE INTO BookInfo (Username, BookID, CurrentPage, Topic)
                VALUES (?, ?, ?, ?)
            ''', (username, book_id, current_page, topic))
            conn.commit()
            print("Progress updated successfully!")
        elif choice == '3':
            # Show progress for all books
            cursor = conn.cursor()
            cursor.execute('SELECT b.Title, bi.CurrentPage, bi.Topic FROM BookInfo bi JOIN Books b ON bi.BookID = b.BookID WHERE bi.Username = ?', (username,))
            user_books = cursor.fetchall()

            if user_books:
                print("Your reading progress:")
                print("\n+================================================================================+")
                print("|              Book                |  Current Page  |           Topic            |")
                print("+==================================================================================+")
                for row in user_books:
                    print(f"| {row[0]:<32} | {row[1]:<14} | {row[2]:<26} |")
                print("+===================================================================================+")
            else:
                print("No progress recorded.")
        elif choice == '4':
            print("Exiting...")
            break
        else:
            print("Invalid choice, please try again.")
