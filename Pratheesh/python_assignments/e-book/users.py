class UserManager:
    def __init__(self, db_connection):
        self.conn = db_connection
        self.cursor = self.conn.cursor()
        self._create_table()

    def _create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                user_id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL,
                is_admin INTEGER DEFAULT 0
            )
        ''')
        self.conn.commit()

    def sign_up(self, name, password):
        self.cursor.execute(
            "INSERT INTO users (name, password, is_admin) VALUES (?, ?, 0)", 
            (name, password)
        )
        self.conn.commit()

    def log_in(self, name, password):
        self.cursor.execute(
            "SELECT user_id, name, is_admin FROM users WHERE name = ? AND password = ?",
            (name, password)
        )
        user = self.cursor.fetchone()
        if user:
            return {"user_id": user[0], "name": user[1], "is_admin": user[2]}
        return None

    def add_admin(self, name, password, security_key):
        correct_key = "ebook2025@12345"
        if security_key != correct_key:
            print("Invalid security key! Admin not added.")
            return
        self.cursor.execute(
            "INSERT INTO users (name, password, is_admin) VALUES (?, ?, 1)", 
            (name, password)
        )
        self.conn.commit()
        print(f"Admin '{name}' added successfully!")
