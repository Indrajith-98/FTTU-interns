from .book import Book


class User:
    def __init__(self, username):
        self.__username = username
        self.__current_book: Book | None = None

    def get_username(self) -> str:
        return self.__username

    def get_current_book(self) -> str:
        if not self.__current_book:
            return "No books assigned"
        return self.__current_book.title

    def update_reading_book(self, book: Book) -> None:
        self.__current_book = book
        print("[Current reading book updated]".upper())
