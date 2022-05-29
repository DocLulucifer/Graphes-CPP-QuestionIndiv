#include "CGraphe.h"
#include "CException.h"
#include "CControleurParseur.h"
#include "CGrapheOperations.h"
#include <cstdio>
#include <cstdlib>

#define EXCArretProgramme 50

using namespace std;

int main(int argc, char* argv[]) {

	if (argc == 2) {

		//D�claration des variables du main
		CControleurParseur* pCONFichierLu = nullptr;
		CGraphe* pGRAGraphe = nullptr, * pGRAGrapheInverse = nullptr;
		CGrapheOperations COPBoiteAOutils;

		//Lecture du fichier pass� en param�tre
		try {
			pCONFichierLu = new CControleurParseur(argv[1]);
			pCONFichierLu->CONLireFichierGraphe();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCCheminVideCtrlParseur) {
				cout << "Erreur : Chemin de fichier pass� en param�tre vide ou nul !" << endl;
				return 1;
			}
		}

		//R�cup�ration du graphe lu et affichage
		try {
			cout << "-----Graphe lu depuis le fichier :-----" << endl << endl;
			pGRAGraphe = new CGraphe(*pCONFichierLu->CONLireGraphe());
			pGRAGraphe->GRAAffichage();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
			}
			else if (EXCException.EXCLireErreur() == EXCListeSommetInexistante) {
				cout << "Erreur : Liste des sommets du graphes vide, Affichage impossible : Rien � afficher !" << endl;
			}
			return 1;
		}

		//R�cup�ration du graphe invers� puis affichage
		try {
			cout << endl << "-----Graphe Inverse-----" << endl << endl;
			pGRAGrapheInverse = COPBoiteAOutils.GRAInversion(pGRAGraphe);
			pGRAGrapheInverse->GRAAffichage();
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCArretProgramme) {
				return 1;
			}
			else if (EXCException.EXCLireErreur() == EXCListeSommetInexistante) {
				cout << "Erreur : Liste des sommets du graphes vide, Affichage impossible : Rien � afficher !" << endl;
				return 1;
			}
			else {
				cout << "Erreur non-specifiee !" << endl;
			}
		}
		
		//Lib�ration de la m�moire allou�e dans le main
		delete pGRAGraphe;
		delete pGRAGrapheInverse;
		delete pCONFichierLu;

	}
	else if (argc > 2) {
		cout << "Erreur : Ne passez qu'un fichier en argument !" << endl;
		return 1;
	}
	else {
		cout << "Erreur : Aucun chemin de fichier passe en argument !" << endl;
		return 1;
	}

	return 0;
}