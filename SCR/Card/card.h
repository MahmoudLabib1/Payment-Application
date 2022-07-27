/*******************************************************************************
 *
 * [File Name]: card.h
 *
 * [Data Created]: July 17/2022
 *
 * [Description]: Header file for function prototypes and configuration of Card.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

#ifndef SCR_CARD_CARD_H_
#define SCR_CARD_CARD_H_

/*******************************************************************************
 *                                 Includes & Definitions
 *******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "../utils/std_types.h"

#define Decimal_CR_ZERO      48


/*******************************************************************************
 *                              Structures & Enumerations
 *******************************************************************************/
/*------------------------------------------------------------------------------------
 [Structure Name]:	ST_cardData_t
 [DISCRIPTION]:	    This structure is responsible for store information about the card;

 -------------------------------------------------------------------------------------*/

typedef struct ST_cardData_t
{
  uint8_t cardHolderName[25];
  uint8_t primaryAccountNumber[20];
  uint8_t cardExpirationDate[6];
}ST_cardData_t;

ST_cardData_t cardData;  //variable from structure type (ST_cardData_t)

/*------------------------------------------------------------------------------------
 [Enum Name]:	EN_cardError_t
 [DISCRIPTION]:	This Enumeration is responsible to text the error values of card
                 to increase the readability of code.

 -------------------------------------------------------------------------------------*/
typedef enum EN_cardError_t
{
OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/*******************************************************************************
 *                              Function Prototypes
 *******************************************************************************/

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getCardHolderName
 [DISCRIPTION]:	This function is responsible to Take From client the Card Holder Name .
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_cardError_t
 ---------------------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getCardExpiryDate
 [DISCRIPTION]:	This function is responsible to Take From client the expire data of the Card.
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_cardError_t
 ---------------------------------------------------------------------------------------*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getCardPAN
 [DISCRIPTION]:	This function is responsible to Take From Client the Primary Account Number of the Card.
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_cardError_t
 ---------------------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: LuhnChecksum
 [DISCRIPTION]:	This function is responsible to Check Validate of the Card PAN
                Using The Luhn Algorithm .
 [Args]: pointer to uint8_t
 [RUTURN]: uint8_t
 ---------------------------------------------------------------------------------------*/
uint8_t LuhnChecksum(uint8_t *PAN);

#endif /* SCR_CARD_CARD_H_ */
