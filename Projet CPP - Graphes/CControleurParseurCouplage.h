#ifndef CONTROL_PARSER_COUPLAGE
#define CONTROL_PARSER_COUPLAGE

#include "CFichier.h"

#define EXCArretProgramme 50

#define EXCCheminVideCtrlParseur 30

class CControleurParseurCouplage {
private:
	char* pcCONChemin;
	int** ppiCouplage;
	unsigned int uiCONNombreCouplage;
public:

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	CControleurParseur																   ****
	**** Entra�ne : La construction d'un objet CControleurParseur par d�faut						   ****
	******************************************************************************************************/
	CControleurParseurCouplage();

	/***********************************************************************************************************************
	**** Entr�es : pcChemin : char*																						****
	**** N�cessite :																		  							****
	**** Sorties :	CControleurParseur																					****
	**** Entra�ne : La construction d'un objet CControleurParseur poss�dant un chemin d'acc�s � un fichier de lecture	****
	***********************************************************************************************************************/
	CControleurParseurCouplage(char* pcChemin);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : La destruction de l'objet CControleurParseur									   ****
	******************************************************************************************************/
	~CControleurParseurCouplage();

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
	
	unsigned int CONLireNombreCouplage();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	pcConChemin : char*																   ****
	**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
	******************************************************************************************************/
	int** CONLireCouplage();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Lis le fichier de lecture														   ****
	******************************************************************************************************/
	void CONLireFichierCouplage();
};

#endif // !CONTROL_PARSER
