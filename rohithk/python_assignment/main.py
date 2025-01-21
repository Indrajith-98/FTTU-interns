from Library.utils.book import Book
from Library.utils.user import User

user = User("rohithk")
python_book = Book(title="Learn Python", total_pages=500)
python_book.assign_book(user)
python_book.turn_page(20)
python_book.get_status()
