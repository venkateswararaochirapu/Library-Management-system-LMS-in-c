# Library Management System (LMS) in C

A console-based Library Management System written in C. It lets a librarian manage books, issue and return them, track due dates, and calculate fines for late returns. All data is saved to text files, so nothing is lost when the program closes.

## Features

- **Add, update and remove books** (by Book ID or Book Title)
- **Search books** by ID, title or author, with partial and case-insensitive matching
- **View all books** in the library
- **Issue books** to users. The issue date and due date (7 days) are generated automatically
- **Return books**. The return date is recorded and the fine is calculated if the book is late
- **List issued books** with issue date, due date, return date and fine
- **Save and load data** from files. Data is loaded at startup and saved on exit

## Fine Rule

```
Fine Amount = Number of Late Days x 5
```

The rate is set by `FINE_PER_DAY` in `header.h`.

## Project Structure

```
LMS/
├── main.c      # Main menu and program flow
├── book.c      # Add, update, remove, search, view books
├── issue.c     # Issue book, return book, list issued books
├── file.c      # File handling, string helpers, search helpers
├── header.h    # Structures, constants and function declarations
└── README.md
```

## Data Structures

**Book**

| Field    | Description          |
| -------- | -------------------- |
| bookID   | Unique ID of book    |
| title    | Book name            |
| author   | Author name          |
| quantity | Available copies     |

**IssueRecord**

| Field      | Description             |
| ---------- | ----------------------- |
| issueID    | Unique issue record ID  |
| bookID     | Issued book ID          |
| userID     | Borrower ID             |
| userName   | Borrower name           |
| issueDate  | Date of issue           |
| dueDate    | Last return date        |
| returnDate | Actual return date      |
| fineAmount | Late return fine        |

## Data Storage

Data is stored in plain text files, one record per line, with fields separated by `|`.

- `Books.txt`: all book details
- `Records.txt`: issue and return history

The files are created when you choose **Save** or **Exit**. Do not type the `|` character in titles, authors or names.

## Build and Run

Requires `gcc` on Linux (the code uses `__fpurge` from `stdio_ext.h`).

```bash
gcc -Wall -Wextra -o lms main.c book.c issue.c file.c
./lms
```

## Menu

```
+----------------------------------------+
|         Book Management Menu           |
|----------------------------------------|
| 1. Add New Book                        |
| 2. Update Book Details                 |
| 3. Remove Book                         |
| 4. Search Book                         |
| 5. View All Books                      |
| 6. Issue Book                          |
| 7. Return Book                         |
| 8. List Issued Books                   |
| 9. Save                                |
| 10. Exit                               |
+----------------------------------------+
```

## Future Improvements

- Admin login with username and password
- Separate file for users
- Reports: most issued books, overdue books, total fine collected
- Different fine rates for normal and reference books
- Stronger input validation
- Makefile for easier building

## Concepts Used

Structures, arrays, pointers, functions, file handling, string handling, and the `time.h` date functions.

## Author

Venkateswara Rao Chirapu
