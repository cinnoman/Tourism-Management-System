#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

enum state {menu, admin, user, loggedIn};
enum state currentState = menu;

typedef struct node {
    char username[100];
    char password[100];
    char place[100];
    float price;
    int numberOfTicker;
    struct node *next;
    int booked;
} node;

typedef struct ticket{
    int serialNumber;
    char placeCode[5];
    char placeName[100];
    float newPrice;
    int totalTicket;
    struct ticket *link;
} ticket;


ticket *top;

int initial[100], n, i;

void getArray() {
    char help[256];

    FILE *fp;

    fp = fopen("array.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    while (fgets(help, sizeof(help), fp) != NULL) {
        initial[i] = atoi(help);
        i++;
    }
    fclose(fp);
    n = i;
}

void updateArrayToFile(int index, int value) {
    FILE *fp;
    FILE *tempFile;
    char buffer[256];
    int currentLine = 0;

    fp = fopen("array.txt", "r");
    tempFile = fopen("temp.txt", "w");
    if (fp == NULL || tempFile == NULL) {
        perror("Error opening the file");
        exit(1);
    }

   
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (currentLine == index) {
            fprintf(tempFile, "%d\n", value);
        } else {
            fprintf(tempFile, "%s", buffer);
        }

        currentLine++;
    }

    fclose(fp);
    fclose(tempFile);
    remove("array.txt");
    rename("temp.txt", "array.txt");
}

void updateCancelledTicketsToFile(int index, int value) {
    FILE *fp;
    FILE *tempFile;
    char buffer[256];
    int currentLine = 0;

    fp = fopen("array.txt", "r");
    tempFile = fopen("temp_array.txt", "w");

 
    if (fp == NULL || tempFile == NULL) {
        perror("Error opening the file");
        exit(1);
    }

  
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (currentLine == index) {
          
            int oldValue = atoi(buffer);
            fprintf(tempFile, "%d\n", oldValue + value);
        } else {
          
            fprintf(tempFile, "%s", buffer);
        }

        currentLine++;
    }

  
    fclose(fp);
    fclose(tempFile);

    
    remove("array.txt");

   
    rename("temp_array.txt", "array.txt");
}

void updateTicketAmount(int placeIndex, int newAmount) {
    if (placeIndex >= 0 && placeIndex < 10) {
        initial[placeIndex] = newAmount;
        updateArrayToFile(placeIndex, newAmount);
        printf("\t\t\tTicket amount for place updated successfully.\n");
    } else {
        printf("\t\t\tInvalid place index.\n");
    }
}


void printCenteredText(char *, int);
void gotoxy(x,y);
void showBrochure();   
node *userInitialState(node*);
node *addUser(node*);  
node *deleteUser(node*);
void loginUser(node*);  
void bookTicket(node*);     
void printTicket(node*);   
void cancelTicket(node*);      
void changePassword(node*);   
void changeUsername(node*);    
void logOutUser();            
void checkTicket(node*);   
void writeToFile(node*);
void exitTheProgramme();       
void addNewTicket();
void writeDestinationsToFile(ticket *);
void readDestinationsFromFile();

char currentUser[100];



