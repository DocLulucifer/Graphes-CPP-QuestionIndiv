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
**** Entraîne : Determine si le couplage ppARCArcs est de taille maximale						   ****
******************************************************************************************************/
bool CGrapheOperations::COPTestCouplage(CGraphe* pGRAGraphe, int** ppiArcs)
{
	if (pGRAGraphe->GRALireType() == true) {
		throw CException(EXCTypeIncorrect);
	}
	if(COPEstUnCouplage(ppiArcs) == false) {
		cout << "C n'est pas un couplage" << endl;
		return false;
	}
	else {
		unsigned int uiboucle, uiTailleComplementaire = pGRAGraphe->GRALireNbArcs() - (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2;
		cout << "C est un couplage" << endl;
		int** ppiEnsembleComplementaire = COPComplementaireCouplage(pGRAGraphe, ppiArcs);
		
		for (uiboucle = 0; uiboucle < uiTailleComplementaire; uiboucle++) {

			int* piArcAAjouter = ppiEnsembleComplementaire[uiboucle];
			int** ppiEnsembleTest = COPAjouterArcAuCouplage(ppiArcs, piArcAAjouter);
			unsigned int uiTailleEnsembleTest = (sizeof(ppiEnsembleTest) / sizeof(ppiEnsembleTest[0][0])) / 2 + 1;

			if(COPEstUnCouplage(ppiEnsembleTest) == true) {
				cout << "Le couplage n'est pas de taille maximale !" << endl;
				
				// Libération de la mémoire avant retour
				for (uiboucle = 0; uiboucle < uiTailleComplementaire; uiboucle++) {
					delete[] ppiEnsembleComplementaire[uiboucle];
				}
				delete[] ppiEnsembleComplementaire;

				for (uiboucle = 0; uiboucle < uiTailleEnsembleTest; uiboucle++) {
					delete[] ppiEnsembleTest[uiboucle];
				}
				delete[] ppiEnsembleTest;
				
				return false;
			}
			
			// Libération de la mémoire avant nouveau test			
			for (uiboucle = 0; uiboucle < uiTailleEnsembleTest; uiboucle++) {
				delete[] ppiEnsembleTest[uiboucle];
			}
			delete[] ppiEnsembleTest;
		}
		
		// Libération de la mémoire avant retour
		for (uiboucle = 0; uiboucle < uiTailleComplementaire; uiboucle++) {
			delete[] ppiEnsembleComplementaire[uiboucle];
		}
		delete[] ppiEnsembleComplementaire;
	}
	return true;
}


bool CGrapheOperations::COPEstUnCouplage(int** ppiArcs)
{
	unsigned int uiboucle, uiboucle2;
	unsigned int uiTaille = (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2;
	int ivaleur1, ivaleur2;

	//Si il n'y a qu'un seul arc, il est forcément un couplage
	if (uiTaille == 1) {
		return true;
	}

	// On teste si le tableau est un couplage
	for (uiboucle = 0; uiboucle < uiTaille; uiboucle++) {
		ivaleur1 = ppiArcs[uiboucle][0];
		ivaleur2 = ppiArcs[uiboucle][1];
		for (uiboucle2 = uiboucle + 1; uiboucle2 < uiTaille; uiboucle2++) {
			if (ppiArcs[uiboucle2][0] == ivaleur2 || ppiArcs[uiboucle2][0] == ivaleur1 || ppiArcs[uiboucle2][1] == ivaleur2 || ppiArcs[uiboucle2][1] == ivaleur1) {
				return false;
			}
		}
	}
	return true;
}

int ** CGrapheOperations::COPAjouterArcAuCouplage(int** ppiArcs, int* piArcs)
{
	// Initialisation des variables
	unsigned int uiTaille = (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2;
	unsigned int uiboucle;

	// Création du tableau temporaire
	int** ppiNouvelEnsemble = new int* [uiTaille + 1];
	for (uiboucle = 0; uiboucle < uiTaille + 1; uiboucle++) {
		ppiNouvelEnsemble[uiboucle] = new int[2];
	}

	// Copie des arcs
	for (uiboucle = 0; uiboucle < uiTaille; uiboucle++) {
		ppiNouvelEnsemble[uiboucle][0] = ppiArcs[uiboucle][0];
		ppiNouvelEnsemble[uiboucle][1] = ppiArcs[uiboucle][1];
	}
	
	// Ajout de l'arc
	ppiNouvelEnsemble[uiTaille][0] = piArcs[0];
	ppiNouvelEnsemble[uiTaille][1] = piArcs[1];
	
	return ppiNouvelEnsemble;
}

int** CGrapheOperations::COPComplementaireCouplage(CGraphe* pGRAGraphe, int** ppiArcs)
{
	int** ppiArcsTMP = new int* [pGRAGraphe->GRALireNbArcs() - (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2];
	int** ppiArcsGraphe = new int* [pGRAGraphe->GRALireNbArcs()];
	unsigned int uiboucle, uiboucle2, uicompteur = 0;
	
	// Initialisation du tableau des arcs de pGRAGraphe
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs(); uiboucle++) {
		ppiArcsGraphe[uiboucle] = new int[2];
	}
	
	// Initialisation du tableau des arcs de pGRAGraphe privé de ppiArcs
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs() - (sizeof(ppiArcs) / sizeof(ppiArcs[0][0])) / 2; uiboucle++) {
		ppiArcsTMP[uiboucle] = new int[2];
	}
	
	// Copie des arcs de pGRAGraphe en un tableau de int**
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbSommet(); uiboucle++) {
		for (uiboucle2 = 0; uiboucle2 < pGRAGraphe->GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
			ppiArcsGraphe[uicompteur][0] = pGRAGraphe->GRALireSommets()[uiboucle]->SOMLireNumero();
			ppiArcsGraphe[uicompteur][1] = pGRAGraphe->GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2]->ARCLireDestination();
			uicompteur++;
		}
	}
	
	// Selection des arcs de ppiArcsGraphe qui ne sont pas dans ppiArcs
	uicompteur = 0;
	for (uiboucle = 0 ; uiboucle < pGRAGraphe->GRALireNbArcs(); uiboucle++) {
		if (COPEstDansEnsembleArcs(ppiArcs, ppiArcsGraphe[uiboucle]) == false) {
			ppiArcsTMP[uicompteur][0] = ppiArcsGraphe[uiboucle][0];
			ppiArcsTMP[uicompteur][1] = ppiArcsGraphe[uiboucle][1];
			uicompteur++;
		}
	}
	
	// Libération de la mémoire
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs(); uiboucle++) {
		delete[] ppiArcsGraphe[uiboucle];
	}
	delete[] ppiArcsGraphe;
	
	// Retour du complémentaire
	return ppiArcsTMP;
}

bool CGrapheOperations::COPEstDansEnsembleArcs(int** ppiEnsembleArcs, int* piArcATester)
{
	// Initialisation des variables
	unsigned int uiTaille = (sizeof(ppiEnsembleArcs) / sizeof(ppiEnsembleArcs[0][0])) / 2;
	unsigned int uiboucle;
	
	// Parcours du tableau
	for (uiboucle = 0; uiboucle < uiTaille; uiboucle++) {
		if (ppiEnsembleArcs[uiboucle][0] == piArcATester[0] && ppiEnsembleArcs[uiboucle][1] == piArcATester[1]) {
			return true;
		}
		else if (ppiEnsembleArcs[uiboucle][0] == piArcATester[1] && ppiEnsembleArcs[uiboucle][1] == piArcATester[0]) {
			return true;
		}
	}
	return false;
}





