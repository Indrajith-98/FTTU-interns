class User:
    def __init__(self, username, book=None, current_page=1, current_topic=None):
        self.username = username
        self.book = book  # The book the user is currently reading
        self.current_page = current_page
        self.current_topic = current_topic  # The topic the user is currently reading

    def to_dict(self):
        return {
            'username': self.username,
            'book': self.book,
            'current_page': self.current_page,
            'current_topic': self.current_topic
        }

    @classmethod
    def from_dict(cls, data):
        return cls(data['username'], data['book'], data['current_page'], data.get('current_topic'))

    def update_topic(self, new_topic):
        """Update the topic the user is currently reading."""
        self.current_topic = new_topic

    def remove_user(self):
        """Remove the user's information."""
        self.username = None
        self.book = None
        self.current_page = None
        self.current_topic = None
