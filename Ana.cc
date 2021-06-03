// -------------------------------------------------
// J.G.C 10/06/2019 - WM sort code for root6
// -------------------------------------------------
#include "Ana.hh"
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <string>

#include "AnaRoot.hh"

GeData::GeData(){}
GeData::~GeData(){}
SiData::SiData(){}
SiData::~SiData(){}
SiSiData::SiSiData(){}
SiSiData::~SiSiData(){}
FisEn::FisEn(){}
FisEn::~FisEn(){}
SiGammaData::SiGammaData(){}
SiGammaData::~SiGammaData(){}
SinglesCal::SinglesCal(){}
SinglesCal::~SinglesCal(){}
HFSData::HFSData(){}
HFSData::~HFSData(){}
SingleData::SingleData(){}
SingleData::~SingleData(){}
PulserData::PulserData(){}
PulserData::~PulserData(){}

using namespace std;

Ana::Ana(){}
Ana::~Ana(){}

// Reads the configuration file for the analysis
int Ana::Init()
{
	int i;
	char hname[100],htitle[256];
	string rootfile;
	char sda[512];

	string HIST_FILE, FIS_CAL, FREQ_FILE;

	COINC_TREE_SS=0;
	COINC_TREE_GG=0;
	LOWER_E=0;
	UPPER_E=0;
	USE_FIS_CAL=0;
	USE_HYPER=0;

	int nLine = 0;

	cout << "\033[1;93m";
	cout << "  ============================================= \n";
	cout << "  =              Start of WM sort             = \n";
	cout << "  ============================================= \n\n";
	ifstream ipFile;
	string cline;
	string cfile = "config.cfg";
	cout << "  Configuration file: " << cfile << "\n";

	if(cfile!="NONE")
	{
		ipFile.open(cfile.c_str());
		if(!ipFile.is_open())
		{
			cout << "  No config file, exiting sort." << endl;
			exit(1);
		}
		else
		{
			while(!ipFile.eof())
			{
				getline(ipFile,cline); //read the name of the file with data files and calibrations	// ER:  File .TXT  --> Do not use it anymore! 
				if(cline[0]!='#')
				{
					if(nLine==1)
					{
						DATA_CALIB_FILE = cline;
					}
					if(nLine==3)
					{
						HIST_FILE=cline;
						cout << "  Histogram definitions from file: " << HIST_FILE << "\n";
					}
					if(nLine==5)
					{
						FIS_CAL=cline;
					}
					if(nLine==7 && cline[0]=='1')
					{
						USE_FIS_CAL=1;
						cout << "  Calibrations are from file: " << FIS_CAL << "\n\n";
						cout << "  USING FISSION CALIBRATION" << "\n";
					}
					else if(nLine==7 && cline[0]=='0') cout << "  Calibrations taken from file: " << DATA_CALIB_FILE << "\n\n";
					if(nLine==9 && cline[0]=='1')
					{
						USE_HYPER=1;
						cout << "  USE HYPERFINE SPLITTING" << "\n";
					}
					if(nLine==11 && cline[0]=='1')
					{
						COINC_TREE_SS=1;
						cout << "  USE COINC_TREE Si-Si" << "\n";
					}
					if(nLine==13 && cline[0]=='1')
					{
						COINC_TREE_GG=1;
						cout << "  USE COINC_TREE GAMMA-GAMMA" << "\n\n";
					}
					if(nLine==15)
					{
						LOWER_E=atof(cline.c_str());
						cout << "  LOWER ENERGY: " << LOWER_E << "\n";
					}
					if(nLine==17)
					{
						UPPER_E=atof(cline.c_str());
						cout << "  UPPER ENERGY: " << UPPER_E << "\n";
					}

				}
				nLine++;
			}
		
		if ((COINC_TREE_SS ==0) && (COINC_TREE_GG==0)) cout << "  SINGLES ONLY, NO COINCIDENCE TREES!" << endl;
		}
	}

	// Ask for and open root file. This will overwrite any root file existing with the same name.
	
	cout << "\n  ---------------------------------------------\n\n";
	
	cout << "  Give root filename:\n";
	cin  >> rootfile;
	cout << "  Output root file: " << rootfile << "\n\n";
	readouts= 0;
	rootFile= new TFile(rootfile.c_str(),"RECREATE");
	if(!(rootFile->IsOpen())) cout << "  ERROR: Could not open root file!\n";


	for(i=0;i<NUMBER_OF_GFLT;i++)
	{
		GFLTtime[i]= 0;
		sprintf(hname,"GFLT%d",i);
		sprintf(htitle,"Time Difference between GFLTs #%d",i);
		GFLT[i]= new TH1F(hname,htitle,4000,-200,200);
	}
	for(i=0;i<NUMBER_OF_DGFS;i++)
	{
		sprintf(hname,"DGFevts%02d",i);
		sprintf(htitle,"Number of events in the buffers of the dgf #%02d",i);
		DGFevts[i]= new TH1F(hname,htitle,3000,0,3000.);
	}

	for(i=0;i<NUMBER_OF_CHANNELS*NUMBER_OF_DGFS;i++)
	{
		sprintf(hname,"xia%02d",i);
		sprintf(htitle,"Uncalibrated Energy for ch %d",i);
		UncXIA[i] = new TH1F(hname,htitle,32768,0.,65536.);
		sprintf(hname,"eng%02d",i);
		sprintf(htitle,"Energy for ch %d",i);
		CalXIA[i] = new TH1F(hname,htitle,5000,0.,10000.);
	}

	/* create all histograms, definitions are taken from the HIST_FILE */
	FILE* fp;
	char line[512];
	int HistNum, NBins, StartCh, StopCh;
	char HistName[128];

	if(HIST_FILE!="NONE")
	{
		fp=fopen(HIST_FILE.c_str(),"r");
		if(fp!=NULL)
		{
			while(fgets(line,512,fp) != NULL)
			{
				if(line[0]!='#')
				{
					sscanf(line,"%d %s %d %d %d",&HistNum,HistName,&NBins,&StartCh,&StopCh);
					Hist[HistNum] = new TH1F(HistName,HistName,NBins,StartCh,StopCh);      
				}
			}
		}
	}

	//read fission calibration from file FIS_CAL
	FILE* fis;
	char aline[512];
	double Afis, Bfis;
	int num;

	if(USE_FIS_CAL)
	{ 
		if(FIS_CAL!="NONE")
		{
			fis=fopen(FIS_CAL.c_str(),"r");
			if(fis!=NULL)
			{
				while(fgets(aline,512,fis) != NULL)
				{
					if(aline[0]!='#')
					{
						sscanf(aline, "%d %lf %lf",&num,&Bfis,&Afis);
						cout << "num: " << num << ", Bfis: " << Bfis << ", Afis: " << Afis << "\n";
						FissionCalB[num-1]=Bfis;
						FissionCalA[num-1]=Afis;
					}
				}
			}
		}
	}

	FILE* ffr;
	char fline[512]; 
	int hh, mm, ss, laserstep;
	double presetfreq,frequency,lstep,timeF;
	char date[20];

	if(USE_HYPER)
	{
		cout << "  Give laser frequency filename (.txt):\n";
		cin  >> FREQ_FILE;
		cout << "  Frequency file used: " << FREQ_FILE << "\n";

		if(FREQ_FILE!="NONE")
		{
			ffr=fopen(FREQ_FILE.c_str(),"r"); 
			if(ffr==NULL) { cout << "  The input laser frequency file " << FREQ_FILE << " does not exist! -> Abort!\n"; exit(1); } 
			if(ffr!=NULL)
			{
				while(fgets(fline,512,ffr) != NULL)
				{
				//	sscanf(fline, "%s %d:%d:%d %d %lf %lf %lf",date,&hh,&mm,&ss,&laserstep,&presetfreq,&frequency,&lstep);	 // adding '&presetfreq' to shift along the columns - frequency was reading present frequency, and lstep was reading average frequency, not integral - GLW, JGC 19/09/14

					// Old version
					sscanf(fline, "%s %d:%d:%d %d %lf %lf",date,&hh,&mm,&ss,&laserstep,&frequency,&lstep);	 
					printf("date: %s, ora: %d, min: %d, sec: %d\n",date,hh,mm,ss);  
					printf("laserstep: %d, frequency: %lf, step laser: %lf\n",laserstep,frequency,lstep);
					timeF=ss+60*mm+3600*hh;
					freq[laserstep]=frequency;
					timeabs[laserstep]=timeF;
				}
				printf(" il file contiene:  %d steps\n",laserstep);
				if(freq[1] == 0.0)
				{
					cout << "Warning, the first frequency in the laser file = 0.0 !!!!!\n";
					EXTRA_FREQ = 1;
				}
			}	 
		}
	}

	/* ----------------- create Tree ------------------------*/
	GeTree= new TTree("gg","Ge-Ge Coincidence Data");
	SiTree= new TTree("sg","Si-Ge Coincidence Data");	// and I think also singles!
	ge_data= new GeData();
	si_data= new SiData();

	//create tree with Si and Ge HFS data.			//ER
	HFSTree = new TTree("hfs","Hyperfine splitting Data" );
	hfs_data= new HFSData();

	//create Single tree with Si and Ge  singles 			//ER
	SingleTree = new TTree ("single_data","SI and Ge singles");
	single_data=new SingleData();

	GeTree->Branch("GeData","GeData",&ge_data);
	SiTree->Branch("SiData","SiData",&si_data);
	HFSTree->Branch("HFSData","HFSData",&hfs_data);
	SingleTree->Branch("SingleData","SingleData",&single_data);

	//create tree with si-gamma coincidences, leaf of gamma energy, si energy and time difference between si event and gamma ray
	SiGammaT = new TTree("SiGammaT","Si-Gamma Coincidence Data");
	si_gamma=new SiGammaData();
	SiGammaT->Branch("SiGammaData", "SiGammaData", &si_gamma);

	/*********************************************************/	// JGC 13/01/2016
	// Create pulser tree						//
	PulserTree  = new TTree("Pulser","Pulser Data");			//
	pulser_data = new PulserData();					//
	PulserTree->Branch("PulserData","PulserData",&pulser_data);	//
	/*********************************************************/	// JGC 13/01/2016

	//histograms of the branches used in the Si and GeTree 
	smultSi = new TH1F("smultSi", "silicon multiplicity", 5, 0, 5);
	gmultSi = new TH1F("gmultSi", "gamma multiplicity", 8, 0, 8);
	stdSi   = new TH1F("stdSi", "silicon time difference", 10, -2000, 2000); 
	gtdSi   = new TH1F("gtdSi", "Ge time difference", 100, -5000, 5000); 
	senASi  = new TH1F("senASi", "silicon energy (alpha calibration)", 16000,-20000,140000);
	senFSi  = new TH1F("senFSi", "silicon energy (fission calibration)", 4096,-1,165);
	genSi   = new TH1F("genSi", "Ge energy", 2500, 0,5000); 
	stSi    = new TH1F("stSi", "silicon time", 2500000,-60000000, 1200000000); 
	gtSi    = new TH1F("gtSi", "Ge time", 2500000,-60000000, 1200000000); 

	gg_mat = new TH2D("gg_mat","Gamma-gamma matrix, 1x1 kev bin",4500,0,4500,4500,0,4500);

	//2D histogram showing the si-si coincidences alpha and fission calibrated and Si-gamma coincidendes
	ssA   = new TH2F("ssA","si-si coincidence 2D (alpha calibration) histogram",500,5000,100000,500,5000,100000);
	ssF   = new TH2F("ssF","si-si coincidence 2D (fission calibration) histogram",500,5,165,500,5,165);
	sigeA = new TH2F("sigeA", "silicon-gamma coincidence 2D histogram (alpha calibration)", 5000,0,10000,1000,0,1000);
	sigeF = new TH2F("sigeF", "silicon-gamma coincidence 2D histogram (fission calibration)", 1000,0,100000,1000,0,1000);

	GammaEngTime = new TNtuple("GammaEngTime","Gamma energy and time","geng:gtime:ndet");

	return 0;
}

