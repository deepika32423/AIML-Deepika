# Bank Account Management System

A menu-driven banking application developed in C that demonstrates the use of structures, random-access binary files, and file handling operations for efficient account management.

---

# Overview

This project simulates a basic banking record system where account information is stored in a binary database file and managed through random-access file operations.

The application supports:

* Creating new accounts
* Updating account balances
* Deleting existing accounts
* Exporting records into a formatted text report

The modified version enhances the original implementation with improved file initialization, input validation, safer file processing, and better usability.

---

# Key Features

* Random-access binary file storage
* Structured account management
* Persistent data handling
* Formatted text file generation
* Input validation for account operations
* Automatic database initialization
* Safer file-reading implementation
* Menu-driven console interface

---

# Technical Concepts Used

* C Programming
* Structures
* Binary File Handling
* Random Access Files
* File Pointers
* `fseek()`, `fread()`, `fwrite()`
* Sequential and Direct File Access
* Console-based UI Design

---

# Project Structure

Bank-Account-System/
│
├── main.c
├── credit.dat
├── accounts.txt
└── README.md

---

# Functional Modules

## 1. Account Creation

Creates and stores a new customer record in the binary database.

### Input Fields

* Account Number
* Last Name
* First Name
* Balance

---

## 2. Account Update

Updates an existing account balance using:

* Credit transactions
* Debit transactions

Changes are written directly into the random-access file.

---

## 3. Account Deletion

Deletes an account by replacing the record with a blank structure.

---

## 4. Text Report Generation

Exports all valid account records into:

accounts.txt

Formatted for readability and printing.

---

# Enhancements Over Original Version

## Automatic File Initialization

### Original Behavior

The application terminated if:

credit.dat

did not exist.

### Modified Behavior

The application now:

* Automatically creates the database file
* Initializes 100 blank records
* Prevents undefined file behavior

---

## Added Initialization Function

void initializeFile(FILE *fPtr)
{
    struct clientData blankClient = {0, "", "", 0.0};

    for (int i = 0; i < TOTAL_RECORDS; i++)
    {
        fwrite(&blankClient,
               sizeof(struct clientData),
               1,
               fPtr);
    }
}

---

## Improved File Reading Logic

### Previous Approach

while (!feof(readPtr))


### Updated Approach

while (fread(&client,
             sizeof(struct clientData),
             1,
             readPtr) == 1)


### Benefit

Prevents duplicate reads and improves reliability.

---

## Input Validation Improvements

if (account < 1 || account > 100)
{
    printf("Invalid account number.\n");
    return;
}

### Benefits

* Prevents invalid memory access
* Improves application stability
* Enhances user safety

---

## Safer String Handling

scanf("%14s %9s %lf",
      client.lastName,
      client.firstName,
      &client.balance);

### Benefit

Reduces risk of buffer overflow.

---

# Compilation & Execution

Compile:

gcc main.c -o bank

Run:

./bank

---

## Windows (MinGW)

Compile:

gcc main.c -o bank.exe

Run:

bank.exe

---

# Sample Menu

===== BANK ACCOUNT MENU =====
1 - Store formatted text file
2 - Update an account
3 - Add a new account
4 - Delete an account
5 - Exit

---

# Example Workflow

1. Launch application
2. Initialize database file
3. Add customer accounts
4. Perform balance updates
5. Export account report
6. Exit program

---

# Future Improvements

Potential enhancements include:

* Authentication system
* Search functionality
* Transaction history
* Encryption support
* GUI implementation
* SQL database integration

---

# Learning Outcomes

This project demonstrates practical understanding of:

* Persistent data storage
* Binary file manipulation
* Random-access record management
* Structured programming in C
* Defensive programming techniques
* File-system-based database simulation

---

# Conclusion

The modified implementation improves the original banking application by introducing:

* Better reliability
* Safer file operations
* Improved user interaction
* Cleaner data management practices

while maintaining the original objective of demonstrating random-access file handling in C.

---
