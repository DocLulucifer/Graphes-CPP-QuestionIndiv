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
	CArc();
	CArc(CArc& ARCParam);
	CArc(int iParam);
	~CArc();

	//Accesseur
	int ARCLireDestination();

	//Modifieur
	void ARCChangerDestination(int iDestination);

	//Surcharge
	CArc& operator=(CArc ARCparam);
};

#endif