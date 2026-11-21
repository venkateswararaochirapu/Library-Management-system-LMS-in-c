#include"header.h"

void addBook (Book *library,int *bookCount)
{
        if(*bookCount >= MAX_BOOKS)
        {
                printf("\nError:Library storage ias full!\n");
                return;
        }
        printf("---Add new Book---\n");
        int newBookID;
        printf("Enter unique book id:");
        scanf("%d",&newBookID);
        for(int i=0;i<*bookCount;i++)
        {
                if(library[i].bookID == newBookID)
                {
                        printf("\nError: this is ID is allready existed!\n");
                        return;
                }
        }
        Book *newBook=&library[*bookCount];
        newBook->bookID=newBookID;
        printf("Enter book title: \n");
        __fpurge(stdin);
        //fgets(newBook->title,sizeof(newBook->title),stdin);
        //newBook->title[strcspn(newBook->title,"\n")]= '\0';
        readString(newBook->title,sizeof(newBook->title));
        printf("Enter Author name: \n");
        __fpurge(stdin);
        //fgets(newBook->author,sizeof(newBook->author),stdin);
        //newBook->author[strcspn(newBook->author,"\n")]= '\0';
        readString(newBook->author,sizeof(newBook->author));
        printf("Enter Available quantity: \n");
        scanf("%d",&newBook->quantity);
        if(newBook->quantity<0)
        {
                printf("Warning: Quantity cannot be negative. Setting to 0.\n");
                newBook->quantity=0;
        }
        (*bookCount)++;
        printf("Success: Book '%s' added to inventory!\n", newBook->title);
}

void updateBook(Book *library,int bookCount)
{
	if(bookCount==0)
	{
		printf("\nNo books available in the library.\n");
        	return;
	}
	char searchname[100];
        int searchid,choice,index=-1;
        printf("\n---update book details---\n");
        printf("By Book id(press: 1)\n");
        printf("By Book Name(press: 2)\n");
        printf("Back to Main Menu(press: 3)\n");
        printf("Enter choice: ");
CHOICE: scanf("%d",&choice);
	__fpurge(stdin);
        if(choice == 1)
        {
                printf("Enter Book Id to update: \n");
                scanf("%d",&searchid);
                index=findbyID(library,bookCount,searchid);
        }
        else if(choice == 2)
        {
                printf("Enter complete Book title to update:\n");
                //fgets(searchname,sizeof(searchname),stdin);
                //searchname[strcspn(searchname,"\n")]='\0';
                readString(searchname,sizeof(searchname));
                index=findbyName(library,bookCount,searchname);
        }
        else if(choice == 3)
        {
                return;
        }
        else
        {
                printf("Invalid choice\n");
                printf("re-enter the choice:\n");
                goto CHOICE;
        }
        if(index == -1 )
        {
                printf("Error: Book records not found.\n");
                return;
        }
        printf("\nModifying record for: %s (ID: %d)\n", library[index].title, library[index].bookID);
        while(1)
        {
                printf("to update title(press 1)\n");
                printf("to modify Author(press 2)\n");
                printf("to modify Quantity(press 3)\n");
                printf("to exit from modifications(press 4)");
                printf("Select which option to modify: ");
                __fpurge(stdin);
		scanf("%d",&choice);
                __fpurge(stdin);
		switch(choice)
                {
                        case 1: printf("Enter New Title:\n");
                                //fgets(library[index].title,sizeof(library[index].title),stdin);
                                //library[index].title[strcspn(library[index].title,"\n")]='\0';
                                readString(library[index].title,sizeof(library[index].title));
                                break;

                        case 2: printf("Enter New Author name:\n");
                                //fgets(library[index].author,sizeof(library[index].author),stdin);
                                //library[index].author[strcspn(library[index].author,"\n")]='\0';
                                readString(library[index].author,sizeof(library[index].author));
                                break;

                        case 3: printf("Enter New Quantity:\n");
                                scanf("%d",&library[index].quantity);
        			if(library[index].quantity<0)
        			{
                			printf("Warning: Quantity cannot be negative. Setting to 0.\n");
               				library[index].quantity=0;
        			}
                                break;

                        case 4: printf("Success: Book details updated successfully!\n");
				return;
                        default: printf("Invalid Choice retry\n");
                }
        }
}

