#include <stdio.h>
#include <stdlib.h>

#define TOTAL_RECORDS 100

// Structure definition
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

// Function prototypes
unsigned int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);
void initializeFile(FILE *fPtr);

int main()
{
    FILE *cfPtr;
    unsigned int choice;

    // Open file in read/write binary mode
    cfPtr = fopen("credit.dat", "rb+");

    // If file doesn't exist, create it
    if (cfPtr == NULL)
    {
        cfPtr = fopen("credit.dat", "wb+");

        if (cfPtr == NULL)
        {
            printf("Unable to create file.\n");
            return 1;
        }

        initializeFile(cfPtr);
    }

    // Menu loop
    while ((choice = enterChoice()) != 5)
    {
        switch (choice)
        {
        case 1:
            textFile(cfPtr);
            break;

        case 2:
            updateRecord(cfPtr);
            break;

        case 3:
            newRecord(cfPtr);
            break;

        case 4:
            deleteRecord(cfPtr);
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    fclose(cfPtr);

    printf("\nProgram terminated successfully.\n");

    return 0;
}

// Initialize file with 100 blank records
void initializeFile(FILE *fPtr)
{
    struct clientData blankClient = {0, "", "", 0.0};

    rewind(fPtr);

    for (int i = 0; i < TOTAL_RECORDS; i++)
    {
        fwrite(&blankClient, sizeof(struct clientData), 1, fPtr);
    }
}

// Menu
unsigned int enterChoice(void)
{
    unsigned int menuChoice;

    printf("\n===== BANK ACCOUNT MENU =====\n");
    printf("1 - Store formatted text file\n");
    printf("2 - Update an account\n");
    printf("3 - Add a new account\n");
    printf("4 - Delete an account\n");
    printf("5 - Exit\n");
    printf("Enter your choice: ");

    scanf("%u", &menuChoice);

    return menuChoice;
}

// Create text file
void textFile(FILE *readPtr)
{
    FILE *writePtr;
    struct clientData client;

    writePtr = fopen("accounts.txt", "w");

    if (writePtr == NULL)
    {
        printf("Unable to create text file.\n");
        return;
    }

    rewind(readPtr);

    fprintf(writePtr, "%-6s %-15s %-10s %-10s\n",
            "Acct", "Last Name", "First Name", "Balance");

    while (fread(&client, sizeof(struct clientData), 1, readPtr) == 1)
    {
        if (client.acctNum != 0)
        {
            fprintf(writePtr, "%-6u %-15s %-10s %.2f\n",
                    client.acctNum,
                    client.lastName,
                    client.firstName,
                    client.balance);
        }
    }

    fclose(writePtr);

    printf("accounts.txt created successfully.\n");
}

// Update existing record
void updateRecord(FILE *fPtr)
{
    unsigned int account;
    double transaction;
    struct clientData client;

    printf("Enter account number (1-100): ");
    scanf("%u", &account);

    if (account < 1 || account > 100)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (account - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
        return;
    }

    printf("\nCurrent Details:\n");
    printf("%u %s %s %.2f\n",
           client.acctNum,
           client.lastName,
           client.firstName,
           client.balance);

    printf("Enter transaction amount (+ credit / - debit): ");
    scanf("%lf", &transaction);

    client.balance += transaction;

    fseek(fPtr,
          -((long)sizeof(struct clientData)),
          SEEK_CUR);

    fwrite(&client, sizeof(struct clientData), 1, fPtr);

    printf("Account updated successfully.\n");
}

// Add new record
void newRecord(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};
    unsigned int accountNum;

    printf("Enter new account number (1-100): ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > 100)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists.\n");
        return;
    }

    printf("Enter Last Name First Name Balance:\n");

    scanf("%14s %9s %lf",
          client.lastName,
          client.firstName,
          &client.balance);

    client.acctNum = accountNum;

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&client, sizeof(struct clientData), 1, fPtr);

    printf("Account added successfully.\n");
}

// Delete record
void deleteRecord(FILE *fPtr)
{
    struct clientData client;
    struct clientData blankClient = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter account number to delete (1-100): ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > 100)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fwrite(&blankClient,
           sizeof(struct clientData),
           1,
           fPtr);

    printf("Account deleted successfully.\n");
} 