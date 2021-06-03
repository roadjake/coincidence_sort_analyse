#ifndef Ana_h
#define Ana_h 0

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TNtuple.h"

#include "AnaDefs.hh"
#include "AnaRoot.hh"

class Ana
{
public:
   Ana();
  ~Ana();

public:
   int Init();
  void Build(ANA_BUFFER *evp);
  void End();
  void ReadCoefficients(const char*, double*, double*, double*, int);
  std::string DATA_CALIB_FILE;

public:
  TFile* rootFile;
  TTree* GeTree;
  TTree* SiTree;
  TTree* SiSiT;
  TTree* SiGammaT;
  TTree* HFSTree ;
  TTree* CorrectedFisEnT;
  TTree* SingleTree;

	TTree* PulserTree;		// JGC pulser
  
  TNtuple* GammaEngTime;

  GeData* ge_data;
  SiData* si_data;
  HFSData* hfs_data;
  SingleData * single_data;

	PulserData* pulser_data;	// JGC pulser
  
  SiSiData* sisi_data;
  FisEn* fis_en;
  
  SiGammaData* si_gamma;\

  int readouts;
  int sCycleNumber;
  int counts;
  int store;
  double checkTime;
  int COINC_TREE_SS;
  int COINC_TREE_GG;
  int COINC_TREE_SG;
  int COINC_TREE_SSorSG;
  int LOWER_E;
  int UPPER_E;
  int USE_FIS_CAL;
  int USE_SINGLES_CAL;
  int USE_HYPER;
  int EXTRA_FREQ;
  double freq[200];
  double timeabs[200];
  double FissionCalA[4];
  double FissionCalB[4];
  double CalSinglesDet1Light[21];
  double CalSinglesDet1Heavy[21];
  double CalSinglesDet2Light[21];
  double CalSinglesDet2Heavy[21];	
  long long GFLTtime[NUMBER_OF_GFLT];
  double xia_offsetA[NUMBER_OF_CHANNELS*NUMBER_OF_DGFS];
  double xia_gain_1A[NUMBER_OF_CHANNELS*NUMBER_OF_DGFS];
  double xia_gain_2A[NUMBER_OF_CHANNELS*NUMBER_OF_DGFS];
  bool  B_CoincPattern[NUMBER_OF_SI][MAXEVENTNUM];
  bool  G_CoincPattern[NUMBER_OF_GE][MAXEVENTNUM];

	double pulserEvent;	// JGC pulser
	double pulserTime;	// JGC pulser

  TH2D* gg_mat;

  TH1F* GFLT[NUMBER_OF_GFLT];
  TH1F* DGFevts[NUMBER_OF_DGFS];
  //TH1F* Hist[NUMBER_OF_CHANNELS*NUMBER_OF_DGFS];
  TH1F* Hist[200];
  TH2F* ssA;
  TH2F* ssF;
  TH2F* ag;
  TH2F* fg;
  TH2F* sigeA;
  TH2F* sigeF;
  TH1F* UncXIA[NUMBER_OF_CHANNELS*NUMBER_OF_DGFS];
  TH1F* CalXIA[NUMBER_OF_CHANNELS*NUMBER_OF_DGFS];
  TH1F* smultSi;
  TH1F* gmultSi;
  TH1F* gtdSi;
  TH1F* stdSi;  
  TH1F* senASi;
  TH1F* senFSi; 
  TH1F* genSi; 
  TH1F* gtSi;
  TH1F* stSi; 
  TH1F* tgfltSi;
  TH1F* SiEnSchmitt;
  TH1F* SiMassSchmitt;
  TH2F* SiEnSchmitt2D;
  TH2F* SiMassSchmitt2D;
  //TH1F* ssA1D;
  TH1F* SiEnACorrected;
  TH1F* SiMassACorrected;
  //TH2F* SiEnACorrected2D;
  //TH2F* SiMassACorrected2D;
  TH1F* SiGamma;
  TH1F* SiGammaTime;
  TH1F* SiGammaMult;
  TH1F* SiGammaTimeXrays;
  TH1F* AlphaGammaTime;
  TH1F* LightFragment;
  TH1F* HeavyFragment;
  TH1F* SimpleEnergy1;
  TH1F* SimpleEnergy2;
  TH1F* Energy1AvMass;
  TH1F* Energy2AvMass;
  TH1F* En1Singles;
  TH1F* En2Singles;
  TH1F* En1CoincAvEn;
  TH1F* En2CoincAvEn;
  FILE *MatrixOutput;
  FILE *TimeOutput;
  FILE *GGGCubeOutput;
  FILE *fissionGammaFile;
  //TH1F* DiagonalProjection;
  
  
  
  TNtuple *gggCube;
 
};
#endif
