// CCustomerBilling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

void addAccount();
bool searchAccount(char[]);
void deleteCust(char[]);
void editCust(char[], int, char[]);

struct Customer {
    char name[30];
    char address[50];
    int phoneNum;
    int paid;
    int due;
    char payDate[15];
};

int main()
{
    int choice;
    bool out = false;
    for (;;) {
        printf("Customer Billing Support\n");
        printf("1. Add Account\n2. Search for Account\n3. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1: addAccount();
            break;
        case 2:
            char searchName[50];
            printf("Search by Customer Name\n");
            scanf("%s", searchName);
            if (searchAccount(searchName) == false) {
                break;
            }

            int c;
            int a;
            char str[5];

            printf("1. Edit\n2. Delete\n3. Exit\n");
            scanf("%d", &c);
            switch (c) {
                case 1: printf("Choose an option\n");
                    printf("1. Change Name\n2. Change Sddress\n3. Change Phone Number\n");
                    printf("4. Change Amount Paid\n5. Change Amount Due\n6. Change Due Date\n");
                    scanf("%d", &a);
                    printf("Enter a new value\n");
                    scanf("%s", str);
                    editCust(searchName, a, str);
                    break;
                case 2: deleteCust(searchName);
                    break;
            }
            break;
        case 3: out = true;
            break;
        }
        if (out == true) {
            break;
        }
    }
}

void display(Customer cust) {
    printf("Customer: %s\n", cust.name);
    printf("Address: %s\n", cust.address);
    printf("Phone number: %d\n", cust.phoneNum);
    printf("Amount paid: $%d\n", cust.paid);
    printf("Amount due: $%d\n", cust.due);
    printf("Due by %s\n", cust.payDate);
}

void addAccount() {
    int choice = 2;
    FILE* fp;

    Customer cust;

    do {
        printf("Enter customer name\n");
        scanf("%s", cust.name);
        printf("Enter address\n");
        char* str = (char*)malloc(MAX);
        //gets_s(str, 100);
        //gets_s(str, 100);
        fgets(cust.address, MAX, stdin);
        fgets(cust.address, MAX, stdin);
        cust.address[strlen(cust.address) - 1] = '\0';
        //printf("%s", cust.address);
        printf("Enter customer phone number\n");
        scanf("%d", &cust.phoneNum);
        printf("Enter amount paid\n");
        scanf("%d", &cust.paid);
        printf("Enter amount due\n");
        scanf("%d", &cust.due);
        printf("Enter payment due date (MM/DD/YR)\n");
        scanf("%s", cust.payDate);
        printf("\n");

        display(cust);
        printf("\nIs this customer data correct? 1. Yes 2. No\n");
        scanf("%d", &choice);
    } while (choice == 2);

    char str[] = "END";

    fp = fopen("C:\\Temp\\tmp\\accounts.txt", "a");
    fprintf(fp, "%s\n", cust.name);
    fprintf(fp, "%s\n", cust.address);
    fprintf(fp, "%d\n", cust.phoneNum);
    fprintf(fp, "%d\n", cust.paid);
    fprintf(fp, "%d\n", cust.due);
    fprintf(fp, "%s\n", cust.payDate);
    fprintf(fp, "%s\n", str);
    fclose(fp);
}

bool searchAccount(char name[]) {   //Returns true if customer found, false if not
    FILE* fp;
    fp = fopen("C:\\Temp\\tmp\\accounts.txt", "r");
    char line[256];
    int count = 0;

    Customer cust;

    while (fgets(line, sizeof line, fp) != NULL) {
        line[strlen(line) - 1] = '\0';
        
        if (strcmp(line, "END") == 0 && count != 0) {
            printf("Customer found\n");
            break;
        }

        if (strcmp(name, line) == 0 || count != 0) {
            switch (count) {
            case 0: strcpy(cust.name, line);
                break;
            case 1: strcpy(cust.address, line);
                break;
            case 2: cust.phoneNum = atoi(line);
                break;
            case 3: cust.paid = atoi(line);
                break;
            case 4: cust.due = atoi(line);
                break;
            case 5: strcpy(cust.payDate, line);
                break;
            }
            count++;
        }
    }
    fclose(fp);
    if (count == 6) {
        display(cust);
        return true;
    }
    else {
        printf("Customer not found\n\n");
        return false;
    }
}

void deleteCust(char name[]) {
    FILE* fp;
    FILE* fp2;
    fp = fopen("C:\\Temp\\tmp\\accounts.txt", "r");
    char line[256];
    fp2 = fopen("C:\\Temp\\tmp\\temp.txt", "w+");
    int count = 0;

    while (fgets(line, sizeof line, fp) != NULL) {
        
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, name) == 0 || count != 0 && count < 8) {
            count++;
        }

        if (count == 0 || count > 7) {
            fputs(line, fp2);
            fputs("\n", fp2);
        }
    }
    
    printf("Customer deleted\n");

    fclose(fp);
    fclose(fp2);

    remove("C:\\Temp\\tmp\\accounts.txt");
    rename("C:\\Temp\\tmp\\temp.txt", "C:\\Temp\\tmp\\accounts.txt");
}

void editCust(char name[], int a, char change[]) {
    FILE* fp;
    FILE* fp2;
    fp = fopen("C:\\Temp\\tmp\\accounts.txt", "r");
    fp2 = fopen("C:\\Temp\\tmp\\temp.txt", "w");
    char line[256];
    int count = 0;
    bool counting = false;

    while (fgets(line, sizeof line, fp) != NULL) {
        line[strlen(line) - 1] = '\0';

        if (strcmp(line, name) == 0) {
            counting = true;
        }
        if (counting == true) {
            count++;
        }
        if (count == a) {
            fputs(change, fp2);
            fputs("\n", fp2);
        }
        else {
            fputs(line, fp2);
            fputs("\n", fp2);
        }
    }

    fclose(fp);
    fclose(fp2);

    remove("C:\\Temp\\tmp\\accounts.txt");
    rename("C:\\Temp\\tmp\\temp.txt", "C:\\Temp\\tmp\\accounts.txt");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