void removeBook(Book *library,int *bookCount)
{
	if(*bookCount==0)
	{
		printf("\nNo books available in the library.\n");
        	return;
	}
	char searchname[100];
        int searchid,choice,index=-1;
        printf("\n---Remove book details---\n");
        printf("By Book id(press: 1)\n");
        printf("By Book Name(press: 2)\n");
        printf("Back to Main Menu(press: 3)\n");
        printf("Enter choice: ");
OPTION: scanf("%d",&choice);
	__fpurge(stdin);
        if(choice == 1)
        {
                printf("Enter Book Id to delete: \n");
                scanf("%d",&searchid);
                index=findbyID(library,*bookCount,searchid);
        }
        else if(choice == 2)
        {
                printf("Enter complete Book title to delete:\n");
                //fgets(searchname,sizeof(searchname),stdin);
                //searchname[strcspn(searchname,"\n")]='\0';
                readString(searchname,sizeof(searchname));
                index=findbyName(library,*bookCount,searchname);
        }
        else if(choice == 3)
        {
                return;
        }
        else
        {
                printf("Invalid choice\n");
                printf("re-enter the choice:\n");
                goto OPTION;
        }
        if(index == -1 )
        {
                printf("Error: Book records not found.\n");
                return;
        }
	for(int i=index;i<(*bookCount)-1;i++)
	{
		library[i]=library[i+1];
	}
	(*bookCount)--;
	printf("Success: Book tracking record deleted from database.\n");
}

void searchBook(Book *library,int bookCount)
{
	if(bookCount==0)
	{
		printf("\nNo books available in the library.\n");
        	return;
	}
	char searchname[100];
	int searchid,choice,found=0,index=-1;
	printf("---Search Book Directory ---\n");
	printf("By Book id(press 1)\n");
	printf("By Book title(press 2)\n");
	printf("By Author name(press 3)\n");
	printf("Back to Main Menu(press 4)\n");
	printf("Enter choice: ");
CHOICE1:scanf("%d",&choice);
	__fpurge(stdin);
	if(choice == 1)
	{
		printf("Enter Book Id: ");
		scanf("%d",&searchid);
		__fpurge(stdin);
		index=findbyID(library,bookCount,searchid);
		if(index != -1)
		{
			printf("Book Found:\nID: %d | Title: %s | Author: %s | Quantity: %d\n",library[index].bookID,library[index].title,library[index].author,library[index].quantity);
			found=1;
		}
	}
	else if(choice == 2)
	{
		printf("Enter Book Title: ");
		__fpurge(stdin);
		readString(searchname,sizeof(searchname));
		printf("\nMatching Results:\n");
		for(int i=0;i<bookCount;i++)
		{
			if(my_strstr(library[i].title,searchname) != NULL)
			{
				printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",library[i].bookID,library[i].title,library[i].author,library[i].quantity);
                        found=1;
			}
		}
	}
	else if(choice == 3)
	{
		printf("Enter Author Name: ");
                __fpurge(stdin);
                readString(searchname,sizeof(searchname));
                printf("\nMatching Results:\n");
                for(int i=0;i<bookCount;i++)
                {
                        if(my_strstr(library[i].author,searchname) != NULL)
                        {
                                printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",library[i].bookID,library[i].title,library[i].author,library[i].quantity);
                        found=1;
                        }
              	}
        }
	else if(choice == 4 ) return;
	else
	{
		printf("Inavlid Choice\n");
		goto CHOICE1;
	}
	if(!found) printf("No books matched your search entry criteria.\n");

}

void viewAllBooks(Book *library,int bookCount)
{
	if(bookCount==0)
	{
		printf("\nNo books available in the library.\n");
        	return;
	}
	printf("\n------>All book details<------\n");
	for(int i=0;i<bookCount;i++)
	{
		printf("\n----------------------------------------\n");
		printf("Book Id : %d\n",library[i].bookID);
		printf("title   : %s\n",library[i].title);
		printf("Author  : %s\n",library[i].author);
		printf("Quantity: %d\n",library[i].quantity);
	}
	printf("\n-----------     <^>      ----------\n");
}
