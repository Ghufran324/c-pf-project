#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_ACCOUNTS 50
#define ID_LENGTH 5
#define PASSWORD_LENGTH 5
#define TRANSACTION_HISTORY_LENGTH 100

typedef struct {
    char id[ID_LENGTH];
    char password[PASSWORD_LENGTH];
    float balance;
    char transactionHistory[TRANSACTION_HISTORY_LENGTH][100];
    int transactionCount;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void loadAccounts();
void saveAccounts();
void adminPortal();
void atmPortal();
void createAccount();
void deleteAccount();
void depositCash();
void viewAllAccounts();
void changeAccountPassword();
void viewAllTransactions();
void checkBalance(int index);
void withdrawCash(int index);
void changeUserPassword(int index);
void displayMainMenu();
void maskPassword(char *password);

int main() {
    loadAccounts();
    displayMainMenu();
    return 0;
}

void displayMainMenu() {
    int choice;
    do {
        printf("\n\t\t\t============================\n");
        printf("\n\t\t\t--- Welcome To VistaBank ---\n");
        printf("\n\t\t\t============================\n");
        printf("\t\t\t 1. Admin Portal\n");
        printf("\t\t\t 2. ATM Portal\n");
        printf("\t\t\t 3. Exit\n\n");
        printf("\t\t\t Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminPortal(); break;
            case 2: atmPortal(); break;
            case 3: saveAccounts(); printf("\n\t\t\tExiting...\n"); break;
            default: printf("\n\t\t\tInvalid option. Please try again.\n");
        }
    } while (choice != 3);
}

void adminPortal() {
    char adminID[ID_LENGTH], adminPassword[PASSWORD_LENGTH];
    while (1) {
    printf("\n\t\t\tEnter Admin ID (4 digits): ");
    scanf("%s", adminID);  // Admin ID ke liye input lena

    // Check if Admin ID contains only digits
    int valid = 1;
    for (int i = 0; i < strlen(adminID); i++) {
        if (adminID[i] < '0' || adminID[i] > '9') {
            valid = 0;
            printf("\n\t\t\tError: Admin ID can only contain digits (0-9).\n");  // Error message for alphabetic characters
            break;
        }
    }

    // Check if Admin ID length is exactly 4 digits
    if (valid && strlen(adminID) != 4) {
        printf("\n\t\t\tError: Admin ID must be exactly 4 digits.\n");  // Error message for wrong length
    }

    // If both conditions are satisfied, break out of the loop
    if (valid && strlen(adminID) == 4) {
        break;  // Valid Admin ID entered, exit loop
    }
}
    printf("\n\t\t\tEnter Admin Password: ");
    maskPassword(adminPassword);

    if ((strcmp(adminID, "1111") == 0 && strcmp(adminPassword, "1111") == 0) ||
        (strcmp(adminID, "2222") == 0 && strcmp(adminPassword, "2222") == 0)) {
        int choice;
        do {
            printf("\n\t\t\t=================================\n");
            printf("\n\t\t\t--- Welcome To Admin Portal ---\n");
            printf("\n\t\t\t=================================\n");
            printf("\t\t\t 1. Create Account\n");
            printf("\t\t\t 2. Delete Account\n");
            printf("\t\t\t 3. Deposit Cash\n");
            printf("\t\t\t 4. View All Accounts\n");
            printf("\t\t\t 5. Change Account Password\n");
            printf("\t\t\t 6. View All Transactions\n");
            printf("\t\t\t 7. Back\n\n");
            printf("\t\t\tSelect an option: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: createAccount();
                break;
                case 2: deleteAccount();
                break;
                case 3: depositCash();
                break;
                case 4: viewAllAccounts();
                break;
                case 5: changeAccountPassword();
                break;
                case 6: viewAllTransactions();
                break;
                case 7:
                break;
                default: printf("\n\t\t\tInvalid option. Please try again.\n");
            }
        } while (choice != 7);
    } else {
        printf("\n\t\t\tInvalid Admin Credentials.\n");
    }
}

void atmPortal() {
    char userID[ID_LENGTH], userPassword[PASSWORD_LENGTH];

    while (1) {
        printf("\n\t\t\tEnter User ID: ");
        scanf("%s", userID);

        // Check if ID contains only digits
        int valid = 1;
        for (int i = 0; i < strlen(userID); i++) {
            if (userID[i] < '0' || userID[i] > '9') {
                valid = 0;
                printf("\n\t\t\tError: Account ID can only contain digits (0-9).\n");
                break;
            }
        }

        // Check if ID length is exactly 4 digits
        if (valid && strlen(userID) != 4) {
            printf("\n\t\t\tError: Account ID must be exactly 4 digits.\n");
        }

        // If both conditions are satisfied, break out of the loop
        if (valid && strlen(userID) == 4) {
            break;  // Valid ID entered, exit loop
        }
    }

    printf("\n\t\t\tEnter User Password: ");
    maskPassword(userPassword);

    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        // Compare IDs and Passwords
        if (strncmp(accounts[i].id, userID, ID_LENGTH) == 0 && strncmp(accounts[i].password, userPassword, PASSWORD_LENGTH) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        int choice;
        do {
            printf("\n\t\t\t=====================================\n\n");
            printf("\n\t\t\t--- Welcome to VistaBank ATM ---\n\n");
            printf("\t\t\t=====================================\n\n");
            printf("\t\t\t 1. Check Balance\n");
            printf("\t\t\t 2. Withdraw Cash\n");
            printf("\t\t\t 3. Change Password\n");
            printf("\t\t\t 4. Back\n\n");
            printf("\t\t\t Select an option: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: checkBalance(index); break;
                case 2: withdrawCash(index); break;
                case 3: changeUserPassword(index); break;
                case 4: break;
                default: printf("\n\t\t\tInvalid option. Please try again.\n");
            }
        } while (choice != 4);
    } else {
        printf("\n\t\t\tInvalid User Credentials.\n");
    }
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("\n\t\t\tMaximum account limit reached.\n");
        return;
    }

    char id[ID_LENGTH], password[PASSWORD_LENGTH];
    while (1) {
    printf("\n\t\t\tEnter Account ID To Create Account : ");
    scanf("%s", id);

    // Check if ID contains only digits
    int valid = 1;
    for (int i = 0; i < strlen(id); i++) {
        if (id[i] < '0' || id[i] > '9') {
            valid = 0;
            printf("\n\t\t\tError: Account ID can only contain digits (0-9).\n");  // Error message for alphabetic characters
            break;
        }
    }

    // Check if ID length is exactly 4 digits
    if (valid && strlen(id) != 4) {
        printf("\n\t\t\tError: Account ID must be exactly 4 digits.\n");  // Error message for wrong length
    }

    // If both conditions are satisfied, break out of the loop
    if (valid && strlen(id) == 4) {
        break;  // Valid ID entered, exit loop
    }
}

    // Check if ID length is exactly 4 digits
    if (strlen(id) != 4) {
        printf("\t\t\tError: Account ID must be exactly 4 digits.\n");
        return;
    }

    printf("\t\t\tEnter new Password (4 digits): ");
    maskPassword(password);


    // Check for duplicate ID
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].id, id) == 0) {
            printf("\n\t\t\tError: Account ID already exists. Please choose a different ID.\n");
            return;
        }
    }

    // Create account
    strcpy(accounts[accountCount].id, id);
    strcpy(accounts[accountCount].password, password);
    accounts[accountCount].balance = 0;
    accounts[accountCount].transactionCount = 0;
    accountCount++;
    printf("\n\n\t\t\tAccount created successfully.\n");
}

