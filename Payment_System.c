#include "Payment_System.h"

ST_accountBalance Balance[10];
int Transaction_Index=0;
ST_transaction Server_Arr [255];

void fillCardData(ST_transaction *transaction){
    printf("Please, Enter Card Holder Name:");
    gets(transaction->cardHolderData.cardHolderName);
    printf("Please, Enter the Primary Account Number:");
    gets(transaction->cardHolderData.primaryAccountNumber);
    printf("Please, Enter the Card Expiry Date:");
    gets(transaction->cardHolderData.cardExpirationDate);
}
void checkAmount(ST_transaction *transaction){
    if(atof(transaction->transData.transAmount)>(float)5000.00){
        transaction->transResponse.transactionStatus=DECLINED;
        transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
        printf("The transaction is DECLINED cause max transaction amount\n");
    }
}
void checkExpiryDate(ST_transaction *transaction){
    if(transaction->cardHolderData.cardExpirationDate[3]<transaction->transData.transactionDate[8]){
        transaction->transResponse.transactionStatus=DECLINED;
        transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
        printf("The transaction is DECLINED cause the card expired\n");
    }else{
        if(transaction->cardHolderData.cardExpirationDate[4]<transaction->transData.transactionDate[9]){
            transaction->transResponse.transactionStatus=DECLINED;
            transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
            printf("The transaction is DECLINED cause the card expired\n");
        }else{
            if(transaction->cardHolderData.cardExpirationDate[0]<transaction->transData.transactionDate[3]){
                transaction->transResponse.transactionStatus=DECLINED;
                transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
                printf("The transaction is DECLINED cause the card expired\n");
            }else{
                if(transaction->cardHolderData.cardExpirationDate[1]<transaction->transData.transactionDate[4]){
                    transaction->transResponse.transactionStatus=DECLINED;
                    transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
                    printf("The transaction is DECLINED cause the card expired\n");
                }
            }
        }
    }
}
void fillTerminalData(ST_transaction *transaction){
    printf("Please, Enter the transaction amount:");
    gets(transaction->transData.transAmount);
    gcvt(5000.00,6,transaction->transData.maxTransAmount);
    checkAmount(transaction);
    if(transaction->transResponse.transactionStatus!=DECLINED){
    printf("Please, Enter the Card Transaction Date:");
    gets(transaction->transData.transactionDate);
    }
}
void checkBalance(ST_transaction *transaction){
    int i=0;
    char Found=0;
    for(i=0;i<Balance_ArrSize;i++){
        if(atoi(transaction->cardHolderData.primaryAccountNumber)== atoi(Balance[i].primaryAccountNumber)){
                Found=1;
            if(atoi(Balance[i].balance)<atoi(transaction->transData.transAmount)){
                transaction->transResponse.transactionStatus=DECLINED;
                transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
                    printf("The transaction is DECLINED cause balance\n");
            }
        }
    }
    if(0==Found){
        transaction->transResponse.transactionStatus=DECLINED;
                transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
                    printf("The transaction is DECLINED cause the account is not exist\n");
    }
}
void saveTransactionIntoServer(ST_transaction *transaction){
    if(transaction->transResponse.transactionStatus!=DECLINED){
        checkExpiryDate(transaction);
        checkBalance(transaction);
    }
    if(transaction->transResponse.transactionStatus!=DECLINED){
            transaction->transResponse.transactionStatus=APPROVED;
                transaction->transResponse.receiptReferenceNumber=++Transaction_Index;
        printf("The Transaction is APPROVED.\n");
    }
    Server_Arr[transaction->transResponse.receiptReferenceNumber]=*transaction;

    printf("Do you want to continue (y/n)?");
}
void main (){
ST_transaction Transaction;
ST_transaction * Transaction_Ptr=&Transaction;
char Continue='Y';
strcpy(Balance[0].primaryAccountNumber,"123456789");
strcpy(Balance[0].balance,"0100.00");
strcpy(Balance[1].primaryAccountNumber,"234567891");
strcpy(Balance[1].balance,"6000.00");
strcpy(Balance[2].primaryAccountNumber,"567891234");
strcpy(Balance[2].balance,"3250.25");
strcpy(Balance[3].primaryAccountNumber,"456789123");
strcpy(Balance[3].balance,"1500.12");
strcpy(Balance[4].primaryAccountNumber,"258649173");
strcpy(Balance[4].balance,"0500.00");
strcpy(Balance[5].primaryAccountNumber,"654823719");
strcpy(Balance[5].balance,"2100.00");
strcpy(Balance[6].primaryAccountNumber,"971362485");
strcpy(Balance[6].balance,"0000.00");
strcpy(Balance[7].primaryAccountNumber,"793148625");
strcpy(Balance[7].balance,"0001.00");
strcpy(Balance[8].primaryAccountNumber,"123123456");
strcpy(Balance[8].balance,"0010.12");
strcpy(Balance[9].primaryAccountNumber,"456789321");
strcpy(Balance[9].balance,"0000.55");
    while(('Y'==Continue)||('y'==Continue)){
    printf("Please Enter Card Data:\n");
    fillCardData(Transaction_Ptr);
    printf("Please Enter Terminal Data:\n");
    fillTerminalData(Transaction_Ptr);
    saveTransactionIntoServer(Transaction_Ptr);
    gets(&Continue);
    }
}
