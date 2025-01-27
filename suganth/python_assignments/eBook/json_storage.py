import json
from book import Book
from user import User

def load_books(file_path):
    try:
        with open(file_path, 'r') as f:
            data = json.load(f)
        if isinstance(data, dict) and 'books' in data:
            return [Book.from_dict(item) for item in data['books']]
        return []  # If the data is not in the expected format
    except (FileNotFoundError, json.JSONDecodeError):
        return []  # Return an empty list if the file doesn't exist or is empty


def load_users(file_path):
    try:
        with open(file_path, 'r') as f:
            data = json.load(f)
        return [User.from_dict(item) for item in data['users']]
    except (FileNotFoundError, json.JSONDecodeError):
        return []  # If file doesn't exist or is empty, return empty list

def save_books(file_path, books):
    with open(file_path, 'w') as f:
        json.dump({"books": [book.to_dict() for book in books]}, f, indent=4)

def save_users(file_path, users):
    with open(file_path, 'w') as f:
        json.dump({"users": [user.to_dict() for user in users]}, f, indent=4)
