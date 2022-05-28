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

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : uiSOMNbArcsSommetSortants : unsigned int											   ****
	**** Entra�ne : Renvoie le nombre d'arcs sortants du sommet										   ****
	******************************************************************************************************/
	unsigned int SOMLireNbArcsSortants() const;

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : ppARCSOMSortants : CArc**														   ****
	**** Entra�ne : Renvoie la liste des arcs sortants												   ****
	******************************************************************************************************/
	const CArc * const* SOMLireArcsSortants() const;

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : ppARCSOMEntrants : CArc**														   ****
	**** Entra�ne : Renvoie la liste des arcs entrants												   ****
	******************************************************************************************************/
	const CArc * const* SOMLireArcsEntrants() const;

	//Modifieurs

	/******************************************************************************************************
	**** Entr�es : iNumero : int																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Modifie le num�ro du sommet														   ****
	******************************************************************************************************/
	void SOMModifierNumero(int iNumero);

	/******************************************************************************************************
	**** Entr�es : pARCArc : CArc*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Ajoute CArc dans la liste des arcs entrants du sommet							   ****
	******************************************************************************************************/
	void SOMAjouterArcEntrant(CArc* pARCArc);

	/******************************************************************************************************
	**** Entr�es : pARCArc : CArc*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Supprime CArc dans la liste des arcs entrants du sommet							   ****
	******************************************************************************************************/
	void SOMSupprimerArcEntrant(CArc* pARCArc);

	/******************************************************************************************************
	**** Entr�es : pARCArc : CArc*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Ajoute CArc dans la liste des arcs sortants du sommet							   ****
	******************************************************************************************************/
	void SOMAjouterArcSortant(CArc* pARCArc);

	/******************************************************************************************************
	**** Entr�es : pARCArc : CArc*																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Supprime CArc dans la liste des arcs sortants du sommet							   ****
	******************************************************************************************************/
	void SOMSupprimerArcSortant(CArc* pARCArc);

	//M�thodes

	/***************************************************************************************************************************
	**** Entr�es : iDestination : int, iParam : int																			****
	**** N�cessite :																		  								****
	**** Sorties :																											****
	**** Entra�ne : Recherche et renvoie l'arc d�sir� � partir de sa destination et du fait qu'il soit entrant ou sortant	****
	***************************************************************************************************************************/
	const CArc* SOMRechercheArc(int iDestination, int iParam) const;

	//Surcharge

	/******************************************************************************************************
	**** Entr�es : SOMSommet : CSommet																   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Cr�e un nouvel objet CSommet par copie de SOMSommet								   ****
	******************************************************************************************************/
	CSommet& operator=(const CSommet SOMSommet);

};

#endif