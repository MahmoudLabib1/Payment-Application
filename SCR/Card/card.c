/*******************************************************************************
 *
 * [File Name]: card.c
 *
 * [Data Created]: July 17/2022
 *
 * [Description]: Source file to implement functionality of Card.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Includes
 *******************************************************************************/
#include "../Card/card.h"

ST_cardData_t cardData ={0}; //Initialized by Zero

/*******************************************************************************
 *                             Function Implementation
 *******************************************************************************/
/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: LuhnChecksum
 [DISCRIPTION]:	This function is responsible to Check Validate of the Card PAN
                Using The Luhn Algorithm .
 [Args]: pointer to uint8_t
 [RUTURN]: uint8_t
 ---------------------------------------------------------------------------------------*/

uint8_t LuhnChecksum(uint8_t *PAN)
{
	uint8_t sum=0;
	uint8_t i_Index ;
	uint8_t PAN_len=strlen((const char*)PAN);
	for(i_Index=0 ; i_Index < PAN_len ; i_Index++)
	{
		if(i_Index % 2 == 0){
			sum += (((PAN[i_Index]-Decimal_CR_ZERO) * 2)/10);
			sum += ((PAN[i_Index]-Decimal_CR_ZERO) * (2)) % 10;
		}
		else
		{
			sum += (PAN[i_Index]-Decimal_CR_ZERO);
		}
	}
	return (sum % 10);
}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getCardHolderName
 [DISCRIPTION]:	This function is responsible to Take From client the Card Holder Name .
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_cardError_t
 ---------------------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
	uint8_t arrIndex=0;
	uint8_t name[25]={0};
	printf("PlZ Enter The card Holder Name :  ");
	gets((char *)name);

	while(arrIndex <= 24)
	{
		cardData->cardHolderName[arrIndex] = name[arrIndex];
		arrIndex++;
	}


	if(cardData->cardHolderName == '\0' )
	{
		return WRONG_NAME;
	}
	else
	{
		if((strlen((const char*)cardData->cardHolderName) < 20) || ((strlen((const char*)cardData->cardHolderName) > 24)))
		{
			return WRONG_NAME;
		}
		else
		{
			return OK;
		}
	}

}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getCardExpiryDate
 [DISCRIPTION]:	This function is responsible to Take From client the expire data of the Card.
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_cardError_t
 ---------------------------------------------------------------------------------------*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	uint8_t arrIndex=0;
	uint8_t card_valid_Date[10];

   //MM/YY 07/25
	printf("\nPlZ Enter The Card Expiry Date :  ");
	gets((char *)card_valid_Date);

	while(arrIndex <= 10)
	{
		cardData->cardExpirationDate[arrIndex] = card_valid_Date[arrIndex];
		arrIndex++;
	}



	if(cardData->cardExpirationDate == '\0' )
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		if((strlen((const char *)cardData->cardExpirationDate) < 5) || (strlen((const char *)cardData->cardExpirationDate) > 5))
		{
			return WRONG_EXP_DATE;
		}
		else
		{
			return OK;
		}
	}

}

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getCardPAN
 [DISCRIPTION]:	This function is responsible to Take From Client the Primary Account Number of the Card.
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_cardError_t
 ---------------------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	uint8_t arrIndex=0;
	uint8_t card_PAN_Date[20];


	printf("\nPlZ Enter The Card PAN :  ");
	gets((char *)card_PAN_Date);

	if(LuhnChecksum((uint8_t *)&card_PAN_Date) == OK)
	{
		while(arrIndex <= 19)
			{
				cardData->primaryAccountNumber[arrIndex] = card_PAN_Date[arrIndex];
				arrIndex++;
			}
	}
	else
	{
		return WRONG_PAN;
	}


	if(cardData->primaryAccountNumber[0] == '\0' )
	{
		return WRONG_PAN;
	}
	else
	{

		if((strlen((const char *)cardData->primaryAccountNumber) < 16) || (strlen((const char *)cardData->primaryAccountNumber) > 19))
		{
			return WRONG_PAN;
		}
		else
		{
			return OK;
		}
	}
}
