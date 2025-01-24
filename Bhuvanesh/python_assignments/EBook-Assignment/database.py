import sqlite3

conn = sqlite3.connect('book_data.db')
cursor = conn.cursor()

cursor.execute('''
    CREATE TABLE IF NOT EXISTS books (
        book_name TEXT PRIMARY KEY,
        page_no INTEGER NOT NULL
    )
''')
conn.commit()

print("Database and table created successfully!")

cursor.execute('''
    CREATE TABLE IF NOT EXISTS user (
        user_id INTEGER PRIMARY KEY,
        username TEXT NOT NULL,
        password TEXT NOT NULL
    )
''')
conn.commit()
print("User table created successfully!")

cursor.execute('''
    CREATE TABLE IF NOT EXISTS user_books (
        user_id INTEGER PRIMARY KEY,
        bookdetails TEXT NOT NULL
    )
''')
conn.commit()

conn.close()

print("User Books table created successfully!")
