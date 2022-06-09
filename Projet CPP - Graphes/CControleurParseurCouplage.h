#ifndef CONTROL_PARSER_COUPLAGE
#define CONTROL_PARSER_COUPLAGE

#include "CFichier.h"
#include "CCouplage.h"

#define EXCArretProgramme 50

#define EXCCheminVideCtrlParseur 30

class CControleurParseurCouplage {
private:
	char* pcCONChemin;
	CCouplage* pCOUCouplage;
public:

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	CControleurParseur																   ****
	**** Entra�ne : La construction d'un objet CControleurParseurCouplage par d�faut				   ****
	******************************************************************************************************/
	CControleurParseurCouplage();

	/*******************************************************************************************************************************
	**** Entr�es : pcChemin : char*																								****
	**** N�cessite :																		  									****
	**** Sorties :	CControleurParseur																							****
	**** Entra�ne : La construction d'un objet CControleurParseurCouplage poss�dant un chemin d'acc�s � un fichier de lecture	****
	*******************************************************************************************************************************/
	CControleurParseurCouplage(char* pcChemin);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : La destruction de l'objet CControleurParseurCouplage							   ****
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
	
	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	unsigned int : Le nombre d'arcs dans le couplage								   ****
	**** Entra�ne :																					   ****
	******************************************************************************************************/
	unsigned int CONLireNombreCouplage();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	CCouplage* : Le CCouplage lu dans le fichier									   ****
	**** Entra�ne :																					   ****
	******************************************************************************************************/
	CCouplage* CONLireCouplage();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Lis le fichier de lecture														   ****
	******************************************************************************************************/
	void CONLireFichierCouplage();
};

#endif // !CONTROL_PARSER
