#include "CCouplage.h"

/******************************************************************************************************
* Entrees : 																					   ****
* Necessite :																			  	       ****
* Sorties : 																					   ****
* Entraine : Genere un objet CCouplage par defaut												   ****
******************************************************************************************************/
CCouplage::CCouplage()
{
	ppiArcs = nullptr;
	uiNbArcs = 0;
}

/******************************************************************************************************
* Entrees : COUCouplage : CCouplage&															   ****
* Necessite : Un objet CCouplage a recopier												  	       ****
* Sorties : 																					   ****
* Entraine : Genere un objet CCouplage par recopie												   ****
******************************************************************************************************/
CCouplage::CCouplage(CCouplage& COUCouplage)
{
	unsigned int uiboucle;
	ppiArcs = new int* [COUCouplage.COULireNbArcs()];
	for (uiboucle = 0; uiboucle < COUCouplage.COULireNbArcs(); uiboucle++) {
		ppiArcs[uiboucle] = new int[2];
	}


	for (uiboucle = 0; uiboucle < COUCouplage.COULireNbArcs(); uiboucle++) {
		ppiArcs[uiboucle][0] = COUCouplage.COULireValeur(uiboucle, 0);
		ppiArcs[uiboucle][1] = COUCouplage.COULireValeur(uiboucle, 1);
	}
	uiNbArcs = COUCouplage.COULireNbArcs();
}

/******************************************************************************************************
* Entrees : 																					   ****
* Necessite :																			  	       ****
* Sorties : 																					   ****
* Entraine : Destruction d'un objet CCouplage													   ****
******************************************************************************************************/
CCouplage::~CCouplage()
{
	unsigned int uiboucle;
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;
	uiNbArcs = 0;
}

/******************************************************************************************************
* Entrees : uiIndice1 : unsigned int, uiIndice2 : unsigned int									   ****
* Necessite :																			  	       ****
* Sorties : int	: une valeur du tableau d'arcs													   ****
* Entraine : 																					   ****
******************************************************************************************************/
int CCouplage::COULireValeur(unsigned int uiIndice1, unsigned int uiIndice2)
{
	if (!(uiIndice1 < uiNbArcs && uiIndice2 < 2)) {
		throw CException(EXCErreurSegmentation);
	}
	return ppiArcs[uiIndice1][uiIndice2];
}

/******************************************************************************************************
* Entrees :																						   ****
* Necessite :																			  	       ****
* Sorties : int	: Le nombre d'arcs contenus														   ****
* Entraine : 																					   ****
******************************************************************************************************/
void CCouplage::COUEcritureValeur(unsigned int uiIndice1, unsigned int uiIndice2, int iValeur)
{
	if (!(uiIndice1 < uiNbArcs && uiIndice2 < 2)) {
		throw CException(EXCErreurSegmentation);
	}
	ppiArcs[uiIndice1][uiIndice2] = iValeur;
}

/******************************************************************************************************
* Entrees : uiIndice1 : unsigned int, uiIndice2 : unsigned int, iVAleur : int					   ****
* Necessite :																			  	       ****
* Sorties :																						   ****
* Entraine : La modification d'une valeur du tableau d'arcs										   ****
******************************************************************************************************/
unsigned int CCouplage::COULireNbArcs()
{
	return uiNbArcs;
}

/******************************************************************************************************
* Entrees : piArcs : int*																		   ****
* Necessite :																			  	       ****
* Sorties :																						   ****
* Entraine : L'ajout d'un arc au tableau d'arcs													   ****
******************************************************************************************************/
void CCouplage::COUAjouterArc(int* piArc)
{
	if (piArc == nullptr) {
		throw CException(EXCPointeurAjoutArcNul);
	}
	unsigned int uiboucle;
	int** ppiNouveau = new int* [uiNbArcs + 1];
	for (uiboucle = 0; uiboucle < uiNbArcs + 1; uiboucle++) {
		ppiNouveau[uiboucle] = new int[2];
	}
	
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		ppiNouveau[uiboucle][0] = ppiArcs[uiboucle][0];
		ppiNouveau[uiboucle][1] = ppiArcs[uiboucle][1];
	}
	
	ppiNouveau[uiNbArcs][0] = piArc[0];
	ppiNouveau[uiNbArcs][1] = piArc[1];

	for (uiboucle = 0 ; uiboucle < uiNbArcs; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;
	uiNbArcs++;
	ppiArcs = ppiNouveau;
}

/******************************************************************************************************
* Entrees : uiIndice : unsigned int																   ****
* Necessite :																			  	       ****
* Sorties :																						   ****
* Entraine : La suppression d'un arc du tableau d'arcs											   ****
******************************************************************************************************/
void CCouplage::COUSupprimerArc(unsigned int uiIndice)
{
	if (!(uiIndice < uiNbArcs)) {
		throw CException(EXCSuppArcCouplageImpossible);
	}
	int** ppiNouveau = new int* [uiNbArcs - 1];
	unsigned int uiboucle, uiArcTrouve = 0;
	for (uiboucle = 0; uiboucle < uiboucle - 1; uiboucle++) {
		ppiNouveau[uiboucle] = new int[2];
	}

	for (uiboucle = 0; uiboucle < uiNbArcs - 1; uiboucle++) {
		if (uiboucle == uiIndice) {
			uiArcTrouve++;
		}
		ppiNouveau[uiboucle][0] = ppiArcs[uiboucle + uiArcTrouve][0];
		ppiNouveau[uiboucle][1] = ppiArcs[uiboucle + uiArcTrouve][1];
	}
	
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;
	uiNbArcs--;
	ppiArcs = ppiNouveau;
}

/******************************************************************************************************
* Entrees : 																					   ****
* Necessite :																			  	       ****
* Sorties :																						   ****
* Entraine : L'affichage dans la console du tableau d'arc										   ****
******************************************************************************************************/
CCouplage& CCouplage::operator=(CCouplage& COUCouplage)
{
	unsigned int uiboucle;
	
	if(uiNbArcs != COUCouplage.COULireNbArcs())
	{
		for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
			delete[] ppiArcs[uiboucle];
		}
		delete[] ppiArcs;
		uiNbArcs = COUCouplage.COULireNbArcs();
		ppiArcs = new int* [uiNbArcs];
		for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
			ppiArcs[uiboucle] = new int[2];
		}
	}
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		ppiArcs[uiboucle][0] = COUCouplage.COULireValeur(uiboucle, 0);
		ppiArcs[uiboucle][1] = COUCouplage.COULireValeur(uiboucle, 1);
	}
	
	return *this;
}

/******************************************************************************************************
* Entrees : COUCouplage : CCouplage&															   ****
* Necessite :																			  	       ****
* Sorties :	this : CCouplage&																	   ****
* Entraine : L'affectation à l'objet des valeurs de l'objet passé en parametre					   ****
******************************************************************************************************/
void CCouplage::COUAfficherCouplage()
{
	unsigned int uiboucle;
	
	cout << endl << "Cardinalite : " << uiNbArcs << endl << endl;
	
	cout << "Arcs : " << endl;

	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		cout << ppiArcs[uiboucle][0] << " <---> " << ppiArcs[uiboucle][1] << endl;
	}

	cout << endl;
}
