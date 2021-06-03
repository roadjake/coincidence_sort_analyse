#ifndef AnaRoot_h
#define AnaRoot_h 0
#include "AnaDefs.hh"

#include "TObject.h"

ClassImp(SingleData);
SingleData::SingleData(){}
SingleData::~SingleData(){}

class GeData : public TObject
{
public:
	GeData();
	~GeData();
	char   gmult;
	int    gtd;
	float  gen[NUMBER_OF_GE+1];
	double gt[NUMBER_OF_GE+1];
	double tgflt[2];
	double adctime[NUMBER_OF_GE+1];
	double Glf;			        //laser frequency

	ClassDef(GeData,1);
};

class SiData : public TObject
{
public:
	SiData();
	~SiData();
	int    smult; 					// Si multiplicity
	int    gmult;						// Ge mult
	int    gtd[NUMBER_OF_GE+1];		// Ge time diff (st-gt)	
	int    std[NUMBER_OF_GE+1];		// was 5, Si-Si time/ dif  Si1-Si2 and Si3-Si4
	float  gen[NUMBER_OF_GE+1];		// Ge energy
	double gt[NUMBER_OF_GE+1];		// Ge time (absolute time, total time)
	float  senA[NUMBER_OF_SI+1];		// Si energy based on alpha calibration
	float  senF[NUMBER_OF_SI+1];		// Si energy based on fission calibration
	double st[NUMBER_OF_SI+1];		// Si time (absolute time, total time)
	double tgflt[2];					// Ge time
	double Glf;						// laser frequency
	double Slf;

	ClassDef(SiData,1);
};

class SiSiData : public TObject
{
public:
	SiSiData();
	~SiSiData();
	double En1[5][10];//[6];
	double En2[5][10];//[6];
	double mass1[5][10];//[6];
	double mass2[5][10];//[6];
	double EnFis_A1;
	double EnFis_A2;
	double Channel1[5][10];//[6];
	double Channel2[5][10];//[6];
	double EnFis_F1;
	double EnFis_F2;
	double MassLightFrag;
	double MassHeavyFrag;
	double EnLightFrag;
	double EnHeavyFrag;
	double En1AvEn;
	double En2AvEn;
	double En1neutron;
	double En2neutron;
	double mass1neutron;
	double mass2neutron;

	double Slf;
	double Glf;

	ClassDef(SiSiData,1);
};

class FisEn : public TObject
{
public:
	FisEn();
	~FisEn();
	double EnFis_A1_Corrected;
	double EnFis_A2_Corrected;
	double MassA1Correct;
	double MassA2Correct;   

	ClassDef(FisEn,1);
};

class SiGammaData : public TObject
{
public:
	SiGammaData();
	~SiGammaData();
	double GammaEng;
	double SiEng;
	double TimeDiffSiGamma;

	ClassDef(SiGammaData,1);
};

class SinglesCal : public TObject
{
public:
	SinglesCal();
	~SinglesCal();
	double SingleFisEn1[20];
	double SingleFisEn2[20];

	void InitData()
	{
		int s;
		for(s=0; s<20; s++)
		{
			SingleFisEn1[s]=-10;
			SingleFisEn2[s]=-5;
		}
	}

	ClassDef(SinglesCal,1);
};

class HFSData : public TObject
{
public:
	HFSData();
	~HFSData();
	double GEng[NUMBER_OF_GE+1];//from 1
	double SEng[NUMBER_OF_SI+1];//from 1
	int    GsCycle;
	int    SsCycle;
	int    gid; 			//Ge id

	double Glf;			//laser frequency
	double Slf;

	int    sid;			//Si id
	double st[NUMBER_OF_SI+1]; //from 1
	double gt[NUMBER_OF_GE+1]; //from 1
	double tgflt[4];
	double pulserEvent;			//JGC pulser
	double pulserTime;			//JGC pulser

	ClassDef(HFSData,1);
};

class SingleData : public TObject
{
public:
	SingleData();
	~SingleData();
	double gEng[NUMBER_OF_GE+1];//from 1
	double sEng[NUMBER_OF_SI+1];//from 1
	double st[NUMBER_OF_SI+1] ; //from 1
	double gt[NUMBER_OF_GE+1];  //from 1
	double tgflt[4];
	double pulserEvent;			//JGC pulser
	double pulserTime;			//JGC pulser

	ClassDef(SingleData,1);
};

class PulserData : public TObject
{
public:
	PulserData();
	~PulserData();
	double pulserEvent;			//JGC pulser
	double pulserTime;			//JGC pulser
	double tgflt[4];

	ClassDef(PulserData,1);
};

#endif