void deleteAccount() {
    char id[ID_LENGTH];
   while (1) {
    printf("\n\t\t\tEnter Account ID to delete: ");
    scanf("%s", id);

    // Check if ID contains only digits
    int valid = 1;
    for (int i = 0; i < strlen(id); i++) {
        if (id[i] < '0' || id[i] > '9') {
            valid = 0;
            printf("\n\n\t\t\tError: Account ID can only contain digits (0-9).\n");  // Error message for alphabetic characters
            break;
        }
    }

    // Check if ID length is exactly 4 digits
    if (valid && strlen(id) != 4) {
        printf("\t\t\tError: Account ID must be exactly 4 digits.\n");  // Error message for wrong length
    }

    // If both conditions are satisfied, break out of the loop
    if (valid && strlen(id) == 4) {
        break;  // Valid ID entered, exit loop
    }
}

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].id, id) == 0) {
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            printf("\t\t\tAccount deleted successfully.\n");
            return;
        }
    }
    printf("\t\t\tAccount ID not found.\n");
}

void depositCash() {
    char id[ID_LENGTH];
    float amount;
    while (1) {
    printf("\t\t\tEnter Account ID to deposit cash: ");
    scanf("%s", id);

    // Check if ID contains only digits
    int valid = 1;
    for (int i = 0; i < strlen(id); i++) {
        if (id[i] < '0' || id[i] > '9') {
            valid = 0;
            printf("\n\t\t\tError: Account ID can only contain digits (0-9).\n");  // Error message for alphabetic characters
            break;
        }
    }

    // Check if ID length is exactly 4 digits
    if (valid && strlen(id) != 4) {
        printf("\n\t\t\tError: Account ID must be exactly 4 digits.\n");  // Error message for wrong length
    }

    // If both conditions are satisfied, break out of the loop
    if (valid && strlen(id) == 4) {
        break;  // Valid ID entered, exit loop
    }
}
    printf("\n\t\t\tEnter amount to deposit: pkr");
    scanf("%f", &amount);

    if (amount < 0) {
            printf("\n\n\t\t\tEnter Positive Numbers only:\n");
            return;
    }else{
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].id, id) == 0) {
            accounts[i].balance += amount;
            sprintf(accounts[i].transactionHistory[accounts[i].transactionCount++], "Deposit: %.2fpkr", amount);
            printf("\n\t\t\t %.2fpkr. deposited successfully.\n", amount);
            return;
        }
    }
    }
    printf("\t\t\tAccount ID not found.\n");
}

