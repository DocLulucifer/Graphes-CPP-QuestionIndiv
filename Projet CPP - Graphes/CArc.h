#ifndef ARC
#define ARC

#define entrant 0
#define sortant 1
#define EXCArretProgramme 50

class CArc {
private :

	//Attribut
	int iARCNumeroSommet;
public :

	//Constructeurs & Destructeurs

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un objet CArc par d�faut											   ****
	******************************************************************************************************/
	CArc();

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un objet CArc par recopie										   ****
	******************************************************************************************************/
	CArc(const CArc& ARCParam);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Construction d'un objet CArc par valeur de destination							   ****
	******************************************************************************************************/
	CArc(int iParam);

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne : Destruction d'un objet CArc par d�faut											   ****
	******************************************************************************************************/
	~CArc();

	//Accesseur

	/******************************************************************************************************
	**** Entr�es :																					   ****
	**** N�cessite :																		  	       ****
	**** Sorties :	int iARCNumeroSommet : Destination de l'arc										   ****
	**** Entra�ne :	Lecture de valeur de destination de l'arc	 									   ****
	******************************************************************************************************/
	int ARCLireDestination() const;

	//Modifieur

	/******************************************************************************************************
	**** Entr�es :	int iDestination : Nouvelle destination de l'arc								   ****
	**** N�cessite :																		  	       ****
	**** Sorties :																					   ****
	**** Entra�ne :	Changement de valeur de destination de l'arc									   ****
	******************************************************************************************************/
	void ARCChangerDestination(int iDestination);

	//Surcharge

	/******************************************************************************************************
	**** Entr�es : const CArc ARCparam : CArc � copier												   ****
	**** N�cessite : ARCparam non nul														  	       ****
	**** Sorties :	CArc & this : Objet modifi� selon le param�tre									   ****
	**** Entra�ne : La copie de l'objet CArc en param�tre											   ****
	******************************************************************************************************/
	CArc& operator=(const CArc ARCparam);
};

#endif