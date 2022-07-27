/*******************************************************************************
 *
 * [File Name]: terminal.h
 *
 * [Data Created]: July 18/2022
 *
 * [Description]: Header file for function prototypes and configuration of terminal.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

#ifndef SCR_TERMINAL_TERMINAL_H_
#define SCR_TERMINAL_TERMINAL_H_

/*******************************************************************************
 *                             Includes
 *******************************************************************************/
#include <time.h>
#include <unistd.h>
#include "../utils/std_types.h"
#include "../Card/card.h"

/*******************************************************************************
 *                              Structures & Enumerations
 *******************************************************************************/
/*------------------------------------------------------------------------------------
 [Structure Name]:	ST_terminalData_t
 [DISCRIPTION]:		This structure is responsible for store information From Terminal
                    to check the validate of card before Transaction Process ;
 -------------------------------------------------------------------------------------*/
typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

ST_terminalData_t termData; // declaration of variable termData from structure Type (ST_terminalData_t)

/*------------------------------------------------------------------------------------
 [Enum Name]:	EN_terminalError_t
 [DISCRIPTION]:	This Enumeration is responsible to text the error values of Terminal
                 to increase the readability of code.
 -------------------------------------------------------------------------------------*/
typedef enum EN_terminalError_t
{
  OK_term, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

/*******************************************************************************
 *                              Function Prototypes
 *******************************************************************************/

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getTransactionDate
 [DISCRIPTION]:	This function is responsible to read the current date from your computer
                and store it into terminal data and Check it.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isCardExpired
 [DISCRIPTION]:	This function is responsible to compares the card expiry date with the transaction date.
 [Args]: cardData from structure (ST_cardData_t) and termData from structure (ST_terminalData_t)
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isValidCardPAN
 [DISCRIPTION]:	This function is responsible to Check Validate of the Card PAN
                Using The Luhn Algorithm But from Terminal .
 [Args]: pointer to structure from type ST_cardData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: getTransactionAmount
 [DISCRIPTION]:	This function is responsible to Take transaction amount and saves it into terminal data.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: isBelowMaxAmount
 [DISCRIPTION]:	This function is responsible to compares the transaction amount with the terminal max amount..
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: setMaxAmount
 [DISCRIPTION]:	This function is responsible to sets the maximum allowed amount into terminal data.
 [Args]: pointer to structure from type ST_terminalData_t
 [RUTURN]: EN_terminalError_t
 ---------------------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif /* SCR_TERMINAL_TERMINAL_H_ */
