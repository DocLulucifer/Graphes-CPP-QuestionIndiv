#pragma once
#ifndef COPGRAPHES
#define COPGRAPHES
#define EXCTypeIncorrect 60

#include "CGraphe.h"

class CGrapheOperations {
public:

	/******************************************************************************************************
	**** Entr�es : pGRAParam : CGraphe*																   ****
	**** N�cessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entra�ne : Cr�e un nouvel objet CGraphe inverse � pGRAParam								   ****
	******************************************************************************************************/
	CGraphe* COPInversion(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entr�es : pGRAParam : CGraphe*																   ****
	**** N�cessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entra�ne : Cr�e un nouvel objet CGraphe en copiant pGRAParam mais �tant non-orient�		   ****
	******************************************************************************************************/
	CGraphe* COPNonOriente(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entr�es : pGRAGraphe : CGraphe*, ppARCArcs : CArc**										   ****
	**** N�cessite :																		  	       ****
	**** Sorties : bool																				   ****
	**** Entra�ne : Determine si le coupage ppARCArcs est de taille maximale						   ****
	******************************************************************************************************/
	bool COPTestCouplage(CGraphe* pGRAGraphe, int** ppARCArcs);
	
	bool COPEstUnCouplage(int** ppARCArcs);
};

#endif