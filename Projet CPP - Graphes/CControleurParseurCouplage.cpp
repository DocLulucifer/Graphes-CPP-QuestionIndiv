#include "CControleurParseurCouplage.h"


/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	CControleurParseur																   ****
**** Entraîne : La construction d'un objet CControleurParseurCouplage par défaut				   ****
******************************************************************************************************/
CControleurParseurCouplage::CControleurParseurCouplage()
{
	pcCONChemin = nullptr;
	pCOUCouplage = new CCouplage();
}

/*******************************************************************************************************************************
**** Entrées : pcChemin : char*																								****
**** Nécessite :																		  									****
**** Sorties :	CControleurParseur																							****
**** Entraîne : La construction d'un objet CControleurParseurCouplage possédant un chemin d'accès à un fichier de lecture	****
*******************************************************************************************************************************/
CControleurParseurCouplage::CControleurParseurCouplage(char* pcChemin)
{
	pcCONChemin = pcChemin;
	pCOUCouplage = new CCouplage();
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : La destruction de l'objet CControleurParseurCouplage							   ****
******************************************************************************************************/
CControleurParseurCouplage::~CControleurParseurCouplage()
{
	pcCONChemin = nullptr;
	delete pCOUCouplage;
	pCOUCouplage = nullptr;	
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
******************************************************************************************************/
char* CControleurParseurCouplage::CONLireChemin()
{
	return pcCONChemin;
}

/******************************************************************************************************
**** Entrées : pcChemin : char*																	   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Modifie le chemin d'accès au fichier de lecture									   ****
******************************************************************************************************/
void CControleurParseurCouplage::CONModifierChemin(char* pcChemin)
{
	pcCONChemin = pcChemin;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	unsigned int : Le nombre d'arcs dans le couplage								   ****
**** Entraîne :																					   ****
******************************************************************************************************/
unsigned int CControleurParseurCouplage::CONLireNombreCouplage()
{
	return pCOUCouplage->COULireNbArcs();
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	CCouplage* : Le CCouplage lu dans le fichier									   ****
**** Entraîne :																					   ****
******************************************************************************************************/
CCouplage* CControleurParseurCouplage::CONLireCouplage()
{
	return pCOUCouplage;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Lis le fichier de lecture														   ****
******************************************************************************************************/
void CControleurParseurCouplage::CONLireFichierCouplage()
{
	if (pcCONChemin == nullptr) {
		throw CException(EXCCheminVideCtrlParseur);
	}
	
	//Initilisations
	CFichier FICParseur(pcCONChemin);
	unsigned int uiNbArcs = 0;
	unsigned int uiBoucle;
	int** ppiArcs = nullptr;

	//R�cup�ration du nombre d'arcs
	try {
		uiNbArcs = FICParseur.FICLireChiffre((char*)"nbarcs");
	}
	catch (CException EXCException) {

		cout << "ERREUR INTERNE PARSEUR : FICLireChiffre (Nb Arcs)" << endl;

		if (EXCException.EXCLireErreur() == EXCParserPointeurNul) {
			cout << "Le pointeur pcToken est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCFichierNonOuvert) {
			cout << "Aucun chemin d'acces au fichier precise ou Flot non initialise !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulSuppChar) {
			cout << "Le pointeur passe en parametre de FICSuppChar est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulMinuscule) {
			cout << "Le pointeur passe en parametre de FICMinuscule est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBoucleInfinie) {
			cout << "Une boucle infinie a ete declenchee dans FICLigneSuivante ! (Ou balise non detectee)" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCLigneNulle) {
			cout << "Le pointeur passe en parametre de FICLigneSuivante est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCValeurNeg) {
			cout << "Valeur parsee negative ou nulle !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCMiseEnFormeIncorecte) {
			cout << "Mise en forme incorrecte ou valeur manquante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBaliseIncorrecte) {
			cout << "Balise incorrecte ou manquante !" << endl;
		}		

		throw CException(EXCArretProgramme);
	}
	
	//R�cup�ration des arcs
	try {
		ppiArcs = FICParseur.FICLireTabAvecVirgule(uiNbArcs, (char*)"arcs", (char*)"debut", (char*)"fin");
	}
	catch (CException EXCException)
	{
		cout << "ERREUR INTERNE PARSEUR : FICLireTabAvecVirgule" << endl;

		if (EXCException.EXCLireErreur() == EXCParserPointeurNul) {
			cout << "Le pointeur pcToken est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCFichierNonOuvert) {
			cout << "Aucun chemin d'acces au fichier precise ou Flot non initialise !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulSuppChar) {
			cout << "Le pointeur passe en parametre de FICSuppChar est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCTokenNulMinuscule) {
			cout << "Le pointeur passe en parametre de FICMinuscule est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBoucleInfinie) {
			cout << "Une boucle infinie a ete declenchee dans FICLigneSuivante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCLigneNulle) {
			cout << "Le pointeur passe en parametre de FICLigneSuivante est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCValeurNeg) {
			cout << "Valeur parsee negative ou nulle !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCMiseEnFormeIncorecte) {
			cout << "Mise en forme incorrecte ou valeur manquante !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCNbLigneIns) {
			cout << "Nombre de lignes indiquees est inferieur au nombre de valeurs renseignees !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCBaliseIncorrecte) {
			cout << "Balise incorrecte ou manquante ! (Il manque peut etre des lignes de valeurs)" << endl;
		}		
		throw CException(EXCArretProgramme);
	}

	//Affectation Couplage
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		pCOUCouplage->COUAjouterArc(ppiArcs[uiBoucle]);
	}

	//Lib�ration m�moire
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++) {
		delete[] ppiArcs[uiBoucle];
	}
	delete[] ppiArcs;
}
