#include "CGrapheOperations.h"

using namespace std;

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
bool CGrapheOperations::COPTestCouplage(CGraphe* pGRAGraphe, int** ppiArcs)
{
	if (pGRAGraphe->GRALireType() == true) {
		throw CException(EXCTypeIncorrect);
	}
	if(COPEstUnCouplage(ppiArcs) == false) {
		cout << "Ce n'est pas un couplage" << endl;
		return false;
	}
	else {
		cout << "C'est un couplage" << endl;
		
	}
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

bool CGrapheOperations::COPEstUnCouplage(int** ppiArcs)
{
	unsigned int uiboucle, uiboucle2;
	int iTaille = (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2;

	//Si il n'y a qu'un seul arc, il est forcément un couplage
	if (iTaille == 1) {
		return true;
	}

	//Initialisation, on part du principe que ppiArcs[0][0] != ppiArcs[0][1]
	int iValeur1 = ppiArcs[0][0], iValeur2 = ppiArcs[0][1];
	for (uiboucle = 0 ; uiboucle < iTaille; uiboucle++) {
		for (uiboucle2 = uiboucle + 1; uiboucle2 < iTaille; uiboucle2++) {
			if (iValeur1 == ppiArcs[uiboucle2][0] || iValeur1 == ppiArcs[uiboucle2][1]) {
				return false;
			}
		}
		iValeur1 = ppiArcs[uiboucle][0];
		for (uiboucle2 = uiboucle + 1; uiboucle2 < iTaille; uiboucle2++) {
			if (iValeur2 == ppiArcs[uiboucle2][0] || iValeur2 == ppiArcs[uiboucle2][1]) {
				return false;
			}
		}
		iValeur2 = ppiArcs[uiboucle][1];
	}
	return true;
}

void CGrapheOperations::COPAjouterArcAuCouplage(int** ppiArcs, int* piArcs)
{
	// Initialisation des variables
	int iTaille = (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2;
	unsigned int uiboucle;

	// Création du tableau temporaire
	int** ppiArcsTMP = new int* [iTaille + 1];
	for (uiboucle = 0; uiboucle < iTaille + 1; uiboucle++) {
		ppiArcsTMP[uiboucle] = new int[2];
	}

	// Copie des arcs
	for (uiboucle = 0; uiboucle < iTaille; uiboucle++) {
		ppiArcsTMP[uiboucle][0] = ppiArcs[uiboucle][0];
		ppiArcsTMP[uiboucle][1] = ppiArcs[uiboucle][1];
	}
	
	// Ajout de l'arc
	ppiArcsTMP[iTaille][0] = piArcs[0];
	ppiArcsTMP[iTaille][1] = piArcs[1];

	// Suppression de l'ancien tableau
	for (uiboucle = 0; uiboucle < iTaille; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;

	// Affectation du nouveau tableau
	ppiArcs = ppiArcsTMP;
}

int** CGrapheOperations::COPComplementaireCouplage(CGraphe* pGRAGraphe, int** ppiArcs)
{
	// Déterminer l'ensemble des arcs de pGRAGraphe privé de ppiArcs
	int** ppiArcsTMP = new int* [pGRAGraphe->GRALireNbArcs() - (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2];
	
	

	return nullptr;
}





