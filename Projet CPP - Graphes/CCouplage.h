#ifndef COUPLAGE
#define COUPLAGE

#pragma warning(disable : 6001)
#pragma warning(disable : 6386)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "CException.h"

#define EXCSuppArcCouplageImpossible 70
#define EXCPointeurAjoutArcNul 71

using namespace std;

class CCouplage {
private:
	// Attributs
		// Tableau des arcs
	int** ppiArcs;
	
		// Nombre d'arcs
	unsigned int uiNbArcs;
public:
	// Constructeurs
	
	/******************************************************************************************************
	* Entrees : 																					   ****
	* Necessite :																			  	       ****
	* Sorties : 																					   ****
	* Entraine : Genere un objet CCouplage par defaut												   ****
	******************************************************************************************************/
	CCouplage();
	
	/******************************************************************************************************
	* Entrees : COUCouplage : CCouplage&															   ****
	* Necessite : Un objet CCouplage a recopier												  	       ****
	* Sorties : 																					   ****
	* Entraine : Genere un objet CCouplage par recopie												   ****
	******************************************************************************************************/
	CCouplage(CCouplage& COUCouplage);
	
	/******************************************************************************************************
	* Entrees : 																					   ****
	* Necessite :																			  	       ****
	* Sorties : 																					   ****
	* Entraine : Destruction d'un objet CCouplage													   ****
	******************************************************************************************************/
	~CCouplage();

	// Accesseurs
	
	/******************************************************************************************************
	* Entrees : uiIndice1 : unsigned int, uiIndice2 : unsigned int									   ****
	* Necessite :																			  	       ****
	* Sorties : int	: une valeur du tableau d'arcs													   ****
	* Entraine : 																					   ****
	******************************************************************************************************/
	int COULireValeur(unsigned int uiIndice1, unsigned int uiIndice2);
	
	/******************************************************************************************************
	* Entrees :																						   ****
	* Necessite :																			  	       ****
	* Sorties : int	: Le nombre d'arcs contenus														   ****
	* Entraine : 																					   ****
	******************************************************************************************************/
	unsigned int COULireNbArcs();
	
	// Modifieurs
	
	/******************************************************************************************************
	* Entrees : uiIndice1 : unsigned int, uiIndice2 : unsigned int, iVAleur : int					   ****
	* Necessite :																			  	       ****
	* Sorties :																						   ****
	* Entraine : La modification d'une valeur du tableau d'arcs										   ****
	******************************************************************************************************/
	void COUEcritureValeur(unsigned int uiIndice1, unsigned int uiIndice2, int iValeur);
	
	/******************************************************************************************************
	* Entrees : piArcs : int*																		   ****
	* Necessite :																			  	       ****
	* Sorties :																						   ****
	* Entraine : L'ajout d'un arc au tableau d'arcs													   ****
	******************************************************************************************************/
	void COUAjouterArc(int* piArc);

	/******************************************************************************************************
	* Entrees : uiIndice : unsigned int																   ****
	* Necessite :																			  	       ****
	* Sorties :																						   ****
	* Entraine : La suppression d'un arc du tableau d'arcs											   ****
	******************************************************************************************************/
	void COUSupprimerArc(unsigned int uiIndice);

	// Methodes

	/******************************************************************************************************
	* Entrees : 																					   ****
	* Necessite :																			  	       ****
	* Sorties :																						   ****
	* Entraine : L'affichage dans la console du tableau d'arc										   ****
	******************************************************************************************************/
	void COUAfficherCouplage();
	
	// Operateurs
	
	/******************************************************************************************************
	* Entrees : COUCouplage : CCouplage&															   ****
	* Necessite :																			  	       ****
	* Sorties :	this : CCouplage&																	   ****
	* Entraine : L'affectation à l'objet des valeurs de l'objet passé en parametre					   ****
	******************************************************************************************************/
	CCouplage& operator=(CCouplage& COUCouplage);
};



#endif // !COUPLAGE
