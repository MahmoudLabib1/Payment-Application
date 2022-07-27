/*******************************************************************************
 *
 * [File Name]: app.h
 *
 * [Data Created]: July 22/2022
 *
 * [Description]: Header file for function prototypes of Application.
 *
 * [Author]: Mahmoud-Labib
 *
 *******************************************************************************/

#ifndef SCR_APPLICATION_APP_H_
#define SCR_APPLICATION_APP_H_


/*******************************************************************************
 *                                 Includes
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../utils/std_types.h"
#include "../Server/server.h"
#include "../Terminal/terminal.h"
#include "../Card/card.h"


/*******************************************************************************
 *                              Function Prototypes
 *******************************************************************************/
/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: appStart
 [DISCRIPTION]:	This function is responsible to start The system .
 [Args]: void
 [RUTURN]: void
 ---------------------------------------------------------------------------------------*/
void appStart(void);

/*--------------------------------------------------------------------------------------
 [FUNCTION NAME]: RepeatSystem
 [DISCRIPTION]:	This function is responsible to re-start The system after ask the client.
 [Args]: void
 [RUTURN]: void
 ---------------------------------------------------------------------------------------*/
void RepeatSystem(void);
#endif /* SCR_APPLICATION_APP_H_ */
