#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseurGraphe.h"
#include "CControleurParseurCouplage.h"
#include "CGrapheOperations.h"
#include <cstdio>
#include <cstdlib>

#define EXCArretProgramme 50

using namespace std;

/******************************************************************************************************
**** Entrées : argc : int, argv : char**														   ****
**** Nécessite :																		  	       ****
**** Sorties :																					   ****
**** Entraîne : Fonction principale																   ****
******************************************************************************************************/
int main(int argc, char* argv[]) {

	if (argc == 3) {

		//Déclaration des variables du main
		CControleurParseurGraphe* pCONFichierLu = nullptr;
		CControleurParseurCouplage* pCONFichierCouplageLu = nullptr;
		int** ppiCouplage = nullptr;
		CGraphe* pGRAGraphe = nullptr, * pGRAGrapheInverse = nullptr;
		CGrapheOperations COPBoiteAOutils;

		//Lecture du graphe passé en paramètre
		try {
			pCONFichierLu = new CControleurParseurGraphe(argv[1]);
			pCONFichierLu->CONLireFichierGraphe();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCCheminVideCtrlParseur) {
				cout << "Erreur : Chemin de fichier passé en paramètre vide ou nul !" << endl;
				return 1;
			}
		}
		
		//Lecture du couplage passé en paramètre
		try {
			pCONFichierCouplageLu = new CControleurParseurCouplage(argv[2]);
			pCONFichierCouplageLu->CONLireFichierCouplage();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCCheminVideCtrlParseur) {
				cout << "Erreur : Chemin de fichier passé en paramètre vide ou nul !" << endl;
				return 1;
			}
		}
		/*
		//Récupération du graphe lu et affichage
		try {
			cout << "-----Graphe lu depuis le fichier :-----" << endl << endl;
			pGRAGraphe = new CGraphe(*pCONFichierLu->CONLireGraphe());
			pGRAGraphe->GRAAffichage();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
			}
			else if (EXCException.EXCLireErreur() == EXCListeSommetInexistante) {
				cout << "Erreur : Liste des sommets du graphes vide, Affichage impossible : Rien à afficher !" << endl;
			}
			return 1;
		}
		*/
		
		// Exécution du test de couplage
		try {
			ppiCouplage = pCONFichierCouplageLu->CONLireCouplage();
			COPBoiteAOutils.COPTestCouplage(pGRAGraphe, ppiCouplage);
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
		}
		//Libération de la mémoire allouée dans le main
		delete pGRAGraphe;
		delete pGRAGrapheInverse;
		delete pCONFichierLu;

	}
	else if (argc > 3) {
		cout << "Erreur : Nombre d'arguments trop grand !" << endl;
		cout << "Veuillez specifier un fichier contenant un graphe et un autre contenant un couplage !" << endl;
		return 1;
	}
	else {
		cout << "Erreur : Nombre d'arguments insuffisants !" << endl;
		cout << "Veuillez specifier un fichier contenant un graphe et un autre contenant un couplage !" << endl;
		return 1;
	}

	return 0;
}