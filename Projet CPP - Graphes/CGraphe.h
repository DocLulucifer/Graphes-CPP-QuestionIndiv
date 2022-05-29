#ifndef GRAPHE
#define GRAPHE

#pragma warning(disable : 6386)

#include "CSommet.h"
#include "CException.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>

#define EXCAucunParamRecherche 20
#define EXCValeurSommetIntrouvable 21
#define EXCListeSommetInexistante 22
#define EXCPointeurSommetNul 23
#define EXCNumeroIndisponible 24

class CSommet;
class CArc;

class CGraphe {
private :

	//Attributs
	CSommet** ppSOMGRAListeSommet;
	unsigned int uiGRANbSommet;
	unsigned int uiGRANbArcs;
	bool bGRAOriente;

public :

	//Constructeur & Destructeur
	
	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un objet CGraphe par d�faut										   ****
	******************************************************************************************************/
	CGraphe();

	/******************************************************************************************************
	**** Entr�es : GRAGraphe : CGraphe&																   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un objet CGraphe par recopie de GRAGraphe						   ****
	******************************************************************************************************/
	CGraphe(const CGraphe& GRAGraphe);
	
	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Destruction de l'objet CGraphe													   ****
	******************************************************************************************************/
	~CGraphe();

	//Accesseurs
	
	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : ppSOMGRAListeSommet : CSommet**													   ****
	**** Entra�ne : Renvoie la liste des sommets de l'objet CGraphe									   ****
	******************************************************************************************************/
	const CSommet* const* GRALireSommets() const;
	
	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : uiGRANbSommet : unsigned int														   ****
	**** Entra�ne : Renvoie le nombre de sommet de l'objet CGraphe									   ****
	******************************************************************************************************/
	unsigned int GRALireNbSommet() const;

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : uiGRANbArcs : unsigned int														   ****
	**** Entra�ne : Renvoie le nombre d'arcs de l'objet CGraphe										   ****
	******************************************************************************************************/
	unsigned int GRALireNbArcs() const;

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties : bGRAOriente : bool																   ****
	**** Entra�ne : Renvoie le type de l'objet CGraphe (1 si oriente, 0 si non-oriente)				   ****
	******************************************************************************************************/
	bool GRALireType() const;

	//Modifieurs
	
	/******************************************************************************************************
	**** Entr�es : pSomDepart : CSommet*, pSOMArrivee : CSommet*									   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Cr�e un arc partant du sommet pSOMDepart allant vers le sommet pSOMArrivee		   ****
	******************************************************************************************************/
	void GRAAjouterArc(CSommet* pSOMDepart, CSommet* pSOMArrivee);

	/*****************************************************************************************************************
	**** Entr�es : iDepart : int, iArrivee : int															      ****
	**** N�cessite :																		  				      ****
	**** Sorties :																								  ****
	**** Entra�ne : Cr�e un arc partant du sommet ayant le numero iDepart vers le sommet ayant le num�ro iArrivee ****
	*****************************************************************************************************************/
	void GRAAjouterArc(int iDepart, int iArrivee);

	/*********************************************************************************************************
	**** Entr�es : iDepart : int, iArrivee : int														  ****
	**** N�cessite :																		  			  ****
	**** Sorties :																						  ****
	**** Entra�ne : Supprime l'arc partant du sommet num�ro iDepart allant vers le sommet num�ro iArrivee ****
	*********************************************************************************************************/
	void GRASupprimerArc(int iDepart, int iArrivee);

	/******************************************************************************************************
	**** Entr�es : SOMSommet CSommet&																   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Ajoute le sommet SOMSommet au graphe											   ****
	******************************************************************************************************/
	void GRAAjouterSommet(CSommet& SOMSommet);

	/******************************************************************************************************
	**** Entr�es : iNum : int																		   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Ajoute le sommet numero iNum au graphe											   ****
	******************************************************************************************************/
	void GRAAjouterSommet(int iNum);
	
	/******************************************************************************************************
	**** Entr�es : pSOMParam : CSommet*																   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Supprime le sommet pSOMParam du graphe											   ****
	******************************************************************************************************/
	void GRASupprimerSommet(CSommet* pSOMParam);

	/******************************************************************************************************
	**** Entr�es : pSOMParam : CSommet*, iNum : int													   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Modifie le num�ro du sommet pSOMParam par le numero iNum						   ****
	******************************************************************************************************/
	void GRAModifierNumSommet(CSommet* pSOMParam, int iNum);
	
	/******************************************************************************************************
	**** Entr�es : bParam : bool																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Modifie le type du graphe (0 = non-orient�, 1 = orient�)						   ****
	******************************************************************************************************/
	void GRAModifierType(bool bParam);

	//M�thodes

	/*************************************************************************************************************
	**** Entr�es : iVal : int																				  ****
	**** N�cessite :																		  				  ****
	**** Sorties : CSommet*																					  ****
	**** Entra�ne : Renvoie un pointeur sur le sommet num�ro iVal s'il existe, renvoie un pointeur null sinon ****
	*************************************************************************************************************/
	CSommet* GRARechercheSommet(int iVal) const;

	/******************************************************************************************************
	**** Entr�es : iSommet : int																	   ****
	**** N�cessite :																		  	       ****
	**** Sorties : int																				   ****
	**** Entra�ne : Renvoie la position du sommet num�ro iSommet s'il existe, -1 sinon				   ****
	******************************************************************************************************/
	int GRARechercheIndexSommet(int iSommet) const;

	/******************************************************************************************************
	**** Entr�es : iVal	: int																		   ****
	**** N�cessite :																		  	       ****
	**** Sorties : bool																				   ****
	**** Entra�ne : Renvoie true si le sommet num�ro iVal n'existe pas, false sinon					   ****
	******************************************************************************************************/
	bool GRANumeroSommetUnique(int iVal);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Fonction d'affichage du graphe													   ****
	******************************************************************************************************/
	void GRAAffichage() const;

	//Surcharge
	
	/******************************************************************************************************
	**** Entr�es : GRAParam : CGraphe&																   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : La copie de l'objet CGraphe en param�tre										   ****
	******************************************************************************************************/
	CGraphe& operator=(const CGraphe &GRAParam);
};

#endif