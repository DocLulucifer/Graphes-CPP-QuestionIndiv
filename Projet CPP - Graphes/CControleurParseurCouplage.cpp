#include "CControleurParseurCouplage.h"


/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	CControleurParseur																   ****
**** Entraîne : La construction d'un objet CControleurParseur par défaut						   ****
******************************************************************************************************/
CControleurParseurCouplage::CControleurParseurCouplage()
{
	pcCONChemin = nullptr;
	uiCONNombreCouplage = 0;
	ppiCouplage = nullptr;
}

/***********************************************************************************************************************
**** Entrées : pcChemin : char*																						****
**** Nécessite :																		  							****
**** Sorties :	CControleurParseur																					****
**** Entraîne : La construction d'un objet CControleurParseur possédant un chemin d'accès à un fichier de lecture	****
***********************************************************************************************************************/
CControleurParseurCouplage::CControleurParseurCouplage(char* pcChemin)
{
	pcCONChemin = pcChemin;
	uiCONNombreCouplage = 0;
	ppiCouplage = nullptr;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : La destruction de l'objet CControleurParseur									   ****
******************************************************************************************************/
CControleurParseurCouplage::~CControleurParseurCouplage()
{
	unsigned int uiboucle;
	pcCONChemin = nullptr;
	
	for (uiboucle = 0 ; uiboucle < uiCONNombreCouplage; uiboucle++)
	{
		delete ppiCouplage[uiboucle];
	}
	delete[] ppiCouplage;
	ppiCouplage = nullptr;
	uiCONNombreCouplage = 0;	
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

unsigned int CControleurParseurCouplage::CONLireNombreCouplage()
{
	return uiCONNombreCouplage;
}

/******************************************************************************************************
**** Entrées :																					   ****
**** Nécessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entraîne : Renvoie le chemin d'accès au fichier de lecture									   ****
******************************************************************************************************/
int** CControleurParseurCouplage::CONLireCouplage()
{
	return ppiCouplage;
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

	//Récupération du nombre d'arcs
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

		throw CException(EXCArretProgramme);
	}
	
	//Récupération des arcs
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
		throw CException(EXCArretProgramme);
	}

	//Affectation Couplage
	
	ppiCouplage = ppiArcs;
}
