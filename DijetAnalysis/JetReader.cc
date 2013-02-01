// *********************************************************************//
//  JetReader - Used for plotting Back-to-back jet suppression factor Aj
//  Also used for plotting Jet phi correlation (Added Sept 18, 2012)
//  Also used for plotting Sum(pt) tracks in cone / primary jet pt (Added 9/18/12)
//  Kurt Jung, Purdue University
//  Created Sept 17, 2012
//  Modified 1/21/13 for pA 2013 Run @ LHC (CMS)
// *********************************************************************//

// **********************
// Runs:     Events:   Data Location:                                                                                     Filesize:   Pileup:   Int. Rate:
// 210837   root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210837_autoforest_v51.root
// 210818   root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210818_autoforest_v51.root
// 210759   root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210759_autoforest_v51.root
// 210738   root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210738_autoforest_v51.root
// 210737      170K     EOS:/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210737_autoforest_v51.root
// 210676      874K     EOS:/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210676_autoforest_v51.root   32G    (PU = 6%)   220 kHz
// 210635      528K	EOS:/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210635_autoforest_v51.root   15G    (PU = 6%)   140 kHz
// 210634      517K	EOS:/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210634_autoforest_v51.root   15G    (PU = 6%)   140 kHz
// 210614      770K	EOS:/store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210614_autoforest_v51.root   22G    (PU = 6%)   140 kHz 

// /store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210534_autoforest_v51.root
// /store/group/phys_heavyions/velicanu/forest/PA2013_HiForest_Express_r210498_autoforest_v51.root

// **********************

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include "TVector3.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define PI 3.14159265359
#define JetPerEvent 600

using namespace std;

struct JetObject{
  double pt;
  double eta;
  double phi;
  double rawpt;
  double refpartonpt;
};

const int mcWeightBins[8] = {15,30,50,80,120,170,220,280};
const double mcWeighting[8] = {5.335E-01, 3.378E-02, 3.778E-03, 4.412E-04, 6.147E-05, 1.018E-05, 2.477E-06, 6.160E-07};

bool DataSort(const JetObject &data1 , const JetObject &data2){
  return data1.pt > data2.pt;
}

double getMCWeight(double refpt){
  int i=0;
  double weight=0;
  while(refpt>mcWeightBins[i] && i<7) i++;
  if(i!=7){
    weight = mcWeighting[i];//-mcWeighting[i+1];
  }
  else weight=mcWeighting[i];

  return weight;
}

