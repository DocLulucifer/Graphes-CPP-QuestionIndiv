#include "CSommet.h"


#pragma warning(disable : 6308)

using namespace std;

/******************************************************************************************************
**** Entr�es :	SOMParam : CSommet&																   ****
**** N�cessite :																		  	       ****
**** Sorties : CSommet																			   ****
**** Entra�ne : Cr�e un nouvel objet CSommet par copie de SOMParam								   ****
******************************************************************************************************/
CSommet::CSommet(const CSommet& SOMParam)
{
    unsigned int uiboucle1;

    iSOMNumero = SOMParam.SOMLireNumero();
    uiSOMNbArcsSommetEntrants = SOMParam.SOMLireNbArcsEntrants();
    uiSOMNbArcsSommetSortants = SOMParam.SOMLireNbArcsSortants();
    
	//Allocation de la memoire pour les arcs entrants et sortants
    ppARCSOMEntrant = new CArc * [uiSOMNbArcsSommetEntrants];
    ppARCSOMSortant = new CArc * [uiSOMNbArcsSommetSortants];

	//Allocation du sous-tableau de sommets avec les valeurs par recopie
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetEntrants; uiboucle1++) {
        ppARCSOMEntrant[uiboucle1] = new CArc(*SOMParam.SOMLireArcsEntrants()[uiboucle1]);
    }
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetSortants; uiboucle1++) {
        ppARCSOMSortant[uiboucle1] = new CArc(*SOMParam.SOMLireArcsSortants()[uiboucle1]);
    }
}


/******************************************************************************************************
**** Entr�es : iNumero : int																	   ****
**** N�cessite :																		  	       ****
**** Sorties : CSommet																			   ****
**** Entra�ne : Cr�e un nouvel objet CSommet poss�dant le num�ro iNumero						   ****
******************************************************************************************************/
CSommet::CSommet(int iNumero)
{
    iSOMNumero = iNumero;

    uiSOMNbArcsSommetEntrants = 0;
    uiSOMNbArcsSommetSortants = 0;

    ppARCSOMEntrant = nullptr;
    ppARCSOMSortant = nullptr;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : 																					   ****
**** Entra�ne : Destruction de l'objet CSommet par d�faut										   ****
******************************************************************************************************/
CSommet::~CSommet()
{
    unsigned int uiboucle;
	
	//Lib�ration de la memoire des arcs entrants
    if (ppARCSOMEntrant != nullptr) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants(); uiboucle++) {
            delete ppARCSOMEntrant[uiboucle];
            ppARCSOMEntrant[uiboucle] = nullptr;
        }
        delete[] ppARCSOMEntrant;
        ppARCSOMEntrant = nullptr;
    }

	//Lib�ration de la memoire des arcs sortants
    if (ppARCSOMSortant != nullptr) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants(); uiboucle++) {
            delete ppARCSOMSortant[uiboucle];
            ppARCSOMSortant[uiboucle] = nullptr;
        }
        delete[] ppARCSOMSortant;
        ppARCSOMSortant = nullptr;
    }
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : iSOMNumero : int																	   ****
**** Entra�ne : Renvoie le num�ro du sommet														   ****
******************************************************************************************************/
int CSommet::SOMLireNumero() const
{
    return iSOMNumero;
}


/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : uiSOMNbArcsSommetEntrants : unsigned int											   ****
**** Entra�ne : Renvoie le nombre d'arcs entrants du sommet										   ****
******************************************************************************************************/
unsigned int CSommet::SOMLireNbArcsEntrants() const
{
    return uiSOMNbArcsSommetEntrants;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : uiSOMNbArcsSommetSortants : unsigned int											   ****
**** Entra�ne : Renvoie le nombre d'arcs sortants du sommet										   ****
******************************************************************************************************/
unsigned int CSommet::SOMLireNbArcsSortants() const
{
    return uiSOMNbArcsSommetSortants;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : ppARCSOMSortants : CArc**														   ****
**** Entra�ne : Renvoie la liste des arcs sortants												   ****
******************************************************************************************************/
const CArc* const* CSommet::SOMLireArcsSortants() const
{
    return ppARCSOMSortant;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : ppARCSOMEntrants : CArc**														   ****
**** Entra�ne : Renvoie la liste des arcs entrants												   ****
******************************************************************************************************/
const CArc* const* CSommet::SOMLireArcsEntrants() const
{
    return ppARCSOMEntrant;
}

/******************************************************************************************************
**** Entr�es : iNumero : int																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Modifie le num�ro du sommet														   ****
******************************************************************************************************/
void CSommet::SOMModifierNumero(int iNumero)
{
    iSOMNumero = iNumero;
}

/******************************************************************************************************
**** Entr�es : pARCArc : CArc*																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Ajoute CArc dans la liste des arcs entrants du sommet							   ****
******************************************************************************************************/
void CSommet::SOMAjouterArcEntrant(CArc* pARCArc)
{
	if (pARCArc == nullptr) {
		throw CException(EXCPointeurArcNul);
	}
    unsigned int uiboucle1;
	
	//Allocation d'un nouveau tableau de pointeurs de arcs temporaire
    CArc** ppARCSOMEntranttmp = new CArc * [uiSOMNbArcsSommetEntrants + 1];
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetEntrants + 1; uiboucle1++) {
        ppARCSOMEntranttmp[uiboucle1] = new CArc;
    }

	//Copie des arcs entrants dans le nouveau tableau et ajout de l'arc � ajouter � la fin de ce tableau
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetEntrants + 1; uiboucle1++) {
        if (uiboucle1 < uiSOMNbArcsSommetEntrants) {
            *ppARCSOMEntranttmp[uiboucle1] = *ppARCSOMEntrant[uiboucle1];
        }
        else {
            *ppARCSOMEntranttmp[uiboucle1] = *pARCArc;
        }
    }

	//Lib�ration de la m�moire des arcs entrants (Ancien tableau)
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetEntrants; uiboucle1++) {
        delete ppARCSOMEntrant[uiboucle1];
        ppARCSOMEntrant[uiboucle1] = nullptr;
    }
    delete[] ppARCSOMEntrant;
    ppARCSOMEntrant = ppARCSOMEntranttmp;
	
	uiSOMNbArcsSommetEntrants++;

}

