#include "CGrapheOperations.h"

/******************************************************************************************************
**** Entrées : pGRAParam : CGraphe*																   ****
**** Nécessite :																		  	       ****
**** Sorties : pGRARetour : CGraphe*															   ****
**** Entraîne : Crée un nouvel objet CGraphe inverse à pGRAParam								   ****
******************************************************************************************************/
CGraphe * CGrapheOperations::COPInversion(const CGraphe* GRAParam) const
{
	CGraphe* pGRARetour = new CGraphe();
	unsigned int uiboucle, uiboucle2;
	for (uiboucle = 0; uiboucle < GRAParam->GRALireNbSommet(); uiboucle++) {
		pGRARetour->GRAAjouterSommet(GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero());
	}

	for (uiboucle = 0; uiboucle < GRAParam->GRALireNbSommet(); uiboucle++) {
		for (uiboucle2 = 0; uiboucle2 < GRAParam->GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
			pGRARetour->GRAAjouterArc(GRAParam->GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination(), GRAParam->GRALireSommets()[uiboucle]->SOMLireNumero());
		}
	}
	return pGRARetour;
}

/******************************************************************************************************
**** Entrées : pGRAParam : CGraphe*																   ****
**** Nécessite :																		  	       ****
**** Sorties : pGRARetour : CGraphe*															   ****
**** Entraîne : Crée un nouvel objet CGraphe en copiant pGRAParam mais étant non-orienté		   ****
******************************************************************************************************/
CGraphe * CGrapheOperations::COPNonOriente(const CGraphe* pGRAParam) const
{
	CGraphe* pGRAGrapheRetour = new CGraphe(*pGRAParam);
	pGRAGrapheRetour->GRAModifierType(false);
	
	return pGRAGrapheRetour;
}

/******************************************************************************************************
**** Entrées : pGRAGraphe : CGraphe*, ppARCArcs : CArc**										   ****
**** Nécessite :																		  	       ****
**** Sorties : bool																				   ****
**** Entraîne : Determine si le coupage ppARCArcs est de taille maximale						   ****
******************************************************************************************************/
bool CGrapheOperations::COPTestCouplage(CGraphe* pGRAGraphe, int** ppARCArcs)
{
	if (pGRAGraphe->GRALireType() == true) {
		throw CException(EXCTypeIncorrect);
	}
	return false;
}

bool CGrapheOperations::COPEstUnCouplage(int** ppARCArcs)
{
	return false;
}




/*
1:	function TestCouplage(G,C)
2:	Si (il existe a1, a2 appartenant à C tel que a1 et a2 ont un sommet en commun) Alors
3:		Afficher « C n’est pas un couplage»
4:	Sinon
5:		Afficher « C est un couplage »
6:		Pour tout a appartenant à A\C Faire
5:			C’← C + {a}
6:			Si (C’ est un couplage) Alors
7:				Afficher « C n’est pas de taille maximale»
8:				Fin
9:			FinSi
10:		Fin Pour
11:	Fin Si
*/
