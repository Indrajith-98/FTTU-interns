# User Book Management System
This is a simple Python-based User Book Management System that allows users to register, log in, and manage their book information, 
including tracking the current page and topic of each book. The system stores user data in an Excel file, allowing for easy retrieval and updating of information.

## Features
**User Registration & Login:** Users can register with a unique username and password, or log in if they already have an account. <br>

**Add a Book:** Users can add a new book to their collection with details like the current page and topic. <br>

**Update Book Info:** Users can update their current page and topic for any of their books. <br>

**Display User Info:** Displays information about all the books a user has added, including the current page and topic. <br>

**Data Persistence:** All user and book data is stored in an Excel file, making it persistent across a single session. <br>

## Requirements
1. Before running the system, make sure you have the following installed: <br>
`Python 3.x`
2. openpyxl library for Excel file manipulation. You can install it using pip: <br>
```
pip install openpyxl
```

## Files and Folder Structure
```
project/
│
├── user_book.py       # Main Python file containing the logic for the user book system
├── user_book_data.xlsx  # Excel file to store user and book data (generated on first use)
└── README.md          # This README file
```

## How to Use
Run the Program: To start the system, simply run the following command in your terminal: <br>
`python user_book.py`

**User Login or Registration:** Upon starting the program, you will be prompted to either: <br>
1. Login: Enter your username and password to log into your existing account. <br>
2. Register: Enter a new username and password to create a new account. <br>

**Available Actions:** Once logged in, you can perform the following actions: <br>

(r)ead: View all books you've added along with their current page and topic. <br>

(u)pdate: Select a book to update its current page and topic. <br>

(a)dd a book: Add a new book to your collection by providing its title, current page, and topic.<br>

(q)uit: Exit the program.<br>


**Data Storage:** All user information (username, password, books, pages, topics) is stored in an Excel file (user_book_data.xlsx). This file is automatically created if it does not exist.
