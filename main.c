#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
	char title[49];
	char author[49];
	char subject[49];
};
int numOfbooks = 1;
struct library {
	struct book collection;
	int num_books;
	struct library *next;
};
struct library* firstBook;

int strcasecmp(const char *a, const char *b) {//case insensitive cmp
	int ca, cb;
	do {
		ca = (unsigned char)*a++;
		cb = (unsigned char)*b++;
		ca = tolower(toupper(ca));
		cb = tolower(toupper(cb));
	} while (ca == cb && ca != '\0');
	return ca - cb;
}
void addBook(struct book b, struct library* thislib,FILE* f) {
	if (thislib->num_books == 0) {
		thislib->num_books =1;
		thislib->collection = b;
		thislib->next = malloc(sizeof(struct library));
		thislib->next->num_books = 2;
	}
	else {
	thislib->collection = b;
	thislib->num_books =  ++numOfbooks;
	thislib->next=  malloc(sizeof(struct library));
	thislib->next->num_books = numOfbooks;
	}
	char line[250];
	//printf("%s", b.title);
	sprintf(line, "The book %s has been added to the library\n", b.title);
	FILE *fOutput;
	fOutput = fopen("output.txt", "a+");
	fprintf(fOutput, line);
	fprintf(fOutput, "\n");
	fclose(fOutput);
	printf(line);
	printf("\n");

}
void deleteBook(char * c, struct library* thislib) {
	struct library* tempBook;
	tempBook = firstBook;
	struct library* prevBook = NULL;
	int isDeleted = 0;
	for (int i = 0; i < thislib->num_books; i++)
	{
		if (strcmp(tempBook->collection.title, c)==0) {
			if (tempBook == firstBook) {
				firstBook = tempBook->next;
			}
			else {
				prevBook->next = tempBook->next;
			}
			isDeleted = 1;
		}
		else {
			prevBook = tempBook;
			tempBook = tempBook->next;
		}
	}
	char line[250];
	if (isDeleted == 1) {
		sprintf(line, "The book %s has been removed from the library.\n", c);
	}
	FILE *fOutput;
	fOutput = fopen("output.txt", "a+");
	fprintf(fOutput, line);
	fprintf(fOutput, "\n");

	fclose(fOutput);
	printf(line);
	printf("\n");


}
void searchBook(char * c, struct library* thislib) {
	struct library* tempBook;
	tempBook = firstBook;
	struct library* prevBook = NULL;
	int isFound = 0;
	for (int i = 0; i < thislib->num_books; i++)
	{
		if (strcmp(tempBook->collection.title, c) == 0) {

			isFound = 1;
			break;
		}
		else {
			prevBook = tempBook;
			tempBook = tempBook->next;
		}
	}
	char line[250];
	if (isFound == 1) {
		sprintf(line, "The book %s is currently in the library.\n", c);
	}
	else {
		sprintf(line, "The book %s is not currently in the library.\n", c);

	}
	FILE *fOutput;
	fOutput = fopen("output.txt", "a+");
	fprintf(fOutput, line);
	fprintf(fOutput, "\n");

	fclose(fOutput);
	printf(line);
	printf("\n");

}
void filterAuthor(char * c, struct library* thislib) {
	struct library* tempBook;
	tempBook = firstBook;
	struct library* prevBook = NULL;
	int isFound = 0;
	char longLine[750]="\0";
	char line[650]="\0";
	for (int i = 0; i < thislib->num_books; i++)
	{
		if (strcasecmp(tempBook->collection.author, c) == 0) {
			strcat(line, tempBook->collection.title);
			strcat(line, "\n");
			isFound = 1;
		}
			prevBook = tempBook;
			tempBook = tempBook->next;
	}
	if (isFound == 1) {
		sprintf(longLine, "List of all books by %s\n", c);
		strcat(longLine, line);
	}
	else {
		sprintf(longLine, "List of all books by %s\nNo books from author %s.\n", c,c);
	}
	FILE *fOutput;
	fOutput = fopen("output.txt", "a+");
	fprintf(fOutput, longLine);
	fprintf(fOutput, "\n");
	fclose(fOutput);
	printf(longLine);
	printf("\n");
}
void filterSubject(char * c, struct library* thislib) {
	struct library* tempBook;
	tempBook = firstBook;
	struct library* prevBook = NULL;
	int isFound = 0;
	char longLine[750] = "\0";
	char line[650] = "\0";
	for (int i = 0; i < thislib->num_books; i++)
	{
		if (strcasecmp(tempBook->collection.subject, c) == 0) {
			strcat(line, tempBook->collection.title);
			strcat(line, "\n");
			isFound = 1;
		}
		prevBook = tempBook;
		tempBook = tempBook->next;
	}
	if (isFound == 1) {
		sprintf(longLine, "List of all books on %s\n", c);
		strcat(longLine, line);
	}
	else {
		sprintf(longLine, "List of all books on %s\nNo books from subject %s.\n",c, c);
	}
	FILE *fOutput;
	fOutput = fopen("output.txt", "a+");
	fprintf(fOutput, longLine);
	fprintf(fOutput, "\n");
	fclose(fOutput);
	printf(longLine);
	printf("\n");
}

int main() {
	struct library*l =  malloc(sizeof(struct library));
	l->num_books = 0;

	firstBook = l;
	FILE *fptr;
	fptr = fopen("library.txt", "a+");
	if (fptr == NULL) {
		printf("Sorry :(! Can't open the file");
	}
	else {
		int numOfUpdates;
		fscanf(fptr, "%d\n", &numOfUpdates);
		char line[256];
		printf("%d\n", numOfUpdates);
		while (fgets(line, sizeof(line), fptr)) {
			int updateType = atoi(line);
			char c[49];
			struct book b;
			switch (updateType) {
			case 1:
				sscanf(line, "%d %s %s %s", &updateType, &b.title, &b.author, &b.subject);
				//printf("%s", b.title);
				addBook(b, l, fptr);
				l = l->next;
				//printf("%s", b.title);
				break;
			case 2:
				sscanf(line, "%d %s", &updateType, c);
				deleteBook(c, l);
				break;
			case 3:
				sscanf(line, "%d %s", &updateType, c);
				searchBook(c, l);
				break;
			case 4:
				sscanf(line, "%d %s", &updateType, c);
				filterAuthor(c, l);
				break;
			case 5:
				sscanf(line, "%d %s", &updateType, c);
				filterSubject(c, l);
				break;
			default:
				printf("%d", updateType);
				break;
			}
		}
	}


	return 0;

}
