# E-Book Reader Application using python

### About

The program includes user registration, login, and management of book details for users. It allows users to register, log in, and read books from various genres, while also enabling an admin portal to add books and view user reading details. The user’s reading progress is tracked, and book data is stored in CSV files.

### Classes & Backend

- User class : Contains user details like name, email, password, and favorite genre.
- Book class : Represents a book with details such as name, author, genre, total pages, and topics with page number limits.
- Backend Files
    - users.txt: Stores registered user data.
    - books.txt: Stores book data.
    - book_readers.txt: Stores user reading progress.

### Execution Flow

##### User 

- 1. Main Menu : Displays options to REGISTER, LOGIN, or access the ADMIN PORTAL.

- 2. After Login : 
    - The user can select a book to read, choose the page to start from, and navigate through the pages (based on page reading topic also changed).
    - Updates reading progress and saves it in book_readers.txt.

- 3. Book Navigation :

    - Options to jump to a specific page, go to the previous page, or next page.
    - Closes the book if the user finishes reading.

- 4. Exit : The user is asked if they want to read another book. If yes, the process continues; otherwise, the program exits.

##### Admin

- 1. Login :
    - Access the admin portal by selecting SWITCH TO ADMIN PORTAL.
    - Enter the default admin password 2003.

- 2. Admin Options:

    - Add a Book : Enter book details (name, author, genre, pages, topics). Saved in books.txt.
    - View User Progress: View user details (name, genre, current book, and page number, topic, reading status) from book_readers.txt.

- 3. Return: Admin can return to the main menu or log out.


#### Additional : 

- View books details are sorted based on the favorite genre of the user.
- User can start reading from the last read page.
- Admin can view the user reading status.

### Output

###### User

