from components.database import DatabaseManager
from utils.headers import print_header, print_subheader


def main():
    db = DatabaseManager()

    while True:
        print_header("📚 BOOK TRACKING SYSTEM")
        print("1. ➕ Add User")
        print("2. 📘 Add Book")
        print("3. 📖 Start Reading a Book")
        print("4. ✏️ Update Reading Progress")
        print("5. 🔍 View Book Status (By User)")
        print("6. 📋 List All Books")
        print("7. 👥 List All Users and Their Books")
        print("0. ❌ Exit")

        choice = input("\nEnter your choice (1-8): ").strip()

        if choice == "1":
            print_subheader("ADD NEW USER")
            username = input("👤 Enter Username: ").strip()
            try:
                user_id = db.add_user(username)
                print(f"✅ User '{username}' added successfully! (User ID: {user_id})")
            except ValueError as e:
                print(f"⚠️ {e}")

        elif choice == "2":
            print_subheader("ADD NEW BOOK")
            title = input("📘 Enter Book Title: ").strip()
            total_pages = input("📄 Enter Total Pages: ").strip()

            if not total_pages.isdigit() or int(total_pages) <= 0:
                print("⚠️ Invalid page count. Please enter a positive number.")
                continue

            total_pages = int(total_pages)
            book_id = db.add_book(title, total_pages)
            print(f"✅ Book '{title}' added successfully! (Book ID: {book_id})")

        elif choice == "3":
            print_subheader("START READING A BOOK")
            username = input("👤 Enter Username: ").strip()
            user = db.get_user(username)

            if not user:
                print("⚠️ User not found! Please add the user first.")
                continue

            title = input("📘 Enter Book Title: ").strip()
            book = db.get_book(title)

            if not book:
                print("⚠️ Book not found! Please add the book first.")
                continue

            try:
                db.add_user_book(user[0], book[0])
                print(f"✅ User '{username}' started reading '{title}'.")
            except ValueError as e:
                print(f"⚠️ {e}")

        elif choice == "4":
            print_subheader("UPDATE READING PROGRESS")
            username = input("👤 Enter Username: ").strip()
            user = db.get_user(username)

            if not user:
                print("⚠️ User not found! Please add the user first.")
                continue

            title = input("📘 Enter Book Title: ").strip()
            book = db.get_book(title)

            if not book:
                print("⚠️ Book not found!")
                continue

            pages_read = input("✏️ Enter Number of Pages Read: ").strip()

            if not pages_read.isdigit() or int(pages_read) <= 0:
                print("⚠️ Invalid number of pages. Please enter a positive number.")
                continue

            pages_read = int(pages_read)

            try:
                db.update_progress(user[0], book[0], pages_read)
                print(f"✅ Progress updated for '{title}' by '{username}'.")
            except ValueError as e:
                print(f"⚠️ {e}")

        elif choice == "5":
            print_subheader("VIEW BOOK STATUS (BY USER)")
            username = input("👤 Enter Username: ").strip()
            user = db.get_user(username)

            if not user:
                print("⚠️ User not found!")
                continue

            title = input("📘 Enter Book Title: ").strip()
            book = db.get_book(title)

            if not book:
                print("⚠️ Book not found!")
                continue

            try:
                status = db.get_user_book_status(user[0], book[0])
                print("\n📖 Book Status:")
                print(f"  📘 Title: {status['title']}")
                print(f"  📄 Progress: {status['current_page']}/{status['total_pages']} pages read.")
            except ValueError as e:
                print(f"⚠️ {e}")

        elif choice == "6":
            print_subheader("LIST ALL BOOKS")
            books = db.list_all_books()

            if books:
                print("\n📋 All Books in the System:")
                for book in books:
                    print(f"  📘 '{book[1]}' - {book[2]} pages (Book ID: {book[0]})")
            else:
                print("⚠️ No books found in the system.")

        elif choice == "7":
            print_subheader("LIST ALL USERS AND THEIR BOOKS")
            users_with_books = db.list_all_users_with_books()

            if users_with_books:
                for username, books in users_with_books.items():
                    print(f"\n👤 User: {username}")
                    for book in books:
                        print(f"  📘 '{book['title']}' - {book['current_page']}/{book['total_pages']} pages read")
            else:
                print("⚠️ No users or books found in the system.")

        elif choice == "0":
            print("\n❌ Exiting the program. Have a great day! 📚")
            break

        else:
            print("\n⚠️ Invalid choice! Please try again.")


if __name__ == "__main__":
    main()
