#pragma once

#pragma warning(disable : 6308)

#include "CGraphe.h"
#include "CSommet.h"

using namespace std;

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Construction d'un objet CGraphe par d�faut										   ****
******************************************************************************************************/
CGraphe::CGraphe()
{
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
	ppSOMGRAListeSommet = nullptr;
}

/******************************************************************************************************
**** Entr�es : GRAGraphe : CGraphe&																   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Construction d'un objet CGraphe par recopie de GRAGraphe						   ****
******************************************************************************************************/
CGraphe::CGraphe(const CGraphe& GRAGraphe)
{
	unsigned int uiboucle;

	uiGRANbArcs = GRAGraphe.GRALireNbArcs();
	uiGRANbSommet = GRAGraphe.GRALireNbSommet();
	bGRAOriente = GRAGraphe.GRALireType();

	//Allocation de la liste de sommets
	ppSOMGRAListeSommet = new CSommet * [GRAGraphe.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAGraphe.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommet[uiboucle] = new CSommet(*GRAGraphe.GRALireSommets()[uiboucle]);
	}
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Destruction de l'objet CGraphe													   ****
******************************************************************************************************/
CGraphe::~CGraphe()
{
	unsigned int uiboucle;
	
	//Lib�ration de la m�moire allou�e pour la liste de sommets
	if (ppSOMGRAListeSommet != nullptr) {
		for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
			delete ppSOMGRAListeSommet[uiboucle];
			ppSOMGRAListeSommet[uiboucle] = nullptr;
			}
		delete[] ppSOMGRAListeSommet;
		ppSOMGRAListeSommet = nullptr;
	}
	
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : ppSOMGRAListeSommet : CSommet**													   ****
**** Entra�ne : Renvoie la liste des sommets de l'objet CGraphe									   ****
******************************************************************************************************/
const CSommet* const* CGraphe::GRALireSommets() const
{
	return ppSOMGRAListeSommet;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : uiGRANbSommet : unsigned int														   ****
**** Entra�ne : Renvoie le nombre de sommet de l'objet CGraphe									   ****
******************************************************************************************************/
unsigned int CGraphe::GRALireNbSommet() const
{
	return uiGRANbSommet;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : uiGRANbArcs : unsigned int														   ****
**** Entra�ne : Renvoie le nombre d'arcs de l'objet CGraphe										   ****
******************************************************************************************************/
unsigned int CGraphe::GRALireNbArcs() const
{
	return uiGRANbArcs;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties : bGRAOriente : bool																   ****
**** Entra�ne : Renvoie le type de l'objet CGraphe (1 si oriente, 0 si non-oriente)				   ****
******************************************************************************************************/
bool CGraphe::GRALireType() const
{
	return bGRAOriente;
}

/******************************************************************************************************
**** Entr�es : pSomDepart : CSommet*, pSOMArrivee : CSommet*									   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Cr�e un arc partant du sommet pSOMDepart allant vers le sommet pSOMArrivee		   ****
******************************************************************************************************/
void CGraphe::GRAAjouterArc(CSommet* pSOMDepart, CSommet* pSOMArrivee)
{
	if (pSOMDepart == nullptr || pSOMArrivee == nullptr) {
		throw CException(EXCPointeurSommetNul);
	}
	
	//Cr�ation d'arcs entre les deux sommets sur base du nu�ro de sommet � relier
	CArc * pARCNouvelArcE = new CArc(pSOMDepart->SOMLireNumero());
	CArc * pARCNouvelArcS = new CArc(pSOMArrivee->SOMLireNumero());
	try {
		pSOMDepart->SOMAjouterArcSortant(pARCNouvelArcS);
		pSOMArrivee->SOMAjouterArcEntrant(pARCNouvelArcE);
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
			cout << "Erreur interne (GRAAjouterArc) : Le pointeur d'arc est nul !" << endl;
		}
		throw CException(EXCArretProgramme);
	}
	
	delete pARCNouvelArcE;
	delete pARCNouvelArcS;
	uiGRANbArcs++;
}

/*****************************************************************************************************************
**** Entr�es : iDepart : int, iArrivee : int															      ****
**** N�cessite :																		  				      ****
**** Sorties :																								  ****
**** Entra�ne : Cr�e un arc partant du sommet ayant le numero iDepart vers le sommet ayant le num�ro iArrivee ****
*****************************************************************************************************************/
void CGraphe::GRAAjouterArc(int iDepart, int iArrivee)
{
	//Cr�ation d'arcs entre les deux sommets sur base du nu�ro de sommet � relier
	CArc* pARCNouvelArcE = new CArc(iDepart);
	CArc* pARCNouvelArcS = new CArc(iArrivee);
	
	CSommet* pSOMDepart = nullptr, * pSOMArrivee = nullptr;
	
	//Obtention des pointeurs de sommets (+v�rification de leur existence)
	pSOMDepart = GRARechercheSommet(iDepart);
	pSOMArrivee = GRARechercheSommet(iArrivee);
	
	if(pSOMDepart == nullptr || pSOMArrivee == nullptr) {
		throw CException(EXCPointeurSommetNul);
	}
	try {
		pSOMDepart->SOMAjouterArcSortant(pARCNouvelArcS);
		pSOMArrivee->SOMAjouterArcEntrant(pARCNouvelArcE);
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
			cout << "Erreur interne (GRAAjouterArc) : Le pointeur d'arc est nul !" << endl;
		}
		throw CException(EXCArretProgramme);
	}
	delete pARCNouvelArcE;
	delete pARCNouvelArcS;
	uiGRANbArcs++;
}

/*********************************************************************************************************
**** Entr�es : iDepart : int, iArrivee : int														  ****
**** N�cessite :																		  			  ****
**** Sorties :																						  ****
**** Entra�ne : Supprime l'arc partant du sommet num�ro iDepart allant vers le sommet num�ro iArrivee ****
*********************************************************************************************************/
void CGraphe::GRASupprimerArc(int iDepart, int iArrivee)
{
	CSommet* pSOMDepart = nullptr, * pSOMArrivee = nullptr;

	//Obtention des pointeurs de sommets (+v�rification de leur existence)
	pSOMDepart = GRARechercheSommet(iDepart);
	if (pSOMDepart == nullptr) {
		throw CException(EXCValeurSommetIntrouvable);
	}
	pSOMArrivee = GRARechercheSommet(iArrivee);
	if (pSOMArrivee == nullptr) {
		throw CException(EXCValeurSommetIntrouvable);
	}

	try {
		pSOMDepart->SOMSupprimerArcEntrant((CArc*)pSOMDepart->SOMRechercheArc(iArrivee, sortant));
		pSOMArrivee->SOMSupprimerArcSortant((CArc*)pSOMArrivee->SOMRechercheArc(iDepart, entrant));
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCSuppImpossible) {
			cout << "Erreur : Suppression d'arc Impossible : La liste des arcs est vide !" << endl;
			throw CException(EXCArretProgramme);
		}
		if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
			cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			throw CException(EXCArretProgramme);
		}
	}

	uiGRANbArcs--;
}