void viewAllAccounts() {
    printf("\n\t\t\t========================\n");
    printf("\n\t\t\t--- All Accounts ---\n");
    printf("\n\t\t\t========================\n");
    for (int i = 0; i < accountCount; i++) {
        printf("\t\t\tID: %s, Password: %s, Balance: %.2fpkr\n", accounts[i].id, accounts[i].password, accounts[i].balance);
    }
}

void changeAccountPassword() {
    char id[ID_LENGTH], newPassword[PASSWORD_LENGTH];
    while (1) {
    printf("\n\t\t\tEnter Account ID to change password: ");
    scanf("%s", id);

    // Check if ID contains only digits
    int valid = 1;
    for (int i = 0; i < strlen(id); i++) {
        if (id[i] < '0' || id[i] > '9') {
            valid = 0;
            printf("\n\t\t\tError: Account ID can only contain digits (0-9).\n");  // Error message for alphabetic characters
            break;
        }
    }

    // Check if ID length is exactly 4 digits
    if (valid && strlen(id) != 4) {
        printf("\t\t\tError: Account ID must be exactly 4 digits.\n");  // Error message for wrong length
    }

    // If both conditions are satisfied, break out of the loop
    if (valid && strlen(id) == 4) {
        break;  // Valid ID entered, exit loop
    }
}
    printf("\t\t\tEnter new Password (4 digits): ");
    maskPassword(newPassword);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].id, id) == 0) {
            strcpy(accounts[i].password, newPassword);
            printf("\n\t\t\tPassword changed successfully.\n");
            return;
        }
    }
    printf("\n\t\t\tAccount ID not found.\n");
}

void viewAllTransactions() {
    printf("\n\t\t\t========================\n");
    printf("\n\t\t\t--- All Transactions ---\n");
    printf("\n\t\t\t========================\n");
    for (int i = 0; i < accountCount; i++) {
        for (int j = 0; j < accounts[i].transactionCount; j++) {
            printf("\n\t\t\tAccount ID: %s, Transaction: %s", accounts[i].id, accounts[i].transactionHistory[j]);
        }
    }
}

void checkBalance(int index) {
    printf("\n\t\t\tCurrent Balance: %.2fpkr\n", accounts[index].balance);
}

void withdrawCash(int index) {
    float amount;
    printf("\n\t\t\tEnter amount to withdraw: pkr");
    scanf("%f", &amount);

    if (amount < 0){
        printf("Enter positive Numbers only:");
    }

    if (amount > accounts[index].balance) {
        printf("\t\t\tInsufficient balance.\n");
        return;
    }

    accounts[index].balance -= amount;
    sprintf(accounts[index].transactionHistory[accounts[index].transactionCount++], "Withdraw: %.2fpkr", amount);
    printf("\n\t\t\t %.2fpkr. withdrawn successfully.\n",amount);
}

void changeUserPassword(int index) {
    char newPassword[PASSWORD_LENGTH];
    printf("\n\t\t\tEnter new Password (4 digits): ");
    maskPassword(newPassword);
    strcpy(accounts[index].password, newPassword);
    printf("\n\t\t\tPassword changed successfully.\n");
}

void maskPassword(char *password) {
    char ch;
    int index = 0;

    while (1) {
        index = 0; // Reset index for each attempt

        while (1) {
            ch = getch(); // Read a character without echoing it
            if (ch == '\r') { // Enter key pressed
                break;
            } else if (ch == '\b') { // Backspace key pressed
                if (index > 0) {
                    printf("\b \b"); // Erase the last star
                    index--;
                }
            } else if (isdigit(ch)) { // Check if the character is a digit
                if (index < 4) {
                    password[index++] = ch;
                    printf("*"); // Show a star for each character
                }
            } else {
                printf("\n\t\t\tInvalid input. Please enter only numbers.\n");
                while ((ch = getch()) != '\n' && ch != '\r') {} // Clear invalid input
                printf("\t\t\tRe-enter Password (4 characters): ");
                continue; // Restart the loop for re-entry
            }
        }
        password[index] = '\0'; // Null-terminate the password

        // Validate password length
        if (strlen(password) != 4) {
            printf("\nInvalid Password! Password must be 4 digits long.\n");
            printf("\t\t\tRe-enter Password (4 characters): ");
            continue; // Restart the outer loop for a new attempt
        }
        break; // Valid password entered, exit loop
    }
}

void loadAccounts() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file) {
        if (fread(&accountCount, sizeof(int), 1, file) != 1 ||
            fread(accounts, sizeof(Account), accountCount, file) != accountCount) {
            printf("\n\t\t\tError: File data is corrupt. Starting with an empty account list.\n");
            accountCount = 0; // Initialize empty account list
        } else {
            printf("\n\t\t\tData loaded successfully from accounts.dat\n");
        }
        fclose(file);
    } else {
        printf("\n\t\t\tWarning: accounts.dat not found. Starting with an empty account list.\n");
        accountCount = 0; // Initialize empty account list
    }
}

void saveAccounts() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file) {
        fwrite(&accountCount, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
        printf("\n\t\t\tData saved successfully to accounts.dat\n");
    } else {
        printf("\n\t\t\tError: Unable to save data to accounts.dat\n");
    }
}

