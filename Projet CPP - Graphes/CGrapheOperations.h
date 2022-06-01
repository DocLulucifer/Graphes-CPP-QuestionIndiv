#ifndef COPGRAPHES

#pragma warning(disable : 6384)

#define COPGRAPHES
#define EXCTypeIncorrect 60

#include "CGraphe.h"

class CGrapheOperations {
public:

	/******************************************************************************************************
	**** Entrées : pGRAParam : CGraphe*																   ****
	**** Nécessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entraîne : Crée un nouvel objet CGraphe inverse à pGRAParam								   ****
	******************************************************************************************************/
	CGraphe* COPInversion(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entrées : pGRAParam : CGraphe*																   ****
	**** Nécessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entraîne : Crée un nouvel objet CGraphe en copiant pGRAParam mais étant non-orienté		   ****
	******************************************************************************************************/
	CGraphe* COPNonOriente(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entrées : pGRAGraphe : CGraphe*, ppARCArcs : CArc**										   ****
	**** Nécessite :																		  	       ****
	**** Sorties : bool																				   ****
	**** Entraîne : Determine si le couplage ppARCArcs est de taille maximale						   ****
	******************************************************************************************************/
	bool COPTestCouplage(CGraphe* pGRAGraphe, int** ppiArcs);
	
	/******************************************************************************************************
	* Entrées : ppiArcs : int**																		   ****
	* Nécessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entraîne : Deteremine si ppiArcs est un couplage												   ****
	******************************************************************************************************/
	bool COPEstUnCouplage(int** ppiArcs);

	/******************************************************************************************************
	* Entrées : ppiArcs : int**, piArcs : int*														   ****
	* Nécessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entraîne : Ajouter un arc au couplage ppiArcs													   ****
	******************************************************************************************************/
	int ** COPAjouterArcAuCouplage(int** ppiArcs, int* piArcs);
	
	int** COPComplementaireCouplage(CGraphe* pGRAGraphe, int** ppiArcs);

	bool COPEstDansEnsembleArcs(int** ppiEnsembleArcs, int* piArcATester);
};

#endif