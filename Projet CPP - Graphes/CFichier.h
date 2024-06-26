#ifndef FIC
#define FIC
#include "CGraphe.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cctype>

#define STR_LENGTH 1024
#define MAX_LOOPING 10000

#define EXCCheminNul 1
#define EXCFichierNonOuvert 2
#define EXCParserPointeurNul 3
#define EXCTokenNulMinuscule 4
#define EXCTokenNulSuppChar 5
#define EXCBoucleInfinie 6
#define EXCLigneNulle 7
#define EXCBaliseIncorrecte 8
#define EXCMiseEnFormeIncorecte 9
#define EXCValeurNeg 10
#define EXCNbLigneIns 11

using namespace std;

class CFichier {
private:
	//Flot de lecture du fichier
	ifstream IFSFICFichier;

public:
	//Constructeurs et Destructeur

	/******************************************************************************************************
	**** Entr�es : 																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un object Cfichier par d�faut									   ****
	******************************************************************************************************/
	CFichier();

	/******************************************************************************************************
	**** Entr�es : 	char * pcChemin																	   ****
	**** N�cessite : pcChemin non nul comme chemin du fichier � lire						  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un object Cfichier par d�faut									   ****
	******************************************************************************************************/
	CFichier(char* pcChemin);

	/******************************************************************************************************
	**** Entr�es : 																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Destruction de l'objet CFichier par d�faut										   ****
	******************************************************************************************************/
	~CFichier();

	//Modifieur

	/******************************************************************************************************
	**** Entr�es : pcChemin : char*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Initialise le flot de lecture du fichier										   ****
	******************************************************************************************************/
	void FICInitialiserFlot(char* pcChemin);

	//Parseur

	/******************************************************************************************************
	**** Entr�es : pcTag : char*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	uiValeurRetournee : unsigned int												   ****
	**** Entra�ne : Renvoie le chiffre lu dans le fichier correspondant au tag						   ****
	******************************************************************************************************/
	unsigned int FICLireChiffre(char* pcTag);

	/******************************************************************************************************
	**** Entr�es : uiNbLignes : unsigned int, pcTag1 : char*, pcTag2 : char*						   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	piValeursRetour : int*															   ****
	**** Entra�ne : Parse les �l�ments de plusieurs lignes (1 seul �l�ment sur la ligne)			   ****
	******************************************************************************************************/
	int* FICLireTabSansVirgule(const unsigned int uiNbLignes, char* pcTag1, char* pcTag2);

	/*************************************************************************************************************
	**** Entr�es : uiNbLignes : unsigned int, pcTag1 : char*, pcTag2 : char*, pcTag3 : char*				  ****
	**** N�cessite :																		  				  ****
	**** Sorties :	ppiValeursRetour : int**																  ****
	**** Entra�ne : Parse les �l�ments de plusieurs lignes (plusieurs �l�ments s�par�s par des virgules)	  ****
	*************************************************************************************************************/
	int** FICLireTabAvecVirgule(const unsigned int uiNbLignes, char* pcTag1, char* pcTag2, char* pcTag3);

	/***********************************************************************************************************************
	**** Entr�es : char* pcChaine, ifstream& fichier																    ****
	**** N�cessite : Un fichier ouvert et une chaine non nulle								  							****
	**** Sorties :																										****
	**** Entra�ne : Renvoie la chaine pcChaine pass�e en param�tre et dont tous les tabh et espaces sont supprim�s	    ****
	***********************************************************************************************************************/
	void FICLigneSuivante(char* pcLigne);

	//Fonctions de handle mauvaise mise en forme

	/***********************************************************************************************************************
	**** Entr�es : char* pcChaine																					    ****
	**** N�cessite :																		  							****
	**** Sorties :	char* pcChaine																						****
	**** Entra�ne : Renvoie la chaine pcChaine pass�e en param�tre et dont toutes les lettres sont pass�es en minuscule ****
	***********************************************************************************************************************/
	char * FICMinuscule(char* pcChaineMin);

	/******************************************************************************************************************
	**** Entr�es : char* pcChaine																				   ****
	**** N�cessite :																		  					   ****
	**** Sorties :																								   ****
	**** Entra�ne : Supprime un charact�re c d'une chaine de caract�re pcChaine pass�e en param�tre				   ****
	******************************************************************************************************************/
	void FICSupp_char(char* pcChaine, const char cCaractere);

	/******************************************************************************************************************
	**** Entr�es : pcToken : char*, pcNomBalise : char*															   ****
	**** N�cessite :																		  					   ****
	**** Sorties : bool																							   ****
	**** Entra�ne : Renvoie true si pcToken = pcNomBalise, false sinon											   ****
	******************************************************************************************************************/
	bool FICVerifBalise(char* pcToken, const char* pcNomBalise);
};


#endif