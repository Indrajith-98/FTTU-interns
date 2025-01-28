class Book:
    def __init__(self, title, total_pages, current_reader=None):
        self.title = title
        self.total_pages = total_pages
        self.current_reader = current_reader  # User who is reading the book

    def to_dict(self):
        return {
            'title': self.title,
            'total_pages': self.total_pages,
            'current_reader': self.current_reader
        }

    @classmethod
    def from_dict(cls, data):
        return cls(data['title'], data['total_pages'], data.get('current_reader'))

    def assign_reader(self, username):
        """Assign a reader to the book."""
        self.current_reader = username

    def remove_reader(self):
        """Remove the current reader from the book."""
        self.current_reader = None
