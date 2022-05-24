#pragma once

#pragma warning(disable : 6308)

#include "CGraphe.h"
#include "CSommet.h"

using namespace std;

CGraphe::CGraphe()
{
	uiGRANbArcs = 0;
	uiGRANbSommet = 0;
	bGRAOriente = true;
	ppSOMGRAListeSommet = nullptr;
}

CGraphe::CGraphe(const CGraphe& GRAGraphe)
{
	unsigned int uiboucle;

	uiGRANbArcs = GRAGraphe.GRALireNbArcs();
	uiGRANbSommet = GRAGraphe.GRALireNbSommet();
	bGRAOriente = GRAGraphe.GRALireType();

	ppSOMGRAListeSommet = new CSommet * [GRAGraphe.GRALireNbSommet()];
	for (uiboucle = 0; uiboucle < GRAGraphe.GRALireNbSommet(); uiboucle++) {
		ppSOMGRAListeSommet[uiboucle] = new CSommet(*GRAGraphe.GRALireSommets()[uiboucle]);
	}
}

CGraphe::~CGraphe()
{
	unsigned int uiboucle;
	if (ppSOMGRAListeSommet != nullptr) {
		for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
			delete ppSOMGRAListeSommet[uiboucle];
			ppSOMGRAListeSommet[uiboucle] = nullptr;
			}
		delete[] ppSOMGRAListeSommet;
		ppSOMGRAListeSommet = nullptr;
	}
	
}

const CSommet* const* CGraphe::GRALireSommets() const
{
	return ppSOMGRAListeSommet;
}

unsigned int CGraphe::GRALireNbSommet() const
{
	return uiGRANbSommet;
}

unsigned int CGraphe::GRALireNbArcs() const
{
	return uiGRANbArcs;
}

bool CGraphe::GRALireType() const
{
	return bGRAOriente;
}

void CGraphe::GRAAjouterArc(CSommet* SOMDepart, CSommet* SOMArrivee)
{
	CArc * pARCNouvelArcE = new CArc(SOMDepart->SOMLireNumero());
	CArc * pARCNouvelArcS = new CArc(SOMArrivee->SOMLireNumero());
	SOMDepart->SOMAjouterArcSortant(pARCNouvelArcS);
	SOMArrivee->SOMAjouterArcEntrant(pARCNouvelArcE);
	delete pARCNouvelArcE;
	delete pARCNouvelArcS;
	uiGRANbArcs++;
}

void CGraphe::GRAAjouterArc(int iDepart, int iArrivee)
{
	CArc* pARCNouvelArcE = new CArc(iDepart);
	CArc* pARCNouvelArcS = new CArc(iArrivee);
	GRARechercheSommet(iDepart)->SOMAjouterArcSortant(pARCNouvelArcS);
	GRARechercheSommet(iArrivee)->SOMAjouterArcEntrant(pARCNouvelArcE);
	delete pARCNouvelArcE;
	delete pARCNouvelArcS;
	uiGRANbArcs++;
}

void CGraphe::GRASupprimerArc(int iDepart, int iArrivee)
{
	CSommet* SOMEntrant = nullptr, * SOMSortant = nullptr;
	try {
		SOMEntrant = GRARechercheSommet(iDepart);
		SOMSortant = GRARechercheSommet(iArrivee);
	}
	catch (CException EXCException) {
		if (EXCException.EXCLireErreur() == EXCSuppImpossible) {
			cout << "Erreur : Suppression d'arc Impossible : La liste des arcs est vide !" << endl;
			throw CException(EXCArretProgramme);
		}
	}


	SOMEntrant->SOMSupprimerArcEntrant(pARCParam);
	SOMSortant->SOMSupprimerArcSortant(pARCParam);

	delete pARCParam;
	uiGRANbArcs--;
}

