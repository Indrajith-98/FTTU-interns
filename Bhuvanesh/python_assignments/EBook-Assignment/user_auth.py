import sqlite3

class UserAuth:
    def __init__(self):
        self.conn = sqlite3.connect('book_data.db')
        self.cursor = self.conn.cursor()

    def register_user(self, user_id, username, password):
        self.cursor.execute('''
            INSERT INTO user (user_id, username, password)
            VALUES (?, ?, ?)''', (user_id, username, password))
        self.conn.commit()
        print(f"User '{username}' with ID {user_id} registered successfully!")

    def authenticate_user(self, user_id, password):
        self.cursor.execute('''
            SELECT user_id, password FROM user WHERE user_id = ?''', (user_id,))
        stored_data = self.cursor.fetchone()

        if stored_data:
            stored_password = stored_data[1]
            if password == stored_password:
                print(f"Authentication successful for user '{user_id}'!")
                return stored_data[0] 
            else:
                print("Incorrect password!")
        else:
            print(f"User '{user_id}' not found.")
        return None

    def close_connection(self):
        self.conn.close()
