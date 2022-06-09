#ifndef COUPLAGE
#define COUPLAGE

#pragma warning(disable : 6001)
#pragma warning(disable : 6386)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "CException.h"

#define EXCSuppArcCouplageImpossible 70
#define EXCPointeurAjoutArcNul 71

using namespace std;

class CCouplage {
private:
	int** ppiArcs;
	unsigned int uiNbArcs;
public:
	CCouplage();
	CCouplage(CCouplage& COUCouplage);
	~CCouplage();

	int COULireValeur(unsigned int uiIndice1, unsigned int uiIndice2);
	void COUEcritureValeur(unsigned int uiIndice1, unsigned int uiIndice2, int iValeur);
	unsigned int COULireNbArcs();

	void COUAjouterArc(int* piArc);
	void COUSupprimerArc(unsigned int uiIndice);

	void COUAfficherCouplage();
	
	CCouplage& operator=(CCouplage& COUCouplage);
};



#endif // !COUPLAGE
