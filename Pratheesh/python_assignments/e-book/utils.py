def view_users(cursor):
    cursor.execute("SELECT * FROM users")
    users = cursor.fetchall()
    print("Users Table:")
    for user in users:
        print(user)

def view_books(cursor):
    cursor.execute("SELECT * FROM books")
    books = cursor.fetchall()
    print("Books Table:")
    for book in books:
        print(book)

def view_reading_status(cursor):
    cursor.execute("SELECT * FROM reading_status")
    statuses = cursor.fetchall()
    print("Reading Status Table:")
    for status in statuses:
        print(status)
