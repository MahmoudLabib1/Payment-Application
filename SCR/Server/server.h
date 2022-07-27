/*******************************************************************************
 *
 * [File Name]: server.h
 *
 * [Data Created]: July 21/2022
 *
 * [Description]: Header file for function prototypes and configuration of server.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

#ifndef SCR_SERVER_SERVER_H_
#define SCR_SERVER_SERVER_H_

/*******************************************************************************
 *                             Includes
 *******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include "../utils/std_types.h"
#include "../Terminal/terminal.h"
#include "../Card/card.h"


/*******************************************************************************
 *                              Structures & Enumerations
 *******************************************************************************/

/*------------------------------------------------------------------------------------
 [Enum Name]:	EN_transState_t
 [DISCRIPTION]:	This Enumeration is responsible to text the error values of transaction state
                 to increase the readability of code.
 -------------------------------------------------------------------------------------*/
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;


/*------------------------------------------------------------------------------------
 [Structure Name]:	ST_transaction_t
 [DISCRIPTION]:		This structure is responsible for store All information collected
                    from card and terminal.
 -------------------------------------------------------------------------------------*/
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

/*------------------------------------------------------------------------------------
 [Enum Name]:	EN_serverError_t
 [DISCRIPTION]:	This Enumeration is responsible to text the error values of Server
                 to increase the readability of code.
 -------------------------------------------------------------------------------------*/
typedef enum EN_serverError_t
{
	OK_server, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE,
}EN_serverError_t ;

/*------------------------------------------------------------------------------------
 [Structure Name]:	ST_accountsDB_t
 [DISCRIPTION]:		This structure is Act as database that collect the PAN And Balance
                    of every Account.
 -------------------------------------------------------------------------------------*/
typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;



ST_accountsDB_t Arr_valid_AccountsDB[255];

ST_transaction_t Arr_transaction[255];
/*******************************************************************************
 *                              Function Prototypes
 *******************************************************************************/

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: recieveTransactionData
 [DISCRIPTION]:	This function is responsible to Take all transaction data and validate its data
                and checks the account details and amount availability and check if saveing the transaction
                success or not then update the database with the new balance.
 [Args]: pointer to structure from type ST_transaction_t
 [RUTURN]: EN_transState_t
 ---------------------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isValidAccount
 [DISCRIPTION]:	This function is responsible to Take card data and validate these data
                and checks if the PAN exists or not in the server's database .
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_transState_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isAmountAvailable
 [DISCRIPTION]:	This function is responsible to Take terminal data and validate these data
                and checks if the transaction's amount is available or not.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_serverError_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: saveTransaction
 [DISCRIPTION]:	This function is responsible to Take all transaction data into the transactions database
                and It gives a sequence number to a transaction, this number is incremented
                once a transaction is processed into the server and control process of saving.
 [Args]: pointer to structure from type ST_transaction_t
 [RUTURN]: EN_serverError_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t *transData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getTransaction
 [DISCRIPTION]:	This function is responsible to check using transactionSequenceNumber if transcationDB Empty
                even save new Client Data or Not.
 [Args]: pointer to structure from type ST_transaction_t and transactionSequenceNumber from type uint32_t
 [RUTURN]: EN_serverError_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

#endif /* SCR_SERVER_SERVER_H_ */
