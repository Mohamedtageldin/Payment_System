#include "Payment_System.h"

void fillCardData(ST_transaction *transaction){
    printf("Please, Enter Card Holder Name:");
    gets(&(transaction->cardHolderData.cardHolderName));
    printf("Please, Enter the Primary Account Number:");
    gets(&(transaction->cardHolderData.primaryAccountNumber));
    printf("Please, Enter the Card Expiry Date:");
    gets(&(transaction->cardHolderData.cardExpirationDate));
}
void checkAmount(ST_transaction *transaction){
    if(atof(transaction->transData.transAmount)>(float)Max_TransactionAmount){
        transaction->transResponse.transactionStatus=DECLINED;
        printf("The transaction is DECLINED");
    }
}
void checkExpiryDate(ST_transaction *transaction){
    if(transaction->cardHolderData.cardExpirationDate[3]<transaction->transData.transactionDate[8]){
        transaction->transResponse.transactionStatus=DECLINED;
        printf("The transaction is DECLINED");
    }else{
        if(transaction->cardHolderData.cardExpirationDate[4]<transaction->transData.transactionDate[9]){
            transaction->transResponse.transactionStatus=DECLINED;
            printf("The transaction is DECLINED");
        }else{
            if(transaction->cardHolderData.cardExpirationDate[0]<transaction->transData.transactionDate[3]){
                transaction->transResponse.transactionStatus=DECLINED;
                printf("The transaction is DECLINED");
            }else{
                if(transaction->cardHolderData.cardExpirationDate[1]<transaction->transData.transactionDate[4]){
                    transaction->transResponse.transactionStatus=DECLINED;
                    printf("The transaction is DECLINED");
                }
            }
        }
    }
}
void fillTerminalData(ST_transaction *transaction){
    printf("Please, Enter the transaction amount:");
    gets(&(transaction->transData.transAmount));
    transaction->transData.maxTransAmount=Max_TransactionAmount;
    checkAmount();
    printf("Please, Enter the Card Transaction Date:");
    gets(&(transaction->transData.transactionDate));
    checkExpiryDate(transaction);
}
void checkBalance(ST_transaction *transaction){
    int i=0;
    for(i=0;i<Balance_ArrSize;i++){
        if((transaction->cardHolderData.cardHolderName)==extern Balance[i]){
            if(atoi(Balance[i].balance)<atoi(transaction->transData.transAmount)){
                transaction->transResponse.transactionStatus=DECLINED;
                    printf("The transaction is DECLINED");
            }
        }
    }
}
void saveTransactionIntoServer(ST_transaction *transaction){

}
