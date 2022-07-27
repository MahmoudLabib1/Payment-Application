/*******************************************************************************
 *
 * [File Name]: server.c
 *
 * [Data Created]: July 21/2022
 *
 * [Description]: Source file to implement functionality of server.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/



/*******************************************************************************
 *                             Includes
 *******************************************************************************/
#include "server.h"
#define PAN_SIZE    19


static volatile uint8_t Account_Index=0;
volatile uint32_t transactionSequenceNumber = 0;
ST_accountsDB_t  Arr_valid_AccountsDB[255]={
		{1000.31,"7604960279361232"},
		{5000.31,"9971750719302925"},
		{11000.31,"5995480867178097"},
		{15000.21,"5081893361192775"},
		{12000.61,"5359540003659712"},
		{200.50,"4573764896095783"}

};

ST_transaction_t Arr_transaction[255]={0};

/*******************************************************************************
 *                                   Private Function
 *******************************************************************************/

//static EN_serverError_t Get_AccountIndex(ST_cardData_t *CardData)
//{
//
//
//}
/*******************************************************************************
 *                             Function Implementation
 *******************************************************************************/

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: recieveTransactionData
 [DISCRIPTION]:	This function is responsible to Take all transaction data and validate its data
                and checks the account details and amount availability and check if saveing the transaction
                success or not then update the database with the new balance.
 [Args]: pointer to structure from type ST_transaction_t
 [RUTURN]: EN_transState_t
 ---------------------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{

	uint8_t Loop_Index=0;
	while(Loop_Index <= 5)
	{
		sleep(1);
		printf(".");
		Loop_Index++;
	}

	if(isValidAccount(&cardData) == OK_server)
	{
		printf("\nThe Account Valid And Exist at Server!");
		if(isAmountAvailable(&termData) == OK_server)
		{
			sleep(1);
			printf("\nYour Balance Has Enough Money!");
			if(saveTransaction(Arr_transaction) == OK_server)
			{
				sleep(1);
				return APPROVED;
			}
			else
			{
				return INTERNAL_SERVER_ERROR ;
			}
		}
		else
		{

			return LOW_BALANCE;
		}
	}
	else
	{

		return DECLINED_STOLEN_CARD;
	}

}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isValidAccount
 [DISCRIPTION]:	This function is responsible to Take card data and validate these data
                and checks if the PAN exists or not in the server's database .
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_transState_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
	uint8_t i_Index=0 , Account_Loop_Index=0;

	while(i_Index <= PAN_SIZE)
	{
		if(cardData->primaryAccountNumber[i_Index] != Arr_valid_AccountsDB[Account_Loop_Index].primaryAccountNumber[i_Index])
		{
			if(Account_Loop_Index <= 254)
			{
				Account_Loop_Index++;
				i_Index=0;
			}
			else
			{
				break;
			}

		}
		else
		{
			if(i_Index == PAN_SIZE){
				Account_Index=Account_Loop_Index;
				return OK_server;
			}
			i_Index++;
		}
	}

		return DECLINED_STOLEN_CARD;
}


/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isAmountAvailable
 [DISCRIPTION]:	This function is responsible to Take terminal data and validate these data
                and checks if the transaction's amount is available or not.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_serverError_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{

	if(Arr_valid_AccountsDB[Account_Index].balance != 0.0 )
	{
		if(termData->transAmount > Arr_valid_AccountsDB[Account_Index].balance )
		{
			return LOW_BALANCE;
		}
		else
		{
			// Update the Balance in The Account
			Arr_valid_AccountsDB[Account_Index].balance = (Arr_valid_AccountsDB[Account_Index].balance) - (termData->transAmount);
			return OK_server;
		}
	}
	else
	{
		return LOW_BALANCE;
	}

}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: saveTransaction
 [DISCRIPTION]:	This function is responsible to Take all transaction data into the transactions database
                and It gives a sequence number to a transaction, this number is incremented
                once a transaction is processed into the server and control process of saving.
 [Args]: pointer to structure from type ST_transaction_t
 [RUTURN]: EN_serverError_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

	if(getTransaction(transactionSequenceNumber,Arr_transaction) == OK_server){

		strcpy((char *)Arr_transaction[transactionSequenceNumber].cardHolderData.cardHolderName ,(const char *) cardData.cardHolderName);
		strcpy((char *)Arr_transaction[transactionSequenceNumber].cardHolderData.cardExpirationDate , (const char *) cardData.cardExpirationDate);
		strcpy((char *)Arr_transaction[transactionSequenceNumber].cardHolderData.primaryAccountNumber ,(const char *)  cardData.primaryAccountNumber);
		strcpy((char *)Arr_transaction[transactionSequenceNumber].terminalData.transactionDate ,(const char *) termData.transactionDate );
		Arr_transaction[transactionSequenceNumber].terminalData.maxTransAmount = termData.maxTransAmount;
		Arr_transaction[transactionSequenceNumber].terminalData.transAmount = termData.transAmount;
		Arr_transaction[transactionSequenceNumber].transState = APPROVED;
		Arr_transaction[transactionSequenceNumber].transactionSequenceNumber = transactionSequenceNumber;
		transactionSequenceNumber++;
		return OK_server;
	}
	else
	{
		return SAVING_FAILED;
	}


}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getTransaction
 [DISCRIPTION]:	This function is responsible to check using transactionSequenceNumber if transcationDB Empty
                even save new Client Data or Not.
 [Args]: pointer to structure from type ST_transaction_t and transactionSequenceNumber from type uint32_t
 [RUTURN]: EN_serverError_t
 ---------------------------------------------------------------------------------------*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
	uint8_t i_Index=0;
	while(i_Index < 255)
	{
		if((i_Index == ZERO )  && (Arr_transaction[i_Index].transactionSequenceNumber == ZERO) && (transactionSequenceNumber == ZERO))
		{
			return OK_server;
		}
		else
		{
			if(Arr_transaction[i_Index].transactionSequenceNumber != transactionSequenceNumber)
			{
				return OK_server;
			}
			else
			{
				i_Index++;
			}
		}

	}
	return SAVING_FAILED;

}