/******************************************************************************************************
**** Entr�es : SOMSommet CSommet&																   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Ajoute le sommet SOMSommet au graphe											   ****
******************************************************************************************************/
void CGraphe::GRAAjouterSommet(CSommet& SOMSommet)
{
	unsigned int uiBoucle;

	//V�rification de l'unicit� du num�ro de sommet et changement de la valeur si besoin
	if (!GRANumeroSommetUnique(SOMSommet.SOMLireNumero())) {
		throw CException(EXCNumeroIndisponible);
	}

	//Equivalent de realloc pour les sommets en passant par un tableau temporaire pour la copie des valeurs
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet + 1];
	for (uiBoucle = 0; uiBoucle < uiGRANbSommet + 1; uiBoucle++) {
		if (uiBoucle < uiGRANbSommet) {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(*ppSOMGRAListeSommet[uiBoucle]);
		}
		else {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(SOMSommet);
		}
	}

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++) {
		delete ppSOMGRAListeSommet[uiBoucle];
	}
	delete[] ppSOMGRAListeSommet;
	
	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	uiGRANbSommet++;
}

/******************************************************************************************************
**** Entr�es : iNum : int																		   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Ajoute le sommet numero iNum au graphe											   ****
******************************************************************************************************/
void CGraphe::GRAAjouterSommet(int iNum)
{
	unsigned int uiBoucle;
	CSommet* pSOMSommet = new CSommet(iNum);
	
	//Verificvation unicit� du num�ro de sommet et changement si besoin
	if (!GRANumeroSommetUnique(pSOMSommet->SOMLireNumero())) {
		delete pSOMSommet;
		throw CException(EXCNumeroIndisponible);
	}

	//Equivalent de realloc pour la liste des sommets en passant par un tableau temporaire pour la copie des valeurs
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet + 1];
	for (uiBoucle = 0; uiBoucle < uiGRANbSommet + 1; uiBoucle++) {
		if (uiBoucle < uiGRANbSommet) {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(*ppSOMGRAListeSommet[uiBoucle]);
		}
		else {
			ppSOMGRAListeSommetTMP[uiBoucle] = new CSommet(*pSOMSommet);
		}
	}

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++) {
		delete ppSOMGRAListeSommet[uiBoucle];
	}
	delete[] ppSOMGRAListeSommet;
	delete pSOMSommet;

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	uiGRANbSommet++;
}

