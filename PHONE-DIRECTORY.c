#include <stdio.h>

#include <stdlib.h>

#include <string.h>

struct contact {
    char first_name[15];
    char last_name[15];
    char mobile_no[15];
};
typedef struct contact contact;
// A function to add contact into the directory
void add_contact() {
    system("cls");
    FILE * fptr;
    contact cn;
    fptr = fopen("PhoneBook", "a");

    printf("\n<Fill details>\n");

    printf("Enter First Name : ");
    scanf("%s", & cn.first_name);

    printf("Enter last Name : ");
    scanf("%s", & cn.last_name);

    printf("\nEnter Mobile Number : ");
    scanf("%s", & cn.mobile_no);

    fwrite( & cn, sizeof(contact), 1, fptr);

    fclose(fptr);

    printf("Enter any key to continue.");
    getch();
    system("cls");
}
// A function to print the no.of contacts in the directory
int directory_info() {
    FILE * fptr;

    fptr = fopen("PhoneBook", "r");
    fseek(fptr, 0, SEEK_END);

    return ftell(fptr) / sizeof(contact);
}

//A function to display the contacts
void display() {
    system("cls");
    FILE * fptr;
    contact cn;
    int mode, count = 1, i, n;
    fptr = fopen("PhoneBook", "r");

    n = directory_info();
    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s|\n", "Sno", "First Name", "Last Name", "Contact Number");
    printf("---------------------------------------------------------------------");

    while (fread( & cn, sizeof(contact), 1, fptr)) {
        printf("\n|%-3d| %-15s%-15s%-20s|", count++, cn.first_name, cn.last_name, cn.mobile_no);
    }

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);

    printf("\n\nEnter any key to continue : ");
    getch();
    system("cls");
}

// A function to modify a cotact
void modify_contact() {
    system("cls");
    FILE * fptr, * fptr1;
    contact cn;
    char first_name[15];
    char last_name[15];
    char modify;
    int found = 0;

    fptr = fopen("PhoneBook", "r");
    fptr1 = fopen("helper", "w");

    printf("Enter the name of Contact to modify:\n");
    printf("Enter First name: ");
    scanf("%s", & first_name);
    printf("Enter Last name: ");
    scanf("%s", & last_name);
    fflush(stdin);

    while (fread( & cn, sizeof(contact), 1, fptr)) {
        if (strcmp(strlwr(cn.first_name), strlwr(first_name)) == 0 && strcmp(strlwr(cn.last_name), strlwr(last_name)) == 0) {
            found = 1;
            printf("\nModify First Name?<y/n> : ");
            scanf("%c", & modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y') {
                printf("Enter New First name : ");
                scanf("%s", & cn.first_name);
                fflush(stdin);
            }
            printf("\nModify Last Name?<y/n> : ");
            scanf("%c", & modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y') {
                printf("Enter New Last name : ");
                scanf("%s", & cn.last_name);
                fflush(stdin);
            }
            printf("\nModify Mobile Number? <y/n> : ");
            scanf("%c", & modify);
            fflush(stdin);
            if (modify == 'y' || modify == 'Y') {
                printf("Enter New Mobile Number : ");
                scanf("%s", & cn.mobile_no);
                fflush(stdin);
            }
        }
        fwrite( & cn, sizeof(contact), 1, fptr1);
    }
    fclose(fptr);
    fclose(fptr1);

    if (found == 1) {
        fptr1 = fopen("helper", "r");
        fptr = fopen("PhoneBook", "w");

        while (fread( & cn, sizeof(contact), 1, fptr1))
            fwrite( & cn, sizeof(contact), 1, fptr);

        printf("\nContact Modified Successfully\n");
    } else
        printf("Contact not found");

    fclose(fptr);
    fclose(fptr1);

    printf("\n\nEnter any key to continue : ");
    getch();
    system("cls");
}
//A function to search for the info of a specified contact
void search_contact() {
    system("cls");
    FILE * fp;
    contact cn;
    int c, flag = 0;
    fp = fopen("PhoneBook", "r");
    if (fp == NULL) {
        printf("\nError in opening\n");
        exit(1);
    }
    printf("\n------------------------------------\n");
    printf("***SEARCH MENU***\n");
    printf("----------------------------------------\n");
    printf("1. Search by name\n2. Search by Phone number\n");
    printf("Enter your choice : ");
    scanf("%d", & c);
    fflush(stdin);
    if (c == 1) {
        char first_name[30], last_name[30];
        printf("Enter the name to be searched for:\n");
        printf("Enter first name : ");
        scanf("%s", & first_name);
        printf("Enter last name : ");
        scanf("%s", & last_name);
        fflush(stdin);
        while (fread( & cn, sizeof(cn), 1, fp) == 1) {

            if (strcmp(strlwr(cn.first_name), strlwr(first_name)) == 0 && strcmp(strlwr(cn.last_name), strlwr(last_name)) == 0) {
                flag = 1;
                printf("\nDetail information about %s\n", first_name);
                printf("---------------------------------------------------------------------\n");
                printf("\n|%-15s%-15s%-20s%-12s|\n", "First Name", "Last Name", "Contact Number", "Tag");
                printf("---------------------------------------------------------------------");
                printf("\n|%-15s%-15s%-20s|\n", cn.first_name, cn.last_name, cn.mobile_no);
                break;
            }
        }
        if (flag == 0) {
            printf("\nSearch not found\n");
            fclose(fp);
        }
    } else if (c == 2) {
        char phone[10];
        printf("Enter phone number to search: ");
        scanf("%s", & phone);
        while (fread( & cn, sizeof(cn), 1, fp) == 1) {
            if (strcmp(phone, cn.mobile_no) == 0) {
                flag = 1;
                printf("\n\nDetail information about %s", phone);
                printf("---------------------------------------------------------------------\n");
                printf("\n|%-15s%-15s%-20s%-12s|\n", "First Name", "Last Name", "Contact Number", "Tag");
                printf("---------------------------------------------------------------------");
                printf("\n|%-15s%-15s%-20s|\n", cn.first_name, cn.last_name, cn.mobile_no);
                break;
            }
        }
        if (flag == 0) {
            printf("\nSearch not found\n");
            fclose(fp);
        }
    } else {
        printf("Wrong Choice!!");
        fclose(fp);
    }
    printf("Enter any key to continue:");
    getch();
    system("cls");
}

