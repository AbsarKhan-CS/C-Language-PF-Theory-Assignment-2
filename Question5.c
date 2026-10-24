#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 4


void displayMenu();
void registerMember(char name[], int *studentID, int *memberType);
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks);
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType);
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine);
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver);

void displayMenu() {
    printf("\n=== UNIVERSITY LIBRARY MANAGEMENT SYSTEM ===\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter Member Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Student/Faculty ID: ");
    scanf("%d", studentID);
    do {
        printf("Enter Membership Type (1 for Student, 2 for Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2) {
            printf("Invalid membership type. Please try again.\n");
        }
    } while (*memberType != 1 && *memberType != 2);
    printf("Member registered successfully!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n%-10s | %-25s | %-10s\n", "ID", "Title", "Copies");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("%-10d | %-25s | %-10d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if (*borrowedCount >= 3) {
        printf("Borrowing limit reached! You cannot borrow more than 3 books at a time.\n");
        return;
    }

    int id, days;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Invalid Book ID!\n");
        return;
    }

    if (availableCopies[index] <= 0) {
        printf("Sorry, no copies of this book are currently available.\n");
        return;
    }

    printf("Enter number of days intended to keep the book: ");
    scanf("%d", &days);
    if (days <= 0) {
        printf("Invalid number of days.\n");
        return;
    }

    availableCopies[index]--;
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;

    printf("Book '%s' borrowed successfully!\n", bookTitles[index]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    int id, daysKept;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);

    int borrowedIndex = -1;
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id) {
            borrowedIndex = i;
            break;
        }
    }

    if (borrowedIndex == -1) {
        printf("Error: You have not borrowed this book.\n");
        return 0.0;
    }

    printf("Enter actual number of days book was kept: ");
    scanf("%d", &daysKept);
    if (daysKept <= 0) {
        printf("Invalid number of days.\n");
        return 0.0;
    }


    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            availableCopies[i]++;
            break;
        }
    }

    
    for (int i = borrowedIndex; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;

    
    int allowedDays = (memberType == 1) ? 14 : 30;
    int rate = (memberType == 1) ? 20 : 10;
    float currentFine = 0.0;

    if (daysKept > allowedDays) {
        int extraDays = daysKept - allowedDays;
        currentFine = extraDays * rate;
        *totalFine += currentFine;

        printf("Late return! Fine generated: Rs. %.2f\n", currentFine);

        char code[20];
        printf("Enter waiver membership code (if applicable): ");
        scanf("%s", code);

        if (strcmp(code, "LIB2026") == 0) {
            printf("Waiver code accepted! 50%% discount applied.\n");
            return currentFine * 0.5f;
        } else {
            printf("Invalid/No waiver code. Full fine applies.\n");
            return currentFine;
        }
    } else {
        printf("Book returned on time. No fine charged.\n");
        return 0.0;
    }
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\n=== MEMBER RECORD ===\n");
    printf("Name: %s\n", name[0] ? name : "N/A");
    printf("ID: %d\n", studentID);
    printf("Type: %s\n", memberType == 1 ? "Student" : (memberType == 2 ? "Faculty" : "N/A"));
    
    printf("Currently Borrowed Book IDs (%d/3): ", borrowedCount);
    if (borrowedCount == 0) {
        printf("None");
    } else {
        for (int i = 0; i < borrowedCount; i++) {
            printf("%d ", borrowedBookIDs[i]);
        }
    }
    printf("\nTotal Fine Before Waiver: Rs. %.2f\n", totalFine);
    printf("Final Fine Payable After Waiver: Rs. %.2f\n", fineAfterWaiver);
}

int main() {
    int bookIDs[MAX_BOOKS] = {101, 102, 103, 104};
    char bookTitles[MAX_BOOKS][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };
    int availableCopies[MAX_BOOKS] = {5, 3, 0, 4};

    char name[100] = "";
    int studentID = 0;
    int memberType = 0;

    int borrowedBookIDs[3];
    int borrowedCount = 0;

    float totalFine = 0.0;
    float fineAfterWaiver = 0.0;

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, MAX_BOOKS);
                break;
            case 3:
                if (memberType == 0) {
                    printf("Please register first (Option 1) before borrowing books.\n");
                } else {
                    borrowBook(bookIDs, bookTitles, availableCopies, MAX_BOOKS, borrowedBookIDs, &borrowedCount, memberType);
                }
                break;
            case 4:
                if (memberType == 0) {
                    printf("Please register first (Option 1) before returning books.\n");
                } else {
                    float netFine = returnBook(bookIDs, availableCopies, MAX_BOOKS, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                    fineAfterWaiver += netFine;
                }
                break;
            case 5:
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                printf("Exiting Library Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select an option between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}