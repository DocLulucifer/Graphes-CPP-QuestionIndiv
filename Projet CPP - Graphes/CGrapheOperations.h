#ifndef COPGRAPHES

#pragma warning(disable : 6384)

#define COPGRAPHES
#define EXCTypeIncorrect 60

#include "CGraphe.h"

class CGrapheOperations {
private:
	/******************************************************************************************************
	* Entr�es : ppiArcs : int**																		   ****
	* N�cessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entra�ne : Deteremine si ppiArcs est un couplage												   ****
	******************************************************************************************************/
	bool COPEstUnCouplage(int** ppiArcs);

	/******************************************************************************************************
	* Entr�es : ppiArcs : int**, piArcs : int*														   ****
	* N�cessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entra�ne : Ajouter un arc au couplage ppiArcs													   ****
	******************************************************************************************************/
	int ** COPAjouterArcAuCouplage(int** ppiArcs, int* piArcs);
	
	int** COPComplementaireCouplage(CGraphe* pGRAGraphe, int** ppiArcs);

	bool COPEstDansEnsembleArcs(int** ppiEnsembleArcs, int* piArcATester);

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
	bool COPTestCouplage(CGraphe* pGRAGraphe, int** ppiArcs);
};

#endif