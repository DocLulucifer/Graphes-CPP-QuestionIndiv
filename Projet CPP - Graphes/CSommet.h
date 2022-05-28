#ifndef SOMMET
#define SOMMET

#pragma warning(disable : 6385)
#pragma warning(disable : 6386)

#include "CArc.h"
#include "CException.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

#define EXCSuppImpossible 40
#define EXCPointeurArcNul 41
#define EXCValeurArcIntrouvable 424222

class CSommet {
private :

	//Attributs
	int iSOMNumero;
	unsigned int uiSOMNbArcsSommetSortants;
	unsigned int uiSOMNbArcsSommetEntrants;
	CArc** ppARCSOMEntrant;
	CArc** ppARCSOMSortant;
public :

	//Constructeurs & Destructeurs

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : CSommet																			   ****
	**** Entra�ne : Cr�e un nouvel objet CSommet par d�faut											   ****
	******************************************************************************************************/
	CSommet() = delete;

	/******************************************************************************************************
	**** Entr�es :	SOMParam : CSommet&																   ****
	**** N�cessite :																		  	       ****
	**** Sorties : CSommet																			   ****
	**** Entra�ne : Cr�e un nouvel objet CSommet par copie de SOMParam								   ****
	******************************************************************************************************/
	CSommet(const CSommet &SOMParam);

	/******************************************************************************************************
	**** Entr�es : iNumero : int																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties : CSommet																			   ****
	**** Entra�ne : Cr�e un nouvel objet CSommet poss�dant le num�ro iNumero						   ****
	******************************************************************************************************/
	CSommet(int iNumero);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : 																					   ****
	**** Entra�ne : Destruction de l'objet CSommet par d�faut										   ****
	******************************************************************************************************/
	~CSommet();

	//Accesseurs

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : iSOMNumero : int																	   ****
	**** Entra�ne : Renvoie le num�ro du sommet														   ****
	******************************************************************************************************/
	int SOMLireNumero() const;

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : uiSOMNbArcsSommetEntrants : unsigned int											   ****
	**** Entra�ne : Renvoie le nombre d'arcs entrants du sommet										   ****
	******************************************************************************************************/
	unsigned int SOMLireNbArcsEntrants() const;
	unsigned int SOMLireNbArcsSortants() const;
	const CArc * const* SOMLireArcsSortants() const;
	const CArc * const* SOMLireArcsEntrants() const;

	//Modifieurs
	void SOMModifierNumero(int iNumero);
	void SOMAjouterArcEntrant(CArc* pARCArc);
	void SOMSupprimerArcEntrant(CArc* pARCArc);
	void SOMAjouterArcSortant(CArc* pARCArc);
	void SOMSupprimerArcSortant(CArc* pARCArc);

	//M�thodes
	const CArc* SOMRechercheArc(int iDestination, int iParam) const;

	//Surcharge
	CSommet& operator=(const CSommet SOMSommet);

};

#endif