int main(){
    system("color E0");
    system("cls");

    int progress = 0;
    int total = 100;  
    int width = 80;   
    getArray();


    printf("             _______               _                 __  __                                                   _      _____           _                 \n");
    printf("            |__   __|             (_)               |  \\/  |                                                 | |    / ____|         | |                \n");
    printf("               | | ___  _   _ _ __ _ ___ _ __ ___   | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  | (___  _   _ ___| |_ ___ _ __ ___  \n");
    printf("               | |/ _ \\| | | | '__| / __| '_ ` _ \\  | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n");
    printf("               | | (_) | |_| | |  | \\__ \\ | | | | | | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_   ____) | |_| \\__ \\ ||  __/ | | | | |\n");
    printf("               |_|\\___/ \\__,_|_|  |_|___/_| |_| |_| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |_____/ \\__, |___/\\__\\___|_| |_| |_|\n");
    printf("                                                                               __/ |                                        __/ |                      \n");
    printf("                                                                              |___/                                        |___/                       \n");

    printCenteredText("\n\n          \t\t\t\tWelcome", width);

    printf("\n\n");

    while (progress <= total) {
        int percentage = (progress * 100) / total;

        int numEquals = (percentage * (width - 9)) / 100;

        printf("\r[ ");
        for (int i = 0; i < numEquals; i++) {
            printf("=");
        }
        for (int i = numEquals; i < width - 9; i++) {
            printf(" ");
        }
        printf("] %d%%", percentage);
        fflush(stdout);
        sleep(1);  

        progress += 100;
    }

    printf("\n\n\n");
    system("pause");
    system("CLS");

    printf("\n\n\n\n\n\n");

    printf("\t\t\t\t\t  __  __                        \n");
    printf("\t\t\t\t\t |  \\/  |                       \n");
    printf("\t\t\t\t\t | \\  / |   ___   _ __    _   _ \n");
    printf("\t\t\t\t\t | |\\/| |  / _ \\ | '_ \\  | | | |\n");
    printf("\t\t\t\t\t | |  | | |  __/ | | | | | |_| |\n");
    printf("\t\t\t\t\t |_|  |_|  \\___| |_| |_|  \\__,_|\n");


    node *head=NULL;
    int choice1, choice2;
    head = userInitialState(head);

    while(1){
           if (currentState == menu) {
            system("color 74");
            printf("\n\n\n\t\t\t\t\t Welcome to the Menu\n\n");
            printf("\t\t\t\t\tAdmin\t - 1\n");
            printf("\t\t\t\t\tUser\t - 2\n\n");
            printf("\t\t\t\t\tEnter: ");
            scanf("%d", &choice1);
             switch (choice1) {
                case 1:
                    currentState = admin;
                    break;
                case 2:
                    currentState = user;
                    system("cls");
                    break;
                default:
                    printf("\t\t\tInvalid input\n");
            }
           }
        else if(currentState==admin){
                system("cls");
                printf("\n\n");
                printf("\t\t\t  _____              _____                           _ \n");
                printf("\t\t\t / ____|            |  __ \\                         | |\n");
                printf("\t\t\t| |       ______    | |__) |   __ _   _ __     ___  | |\n");
                printf("\t\t\t| |      |______|   |  ___/   / _` | | '_ \\   / _ \\ | |\n");
                printf("\t\t\t| |____             | |      | (_| | | | | | |  __/ | |\n");
                printf("\t\t\t \\_____|            |_|       \\__,_| |_| |_|  \\___| |_|\n");

                printf("\n\n");
                printf("\t\t\tEnter admin's username: ");
                char username[100];
                char password[100];
                scanf("%s", username);
                printf("\t\t\tEnter password: ");
                scanf(" %[^\n]s", password);
                if((!strcmp(username, "admin")) && (!strcmp(password, "password"))){
                    currentState=admin;
                    printf("\n\t\t\tFor adding new destination     - 1\n");
                    printf("\t\t\tFor adding new ticket amount   - 2\n");
                    printf("\n\t\t\tEnter: ");
                    int choice;
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        addNewTicket();
                        // writeDestinationsToFile(top);
                        break;
                    case 2:
                        printf("\t\t\tEnter the place serial (1-10): ");
                        int placeSerial;
                        int placeIndex;
                        int newAmount;
                        scanf("%d", &placeSerial);

                        placeIndex = placeSerial - 1;

                        if (placeIndex >= 0 && placeIndex < 10) {
                              printf("\t\t\tEnter the new ticket amount: ");
                              scanf("%d", &newAmount);
                              updateTicketAmount(placeIndex, newAmount);
                            } else {
                                printf("\t\t\tInvalid place index.\n");
                            }
                    }
                }
                currentState=menu;

        }
        else if(currentState==user){
            system("color 74");
            system("pause");
            system("cls");
            printf("\n\n");
            printf("\t\t\t ____    _    _   _____     ____    __  __    ____    _   _ \n");
            printf("\t\t\t|  _ \\  | |  | | |  __ \\   / __ \\  |  \\/  |  / __ \\  | \\ | |\n");
            printf("\t\t\t| |_) | | |__| | | |__) | | |  | | | \\  / | | |  | | |  \\| |\n");
            printf("\t\t\t|  _ <  |  __  | |  _  /  | |  | | | |\\/| | | |  | | | . ` |\n");
            printf("\t\t\t| |_) | | |  | | | | \\ \\  | |__| | | |  | | | |__| | | |\\  |\n");
            printf("\t\t\t|____/  |_|  |_| |_|  \\_\\  \\____/  |_|  |_|  \\____/  |_| \\_|\n");
            printf("\n\n\t\t\t\t\t Add User    -  1\n\t\t\t\t\t Login User  -  2\n\t\t\t\t\t Brochure    -  3\n\t\t\t\t\t Exit        -  4\n\n\t\t\t\t\t Enter: ");
            scanf("%d", &choice1);
            switch (choice1)
            {
            case 1:
                head=addUser(head);
                break;
            case 2:
                loginUser(head);
                break;
            case 3:
                showBrochure();
                readDestinationsFromFile();
                break;
            case 4:
                 exitTheProgramme();
                 exit(0);
                 break;
            default:
                printf("\t\t\tInvalid input\n");
            }
            currentState==menu;
        }
        else if(currentState==loggedIn){
            system("CLS");
            printf("\n\n");
            printf("\t\t\t                                                   _   \n");
            printf("\t\t\t     /\\                                           | |  \n");
            printf("\t\t\t    /  \\      ___    ___    ___    _   _   _ __   | |_ \n");
            printf("\t\t\t   / /\\ \\    / __|  / __|  / _ \\  | | | | | '_ \\  | __|\n");
            printf("\t\t\t  / ____ \\  | (__  | (__  | (_) | | |_| | | | | | | |_ \n");
            printf("\t\t\t /_/    \\_\\  \\___|  \\___|  \\___/   \\__,_| |_| |_|  \\__|\n");
            printf("\t\t\t                                                        \n");

            printf("\n\t\t\tBook Ticket         -  1\n\t\t\tCheck Ticket        -  2\n\t\t\tPrint Ticket        -  3\n\t\t\tCancel Ticket       -  4\n\t\t\tChange Password     -  5\n\t\t\tChange username     -  6\n\t\t\tLogout User         -  7\n"
            "\t\t\tBrochure            -  8\n\t\t\tDelete Account      -  9\n\t\t\tExit                - 10\n\n\t\t\tEnter:   ");
            scanf("%d", &choice2);
            switch (choice2)
            {
            case 1:
                bookTicket(head);
                system("PAUSE");
                system("CLS");
                break;
            case 2:
                checkTicket(head);
                system("PAUSE");
                system("CLS");
                break;
            case 3:
                printTicket(head);
                system("PAUSE");
                system("CLS");
                break;
            case 4:
                cancelTicket(head);
                system("PAUSE");
                system("CLS");
                break;
            case 5:
                changePassword(head);
                system("PAUSE");
                system("CLS");
                break;
            case 6:
                changeUsername(head);
                system("PAUSE");
                system("CLS");
                break;
            case 7:
                logOutUser(head);
                system("PAUSE");
                system("CLS");
                break;
            case 8:
                showBrochure();
                readDestinationsFromFile();
                system("PAUSE");
                system("CLS");
                break;
            case 9:
                deleteUser(head);
                system("PAUSE");
                system("CLS");
            case 10:
                exitTheProgramme();
                exit(0);
                break;
            default:
                printf("\t\t\tInvalid input");
            }
            currentState==menu;
        }
    }

    return 0;
}