```
PS D:\EBookReader> python main.py
WELCOME TO INSTABOOK!!
1. REGISTER
2. LOGIN
3. SWITCH TO ADMIN PORTAL

CHOOSE YOUR CHOICE : 1
ENTER FOLLOWING DETAILS...
NAME : Harini
EMAIL : har
INVALID MAIL ID!! PLEASE TRY AGAIN...
EMAIL : harini@gmail.com
PASSWORD SHOULD CONTAIN 1-UPPERCASE & LOWERCASE LETTER, 1 DIGIT & SPCL CHAR AND MIN LENGTH 8
PASSWORD : Harini@03
1. FICTION
2. NON-FICTION
3. MYSTERY
4. THRILLER
5. BIOGRAPHY
6. HORROR
7. FANTASY
8. ADVENTURE
9. COOKBOOKS
10. HISTORY
CHOOSE BOOK GENRE : 7
Data stored successfully!!
Hii Harini, Your data was registered successfully!!
REDIRECTING TO LOGIN PAGE ...
ENTER FOLLOWING DETAILS TO LOGIN ...
EMAIL : harini@gmail.com
PASSWORD : Harini@03
Hii Harini, login successfully!! let's explore books!!
LET'S CHOOSE YOUR FAV BOOK TO READ ...
Book No.    : 1
Name        : Harry Potter and the Sorcerer's Stone
Author      : J.K. Rowling
Genre       : FANTASY
Total Pages : 309
Book Topics : {'The Arrival at Hogwarts': [1, 80], 'The Sorting Hat Ceremony': [81, 100], "The Mystery of the Sorcerer's Stone": [101, 150], 'The Forbidden Forest Encounter': [151, 230], 'The Final Showdown': [231, 309]}    

Book No.    : 2
Name        : A Game of Thrones
Author      : George R.R. Martin
Genre       : FANTASY
Total Pages : 694
Book Topics : {'The Starks': [1, 100], "King's Landing": [101, 300], 'The Wall': [301, 500], 'War and Betrayal': [501, 650], 'Aftermath': [651, 694]}

Book No.    : 3
Name        : The Hobbit
Author      : J.R.R. Tolkien
Genre       : ADVENTURE
Total Pages : 310
Book Topics : {"Bilbo's Unexpected Adventure Begins": [1, 45], 'The Journey through the Misty Mountains': [46, 120], 'The Meeting with Smaug the Dragon': [121, 190], 'The Battle of Five Armies': [191, 270], 'Bilbo Returns Home': [271, 310]}

Book No.    : 4
Name        : The Great Gatsby
Author      : F. Scott Fitzgerald
Genre       : FICTION
Total Pages : 218
Book Topics : {'The Arrival of Gatsby': [1, 40], "Gatsby's Mansion Parties": [41, 100], "Gatsby and Daisy's Reunion": [101, 150], 'The Tragic Love Story': [151, 200], 'The Death of Gatsby': [201, 218]}

Book No.    : 5
Name        : 1984
Author      : George Orwell
Genre       : FICTION
Total Pages : 328
Book Topics : {'Winston’s First Thoughts of Rebellion': [1, 80], 'Winston’s Love Affair with Julia': [81, 140], "The Betrayal by O'Brien": [141, 230], 'Winston’s Imprisonment in the Ministry of Love': [231, 290], 'The Final Acceptance of Big Brother': [291, 328]}

Book No.    : 6
Name        : The Silent Patient
Author      : Alex Michaelides
Genre       : MYSTERY
Total Pages : 325
Book Topics : {"Introduction to Alicia's World": [1, 50], 'The Investigation Begins': [51, 100], 'Secrets Unfold': [101, 200], 'Twists and Turns': [201, 300], 'Revelation': [301, 325]}

Book No.    : 7
Name        : The Shining
Author      : Stephen King
Genre       : HORROR
Total Pages : 447
Book Topics : {'The Overlook Hotel': [1, 100], "Jack's Struggles": [101, 200], "Danny's Visions": [201, 300], 'The Horror Unleashed': [301, 400], 'The Final Confrontation': [401, 447]}

Book No.    : 8
Name        : The Hunger Games
Author      : Suzanne Collins
Genre       : ADVENTURE
Total Pages : 374
Book Topics : {'Introduction to Panem': [1, 50], 'The Reaping': [51, 100], 'The Arena': [101, 250], 'The Games': [251, 350], 'The Aftermath': [351, 374]}

Book No.    : 9
Name        : And Then There Were None
Author      : Agatha Christie
Genre       : THRILLER
Total Pages : 264
Book Topics : {'The Invitation': [1, 40], 'The Island': [41, 100], 'The Murders Begin': [101, 180], 'Suspicions': [181, 240], 'The Truth Revealed': [241, 264]}

Book No.    : 10
Name        : Mastering the Art of French Cooking
Author      : Julia Child
Genre       : COOKBOOKS
Total Pages : 684
Book Topics : {'Basic Techniques': [1, 100], 'Appetizers': [101, 200], 'Main Courses': [201, 400], 'Desserts': [401, 600], 'Tips and Tricks': [601, 684]}

Book No.    : 11
Name        : The Road
Author      : Cormac McCarthy
Genre       : FICTION
Total Pages : 287
Book Topics : {'The Journey Begins': [1, 50], 'Survival': [51, 100], 'Danger and Loss': [101, 200], 'Hope and Despair': [201, 250], 'The End of the Road': [251, 287]}

ENTER BOOK NO. TO READ : 2
START READING THE BOOK...
 Name        : A Game of Thrones
Author      : George R.R. Martin
Genre       : FANTASY
Total Pages : 694
Book Topics : {'The Starks': [1, 100], "King's Landing": [101, 300], 'The Wall': [301, 500], 'War and Betrayal': [501, 650], 'Aftermath': [651, 694]}
 FROM THE FIRST PAGE
1. NAVIGATE TO SPECIFIC PAGE
2. PREV PAGE
3. NEXT PAGE
4. CLOSE THE BOOK
3
1. NAVIGATE TO SPECIFIC PAGE
2. PREV PAGE
3. NEXT PAGE
4. CLOSE THE BOOK
1
PAGE NUMBER TO JUMP : 98
1. NAVIGATE TO SPECIFIC PAGE
2. PREV PAGE
3. NEXT PAGE
4. CLOSE THE BOOK
2
1. NAVIGATE TO SPECIFIC PAGE
2. PREV PAGE
3. NEXT PAGE
4. CLOSE THE BOOK
4
BOOK READING CLOSED!! READ AGAIN LATER!!
DO YOU WANT TO READ ANOTHER BOOK (1-YES/0-NO) ? 1
LET'S CHOOSE YOUR FAV BOOK TO READ ...
Book No.    : 1
Name        : Harry Potter and the Sorcerer's Stone
Author      : J.K. Rowling
Genre       : FANTASY
Total Pages : 309
Book Topics : {'The Arrival at Hogwarts': [1, 80], 'The Sorting Hat Ceremony': [81, 100], "The Mystery of the Sorcerer's Stone": [101, 150], 'The Forbidden Forest Encounter': [151, 230], 'The Final Showdown': [231, 309]}    

Book No.    : 2
Name        : A Game of Thrones
Author      : George R.R. Martin
Genre       : FANTASY
Total Pages : 694
Book Topics : {'The Starks': [1, 100], "King's Landing": [101, 300], 'The Wall': [301, 500], 'War and Betrayal': [501, 650], 'Aftermath': [651, 694]}

Book No.    : 3
Name        : The Hobbit
Author      : J.R.R. Tolkien
Genre       : ADVENTURE
Total Pages : 310
Book Topics : {"Bilbo's Unexpected Adventure Begins": [1, 45], 'The Journey through the Misty Mountains': [46, 120], 'The Meeting with Smaug the Dragon': [121, 190], 'The Battle of Five Armies': [191, 270], 'Bilbo Returns Home': [271, 310]}

Book No.    : 4
Name        : The Great Gatsby
Author      : F. Scott Fitzgerald
Genre       : FICTION
Total Pages : 218
Book Topics : {'The Arrival of Gatsby': [1, 40], "Gatsby's Mansion Parties": [41, 100], "Gatsby and Daisy's Reunion": [101, 150], 'The Tragic Love Story': [151, 200], 'The Death of Gatsby': [201, 218]}

Book No.    : 5
Name        : 1984
Author      : George Orwell
Genre       : FICTION
Total Pages : 328
Book Topics : {'Winston’s First Thoughts of Rebellion': [1, 80], 'Winston’s Love Affair with Julia': [81, 140], "The Betrayal by O'Brien": [141, 230], 'Winston’s Imprisonment in the Ministry of Love': [231, 290], 'The Final Acceptance of Big Brother': [291, 328]}

Book No.    : 6
Name        : The Silent Patient
Author      : Alex Michaelides
Genre       : MYSTERY
Total Pages : 325
Book Topics : {"Introduction to Alicia's World": [1, 50], 'The Investigation Begins': [51, 100], 'Secrets Unfold': [101, 200], 'Twists and Turns': [201, 300], 'Revelation': [301, 325]}

Book No.    : 7
Name        : The Shining
Author      : Stephen King
Genre       : HORROR
Total Pages : 447
Book Topics : {'The Overlook Hotel': [1, 100], "Jack's Struggles": [101, 200], "Danny's Visions": [201, 300], 'The Horror Unleashed': [301, 400], 'The Final Confrontation': [401, 447]}

Book No.    : 8
Name        : The Hunger Games
Author      : Suzanne Collins
Genre       : ADVENTURE
Total Pages : 374
Book Topics : {'Introduction to Panem': [1, 50], 'The Reaping': [51, 100], 'The Arena': [101, 250], 'The Games': [251, 350], 'The Aftermath': [351, 374]}

Book No.    : 9
Name        : And Then There Were None
Author      : Agatha Christie
Genre       : THRILLER
Total Pages : 264
Book Topics : {'The Invitation': [1, 40], 'The Island': [41, 100], 'The Murders Begin': [101, 180], 'Suspicions': [181, 240], 'The Truth Revealed': [241, 264]}

Book No.    : 10
Name        : Mastering the Art of French Cooking
Author      : Julia Child
Genre       : COOKBOOKS
Total Pages : 684
Book Topics : {'Basic Techniques': [1, 100], 'Appetizers': [101, 200], 'Main Courses': [201, 400], 'Desserts': [401, 600], 'Tips and Tricks': [601, 684]}

Book No.    : 11
Name        : The Road
Author      : Cormac McCarthy
Genre       : FICTION
Total Pages : 287
Book Topics : {'The Journey Begins': [1, 50], 'Survival': [51, 100], 'Danger and Loss': [101, 200], 'Hope and Despair': [201, 250], 'The End of the Road': [251, 287]}

ENTER BOOK NO. TO READ : 2
START READING THE BOOK...
 Name        : A Game of Thrones
Author      : George R.R. Martin
Genre       : FANTASY
Total Pages : 694
Book Topics : {'The Starks': [1, 100], "King's Landing": [101, 300], 'The Wall': [301, 500], 'War and Betrayal': [501, 650], 'Aftermath': [651, 694]}
 FROM THE LAST PAGE ( 97 ) YOU READ
1. NAVIGATE TO SPECIFIC PAGE
2. PREV PAGE
3. NEXT PAGE
4. CLOSE THE BOOK
4
BOOK READING CLOSED!! READ AGAIN LATER!!
DO YOU WANT TO READ ANOTHER BOOK (1-YES/0-NO) ? 0
```

