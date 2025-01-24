class Book:
    def __init__(self, book_id, title, total_pages, current_page=0):
        self.book_id = book_id
        self.title = title
        self.total_pages = total_pages
        self.current_page = current_page

    def update_progress(self, pages_read):
        """Update the current page number."""
        if self.current_page + pages_read > self.total_pages:
            raise ValueError("Pages read cannot exceed total pages.")
        self.current_page += pages_read

    def __repr__(self):
        return f"Book(id={self.book_id}, title={self.title}, total_pages={self.total_pages}, current_page={self.current_page})"