void printCenteredText(char *text, int width) {
    int textLength = strlen(text);

    if (textLength >= width) {
        printf("%s", text);
    } else {
        int padding = (width - textLength) / 2;
        for (int i = 0; i < padding; i++) {
            putchar(' ');
        }
        printf("%s", text);
    }
    printf("\n");
}

void gotoxy(int x, int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//admin

void writeDestinationsToFile(ticket *top) {
    FILE *fp = fopen("destinations.txt", "a"); //append
    if (fp == NULL) {
        printf("Could not open destinations file for writing.\n");
        return;
    }

    ticket *temp = top;
    while (temp != NULL) {
        fprintf(fp, " %d  - %s.  %s    - Taka %f   available tickets - %d\n",temp->serialNumber, temp->placeCode, temp->placeName, temp->newPrice, temp->totalTicket);
        temp = temp->link;
    }

    fclose(fp);
}



void addNewTicket(){

    ticket *newNode;
    newNode = malloc(sizeof(ticket));
    fflush(stdin);
    printf("\t\t\tEnter serial number: ");
    scanf("%d", &newNode->serialNumber);
    fflush(stdin);
    printf("\t\t\tEnter code: ");
    scanf("%s", newNode->placeCode);
     fflush(stdin);
    printf("\t\t\tEnter new destination name: ");
    scanf(" %[^\n]s", newNode->placeName);
     fflush(stdin);
    printf("\t\t\tEnter price: ");
    scanf("%f", &newNode->newPrice);
     fflush(stdin);
    printf("\t\t\tEnter available tickets: ");
    scanf("%d", &newNode->totalTicket);
    newNode->link = NULL;

    if(top==NULL){
        top = newNode;
    }
    else{
        ticket *temp = top;
        while(temp->link!=NULL){
            temp=temp->link;
        }
        temp->link = newNode;
    }
     writeDestinationsToFile(top);
     printf("\t\t\tDestination added successfully.\n");
}

void readDestinationsFromFile() {
    FILE *fp = fopen("destinations.txt", "r");
    if(fp!=NULL){
        char line[200]; 
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("\t\t\t%s", line);
    }
    fclose(fp);
    }
    return;
}



