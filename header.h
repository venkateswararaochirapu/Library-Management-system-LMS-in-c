#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<time.h>

#define MAX_BOOKS    500
#define MAX_RECORDS  1000
#define FINE_PER_DAY 5.0

typedef struct Book 
{
	int bookID;
	char title[100];
	char author[50];
	int quantity;
}Book;

typedef struct IssueRecord
{
	int issueID;
	int bookID;
	int userID;
	char userName[50];
	char issueDate[11];  //yyyy-mm-dd
	char dueDate[11];    //yyyy-mm-dd
	char returnDate[11]; //yyyy-mm-dd
	float fineAmount;
}IssueRecord;

void addBook(Book *library,int *bookCount);
void updateBook(Book *library,int bookCount);
void removeBook(Book *library,int *bookCount);
void searchBook(Book *library,int bookCount);
void viewAllBooks(Book *library,int bookCount);

void issueBook(Book *library,int bookCount,IssueRecord *records,int *recordCount);
void returnBook(Book *library,int bookCount,IssueRecord *records,int *recordCount);
void listIssueBooks(const IssueRecord *records,int recordCount);

void loadData(Book *library,int *bookCount,IssueRecord *records,int *recordCount);
void saveData(const Book *library,int bookCount,const IssueRecord *records,int recordCount);


void readString(char *str,int size);
int my_strcmp(const char *s1,const char *s2);
char *my_strstr(const char *str,const char *sub);
int findbyID(Book *library,int bookCount,int id);
int findbyName(Book *library,int bookCount,char *name);
int findbyAuthor(Book *library,int bookCount,char *author);
