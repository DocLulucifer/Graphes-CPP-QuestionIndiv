#include "CFichier.h"
#pragma warning(disable : 4996)

using namespace std;


/******************************************************************************************************
**** Entr�es : char* pcChemin																	   ****
**** N�cessite :																		  	       ****
**** Sorties :	CMatrice MATretour																   ****
**** Entra�ne : Renvoie la matrice du fichier texte dont le chemin pcChemin est pass� en param�tre ****
******************************************************************************************************/
/*CGraphe Cfichier::FICLireFichier(const char* pcChemin)
{
	if (pcChemin == nullptr) {
		throw CException(EXCCheminNul);
	}
	ifstream fichier(pcChemin);

	unsigned int uiNbSommets, uiNbArcs, uiboucle1, uiboucle2;

	if (fichier.is_open()) {

		char* pcLigne = new char[STR_LENGTH];

		//On r�cup�re le nombre de sommets

		FICLigneSuivante(pcLigne, fichier);

		char *pcToken = strtok(pcLigne, "=");
		
		if (!FICVerifBalise(pcToken, "sommet")) {
			delete[] pcLigne;
			throw CException(EXCBaliseIncorrecte);
		}
		
		pcToken = strtok(NULL, "=");

		if (pcToken == nullptr) {
			//Toutes les exceptions gerent la lib�ration de la m�moire occup�e par pcLigne
			delete[] pcLigne;
			throw CException(EXCParserPointeurNul);
		}
		//On veut une dimension minimum �gale � 1
		else if (atoi(pcToken) <= 0) {
			delete[] pcLigne;
			throw CException(EXCNbSommetsNeg);
		}
		
		uiNbSommets = (unsigned int)(atoi(pcToken));

		//On r�cup�re le nombre d'arcs

		FICLigneSuivante(pcLigne, fichier);

		char* pcToken = strtok(pcLigne, "=");

		if (!FICVerifBalise(pcToken, "arc")) {
			delete[] pcLigne;
			throw CException(EXCBaliseIncorrecte);
		}

		pcToken = strtok(NULL, "=");

		if (pcToken == nullptr) {//Toutes les exceptions gerent la lib�ration de la m�moire occup�e par pcLigne
			delete[] pcLigne;
			throw CException(EXCParserPointeurNul);
		}
		//On veut une dimension minimum �gale � 1
		else if (atoi(pcToken) <= 0) {
			delete[] pcLigne;
			throw CException(EXCNbArcsNeg);
		}

		uiNbArcs = (unsigned int)(atoi(pcToken));

		delete[] pcLigne;
	}
	else {
		throw CException(EXCFichierNonOuvert);
	}
	//Cas impossible mais n�c�ssaire � la compilation

	CMatrices<double> MATretour;

	return MATretour;
}*/

/***********************************************************************************************************************
**** Entr�es : char* pcChaine, ifstream& fichier																    ****
**** N�cessite : Un fichier ouvert et une chaine non nulle								  							****
**** Sorties :																										****
**** Entra�ne : Renvoie la chaine pcChaine pass�e en param�tre et dont tous les tabh et espaces sont supprim�s	    ****
***********************************************************************************************************************/
void Cfichier::FICLigneSuivante(char* pcLigne, ifstream& fichier) {

	unsigned int uiBoucle = 0;

	if (pcLigne == nullptr) {
		throw CException(EXCLigneNulle);
	}
	if (!fichier) {
		throw CException(EXCFichierNonOuvert);
	}

	do
	{
		fichier.getline(pcLigne, STR_LENGTH);
		FICSupp_char(pcLigne, ' ');
		FICSupp_char(pcLigne, '\t');
		uiBoucle++;
		if (uiBoucle == MAX_LOOPING) {
			throw CException(EXCBoucleInfinie);
		}
	} while (pcLigne[0] == '\n' || pcLigne[0] == '\0' || pcLigne[0] == '\r');
}


/***********************************************************************************************************************
**** Entr�es : char* pcChaine																					    ****
**** N�cessite :																		  							****
**** Sorties :	char* pcChaine																						****
**** Entra�ne : Renvoie la chaine pcChaine pass�e en param�tre et dont toutes les lettres sont pass�es en minuscule ****
***********************************************************************************************************************/
char * Cfichier::FICMinuscule(char* pcChaine)
{
	if (pcChaine == nullptr) {
		throw CException(EXCTokenNulMinuscule);
	}
	unsigned int uiboucle;

	for (uiboucle = 0; pcChaine[uiboucle] != '\0'; uiboucle++) {
		pcChaine[uiboucle] = tolower(pcChaine[uiboucle]);
	}
	return pcChaine;
}


/******************************************************************************************************************
**** Entr�es : char* pcChaine																				   ****
**** N�cessite :																		  					   ****
**** Sorties :																								   ****
**** Entra�ne : Supprime un charact�re c d'une chaine de caract�re pcChaine pass�e en param�tre				   ****
******************************************************************************************************************/
void Cfichier::FICSupp_char(char* pcChaine, const char cCharactere)
{
	if (pcChaine == nullptr) {
		throw CException(EXCTokenNulSuppEspace);
	}
	unsigned int uiboucle1, uiboucle2;

	for (uiboucle1 = 0; pcChaine[uiboucle1] != '\0'; uiboucle1++) {
		if (pcChaine[uiboucle1] == cCharactere) {
			for (uiboucle2 = uiboucle1; pcChaine[uiboucle2] != '\0'; uiboucle2++) {
				pcChaine[uiboucle2] = pcChaine[uiboucle2 + 1];
			}
			uiboucle1--;
		}
	}
	pcChaine[uiboucle1] = '\0';
}

bool Cfichier::FICVerifBalise(char* pcToken,const char* pcNomBalise)
{
	if (strstr(FICMinuscule(pcToken), pcNomBalise) == nullptr) {
		return false;
	}
	else {
		return true;
	}
}