/******************************************************************************************************
**** Entr�es : pARCArc : CArc*																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Supprime CArc dans la liste des arcs entrants du sommet							   ****
******************************************************************************************************/
void CSommet::SOMSupprimerArcEntrant(CArc* pARCArc)
{
	if (pARCArc == nullptr) {
		throw CException(EXCPointeurArcNul);
	}
    if (uiSOMNbArcsSommetEntrants == 0) {
        throw CException(EXCSuppImpossible);
    }
	
    unsigned int uiboucle, uiArcTrouve = 0;
	
	//Allocation d'un nouveau tableau de pointeurs de arcs temporaire
    CArc** ppARCSOMEntranttmp = new CArc * [uiSOMNbArcsSommetEntrants - 1];
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetEntrants - 1; uiboucle++) {
        ppARCSOMEntranttmp[uiboucle] = new CArc;
    }

	//Suppression de l'arc � supprimer
	for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() - 1; uiboucle++) {
		if (SOMLireArcsEntrants()[uiboucle] == pARCArc) {
			uiArcTrouve = 1;
            delete ppARCSOMEntrant[uiboucle];
		}

		ppARCSOMEntrant[uiboucle] = ppARCSOMEntrant[uiboucle + uiArcTrouve];
	}

	//Copie des arcs entrants dans le nouveau tableau
    for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants() - 1; uiboucle++) {
        *ppARCSOMEntranttmp[uiboucle] = *ppARCSOMEntrant[uiboucle];
    }

	//Lib�ration de la m�moire des arcs entrants (Ancien tableau)
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetEntrants; uiboucle++) {
        delete ppARCSOMEntrant[uiboucle];
        ppARCSOMEntrant[uiboucle] = nullptr;
    }
    delete[] ppARCSOMEntrant;
    ppARCSOMEntrant = ppARCSOMEntranttmp;
	uiSOMNbArcsSommetEntrants--;
    
}

/******************************************************************************************************
**** Entr�es : pARCArc : CArc*																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Ajoute CArc dans la liste des arcs sortants du sommet							   ****
******************************************************************************************************/
void CSommet::SOMAjouterArcSortant(CArc* pARCArc)
{
	if (pARCArc == nullptr) {
		throw CException(EXCPointeurArcNul);
	}
	
    unsigned int uiboucle1;
	
	//Allocation d'un nouveau tableau de pointeurs de arcs temporaire
    CArc** ppARCSOMSortanttmp = new CArc * [uiSOMNbArcsSommetSortants + 1];
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetSortants + 1; uiboucle1++) {
        ppARCSOMSortanttmp[uiboucle1] = new CArc;
    }

	//Copie des arcs sortants dans le nouveau tableau et ajout de l'arc � ajouter � la fin de ce tableau
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetSortants + 1; uiboucle1++) {
        if (uiboucle1 < uiSOMNbArcsSommetSortants) {
            *ppARCSOMSortanttmp[uiboucle1] = *ppARCSOMSortant[uiboucle1];
        }
        else {
            *ppARCSOMSortanttmp[uiboucle1] = *pARCArc;
        }
    }

	//Lib�ration de la m�moire des arcs sortants (Ancien tableau)
    for (uiboucle1 = 0; uiboucle1 < uiSOMNbArcsSommetSortants; uiboucle1++) {
        delete ppARCSOMSortant[uiboucle1];
        ppARCSOMSortant[uiboucle1] = nullptr;
    }
    delete[] ppARCSOMSortant;
    ppARCSOMSortant = ppARCSOMSortanttmp;

    uiSOMNbArcsSommetSortants++;
}

