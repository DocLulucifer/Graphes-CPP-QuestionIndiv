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
bool CGrapheOperations::COPTestCouplage(CGraphe* pGRAGraphe, CCouplage* pCOUCouplage)
{
	if (pGRAGraphe->GRALireType() == true) {
		throw CException(EXCTypeIncorrect);
	}
	
	bool bRetour;
	try {
		bRetour = COPEstUnCouplage(pCOUCouplage);
	}
	catch (CException EXCException) {
		cout << "Erreur Interne dans TestCouplage : Dans COPEstUnCouplage :" << endl;

		if (EXCException.EXCLireErreur() == EXCPointeurCouplageNul) {
			cout << "Le pointeur de couplage est nul !" << endl;
		}
		if (EXCException.EXCLireErreur() == EXCCouplageVide) {
			cout << "Le couplage est vide !" << endl;
		}

		throw CException(EXCArretProgramme);
	}
	
	if (bRetour == false) {
		cout << "L'ensemble d'arcs passe en parametre n'est pas un couplage !" << endl;
		return false;
	}
	else {
		unsigned int uiboucle, uiTailleComplementaire = pGRAGraphe->GRALireNbArcs() - pCOUCouplage->COULireNbArcs();
		int* piArcAAjouter = new int[2];
		cout << "L'ensemble d'arcs passe en parametre est un couplage !" << endl;
		
		cout << endl << "--- Affichage du couplage ---" << endl;
		pCOUCouplage->COUAfficherCouplage();
		
		CCouplage* pCOUEnsembleComplementaire = nullptr;
		try {
			pCOUEnsembleComplementaire = COPComplementaireCouplage(pGRAGraphe, pCOUCouplage);
		}
		catch (CException EXCException) {
			cout << "Erreur Interne dans TestCouplage : Dans COPComplementaireCouplage :" << endl;

			if (EXCException.EXCLireErreur() == EXCPointeurCouplageNul) {
				cout << "Le pointeur de couplage est nul !" << endl;
			}
			if (EXCException.EXCLireErreur() == EXCPointeurGrapheNul) {
				cout << "Le pointeur de graphe est nul !" << endl;
			}

			throw CException(EXCArretProgramme);
		}
		
		for (uiboucle = 0; uiboucle < uiTailleComplementaire; uiboucle++) {
			
			try {
				piArcAAjouter[0] = pCOUEnsembleComplementaire->COULireValeur(uiboucle, 0);
				piArcAAjouter[1] = pCOUEnsembleComplementaire->COULireValeur(uiboucle, 0);
			}
			catch (CException EXCException) {
				cout << "Erreur Interne dans TestCouplage : Dans COULireValeur :" << endl;

				if (EXCException.EXCLireErreur() == EXCErreurSegmentation) {
					cout << "SIGSEGV : Accès en lecture interdit !" << endl;
				}
				throw CException(EXCArretProgramme);
			}
			
			CCouplage* pCOUEnsembleTest = nullptr;
			try {
				pCOUEnsembleTest = COPAjouterArcAuCouplage(pCOUCouplage, piArcAAjouter);
			}
			catch (CException EXCException) {
				cout << "Erreur Interne dans TestCouplage : Dans COPAjouterArcAuCouplage :" << endl;

				if (EXCException.EXCLireErreur() == EXCPointeurCouplageNul) {
					cout << "Le pointeur de couplage est nul !" << endl;
				}
				if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
					cout << "Le pointeur d'arc a ajouter est nul !" << endl;
				}
				throw CException(EXCArretProgramme);
			}
			unsigned int uiTailleEnsembleTest = pCOUEnsembleTest->COULireNbArcs();

			try {
				if (COPEstUnCouplage(pCOUEnsembleTest) == true) {
					cout << "Le couplage n'est pas de taille maximale !" << endl;

					// Libération de la mémoire avant retour
					delete pCOUEnsembleComplementaire;
					delete pCOUEnsembleTest;
					delete[] piArcAAjouter;

					return false;
				}
			}
			catch (CException EXCException) {
				cout << "Erreur Interne dans TestCouplage : Dans COPEstUnCouplage :" << endl;
				
				if (EXCException.EXCLireErreur() == EXCPointeurCouplageNul) {
					cout << "Le pointeur de couplage est nul !" << endl;
				}
				if (EXCException.EXCLireErreur() == EXCCouplageVide) {
					cout << "Le couplage est vide !" << endl;
				}
				
				throw CException(EXCArretProgramme);
			}
			
			
			// Libération de la mémoire avant nouveau test			
			delete pCOUEnsembleTest;
		}
		
		// Libération de la mémoire avant retour
		delete pCOUEnsembleComplementaire;
		delete[] piArcAAjouter;
	}
	cout << "Le couplage est de taille maximale !" << endl;
	return true;
}


