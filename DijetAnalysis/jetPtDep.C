#include "commonUtility.h"

const double PI=3.1415926;

double GetMu(TH1D *input, int parorErr){

  TF1 *fitter = new TF1("fitter","gaus",-2,2);
  input->Scale(1./(input->GetEntries()));
  fitter->SetParameters(input->GetMaximum(),-0.1,1.0);
  input->Fit("fitter","qN0","",-1.5,1.5);
  if(parorErr==1){
    return fitter->GetParameter(1);
  }
  else if(parorErr==2){
    return fitter->GetParError(1);
  }
  else return 0;
}

void jetPtDep(){

  //double multbins[4] = {0,47,66,90}; //(~equal integration)
  double multbins[6] = {0,5,10,15,20,30}; //hiHFplusEta4 binning???
  //double multbins[6] = {0,60,90,110,150,180}; //mult binning
  double phitop=2, phibot=3;
  double deltaPhiCut = (phitop*PI/phibot);
  std::string jetcoll = "ak3PuPF";

  std::string infile = "FullForest_highPt_v71_akPu3PF.root";
  TFile *f0 = TFile::Open(infile.c_str());
  if(!f0){ cout << "You don't have this jet collection yet!!" << endl; exit(0);}
  TTree *dijetTree = (TTree*)f0->Get("dijetTree");

  TFile *f1 = new TFile("PbPb_ReReco_Full_Good_akPu3PF.root","OLD");
  TTree *nt = (TTree*)f1->Get("dijetTree");
  TFile *fMC = new TFile("PythiaMIT_out_akPu3PF.root");
  TTree *mcTree = (TTree*)fMC->Get("dijetTree");

  TH1D *ptDepLead[6];
  TH1D *ptDepSublead[6];
  TH1D *MCptDepLead[6];
  TH1D *MCptDepSublead[6];
  TH1D *eta1Dep[6];
  TH1D *eta2Dep[6];
  TH1D *MCeta1Dep[6];
  TH1D *MCeta2Dep[6];
  TH1D *pPbeta[9];
  TH1D *PbPbeta[6];
  TH1D *MCeta[9];
  TH1D *pt1Dep[9];
  TH1D *pt2Dep[9];
  TH1D *MCpt1Dep[9];
  TH1D *MCpt2Dep[9];

  TH1D *etaDistro = new TH1D("etaDistro","",20,-2,2);
  TH1D *MCetaDistro = new TH1D("MCetaDistro","",20,-2,2);
  etaDistro->Sumw2();
  MCetaDistro->Sumw2();

  char* histoname = new char[50];
  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d","ptDepLead_",i);
    ptDepLead[i] = new TH1D(histoname,"",10,0,1);
    ptDepLead[i]->Sumw2();
    sprintf(histoname,"%s%d","ptDepSublead_",i);
    ptDepSublead[i] = new TH1D(histoname,"",10,0,1);
    ptDepSublead[i]->Sumw2();
    sprintf(histoname,"%s%d","MCptDepLead_",i);
    MCptDepLead[i] = new TH1D(histoname,"",10,0,1);
    MCptDepLead[i]->Sumw2();
    sprintf(histoname,"%s%d","MCptDepSublead_",i);
    MCptDepSublead[i] = new TH1D(histoname,"",10,0,1);
    MCptDepSublead[i]->Sumw2();
    sprintf(histoname,"%s%d","eta1Dep_",i);
    eta1Dep[i] = new TH1D(histoname,"",30,0,3.142);
    eta1Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","eta2Dep_",i);
    eta2Dep[i] = new TH1D(histoname,"",30,0,3.142);
    eta2Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","MCeta1Dep_",i);
    MCeta1Dep[i] = new TH1D(histoname,"",30,0,3.142);
    MCeta1Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","MCeta2Dep_",i);
    MCeta2Dep[i] = new TH1D(histoname,"",30,0,3.142);
    MCeta2Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","PbPbeta_",i);
    PbPbeta[i] = new TH1D(histoname,"",20,-2,2);
    PbPbeta[i]->Sumw2();
   
  }
  for(int i=0; i<10; i++){
    sprintf(histoname,"%s%d","pt1Dep_",i);
    pt1Dep[i] = new TH1D(histoname,"",30,0,3.142);
    pt1Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","pt2Dep_",i);
    pt2Dep[i] = new TH1D(histoname,"",30,0,3.142);
    pt2Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","MCpt1Dep_",i);
    MCpt1Dep[i] = new TH1D(histoname,"",30,0,3.142);
    MCpt1Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","MCpt2Dep_",i);
    MCpt2Dep[i] = new TH1D(histoname,"",30,0,3.142);
    MCpt2Dep[i]->Sumw2();
    sprintf(histoname,"%s%d","MCeta_",i);
    MCeta[i] = new TH1D(histoname,"",20,-2,2);
    MCeta[i]->Sumw2();
    sprintf(histoname,"%s%d","pPbeta_",i);
    pPbeta[i] = new TH1D(histoname,"",20,-2,2);
    pPbeta[i]->Sumw2();
  }

  std::string cut0 = "pt1>150 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut1 = "pt1>130 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut2 = "pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut3 = "pt1>110 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut4 = "pt1>100 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus &&  rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut5 = "pt1>90 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus &&  rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";

  std::string cut10 = "pt1>120 && pt2>60 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus &&  rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut11 = "pt1>120 && pt2>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut12 = "pt1>120 && pt2>40 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut13 = "pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut14 = "pt1>120 && pt2>25 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cut15 = "pt1>120 && pt2>20 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";

  std::string cutmc0 = "(weight/MCpthatEntries)*(pt1>150 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc1 = "(weight/MCpthatEntries)*(pt1>130 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc2 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc3 = "(weight/MCpthatEntries)*(pt1>110 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc4 = "(weight/MCpthatEntries)*(pt1>100 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc5 = "(weight/MCpthatEntries)*(pt1>90 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";

  std::string cutmc10 = "(weight/MCpthatEntries)*(pt1>120 && pt2>60 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc11 = "(weight/MCpthatEntries)*(pt1>120 && pt2>50 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc12 = "(weight/MCpthatEntries)*(pt1>120 && pt2>40 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc13 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc14 = "(weight/MCpthatEntries)*(pt1>120 && pt2>25 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmc15 = "(weight/MCpthatEntries)*(pt1>120 && pt2>20 && pthat>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";

  std::string cutphi0 = "pt1>120 && pt2>30 && eta1<-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi1 = "pt1>120 && pt2>30 && eta1<-0.66 && eta1>-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi2 = "pt1>120 && pt2>30 && eta1<0 && eta1>-0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi3 = "pt1>120 && pt2>30 && eta1>0 && eta1<0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi4 = "pt1>120 && pt2>30 && eta1>0.66 && eta1<1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi5 = "pt1>120 && pt2>30 && eta1>1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";

  std::string cutphi10 = "pt1>120 && pt2>30 && eta2<-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi11 = "pt1>120 && pt2>30 && eta2<-0.66 && eta2>-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi12 = "pt1>120 && pt2>30 && eta2<0 && eta2>-0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi13 = "pt1>120 && pt2>30 && eta2>0 && eta2<0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi14 = "pt1>120 && pt2>30 && eta2>0.66 && eta2<1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutphi15 = "pt1>120 && pt2>30 && eta2>1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";

  std::string cutmcphi0 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta1<-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70  && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi1 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta1<-0.66 && eta1>-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi2 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta1<0 && eta1>-0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi3 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta1>0 && eta1<0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi4 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta1>0.66 && eta1<1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi5 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta1>1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";

  std::string cutmcphi10 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta2<-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi11 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta2<-0.66 && eta2>-1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi12 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta2<0 && eta2>-0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi13 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta2>0 && eta2<0.66 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi14 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta2>0.66 && eta2<1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcphi15 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && eta2>1.33 && hiHFplusEta4>=0 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";

  std::string cutpt0 = "pt1>90 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt1 = "pt1>100 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt2 = "pt1>110 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt3 = "pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt4 = "pt1>130 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt5 = "pt1>150 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt6 = "pt1>180 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt7 = "pt1>220 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt8 = "pt1>300 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";

  std::string cutpt10 = "pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt11 = "pt1>120 && pt2>35 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt12 = "pt1>120 && pt2>40 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt13 = "pt1>120 && pt2>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt14 = "pt1>120 && pt2>60 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt15 = "pt1>120 && pt2>70 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt16 = "pt1>120 && pt2>80 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt17 = "pt1>120 && pt2>100 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";
  std::string cutpt18 = "pt1>120 && pt2>120 && hiHFplusEta4>=0 && hiHFplusEta4<70 && PUFilterGplus && rawPt1>15 && rawPt2>15";

  std::string cutmcpt0 = "pt1>90 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt1 = "pt1>100 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt2 = "pt1>110 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt3 = "pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt4 = "pt1>130 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt5 = "pt1>150 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt6 = "pt1>180 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt7 = "pt1>220 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt8 = "pt1>300 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";

  std::string cutmcpt10 = "pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt11 = "pt1>120 && pt2>35 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt12 = "pt1>120 && pt2>40 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt13 = "pt1>120 && pt2>50 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt14 = "pt1>120 && pt2>60 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt15 = "pt1>120 && pt2>70 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt16 = "pt1>120 && pt2>80 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt17 = "pt1>120 && pt2>100 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  std::string cutmcpt18 = "pt1>120 && pt2>120 && hiHFplusEta4>=0 && hiHFplusEta4<70 && pthat>50 && rawPt1>15 && rawPt2>15";
  
  std::string cutetau0 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=0  && hiHFplusEta4<2 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau033 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=2 && hiHFplusEta4<4 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau066 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=4 && hiHFplusEta4<6 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau1 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=5 && hiHFplusEta4<10 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau2 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=10 && hiHFplusEta4<15 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau3 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=15 && hiHFplusEta4<20 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau4 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=20 && hiHFplusEta4<30 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau5 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>=30 && hiHFplusEta4<70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";
  std::string cutetau6 = "rawPt1>120 && rawPt2>30 && hiHFplusEta4>70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944";

  std::string cutmcetau0 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>0 && hiHFplusEta4<=2 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau033 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>2 && hiHFplusEta4<=4 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau066 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>4 && hiHFplusEta4<=6 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau1 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>6 && hiHFplusEta4<=10 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau2 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>10 && hiHFplusEta4<=15 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau3 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>15 && hiHFplusEta4<=20 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau4 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>20 && hiHFplusEta4<=30 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau5 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>30 && hiHFplusEta4<=70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";
  std::string cutmcetau6 = "(weight/MCpthatEntries)*(pt1>120 && pt2>30 && pthat>50 && hiHFplusEta4>70 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)";

  dijetTree->Draw("pt2/pt1>>ptDepLead_0",cut0.c_str());
  dijetTree->Draw("pt2/pt1>>ptDepLead_1",cut1.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepLead_2",cut2.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepLead_3",cut3.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepLead_4",cut4.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepLead_5",cut5.c_str(),"same");

  dijetTree->Draw("pt2/pt1>>ptDepSublead_0",cut10.c_str());
  dijetTree->Draw("pt2/pt1>>ptDepSublead_1",cut11.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepSublead_2",cut12.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepSublead_3",cut13.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepSublead_4",cut14.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>ptDepSublead_5",cut15.c_str(),"same");

  mcTree->Draw("pt2/pt1>>MCptDepLead_0",cutmc0.c_str());
  mcTree->Draw("pt2/pt1>>MCptDepLead_1",cutmc1.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepLead_2",cutmc2.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepLead_3",cutmc3.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepLead_4",cutmc4.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepLead_5",cutmc5.c_str(),"same");

  mcTree->Draw("pt2/pt1>>MCptDepSublead_0",cutmc10.c_str());
  mcTree->Draw("pt2/pt1>>MCptDepSublead_1",cutmc11.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepSublead_2",cutmc12.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepSublead_3",cutmc13.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepSublead_4",cutmc14.c_str(),"same");
  mcTree->Draw("pt2/pt1>>MCptDepSublead_5",cutmc15.c_str(),"same");

  dijetTree->Draw("acos(cos(phi1-phi2))>>eta1Dep_0",cutphi0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta1Dep_1",cutphi1.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta1Dep_2",cutphi2.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta1Dep_3",cutphi3.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta1Dep_4",cutphi4.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta1Dep_5",cutphi5.c_str(),"same");

  dijetTree->Draw("acos(cos(phi1-phi2))>>eta2Dep_0",cutphi10.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta2Dep_1",cutphi11.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta2Dep_2",cutphi12.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta2Dep_3",cutphi13.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta2Dep_4",cutphi14.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>eta2Dep_5",cutphi15.c_str(),"same");

  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta1Dep_0",cutmcphi0.c_str());
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta1Dep_1",cutmcphi1.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta1Dep_2",cutmcphi2.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta1Dep_3",cutmcphi3.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta1Dep_4",cutmcphi4.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta1Dep_5",cutmcphi5.c_str(),"same");

  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta2Dep_0",cutmcphi10.c_str());
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta2Dep_1",cutmcphi11.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta2Dep_2",cutmcphi12.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta2Dep_3",cutmcphi13.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta2Dep_4",cutmcphi14.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCeta2Dep_5",cutmcphi15.c_str(),"same");

  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_0",cutpt0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_1",cutpt1.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_2",cutpt2.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_3",cutpt3.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_4",cutpt4.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_5",cutpt5.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_6",cutpt6.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_7",cutpt7.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt1Dep_8",cutpt8.c_str(),"same");

  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_0",cutpt10.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_1",cutpt11.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_2",cutpt12.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_3",cutpt13.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_4",cutpt14.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_5",cutpt15.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_6",cutpt16.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_7",cutpt17.c_str(),"same");
  dijetTree->Draw("acos(cos(phi1-phi2))>>pt2Dep_8",cutpt18.c_str(),"same");

  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_0",cutmcpt0.c_str());
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_1",cutmcpt1.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_2",cutmcpt2.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_3",cutmcpt3.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_4",cutmcpt4.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_5",cutmcpt5.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_6",cutmcpt6.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_7",cutmcpt7.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt1Dep_8",cutmcpt8.c_str(),"same");

  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_0",cutmcpt10.c_str());
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_1",cutmcpt11.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_2",cutmcpt12.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_3",cutmcpt13.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_4",cutmcpt14.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_5",cutmcpt15.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_6",cutmcpt16.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_7",cutmcpt17.c_str(),"same");
  mcTree->Draw("acos(cos(phi1-phi2))>>MCpt2Dep_8",cutmcpt18.c_str(),"same");

  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_0",cutetau0.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_1",cutetau033.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_2",cutetau066.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_3",cutetau1.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_4",cutetau2.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_5",cutetau3.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_6",cutetau4.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_7",cutetau5.c_str(),"same");
  dijetTree->Draw("(eta1+eta2)/2>>pPbeta_8",cutetau6.c_str(),"same");

  nt->Draw("(eta1+eta2)/2>>PbPbeta_0",cutetau0.c_str(),"same");
  nt->Draw("(eta1+eta2)/2>>PbPbeta_1",cutetau1.c_str(),"same");
  nt->Draw("(eta1+eta2)/2>>PbPbeta_2",cutetau2.c_str(),"same");
  nt->Draw("(eta1+eta2)/2>>PbPbeta_3",cutetau3.c_str(),"same");
  nt->Draw("(eta1+eta2)/2>>PbPbeta_4",cutetau4.c_str(),"same");
  nt->Draw("(eta1+eta2)/2>>PbPbeta_5",cutetau5.c_str(),"same");
  
  mcTree->Draw("(eta1+eta2)/2>>MCeta_0",cutmcetau0.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_1",cutmcetau033.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_2",cutmcetau066.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_3",cutmcetau1.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_4",cutmcetau2.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_5",cutmcetau3.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_6",cutmcetau4.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_7",cutmcetau5.c_str(),"same");
  mcTree->Draw("(eta1+eta2)/2>>MCeta_8",cutmcetau6.c_str(),"same");

  dijetTree->Draw("(eta1+eta2)/2>>etaDistro","pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PUFilterGplus && acos(cos(phi1-phi2)) > 2.0944");
  mcTree->Draw("(eta1+eta2)/2>>MCetaDistro","(weight/MCpthatEntries)*(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0944)","same");
  etaDistro->Scale(1./etaDistro->GetEntries());
  MCetaDistro->SetLineColor(2);
  MCetaDistro->SetMarkerColor(2);
  MCetaDistro->Scale(1./MCetaDistro->GetEntries());
  c1->Clear();
  c1->Divide(2,1);
  c1->cd(1);
  MCeta[0]->Scale(1./MCeta[0]->GetEntries());
  MCeta[0]->Scale(1e10);
  MCeta[0]->SetMaximum(0.15);
  MCeta[0]->SetXTitle("MC, <(gen #eta_{1}+gen #eta_{2})/2>");
  MCeta[0]->SetYTitle("Event Fraction");
  MCeta[0]->Draw();
  c1->cd(2);
  pPbeta[0]->Scale(1./pPbeta[0]->GetEntries());
  pPbeta[0]->SetMaximum(0.15);
  pPbeta[0]->SetXTitle("pPb Data, <(#eta_{1}+#eta_{2})/2>");
  pPbeta[0]->SetYTitle("Event Fraction");
  pPbeta[0]->Draw();
  TLegend *leg1 = new TLegend(0.15,0.78,0.99,0.91);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->AddEntry(pPbeta[0],"0<=E_{T}^{HFplus[#eta>4]}<2");
  leg1->AddEntry(pPbeta[2],"4<=E_{T}^{HFplus[#eta>4]}<6");
  leg1->AddEntry(pPbeta[4],"10<=E_{T}^{HFplus[#eta>4]}<15");
  leg1->AddEntry(pPbeta[6],"20<=E_{T}^{HFplus[#eta>4]}<30");
  for(int i=1; i<4; i++){
    c1->cd(1);
    MCeta[i*2]->Scale(1./MCeta[i*2]->GetEntries());
    MCeta[i*2]->Scale(1e10);
    MCeta[i*2]->SetLineColor(2*i);
    MCeta[i*2]->SetMarkerColor(2*i);
    MCeta[i*2]->Draw("same");
    c1->cd(2);
    pPbeta[i*2]->Scale(1./pPbeta[i*2]->GetEntries());
    pPbeta[i*2]->SetLineColor(2*i);
    pPbeta[i*2]->SetMarkerColor(2*i);
    pPbeta[i*2]->Draw("same");
  }
  leg1->Draw();

  TGraphErrors *centr[4];
  Double_t lead_npt[6] = {150,130,120,110,100,90};
  Double_t lead_avgPt[6] = {ptDepLead[0]->GetMean(), ptDepLead[1]->GetMean(), ptDepLead[2]->GetMean(), ptDepLead[3]->GetMean(), ptDepLead[4]->GetMean(), ptDepLead[5]->GetMean()};
  Double_t lead_nptErr[6] = {0,0,0,0,0,0};
  Double_t lead_avgPtErr[6] = {ptDepLead[0]->GetMeanError(), ptDepLead[1]->GetMeanError(), ptDepLead[2]->GetMeanError(), ptDepLead[3]->GetMeanError(), ptDepLead[4]->GetMeanError(), ptDepLead[5]->GetMeanError()};

  Double_t sublead_npt[6] = {60,50,40,30,25,20};
  Double_t sublead_avgPt[6] = {ptDepSublead[0]->GetMean(), ptDepSublead[1]->GetMean(), ptDepSublead[2]->GetMean(), ptDepSublead[3]->GetMean(), ptDepSublead[4]->GetMean(), ptDepSublead[5]->GetMean()};
  Double_t sublead_nptErr[6] = {0,0,0,0,0,0};
  Double_t sublead_avgPtErr[6] = {ptDepSublead[0]->GetMeanError(), ptDepSublead[1]->GetMeanError(), ptDepSublead[2]->GetMeanError(), ptDepSublead[3]->GetMeanError(), ptDepSublead[4]->GetMeanError(), ptDepSublead[5]->GetMeanError()};

  //MC leading and subleading pt dependence
  Double_t mclead_avgPt[6] = {MCptDepLead[0]->GetMean(), MCptDepLead[1]->GetMean(), MCptDepLead[2]->GetMean(), MCptDepLead[3]->GetMean(), MCptDepLead[4]->GetMean(), MCptDepLead[5]->GetMean()};
  Double_t mclead_avgPtErr[6] = {MCptDepLead[0]->GetMeanError(), MCptDepLead[1]->GetMeanError(), MCptDepLead[2]->GetMeanError(), MCptDepLead[3]->GetMeanError(), MCptDepLead[4]->GetMeanError(), MCptDepLead[5]->GetMeanError()};

  Double_t mcsublead_avgPt[6] = {MCptDepSublead[0]->GetMean(), MCptDepSublead[1]->GetMean(), MCptDepSublead[2]->GetMean(), MCptDepSublead[3]->GetMean(), MCptDepSublead[4]->GetMean(), MCptDepSublead[5]->GetMean()};
  Double_t mcsublead_avgPtErr[6] = {MCptDepSublead[0]->GetMeanError(), MCptDepSublead[1]->GetMeanError(), MCptDepSublead[2]->GetMeanError(), MCptDepSublead[3]->GetMeanError(), MCptDepSublead[4]->GetMeanError(), MCptDepSublead[5]->GetMeanError()};

  TGraphErrors *etar[4];
  Double_t lead_neta[6] = {-1.66, -1, -0.33, 0.33, 1, 1.66};
  Double_t lead_avgeta[6] = {eta1Dep[0]->GetMean(), eta1Dep[1]->GetMean(), eta1Dep[2]->GetMean(), eta1Dep[3]->GetMean(), eta1Dep[4]->GetMean(), eta1Dep[5]->GetMean()};
  Double_t lead_netaErr[6] = {0,0,0,0,0,0};
  Double_t lead_avgetaErr[6] = {eta1Dep[0]->GetMeanError(), eta1Dep[1]->GetMeanError(), eta1Dep[2]->GetMeanError(), eta1Dep[3]->GetMeanError(), eta1Dep[4]->GetMeanError(), eta1Dep[5]->GetMeanError()};

  Double_t sublead_neta[6] = {-1.66, -1, -0.33, 0.33, 1, 1.66};
  Double_t sublead_avgeta[6] = {eta2Dep[0]->GetMean(), eta2Dep[1]->GetMean(), eta2Dep[2]->GetMean(), eta2Dep[3]->GetMean(), eta2Dep[4]->GetMean(), eta2Dep[5]->GetMean()};
  Double_t sublead_netaErr[6] = {0,0,0,0,0,0};
  Double_t sublead_avgetaErr[6] = {eta2Dep[0]->GetMeanError(), eta2Dep[1]->GetMeanError(), eta2Dep[2]->GetMeanError(), eta2Dep[3]->GetMeanError(), eta2Dep[4]->GetMeanError(), eta2Dep[5]->GetMeanError()};

  Double_t mclead_avgeta[6] = {MCeta1Dep[0]->GetMean(), MCeta1Dep[1]->GetMean(), MCeta1Dep[2]->GetMean(), MCeta1Dep[3]->GetMean(), MCeta1Dep[4]->GetMean(), MCeta1Dep[5]->GetMean()};
  Double_t mclead_avgetaErr[6] = {MCeta1Dep[0]->GetMeanError(), MCeta1Dep[1]->GetMeanError(), MCeta1Dep[2]->GetMeanError(), MCeta1Dep[3]->GetMeanError(), MCeta1Dep[4]->GetMeanError(), MCeta1Dep[5]->GetMeanError()};

  Double_t mcsublead_avgeta[6] = {MCeta2Dep[0]->GetMean(), MCeta2Dep[1]->GetMean(), MCeta2Dep[2]->GetMean(), MCeta2Dep[3]->GetMean(), MCeta2Dep[4]->GetMean(), MCeta2Dep[5]->GetMean()};
  Double_t mcsublead_avgetaErr[6] = {MCeta2Dep[0]->GetMeanError(), MCeta2Dep[1]->GetMeanError(), MCeta2Dep[2]->GetMeanError(), MCeta2Dep[3]->GetMeanError(), MCeta2Dep[4]->GetMeanError(), MCeta2Dep[5]->GetMeanError()};

  TGraphErrors *ptr[4];
  Double_t lead_npt2[9] = {90,100,110,120,130,150,180,220,300};
  Double_t lead_avgpt2[9] = {pt1Dep[0]->GetMean(), pt1Dep[1]->GetMean(), pt1Dep[2]->GetMean(), pt1Dep[3]->GetMean(), pt1Dep[4]->GetMean(), pt1Dep[5]->GetMean(), pt1Dep[6]->GetMean(), pt1Dep[7]->GetMean(), pt1Dep[8]->GetMean()};
  Double_t lead_nptErr2[9] = {0,0,0,0,0,0,0,0,0};
  Double_t lead_avgptErr2[9] = {pt1Dep[0]->GetMeanError(), pt1Dep[1]->GetMeanError(), pt1Dep[2]->GetMeanError(), pt1Dep[3]->GetMeanError(), pt1Dep[4]->GetMeanError(), pt1Dep[5]->GetMeanError(), pt1Dep[6]->GetMeanError(), pt1Dep[7]->GetMeanError(), pt1Dep[8]->GetMeanError()};

  Double_t sublead_npt2[9] = {30,35,40,50,60,70,80,100,120};
  Double_t sublead_avgpt2[9] = {pt2Dep[0]->GetMean(), pt2Dep[1]->GetMean(), pt2Dep[2]->GetMean(), pt2Dep[3]->GetMean(), pt2Dep[4]->GetMean(), pt2Dep[5]->GetMean(), pt2Dep[6]->GetMean(), pt2Dep[7]->GetMean(), pt2Dep[8]->GetMean()};
  Double_t sublead_nptErr2[9] = {0,0,0,0,0,0,0,0,0};
  Double_t sublead_avgptErr2[9] = {pt2Dep[0]->GetMeanError(), pt2Dep[1]->GetMeanError(), pt2Dep[2]->GetMeanError(), pt2Dep[3]->GetMeanError(), pt2Dep[4]->GetMeanError(), pt2Dep[5]->GetMeanError(), pt2Dep[6]->GetMeanError(), pt2Dep[7]->GetMeanError(), pt2Dep[8]->GetMeanError()};

  Double_t mclead_avgpt2[9] = {MCpt1Dep[0]->GetMean(), MCpt1Dep[1]->GetMean(), MCpt1Dep[2]->GetMean(), MCpt1Dep[3]->GetMean(), MCpt1Dep[4]->GetMean(), MCpt1Dep[5]->GetMean(), MCpt1Dep[6]->GetMean(), MCpt1Dep[7]->GetMean(), MCpt1Dep[8]->GetMean()};
  Double_t mclead_avgptErr2[9] = {MCpt1Dep[0]->GetMeanError(), MCpt1Dep[1]->GetMeanError(), MCpt1Dep[2]->GetMeanError(), MCpt1Dep[3]->GetMeanError(), MCpt1Dep[4]->GetMeanError(), MCpt1Dep[5]->GetMeanError(), MCpt1Dep[6]->GetMeanError(), MCpt1Dep[7]->GetMeanError(), MCpt1Dep[8]->GetMeanError()};

  Double_t mcsublead_avgpt2[9] = {MCpt2Dep[0]->GetMean(), MCpt2Dep[1]->GetMean(), MCpt2Dep[2]->GetMean(), MCpt2Dep[3]->GetMean(), MCpt2Dep[4]->GetMean(), MCpt2Dep[5]->GetMean(), MCpt2Dep[6]->GetMean(), MCpt2Dep[7]->GetMean(), MCpt2Dep[8]->GetMean()};
  Double_t mcsublead_avgptErr2[9] = {MCpt2Dep[0]->GetMeanError(), MCpt2Dep[1]->GetMeanError(), MCpt2Dep[2]->GetMeanError(), MCpt2Dep[3]->GetMeanError(), MCpt2Dep[4]->GetMeanError(), MCpt2Dep[5]->GetMeanError(), MCpt2Dep[6]->GetMeanError(), MCpt2Dep[7]->GetMeanError(), MCpt2Dep[8]->GetMeanError()};

  TGraphErrors *DogaEtar[3];
  /* cout << endl << "*** BEGIN pPb ENTRIES ******" << endl << endl;
  //Double_t pPbEta[6] = {2.95567, 7.50071, 12.3948, 17.3344, 24.0483, 33.8478};
  Double_t pPbEta[8] = {1.18272,3.0409,5.0207,7.986,12.395,17.334,24.0483,36.3042};
  Double_t pPbavgeta[8] = {GetMu(pPbeta[0],1), GetMu(pPbeta[1],1), GetMu(pPbeta[2],1), GetMu(pPbeta[3],1), GetMu(pPbeta[4],1), GetMu(pPbeta[5],1), GetMu(pPbeta[6],1), GetMu(pPbeta[7],1)};
  Double_t pPbEtaErr[8] = {0,0,0,0,0,0,0,0};
  Double_t pPbavgetaErr[8] = {GetMu(pPbeta[0],2), GetMu(pPbeta[1],2), GetMu(pPbeta[2],2), GetMu(pPbeta[3],2), GetMu(pPbeta[4],2), GetMu(pPbeta[5],2), GetMu(pPbeta[6],2), GetMu(pPbeta[7],2)};

  cout << endl << "*** BEGIN PbPb ENTRIES ******" << endl << endl;
  Double_t PbPbEta[6] = {3.26724, 7.6717, 12.6661, 17.4677, 25.3719, 50.0559};
  Double_t PbPbavgeta[6] = {GetMu(PbPbeta[0],1), GetMu(PbPbeta[1],1), GetMu(PbPbeta[2],1), GetMu(PbPbeta[3],1), GetMu(PbPbeta[4],1), GetMu(PbPbeta[5],1)};
  Double_t PbPbEtaErr[6] = {0,0,0,0,0,0};
  Double_t PbPbavgetaErr[6] = {GetMu(PbPbeta[0],2), GetMu(PbPbeta[1],2), GetMu(PbPbeta[2],2), GetMu(PbPbeta[3],2), GetMu(PbPbeta[4],2), GetMu(PbPbeta[5],2)};

  cout << endl << "*** BEGIN MC ENTRIES ******" << endl << endl;
  //Double_t MCEta[6] = {2.79149, 7.3017, 12.3502, 17.2902, 23.755, 34.5008};
  Double_t MCEta[8] = {1.2529,2.9876,4.953,7.8815,12.3502,17.2902,23.755,34.5008};
  Double_t MCavgeta[8] = {GetMu(MCeta[0],1), GetMu(MCeta[1],1), GetMu(MCeta[2],1), GetMu(MCeta[3],1), GetMu(MCeta[4],1), GetMu(MCeta[5],1),GetMu(MCeta[6],1), GetMu(MCeta[7],1)};
  Double_t MCEtaErr[8] = {0,0,0,0,0,0,0,0};
  Double_t MCavgetaErr[8] = {GetMu(MCeta[0],2), GetMu(MCeta[1],2), GetMu(MCeta[2],2), GetMu(MCeta[3],2), GetMu(MCeta[4],2), GetMu(MCeta[5],2),GetMu(MCeta[6],2), GetMu(MCeta[7],2)};*/

  Double_t pPbEta[9] = {1.18272,3.0409,5.0207,7.986,12.395,17.334,24.0483,36.3042,74.2588}; //for hiHFplusEta4 binning
  //Double_t pPbEta[9] = {1.66038,3.14937,4.44253,6.36324,9.09223,12.0469,16.1132,24.4131,43.257}; //for (hiHFplus - hiHFplusEta4) binning
  Double_t pPbavgeta[9] = {pPbeta[0]->GetMean(), pPbeta[1]->GetMean(), pPbeta[2]->GetMean(), pPbeta[3]->GetMean(), pPbeta[4]->GetMean(), pPbeta[5]->GetMean(), pPbeta[6]->GetMean(), pPbeta[7]->GetMean(), pPbeta[8]->GetMean()};
  Double_t pPbEtaErr[9] = {0,0,0,0,0,0,0,0,0};
  Double_t pPbavgetaErr[9] = {pPbeta[0]->GetMeanError(), pPbeta[1]->GetMeanError(), pPbeta[2]->GetMeanError(), pPbeta[3]->GetMeanError(), pPbeta[4]->GetMeanError(), pPbeta[5]->GetMeanError(), pPbeta[6]->GetMeanError(), pPbeta[7]->GetMeanError(), pPbeta[8]->GetMeanError()};

  Double_t PbPbEta[6] = {3.26724, 7.6717, 12.6661, 17.4677, 25.3719, 50.0559};
  Double_t PbPbavgeta[6] = {PbPbeta[0]->GetMean(), PbPbeta[1]->GetMean(), PbPbeta[2]->GetMean(), PbPbeta[3]->GetMean(), PbPbeta[4]->GetMean(), PbPbeta[5]->GetMean()};
  Double_t PbPbEtaErr[6] = {0,0,0,0,0,0};
  Double_t PbPbavgetaErr[6] = {PbPbeta[0]->GetMeanError(), PbPbeta[1]->GetMeanError(), PbPbeta[2]->GetMeanError(), PbPbeta[3]->GetMeanError(), PbPbeta[4]->GetMeanError(), PbPbeta[5]->GetMeanError()};

  Double_t MCEta[8] = {1.2529,2.9876,4.953,7.8815,12.3502,17.2902,23.755,34.5008}; //for hiHFplusEta4 binning
  //Double_t MCEta[9] = {2.35827,3.55056,4.67142,6.46687,9.40546,12.8326,17.007,22.8541,27.185}; // for (hiHFplus - hiHFplusEta4) binning
  Double_t MCavgeta[9] = {MCeta[0]->GetMean(), MCeta[1]->GetMean(), MCeta[2]->GetMean(), MCeta[3]->GetMean(), MCeta[4]->GetMean(), MCeta[5]->GetMean(), MCeta[9]->GetMean(), MCeta[7]->GetMean(), MCeta[8]->GetMean()};
  Double_t MCEtaErr[9] = {0,0,0,0,0,0,0,0,0};
  Double_t MCavgetaErr[9] = {MCeta[0]->GetMeanError(), MCeta[1]->GetMeanError(), MCeta[2]->GetMeanError(), MCeta[3]->GetMeanError(), MCeta[4]->GetMeanError(), MCeta[5]->GetMeanError(), MCeta[6]->GetMeanError(), MCeta[7]->GetMeanError(), MCeta[8]->GetMeanError()};

  
  centr[0] = new TGraphErrors(6,lead_npt, lead_avgPt, lead_nptErr, lead_avgPtErr);
  centr[1] = new TGraphErrors(6,sublead_npt, sublead_avgPt, sublead_nptErr, sublead_avgPtErr);
  centr[2] = new TGraphErrors(6,lead_npt, mclead_avgPt, lead_nptErr, mclead_avgPtErr);
  centr[3] = new TGraphErrors(6,sublead_npt, mcsublead_avgPt, sublead_nptErr, mcsublead_avgPtErr);

  etar[0] = new TGraphErrors(6,lead_neta, lead_avgeta, lead_netaErr, lead_avgetaErr);
  etar[1] = new TGraphErrors(6,sublead_neta, sublead_avgeta, sublead_netaErr, sublead_avgetaErr);
  etar[2] = new TGraphErrors(6,lead_neta, mclead_avgeta, lead_netaErr, mclead_avgetaErr);
  etar[3] = new TGraphErrors(6,sublead_neta, mcsublead_avgeta, sublead_netaErr, mcsublead_avgetaErr);

  ptr[0] = new TGraphErrors(8,lead_npt2, lead_avgpt2, lead_nptErr2, lead_avgptErr2);
  ptr[1] = new TGraphErrors(8,sublead_npt2, sublead_avgpt2, sublead_nptErr2, sublead_avgptErr2);
  ptr[2] = new TGraphErrors(8,lead_npt2, mclead_avgpt2, lead_nptErr2, mclead_avgptErr2);
  ptr[3] = new TGraphErrors(8,sublead_npt2, mcsublead_avgpt2, sublead_nptErr2, mcsublead_avgptErr2);

  DogaEtar[0] = new TGraphErrors(8,pPbEta,pPbavgeta,pPbEtaErr,pPbavgetaErr);
  DogaEtar[1] = new TGraphErrors(6,PbPbEta,PbPbavgeta,PbPbEtaErr,PbPbavgetaErr);
  DogaEtar[2] = new TGraphErrors(8,MCEta,MCavgeta,MCEtaErr,MCavgetaErr);

  TCanvas *c5 = new TCanvas("c5","",600,600);
  c5->cd();
  TH1D *temphist = new TH1D("temphist","",1,0,60);
  temphist->SetMaximum(0.5);
  temphist->SetMinimum(-0.5);
  temphist->Draw();
  temphist->SetXTitle("E_{T}^{HFplus[#eta>4]}");
  temphist->SetYTitle("<((#eta_{1}+#eta_{2})/2)>");
  DogaEtar[1]->SetMarkerColor(4);
  DogaEtar[1]->SetLineColor(4);
  DogaEtar[1]->Draw("P,same");
  DogaEtar[2]->SetMarkerColor(2);
  DogaEtar[2]->SetLineColor(2);
  DogaEtar[2]->Draw("P,same");
  DogaEtar[0]->Draw("P,same");

  TCanvas *c2 = new TCanvas("c2","",800,500);
  c2->Divide(2,1);
  c2_1->cd();
  TH1D *tmp = new TH1D("tmp","",1,80,160);
  tmp->SetMaximum(0.76);
  tmp->SetMinimum(0.64);
  tmp->SetXTitle("p_{T,leading} threshold");
  tmp->SetYTitle("<p_{T,2}/p_{T,1}>");
  tmp->Draw();
  TLegend *mleg = new TLegend(0.15,0.78,0.99,0.91);
  mleg->AddEntry(centr[0], "pPb Data (2013) #sqrt{s}=5 TeV","pL");
  mleg->AddEntry(centr[2], "HIJING + PYTHIA (2013) #sqrt{s}=5 TeV","pL");
  mleg->SetBorderSize(0);
  mleg->SetFillColor(0);
  mleg->Draw();
  centr[0]->Draw("P,same");
  centr[2]->SetLineColor(2);
  centr[2]->SetMarkerColor(2);
  centr[2]->Draw("P,same");
  c2_2->cd();
  TH1D *tmp2 = new TH1D("tmp2","",1,10,70);
  tmp2->SetMaximum(0.76);
  tmp2->SetMinimum(0.64);
  tmp2->SetXTitle("p_{T,subleading} threshold");
  tmp2->SetYTitle("<p_{T,2}/p_{T,1}>");
  tmp2->Draw();
  t1 = new TLatex(40,0.73,"CMS Preliminary");
  t1->SetTextSize(0.04);
  t1->Draw();
  centr[1]->Draw("P,same");
  centr[3]->SetLineColor(2);
  centr[3]->SetMarkerColor(2);
  centr[3]->Draw("P,same");

  TCanvas *c3 = new TCanvas("c3","",800,500);
  c3->Divide(2,1);
  c3_1->cd();
  TH1D *tmp3 = new TH1D("tmp3","",1,-2,2);
  tmp3->SetMaximum(3);
  tmp3->SetMinimum(2.82);
  tmp3->SetXTitle("#eta_{leading}");
  tmp3->SetYTitle("<#Delta#phi>");
  tmp3->Draw();
  TLegend *mleg = new TLegend(0.15,0.78,0.99,0.91);
  mleg->AddEntry(centr[0], "pPb Data (2013) #sqrt{s}=5 TeV","pL");
  mleg->AddEntry(centr[2], "HIJING + PYTHIA (2013) #sqrt{s}=5 TeV","pL");
  mleg->SetBorderSize(0);
  mleg->SetFillColor(0);
  mleg->Draw();
  etar[0]->Draw("P,same");
  etar[2]->SetLineColor(2);
  etar[2]->SetMarkerColor(2);
  etar[2]->Draw("P,same");
  c3_2->cd();
  TH1D *tmp4 = new TH1D("tmp4","",1,-2,2);
  tmp4->SetMaximum(3);
  tmp4->SetMinimum(2.82);
  tmp4->SetXTitle("#eta_{subleading}");
  tmp4->SetYTitle("<#Delta#phi>");
  tmp4->Draw();
  t1 = new TLatex(0,3.1,"CMS Preliminary");
  t1->SetTextSize(0.04);
  t1->Draw();
  etar[1]->Draw("P,same");
  etar[3]->SetLineColor(2);
  etar[3]->SetMarkerColor(2);
  etar[3]->Draw("P,same");

  TCanvas *c4 = new TCanvas("c4","",800,500);
  c4->Divide(2,1);
  c4_1->cd();
  TH1D *tmp5 = new TH1D("tmp5","",1,0,310);
  tmp5->SetMaximum(3);
  tmp5->SetMinimum(2.82);
  tmp5->SetXTitle("#p_{T,leading}");
  tmp5->SetYTitle("<#Delta#phi>");
  tmp5->Draw();
  TLegend *mleg = new TLegend(0.15,0.78,0.99,0.91);
  mleg->AddEntry(centr[0], "pPb Data (2013) #sqrt{s}=5 TeV","pL");
  mleg->AddEntry(centr[2], "HIJING + PYTHIA (2013) #sqrt{s}=5 TeV","pL");
  mleg->SetBorderSize(0);
  mleg->SetFillColor(0);
  mleg->Draw();
  ptr[0]->Draw("P,same");
  ptr[2]->SetLineColor(2);
  ptr[2]->SetMarkerColor(2);
  ptr[2]->Draw("P,same");
  c4_2->cd();
  TH1D *tmp6 = new TH1D("tmp6","",1,0,130);
  tmp6->SetMaximum(3);
  tmp6->SetMinimum(2.82);
  tmp6->SetXTitle("#p_{T,subleading}");
  tmp6->SetYTitle("<#Delta#phi>");
  tmp6->Draw();
  t1 = new TLatex(0,3.1,"CMS Preliminary");
  t1->SetTextSize(0.04);
  t1->Draw();
  ptr[1]->Draw("P,same");
  ptr[3]->SetLineColor(2);
  ptr[3]->SetMarkerColor(2);
  ptr[3]->Draw("P,same");

}