###### Admin

```
PS D:\EBookReader> python main.py
WELCOME TO INSTABOOK!!
1. REGISTER
2. LOGIN
3. SWITCH TO ADMIN PORTAL

CHOOSE YOUR CHOICE : 3
ENTER ADMIN PORTAL PASSWORD : 2003
1. ADD NEW BOOKS
2. VIEW USER READING DETAILS
CHOOSE YOUR TASK : 1
ENTER BASIC BOOK DETAILS
BOOK NAME : Harry Potter and The Goblet of Fire
BOOK AUTHOR NAME : J.K. Rowling
1. FICTION
2. NON-FICTION
3. MYSTERY
4. THRILLER
5. BIOGRAPHY
6. HORROR
7. FANTASY
8. ADVENTURE
9. COOKBOOKS
10. HISTORY
CHOOSE BOOK GENRE : 7
TOTAL NO. OF PAGES : 640
ENTER TOPICS (e-exit) : The Riddle House and the Dark Mark
LOWER & UPPER PG LIMIT :
1,40
ENTER TOPICS (e-exit) : The Quidditch World Cup and the Death Eaters
LOWER & UPPER PG LIMIT :
41,90
ENTER TOPICS (e-exit) : The Triwizard Tournament Announcement
LOWER & UPPER PG LIMIT :
91,130
ENTER TOPICS (e-exit) : The First Task: The Dragon Challenge
LOWER & UPPER PG LIMIT :
131,180
ENTER TOPICS (e-exit) : The Yule Ball and Hogwarts Rivalries 
LOWER & UPPER PG LIMIT :
181,220
ENTER TOPICS (e-exit) : The Second Task: The Lake Rescue
LOWER & UPPER PG LIMIT :
221,260
ENTER TOPICS (e-exit) : Barty Crouch Jr. and the Secrets of the Tournament
LOWER & UPPER PG LIMIT :
261,300
ENTER TOPICS (e-exit) : The Pensieve and Dumbledore’s Past
LOWER & UPPER PG LIMIT :
301,340
ENTER TOPICS (e-exit) : The Third Task: The Maze
LOWER & UPPER PG LIMIT :
341,380
ENTER TOPICS (e-exit) : The Return of Voldemort and the Final Confrontation
LOWER & UPPER PG LIMIT :
381,640
ENTER TOPICS (e-exit) : e
Book Data stored successfully!!
1. ADD NEW BOOKS
2. VIEW USER READING DETAILS
3. EXIT
CHOOSE YOUR TASK : 2
----------------------------------------
Record 1:
----------------------------------------
User        : Deivanayaki
Book        : Harry Potter and the Sorcerer's Stone
Page Number : 83
Topic       : The Sorting Hat Ceremony
Status      : Reading Closed
----------------------------------------
----------------------------------------
Record 2:
----------------------------------------
User        : Deivanayaki
Book        : A Game of Thrones
Page Number : 3
Topic       : The Starks
Status      : Reading Closed
----------------------------------------
----------------------------------------
Record 3:
----------------------------------------
User        : Srivani
Book        : Harry Potter and the Sorcerer's Stone
Page Number : 81
Topic       : The Sorting Hat Ceremony
Status      : Reading Closed
----------------------------------------
----------------------------------------
Record 4:
----------------------------------------
User        : Harini
Book        : A Game of Thrones
Page Number : 97
Topic       : The Starks
Status      : Reading Closed
----------------------------------------
1. ADD NEW BOOKS
2. VIEW USER READING DETAILS
3. EXIT
CHOOSE YOUR TASK : 3
```