//A function to delete a contact from the directory
void delete_contact() {
    contact cn;
    FILE * fptr, * fptr1;
    int flag;
    system("cls");
    fptr = fopen("PhoneBook", "r");
    if (fptr == NULL) {
        printf("CONTACT'S DATA NOT ADDED YET");
    } else {
        fptr1 = fopen("helper", "w+");
        if (fptr1 == NULL) printf("Error in opening the file");
        else {

            int choice;
            printf("\n----------------------------------------");
            printf("\n***DELETION MENU***\n");
            printf("----------------------------------------\n");
            printf("1.Deletion through mobile number\n2.Deletion through name\n");
            printf("Enter your choice: ");
            scanf("%d", & choice);
            if (choice == 1) {
                char mobile_no[25];
                printf("Enter CONTACT's mobile_no:");
                scanf("%s", & mobile_no);
                fflush(stdin);
                while (fread( & cn, sizeof(cn), 1, fptr) == 1) {
                    if (strcmp(mobile_no, cn.mobile_no) != 0) {
                        fwrite( & cn, sizeof(cn), 1, fptr1);
                    }
                    if (strcmp(mobile_no, cn.mobile_no) == 0) {
                        flag = 1;
                    }
                }
            } else if (choice == 2) {
                char first_name[25], last_name[25];
                printf("Enter CONTACT's first_name: ");
                scanf("%s", & first_name);
                printf("Enter CONTACT's last_name: ");
                scanf("%s", & last_name);
                fflush(stdin);
                while (fread( & cn, sizeof(cn), 1, fptr) == 1) {
                    if (strcmp(strlwr(cn.first_name), strlwr(first_name)) != 0 || strcmp(strlwr(cn.last_name), strlwr(last_name)) != 0) {
                        fwrite( & cn, sizeof(cn), 1, fptr1);
                    }
                    if (strcmp(strlwr(cn.first_name), strlwr(first_name)) == 0 && strcmp(strlwr(cn.last_name), strlwr(last_name)) == 0) {
                        flag = 1;
                    }
                }
            } else {
                printf("\nWrong choice!\nEnter any key to continue");
                getch();
                system("cls");
            }

            fclose(fptr);
            fclose(fptr1);
            if (flag != 1) {
                printf("NO CONTACT'S RECORD TO DELETE!\n");
            } else {
                fptr1 = fopen("helper", "r");
                fptr = fopen("PhoneBook", "w");
                while (fread( & cn, sizeof(contact), 1, fptr1))
                    fwrite( & cn, sizeof(contact), 1, fptr);
                printf("\nContact Deleted Successfully\n");

            }
            fclose(fptr1);
            fclose(fptr);
        }
    }
    printf("Enter any key:");
    getch();
    system("cls");
}

//Driver code
int main() {
    int operation = 1;

    while (operation) {
        printf("\n1 : Create Contact\n");
        printf("2 : Display Directory\n");
        printf("3 : Modify Contact\n");
        printf("4 : Search Contact\n");
        printf("5 : Delete Contact\n");
        printf("6 : Exit Program\n");
        printf("\nChoose Operation : ");
        scanf("%d", & operation);

        switch (operation) {
        case 1:
            add_contact();
            break;
        case 2:
            display();
            break;
        case 3:
            modify_contact();
            break;
        case 4:
            search_contact();
            break;
        case 5:
            delete_contact();
            break;
        case 6:
            exit(1);
            break;
        default:
            system("cls");
            printf("\nInvalid Operation !!");
            printf("\nEnter 1 to 6 only");
            printf("\n Enter any key to continue");
            getch();
            system("cls");
        }
    }

    return 0;
}
