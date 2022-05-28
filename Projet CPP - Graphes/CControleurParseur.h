#ifndef CONTROL_PARSER
#define CONTROL_PARSER

#include "CGraphe.h"
#include "CFichier.h"

#define EXCArretProgramme 50

#define EXCCheminVideCtrlParseur 30

class CControleurParseur {
private:
	char* pcCONChemin;
	CGraphe* pGRACONGraphe;
public:

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	CControleurParseur																   ****
	**** Entra�ne : La construction d'un objet CControleurParseur par d�faut						   ****
	******************************************************************************************************/
	CControleurParseur();

	/***********************************************************************************************************************
	**** Entr�es : pcChemin : char*																						****
	**** N�cessite :																		  							****
	**** Sorties :	CControleurParseur																					****
	**** Entra�ne : La construction d'un objet CControleurParseur poss�dant un chemin d'acc�s � un fichier de lecture	****
	***********************************************************************************************************************/
	CControleurParseur(char* pcChemin);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : La destruction de l'objet CControleurParseur									   ****
	******************************************************************************************************/
	~CControleurParseur();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	pcConChemin : char*																   ****
	**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
	******************************************************************************************************/
	char* CONLireChemin();

	/******************************************************************************************************
	**** Entr�es : pcChemin : char*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Modifie le chemin d'acc�s au fichier de lecture									   ****
	******************************************************************************************************/
	void CONModifierChemin(char* pcChemin);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	pcConChemin : char*																   ****
	**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
	******************************************************************************************************/
	CGraphe* CONLireGraphe();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Lis le fichier de lecture														   ****
	******************************************************************************************************/
	void CONLireFichierGraphe();
};

#endif // !CONTROL_PARSER