node *userInitialState(node *head){
    node *t, *newNode, temp;
    FILE *fp;
    fp=fopen("user.txt", "r");

    if(fp==NULL){
        return NULL;
    }
    if(fgetc(fp)==EOF){
        return NULL;
    }

    rewind(fp);
    while (fscanf(fp, "%s %s %s %f %d %d", temp.username, temp.password, temp.place, &temp.price, &temp.numberOfTicker, &temp.booked)!=EOF){
        newNode=(node*)malloc(sizeof(node));
        strcpy(newNode->username, temp.username);
        strcpy(newNode->password, temp.password);
        strcpy(newNode->place, temp.place);
        newNode->price = temp.price;
        newNode->numberOfTicker = temp.numberOfTicker;
        newNode->booked=temp.booked;
        newNode->next = NULL;

        if (head==NULL)
        {
            head=t=newNode;
        }
        else {
            head->next=newNode;
            head=newNode;
        }
    }
   fclose(fp);
   return t;
}

void writeToFile(node* head){
    FILE *fp;
    fp = fopen("user.txt","w");
    while (head!=NULL)
    {
        fprintf(fp,"%s %s %s %f %d %d\n", head->username, head->password, head->place, head->price, head->numberOfTicker,head->booked);
        head=head->next;
    }
    fclose(fp);
}

void showBrochure(){
    system("CLS");
    printf("\t\t\t  _____           _                   _        _         _   \n");
    printf("\t\t\t |  __ \\         (_)                 | |      (_)       | |  \n");
    printf("\t\t\t | |__) |  _ __   _    ___    ___    | |       _   ___  | |_ \n");
    printf("\t\t\t |  ___/  | '__| | |  / __|  / _ \\   | |      | | / __| | __|\n");
    printf("\t\t\t | |      | |    | | | (__  |  __/   | |____  | | \\__ \\ | |_ \n");
    printf("\t\t\t |_|      |_|    |_|  \\___|  \\___|   |______| |_| |___/  \\__|\n");

    printf("\n\n");
    getArray();
    printf("\t\t\t 1   - AA. Maldives    - Taka 50,000.0   avaiable tickets - %d\n", initial[0]);
    printf("\t\t\t 2   - BB. Sri Lanka   - Taka 60,000.0   avaiable tickets - %d\n", initial[1]);
    printf("\t\t\t 3   - CC. Bali        - Taka 100000.0   avaiable tickets - %d\n", initial[2]);
    printf("\t\t\t 4   - DD. Thailand    - Taka 25000.0    avaiable tickets - %d\n", initial[3]);
    printf("\t\t\t 5   - EE. Cox's Bazar - Taka 10,000     avaiable tickets - %d\n", initial[4]);
    printf("\t\t\t 6   - FF. Kolkata     - Taka 15,000.0   avaiable tickets - %d\n", initial[5]);
    printf("\t\t\t 7   - GG. Kashmir     - Taka 30,000.0   avaiable tickets - %d\n", initial[6]);
    printf("\t\t\t 8   - HH. Malaysia    - Taka 35,000.0   avaiable tickets - %d\n", initial[7]);
    printf("\t\t\t 9   - II. Turkey      - Taka 120,000.0  avaiable tickets - %d\n", initial[8]);
    printf("\t\t\t10   - JJ. Australia   - Taka 200,000.0  avaiable tickets - %d\n", initial[9]);

}


