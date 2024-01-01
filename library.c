#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STUDENTS 100

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
};

struct Student {
    int systemId;
    char name[100];
    int bookID;
};

void addBook(struct Book books[], int *numBooks) {
    struct Book book;

    printf("Enter book ID: ");
    scanf("%d", &book.id);
    printf("Enter book title: ");
    getchar();
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = '\0';
    printf("Enter author name: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = '\0';
    printf("Enter quantity: ");
    scanf("%d", &book.quantity);

    books[*numBooks] = book;
    (*numBooks)++;

    printf("Book added successfully!\n");
}

void displayBooks(struct Book books[], int numBooks) {
    printf("\nLibrary Book List:\n");
    printf("ID\tTitle\tAuthor\tQuantity\n");

    for (int i = 0; i < numBooks; i++) {
        printf("%d\t%s\t%s\t%d\n", books[i].id, books[i].title, books[i].author, books[i].quantity);
    }

    printf("\n");
}
void issueBook(struct Book books[], int numBooks, struct Student students[], int *numStudents) {
    int bookID, studentsystemId;

    printf("Enter student system I'd: ");
    scanf("%d", &studentsystemId);
    printf("Enter book ID to issue: ");
    scanf("%d", &bookID);

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookID) {
            if (books[i].quantity > 0) {

                books[i].quantity--;

                struct Student student;
                student.systemId = studentsystemId;
                student.bookID = bookID;

                students[*numStudents] = student;
                (*numStudents)++;

                printf("Book issued successfully!\n");
                return;
            } else {
                printf("Book not available for issuance. (Quantity is zero)\n");
                return;
            }
        }
    }

    printf("Book not found with ID %d\n", bookID);
}

void returnBook(struct Book books[], int numBooks, struct Student students[], int numStudents) {
    int bookID, studentsystemId;

    printf("Enter student system I'd: ");
    scanf("%d", &studentsystemId);
    printf("Enter book ID to return: ");
    scanf("%d", &bookID);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].systemId == studentsystemId && students[i].bookID == bookID) {

            for (int j = 0; j < numBooks; j++) {
                if (books[j].id == bookID) {
                    books[j].quantity++;
                    printf("Book returned successfully!\n");

                    for (int k = i; k < numStudents - 1; k++) {
                        students[k] = students[k + 1];
                    }
                    --numStudents;
                    return;
                }
            }
        }
    }

    printf("Student with system I'd %d does not have book with ID %d\n", studentsystemId, bookID);
}

int main() {
    struct Book books[MAX_BOOKS];
    struct Student students[MAX_STUDENTS];
    int numBooks = 0;
    int numStudents = 0;

    int choice;

    do {
        printf("\nLibrary Management System (Computer Science Department)\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                displayBooks(books, numBooks);
                break;
            case 3:
                issueBook(books, numBooks, students, &numStudents);
                break;
            case 4:
                returnBook(books, numBooks, students, numStudents);
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    return 0;
}
