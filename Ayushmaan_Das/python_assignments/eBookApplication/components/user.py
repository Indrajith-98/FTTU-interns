class User:
    def __init__(self, user_id, username):
        self.user_id = user_id
        self.username = username

    def __repr__(self):
        return f"User(id={self.user_id}, username={self.username})"