void checkTicket(node *head){
    while (head!=NULL)
    {
        if(!strcmp(head->username, currentUser)){
            break;
       }
       head=head->next;
    }
    if(!strcmp(head->place, "\0") || head->price==0.0 || head->numberOfTicker==0){
        printf("\n\t\t\tYou haven't booked any ticket yet\n\n");
        return;
    }
    float amount = 0.0;
    amount = (head->price) * (head->numberOfTicker);
    printf("\n\t\t\tYou have booked %d tickets for visiting %s and the total cost is %f\n\n", head->numberOfTicker, head->place, amount);

}


node *addUser(node *head){
    system("cls");
    printf("\n\n");
    printf("\t\t   _____                         _                                                               _   \n");
    printf("\t\t  / ____|                       | |                /\\                                           | |  \n");
    printf("\t\t | |       _ __    ___    __ _  | |_    ___       /  \\      ___    ___    ___    _   _   _ __   | |_ \n");
    printf("\t\t | |      | '__|  / _ \\  / _` | | __|  / _ \\     / /\\ \\    / __|  / __|  / _ \\  | | | | | '_ \\  | __|\n");
    printf("\t\t | |____  | |    |  __/ | (_| | | |_  |  __/    / ____ \\  | (__  | (__  | (_) | | |_| | | | | | | |_ \n");
    printf("\t\t  \\_____| |_|     \\___|  \\__,_|  \\__|  \\___|   /_/    \\_\\  \\___|  \\___|  \\___/   \\__,_| |_| |_|  \\__|\n");

    node *temp;
    temp = head;
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    fflush(stdin);
    printf("\n\n\n\t\t\tEnter username or email: ");
    scanf("%s", newNode->username);
    while (temp!=NULL)
    {
        if(!strcmp(temp->username, newNode->username)){
            printf("\n\t\t\tUsername already exists\n");
            return head;
        }
        temp=temp->next;
    }
    temp=head;
    fflush(stdin);
    printf("\t\t\tEnter Password: ");
    scanf(" %[^\n]s", &newNode->password);
    printf("\n\t\t\tAccount created successfully\n");
    newNode->next=NULL;
    strcpy(newNode->place, "N/A");
    newNode->price = 0.0;
    newNode->numberOfTicker = 0;
    newNode->booked=0;

    if(temp==NULL){
        temp=head=newNode;
    }
    else {
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newNode;
    }
    writeToFile(head);
    return head;
}


void loginUser(node *head){
    system("cls");

    printf("\n\n");
    printf("\t\t\t   _____   _____    _____   _   _     _____   _   _ \n");
    printf("\t\t\t  / ____| |_   _|  / ____| | \\ | |   |_   _| | \\ | |\n");
    printf("\t\t\t | (___     | |   | |  __  |  \\| |     | |   |  \\| |\n");
    printf("\t\t\t  \\___ \\    | |   | | |_ | | . ` |     | |   | . ` |\n");
    printf("\t\t\t  ____) |  _| |_  | |__| | | |\\  |    _| |_  | |\\  |\n");
    printf("\t\t\t  |____/  |_____|  \\_____| |_| \\_|   |_____| |_| \\_|\n");
    printf("\t\t\t                                                    \n");

    char username[100];
    char password[100];
    fflush(stdin);
    printf("\n\n");
    printf("\n\n\t\t\tEnter username or email: ");
    scanf("%s", username);
    fflush(stdin);
    printf("\t\t\tEnter password: ");
    scanf(" %[^\n]s", password);
    while (head!=NULL)
    {
        if((!strcmp(head->username, username)) && (!strcmp(head->password, password))){
            currentState = loggedIn;
            strcpy(currentUser, username);
            printf("\n\t\t\tLogin successful.\n");
            gotoxy(24, 20);
            system("PAUSE");
            return;
        }

        else if((!strcmp(head->username, username)) && (strcmp(head->password, password))){
            printf("\n\t\t\tWrong password\n");
            return;
        }
        head=head->next;
    }
    printf("\n\t\t\tUser not found\n");
}

