#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseurGraphe.h"
#include "CControleurParseurCouplage.h"
#include "CGrapheOperations.h"
#include "CCouplage.h"
#include <cstdio>
#include <cstdlib>

#define EXCArretProgramme 50

using namespace std;

/******************************************************************************************************
**** Entr�es : argc : int, argv : char**														   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Fonction principale																   ****
******************************************************************************************************/
int main(int argc, char* argv[]) {

	if (argc == 3) {

		//Declaration des variables du main
		CControleurParseurGraphe* pCONFichierLu = nullptr;
		CControleurParseurCouplage* pCONFichierCouplageLu = nullptr;
		CCouplage* pCOUCouplageLu = nullptr;
		CGraphe* pGRAGraphe = nullptr;
		CGrapheOperations COPBoiteAOutils;

		//Lecture du graphe passe en param�tre
		try {
			pCONFichierLu = new CControleurParseurGraphe(argv[1]);
			pCONFichierLu->CONLireFichierGraphe();
		}
		catch (CException EXCException) {
			cout << "--- ERREUR PARSAGE GRAPHE ---" << endl;
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCCheminVideCtrlParseur) {
				cout << "Erreur : Chemin de fichier passe en parametre vide ou nul !" << endl;
				return 1;
			}
		}
		
		//Lecture du couplage passe en parametre
		try {
			pCONFichierCouplageLu = new CControleurParseurCouplage(argv[2]);
			pCONFichierCouplageLu->CONLireFichierCouplage();
		}
		catch (CException EXCException) {
			cout << "--- ERREUR PARSAGE COUPLAGE ---" << endl;
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCCheminVideCtrlParseur) {
				cout << "Erreur : Chemin de fichier passe en parametre vide ou nul !" << endl;
				return 1;
			}
		}
		
		//Recuperation du graphe lu et affichage
		try {
			cout << "-----Graphe lu depuis le fichier :-----" << endl << endl;
			pGRAGraphe = new CGraphe(*pCONFichierLu->CONLireGraphe());
			pGRAGraphe->GRAModifierType(false);
			pGRAGraphe->GRAAffichage();
		}
		catch (CException EXCException) {
			cout << "--- ERREUR LECTURE GRAPHE ---" << endl;
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
			}
			else if (EXCException.EXCLireErreur() == EXCListeSommetInexistante) {
				cout << "Erreur : Liste des sommets du graphes vide, Affichage impossible : Rien � afficher !" << endl;
			}
			return 1;
		}
		
		// Execution du test de couplage
		try {
			pCOUCouplageLu = new CCouplage(*pCONFichierCouplageLu->CONLireCouplage());
			COPBoiteAOutils.COPTestCouplage(pGRAGraphe, pCOUCouplageLu);
		}
		catch (CException EXCException) {
			cout << "--- ERREUR TEST COUPLAGE ---" << endl;
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
		}
		//Liberation de la memoire allouee dans le main
		delete pGRAGraphe;
		delete pCOUCouplageLu;
		delete pCONFichierLu;
		delete pCONFichierCouplageLu;

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