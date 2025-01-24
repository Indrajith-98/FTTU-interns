
import sqlite3

def display_books(conn):
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM Books')
    rows = cursor.fetchall()

    if rows:
        print("\n+-----+----------------------------------+--------------+")
        print("| ID  | Title                            | Total Pages  |")
        print("+-----+----------------------------------+--------------+")
        for row in rows:
            print(f"| {row[0]:<4}| {row[1]:<32}| {row[2]:<12}|")
        print("+-----+----------------------------------+--------------+")
    else:
        print("\nNo books available.")

# Sign-up functionality
def signup(conn, username):
    password = input("Enter your password: ")
    cursor = conn.cursor()
    cursor.execute("INSERT INTO Users (Username, Password) VALUES (?, ?)", (username, password))
    conn.commit()
    print(f"User '{username}' has been successfully created! You can now log in.")
