class Book:
    def __init__(self, username, topic, total_pages, current_page):
        self.username = username
        self.topic = topic
        self.total_pages = total_pages
        self.current_page = current_page

    def update_progress(self, new_page):
        """Update the current page number."""
        if new_page > self.total_pages:
            raise ValueError("Current page cannot exceed total pages.")
        self.current_page = new_page

    def __repr__(self):
        return f"Book(username={self.username}, topic={self.topic}, total_pages={self.total_pages}, current_page={self.current_page})"
