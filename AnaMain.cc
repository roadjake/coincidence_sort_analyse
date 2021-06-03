/* The offline analysis program for beta-decay experiments in LLN
	- author:	 Oleg Ivanov, updated for root6 by James Cubiss (10/06/2019)
	- input:     data from IGOR (.bin files)
	- output:    ROOT file with various histograms and single, beta-gamma, and gamma-gamma coincidence events
	- compiling: make compile OR make compileall
	- running:	 ./anaSort <PARAMETERS>
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <time.h> //ER added on 08/09

#include "Ana.hh"

int decodeDgfData(int sevtId, int sevtWc, unsigned short * sevtData, ANA_BUFFER* evp, int nofProcessedEvents);

Ana ana;

using namespace std;

time_t Start, End;  //ER added on 08/09
double dif;
double dif1;
double dif2;

void ctrlc_hand(int s)
{
	cout << "*** User Abort ***\n";
	ana.End();
	exit(0);
}

main(int argc, char **argv)
{
 
	time (&Start); //ER added on 08/09
	int ret;
	int nofProcessedEvents= 0;
	char datafile[200];
	ANA_BUFFER *evp;
	unsigned short lSize,lmod=0,lmod_pr,mod;
	long lPos;
	unsigned short* lbuffer;
	unsigned short* lheader;
	unsigned short* q;

	signal(SIGINT,ctrlc_hand);

	if((evp = (ANA_BUFFER*)malloc(sizeof(ANA_BUFFER))) == NULL) { cout << "  Error during malloc!\n"; exit(1); }
	memset(evp,0,sizeof(ANA_BUFFER));

	ret = ana.Init();
	if(ret<0) { cout << "Initialization Error!\n"; exit(1); }

	FILE* rfp;
	char rline[512];
	char bin_file[128];
	char cal_file_alpha[128];

	if(ana.DATA_CALIB_FILE!="NONE")
	{
		rfp=fopen(ana.DATA_CALIB_FILE.c_str(),"r");
		if(rfp!=NULL)
		{
			while(fgets(rline,512,rfp) != NULL)
			{
				if(rline[0]!='#')
				{
					sscanf(rline,"%s",cal_file_alpha); //ER

					cout << "  Give binary file to be processed:\n";
					cin  >>  bin_file;   //ER
					cout << "  Binary file: " << bin_file << "\n\n"; //ER
					ana.ReadCoefficients(cal_file_alpha,ana.xia_offsetA,ana.xia_gain_1A,ana.xia_gain_2A,NUMBER_OF_CHANNELS*NUMBER_OF_DGFS);

					cout << "  Sorting data:\n\n";

					strcpy(datafile,bin_file); //ER

					FILE* pFile = fopen(datafile,"rb");
					if(pFile==NULL) { cout << "  The input data file " << datafile << " does not exist! -> Abort!\n"; exit(1); }
					lPos = ftell(pFile);

					while(!feof(pFile))  // WHILE loop to read the .bin file
					{
						if((lheader = (unsigned short*)malloc(12))==NULL) exit(2);
						size_t tmpRes = fread(lheader,1,12,pFile);
						q= lheader;
						lSize= *q++;
						lmod_pr= lmod;
						lmod= *q++;
						free(lheader);
						if((lmod_pr >= lmod) || (feof(pFile)))
						{
							ana.Build(evp);
							memset(evp,0,sizeof(ANA_BUFFER));
							if(feof(pFile)) break;
						}
						fseek(pFile,lPos,SEEK_SET);
						if((lbuffer = (unsigned short*)malloc(2*lSize))==NULL) exit(2);
						lPos+= fread(lbuffer,1,2*lSize,pFile);
						if(decodeDgfData(10,lSize,lbuffer,evp,nofProcessedEvents) != 1) { cout << "Decoding DGF buffers failed!\n"; break; }
						free(lbuffer);
					}   // END WHILE loop to read the .bin file

					fclose(pFile);
				} // read lines in the .TXT file
			} // while loop over the rows
		} // check that the file can be opened
	} // check that file exists

	ana.End();

	time (&End); //ER added on 08/09
	dif = difftime(End,Start);
	cout << "\033[93m";
	cout << "  Processed in : " << dif << " seconds \n\n";
	
	cout << "  =============================================\n";
	cout << "  =              End of WM sort               =\n";
	cout << "  =============================================\n\n\033[0m";
	
	exit(0);
}

/* subevent id 1-10, type [10,22]: raw dgf data, format 0x103 */
int decodeDgfData(int sevtId, int sevtWc, unsigned short* sevtData, ANA_BUFFER* evp, int nofProcessedEvents)
{
	int len;
	unsigned short eventnum,channum,modnum,bufformat,hitpat,mod;
	unsigned short* next_module;
	unsigned short* send = sevtData + (sevtWc*sizeof(short)); /* global end of subevent */
	unsigned short* q = sevtData;

	#ifdef XIA_DEBUG
	cout << "evt # " << nofProcessedEvents << ": Subevent XIA " << sevtId << ": Dgf data, wc=" << sevtWc << "\n";
	#endif
	while(sevtWc>0)
	{
		eventnum=0;
		len=*q++;
		next_module= sevtData+len;
		modnum=*q++;
		modnum--;	/* DAQ counts from 1 */
		if(next_module>send)
		{
			cout << " XIA wrong buffer length: " << len << ", anfang:" << q << ", send: " << send << "\n";
			q=send;
			break;
		}
		if(modnum>NUMBER_OF_DGFS)
		{
			cout << " XIA wrong module number: " << modnum << "\n";
			q=next_module;
		}
		else
		{
			bufformat=*q++;
			#ifdef XIA_DEBUG
			cout << "  XIA module nb: " << modnum << ", length: " << len << ", type: " << sevtId << ", bufferformat: " << bufformat << "\n";
			#endif
			if((bufformat == COMP1_LM_BUFFORMAT) ||
			   (bufformat == COMP2_LM_BUFFORMAT) ||
			   (bufformat == COMP3_LM_BUFFORMAT)   )
			{
				evp->dgf[modnum].buftime[2]=*q++;	/* high */
				evp->dgf[modnum].buftime[1]=*q++;	/* mid */
				evp->dgf[modnum].buftime[0]=*q++;	/* low */
			}
			else
			{
				cout << "wrong buffer format: " << bufformat << " !\n";
				q=next_module;
			}
		}

		while(q < next_module)
		{
			if(eventnum>=MAXEVENTNUM)
			{
				cout << " XIA number of events (" << eventnum << ") exceeds array length (" << MAXEVENTNUM <<") -> skip other events\n";
				q=next_module;
				break;
			}
			hitpat=*q++;
			evp->dgf[modnum].hitpattern[eventnum]=hitpat;
			evp->dgf[modnum].eventtime[eventnum][1]=*q++;	/* high */
			evp->dgf[modnum].eventtime[eventnum][0]=*q++;	/* low */
			evp->dgf[modnum].eventtime[eventnum][2]=	evp->dgf[modnum].buftime[2] + (evp->dgf[modnum].eventtime[eventnum][1] < evp->dgf[modnum].buftime[1]);
			evp->dgf[modnum].leventtime[eventnum]=	evp->dgf[modnum].eventtime[eventnum][0]+
			65536ll*evp->dgf[modnum].eventtime[eventnum][1]+
			65536ll*65536ll*evp->dgf[modnum].eventtime[eventnum][2];
			#ifdef XIA_DEBUG
			printf(" XIA hitpattern: 0x%x\n XIA evtT_A=%d  evtT_B=%d  evtT_C=%d\n",hitpat,evp->dgf[modnum].eventtime[eventnum][0],evp->dgf[modnum].eventtime[eventnum][1],evp->dgf[modnum].eventtime[eventnum][2]);
			printf(" XIA runtimes: A %d B %d C %d\n",evp->dgf[modnum].buftime[2],evp->dgf[modnum].buftime[1],evp->dgf[modnum].buftime[0]);
			#endif
			if(hitpat>15)
			{
				cout << " XIA hitpattern error: hitpattern=" << hitpat << "\n module: " << modnum << ", q: " << q << ", next_module: " << next_module << ", send: " << send << "\n";
				q=next_module;
			}
			else
			{
				for(channum=0; channum<4; channum++)
				{
					if(hitpat&(1<<channum))
					{
						evp->dgf[modnum].FTtime[eventnum][channum]=*q++;
						evp->dgf[modnum].energy[eventnum][channum]=*q++;
						if(bufformat == COMP2_LM_BUFFORMAT)
						{
							evp->dgf[modnum].CFtime[eventnum][channum]=*q++; *q++;
						} else evp->dgf[modnum].CFtime[eventnum][channum]= 0;
						#ifdef XIA_DEBUG
						printf(" XIA module %d channel %d event %d: FTtime: %d, energy: %d\n",modnum,channum,eventnum,evp->dgf[modnum].FTtime[eventnum][channum],evp->dgf[modnum].energy[eventnum][channum]);
						#endif
						evp->dgf[modnum].lFTtime[eventnum][channum]=	evp->dgf[modnum].FTtime[eventnum][channum]+
						65536ll*evp->dgf[modnum].eventtime[eventnum][1] +
						65536ll*65536ll*evp->dgf[modnum].eventtime[eventnum][2];
					}
				}
				eventnum++;
			}
		} // while(q < next_module)
		evp->dgf[modnum].numofevents=eventnum;
		sevtWc -= len;
		if(len & 1) { q++; sevtWc--; } /* MBS data: always 32bit words -> if len odd -> fill word has to be skipped */
	} // while(sevtWc)
	return 1;
}
