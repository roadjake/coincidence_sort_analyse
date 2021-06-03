// ALL INITIAL PARAMETERS
#ifndef AnaDefs_h
#define AnaDefs_h 0

#define NUMBER_OF_DGFS		9	/* counts from 1 */
#define NUMBER_OF_GE		2	/* counts from 1 */
#define NUMBER_OF_SI		4	/* counts from 1 */
#define NUMBER_OF_GFLT		4	/* counts from 1 */

#define NUMBER_OF_CHANNELS	4	/* counts from 1 */
#define MAXEVENTNUM		1637	/* counts from 1 */

#define SI_ENERGY_THRESH_LO	0	/* keV */
#define SI_ENERGY_THRESH_HI	200000	/* keV */
#define GE_ENERGY_THRESH_LO	10	/* keV */
#define GE_ENERGY_THRESH_HI	5000	/* keV */

// Time between Si and Si
#define TIME_SI_SI_L		-/*10000000*/300	/* ns */
#define TIME_SI_SI_R		/*10000000*/300	/* ns */

// Time between Ge and Ge
#define TIME_GE_GE_L		-/*10000000*/1200	/* ns */
#define TIME_GE_GE_R		/*10000000*/1200	/* ns */

// Time between Si and Ge
#define TIME_SI_GE_L		-10000000/*2000	 ns -2000*/
#define TIME_SI_GE_R		10000000/*2000	 ns */

#define STAND_LM_BUFFORMAT	4352	/* standard list mode	*/
#define COMP1_LM_BUFFORMAT	4353	/* compressed list mode 1 */
#define COMP2_LM_BUFFORMAT	4354	/* compressed list mode 2 */
#define COMP3_LM_BUFFORMAT	4355	/* compressed list mode 3 */

#define GFLT_LASER		0	//channel of gflt for laser = DAQ gate

//******* JGC pulser
#define PULSER_FREQ		99.999	/* Hz */
//#define XIA_DEBUG


	 const short GE_MODULES[NUMBER_OF_GE]		= {  0, 1 };	/* counts from 0 */
	 const short GE_CHANNELS[NUMBER_OF_GE]		= {  0, 0 };	/* counts from 0 */
	 const short SI_MODULES[NUMBER_OF_SI]		= {  2, 3, 4, 5 };	/* counts from 0 */
	 const short SI_CHANNELS[NUMBER_OF_SI]		= {  0, 0, 0, 0 };	/* counts from 0 */
	//******* JGC pulser
	 const short PULSER_MODULE			= 6; // Assume one pulser in card 6
	 const short PULSER_CHANNEL			= 0; // and channel 0.
	 const short GFLT_MODULES[NUMBER_OF_GFLT]	= {  7,  7, 7, 7 };		/* counts from 0 */
	 const short GFLT_CHANNELS[NUMBER_OF_GFLT]	= {  0,  1, 2, 3 };		/* counts from 0 */
		
typedef struct
{
  double dspevents;
  double realtime;
  double runtime;
  double gslt;
  double livetime[NUMBER_OF_CHANNELS];
  double fastpeaks[NUMBER_OF_CHANNELS];
  double gsltpeaks[NUMBER_OF_CHANNELS];
  double slowpeaks[NUMBER_OF_CHANNELS];
} xiarates;

typedef struct
{
  unsigned short numofevents;
  unsigned short eventtime[MAXEVENTNUM][3];	/* 0 - low, 1 - middle, 2 - high */
  unsigned short energy[MAXEVENTNUM][NUMBER_OF_CHANNELS];
  unsigned short FTtime[MAXEVENTNUM][NUMBER_OF_CHANNELS];
  unsigned short CFtime[MAXEVENTNUM][NUMBER_OF_CHANNELS];
  unsigned short buftime[3];
  unsigned short hitpattern[MAXEVENTNUM];
  long long leventtime[MAXEVENTNUM];
  long long lFTtime[MAXEVENTNUM][NUMBER_OF_CHANNELS];
//  xiarates rates;
} DGF4C;

typedef struct
{
  DGF4C dgf[NUMBER_OF_DGFS];
  int dgfhasrateinfo;
} ANA_BUFFER;

#endif
