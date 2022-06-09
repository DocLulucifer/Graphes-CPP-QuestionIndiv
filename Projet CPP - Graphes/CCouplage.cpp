#include "CCouplage.h"

CCouplage::CCouplage()
{
	ppiArcs = nullptr;
	uiNbArcs = 0;
}

CCouplage::CCouplage(CCouplage& COUCouplage)
{
	unsigned int uiboucle;
	ppiArcs = new int* [COUCouplage.COULireNbArcs()];
	for (uiboucle = 0; uiboucle < COUCouplage.COULireNbArcs(); uiboucle++) {
		ppiArcs[uiboucle] = new int[2];
	}


	for (uiboucle = 0; uiboucle < COUCouplage.COULireNbArcs(); uiboucle++) {
		ppiArcs[uiboucle][0] = COUCouplage.COULireValeur(uiboucle, 0);
		ppiArcs[uiboucle][1] = COUCouplage.COULireValeur(uiboucle, 1);
	}
	uiNbArcs = COUCouplage.COULireNbArcs();
}

CCouplage::~CCouplage()
{
	unsigned int uiboucle;
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;
	uiNbArcs = 0;
}

int CCouplage::COULireValeur(unsigned int uiIndice1, unsigned int uiIndice2)
{
	if (!(uiIndice1 < uiNbArcs && uiIndice2 < 2)) {
		throw CException(EXCErreurSegmentation);
	}
	return ppiArcs[uiIndice1][uiIndice2];
}

void CCouplage::COUEcritureValeur(unsigned int uiIndice1, unsigned int uiIndice2, int iValeur)
{
	if (!(uiIndice1 < uiNbArcs && uiIndice2 < 2)) {
		throw CException(EXCErreurSegmentation);
	}
	ppiArcs[uiIndice1][uiIndice2] = iValeur;
}

unsigned int CCouplage::COULireNbArcs()
{
	return uiNbArcs;
}

void CCouplage::COUAjouterArc(int* piArc)
{
	if (piArc == nullptr) {
		throw CException(EXCPointeurAjoutArcNul);
	}
	unsigned int uiboucle;
	int** ppiNouveau = new int* [uiNbArcs + 1];
	for (uiboucle = 0; uiboucle < uiNbArcs + 1; uiboucle++) {
		ppiNouveau[uiboucle] = new int[2];
	}
	
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		ppiNouveau[uiboucle][0] = ppiArcs[uiboucle][0];
		ppiNouveau[uiboucle][1] = ppiArcs[uiboucle][1];
	}
	
	ppiNouveau[uiNbArcs][0] = piArc[0];
	ppiNouveau[uiNbArcs][1] = piArc[1];

	for (uiboucle = 0 ; uiboucle < uiNbArcs; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;
	uiNbArcs++;
	ppiArcs = ppiNouveau;
}

void CCouplage::COUSupprimerArc(unsigned int uiIndice)
{
	if (!(uiIndice < uiNbArcs)) {
		throw CException(EXCSuppArcCouplageImpossible);
	}
	int** ppiNouveau = new int* [uiNbArcs - 1];
	unsigned int uiboucle, uiArcTrouve = 0;
	for (uiboucle = 0; uiboucle < uiboucle - 1; uiboucle++) {
		ppiNouveau[uiboucle] = new int[2];
	}

	for (uiboucle = 0; uiboucle < uiNbArcs - 1; uiboucle++) {
		if (uiboucle == uiIndice) {
			uiArcTrouve++;
		}
		ppiNouveau[uiboucle][0] = ppiArcs[uiboucle + uiArcTrouve][0];
		ppiNouveau[uiboucle][1] = ppiArcs[uiboucle + uiArcTrouve][1];
	}
	
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		delete[] ppiArcs[uiboucle];
	}
	delete[] ppiArcs;
	uiNbArcs--;
	ppiArcs = ppiNouveau;
}

CCouplage& CCouplage::operator=(CCouplage& COUCouplage)
{
	unsigned int uiboucle;
	
	if(uiNbArcs != COUCouplage.COULireNbArcs())
	{
		for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
			delete[] ppiArcs[uiboucle];
		}
		delete[] ppiArcs;
		uiNbArcs = COUCouplage.COULireNbArcs();
		ppiArcs = new int* [uiNbArcs];
		for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
			ppiArcs[uiboucle] = new int[2];
		}
	}
	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		ppiArcs[uiboucle][0] = COUCouplage.COULireValeur(uiboucle, 0);
		ppiArcs[uiboucle][1] = COUCouplage.COULireValeur(uiboucle, 1);
	}
	
	return *this;
}


void CCouplage::COUAfficherCouplage()
{
	unsigned int uiboucle;

	for (uiboucle = 0; uiboucle < uiNbArcs; uiboucle++) {
		cout << ppiArcs[uiboucle][0] << " <---> " << ppiArcs[uiboucle][1] << endl;
	}

	cout << endl;
}