bool CGrapheOperations::COPEstUnCouplage(CCouplage* pCOUCouplage)
{
	if (pCOUCouplage == nullptr) {
		throw CException(EXCPointeurCouplageNul);
	}

	unsigned int uiboucle, uiboucle2;
	unsigned int uiTaille = pCOUCouplage->COULireNbArcs();
	int ivaleur1, ivaleur2;

	if (uiTaille == 0) {
		throw CException(EXCCouplageVide);
	}
	
	//Si il n'y a qu'un seul arc, il est forcément un couplage
	if (uiTaille == 1) {
		return true;
	}

	// On teste si le tableau est un couplage
	for (uiboucle = 0; uiboucle < uiTaille; uiboucle++) {
		try {
			ivaleur1 = pCOUCouplage->COULireValeur(uiboucle, 0);
			ivaleur2 = pCOUCouplage->COULireValeur(uiboucle, 1);
		}
		catch (CException EXCException) {
			cout << "Dans TestCouplage : Dans COULireValeur :" << endl;

			if (EXCException.EXCLireErreur() == EXCErreurSegmentation) {
				cout << "SIGSEGV : Accès en lecture interdit !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		for (uiboucle2 = uiboucle + 1; uiboucle2 < uiTaille; uiboucle2++) {
			try {
				if (pCOUCouplage->COULireValeur(uiboucle2, 0) == ivaleur2 || pCOUCouplage->COULireValeur(uiboucle2, 0) == ivaleur1 || pCOUCouplage->COULireValeur(uiboucle2, 1) == ivaleur2 || pCOUCouplage->COULireValeur(uiboucle2, 1) == ivaleur1) {
					return false;
				}
			}
			catch (CException EXCException) {
				cout << "Dans TestCouplage : Dans COULireValeur :" << endl;

				if (EXCException.EXCLireErreur() == EXCErreurSegmentation) {
					cout << "SIGSEGV : Accès en lecture interdit !" << endl;
				}
				throw CException(EXCArretProgramme);
			}
		}
	}
	return true;
}

CCouplage* CGrapheOperations::COPAjouterArcAuCouplage(CCouplage* pCOUCouplage, int* piArcs)
{
	if (pCOUCouplage == nullptr) {
		throw CException(EXCPointeurCouplageNul);
	}
	if (piArcs == nullptr) {
		throw CException(EXCPointeurArcNul);
	}
	
	// Initialisation des variables
	unsigned int uiTaille = pCOUCouplage->COULireNbArcs();
	unsigned int uiboucle;

	// Création du tableau temporaire
	int** ppiNouvelEnsemble = new int* [uiTaille + 1];
	for (uiboucle = 0; uiboucle < uiTaille + 1; uiboucle++) {
		ppiNouvelEnsemble[uiboucle] = new int[2];
	}

	// Copie des arcs
	for (uiboucle = 0; uiboucle < uiTaille; uiboucle++) {
		try {
			ppiNouvelEnsemble[uiboucle][0] = pCOUCouplage->COULireValeur(uiboucle, 0);
			ppiNouvelEnsemble[uiboucle][1] = pCOUCouplage->COULireValeur(uiboucle, 1);
		}
		catch (CException EXCException) {
			cout << "Dans COPAjouterArcAuCouplage : Dans COULireValeur :" << endl;

			if (EXCException.EXCLireErreur() == EXCErreurSegmentation) {
				cout << "SIGSEGV : Accès en lecture interdit !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
	}
	
	// Ajout de l'arc
	ppiNouvelEnsemble[uiTaille][0] = piArcs[0];
	ppiNouvelEnsemble[uiTaille][1] = piArcs[1];
	
	// Initialisation du retour de couplage
	CCouplage* pCOURetour = new CCouplage();
	for (uiboucle = 0; uiboucle < uiTaille + 1; uiboucle++) {
		try {
			pCOURetour->COUAjouterArc(ppiNouvelEnsemble[uiboucle]);
		}
		catch (CException EXCException) {
			cout << "Dans COPAjouterArcAuCouplage : Dans COUAjouterArc :" << endl;

			if (EXCException.EXCLireErreur() == EXCPointeurAjoutArcNul) {
				cout << "Le pointeur d'arc a ajouter au couplage est nul !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
	}
	
	// Libération de la mémoire
	for (uiboucle = 0; uiboucle < uiTaille + 1; uiboucle++) {
		delete[] ppiNouvelEnsemble[uiboucle];
	}
	delete[] ppiNouvelEnsemble;
	
	return pCOURetour;
}

CCouplage* CGrapheOperations::COPComplementaireCouplage(CGraphe* pGRAGraphe, CCouplage* pCOUCouplage)
{
	if (pGRAGraphe == nullptr) {
		throw CException(EXCPointeurGrapheNul);
	}
	if (pCOUCouplage == nullptr) {
		throw CException(EXCPointeurCouplageNul);
	}
	if(pGRAGraphe->GRALireNbArcs() - pCOUCouplage->COULireNbArcs() == 0) {
		return nullptr;
	}

	// Initialisation des variables
	int** ppiArcsTMP = new int* [pGRAGraphe->GRALireNbArcs() - pCOUCouplage->COULireNbArcs()];
	int** ppiArcsGraphe = new int* [pGRAGraphe->GRALireNbArcs()];
	unsigned int uiboucle, uiboucle2, uicompteur = 0;
	
	// Initialisation du tableau des arcs de pGRAGraphe
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs(); uiboucle++) {
		ppiArcsGraphe[uiboucle] = new int[2];
	}
	
	// Initialisation du tableau des arcs de pGRAGraphe privé de ppiArcs
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs() - pCOUCouplage->COULireNbArcs(); uiboucle++) {
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
	bool bRetour;
	for (uiboucle = 0 ; uiboucle < pGRAGraphe->GRALireNbArcs(); uiboucle++) {
		try {
			bRetour = COPEstDansEnsembleArcs(pCOUCouplage, ppiArcsGraphe[uiboucle]);
		}
		catch (CException EXCException) {
			cout << "Dans COPComplementaireCouplage : Dans COPEstDansEnsembleArcs :" << endl;

			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Le pointeur de l'arc a comparer est nul !" << endl;
			}
			if (EXCException.EXCLireErreur() == EXCPointeurCouplageNul) {
				cout << "Le pointeur du couplage a comparer est nul !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		if (bRetour == false) {
			ppiArcsTMP[uicompteur][0] = ppiArcsGraphe[uiboucle][0];
			ppiArcsTMP[uicompteur][1] = ppiArcsGraphe[uiboucle][1];
			uicompteur++;
		}
	}
	
	// Initialisation du retour de couplage
	CCouplage* pCOUCouplageRetour = new CCouplage();
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs() - pCOUCouplage->COULireNbArcs(); uiboucle++) {
		try {
			pCOUCouplageRetour->COUAjouterArc(ppiArcsTMP[uiboucle]);
		}
		catch (CException EXCException) {
			cout << "Dans COPComplementaireCouplage : Dans COUAjouterArc :" << endl;

			if (EXCException.EXCLireErreur() == EXCPointeurAjoutArcNul) {
				cout << "Le pointeur d'arc a ajouter au couplage est nul !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
	}
	
	// Libération de la mémoire
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs(); uiboucle++) {
		delete[] ppiArcsGraphe[uiboucle];
	}
	delete[] ppiArcsGraphe;
	for (uiboucle = 0; uiboucle < pGRAGraphe->GRALireNbArcs() - pCOUCouplage->COULireNbArcs(); uiboucle++) {
		delete[] ppiArcsTMP[uiboucle];
	}
	delete[] ppiArcsTMP;
	// Retour du complémentaire
	
	return pCOUCouplageRetour;
}

bool CGrapheOperations::COPEstDansEnsembleArcs(CCouplage* pCOUCouplage, int* piArcATester)
{
	if (pCOUCouplage == nullptr) {
		throw CException(EXCPointeurCouplageNul);
	}
	if (piArcATester == nullptr) {
		throw CException(EXCPointeurArcNul);
	}
	if (pCOUCouplage->COULireNbArcs() == 0) {
		return false;
	}
	// Initialisation des variables
	unsigned int uiTaille = pCOUCouplage->COULireNbArcs();
	unsigned int uiboucle;
	
	// Parcours du tableau
	for (uiboucle = 0; uiboucle < uiTaille; uiboucle++) {
		try {
			if (pCOUCouplage->COULireValeur(uiboucle, 0) == piArcATester[0] && pCOUCouplage->COULireValeur(uiboucle, 1) == piArcATester[1]) {
				return true;
			}
			else if (pCOUCouplage->COULireValeur(uiboucle, 0) == piArcATester[1] && pCOUCouplage->COULireValeur(uiboucle, 1) == piArcATester[0]) {
				return true;
			}
		}
		catch (CException EXCException) {
			cout << "Dans COPEstDansEnsembleArcs : Dans COULireValeur :" << endl;

			if (EXCException.EXCLireErreur() == EXCErreurSegmentation) {
				cout << "SIGSEGV : Accès en lecture interdit !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
	}
	return false;
}





