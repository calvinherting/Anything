#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TRUE 1



typedef struct duration
{
	int hours;
	int minutes;
}Duration;

typedef struct record
{
	char title[20];
	char director[20];
	char description[200];
	char genre[20];
	Duration runtime;
	int year;
	int timesPlayed;
	int rating;

}Record;

typedef struct node
{
	Record Data;
	struct node* Next;
	struct node* Prev;
}Node;

//Uses head to see if the list is empty
int isEmpty(Node* head);
//Displays the home menu of the playlist manager and returns the user choice.
int displayMenu(void);
//Inserts node at the front of the list
int insertFront(Node* node, Node** head, Node** tail);
//Reads from a file and stores the data in a new node.
void readFile(Node** head, Node** tail);
//Writes to the same .csv file with the new data from playlist manager.
void writeFile(Node** tail);
//Prints out the list (aka displays the videos)
void printList(Node* head);
//Allows the user to insert their own node at the beginning of the list. The user inputs video data.
void userInsert(Node** head, Node** tail);
//Allows the user to edit any fields within each video in linked list. 
void editList(Node** head);
//Finds the user desired director and returns a pointer to that specific node. 
Node* findDirector(Node** head, char* director);
//Allows the user to rate every video. 
void rateFilm(Node** head);
//Allows the user to choose which video they would like to start with in the playlist and then plays every title in list after that. 
void playFilm(Node* head);
