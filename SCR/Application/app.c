/*******************************************************************************
 *
 * [File Name]: app.c
 *
 * [Data Created]: July 22/2022
 *
 * [Description]: Source file to implement functionality of Application.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

/*******************************************************************************
 *                                 Includes
 *******************************************************************************/
#include "app.h"

/****************************** Global Variables *******************************/
volatile bool Again= TRUE;
volatile uint8_t  *character=NULL;
/*******************************************************************************
 *                             Function Implementation
 *******************************************************************************/

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: appStart
 [DISCRIPTION]:	This function is responsible to start The system .
 [Args]: void
 [RUTURN]: void
 ---------------------------------------------------------------------------------------*/
void appStart(void)
{



	printf("*************************************************************************\n");
	printf("*\t\t\tWELCOME TO PAYMENT APPLICATION\t\t\t*\n");
	printf("*************************************************************************\n");

	if(getCardHolderName(&cardData) == OK)
	{
		if(getCardExpiryDate(&cardData) == OK)
		{
			if((getCardPAN(&cardData) == OK) && (isValidCardPAN(&cardData) == OK_term))
			{
				sleep(1);
				printf("\n---------The card PAN VALID---------");

				if(getTransactionDate(&termData) == OK_term)
				{
					if(isCardExpired(cardData,termData) == OK_term)
					{
						sleep(1);
						printf("\nThe Card Data Accepted!");
						if(getTransactionAmount(&termData) == OK_term)
						{
							if(setMaxAmount(&termData) == OK_term)
							{
								if(isBelowMaxAmount(&termData) == OK_term)
								{
									sleep(1);
									printf("\nThe Transaction Amount Accepted!!");
									sleep(1);
									printf("\nPlZ Wait a Sec To Check Your Account At The Server");
									if( recieveTransactionData(Arr_transaction) == APPROVED)
									{
										sleep(1);
										printf("\n----- The Money Transfer Is DONE -----\n");
										sleep(1);
										printf("\n--------------- Thank You For Use Our ATM Serves ---------------");
									}
									else
									{
										if( recieveTransactionData(Arr_transaction) == DECLINED_STOLEN_CARD)
										{
											sleep(1);
											printf("\nThis Account NOT Exist at Server!!!!");
											sleep(1);
											printf("\nThis Card Stolen!!");
											RepeatSystem();
										}
										else if(recieveTransactionData(Arr_transaction) == LOW_BALANCE)
										{
											sleep(1);
											printf("\nYour Balance Not Have Enough Money To Transfer!!");
											RepeatSystem();
										}
										else
										{
											sleep(1);
											printf("\n Server Error!!");
											RepeatSystem();
										}
									}
								}
								else
								{
									sleep(1);
									printf("\nThe Amount EXCEED MaxTransaction!!");
									RepeatSystem();
								}
							}
							else
							{
								sleep(1);
								printf("\nThe MaxTransaction INVALID!!");
								RepeatSystem();
							}
						}
						else
						{
							sleep(1);
							printf("\nThe Amount INVALID!!");
							RepeatSystem();
						}
					}
					else
					{
						sleep(1);
						printf("\nThe Card EXPIRED!!");
						RepeatSystem();
					}
				}
				else
				{
					sleep(1);
					printf("\nThe Transaction Date Wrong!");
					RepeatSystem();
				}
			}
			else
			{
				sleep(1);
				printf("\nThe Card PAN Error!");
				RepeatSystem();
			}
		}
		else
		{
			sleep(1);
			printf("\nThe Card ExpirtyDate Error!");
			sleep(1);
			printf("\nFormat must be MM/YY 07/25");
			RepeatSystem();
		}
	}
	else
	{
		sleep(1);
		printf("\nThe Card Holder Name Error!");
		RepeatSystem();

	}
}







/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: RepeatSystem
 [DISCRIPTION]:	This function is responsible to re-start The system after ask the client.
 [Args]: void
 [RUTURN]: void
 ---------------------------------------------------------------------------------------*/
void RepeatSystem(void)
{
	sleep(1);
	printf("\nARE You Want Start The System AGAIN (Y/N):");
	gets((char *)&character);

	if((*character == 'Y') || (*character == 'y'))
	{
		Again = TRUE;
	}
	else if((*character == 'N') || (*character == 'n'))
	{
		Again = FALSE;
	}

}
