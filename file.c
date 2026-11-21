#include"header.h"
#include<string.h>
#include<ctype.h>
void readString(char *str,int size)
{
    if(fgets(str,size,stdin) != NULL)
    {
        str[strcspn(str, "\n")] = '\0'; // Strip newline immediately
    }
}
int my_strcmp(const char *s1,const char *s2)
{
        while(*s1 && *s2 && (tolower((unsigned char)*s1) == tolower((unsigned char)*s2)))
        {
                s1++;
                s2++;
        }
        return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
char *my_strstr(const char *str,const char *sub)
{
        if(*sub == '\0') return (char *)str;
        for(;*str;str++)
        {
                if(tolower((unsigned char)*str) == tolower((unsigned char)*sub))
                {
                        char *s1=(char *)str;
                        char *s2=(char *)sub;
                        while(*s1 && *s2 && tolower((unsigned char)*s1) == tolower((unsigned char)*s2))
                        {
                                s1++;
                                s2++;
                        }
                        if(*s2 == '\0') return (char *)str;
                }
        }
        return NULL;
}

int findbyID(Book *library,int bookCount,int id)
{
        for(int i=0;i<bookCount;i++)
        {
                if(library[i].bookID == id)
                        return i;
        }
        return -1;
}
int findbyName(Book *library,int bookCount,char *name)
{
        for(int i=0;i<bookCount;i++)
        {
                if(my_strcmp(library[i].title,name)==0)
                        return i;
        }
        return -1;
}
int findbyAuthor(Book *library,int bookCount,char *author)
{
        for(int i=0;i<bookCount;i++)
        {
                if(my_strcmp(library[i].author,author)==0)
                {
                        return i;
                }
        }
        return -1;
}

void saveData(const Book *library,int bookCount,const IssueRecord *records,int recordCount)
{
	FILE *fptr=NULL;
	fptr=fopen("Books.txt","w");
	if(fptr==NULL)
	{
		printf("ERROR: file can't open\n");
		return;
	}
	for(int i=0;i<bookCount;i++)
	{
		fprintf(fptr,"%d|%s|%s|%d\n",
				library[i].bookID,
				library[i].title,
				library[i].author,
				library[i].quantity);
	}
	fclose(fptr);
	fptr=fopen("Records.txt","w");
	if(fptr==NULL)
        {
                printf("ERROR: file can't open\n");
                return;
        }
	for(int i=0;i<recordCount;i++)
        {
		fprintf(fptr, "%d|%d|%d|%s|%s|%s|%s|%.2f\n",
                    records[i].issueID,
                    records[i].bookID,
                    records[i].userID,
                    records[i].userName,
                    records[i].issueDate,
                    records[i].dueDate,
                    records[i].returnDate,
                    records[i].fineAmount);
        }
        fclose(fptr);
	printf("Data saved Sucessfully\n");
}
void loadData(Book *library,int *bookCount,IssueRecord *records,int *recordCount)
{
	FILE *fptr=NULL;
	*bookCount=0;
	*recordCount=0;
	fptr=fopen("Books.txt","r");
        if(fptr==NULL)
	{
		printf("ERROR: file can't open\n");
		return;
	}
	while(*bookCount< MAX_BOOKS &&
		fscanf(fptr,"%d|%99[^|]|%49[^|]|%d\n",
				&library[*bookCount].bookID,
				library[*bookCount].title,
				library[*bookCount].author,
				&library[*bookCount].quantity)==4)
	{
		(*bookCount)++;
	}
	fclose(fptr);
	fptr=fopen("Records.txt","r");
	if(fptr==NULL)
        {
                printf("ERROR: file can't open\n");
                return;
        }
	while(*recordCount<MAX_RECORDS &&
		fscanf(fptr, "%d|%d|%d|%49[^|]|%10[^|]|%10[^|]|%10[^|]|%f\n",
                    &records[*recordCount].issueID,
                    &records[*recordCount].bookID,
                    &records[*recordCount].userID,
                    records[*recordCount].userName,
                    records[*recordCount].issueDate,
                    records[*recordCount].dueDate,
                    records[*recordCount].returnDate,
                    &records[*recordCount].fineAmount)==8)
	{
		(*recordCount)++;
	}
        fclose(fptr);

}