void CGraphe::GRAAjouterSommet(CSommet& SOMSommet)
{
	int iNum;
	unsigned int uiBoucle;
	char pcEntree[1024];

	while (!GRANumeroSommetUnique(SOMSommet.SOMLireNumero())) {
		cout << "Les numeros de sommets utilises sont :" << endl;
		for (uiBoucle = 0; uiBoucle < GRALireNbSommet(); uiBoucle++) {
			cout << GRALireSommets()[uiBoucle]->SOMLireNumero() << "  ";
		}
		cout << endl;
		cin >> pcEntree;
		iNum = atoi(pcEntree);
		SOMSommet.SOMModifierNumero(iNum);
		}

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

void CGraphe::GRAAjouterSommet(int iNum)
{
	unsigned int uiBoucle;
	char pcEntree[1024];
	CSommet* pSOMSommet = new CSommet(iNum);
	
	while (!GRANumeroSommetUnique(pSOMSommet->SOMLireNumero())) {
		cout << "Les numeros de sommets utilises sont :" << endl;
		for (uiBoucle = 0; uiBoucle < GRALireNbSommet(); uiBoucle++) {
			cout << GRALireSommets()[uiBoucle]->SOMLireNumero() << "  ";
		}
		cout << endl;
		cin >> pcEntree;
		iNum = atoi(pcEntree);
		pSOMSommet->SOMModifierNumero(iNum);
	}

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

void CGraphe::GRASupprimerSommet(int iNumSommet)
{
	unsigned int uiboucle, uiSommetTrouve = 0;
	int iNumeroSommetDestination;
	CArc* pARCArcASupprimer;

	for (uiboucle = 0; uiboucle < GRARechercheSommet(iNumSommet)->SOMLireNbArcsEntrants(); uiboucle++) {
		iNumeroSommetDestination = GRARechercheSommet(iNumSommet)->SOMLireArcsEntrants()[uiboucle]->ARCLireDestination();
		pARCArcASupprimer = (CArc*)GRARechercheSommet(iNumeroSommetDestination)->SOMRechercheArc(iNumSommet, entrant);

		GRARechercheSommet(iNumeroSommetDestination)->SOMSupprimerArcSortant(pARCArcASupprimer);
		GRARechercheSommet(iNumSommet)->SOMSupprimerArcEntrant(pARCArcASupprimer);
	}

	for (uiboucle = 0; uiboucle < GRARechercheSommet(iNumSommet)->SOMLireNbArcsSortants(); uiboucle++) {
		iNumeroSommetDestination = GRARechercheSommet(iNumSommet)->SOMLireArcsSortants()[uiboucle]->ARCLireDestination();
		pARCArcASupprimer = (CArc*)GRARechercheSommet(iNumeroSommetDestination)->SOMRechercheArc(iNumSommet, entrant);

		GRARechercheSommet(iNumeroSommetDestination)->SOMSupprimerArcEntrant(pARCArcASupprimer);
		GRARechercheSommet(iNumSommet)->SOMSupprimerArcSortant(pARCArcASupprimer);
	}


	for (uiboucle = 0; uiboucle < GRALireNbSommet() - 1; uiboucle++) {
		if (GRALireSommets()[uiboucle]->SOMLireNumero() == iNumSommet) {
			uiSommetTrouve = 1;
			delete ppSOMGRAListeSommet[uiboucle];
		}

		ppSOMGRAListeSommet[uiboucle] = ppSOMGRAListeSommet[uiboucle + uiSommetTrouve];
	}

	CSommet** ppSOMGRAListeSommetTMP = new CSommet * [uiGRANbSommet - 1];
	for (uiboucle = 0; uiboucle < uiGRANbSommet - 1; uiboucle++) {
		ppSOMGRAListeSommetTMP[uiboucle] = new CSommet(*ppSOMGRAListeSommet[uiboucle]);
	}


	for (uiboucle = 0; uiboucle < uiGRANbSommet; uiboucle++) {
		delete ppSOMGRAListeSommet[uiboucle];
		ppSOMGRAListeSommet[uiboucle] = nullptr;
	}
	delete[] ppSOMGRAListeSommet;


	uiGRANbSommet--;

}

void CGraphe::GRAModifierType(bool bParam)
{
	bGRAOriente = bParam;
}

CSommet* CGraphe::GRARechercheSommetAvecArc(CArc* pARCParam, int iParam) const
{
	unsigned int uiboucle, uiboucle2;
	if (iParam == entrant) {
		for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
			for (uiboucle2 = 0; uiboucle < GRALireSommets()[uiboucle]->SOMLireNbArcsEntrants(); uiboucle2++) {
				if (GRALireSommets()[uiboucle]->SOMLireArcsEntrants()[uiboucle2] == pARCParam) {
					return (CSommet*)GRALireSommets()[uiboucle];
				}
			}
		}
	}
	else if (iParam == sortant) {
		for (uiboucle = 0; uiboucle < GRALireNbSommet(); uiboucle++) {
			for (uiboucle2 = 0; uiboucle < GRALireSommets()[uiboucle]->SOMLireNbArcsSortants(); uiboucle2++) {
				if (GRALireSommets()[uiboucle]->SOMLireArcsSortants()[uiboucle2] == pARCParam) {
					return (CSommet*)GRALireSommets()[uiboucle];
				}
			}
		}
	}
	else {
		throw CException(EXCAucunParamRecherche);
		 
	}
	return (CSommet*)GRALireSommets()[0];
}

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

void CGraphe::GRAAffichage() const
{
	if (ppSOMGRAListeSommet == nullptr) {
		throw CException(EXCListeSommetInexistante);
	}
	unsigned int uiboucleSommet;
	unsigned int uiboucleArc;

	if (bGRAOriente == true) {
		cout << "Type de Graphe : Oriente" << endl;
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
			}
			cout << endl;
		}
	}
	else {
		cout << "Type de Graphe : Non-Oriente" << endl;
		for (uiboucleSommet = 0; uiboucleSommet < uiGRANbSommet; uiboucleSommet++) {
			cout << "Sommet " << GRALireSommets()[uiboucleSommet]->SOMLireNumero() << " : " << endl;
			for (uiboucleArc = 0; uiboucleArc < GRALireSommets()[uiboucleSommet]->SOMLireNbArcsSortants(); uiboucleArc++) {
				cout << "<--> " << GRALireSommets()[uiboucleSommet]->SOMLireArcsSortants()[uiboucleArc]->ARCLireDestination() << endl;
			}
			cout << endl;
		}
	}
}
