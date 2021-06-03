#ifndef AnaRoot_h
#define AnaRoot_h 0
#include "AnaDefs.hh"

#include "TObject.h"

class GeData : public TObject
{
public:
	GeData();
	~GeData();
//	virtual ~GeData(){}
	char   gmult;
	int    gtd;
	float  gen[NUMBER_OF_GE+1];
	double gt[NUMBER_OF_GE+1];
	double tgflt[2];
	double adctime[NUMBER_OF_GE+1];
	double Glf;			        //laser frequency

	void InitData()
	{
		int c;
		for(c=0;c<NUMBER_OF_GE+1;c++)
		{
			gen[c]	= -100;
			gtd   	=-50000;
			gt[c]	=-50000;
			gmult	= 0;
			adctime[c]	= -10000;
		}

		for(c=0;c<2;c++)
		{
			tgflt[c]	=-50000.;
		}
		Glf = -10;
	}

	ClassDef(GeData,1);
};

class SiData : public TObject
{
public:
	SiData();
	~SiData();
//	virtual ~SiData(){}
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

	void InitData()
	{
		int c;
		gmult	= 0;
		for(c=0;c<NUMBER_OF_GE+1;c++)
		{
			gen[c]	= -100.;
			gtd[c]	=-50000;
			gt[c]	=-50000;
			std[c]	=-50000;
		}
		for(c=0;c<NUMBER_OF_SI+1;c++)
		{
			senA[c]	=-1.;
			senF[c]	=-1.;
			st[c]	=-50000;
		}
		for(c=0;c<2;c++)
		{
			tgflt[c]	=-50000.;
		}
		smult		= 1;

		Glf = -10;
		Slf = -10;
	}

	ClassDef(SiData,1);
};

class SiSiData : public TObject
{
public:
	SiSiData();
	~SiSiData();
//	virtual ~SiSiData(){}
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

	void InitData()
	{
		EnFis_A1=-5;
		EnFis_A2=-10;
		EnFis_F1=-5;
		EnFis_F2=-10;
		MassLightFrag=-10;
		MassHeavyFrag=-20;
		EnLightFrag=-10;
		EnHeavyFrag=-5;
		En1AvEn=-10;
		En2AvEn=-5;
		En1neutron=-5;
		En2neutron=-10;
		mass1neutron=-5;
		mass2neutron=-10;

		Slf = -10;
		Glf = -10;

		int c, d;//, e;
		
		for(d=0;d<5;d++)
		{
			for(c=0;c<10;c++)
			{
				En1[d][c]=-5;//[e]=-5;
				En2[d][c]=-10;//[e]=-10;
				mass1[d][c]=-5;//[e]=-5;
				mass2[d][c]=-10;//[e]=-10;
				Channel1[d][c]=-2;//[e]=-2;
				Channel2[d][c]=-1;//[e]= -1;
			}
		}
	}

	ClassDef(SiSiData,1);
};

class FisEn : public TObject
{
public:
	FisEn();
	~FisEn();
//	virtual ~FisEn(){}
	double EnFis_A1_Corrected;
	double EnFis_A2_Corrected;
	double MassA1Correct;
	double MassA2Correct;   

	void InitData()
	{
		EnFis_A1_Corrected=-5;
		EnFis_A2_Corrected=-10;
		MassA1Correct=-5;
		MassA2Correct=-10;   
	}

	ClassDef(FisEn,1);
};

class SiGammaData : public TObject
{
public:
	SiGammaData();
	~SiGammaData();
//	virtual ~SiGammaData(){}
	double GammaEng;
	double SiEng;
	double TimeDiffSiGamma;

	void InitData()
	{
		GammaEng=-10;
		SiEng=-10;
		TimeDiffSiGamma=-50000;
	}

	ClassDef(SiGammaData,1);
};

class SinglesCal : public TObject
{
public:
	SinglesCal();
	~SinglesCal();
//	virtual ~SinglesCal(){}
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
//	virtual ~HFSData(){}
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
	
	void InitData()
	{
		for(int i=1;i<NUMBER_OF_GE+1;i++)
		{
			GEng[i]=-50000;
			gt[i]=-50000;
		}

		for(int i=1;i<NUMBER_OF_SI+1;i++)
		{
			SEng[i]=-10000;
			st[i]	=-50000;
		}
		for(short c=0;c<4;c++)
		{
			tgflt[c]	=-50000.;
		}
		GsCycle = -10;
		SsCycle = -10;
		Slf = -10;
		Glf = -10;
		sid = -10;
		gid = -10;
		pulserEvent = -99.;	// JGC pulser
		pulserTime  = -99.;	// JGC pulser
	}

	ClassDef(HFSData,1);
};

class SingleData : public TObject
{
public:
	SingleData();
	~SingleData();
//	virtual ~SingleData(){}
	double gEng[NUMBER_OF_GE+1];//from 1
	double sEng[NUMBER_OF_SI+1];//from 1
	double st[NUMBER_OF_SI+1] ; //from 1
	double gt[NUMBER_OF_GE+1];  //from 1
	double tgflt[4];
	double pulserEvent;			//JGC pulser
	double pulserTime;			//JGC pulser

	void InitData()
	{
		for(int i=1;i<NUMBER_OF_GE+1;i++)
		{
			gEng[i]=-50000;
			gt[i]=-50000;
		}

		for(int i=1;i<NUMBER_OF_SI+1;i++)
		{
			sEng[i]=-10000;
			st[i] =-50000;
		}
		for(short c=0;c<4;c++)
		{
			tgflt[c]     =-50000.;
		}
		pulserEvent = -99.;	// JGC pulser
		pulserTime  = -99.;	// JGC pulser
	}

	ClassDef(SingleData,1);
};

class PulserData : public TObject
{
public:
	PulserData();
	~PulserData();
//	virtual ~PulserData(){}
	double pulserEvent;			//JGC pulser
	double pulserTime;			//JGC pulser
	double tgflt[4];

	void InitData()
	{
		pulserEvent = -99.;	// JGC pulser
		pulserTime  = -99.;	// JGC pulser

		for(short c=0;c<4;c++)
		{
			tgflt[c]	=-50000.;
		}
	}

	ClassDef(PulserData,1);
};

#endif