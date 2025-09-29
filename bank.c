#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char name[100];
    int id;
    float balance;
};

struct History {
    char type[100];
    float balance;
    float amount;
    int year;
    int month;
    int day;
    int hour;
    int minute;
};


struct History data[100];
int historyCount = 0;

void addHistory(const char *type, float balance, float amount){

    strcpy(data[historyCount].type, type);
    data[historyCount].balance = balance;
    data[historyCount].amount = amount;

    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    
    data[historyCount].year = date->tm_year + 1900;
    data[historyCount].month = date->tm_mon + 1;
    data[historyCount].day = date->tm_mday;
    data[historyCount].hour = date->tm_hour;
    data[historyCount].minute = date->tm_min;

    historyCount++;

};

void seeHistory(){
    for(int i = 0; i < historyCount; i++){
    printf("%d. Type: %s\n   Amount %s: %.3f\n   Balance: %.3f\n   %d-%02d-%02d\n   %02d:%02d\n",
        i + 1, data[i].type, data[i].type, data[i].amount, data[i].balance,  data[i].year, data[i].month, data[i].day,data[i].hour, data[i].minute);
    
        printf("\n");
     }
};

void details(struct user *acc){

    printf("\n==== ACCOUNT DETAILS ====\n");
    printf("USER: Andi\n");
    printf("ACCOUNT ID: 908070\n");
    printf("BALANCE: %.3f\n", acc->balance);
    
};

void deposit(struct user *acc){
    float amount = 0;
    printf("Deposit money: Rp");
    scanf("%f", &amount);

    acc->balance += amount;
    printf("SUCESSFULLY DEPOSITED Rp%.3f\n", amount);
    addHistory("DEPOSIT", amount, acc->balance);
    
}

struct Account {
    char nameAcc[100];
    int AccID;
    float balanceAcc;
};

struct Account datas[] = {
    {"GILBERT", 50234, 150.000},
    {"COLE", 50239, 100.000}

};

int size = sizeof(datas) / sizeof(datas[0]);

void transfer(struct user *acc){
    float amount = 0;
    int accID = 0;
    
    printf("Enter Account ID Refer: ");
    scanf(" %d", &accID);

    for(int i = 0; i < size; i++){
        if(accID == datas[i].AccID)
        printf("How much to transfer: ");
        scanf("%f", &amount);

        if(acc->balance < amount){
            printf("INSUFFICIENT BALANCE!");
        }
        else {
            acc->balance -= amount;
            datas[i].balanceAcc += amount;

            printf("SUCCESFULLY TRANSFERED!");
            addHistory("TRANSFER", amount, acc->balance);

        }
        break;
    }
    
    
}

void seeAccount(struct Account datas[], int size){
    for(int i = 0; i < size; i++){
    printf("%d. USER        : %s\n   ACCOUNT ID  : %d\n   BALANCE     : Rp%.3f\n", 
            i + 1, datas[i].nameAcc, datas[i].AccID, datas[i].balanceAcc);
        
            printf("\n");
    }
}


int main(){
    struct user user;
    int choice;
    
    do {

        printf("\n==================\n");
        printf("  BLUE BANK MENU  \n");
        printf("==================\n");
        printf("(1). Account Details\n(2). Deposit Money\n(3). Transfer Money\n(4). Transaction History\n(5). Account user\n(6). EXIT\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            details(&user);
            break;

            case 2:
            deposit(&user);
            break;

            case 3:
            transfer(&user);
            printf("\n");
            break;

            case 4:
            seeHistory();
            break;

            case 5:
            seeAccount(datas, size);
            break;
        }


    } while (choice != 6);
    printf("Thank you for using!");

    return 0;

}
