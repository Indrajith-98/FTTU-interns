from Operators.manage_users import init_db, register_user, authenticate_user, update_last_read, get_last_read
from Operators.handle_files import load_text_file
from Operators.utils import paginate


def main():
    init_db()  # Ensure database and tables are initialized

    print("Welcome to the eBook Reader!")
    user_id = None

    while not user_id:
        print("[1] Register")
        print("[2] Login")
        choice = input("Choose an option: ").strip()

        if choice == "1":
            username = input("Enter a new username: ").strip()
            password = input("Enter a password: ").strip()
            register_user(username, password)
            print("Registration successful! Please log in.")
            continue  # Redirect to login after registration
        elif choice == "2":
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            user_id = authenticate_user(username, password)
            if not user_id:
                print("Login failed. Please try again.")
        else:
            print("Invalid choice.")

    # User authenticated, proceed with the reader
    file_path = "/Users/pravinpb/pycode/MCW/Assignments/submissions/FTTU-interns/pravin/python_assignments/eReader/BookRepo/summa.txt"
    content = load_text_file(file_path)
    if not content:
        return

    lines_per_page = 20
    pages = list(paginate(content, lines_per_page))
    current_page = get_last_read(user_id, file_path)
    print(f"Resuming from page {current_page}")

    while True:
        print(current_page)
        print("\n".join(pages[current_page]))
        print(f"\nPage {current_page + 1}/{len(pages)}")
        command = input("\nCommands: [n] next, [p] previous, [q] quit: ").strip().lower()

        if command == 'n' and current_page < len(pages) - 1:
            current_page += 1
        elif command == 'p' and current_page > 0:
            current_page -= 1
        elif command == 'q':
            print("Last Current Page:", current_page)
            print("userid:", user_id)
            
            update_last_read(user_id, file_path, current_page)
            print("Progress saved. Exiting reader. Goodbye!")
            break
        else:
            print("Invalid command. Try again.")


if __name__ == "__main__":
    main()
