#ifndef COPGRAPHES

#pragma warning(disable : 6384)

#define COPGRAPHES
#define EXCTypeIncorrect 60

#include "CGraphe.h"
#include "CCouplage.h"

class CGrapheOperations {
private:
	/******************************************************************************************************
	* Entr�es : ppiArcs : int**																		   ****
	* N�cessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entra�ne : Deteremine si ppiArcs est un couplage												   ****
	******************************************************************************************************/
	bool COPEstUnCouplage(CCouplage * pCOUCouplage);

	/******************************************************************************************************
	* Entr�es : ppiArcs : int**, piArcs : int*														   ****
	* N�cessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entra�ne : Ajouter un arc au couplage ppiArcs													   ****
	******************************************************************************************************/
	CCouplage* COPAjouterArcAuCouplage(CCouplage* pCOUCouplage, int* piArcs);
	
	CCouplage* COPComplementaireCouplage(CGraphe* pGRAGraphe, CCouplage* pCOUCouplage);

	bool COPEstDansEnsembleArcs(CCouplage* pCOUCouplage, int* piArcATester);

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
	**** Entra�ne : Determine si le couplage ppARCArcs est de taille maximale						   ****
	******************************************************************************************************/
	bool COPTestCouplage(CGraphe* pGRAGraphe, CCouplage* pCOUCouplage);

};

#endif