#ifndef COPGRAPHES

#pragma warning(disable : 6384)

#define COPGRAPHES
#define EXCTypeIncorrect 60
#define EXCPointeurCouplageNul 61
#define EXCPointeurGrapheNul 62
#define EXCCouplageVide 63


#include "CGraphe.h"
#include "CCouplage.h"

class CGrapheOperations {
	// Nous avons un ensemble de methodes en prive car elles ne servent que TestCouplage.
	// Il est donc inutile de les rendre public.
private:
	/******************************************************************************************************
	* Entrees : pCOUCouplage : CCouplage*															   ****
	* Necessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entraine : Deteremine si pCOUCouplage est bein un couplage									   ****
	******************************************************************************************************/
	bool COPEstUnCouplage(CCouplage * pCOUCouplage);

	/******************************************************************************************************
	* Entrees : pCOUCouplage : CCouplage*, piArcs : int*											   ****
	* Necessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entraine : Ajouter un arc au couplage pCOUCouplage											   ****
	******************************************************************************************************/
	CCouplage* COPAjouterArcAuCouplage(CCouplage* pCOUCouplage, int* piArcs);
	
	/******************************************************************************************************
	* Entrees : pGRAGraphe : CGraphe*, pCOUCouplage : CCouplage*									   ****
	* Necessite :																			  	       ****
	* Sorties : CCouplage* : Ensemble d'arcs complementaire											   ****
	* Entraine : Genere l'ensemble des arcs du graphe prives de ceux du couplage					   ****
	******************************************************************************************************/
	CCouplage* COPComplementaireCouplage(CGraphe* pGRAGraphe, CCouplage* pCOUCouplage);

	/******************************************************************************************************
	* Entrees : pCOUCouplage : CCouplage*, piArcATester : int*										   ****
	* Necessite :																			  	       ****
	* Sorties : bool																				   ****
	* Entraine : Dit si l'arc passe en parametre est bien dans l'ensemble pCOUCouplage				   ****
	******************************************************************************************************/
	bool COPEstDansEnsembleArcs(CCouplage* pCOUCouplage, int* piArcATester);

public:

	/******************************************************************************************************
	**** Entrées : pGRAParam : CGraphe*																   ****
	**** Nécessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entraîne : Crée un nouvel objet CGraphe inverse à pGRAParam								   ****
	******************************************************************************************************/
	CGraphe* COPInversion(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entrees : pGRAParam : CGraphe*																   ****
	**** Necessite :																		  	       ****
	**** Sorties : pGRARetour : CGraphe*															   ****
	**** Entraine : Cr�e un nouvel objet CGraphe en copiant pGRAParam mais �tant non-orient�		   ****
	******************************************************************************************************/
	CGraphe* COPNonOriente(const CGraphe* pGRAParam) const;

	/******************************************************************************************************
	**** Entrees : pGRAGraphe : CGraphe*, pCOUCouplage : CCouplage*									   ****
	**** Necessite :																		  	       ****
	**** Sorties : bool																				   ****
	**** Entraine : Determine si le couplage pCOUCouplage est de taille maximale					   ****
	******************************************************************************************************/
	bool COPTestCouplage(CGraphe* pGRAGraphe, CCouplage* pCOUCouplage);

};

#endif