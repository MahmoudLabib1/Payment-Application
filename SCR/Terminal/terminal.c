/*******************************************************************************
 *
 * [File Name]: terminal.c
 *
 * [Data Created]: July 18/2022
 *
 * [Description]: Source file to implement functionality of Terminal.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Includes
 *******************************************************************************/
#include "terminal.h"
#define MAX_TRANSFER_AMOUNT       3000.00


ST_terminalData_t termData ={0}; // Initialization of termData By Zero
/*******************************************************************************
 *                             Function Implementation
 *******************************************************************************/

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getTransactionDate
 [DISCRIPTION]:	This function is responsible to read the current date from your computer
                and store it into terminal data and Check it.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	uint8_t arrIndex ,temp=0;
	time_t Todaydate;
	time(&Todaydate);

	strcpy( (char *)termData->transactionDate , _strdate ((char *)&Todaydate)); //Before 07/22/22
	termData->transactionDate[8] = termData->transactionDate[6];
	termData->transactionDate[9] = termData->transactionDate[7];
	termData->transactionDate[6] = '2';
	termData->transactionDate[7] = '0';//then 07/20/2022
	for(arrIndex=0 ; arrIndex < 2 ; arrIndex++){
		temp = termData->transactionDate[arrIndex];
		termData->transactionDate[arrIndex] = termData->transactionDate[arrIndex+3];
		termData->transactionDate[arrIndex+3] = temp;
	}
	termData->transactionDate[10] = '\0'; //After 20/07/2022


	if(termData->transactionDate == '\0')
	{
		return WRONG_DATE;
	}
	else
	{
		if(strlen((const char *)termData->transactionDate) < 10)
		{
			return WRONG_DATE;
		}
		else
		{

			return OK_term;
		}
	}

}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isCardExpired
 [DISCRIPTION]:	This function is responsible to compares the card expiry date with the transaction date.
 [Args]: cardData from structure (ST_cardData_t) and termData from structure (ST_terminalData_t)
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{          //07/22
	//20/07/2022
	uint8_t terminalarrIndex ,EXPIRED_Flag= FALSE ;

	for(terminalarrIndex=9 ; terminalarrIndex >= 3 ; terminalarrIndex-- )
	{
		if((terminalarrIndex == 9) || (terminalarrIndex == 8))
		{
			if(cardData.cardExpirationDate[terminalarrIndex-5] < termData.transactionDate[terminalarrIndex])
			{
				EXPIRED_Flag=TRUE;
			}
			else if(cardData.cardExpirationDate[terminalarrIndex-5] > termData.transactionDate[terminalarrIndex])
			{
				EXPIRED_Flag=FALSE;
			}
			else
			{
				continue;
			}
		}
		else if((terminalarrIndex == 4) || (terminalarrIndex == 3))
		{
			if(cardData.cardExpirationDate[terminalarrIndex-3] < termData.transactionDate[terminalarrIndex])
			{
				EXPIRED_Flag=TRUE;
			}
			else if(cardData.cardExpirationDate[terminalarrIndex-3] > termData.transactionDate[terminalarrIndex])
			{
				EXPIRED_Flag=FALSE;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}

	if(EXPIRED_Flag == TRUE)
	{
		return EXPIRED_CARD;
	}
	else
	{
		return OK_term;
	}

}


/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isValidCardPAN
 [DISCRIPTION]:	This function is responsible to Check Validate of the Card PAN
                Using The Luhn Algorithm But from Terminal .
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
	if(LuhnChecksum(cardData->primaryAccountNumber) == OK)
	{
		return OK_term;
	}
	else
	{
		return INVALID_CARD;
	}
}


/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getTransactionAmount
 [DISCRIPTION]:	This function is responsible to Take transaction amount and saves it into terminal data.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	sleep(1);
	printf("\nPLZ Enter The Tansaction Amount :  ");
	scanf(" %f", &termData->transAmount);
	if(termData->transAmount <= 0){
		return INVALID_AMOUNT;
	}
	else
	{
		return OK_term;
	}
}



/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isBelowMaxAmount
 [DISCRIPTION]:	This function is responsible to compares the transaction amount with the terminal max amount..
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{

	if(termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return OK;
	}


}


/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: setMaxAmount
 [DISCRIPTION]:	This function is responsible to sets the maximum allowed amount into terminal data.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	termData->maxTransAmount = MAX_TRANSFER_AMOUNT;
	if(termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return OK;
	}
}