/******************************************************************************************************
**** Entr�es : pARCArc : CArc*																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Supprime CArc dans la liste des arcs sortants du sommet							   ****
******************************************************************************************************/
void CSommet::SOMSupprimerArcSortant(CArc* pARCArc)
{
    if (uiSOMNbArcsSommetSortants == 0) {
        throw CException(EXCSuppImpossible);
    }
	if (pARCArc == nullptr) {
		throw CException(EXCPointeurArcNul);
	}
	
    unsigned int uiboucle, uiArcTrouve = 0;

	//Allocation d'un nouveau tableau de pointeurs de arcs temporaire
    CArc** ppARCSOMSortanttmp = new CArc * [uiSOMNbArcsSommetSortants - 1];
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetSortants - 1; uiboucle++) {
        ppARCSOMSortanttmp[uiboucle] = new CArc;
    }

	//Suppression de l'arc � supprimer
    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() - 1; uiboucle++) {
        if (SOMLireArcsSortants()[uiboucle] == pARCArc) {
            uiArcTrouve = 1;
            delete ppARCSOMSortant[uiboucle];
        }

        ppARCSOMSortant[uiboucle] = ppARCSOMSortant[uiboucle + uiArcTrouve];
    }

	//Copie des arcs sortants dans le nouveau tableau
    for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants() - 1; uiboucle++) {
        ppARCSOMSortanttmp[uiboucle] = ppARCSOMSortant[uiboucle];
    }

	//Lib�ration de la m�moire des arcs sortants (Ancien tableau)
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetSortants; uiboucle++) {
        delete ppARCSOMSortant[uiboucle];
        ppARCSOMSortant[uiboucle] = nullptr;
    }
    delete[] ppARCSOMSortant;
    ppARCSOMSortant = ppARCSOMSortanttmp;
    uiSOMNbArcsSommetSortants--;
}

/***************************************************************************************************************************
**** Entr�es : iDestination : int, iParam : int																			****
**** N�cessite :																		  								****
**** Sorties :																											****
**** Entra�ne : Recherche et renvoie l'arc d�sir� � partir de sa destination et du fait qu'il soit entrant ou sortant	****
***************************************************************************************************************************/
const CArc* CSommet::SOMRechercheArc(int iDestination, int iParam) const
{
    unsigned int uiboucle;

	//Sp�cification de si l'arc � trouver est dans le tableau des arcs entrants ou sortants
    if (iParam == entrant) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsEntrants(); uiboucle++) {
            if (SOMLireArcsEntrants()[uiboucle]->ARCLireDestination() == iDestination) {
                return SOMLireArcsEntrants()[uiboucle];
            }
        }
    }
    else if (iParam == sortant) {
        for (uiboucle = 0; uiboucle < SOMLireNbArcsSortants(); uiboucle++) {
            if (SOMLireArcsSortants()[uiboucle]->ARCLireDestination() == iDestination) {
                return SOMLireArcsSortants()[uiboucle];
            }
        }
    }
    return nullptr;
}

/******************************************************************************************************
**** Entr�es : SOMSommet : CSommet																   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Cr�e un nouvel objet CSommet par copie de SOMSommet								   ****
******************************************************************************************************/
CSommet& CSommet::operator=(const CSommet SOMSommet)
{
    unsigned int uiboucle;

    iSOMNumero = SOMSommet.SOMLireNumero();
    
    CArc** ppARCSOMEntrantTMP = new CArc * [SOMSommet.SOMLireNbArcsEntrants()];
    CArc** ppARCSOMSortantTMP = new CArc * [SOMSommet.SOMLireNbArcsSortants()];
	
    //Copie par duplication des objets
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetEntrants; uiboucle++) {
        ppARCSOMEntrant[uiboucle] = new CArc(*SOMSommet.SOMLireArcsEntrants()[uiboucle]);
    }
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetSortants; uiboucle++) {
        ppARCSOMSortant[uiboucle] = new CArc(*SOMSommet.SOMLireArcsSortants()[uiboucle]);
    }

	//Lib�ration de la m�moire des arcs (Ancien tableau)
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetEntrants; uiboucle++) {
        delete ppARCSOMEntrant[uiboucle];
        ppARCSOMEntrant[uiboucle] = nullptr;
    }
    for (uiboucle = 0; uiboucle < uiSOMNbArcsSommetSortants; uiboucle++) {
        delete ppARCSOMSortant[uiboucle];
        ppARCSOMSortant[uiboucle] = nullptr;
    }
    delete[] ppARCSOMEntrant;
    delete[] ppARCSOMSortant;

    uiSOMNbArcsSommetEntrants = SOMSommet.SOMLireNbArcsEntrants();
    uiSOMNbArcsSommetSortants = SOMSommet.SOMLireNbArcsSortants();

    ppARCSOMEntrant = ppARCSOMEntrantTMP;
    ppARCSOMSortant = ppARCSOMSortantTMP;

    return *this;
}