/******************************************************************************************************
**** Entr�es : pSOMParam : CSommet*																   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Supprime le sommet pSOMParam du graphe											   ****
******************************************************************************************************/
void CGraphe::GRASupprimerSommet(CSommet* pSOMParam)
{
	unsigned int uiboucle, uiSommetTrouve = 0;

	for (uiboucle = 0; uiboucle < pSOMParam->SOMLireNbArcsEntrants(); uiboucle++) {

		//Suppression de l'arc dans le sommet ant�rieur
		CSommet* pSOMSommetPrecedent;
		try {
			pSOMSommetPrecedent = (CSommet*)GRARechercheSommet(pSOMParam->SOMLireArcsEntrants()[uiboucle]->ARCLireDestination());
			if (pSOMSommetPrecedent == nullptr) {
				throw  CException(EXCValeurSommetIntrouvable);
			}
			pSOMSommetPrecedent->SOMSupprimerArcSortant((CArc*)pSOMSommetPrecedent->SOMRechercheArc(pSOMParam->SOMLireNumero(), sortant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCValeurSommetIntrouvable) {
				cout << "Erreur : Suppression du sommet impossible : Le sommet n'existe pas !" << endl;
			}
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}

		//Suppression de l'arc dans le sommet � supprimer
		try {
			pSOMParam->SOMSupprimerArcEntrant((CArc*)pSOMParam->SOMRechercheArc(pSOMSommetPrecedent->SOMLireNumero(), entrant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		uiGRANbArcs--;
	}

	for (uiboucle = 0; uiboucle < pSOMParam->SOMLireNbArcsSortants(); uiboucle++) {

		//Suppression de l'arc dans le sommet suivant
		CSommet* pSOMSommetSuivant;
		try {
			pSOMSommetSuivant = (CSommet*)GRARechercheSommet(pSOMParam->SOMLireArcsSortants()[uiboucle]->ARCLireDestination());
			if (pSOMSommetSuivant == nullptr) {
				throw  CException(EXCValeurSommetIntrouvable);
			}
			pSOMSommetSuivant->SOMSupprimerArcEntrant((CArc*)pSOMSommetSuivant->SOMRechercheArc(pSOMParam->SOMLireNumero(), entrant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCValeurSommetIntrouvable) {
				cout << "Erreur : Suppression du sommet impossible : Le sommet n'existe pas !" << endl;
			}
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		

		//Suppression de l'arc dans le sommet � supprimer
		try {
			pSOMParam->SOMSupprimerArcSortant((CArc*)pSOMParam->SOMRechercheArc(pSOMSommetSuivant->SOMLireNumero(), sortant));
		}
		catch (CException EXCException) {
			if (EXCException.EXCLireErreur() == EXCPointeurArcNul) {
				cout << "Erreur : Suppression d'arc Impossible : L'arc n'existe pas !" << endl;
			}
			throw CException(EXCArretProgramme);
		}
		uiGRANbArcs--;
	}

	//Suppression du sommet dans la liste et realloc par tableau temporaire
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet - 1];
	for (uiboucle = 0; uiboucle < GRALireNbSommet() - 1; uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == pSOMParam->SOMLireNumero()) {
			uiSommetTrouve = 1;
		}
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*ppSOMGRAListeSommet[uiboucle + uiSommetTrouve]);
	}


	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	uiGRANbSommet--;

}

/******************************************************************************************************
**** Entr�es : pSOMParam : CSommet*, iNum : int													   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Modifie le num�ro du sommet pSOMParam par le numero iNum						   ****
******************************************************************************************************/
void CGraphe::GRAModifierNumSommet(CSommet* pSOMParam, int iNum)
{
	if (pSOMParam == nullptr) {
		throw CException(EXCPointeurSommetNul);
	}
	if (GRANumeroSommetUnique(iNum) == false) {
		throw CException(EXCNumeroIndisponible);
	}
	pSOMParam->SOMModifierNumero(iNum);

}

/******************************************************************************************************
**** Entr�es : bParam : bool																	   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Modifie le type du graphe (0 = non-orient�, 1 = orient�)						   ****
******************************************************************************************************/
void CGraphe::GRAModifierType(bool bParam)
{
	bGRAOriente = bParam;
}

/*************************************************************************************************************
**** Entr�es : iVal : int																				  ****
**** N�cessite :																		  				  ****
**** Sorties : CSommet*																					  ****
**** Entra�ne : Renvoie un pointeur sur le sommet num�ro iVal s'il existe, renvoie un pointeur null sinon ****
*************************************************************************************************************/
CSommet* CGraphe::GRARechercheSommet(int iVal) const
{
	unsigned int uiboucle;
	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iVal) {
			return (CSommet*)GRALireSommets()[uiboucle];
		}
	}
	return nullptr;
}

/******************************************************************************************************
**** Entr�es : iSommet : int																	   ****
**** N�cessite :																		  	       ****
**** Sorties : int																				   ****
**** Entra�ne : Renvoie la position du sommet num�ro iSommet s'il existe, -1 sinon				   ****
******************************************************************************************************/
int CGraphe::GRARechercheIndexSommet(int iSommet) const
{
	unsigned int uiboucle;

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iSommet) {
			return (int)uiboucle;
		}
	}
	return -1;
}