void Ana::Build(ANA_BUFFER *evp)
{
	double EEngA,BTime,EngA, EngF, EEngF;
	int temp;
	int ADCeng,cTD,BestTD,XIAC, ADCeng2;
	double ADCtime;
	short XIAmod,XIAnofsubevts,XIAsubevt,modchan,XIAchan,BestEvt,i,sg,i_R,N_R,i_C,N_C,i_SI,N_SI,i_GE,N_GE,chan,chan2,N_PUL;
  
	/* Histograms */
	for(XIAmod = 0; XIAmod<NUMBER_OF_GFLT; XIAmod++)
	{
		for(i=0; i<evp->dgf[GFLT_MODULES[XIAmod]].numofevents; i++)
		{
			if((evp->dgf[GFLT_MODULES[XIAmod]].energy[i][GFLT_CHANNELS[XIAmod]] > 0) && (evp->dgf[GFLT_MODULES[XIAmod]].lFTtime[i][GFLT_CHANNELS[XIAmod]]>0))
			{
     
				if (XIAmod==0) //GFLT_SC 
				{ 
					sCycleNumber+=1;
					cout << "\033[34m     Number of openings of ACQ gate " << sCycleNumber << "\n";
					checkTime=(evp->dgf[GFLT_MODULES[XIAmod]].lFTtime[i][GFLT_CHANNELS[XIAmod]])/40.;
				}

				if(GFLTtime[XIAmod] > 0)
				{
					// nel programma di Valentina il supercycle e' contato dentro questo IF
					// il che vuol dire che il primo ACQ gate aperto e' contato come 0
					BTime= (evp->dgf[GFLT_MODULES[XIAmod]].lFTtime[i][GFLT_CHANNELS[XIAmod]] - GFLTtime[XIAmod])/40000000.;

					GFLT[XIAmod]->Fill(BTime);
				}
				
				GFLTtime[XIAmod] = evp->dgf[GFLT_MODULES[XIAmod]].lFTtime[i][GFLT_CHANNELS[XIAmod]];
			}
		}
	}

	//Energy histograms Si, Alpha, Gamma
	for(XIAmod = 0; XIAmod<NUMBER_OF_DGFS; XIAmod++)
	{
		XIAnofsubevts=evp->dgf[XIAmod].numofevents;
		for(XIAsubevt=0; XIAsubevt<XIAnofsubevts; XIAsubevt++)
		{
			for(modchan=0; modchan<NUMBER_OF_CHANNELS; modchan++)
			{
				XIAchan = XIAmod*NUMBER_OF_CHANNELS + modchan;
				ADCeng = evp->dgf[XIAmod].energy[XIAsubevt][modchan];
				ADCtime = (double)evp->dgf[XIAmod].lFTtime[XIAsubevt][modchan]/40.;

				if((ADCeng > 0) && (evp->dgf[XIAmod].lFTtime[XIAsubevt][modchan] > 0));
				{
					// NOTA BENE: Si potrebbero scrivere i tempi --> Vedi Valentina //ER
					UncXIA[XIAchan]->Fill(ADCeng);
					EngA=xia_offsetA[XIAchan] + xia_gain_1A[XIAchan]*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_2A[XIAchan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX);
					EngF=FissionCalB[XIAchan] + FissionCalA[XIAchan]*(ADCeng + rand()/(float)RAND_MAX);
					CalXIA[XIAchan]->Fill(EngA);

					//Gamma Energy
					if(XIAchan == 0 || XIAchan == 4 )
					{
						single_data->InitData();
						single_data->gEng[1+XIAchan/4]	= EngA;
						single_data->gt[1+XIAchan/4]   = ADCtime; 
						single_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
						single_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
						single_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
						single_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate

						/*if ((COINC_TREE_SS ==0) && (COINC_TREE_GG==0))*/ SingleTree->Fill();
						Hist[61+XIAchan/4]->Fill(EngA); 		//61 = gamma1e and 62 = gamma2e
						Hist[65]->Fill(EngA);					//65 = sumgamma
						if((ADCtime-GFLTtime[1]/40.)/1000000>0.02 && (ADCtime-GFLTtime[1]/40.)/1000000<0.2)Hist[63+XIAchan/4]->Fill(EngA); //63 = gamma1e and 64 = gamma2e
						Hist[71+XIAchan/4]->Fill(ADCtime/1000000);	//71 = gtime1 and 72 = gtime2
						Hist[79]->Fill(ADCtime/1000000);			//79 = gtimeAll

						double time_gamma = (ADCtime - (double)GFLTtime[0]/40)/1000000;
						GammaEngTime->Fill(EngA,((ADCtime - (double)GFLTtime[0]/40)/1000000),XIAchan/4); //ntupla single gamma's
					}

					//Si Energy
					for(i=1; i<NUMBER_OF_CHANNELS+1; i++)
					{
						short dum;
						dum = (4*i) + 4;	 
						if(XIAchan == dum)
						{		 
							single_data->InitData();
							single_data->sEng[i]  = EngA;
							single_data->st[i]    = ADCtime; //check it was /1000000, changed on 01/12 
							single_data->tgflt[0] = (double)GFLTtime[0]/40.; // ACQ
							single_data->tgflt[1] = (double)GFLTtime[1]/40.; // PP
							single_data->tgflt[2] = (double)GFLTtime[2]/40.; // SC
							single_data->tgflt[3] = (double)GFLTtime[3]/40.; // beam Gate
							/*if ((COINC_TREE_SS ==0) && (COINC_TREE_GG==0))*/ SingleTree->Fill();

							Hist[37]->Fill(EngA);         	//Fill Si (full range, alpha calibration) --> all silicon detectors together! siA_raw

							Hist[80+i]->Fill(ADCtime/1000000); 	// 06 May 2011: Filling the Histo with Si absolute Time (in seconds) ! stime[i]
							Hist[30+i]->Fill(EngA);				//Fill Si (full range, alpha calibration) s[i]e
							Hist[40+i]->Fill(EngA);					//Fill Alpha (0-8MeV)	alpha[i]e
							Hist[50+i]->Fill(EngF);						//Si Energy (fission calibration) f[i]e	
						}
					} //loop NUMBER_OF_CHANNELS+1

					/**********************************************************************************************************************/// JGC 13/01/2016
					// Add pulser branch to singles tree
					if (XIAchan == 24)
					{
						single_data -> InitData();
						single_data -> pulserEvent = 1.;
						single_data -> pulserTime  = ADCtime;
						single_data -> tgflt[0]    = (double)GFLTtime[0]/40.; // ACQ
						single_data -> tgflt[1]    = (double)GFLTtime[1]/40.; // PP
						single_data -> tgflt[2]    = (double)GFLTtime[2]/40.; // SC
						single_data -> tgflt[3]    = (double)GFLTtime[3]/40.; // beam gate
						SingleTree  -> Fill();
					}
					
					/**********************************************************************************************************************/// JGC 13/01/2016

					//sum of Si1 and Si21
					if(XIAchan == 8 || XIAchan == 12)		
					{	
						Hist[35]->Fill(EngA);	//alpha calibration , range (0-8MeV)	sums12e
						Hist[55]->Fill(EngF);		//fission calibration		sumf12e
					}

					//sum of Si3 and Si4
					if(XIAchan==16 || XIAchan==20)
					{
						Hist[36]->Fill(EngA);	//alpha calibration, range (0-8MeV)	sums34e
						Hist[56]->Fill(EngF);		//fission calibration 		sumf12e
					}	

				}  // close if((ADCeng > 0)
			}	// close loop for
		}

		if(XIAnofsubevts > 0) DGFevts[XIAmod]->Fill(XIAnofsubevts);
   
   
	}


/**********************************************************************************************************************/// JGC 13/01/2016
															//
	// Make pulser tree												//
	for(N_PUL=0; N_PUL<evp->dgf[PULSER_MODULE].numofevents; N_PUL++)						//
	{													//
		ADCtime = (double)evp->dgf[PULSER_MODULE].lFTtime[N_PUL][PULSER_CHANNEL]/40.;			//
															//
		pulser_data -> pulserEvent = 1.;								//
		pulser_data -> pulserTime  = ADCtime;								//
		pulser_data -> tgflt[0]    = (double)GFLTtime[0]/40.; // ACQ					//
		pulser_data -> tgflt[1]    = (double)GFLTtime[1]/40.; // PP					//
		pulser_data -> tgflt[2]    = (double)GFLTtime[2]/40.; // SC					//
		pulser_data -> tgflt[3]    = (double)GFLTtime[3]/40.; // beam Gate				//
															//
		PulserTree  -> Fill();										//
	}													//
															//
/**********************************************************************************************************************/// JGC 13/01/2016

//==========================================================================
//start of hfs part -- no coincidences required only singles alpha and gamma
//==========================================================================

	if(USE_HYPER)
	{
		//Read in germanium 1
		int ge1chan=0;
		for(short N_GE=0; N_GE<evp->dgf[0].numofevents; N_GE++)
		{
			ADCeng = evp->dgf[0].energy[N_GE][0]; //GE_MODULES = 0,1 CHANNELS= 0,0
			 
			if(ADCeng >100 && ADCeng<60000)
			{
				EEngA	= xia_gain_2A[ge1chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[ge1chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[ge1chan];
			 
				if((EEngA > GE_ENERGY_THRESH_LO) && (EEngA <= GE_ENERGY_THRESH_HI))
				{
					hfs_data->InitData();
					hfs_data->gid	= 1;
					hfs_data->GsCycle	= sCycleNumber;
					hfs_data->GEng[1]	= EEngA;
					hfs_data->gt[1]   =(double)evp->dgf[0].lFTtime[N_GE][0]/40.;
					hfs_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
					hfs_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
					hfs_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
					hfs_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate

					if(EXTRA_FREQ == 1)       hfs_data->Glf=freq[sCycleNumber+1];
					else hfs_data->Glf=freq[sCycleNumber];
					hfs_data->Glf=freq[sCycleNumber];
					HFSTree->Fill();
				}
			}
		}


		//Read in germanium 2
		int ge2chan=4;
		for(short N_GE=0; N_GE<evp->dgf[1].numofevents; N_GE++)
		{
			ADCeng	= evp->dgf[1].energy[N_GE][0]; //GE_MODULES = 0,1 CHANNELS= 0,0

			if(ADCeng >100 && ADCeng<60000)
			{
				EEngA	= xia_gain_2A[ge2chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[ge2chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[ge2chan];

				if((EEngA > GE_ENERGY_THRESH_LO) && (EEngA <= GE_ENERGY_THRESH_HI))
				{
					hfs_data->InitData();
					hfs_data->gid	= 2;
					hfs_data->GsCycle	= sCycleNumber;
					hfs_data->GEng[2]	= EEngA;
					hfs_data->gt[2]   =(double)evp->dgf[1].lFTtime[N_GE][0]/40.;
					hfs_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
					hfs_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
					hfs_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
					hfs_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate
					if(EXTRA_FREQ == 1)       hfs_data->Glf=freq[sCycleNumber+1]; 
					else hfs_data->Glf=freq[sCycleNumber];
					hfs_data->Glf=freq[sCycleNumber];
					HFSTree->Fill();
				}   
			}
		}


		//Read in silicon 1
		int Si1chan=8;
		for(short N_SI=0;N_SI<evp->dgf[2].numofevents;N_SI++)
		{
			ADCeng    = evp->dgf[2].energy[N_SI][0];

			if (ADCeng>1000 && ADCeng<60000)
			{
				EngA=xia_offsetA[Si1chan]+xia_gain_1A[Si1chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_2A[Si1chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX);	

				if((EngA>SI_ENERGY_THRESH_LO) && (EngA<=SI_ENERGY_THRESH_HI))
				{
					hfs_data->InitData();
					hfs_data->sid=1;
					hfs_data->SsCycle = sCycleNumber;
					hfs_data->SEng[1] = EngA;
					hfs_data->st[1]   =(double)evp->dgf[2].lFTtime[N_SI][0]/40.;
					hfs_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
					hfs_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
					hfs_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
					hfs_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate
					if(EXTRA_FREQ == 1)      hfs_data->Slf=freq[sCycleNumber+1]; 
					else hfs_data->Slf=freq[sCycleNumber];
					hfs_data->Slf=freq[sCycleNumber];
					HFSTree->Fill();
				}   
			}
		} 


		//Read in silicon 2
		int Si2chan=12;
		for(short N_SI=0;N_SI<evp->dgf[3].numofevents;N_SI++)
		{
			ADCeng    = evp->dgf[3].energy[N_SI][0];

			if (ADCeng>1000 && ADCeng<60000)
			{
				EngA=xia_offsetA[Si2chan]+xia_gain_1A[Si2chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_2A[Si2chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX);	

				if((EngA>SI_ENERGY_THRESH_LO) && (EngA<=SI_ENERGY_THRESH_HI))
				{
					hfs_data->InitData();
					hfs_data->sid=2;
					hfs_data->SsCycle = sCycleNumber;
					hfs_data->SEng[2] = EngA;
					hfs_data->st[2]   =(double)evp->dgf[3].lFTtime[N_SI][0]/40.;
					hfs_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
					hfs_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
					hfs_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
					hfs_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate
					if(EXTRA_FREQ == 1)      hfs_data->Slf=freq[sCycleNumber+1]; 
					else hfs_data->Slf=freq[sCycleNumber];
					hfs_data->Slf=freq[sCycleNumber];
					HFSTree->Fill();
				}
			}
		} 


		//Read in silicon 3
		int Si3chan=16;
		for(short N_SI=0;N_SI<evp->dgf[4].numofevents;N_SI++)
		{
			ADCeng    = evp->dgf[4].energy[N_SI][0];

			if (ADCeng>1000 && ADCeng<60000)
			{
				EngA=xia_offsetA[Si3chan]+xia_gain_1A[Si3chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_2A[Si3chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX);	

				if((EngA>SI_ENERGY_THRESH_LO) && (EngA<=SI_ENERGY_THRESH_HI))
				{
					hfs_data->InitData();
					hfs_data->sid=3;
					hfs_data->SsCycle = sCycleNumber;
					hfs_data->SEng[3] = EngA;
					hfs_data->st[3]   =(double)evp->dgf[4].lFTtime[N_SI][0]/40.;
					hfs_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
					hfs_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
					hfs_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
					hfs_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate
					if(EXTRA_FREQ == 1)      hfs_data->Slf=freq[sCycleNumber+1]; 
					else hfs_data->Slf=freq[sCycleNumber];
					hfs_data->Slf=freq[sCycleNumber];
					HFSTree->Fill();
				}   
			}
		}


		//Read in silicon 4
		int Si4chan=20;
		for(short N_SI=0;N_SI<evp->dgf[5].numofevents;N_SI++)
		{
			ADCeng    = evp->dgf[5].energy[N_SI][0];

			if (ADCeng>1000 && ADCeng<60000)
			{
				EngA=xia_offsetA[Si4chan]+xia_gain_1A[Si4chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_2A[Si4chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX);	

				if((EngA>SI_ENERGY_THRESH_LO) && (EngA<=SI_ENERGY_THRESH_HI))
				{
					hfs_data->InitData();
					hfs_data->sid=4;
					hfs_data->SsCycle = sCycleNumber;
					hfs_data->SEng[4] = EngA;
					hfs_data->st[4]   =(double)evp->dgf[5].lFTtime[N_SI][0]/40.;
					hfs_data->tgflt[0]= (double)GFLTtime[0]/40.; // ACQ
					hfs_data->tgflt[1]= (double)GFLTtime[1]/40.; // PP
					hfs_data->tgflt[2]= (double)GFLTtime[2]/40.; // SC
					hfs_data->tgflt[3]= (double)GFLTtime[3]/40.; // beam Gate
					if(EXTRA_FREQ == 1)      hfs_data->Slf=freq[sCycleNumber+1]; 
					else hfs_data->Slf=freq[sCycleNumber];
					hfs_data->Slf=freq[sCycleNumber];
					HFSTree->Fill();
				}
			}
		}


		for(N_PUL=0; N_PUL<evp->dgf[PULSER_MODULE].numofevents; N_PUL++)
		{
			ADCtime = (double)evp->dgf[PULSER_MODULE].lFTtime[N_PUL][PULSER_CHANNEL]/40.;			//

			hfs_data -> InitData();
			hfs_data->SsCycle = sCycleNumber;
			hfs_data -> pulserEvent = 1;
			hfs_data -> pulserTime  = ADCtime;
			hfs_data -> tgflt[0]    = (double)GFLTtime[0]/40.; // ACQ
			hfs_data -> tgflt[1]    = (double)GFLTtime[1]/40.; // PP
			hfs_data -> tgflt[2]    = (double)GFLTtime[2]/40.; // SC
			hfs_data -> tgflt[3]    = (double)GFLTtime[3]/40.; // beam Gate
			if(EXTRA_FREQ == 1)      hfs_data->Slf=freq[sCycleNumber+1]; 
			else hfs_data->Slf=freq[sCycleNumber];
			hfs_data->Slf=freq[sCycleNumber];
			HFSTree->Fill();
		}
}

///===============
// End of HFS Tree  
///===============


/***********************************************************************************************/


//=============================================================
// Start of the Gamma-Gamma coincidences (NO Si is required!!!)
//=============================================================
if(COINC_TREE_GG)
{
// ---------      Reset Matrix G_CoincPattern	   -------------
	for(i_R=0; i_R<NUMBER_OF_GE; i_R++)
		for(N_R=0; N_R<MAXEVENTNUM; N_R++) { G_CoincPattern[i_R][N_R]= false; }
//---------------------------------------------------------------

	for(i_R=0; i_R<NUMBER_OF_GE-1; i_R++)
	{
		for(N_R=0; N_R<evp->dgf[GE_MODULES[i_R]].numofevents; N_R++)
		{
			ADCeng = evp->dgf[GE_MODULES[i_R]].energy[N_R][GE_CHANNELS[i_R]];
			EEngA  = xia_gain_2A[NUMBER_OF_CHANNELS*GE_MODULES[i_R]+GE_CHANNELS[i_R]]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[NUMBER_OF_CHANNELS*GE_MODULES[i_R]+GE_CHANNELS[i_R]]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[NUMBER_OF_CHANNELS*GE_MODULES[i_R]+GE_CHANNELS[i_R]];

			if(!G_CoincPattern[i_R][N_R] && (EEngA > GE_ENERGY_THRESH_LO) && (EEngA <= GE_ENERGY_THRESH_HI) && (evp->dgf[GE_MODULES[i_R]].lFTtime[N_R][GE_CHANNELS[i_R]] > 0))
			{
				ge_data->InitData();

				// Check that the energies of the 1st range (index I_R) are within the imposed thresholds (above)
				//            the energies of the 2nd range (index I_R) are within the imposed thresholds (below)
				// and that the time difference cTD between the 1st and 2nd range is less than bestTD
				// Loop over all events
				// The control on G_CoincPattern is used to skip events that have been checked and loaded into the tree
     
				for(i_C=i_R+1; i_C<NUMBER_OF_GE; i_C++)
				{
					BestEvt= -1;
					BestTD= 26000;

					for(N_C=0; N_C<evp->dgf[GE_MODULES[i_C]].numofevents; N_C++)
					{
						ADCeng = evp->dgf[GE_MODULES[i_C]].energy[N_C][GE_CHANNELS[i_C]];
						EEngA  = xia_gain_2A[NUMBER_OF_CHANNELS*GE_MODULES[i_C]+GE_CHANNELS[i_C]]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[NUMBER_OF_CHANNELS*GE_MODULES[i_C]+GE_CHANNELS[i_C]]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[NUMBER_OF_CHANNELS*GE_MODULES[i_C]+GE_CHANNELS[i_C]];
						if(!G_CoincPattern[i_C][N_C] && (EEngA > GE_ENERGY_THRESH_LO) && (EEngA <= GE_ENERGY_THRESH_HI) && (evp->dgf[GE_MODULES[i_C]].lFTtime[N_C][GE_CHANNELS[i_C]] > 0))
						{
							cTD= 25*int(evp->dgf[GE_MODULES[i_C]].lFTtime[N_C][GE_CHANNELS[i_C]] - evp->dgf[GE_MODULES[i_R]].lFTtime[N_R][GE_CHANNELS[i_R]]);
							if((cTD >= TIME_GE_GE_L) && (cTD <= TIME_GE_GE_R) && (abs(cTD) < abs(BestTD)))
							{
								BestTD= cTD;
								BestEvt= N_C;
							}
						}
					}

					if(BestEvt > -1) // If the two ranges are between TIME_GE_GE_L and TIME_GE_GE_R (set in AnaDefs.hh)
					{
						G_CoincPattern[i_R][N_R]= true;
						G_CoincPattern[i_C][BestEvt]= true;
				       
						if(ge_data->gmult == 0) // The first time it also writes tgflt[0], tgflt[1]
						{			            // but does not write for subsequent times (gmult>0)
							/************************************************************************** 
							ge_data->gen[i_R+1]   energy first gamma
							ge_data->gen[i_C+1]    energy second gamma
							ge_data->gt[i_R+1]     absolute time first gamma
							ge_data->gt[i_C+1]     absolute time second gamma
							ge_data->tgflt[0]      reference time (ACQ gate start)
							ge_data->tgflt[1]      reference time (first proton pulse arrives)
							ge_data->adctime[i_R+1]  absolute time first gamma - reference time
							ge_data->adctime[i_C+1]  absolute time second gamma - reference time
							ge_data->gtd          time difference first gamma - second gamma
							**************************************************************************/   
							ge_data->gmult++;
							ADCeng			        = evp->dgf[GE_MODULES[i_R]].energy[N_R][GE_CHANNELS[i_R]]; // get channel number
							ge_data->gen[i_R+1]	    = xia_gain_2A[NUMBER_OF_CHANNELS*GE_MODULES[i_R]+GE_CHANNELS[i_R]]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[NUMBER_OF_CHANNELS*GE_MODULES[i_R]+GE_CHANNELS[i_R]]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[NUMBER_OF_CHANNELS*GE_MODULES[i_R]+GE_CHANNELS[i_R]];
							ge_data->gt[i_R+1]	    = (double)evp->dgf[GE_MODULES[i_R]].lFTtime[N_R][GE_CHANNELS[i_R]]/40.;
							ge_data->adctime[i_R+1]	= ((double)evp->dgf[GE_MODULES[i_R]].lFTtime[N_R][GE_CHANNELS[i_R]]/40.- (double)GFLTtime[0]/40.)/1000000;
							ge_data->gtd    	    = 25*(int)(evp->dgf[GE_MODULES[i_C]].lFTtime[BestEvt][GE_CHANNELS[i_C]] - evp->dgf[GE_MODULES[i_R]].lFTtime[N_R][GE_CHANNELS[i_R]]);
							ge_data->tgflt[0]	    = (double)GFLTtime[0]/40.;
							ge_data->tgflt[1]	    = (double)GFLTtime[1]/40.;
						}
				
						ge_data->gmult++;
						ADCeng			        = evp->dgf[GE_MODULES[i_C]].energy[BestEvt][GE_CHANNELS[i_C]];
						ge_data->gen[i_C+1]	    = xia_gain_2A[NUMBER_OF_CHANNELS*GE_MODULES[i_C]+GE_CHANNELS[i_C]]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[NUMBER_OF_CHANNELS*GE_MODULES[i_C]+GE_CHANNELS[i_C]]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[NUMBER_OF_CHANNELS*GE_MODULES[i_C]+GE_CHANNELS[i_C]];
						ge_data->gt[i_C+1]	    = (double)evp->dgf[GE_MODULES[i_C]].lFTtime[BestEvt][GE_CHANNELS[i_C]]/40.;
						ge_data->adctime[i_C+1]	= ((double)evp->dgf[GE_MODULES[i_C]].lFTtime[BestEvt][GE_CHANNELS[i_C]]/40.- (double)GFLTtime[0]/40)/1000000;
						ge_data->gtd            = 25*(int)(evp->dgf[GE_MODULES[i_C]].lFTtime[BestEvt][GE_CHANNELS[i_C]] - evp->dgf[GE_MODULES[i_R]].lFTtime[N_R][GE_CHANNELS[i_R]]);	
						ge_data->Glf            = freq[sCycleNumber]; //printf("%f\n",freq[sCycleNumber]);
					}	// close if BestEvt

				}	//close loop i_C

			    if ((ge_data -> gmult) > 0)
				{		// Elisa: to avoid to write 10^9 zero in the root files!!!!!!
			     		GeTree->Fill();
				}   
			}
		}
	}
}		// close if COINC_TREE_GG

///===============================
// End of Gamma-Gamma coincidences  
///===============================


/***********************************************************************************************/

///========================================
// Start of Si-Si and Si-Gamma coincidences
///========================================

if(COINC_TREE_SS)
{
	// ---- Reset Matrix B_CoincPattern	   -------------
	for(i_SI=0; i_SI<NUMBER_OF_SI; i_SI++)
		for(N_SI=0; N_SI<MAXEVENTNUM; N_SI++)  { B_CoincPattern[i_SI][N_SI]= false;	}
// ---------------------------------------------------- 
 
	for(i_SI=0; i_SI<NUMBER_OF_SI; i_SI++)   ///loop su un Si
	{
		for(N_SI=0; N_SI<evp->dgf[SI_MODULES[i_SI]].numofevents; N_SI++)
		{
			chan=NUMBER_OF_CHANNELS*SI_MODULES[i_SI]+SI_CHANNELS[i_SI];
			ADCeng	= evp->dgf[SI_MODULES[i_SI]].energy[N_SI][SI_CHANNELS[i_SI]];
			EEngA	= xia_gain_2A[chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[chan];
			EEngF	=  FissionCalA[chan]*(ADCeng + rand()/(float)RAND_MAX) + FissionCalB[chan];
			
			if(!B_CoincPattern[i_SI][N_SI] && (EEngA > SI_ENERGY_THRESH_LO) && (EEngA <= SI_ENERGY_THRESH_HI))
			{
				if(ADCeng >LOWER_E && ADCeng<UPPER_E) //threshold to cut off noise (<1000) and alphas (<5000)+ cut off the overflow (>64000)
				{
					/* Single Si */
					si_data->InitData();
					si_data->senA[i_SI+1]	= EEngA;	// alpha calibrated
					si_data->senF[i_SI+1]	= EEngF; 	//fission calibrated
					si_data->st[i_SI+1]	= (double)evp->dgf[SI_MODULES[i_SI]].lFTtime[N_SI][SI_CHANNELS[i_SI]]/40.;
					si_data->tgflt[0]		= (double)GFLTtime[0]/40.; //absolute time when a new ACQ gate starts
					si_data->tgflt[1]		= (double)GFLTtime[1]/40.; //absolute time when proton pulse arrives 
					si_data->Slf = freq[sCycleNumber];
	     
					//fill histogram corresponding histo's
					senFSi->Fill(EEngF);
					senASi->Fill(EEngA);
					stSi->Fill(si_data->st[i_SI+1]);

					// Start of the Si-Si part
					// We need Si-Si coincidences only WITHIN pairs Si1-Si2 and Si3-Si4!
  
					for(i_C=i_SI+1; i_C<NUMBER_OF_SI; i_C++)
					{
						if ((i_SI==0 && i_C==1) or (i_SI==2 && i_C==3))      
						{
							BestEvt= -1;
							BestTD= TIME_SI_SI_R+100;
							for(N_C=0; N_C<evp->dgf[SI_MODULES[i_C]].numofevents; N_C++)
							{
								ADCeng	= evp->dgf[SI_MODULES[i_SI]].energy[N_SI][SI_CHANNELS[i_SI]];
								EEngA	= xia_gain_2A[chan]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[chan]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[chan];
								EEngF	= FissionCalA[chan]*(ADCeng + rand()/(float)RAND_MAX) + FissionCalB[chan];
							
								if(!B_CoincPattern[i_C][N_C] && (EEngA > SI_ENERGY_THRESH_LO) && (EEngA <= SI_ENERGY_THRESH_HI))
								{
									cTD= 25*(int)(evp->dgf[SI_MODULES[i_C]].lFTtime[N_C][SI_CHANNELS[i_C]] - evp->dgf[SI_MODULES[i_SI]].lFTtime[N_SI][SI_CHANNELS[i_SI]]);
									if((cTD >= TIME_SI_SI_L) && (cTD <= TIME_SI_SI_R) && (abs(cTD) < abs(BestTD)))	//[-300,300]
									{
										BestTD= cTD;
										BestEvt= N_C;
									}
								}
							}

							if(BestEvt > -1)  // si Si-Si coincidences --> then Fill  SiSiData (SiSiT)
							{
								B_CoincPattern[i_SI][N_SI]= true;	
								B_CoincPattern[i_C][BestEvt]= true;
								si_data->smult++; 
								//fill histogram
								smultSi->Fill(si_data->smult);
								chan2=NUMBER_OF_CHANNELS*SI_MODULES[i_C]+SI_CHANNELS[i_C];
						
								ADCeng2	= evp->dgf[SI_MODULES[i_C]].energy[BestEvt][SI_CHANNELS[i_C]];
						
								si_data->senA[i_C+1]	= xia_gain_2A[chan2]*(ADCeng2 + rand()/(float)RAND_MAX)*(ADCeng2 + rand()/(float)RAND_MAX) + xia_gain_1A[chan2]*(ADCeng2 + rand()/(float)RAND_MAX) + xia_offsetA[chan2];
								si_data->senF[i_C+1]	= FissionCalA[chan2]*(ADCeng2 + rand()/(float)RAND_MAX) + FissionCalB[chan2];
								si_data->st[i_C+1]	= (double)evp->dgf[SI_MODULES[i_C]].lFTtime[BestEvt][SI_CHANNELS[i_C]]/40.;
							 
								//fill histogram 
								senFSi->Fill(si_data->senF[i_C+1]); //fission calibrated
								senASi->Fill(si_data->senA[i_C+1]); //alpha calibrated
								stSi->Fill(si_data->st[i_C+1]);
							
								temp= 25*(int)(evp->dgf[SI_MODULES[i_C]].lFTtime[BestEvt][SI_CHANNELS[i_C]] - evp->dgf[SI_MODULES[i_SI]].lFTtime[N_SI][SI_CHANNELS[i_SI]]);

								if (i_SI==0) 
								{
										si_data->std[1]=temp;
									//fill histogram
									stdSi->Fill(si_data->std[1]);
									Hist[101]->Fill(temp);
								}

								if (i_SI==2) 
								{
									si_data->std[2]=temp;
									// fill histogram
									stdSi->Fill(si_data->std[2]);
									Hist[102]->Fill(temp);
								}
			
								//fill 2D histogram to see silicon-silicon coincidences
								ssA->Fill(si_data->senA[i_SI+1],si_data->senA[i_C+1]);
								ssF->Fill(si_data->senF[i_SI+1],si_data->senF[i_C+1]);
							}  // close Best Event
						} // close if ((i_SI==0 && i_C==1) or (i_SI==2 && i_C==3))      
					} // close loop over Si --> for(i_C=i_SI+1; i_C<NUMBER_OF_SI; i_C++)
	     			// End of the Si-Si part      

					// Start of the Si-Gamma part
					for(i_GE=0; i_GE<NUMBER_OF_GE; i_GE++)
					{
						BestEvt= -1;
						BestTD= TIME_SI_GE_R+1000;
			
						for(N_GE=0; N_GE<evp->dgf[GE_MODULES[i_GE]].numofevents; N_GE++)
						{
							ADCeng	= evp->dgf[GE_MODULES[i_GE]].energy[N_GE][GE_CHANNELS[i_GE]];	// ADC channel
							EEngA	= xia_gain_2A[NUMBER_OF_CHANNELS*GE_MODULES[i_GE]+GE_CHANNELS[i_GE]]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[NUMBER_OF_CHANNELS*GE_MODULES[i_GE]+GE_CHANNELS[i_GE]]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[NUMBER_OF_CHANNELS*GE_MODULES[i_GE]+GE_CHANNELS[i_GE]];
			
							if((EEngA > GE_ENERGY_THRESH_LO) && (EEngA <= GE_ENERGY_THRESH_HI) && (evp->dgf[GE_MODULES[i_GE]].lFTtime[N_GE][GE_CHANNELS[i_GE]] > 0))
							{
								cTD= 25*(int)(evp->dgf[GE_MODULES[i_GE]].lFTtime[N_GE][GE_CHANNELS[i_GE]] - evp->dgf[SI_MODULES[i_SI]].lFTtime[N_SI][SI_CHANNELS[i_SI]]);
			
								if((cTD >= TIME_SI_GE_L) && (cTD <= TIME_SI_GE_R) && (abs(cTD) < abs(BestTD)))  //[-2000,2000]
								{
									BestTD  = cTD;
									BestEvt = N_GE;
								}
							}
						}
			
						if(BestEvt > -1) // si Ge-Si coincidences --> then Fill  SiGammaT
						{
					      	ADCeng               = evp->dgf[GE_MODULES[i_GE]].energy[BestEvt][GE_CHANNELS[i_GE]];	// get channel number
							si_data->gen[i_GE+1] = xia_gain_2A[NUMBER_OF_CHANNELS*GE_MODULES[i_GE]+GE_CHANNELS[i_GE]]*(ADCeng + rand()/(float)RAND_MAX)*(ADCeng + rand()/(float)RAND_MAX) + xia_gain_1A[NUMBER_OF_CHANNELS*GE_MODULES[i_GE]+GE_CHANNELS[i_GE]]*(ADCeng + rand()/(float)RAND_MAX) + xia_offsetA[NUMBER_OF_CHANNELS*GE_MODULES[i_GE]+GE_CHANNELS[i_GE]];
							si_data->gt[i_GE+1]  = (double)evp->dgf[GE_MODULES[i_GE]].lFTtime[BestEvt][GE_CHANNELS[i_GE]]/40.;
							si_data->gtd[i_GE+1] = 25*(int)(evp->dgf[GE_MODULES[i_GE]].lFTtime[BestEvt][GE_CHANNELS[i_GE]] - evp->dgf[SI_MODULES[i_SI]].lFTtime[N_SI][SI_CHANNELS[i_SI]]);
			       
							//fill histogram
							genSi->Fill(si_data->gen[i_GE+1]);
							gtSi->Fill(si_data->gt[i_GE+1]);
							gtdSi->Fill(si_data->gtd[i_GE+1]);
							Hist[(10+i_GE+1)*10+i_SI+1]->Fill(si_data->gtd[i_GE+1]);
			        
							si_data->gmult++;
							gmultSi->Fill(si_data->gmult);
			
							//fill 2D histogram to see silicon-gamma coincidences
							sigeF->Fill(si_data->senF[i_SI+1],si_data->gen[i_GE+1]);
							sigeA->Fill(si_data->senA[i_SI+1],si_data->gen[i_GE+1]);
				
							//tree with silicon gamma coicincidenc energies and time difference
							si_gamma->GammaEng=si_data->gen[i_GE+1];
							si_gamma->SiEng=si_data->senA[i_SI+1];
							si_gamma->TimeDiffSiGamma=si_data->gtd[i_GE+1];
		     
							SiGammaT->Fill();
					    }			// close if Best Event
					} // close loop over Ge  --> (for(i_GE=0; i_GE<NUMBER_OF_GE; i_GE++)

					SiTree->Fill();
     
				} // close if energy cut
			} // BCoinPattern 
		} // loop events
	} // loop over Si
} // if COINC_TREE_SS)
// END OF if(COINC_TREE_SS)

readouts++;
}


///===============================
// End of Si-Si Si-Ge coincidences  
///===============================

/***********************************************************************************************/

void Ana::End()
{
	if(rootFile != NULL)
	{
		rootFile->Write();
		rootFile->Close();
		delete rootFile;
		rootFile = NULL;
		cout << "\t" << readouts << " DAQ readouts processed\n\n\a";
	}
}

void Ana::ReadCoefficients(const char* file, double* offset, double* gain_1, double* gain_2, int number)
{
	FILE* fp;
	int i=0;
	char line[512];
	bool clearflag=1;
	cout << "  Calibration file: " << file << "\n";
	
	cout << "\n  ---------------------------------------------\n\n";

	if(file!="NONE")
	{
		fp=fopen(file,"r");
		if(fp!=NULL)
		{
			while(fgets(line,512,fp) != NULL)
			{
				if(line[0]!='#') { sscanf(line,"%lf %lf %lf",&offset[i],&gain_1[i],&gain_2[i]); i++; }
			}
			if(i!=number)	cout << "\033[91mRead values for " << i << " instead of " << number << " channels! Default values are used!\n\033[0m";
			 else clearflag= 0;
		}
		else		cout << "\033[91mCouldn't open file " << file << " ! UNCALIBRATED Default values are used!\n\033[0m";
	}

	if(clearflag)
	{
		for(i=0; i<number; i++)
		{
			offset[i]= 0;
			gain_1[i]= 1;
			gain_2[i]= 0;
		}
	}
}
