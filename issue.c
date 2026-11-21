#include"header.h"
#include<string.h>

void issueBook(Book *library,int bookCount,IssueRecord *records,int *recordCount)
{
	if(*recordCount>=MAX_RECORDS)
	{
		printf("ERROR: Issue record storage is full\n");
		return;
	}
	int index=-1,bookid;
	printf("Enter your bookID:");
	__fpurge(stdin);
	scanf("%d",&bookid);
        index=findbyID(library,bookCount,bookid);
	if(index==-1)
	{
		printf("Error: Book not found!\n");
		return;
	}
	if(library[index].quantity<=0)
	{
		printf("Error: Book is currently out of stock!\n");
		return;
	}
	printf("Enter user ID: ");
	__fpurge(stdin);
	scanf("%d",&records[*recordCount].userID);
	printf("Enter username: ");
	__fpurge(stdin);
	readString(records[*recordCount].userName, sizeof(records[*recordCount].userName));
	records[*recordCount].issueID=((*recordCount)==0)?1:records[*recordCount-1].issueID+1;
	records[*recordCount].bookID=bookid;
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(records[*recordCount].issueDate, sizeof(records[*recordCount].issueDate), "%Y-%m-%d", t);
	time_t due = now + (7 * 24 * 60 * 60); 
	struct tm *dt = localtime(&due);
	strftime(records[*recordCount].dueDate, sizeof(records[*recordCount].dueDate), "%Y-%m-%d", dt);
	strcpy(records[*recordCount].returnDate,"Pending");
	records[*recordCount].fineAmount=0;
	library[index].quantity--;
	printf("Success: Book '%s' issued! (Issue ID: %d | Due Date: %s)\n",
       		library[index].title,records[*recordCount].issueID,records[*recordCount].dueDate);

	(*recordCount)++;
	
}

void returnBook(Book *library,int bookCount,IssueRecord *records,int *recordCount)
{
	if(*recordCount==0)
	{
		printf("No issue records found in the system\n");
		return;
	}
	int userid,bookid,rcvindex=-1,bookindex=-1;
	printf("Enter BookID: ");
	__fpurge(stdin);
	scanf("%d",&bookid);
	__fpurge(stdin);
	printf("Enter userID: ");
	scanf("%d",&userid);
	__fpurge(stdin);
	for(int i=0;i<*recordCount;i++)
	{
		if((records[i].bookID == bookid) && (records[i].userID == userid) && (strcmp(records[i].returnDate,"Pending")==0))
		{
			rcvindex=i;
		}
	}
	if(rcvindex==-1)
	{
		printf("Error: No active issue record found for this Book ID and User ID\n");
		return;
	}
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(records[rcvindex].returnDate,sizeof(records[rcvindex].returnDate),"%Y-%m-%d",t);
	t->tm_hour=0;	
	t->tm_min=0;
	t->tm_sec=0;
	time_t todayMidnight = mktime(t);
	int y,m,d;
	sscanf(records[rcvindex].dueDate, "%d-%d-%d", &y, &m, &d);
	struct tm due_tm={0};
	due_tm.tm_year = y-1900;
	due_tm.tm_mon = m-1;
	due_tm.tm_mday = d;
	time_t dueTime = mktime(&due_tm);
	double diffSeconds = difftime(todayMidnight, dueTime); 
	int lateDays = (int)(diffSeconds / (24 * 60 * 60));    
	if(lateDays>0)
	{
		records[rcvindex].fineAmount=lateDays*FINE_PER_DAY;
	}
	else
	{
		lateDays=0;
		records[rcvindex].fineAmount=0;
	}
	bookindex=findbyID(library,bookCount,bookid);
	if(bookindex!=-1)
	{
		library[bookindex].quantity++;
	}
	else
	{
		printf("Note: Book record (ID %d) no longer exists in catalog; inventory not updated.\n", bookid);
	}
	printf("Success: Book returned on %s | Late Days: %d | Fine Amount: %.2f\n",
           records[rcvindex].returnDate,lateDays,records[rcvindex].fineAmount);
}
void listIssueBooks(const IssueRecord *records,int recordCount)
{
    if (recordCount==0)
    {
        printf("\nNo issue records available.\n");
        return;
    }

    printf("\n---------> Issued Books Log  <---------\n");
    for (int i = 0; i < recordCount; i++)
    {
        printf("\n----------------------------------------\n");
        printf("Issue ID    : %d\n", records[i].issueID);
        printf("Book ID     : %d\n", records[i].bookID);
        printf("User ID     : %d\n", records[i].userID);
        printf("User Name   : %s\n", records[i].userName);
        printf("Issue Date  : %s\n", records[i].issueDate);
        printf("Due Date    : %s\n", records[i].dueDate);
        printf("Return Date : %s\n", records[i].returnDate);
        printf("Fine Amount : %.2f\n", records[i].fineAmount);
    }
    printf("\n-------------     <^>      -------------\n");
}

