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
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	CControleurParseur																   ****
	**** Entraîne : La construction d'un objet CControleurParseurCouplage par défaut				   ****
	******************************************************************************************************/
	CControleurParseurCouplage();

	/*******************************************************************************************************************************
	**** Entrées : pcChemin : char*																								****
	**** Nécessite :																		  									****
	**** Sorties :	CControleurParseur																							****
	**** Entraîne : La construction d'un objet CControleurParseurCouplage possédant un chemin d'accès à un fichier de lecture	****
	*******************************************************************************************************************************/
	CControleurParseurCouplage(char* pcChemin);

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : La destruction de l'objet CControleurParseurCouplage							   ****
	******************************************************************************************************/
	~CControleurParseurCouplage();

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	pcConChemin : char*																   ****
	**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
	******************************************************************************************************/
	char* CONLireChemin();

	/******************************************************************************************************
	**** Entrées : pcChemin : char*																	   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Modifie le chemin d'accès au fichier de lecture									   ****
	******************************************************************************************************/
	void CONModifierChemin(char* pcChemin);
	
	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	unsigned int : Le nombre d'arcs dans le couplage								   ****
	**** Entraîne :																					   ****
	******************************************************************************************************/
	unsigned int CONLireNombreCouplage();

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :	CCouplage* : Le CCouplage lu dans le fichier									   ****
	**** Entraîne :																					   ****
	******************************************************************************************************/
	CCouplage* CONLireCouplage();

	/******************************************************************************************************
	**** Entrées :																					   ****
	**** Nécessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entraîne : Lis le fichier de lecture														   ****
	******************************************************************************************************/
	void CONLireFichierCouplage();
};

#endif // !CONTROL_PARSER