/******************************************************************************************************
**** Entr�es : iVal	: int																		   ****
**** N�cessite :																		  	       ****
**** Sorties : bool																				   ****
**** Entra�ne : Renvoie true si le sommet num�ro iVal n'existe pas, false sinon					   ****
******************************************************************************************************/
bool CGraphe::GRANumeroSommetUnique(int iVal)
{
	unsigned int uiboucle;

	for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iVal) {
			return false;
		}
	}
	return true;
}

/******************************************************************************************************
**** Entr�es :																					   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : Fonction d'affichage du graphe													   ****
******************************************************************************************************/
void CGraphe::GRAAffichage() const
{
	if (ppSOMGRAListeSommet == nullptr) {
		throw CException(EXCListeSommetInexistante);
	}
	unsigned int uiboucleSommet;
	unsigned int uiboucleArc;

	if (bGRAOriente == true) {
		cout << "Type de Graphe : Oriente" << endl;
		cout << "Nombre de sommets : " << GRALireNbSommet() << endl;
		cout << "Nombre d'arcs : " << GRALireNbArcs() << endl << endl;
		
		//Lecture des sommets sortants uniquement pour le graphe orient�
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			if (GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants() > 0) {
				cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
				for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
					cout << "--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
				}
				cout << endl;
			}
		}
	}
	else {
		cout << "Type de Graphe : Non-Oriente" << endl;
		cout << "Nombre de sommets : " << GRALireNbSommet() << endl;
		cout << "Nombre d'arcs : " << GRALireNbArcs() << endl << endl;

		//Lecture des sommets sortants et entrants pour le graphe non-orient�
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
			if (GRALireSommets()[uiboucleSommet]->SOMLireNbArcsEntrants() > 0) {
				for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsEntrants(); uiboucleArc++) {
					cout << "<--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsEntrants()[uiboucleArc]->ARCLireDestination() << endl;
				}
			}
			if (GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants() > 0) {
				for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
					cout << "<--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
				}
			}
			cout << endl;
		}
	}
}

/******************************************************************************************************
**** Entr�es : GRAParam : CGraphe&																   ****
**** N�cessite :																		  	       ****
**** Sorties :																					   ****
**** Entra�ne : La copie de l'objet CGraphe en param�tre										   ****
******************************************************************************************************/
CGraphe& CGraphe::operator=(const CGraphe &GRAParam)
{
	unsigned int uiboucle;
	bGRAOriente = GRAParam.GRALireType();

	//Copie par duplication des objets
	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [GRAParam.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAParam.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*GRAParam.GRALireSommets()[uiboucle]);
	}

	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;

	uiGRANbArcs = GRAParam.GRALireNbArcs();
	uiGRANbSommet = GRAParam.GRALireNbSommet();

	ppSOMGRAListeSommet = ppSOMGRAListeSommetTMP;

	return *this;
}
