#pragma once
#ifndef COPGRAPHES
#define COPGRAPHES

#include "CGraphe.h"

class CGrapheOperations {
public:

	/******************************************************************************************************
	**** Entr�es : pGRAParam : CGraphe*																   ****
	**** N�cessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entra�ne : Cr�e un nouvel objet CGraphe inverse � pGRAParam								   ****
	******************************************************************************************************/
	CGraphe* GRAInversion(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entr�es : pGRAParam : CGraphe*																   ****
	**** N�cessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entra�ne : Cr�e un nouvel objet CGraphe en copiant pGRAParam mais �tant non-orient�		   ****
	******************************************************************************************************/
	CGraphe* GRANonOriente(const CGraphe* pGRAParam) const;
};

#endif