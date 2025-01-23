class Book:
    def __init__(self, title, total_pages) -> None:
        self.total_pages = total_pages
        self.title = title
        self.current_user = None
        self.current_page = 0
        self.current_section = None

    def assign_book(self, user):
        from .user import User

        if isinstance(user, User):
            self.current_user = user
            self.current_page = 1
            print(f"Book assigned to {user.get_username()}. Start reading!")

    def turn_page(self, page_no):
        if page_no < 0 or page_no > self.total_pages:
            print("[INVALID BOOK PAGE]")
            return
        self.current_page = page_no

    def get_status(self):
        if self.current_user:
            print(f"User: {self.current_user.get_username()}")
            print(f"Current Page: {self.current_page}")
        else:
            print("No user is currently reading this book.")
