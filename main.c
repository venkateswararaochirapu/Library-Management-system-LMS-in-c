#include "header.h"

int main(void)
{
    Book library[MAX_BOOKS];
    IssueRecord records[MAX_RECORDS];
    int bookCount = 0;
    int recordCount = 0;
    int choice;   
    loadData(library,&bookCount,records,&recordCount);
    while (1)
    {
        printf("\n+----------------------------------------+\n");
        printf("|         Book Management Menu           |\n");
        printf("|----------------------------------------|\n");
        printf("| 1. Add New Book                        |\n");
        printf("| 2. Update Book Details                 |\n");
        printf("| 3. Remove Book                         |\n");
        printf("| 4. Search Book                         |\n");
        printf("| 5. View All Books                      |\n");
        printf("| 6. Issue Book                          |\n");
        printf("| 7. Return Book                         |\n");
        printf("| 8. List Issued Books                   |\n");
        printf("| 9. Save                                |\n");
        printf("| 10. Exit                               |\n");
        printf("+----------------------------------------+\n");
        printf("Enter your choice (1-10): ");
        __fpurge(stdin);
	scanf("%d",&choice);
        switch (choice)
        {
            case 1: addBook(library, &bookCount);
                    break;
            case 2: updateBook(library, bookCount);
                    break;
            case 3: removeBook(library, &bookCount);
                    break;
            case 4: searchBook(library, bookCount);
                    break;
            case 5: viewAllBooks(library, bookCount);
                    break;
            case 6: issueBook(library, bookCount, records, &recordCount);
                    break;
            case 7: returnBook(library, bookCount, records, &recordCount);
                    break;
            case 8: listIssueBooks(records, recordCount);
                    break;
            case 9: saveData(library, bookCount, records, recordCount);
                    break;
            case 10:printf("\nSaving data before exit...\n");
                    saveData(library, bookCount, records, recordCount);
                    printf("Exiting Library Management System. Goodbye!\n");
                    return 0;
            default:printf("Invalid choice! Please select an option between 1 and 10.\n");
        }
    }
    return 0;
}