void JetReader(std::string infile = "PA2013_filelist.txt", std::string outfile = "Dijet_Jet80_3Run_", int startfile=0, int endfile=1){
    
  //************************************/
  //    Jet Cuts:
  double phicutoff = (2.0*PI / 3.0);
  double etacut = 2.0;
  double etashift = 0.;
  double algoConeSize = 0.5;
  std::string jetCollection = "akPu3PF";
  bool backgroundCalc = false;

  //************************************/

  const int multiplicityBins = 6;
  int multBinColl[multiplicityBins+1] = {0,35,60,90,110,150,1000};
  const int etaBins = 2; //Positive and negative eta
  bool isMC = true;

  //************************************/
  
  cout << "************ PARAMETER SET *************" << endl;
  cout << "Abs(phi) cutoff: " << phicutoff << endl;
  cout << "Abs(eta) cutoff: " << etacut << endl;
  cout << "Cone size: " << algoConeSize << endl;
  cout << "Jet Collection: " << jetCollection << endl;
  if(backgroundCalc) cout << "Background Calculation: ON" << endl;
  else cout << "Background Calculation: OFF" << endl;
  if(isMC) cout << "MC Turned ON... Using Reweighting Factors" << endl;
  else cout << "MC Off.  Assuming no reweighting necessary." << endl;
  cout << "****************************************" << endl;

  outfile = outfile+jetCollection+".root";
  TFile *out = new TFile(outfile.c_str(),"recreate");
  
  ifstream instr (infile.c_str(), ifstream::in);
  string filename;
  
  TH1D *aj_60_30[multiplicityBins][etaBins];
  TH1D *aj_80_30[multiplicityBins][etaBins];
  TH1D *aj_100_30[multiplicityBins][etaBins];

  for(int imult = 0; imult<multiplicityBins; imult++){
    for(int ieta = 0; ieta<etaBins; ieta++){
      char* histoname = new char[100];
      sprintf(histoname,"%s%d%s%d","aj_60_30_mult",imult,"_eta",ieta);
      aj_60_30[imult][ieta] = new TH1D(histoname,"",10,0,1);
      sprintf(histoname,"%s%d%s%d","aj_80_30_mult",imult,"_eta",ieta);
      aj_80_30[imult][ieta] = new TH1D(histoname,"",10,0,1);
      sprintf(histoname,"%s%d%s%d","aj_100_30_mult",imult,"_eta",ieta);
      aj_100_30[imult][ieta] = new TH1D(histoname,"",10,0,1);
      aj_60_30[imult][ieta]->Sumw2();
      aj_80_30[imult][ieta]->Sumw2();
      aj_100_30[imult][ieta]->Sumw2();
    }
  }

  TH1D *coneSumPt = new TH1D("coneSumPt","",100,0,2.5);
  coneSumPt->Sumw2();


  //Dijet Tree Creation
  // !!!!*******************************************************!!!!
  // !!  WARNING! Dijet Tree has implicit pt > 20 && |eta|<2 cuts !!
  // !!!!*******************************************************!!!!
  double pt1, pt2, pt3, phi1, phi2, phi3, eta1, eta2, eta3, rawpt1, rawpt2, rawpt3, eForward, vecPt3Pt2, zvtx, pthat, weight;
  int evtTrks, evtTrksSubJets, evtTrksSubLeadingJet, oldTrks;
  bool PUFilterG, PUFilterGLoose;
  TTree *dijetTree = new TTree("dijetTree","");
  dijetTree->Branch("pt1",&pt1);
  dijetTree->Branch("eta1",&eta1);
  dijetTree->Branch("phi1",&phi1);
  dijetTree->Branch("pt2",&pt2);
  dijetTree->Branch("eta2",&eta2);
  dijetTree->Branch("phi2",&phi2);
  dijetTree->Branch("tracks",&evtTrks);
  dijetTree->Branch("rawPt1",&rawpt1);
  dijetTree->Branch("rawPt2",&rawpt2);
  dijetTree->Branch("pthat",&pthat);
  dijetTree->Branch("weight",&weight);
  dijetTree->Branch("zvtx",&zvtx);
  dijetTree->Branch("pt3",&pt3);
  dijetTree->Branch("eta3",&eta3);
  dijetTree->Branch("phi3",&phi3);
  dijetTree->Branch("rawPt3",&rawpt3);
  dijetTree->Branch("hiHFplusEta4",&eForward);
  dijetTree->Branch("vecPt3Pt2",&vecPt3Pt2);
  dijetTree->Branch("oldTrks",&oldTrks);
  dijetTree->Branch("nTrksSubJets",&evtTrksSubJets);
  dijetTree->Branch("nTrksSubLeadingJet",&evtTrksSubLeadingJet);
  dijetTree->Branch("PUFilterG",&PUFilterG);
  dijetTree->Branch("PUFilterGloose",&PUFilterGLoose);

  int nContainers = 3;
  TH1D *phiCorr[nContainers];
  TH1D *phiCorrAll[nContainers];
  TH1D *phiCorrNoSub[nContainers];
  TH1D *phiCorrMix[nContainers];
  TH1D *phiCorrMixAll[nContainers];
  TH1D *phiCorrMixNoSub[nContainers];
  char* histoname = new char[100];

  for(int i=0; i<nContainers; i++){
    sprintf(histoname, "%s%d","phiCorrBin",i);
    phiCorr[i] = new TH1D(histoname,"",30,0,PI); //leading & subleading jet phi correlation
    sprintf(histoname, "%s%d","phiCorrAllBin",i);
    phiCorrAll[i] = new TH1D(histoname,"",30,0,PI); // phi correlations for all jets above 20 GeV
    sprintf(histoname, "%s%d","phiCorrNoSubBin",i);
    phiCorrNoSub[i] = new TH1D(histoname,"",30,0,PI); //phi correlations for all jets EXCEPT subleading jet

    sprintf(histoname, "%s%d","phiCorrMixBin",i);
    phiCorrMix[i] = new TH1D(histoname,"",30,0,PI); //leading & subleading jet phi correlation
    sprintf(histoname, "%s%d","phiCorrMixAllBin",i);
    phiCorrMixAll[i] = new TH1D(histoname,"",30,0,PI); // phi correlations for all jets above 20 GeV
    sprintf(histoname, "%s%d","phiCorrMixNoSubBin",i);
    phiCorrMixNoSub[i] = new TH1D(histoname,"",30,0,PI); //phi correlations for all jets EXCEPT subleading jet
    
    phiCorr[i]->Sumw2();
    phiCorrAll[i]->Sumw2();
    phiCorrNoSub[i]->Sumw2(); 

    phiCorrMix[i]->Sumw2();
    phiCorrMixAll[i]->Sumw2();
    phiCorrMixNoSub[i]->Sumw2();
  }

  //JetAnalyzer
  Float_t jetpt[JetPerEvent];
  Float_t jetphi[JetPerEvent];
  Float_t jeteta[JetPerEvent];
  int evt = 0;

  //Raw Jet Pt Analyzer
  Float_t rawJetPt[JetPerEvent];
  Float_t refpartonPt[JetPerEvent];
  //Float_t rawJetPhi[JetPerEvent];
  //Float_t rawJetEta[JetPerEvent];

  //TrackAnalyzer
  Float_t trackPt[2500];
  Float_t trackEta[2500];
  Float_t trackPhi[2500];
  //Int_t ntrks;
  Float_t vz[2];
  Float_t zVtx[10];

  //Trigger Selection
  Int_t MultJetXTrg;
  Int_t Jet80Trg;

  //Event Selection
  Int_t pPAcollisionEventSelectionPA;
  Int_t pHBHENoiseFilter;
  Int_t VertexFilterG;
  Int_t VertexFilterGloose;

  //hi Tracks (N tracks w/ quality cuts && forward energy dep.)
  Int_t hiNtracks;
  Float_t hiHF;
  Int_t oldOffTracks;
  Float_t ptHat;

  double avgMult[multiplicityBins];
  int avgMultColl[multiplicityBins];
  for(int i=0; i<multiplicityBins; i++){
    avgMult[i]=0;
    avgMultColl[i]=0;
  }
  
  std::vector<std::vector< JetObject > > eventVector[5];
  std::vector<std::vector< JetObject > > MBeventVector[5];
  
  std::vector< JetObject > ptvector;
  std::vector< JetObject > MBpartVector;
  std::vector< JetObject >::iterator it;

  int nEntries = 0;
  int totEntries = 0;
  jetCollection = jetCollection+"JetAnalyzer/t";
  
 for(int i=0; i<startfile; i++){
    instr >> filename;
  }
  for(int ifile=startfile; ifile<endfile; ifile++){
    instr >> filename;
    cout << "Opened file: " << filename.c_str() << endl;
    if(isMC) cout << "MC is ON. Using weight: " << mcWeighting[ifile] << endl;
    TFile *inf = TFile::Open(filename.c_str());
    if(!inf) cout << "Warning, file not opened correctly!" << endl;

    TTree* t = (TTree*)inf->Get(jetCollection.c_str());
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
    nEntries = t->GetEntries();
    totEntries += nEntries;

    t->SetBranchAddress("jtpt", &jetpt);
    t->SetBranchAddress("jtphi", &jetphi);
    t->SetBranchAddress("jteta", &jeteta);
    t->SetBranchAddress("evt", &evt);
    t->SetBranchAddress("rawpt",&rawJetPt);
    if(isMC) t->SetBranchAddress("refparton_pt",&refpartonPt);

    t->SetBranchAddress("trkPt", &trackPt);
    t->SetBranchAddress("trkEta", &trackEta);
    t->SetBranchAddress("trkPhi", &trackPhi);
    t->SetBranchAddress("nTrk", &oldOffTracks);
    t->SetBranchAddress("vz", &vz);
    t->SetBranchAddress("zVtx",&zVtx);
    if(isMC) t->SetBranchAddress("pthat",&ptHat);
  
    if(!isMC) t->SetBranchAddress("HLT_PAPixelTrackMultiplicity140_Jet80_NoJetID_v1", &MultJetXTrg);
    else MultJetXTrg=0;
    t->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&Jet80Trg);
    t->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
    t->SetBranchAddress("pPAcollisionEventSelectionPA",&pPAcollisionEventSelectionPA);

    t->SetBranchAddress("hiNtracks", &hiNtracks);
    t->SetBranchAddress("hiHFplusEta4",&hiHF);
    t->SetBranchAddress("pVertexFilterCutG",&VertexFilterG);
    t->SetBranchAddress("pVertexFilterCutGloose",&VertexFilterGloose);

    cout << "File entries: " << nEntries << endl;
    int step = 1;
    for(int ientry=0; ientry<nEntries; ientry++){
      if(ientry%100000 == 0){
	cout << "step " << step++ << " of " << (nEntries/100000+1) << endl;
      }

      for(int i=0; i<10; i++){
	zVtx[i]=0;
      }
      
      //reinitialize array at every new event
      for(int i=0; i<JetPerEvent; i++){
	jetpt[i] = 0;
	jetphi[i] = 0;
	jeteta[i] = 0;
	rawJetPt[i] = 0;
	refpartonPt[i] = 0;
      }
      for(int i=0; i<2500; i++){
	trackPt[i] = 0;
	trackEta[i] = 0;
	trackPhi[i] = 0;
      }

      //check for trigger pass at first to save time
      //Switch between High multiplicity + Jet trigger and simple Jet 80 trigger
      t->GetEntry(ientry);
      //if(MultJetXTrg && pPAcollisionEventSelectionPA && pHBHENoiseFilter){
      if(Jet80Trg && pPAcollisionEventSelectionPA && pHBHENoiseFilter && zVtx[1] == 0){
      
	int multBin=0;
	while(hiNtracks > multBinColl[multBin+1] && multBin < multiplicityBins) multBin++;
	if(multBin==multiplicityBins) multBin--;
      
	avgMult[multBin] += hiNtracks;
	avgMultColl[multBin]++;      

	evtTrks = hiNtracks;
	oldTrks = oldOffTracks;
	evtTrksSubJets = oldTrks;
	evtTrksSubLeadingJet = oldTrks;
	eForward = hiHF;
	PUFilterG = VertexFilterG;
	PUFilterGLoose = VertexFilterGloose;
	if(isMC){
	  pthat = ptHat;
	  weight = getMCWeight(pthat);
	}
	else{ pthat=0; weight=1; }
	//offTracks = oldOffTracks;
	zvtx = vz[1];
	//if(ntrks>800) continue;
	      
	//construct vector of jets in each event in form (pt, (phi, eta))
	for(int j=0; j<JetPerEvent; j++){
	  if(jetpt[j] > 20 && (TMath::Abs(jeteta[j]-etashift)) < etacut && TMath::Abs(vz[1]) < 30){
	    JetObject tmp;
	    tmp.pt = jetpt[j];
	    tmp.eta = jeteta[j];
	    tmp.phi = jetphi[j];
	    tmp.rawpt = rawJetPt[j];
	    if(isMC) tmp.refpartonpt = refpartonPt[j];
	    else tmp.refpartonpt = 0;
	    ptvector.push_back(tmp);
	  }
	}
	/*for(int itrk=0; itrk<hiNtracks; itrk++){
	  JetObject tmp;
	  tmp.pt = trackPt[itrk];
	  tmp.eta = trackEta[itrk];
	  tmp.phi = trackPhi[itrk];
	  tmp.rawpt = -1;
	  MBpartVector.push_back(tmp);
	  }*/
	if(backgroundCalc){
	  if(ptvector.size() > 1){
	    if(TMath::Abs(vz[1]) < 20){
	      int vzarr = (int)((20.+vz[1]) / 8.);
	      eventVector[vzarr].push_back(ptvector);
	      if(MBpartVector.size() > 1){
		MBeventVector[vzarr].push_back(MBpartVector);
	      }
	    }
	  }
	}
      
	//ptvector contains all pt values w/ coordinate values in event in ascending order
	//This probably doesn't do anything, but it keeps me sane
	sort(ptvector.begin(), ptvector.end(), DataSort);
      
	//reverses to sort in descending order
	//reverse(ptvector.begin(), ptvector.end());

	//Do ntrack subtraction within the jet cone
	if(ptvector.size() > 0){
	  for(unsigned int ijet=0; ijet<ptvector.size(); ijet++){
	    for(int itrk=0; itrk<oldTrks; itrk++){
	      if(trackPt[itrk] > 0.1 && trackPt[itrk] < 1.2){
		if(TMath::Sqrt(pow((trackEta[itrk] - ptvector.at(ijet).eta),2) + pow((trackPhi[itrk] - ptvector.at(ijet).phi),2)) < 0.3){
		  if(ijet==0){
		    evtTrksSubLeadingJet--;
		  }
		  evtTrksSubJets--;
		}
	      }
	    }
	  }
	}

	int etabin=-1;
	if(ptvector.size() >= 2){
	  //for(unsigned int ijet=1; ijet<ptvector.size(); ijet++){
	  TVector3 ptVec2, ptVec3;
	  eta1 = ptvector.at(0).eta;
	  eta2 = ptvector.at(1).eta;
	  phi1 = ptvector.at(0).phi;
	  phi2 = ptvector.at(1).phi;
	  pt1 = ptvector.at(0).pt;
	  pt2 = ptvector.at(1).pt;
	  rawpt1 = ptvector.at(0).rawpt;
	  rawpt2 = ptvector.at(1).rawpt;
	  if(ptvector.size() > 2){
	    eta3 = ptvector.at(2).eta;
	    phi3 = ptvector.at(2).phi;
	    pt3 = ptvector.at(2).pt;
	    rawpt3 = ptvector.at(2).rawpt;
	    ptVec2.SetPtEtaPhi(pt2,eta2,phi2);
	    ptVec3.SetPtEtaPhi(pt3,eta3,phi3);
	    vecPt3Pt2 = (ptVec2+ptVec3).Mag();
	  }
	  else{
	    eta3 = -999;
	    phi3 = -999;
	    pt3 = -999;
	    rawpt3 = -999;
	    vecPt3Pt2 = -999;
	  }
	  //cout << "Total tracks: " << hiNtracks << endl;
	  //cout << "Tracks - leading jet: " << evtTrksSubLeadingJet << endl;
	  //cout << "Tracks - all jets: " << evtTrksSubJets << endl;
	  dijetTree->Fill();
	  if(ptvector.at(0).eta > 0) etabin = 1;
	  else etabin = 0;
	  if(TMath::Abs(ptvector.at(0).phi - ptvector.at(1).phi) > phicutoff){
	    double aj_evt =  ((pt1 - pt2) / (pt1 + pt2));
	    if(pt1 > 60 && pt2 > 30){
	      aj_60_30[multBin][etabin]->Fill(aj_evt);
	    }
	    if(pt1 > 80 && pt2 > 30){
	      aj_80_30[multBin][etabin]->Fill(aj_evt);
	    }
	    if(pt1 > 100 && pt2 > 30){
	      aj_100_30[multBin][etabin]->Fill(aj_evt);
	    }
	    //  }
	  }
	  for(unsigned int k=1; k<ptvector.size(); k++){
	    double delPhi = TMath::Abs(ptvector.at(0).phi - ptvector.at(k).phi);
	    if(delPhi > PI){
	      delPhi = TMath::Abs(delPhi - (2*PI));
	    }
	    //Primary jet > 60 GeV && Secondary > 30 GeV
	    if(ptvector.at(0).pt > 60 && ptvector.at(1).pt > 30){
	      if(k==1){
		phiCorr[0]->Fill(delPhi);
	      }
	      else{
		phiCorrNoSub[0]->Fill(delPhi);
	      }
	      phiCorrAll[0]->Fill(delPhi);
	    }
	    //Primary jet > 80 GeV && Secondary > 30 GeV
	    if(ptvector.at(0).pt > 80 && ptvector.at(1).pt > 30){
	      if(k==1){
		phiCorr[1]->Fill(delPhi);
	      }
	      else{
		phiCorrNoSub[1]->Fill(delPhi);
	      }
	      phiCorrAll[1]->Fill(delPhi);
	    }
	    //Primary jet > 100 GeV && Secondary > 30 GeV
	    if(ptvector.at(0).pt > 100 && ptvector.at(1).pt > 30){
	      if(k==1){
		phiCorr[2]->Fill(delPhi);
	      }
	      else{
		phiCorrNoSub[2]->Fill(delPhi);
	      }
	      phiCorrAll[2]->Fill(delPhi);
	    }
	  }
	}
      
	//Now calculate Sum pT from tracks within jet cone / Jet pT
	/*	for(unsigned int ijet = 0; ijet<ptvector.size(); ijet++){
	  double PrimJetPt = ptvector.at(ijet).pt;
	  double PrimJetPhi = ptvector.at(ijet).phi;
	  double PrimJetEta = ptvector.at(ijet).eta;
	  double trkSumPt = 0;
	  //if(ntrks > 400) continue;  //I'll assume anything with more than 400 tracks is pileup and is not useful
	  for(int itrk=0; itrk<hiNtracks; itrk++){
	    if(TMath::Sqrt(pow((trackEta[itrk] - PrimJetEta),2) + pow((trackPhi[itrk] - PrimJetPhi),2)) < algoConeSize){
	      trkSumPt += trackPt[itrk];
	    }
	    }
	  coneSumPt->Fill(trkSumPt/PrimJetPt);
	}*/
	ptvector.clear();
	MBpartVector.clear();
	//cout << "evt: " << ientry << " finished" << endl;
      }
    }
    cout << "foreground done" << endl;
  }
  
  //Now do event mixing for the background - mix leading pt jet with all jets in all other events:
  if(backgroundCalc){
    for(unsigned int izvtx=0; izvtx<5; izvtx++){
      cout << "eventVector["<<izvtx<<"] size: " << eventVector[izvtx].size() << endl;
      if(eventVector[izvtx].size() < 2) {
	cout << "Warning, low statistics in eventVector["<<izvtx<<"]..." << endl;
	continue;
      }
      for(unsigned int ievt=0; ievt<eventVector[izvtx].size()-1; ievt++){
	if(eventVector[izvtx].at(ievt).at(0).pt <= 40) continue;
	for(unsigned int ievtII=0; ievtII<MBeventVector[izvtx].size(); ievtII++){
	  if(ievt==ievtII) continue;
	  for(unsigned int itrkII=0; itrkII<MBeventVector[izvtx].at(ievtII).size(); itrkII++){
	    double delPhi = TMath::Abs(eventVector[izvtx].at(ievt).at(0).phi - MBeventVector[izvtx].at(ievtII).at(itrkII).phi);
	    if(delPhi > PI){
	      delPhi = TMath::Abs(delPhi - (2*PI));
	    }
	    //Primary jet > 40 GeV && Secondary > 20 GeV
	    if(eventVector[izvtx].at(ievt).at(0).pt > 40 && MBeventVector[izvtx].at(ievtII).at(itrkII).pt > 20){
	      phiCorrMixAll[0]->Fill(delPhi);
	    }
	    //Primary jet > 50 GeV && Secondary > 25 GeV
	    if(eventVector[izvtx].at(ievt).at(0).pt > 50 && MBeventVector[izvtx].at(ievtII).at(itrkII).pt > 25){
	      
	      phiCorrMixAll[1]->Fill(delPhi);
	    }
	    //Primary jet > 60 GeV && Secondary > 30 GeV
	    if(eventVector[izvtx].at(ievt).at(0).pt > 60 && MBeventVector[izvtx].at(ievtII).at(itrkII).pt > 30){
	      
	      phiCorrMixAll[2]->Fill(delPhi);
	    }
	  }
	}
      }
    }
  }

  out->cd();
  double scl = 1/(float)nEntries;
  for(int imult=0; imult<multiplicityBins; imult++){
    for(int ieta=0; ieta<etaBins; ieta++){
      aj_60_30[imult][ieta]->Scale(scl);
      aj_60_30[imult][ieta]->Scale(1./(float)aj_60_30[imult][ieta]->Integral());
      aj_60_30[imult][ieta]->Write();
      aj_80_30[imult][ieta]->Scale(scl);
      aj_80_30[imult][ieta]->Scale(1./(float)aj_80_30[imult][ieta]->Integral());
      aj_80_30[imult][ieta]->Write();
      aj_100_30[imult][ieta]->Scale(scl);
      aj_100_30[imult][ieta]->Scale(1./(float)aj_100_30[imult][ieta]->Integral());
      aj_100_30[imult][ieta]->Write();
    }
    cout << "total events in mult bin " << imult << " = " << avgMultColl[imult] << endl;
    avgMult[imult] = avgMult[imult]/(double)avgMultColl[imult];
    cout << "<mult> for " << multBinColl[imult] << " < N < " << multBinColl[imult+1] << " = " << avgMult[imult] << endl;
  }
  
  //float MBevtsize=0;
  //for(int i=0; i<5; i++){
  //  MBevtsize += MBeventVector[i].size();
  //}
  
  /*  for(int i=0; i<nContainers; i++){
    sprintf(histoname,"%s%d%s","Jet / Subleading Jet (p_{T} > ",(20+5*i),") Correlation");
    phiCorr[i]->SetTitle(histoname);
    phiCorr[i]->SetXTitle("#Delta#phi");
    phiCorr[i]->SetYTitle("Njets");
    phiCorr[i]->Scale(scl);
    phiCorr[i]->Write();
    sprintf(histoname,"%s%d%s","Jet / All Jet (p_{T} > ",(20+5*i),") Correlation");
    phiCorrAll[i]->SetTitle(histoname);
    phiCorrAll[i]->SetXTitle("#Delta#phi");
    phiCorrAll[i]->SetYTitle("Njets");
    phiCorrAll[i]->Scale(scl);
    phiCorrAll[i]->Write();
    sprintf(histoname,"%s%d%s","Jet / All Jets without subjet (p_{T} > ",(20+5*i),") Correlation");
    phiCorrNoSub[i]->SetTitle(histoname);
    phiCorrNoSub[i]->SetXTitle("#Delta#phi");
    phiCorrNoSub[i]->SetYTitle("Njets");
    phiCorrNoSub[i]->Scale(scl);
    phiCorrNoSub[i]->Write();
    sprintf(histoname,"%s%d%s","Jet / All Jet (p_{T} > ",(20+5*i),") Event Mixing BG");
    phiCorrMixAll[i]->SetTitle(histoname);
    phiCorrMixAll[i]->SetXTitle("#Delta#phi");
    phiCorrMixAll[i]->SetYTitle("Njets");
    phiCorrMixAll[i]->Scale(scl);
    //phiCorrMixAll[i]->Scale(1./(float)MBevtsize);
    phiCorrMixAll[i]->Write();
    }*/
  //coneSumPt->Write();
  
  dijetTree->Write();

  out->Close();
}
