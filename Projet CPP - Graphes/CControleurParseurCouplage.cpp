#include "CControleurParseurCouplage.h"


/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	CControleurParseur																   ****
**** Entra�ne : La construction d'un objet CControleurParseur par d�faut						   ****
******************************************************************************************************/
CControleurParseurCouplage::CControleurParseurCouplage()
{
	pcCONChemin = nullptr;
	uiCONNombreCouplage = 0;
	ppiCouplage = nullptr;
}

/***********************************************************************************************************************
**** Entr�es : pcChemin : char*																						****
**** N�cessite :																		  							****
**** Sorties :	CControleurParseur																					****
**** Entra�ne : La construction d'un objet CControleurParseur poss�dant un chemin d'acc�s � un fichier de lecture	****
***********************************************************************************************************************/
CControleurParseurCouplage::CControleurParseurCouplage(char* pcChemin)
{
	pcCONChemin = pcChemin;
	uiCONNombreCouplage = 0;
	ppiCouplage = nullptr;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : La destruction de l'objet CControleurParseur									   ****
******************************************************************************************************/
CControleurParseurCouplage::~CControleurParseurCouplage()
{
	unsigned int uiboucle;
	pcCONChemin = nullptr;
	
	for (uiboucle = 0 ; uiboucle < uiCONNombreCouplage; uiboucle++)
	{
		delete[] ppiCouplage[uiboucle];
	}
	delete[] ppiCouplage;
	ppiCouplage = nullptr;
	uiCONNombreCouplage = 0;	
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
******************************************************************************************************/
char* CControleurParseurCouplage::CONLireChemin()
{
	return pcCONChemin;
}

/******************************************************************************************************
**** Entr�es : pcChemin : char*																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Modifie le chemin d'acc�s au fichier de lecture									   ****
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
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :	pcConChemin : char*																   ****
**** Entra�ne : Renvoie le chemin d'acc�s au fichier de lecture									   ****
******************************************************************************************************/
int** CControleurParseurCouplage::CONLireCouplage()
{
	return ppiCouplage;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Lis le fichier de lecture														   ****
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
		throw CException(EXCArretProgramme);
	}

	//Affectation Couplage
	uiCONNombreCouplage = uiNbArcs;
	ppiCouplage = ppiArcs;
}
