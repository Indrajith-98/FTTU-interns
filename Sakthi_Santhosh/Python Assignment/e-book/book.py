class Book:
    """Represents a book with its details."""

    def __init__(self, title, author, total_pages, topic, chapters, users=None):
        self.title = title
        self.author = author
        self.total_pages = total_pages
        self.topic = topic
        self.chapters = chapters
        # Initialize users as an empty dictionary if not provided
        self.users = users if users is not None else {}

    def to_dict(self):
        """Convert the book object to a dictionary."""
        return {
            "title": self.title,
            "author": self.author,
            "total_pages": self.total_pages,
            "topic": self.topic,
            "chapters": self.chapters,
            "users": self.users,
        }

    def add_user(self):
        """Add a new user to the book."""
        username = input("Enter the new reader's name: ")
        if username in self.users:
            print("This user already exists.")
        else:
            self.users[username] = {"current_page": 0, "current_chapter": self.chapters[0] if self.chapters else "Unknown"}
            print(f"User '{username}' added successfully.")

    def update_user_progress(self):
        """Update a user's reading progress."""
        username = input("Enter the reader's name: ")
        if username in self.users:
            page = int(input(f"Enter the current page number (1-{self.total_pages}): "))
            if 1 <= page <= self.total_pages:
                chapter_index = (page - 1) // (self.total_pages // len(self.chapters))
                self.users[username] = {
                    "current_page": page,
                    "current_chapter": self.chapters[chapter_index],
                }
                print(f"Updated {username}'s progress to page {page}, chapter '{self.chapters[chapter_index]}'.")
            else:
                print("Page number out of range.")
        else:
            print("This user does not exist.")

    def display_users(self):
        """Display all users and their progress."""
        if not self.users:
            print("No users have been added yet.")
        else:
            print("\n--- Users and Progress ---")
            for user, progress in self.users.items():
                print(f"User: {user}")
                print(f"Current Page: {progress['current_page']}")
                print(f"Current Chapter: {progress['current_chapter']}")
            print("--------------------------")
