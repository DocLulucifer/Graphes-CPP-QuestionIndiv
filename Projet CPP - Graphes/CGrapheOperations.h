#pragma once
#ifndef COPGRAPHES
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
	**** Entraîne : Determine si le coupage ppARCArcs est de taille maximale						   ****
	******************************************************************************************************/
	bool COPTestCouplage(CGraphe* pGRAGraphe, int** ppARCArcs);
	
	bool COPEstUnCouplage(int** ppARCArcs);
};

#endif