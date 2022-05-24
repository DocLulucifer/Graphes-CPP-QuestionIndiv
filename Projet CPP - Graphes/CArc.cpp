#include "CArc.h"

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Construction d'un objet CArc par d�faut											   ****
******************************************************************************************************/
CArc::CArc()
{
	iARCNumeroSommet = -1;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Construction d'un objet CArc par recopie										   ****
******************************************************************************************************/
CArc::CArc(const CArc& ARCParam)
{
	iARCNumeroSommet = ARCParam.ARCLireDestination();
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Construction d'un objet CArc par valeur de destination							   ****
******************************************************************************************************/
CArc::CArc(int iParam)
{
	iARCNumeroSommet = iParam;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Destruction d'un objet CArc par d�faut											   ****
******************************************************************************************************/
CArc::~CArc()
{

}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	int iARCNumeroSommet : Destination de l'arc										   ****
**** Entra�ne :	Lecture de valeur de destination de l'arc	 									   ****
******************************************************************************************************/
int CArc::ARCLireDestination() const
{
	return iARCNumeroSommet;
}

/******************************************************************************************************
**** Entr�es :	int iDestination : Nouvelle destination de l'arc								   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne :	Changement de valeur de destination de l'arc									   ****
******************************************************************************************************/
void CArc::ARCChangerDestination(int iDestination)
{
	iARCNumeroSommet= iDestination;
}

/******************************************************************************************************
**** Entr�es : const CArc ARCparam : CArc � copier												   ****
**** N�cessite : ARCparam non nul														  	       ****
**** Sorties :	CArc & this : Objet modifi� selon le param�tre									   ****
**** Entra�ne : La copie de l'objet CArc en param�tre											   ****
******************************************************************************************************/
CArc& CArc::operator=(const CArc ARCparam)
{
	iARCNumeroSommet = (int)ARCparam.ARCLireDestination();
	return *this;
}