void bookTicket(node *head){
    int flag = 0;
    int placeIndex;
    node *temp = head;
    char place[100];
    while (temp!=NULL)
    {
        if(!strcmp(temp->username, currentUser)){
            break;
        }
        temp=temp->next;
    }
    if(temp==NULL)
        return;
    if(temp->booked!=0){
        printf("\t\t\tYou should cancel the previous ticket\n");
        return;
    }
    showBrochure();
    readDestinationsFromFile();

    float priceList[]={50000.0, 60000.0, 100000.0, 25000.0, 10000.0, 15000.0, 30000.0, 35000.0, 120000.0, 200000.0};
    fflush(stdin);
    printf("\t\t\tEnter the place name: (eg: AA, BB): ");
    scanf(" %[^\n]s", place);
    char choice;
    fflush(stdin);
    printf("\n\t\t\tConfirm Booking? [1] for yes, [2] for no: ");
    scanf("%c", &choice);
    float price;
    if(choice!='1')
        return;

    if(!strcmp(place, "AA"))  {
            price=priceList[0];
            placeIndex = 0;
    }
    else if(!strcmp(place, "BB")) {
        price=priceList[1];
        placeIndex = 1;
    }
    else if(!strcmp(place, "CC")) {
        price=priceList[2];
        placeIndex = 2;
    }
    else if(!strcmp(place, "DD"))  {
            price=priceList[3];
            placeIndex = 3;
    }
    else if(!strcmp(place, "EE"))  {
            price=priceList[4];
            placeIndex = 4;
    }
    else if(!strcmp(place, "FF")) {
            price=priceList[5];
            placeIndex = 5;
    }
    else if(!strcmp(place, "GG"))  {
            price=priceList[6];
            placeIndex = 6;
    }
    else if(!strcmp(place, "HH"))  {
            price=priceList[7];
            placeIndex = 7;
    }
    else if(!strcmp(place, "II"))  {
            price=priceList[8];
            placeIndex = 8;
    }
    else if(!strcmp(place, "JJ"))  {
            price=priceList[9];
            placeIndex = 9;
    }

    else {
         printf("\t\t\tInvalid code!\n");
         return;
    }
    printf("\t\t\tHow many ticket do you want to buy? ");
    scanf("%d", &temp->numberOfTicker);

    if(temp->numberOfTicker==0)
        return;

    if(temp->numberOfTicker>initial[placeIndex]){
        printf("\t\t\tInsufficient tickets available for %s\n", place);
        return;
    }

    initial[placeIndex] -= temp->numberOfTicker;
    temp->booked=1;
    updateArrayToFile(placeIndex, initial[placeIndex]);

    strcpy(temp->place, place);
    temp->price=price;
    writeToFile(head);
    printf("\n\t\t\tBooking done.\n");
    system("PAUSE");
}


void printTicket(node *head){
    while (head!=NULL)
    {
        if(!strcmp(head->username, currentUser)){
            break;
        }
        head=head->next;
    }
    if(!strcmp(head->place, "\0") || head->price==0.0 || head->numberOfTicker==0){
        printf("\t\t\tYou haven't booked a ticket yet.\n");
        return;
    }
    float amount = 0.0;
    amount = (head->price) * (head->numberOfTicker);
    FILE *fp;
    char fileName[100];
    strcpy(fileName, head->username);
    strcat(fileName, "_ticket.txt");
    fp = fopen(fileName, "w");
    if(fp==NULL){
        printf("\t\t\tNo ticket\n");
        return;
    }
    if(fgetc(fp)==EOF){
        fprintf(fp,"\t\tTourist ticket\n\t\t------------\n\n");
    }
    fprintf(fp," Username is %s.\n Tour destination is %s.\n Ticket cost is %f.\n Number of ticket is %d.\n Total cost is %f.\n", head->username, head->place, head->price, head->numberOfTicker, amount);
    fclose(fp);
}

