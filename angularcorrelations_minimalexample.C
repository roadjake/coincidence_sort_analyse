/* 
* Copyright 2019 Sandro Kraemer*  
* Licensed under the EUPL, Version 1.1 or – as soon theywill be approved by the European Commission - subsequentversions of the EUPL (the "Licence");
* You may not use this work except in compliance with theLicence.* You may obtain a copy of the Licence at:
*  *https://joinup.ec.europa.eu/software/page/eupl5*  
* Unless required by applicable law or agreed to inwriting, software distributed under the Licence isdistributed on an "AS IS" basis,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, eitherexpress or implied.
* See the Licence for the specific language governingpermissions and limitations under the Licence.
*/

#include "TFile.h"
#include "TTree.h"
#include <stdio.h>
#include <TChain.h>

struct data_struct{
	ULong64_t time;
	UShort_t energy;
	UShort_t detector;
};
#define DATALENGTH 4000000

void angularcorrelations_minimalexample() {
	
	struct data_struct data[DATALENGTH];
	struct data_struct temp;
	
	//Initialize tree structure
	TFile *file;
	TTree *tree;
	TLeaf *leaf_energy;	
	TLeaf *leaf_time;
    	TLeaf *leaf_detector;
	if((file = TFile::Open("input.root"))==0){cout << "Could not find file" <<endl;return 1;}
	if((tree = (TTree*)file->Get("Data_F"))==0){cout << "Could not find tree" << endl;return 1;}
	if((leaf_energy = tree->GetLeaf("Energy"))==0){cout << "Could not find leaf" << endl;return 1;} //Contains the energy in channels
	if((leaf_time = tree->GetLeaf("Timestamp"))==0){cout << "Could not find leaf" << endl;return 1;} //Contains the timestamp in picoseconds
	if((leaf_detector = tree->GetLeaf("Channel"))==0){cout << "Could not find leaf" << endl;return 1;}//Contains the channelnumber/detector


	//load data into RAM
	int entries = tree->GetEntries();
	fprintf(stderr,"\nloading %d entries into RAM\n",entries);
	if(entries>DATALENGTH) {fprintf(stderr,"\nERROR: not enough memory. Change settings.");exit(1);}
	for(int n=0;n<entries;n++){
		if(n%1000==0) {fprintf(stderr,"\r  processing %.0f percent",(float)n/(float)entries*100);}
		tree->GetEntry(n);
		data[n].time = leaf_time->GetValue(0)/1000;
		data[n].energy = leaf_energy->GetValue(0);
		data[n].detector = leaf_detector->GetValue(0);
	}
	file->Close();
	fprintf(stderr,"\r  ok                    ");


	//output an energy histogram for each detector
	fprintf(stderr,"\nplotting energy histograms\n");
	TH1F *energy1histo = new TH1F("energy1","energy detector 1 (unconstrained)",600,0,600);
	TH1F *energy2histo = new TH1F("energy2","energy detector 2 (unconstrained)",600,0,600);
	for(int n=0;n<entries;n++){
		if(data[n].detector == 0){
			energy1histo->Fill(data[n].energy);
		}
		if(data[n].detector == 1){
			energy2histo->Fill(data[n].energy);
		}
	}
	new TCanvas();
	energy1histo->Draw();
	new TCanvas();
	energy2histo->Draw();
	fprintf(stderr,"\r  ok                    ");
	


}
