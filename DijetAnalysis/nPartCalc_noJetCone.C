
#include "TFile.h"
#include "TVector3.h"
#include "TH1D.h"
#include "TTree.h"
#include "TMath.h"

#include <iostream>
#include <fstream>

#define PI 3.14159266

using namespace std;

void nPartCalc_noJetCone(std::string infile, int startfile, int endfile){

  const int JetPerEvent=500;
  const int trackPerEvent=1500;
  
  Float_t jetpt[JetPerEvent];
  Float_t jetphi[JetPerEvent];
  Float_t jeteta[JetPerEvent];

  Float_t trackPt[trackPerEvent];
  Float_t trackEta[trackPerEvent];
  Float_t trackPhi[trackPerEvent];

  Int_t pPAcollisionEventSelectionPA;
  Int_t pHBHENoiseFilter;

  TH1D *trkTot = new TH1D("trkTot","",200,0,15);
  TH1D *trkPerp = new TH1D("trkPerp","",200,0,15);

  TFile *out = new TFile("nPartCalc.root","recreate");

  ifstream instr (infile.c_str(), ifstream::in);
  string filename;
  for(int i=0; i<startfile; i++){
    instr >> filename;
  }
  for(int ifile=startfile; ifile<endfile; ifile++){
    instr >> filename;
    cout << "Opened file: " << filename.c_str() << endl;
    TFile *inf = TFile::Open(filename.c_str());
    if(!inf) cout << "Warning, file not opened correctly!" << endl;

    TTree* t = (TTree*)inf->Get("akPu3PFJetAnalyzer/t");
    TTree* trks = (TTree*)inf->Get("ppTrack/trackTree");
    TTree *hltTree = (TTree*)inf->Get("hltanalysis/HltTree");
    TTree *evtSel = (TTree*)inf->Get("skimanalysis/HltTree");
    //Switch to hiNtracks (N charged trks w/ quality & eta? cuts)
    TTree *hiEvt = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");

    if(!t || !trks || !hltTree || !evtSel || !hiEvt) {cout << "Cannot get trees from file!" << endl; exit(0); }
    t->AddFriend("ppTrack/trackTree");
    t->AddFriend("hltanalysis/HltTree");
    t->AddFriend("skimanalysis/HltTree");
    t->AddFriend("hiEvtAnalyzer/HiTree");

    t->SetBranchAddress("jtpt", &jetpt);
    t->SetBranchAddress("jtphi", &jetphi);
    t->SetBranchAddress("jteta", &jeteta);
    t->SetBranchAddress("trkPt", &trackPt);
    t->SetBranchAddress("trkEta", &trackEta);
    t->SetBranchAddress("trkPhi", &trackPhi);

    t->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
    t->SetBranchAddress("pPAcollisionEventSelectionPA",&pPAcollisionEventSelectionPA);

    int nEntries = t->GetEntries();
    cout << "File entries: " << nEntries << endl;
    int step = 1;
    for(int ientry=0; ientry<nEntries; ientry++){
      if(ientry%100000 == 0){
	cout << "step " << step++ << " of " << (nEntries/100000+1) << endl;
      }
      
      //reinitialize array at every new event
      for(int i=0; i<JetPerEvent; i++){
	jetpt[i] = 0;
	jetphi[i] = 0;
	jeteta[i] = 0;
      }
      for(int i=0; i<trackPerEvent; i++){
	trackPt[i] = 0;
	trackEta[i] = 0;
	trackPhi[i] = 0;
      }

       t->GetEntry(ientry);
       if(pPAcollisionEventSelectionPA && pHBHENoiseFilter){

	 //Find Highest pT in jet collection
	 double hiJetPt = jetpt[0];
	 int hiJetNo=0;
	 for(int jetno=1; jetno<JetPerEvent; jetno++){
	   if(jetpt[jetno] > hiJetPt) {hiJetPt = jetpt[jetno]; hiJetNo=jetno;}
	 }
	 TVector3 leadJet;
	 leadJet.SetPtEtaPhi(jetpt[hiJetNo], jeteta[hiJetNo], jetphi[hiJetNo]);

	 for(int itrk=0; itrk<trackPerEvent; itrk++){
	   if(trackPt[itrk] > 0.1){
	     trkTot->Fill(trackPt[itrk]);
	     TVector3 track;
	     track.SetPtEtaPhi(trackPt[itrk], trackEta[itrk], trackPhi[itrk]);
	     double cosTheta = track.Dot(leadJet) / (track.Mag()*leadJet.Mag());
	     //if((angle > PI/4 && angle < 3*PI/4) || (angle > 5*PI/4 && angle < 7*PI/4)){
	     if( TMath::Abs(cosTheta) < (TMath::Sqrt(2)/2.)){
	       trkPerp->Fill(trackPt[itrk]);
	     }
	   }
	 }
       }
    }
  }
  out->cd();
  trkTot->Write();
  trkPerp->Write();
  out->Close();
}