void cancelTicket(node *head) {
   
    node *temp = head;
    while (temp != NULL) {
        if (!strcmp(temp->username, currentUser)) {
            break;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\t\t\tUser not found.\n");
        return;
    }

    if (temp->booked == 0) {
        printf("\t\t\tYou haven't booked any ticket yet.\n");
    } else {
        int placeIndex = -1;

     
        if (!strcmp(temp->place, "AA")) {
            placeIndex = 0;
        } else if (!strcmp(temp->place, "BB")) {
            placeIndex = 1;
        } else if (!strcmp(temp->place, "CC")) {
            placeIndex = 2;
        } else if (!strcmp(temp->place, "DD")) {
            placeIndex = 3;
        } else if (!strcmp(temp->place, "EE")) {
            placeIndex = 4;
        } else if (!strcmp(temp->place, "FF")) {
            placeIndex = 5;
        } else if (!strcmp(temp->place, "GG")) {
            placeIndex = 6;
        } else if (!strcmp(temp->place, "HH")) {
            placeIndex = 7;
        } else if (!strcmp(temp->place, "II")) {
            placeIndex = 8;
        } else if (!strcmp(temp->place, "JJ")) {
            placeIndex = 9;
        }

        if (placeIndex == -1) {
            printf("\t\t\tInvalid destination.\n");
            return;
        }
      
        int canceledTickets = temp->numberOfTicker;
        initial[placeIndex] += canceledTickets;
        updateCancelledTicketsToFile(placeIndex, canceledTickets);

       
        temp->booked = 0;
        strcpy(temp->place, "N/A");
        temp->price = 0.0;
        temp->numberOfTicker = 0;

        writeToFile(head);
        printf("\t\t\tYour ticket has been successfully cancelled.\n");
    }
}



void changePassword(node *head) {
    node *temp = head;
    char currentPassword[100];
    char newPassword[100];
    char newPasswordConfirm[100];

    system("CLS");
    printf("     _____   _                                                                                                  _ \n");
    printf("    / ____| | |                                                                                                | |\n");
    printf("   | |      | |__     __ _   _ __     __ _    ___     _ __     __ _   ___   ___  __      __   ___    _ __    __| |\n");
    printf("   | |      | '_ \\   / _` | | '_ \\   / _` |  / _ \\   | '_ \\   / _` | / __| / __| \\ \\ /\\ / /  / _ \\  | '__|  / _` |\n");
    printf("   | |____  | | | | | (_| | | | | | | (_| | |  __/   | |_) | | (_| | \\__ \\ \\__ \\  \\ V  V /  | (_) | | |    | (_| |\n");
    printf("    \\_____| |_| |_|  \\__,_| |_| |_|  \\__, |  \\___|   | .__/   \\__,_| |___/ |___/   \\_/\\_/    \\___/  |_|     \\__,_|\n");
    printf("                                      __/ |          | |                                                           \n");
    printf("                                     |___/           |_|                                                           \n");
    fflush(stdin);
    printf("\n\n\t\t\t\tEnter your current password to continue: ");
    scanf("%s", currentPassword);

    while (temp != NULL) {
        if (!strcmp(temp->username, currentUser))
            break;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\t\t\t\tUser not found. Unable to change the password.\n");
        return;
    }

    if (!strcmp(currentPassword, temp->password)) {
        printf("\t\t\t\tEnter your new password: ");
        scanf(" %s", newPassword);

        printf("\t\t\t\tConfirm your new password: ");
        scanf(" %s", newPasswordConfirm);

        if (strcmp(newPassword, newPasswordConfirm) == 0) {
            strcpy(temp->password, newPassword);
            writeToFile(head);
            printf("\t\t\t\tPassword changed successfully.\n");
        } else {
            printf("\t\t\t\tPasswords do not match. Password change failed.\n");
        }
    } else {
        printf("\t\t\t\tIncorrect current password. Password change failed.\n");
    }
}


void changeUsername(node *head){
    system("CLS");
    printf("\n\n");
    printf("   _____   _                                        _    _                                                        \n");
    printf("  / ____| | |                                      | |  | |                                                       \n");
    printf(" | |      | |__     __ _   _ __     __ _    ___    | |  | |  ___    ___   _ __   _ __     __ _   _ __ ___     ___ \n");
    printf(" | |      | '_ \\   / _` | | '_ \\   / _` |  / _ \\   | |  | | / __|  / _ \\ | '__| | '_ \\   / _` | | '_ ` _ \\   / _ \\\n");
    printf(" | |____  | | | | | (_| | | | | | | (_| | |  __/   | |__| | \\__ \\ |  __/ | |    | | | | | (_| | | | | | | | |  __/\n");
    printf("  \\_____| |_| |_|  \\__,_| |_| |_|  \\__, |  \\___|    \\____/  |___/  \\___| |_|    |_| |_|  \\__,_| |_| |_| |_|  \\___|\n");
    printf("                                    __/ |                                                                         \n");
    printf("                                   |___/                                                                          \n");
    printf("\n\n");
    node *temp = head;
    char currentPassword[100];
    char newUsername[100];
    printf("\t\t\tEnter your current password to continue: ");
    scanf(" %[^\n]s",currentPassword);
    while (temp!=NULL)
    {
         if(!(strcmp(temp->username, currentUser)) && !(strcmp(temp->password, currentPassword))){
            break;
         }
         temp=temp->next;
    }
    if (temp == NULL) {
       printf("\t\t\tAuthentication failed. Unable to change username.\n");
       return;
    }
    if(!(strcmp(currentPassword, temp->password))){
        printf("\t\t\tEnter new username: ");
        scanf("%s", &newUsername);

        node *check = head;
        while (check!=NULL)
        {
            if(!(strcmp(newUsername, check->username))){
                printf("\t\t\tUsername already in use. Please choose a different username.\n");
                return;
            }
            check=check->next;
        }
        strcpy(temp->username, newUsername);
        writeToFile(head);
        printf("\t\t\tUsername changed successfully\n\n");

    }


}


node* deleteUser(node* head) {
    system("cls");
    printf("\n\n");
    printf("\t\t\t  _____           _          _              _    _                     \n");
    printf("\t\t\t |  __ \\         | |        | |            | |  | |                    \n");
    printf("\t\t\t | |  | |   ___  | |   ___  | |_    ___    | |  | |  ___    ___   _ __ \n");
    printf("\t\t\t | |  | |  / _ \\ | |  / _ \\ | __|  / _ \\   | |  | | / __|  / _ \\ | '__|\n");
    printf("\t\t\t | |__| | |  __/ | | |  __/ | |_  |  __/   | |__| | \\__ \\ |  __/ | |   \n");
    printf("\t\t\t |_____/   \\___| |_|  \\___|  \\__|  \\___|    \\____/  |___/  \\___| |_|   \n");
    printf("\n\n");
    char username[100];
    char password[100];

    fflush(stdin);
    printf("\n\n");
    printf("\t\t\tEnter your username or email: ");
    scanf("%s", username);

    fflush(stdin);
    printf("\t\t\tEnter your password: ");
    scanf(" %[^\n]s", password);

    node* temp = head;
    node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            char confirm;
            printf("\n\t\t\tAre you sure you want to delete your account? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                char fileName[100];
                strcpy(fileName, temp->username);
                strcat(fileName, "_ticket.txt");
                remove(fileName);

                if (prev != NULL) {
                    prev->next = temp->next;
                } else {
                    head = temp->next;
                }

                free(temp);

                printf("\n\t\t\tAccount deleted successfully.\n");
                writeToFile(head);
                return head;
            } else {
                printf("\n\t\t\tAccount deletion cancelled.\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }

    printf("\n\t\t\tUser not found or incorrect password. Account deletion failed.\n");
    return head;
}




void logOutUser(){
    if(currentState==menu || strcmp(currentUser, "\0")==0){
        printf("\t\t\tYou must login first\n");
        return;
    }
    strcpy(currentUser, "\0");
    currentState=menu;
    printf("\t\t\tYou have successfully logged out\n");
}

void exitTheProgramme(){
    printf("\t\t\tDeveloped by Team Bhromon\n");
    char exitprog;
    fflush(stdin);
    scanf("%c", &exitprog);
}








