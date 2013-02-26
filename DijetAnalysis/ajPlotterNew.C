#include "commonUtility.h"

#include <iostream>
#include <string>
#include <sstream>

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TROOT.h"

const double PI=3.1415926;

double findDelPhiAngle(TH1D *input, int parorErr){
  
  TF1 *fitter = new TF1("fitter","[1]*exp((x-3.1415)/[0])/((1-exp(-3.1415/[0]))*[0])",0,4);
  fitter->SetParameters(1.0/input->GetMaximum(),0.2);
  fitter->SetParLimits(0,0.15,0.35);
  input->Fit("fitter","qN0","",2.0944,3.1415);
  if(parorErr==1){
    return fitter->GetParameter(0);
  }
  else if(parorErr==2){
    return fitter->GetParError(0);
  }
  else return 0;
}

void ajPlotterNew(int p1=120, int p2=30, bool write_output=0){

  std::string outputname = "hist_output_etaLT3_akPu5PF.root";
  //double multbins[4] = {0,47,66,90}; //(~equal integration)
  //double multbins[6] = {0,0,10,15,20,30}; //hiHFplusEta4 binning
  double multbins[7] = {0,0,20,25,30,40,90}; //hiHFsumEta4 binning
  //double multbins[6] = {0,60,90,110,150,180}; //mult binning
  double phitop=2, phibot=3;
  double deltaPhiCut = (phitop*PI/phibot);
  std::string jetcoll = "akPu3Calo";

  //std::string infile = "LowPtSample_v71_akPu5PF.root"; //lowPt Sample
  std::string infile = "FullForest_v77_etaLT3_akPu3Calo.root"; //updated JECs
  TFile *f0 = new TFile(infile.c_str(),"OLD");
  if(!f0){ cout << "You don't have this jet collection yet!!" << endl; exit(0);}
  TFile *f1 = new TFile("PbPb_ReReco_Full_etaLT3_akPu3PF.root","OLD");
  TTree *ntree = (TTree*)f1->Get("dijetTree");
  TTree *dijetTree = (TTree*)f0->Get("dijetTree");

  TFile *f2 = new TFile("YaxianPPData_etaLT3_akPu3PF.root","OLD");
  TTree *ppTree = (TTree*)f2->Get("dijetTree");

  //TFile *fMC = new TFile("mix_hydjet.root");
  //TTree *mcTree = (TTree*)fMC->Get("ntdijet");
  //TTree *evtTree = (TTree*)fMC->Get("ntevt");
  //TFile *fWeight = new TFile("weights_hydjet.root");
  //TTree *wTree = (TTree*)fWeight->Get("ntw");

  //mcTree->AddFriend(wTree);
  //mcTree->AddFriend(evtTree);

  TFile *fMC = new TFile("PythiaMIT_out_etaLT3_akPu3Calo.root");
  TTree *mcTree = (TTree*)fMC->Get("dijetTree");
  
  //TCanvas *c1 = new TCanvas("c1","",1200,800);
  //c1->cd();

  TH1D *mult0[7], *delphi0[7], *MC[6], *MCdphi[6], *mult[9], *multbg[9], *delphi[9];
  char* histoname = new char[40];
  for(int i=0; i<7; i++){
    sprintf(histoname,"%s%d%s","mult",i,"_0");
    mult0[i] = new TH1D(histoname,"",10,0,1);
    mult0[i]->Sumw2();
    sprintf(histoname,"%s%d%s","delphi",i,"_0");
    delphi0[i] = new TH1D(histoname,"",30,0,PI);
    delphi0[i]->Sumw2();
  }
  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d%s","MC",i,"_0");
    MC[i] = new TH1D(histoname,"",10,0,1);
    MC[i]->Sumw2();
    sprintf(histoname,"%s%d%s","MCdphi",i,"_0");
    MCdphi[i] = new TH1D(histoname,"",30,0,PI);
    MCdphi[i]->Sumw2();
  }
  for(int i=0; i<9; i++){
    sprintf(histoname,"%s%d","mult",i*10+10);
    mult[i] = new TH1D(histoname,"",10,0,1);
    mult[i]->Sumw2();
    sprintf(histoname,"%s%d","multbg",i*10+11);
    multbg[i] = new TH1D(histoname,"",10,0,1);
    multbg[i]->Sumw2();
    sprintf(histoname,"%s%d","delphi",i*10+10);
    delphi[i] = new TH1D(histoname,"",30,0,PI);
    delphi[i]->Sumw2();
  }

  TH1D *pp[6];
  TH1D *ppdphi[6];
  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d","pp_",i);
    pp[i] = new TH1D(histoname,"",10,0,1);
    pp[i]->Sumw2();
    sprintf(histoname,"%s%d","ppdphi_",i);
    ppdphi[i] = new TH1D(histoname,"",30,0,PI);
    ppdphi[i]->Sumw2();
  }

  TH1D *mult_etapos[6];
  TH1D *mult_etaneg[6];
  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d","mult_etapos",i);
    mult_etapos[i] = new TH1D(histoname,"",10,0,1);
    sprintf(histoname,"%s%d","mult_etaneg",i);
    mult_etaneg[i] = new TH1D(histoname,"",10,0,1);
    mult_etapos[i]->Sumw2();
    mult_etaneg[i]->Sumw2();
    mult_etaneg[i]->SetLineColor(2);
    mult_etaneg[i]->SetMarkerColor(2);
  }

  TH1D *vz0 = new TH1D("vz0","",10,0,1);
  TH1D *vz1 = new TH1D("vz1","",10,0,1);
  TH1D *vz2 = new TH1D("vz2","",10,0,1);
  vz0->Sumw2();
  vz1->Sumw2();
  vz2->Sumw2();

  TH1D *avgPt[6], *PbavgPt[6];

  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d","avgPt",i);
    avgPt[i] = new TH1D(histoname,"",10,0,PI);
    avgPt[i]->Sumw2();
    sprintf(histoname,"%s%d","PbavgPt",i);
    PbavgPt[i] = new TH1D(histoname,"",10,0,PI);
    PbavgPt[i]->Sumw2();
    PbavgPt[i]->SetMarkerColor(4);
    PbavgPt[i]->SetLineColor(4);
    PbavgPt[i]->SetMarkerStyle(25);
  }

  TH1D *multavg[6];
  char* title = new char[20];
  for(int i=0; i<6; i++){
    sprintf(title,"%s%d","multavg_",i);
    multavg[i] = new TH1D(title,"",200,0,1);
    multavg[i]->SetMarkerStyle(26);
    multavg[i]->Sumw2();
  }

  stringstream s1, s2, m1, m2, m3, m4, m5, m6, delphicut, ptop, pbot;
  s1 << p1;
  s2 << p2;
  m1 << multbins[0];
  m2 << multbins[1];
  m3 << multbins[2];
  m4 << multbins[3];
  m5 << multbins[4];
  m6 << multbins[5];
  delphicut << deltaPhiCut;
  ptop << phitop;
  pbot << phibot;
  string p1Str = s1.str();
  string p2Str = s2.str();
  string m1Str = m1.str();
  string m2Str = m2.str();
  string m3Str = m3.str();
  string m4Str = m4.str();
  string m5Str = m5.str();
  string m6Str = m6.str();
  string dphiStr = delphicut.str();

  //cuts for pPb Data
  std::string cut0_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";
  std::string cut1_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4<" + m3Str + " && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";
  std::string cut2_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+m3Str+" && hiHFplusEta4+hiHFminusEta4<"+m4Str+" && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";
  std::string cut3_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=" + m4Str +" && hiHFplusEta4+hiHFminusEta4<" + m5Str + " && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";
  std::string cut4_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+m5Str+" && hiHFplusEta4+hiHFminusEta4<"+m6Str+" && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";
  std::string cut5_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+m6Str+" && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";
  std::string cut6_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=40 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt2<30";

  //cuts for pp Data
  std::string cutpp0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutpp1 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutpp2 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutpp3 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutpp4 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutpp5 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;

  //cuts for vz dependence study
  std::string cutvz0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=" + m6Str +" && abs(zvtx)<20 && abs(zvtx)>3 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutvz1 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=" + m6Str +" && abs(zvtx)<20 && abs(zvtx)>5 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutvz2 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=" + m6Str +" && abs(zvtx)<20 && abs(zvtx)>10 && acos(cos(phi1-phi2)) > "+dphiStr;
  
  //cuts for Hijing + Pythia MC
  std::string hMCcut0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat > 30 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt2<30)";
  std::string hMCcut1 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat > 30 &&rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4<"+m3Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt2<30)";
  std::string hMCcut2 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat > 30 &&rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m3Str+" && hiHFplusEta4+hiHFminusEta4<"+m4Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt2<30)";
  std::string hMCcut3 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat > 30 &&rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m4Str+" && hiHFplusEta4+hiHFminusEta4<"+m5Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt2<30)";
  std::string hMCcut4 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat > 30 &&rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m5Str+" && hiHFplusEta4+hiHFminusEta4<"+m6Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt2<30)";
  std::string hMCcut5 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat > 30 &&rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m6Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt2<30)";
  
  //cuts for PbPb data
  std::string cut90 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut80 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4<" + m3Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut70 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m3Str +" && hiHFplusEta4+hiHFminusEta4<" + m4Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut60 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m4Str +" && hiHFplusEta4+hiHFminusEta4<" + m5Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut50 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m5Str +" && hiHFplusEta4+hiHFminusEta4<" + m6Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut40 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m6Str +" && hiHFplusEta4+hiHFminusEta4< 90 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut30 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=0 && hiHFplusEta4+hiHFminusEta4<25 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut20 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=25 && hiHFplusEta4+hiHFminusEta4<50 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";
  std::string cut10 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=50 && hiHFplusEta4+hiHFminusEta4<90 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > "+dphiStr;// && pt2<30";

  std::string cut91 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";
  std::string cut81 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4<" + m3Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut71 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m3Str +" && hiHFplusEta4+hiHFminusEta4<" + m4Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut61 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m4Str +" && hiHFplusEta4+hiHFminusEta4<" + m5Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut51 = "1.0*pt1>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m5Str +" && hiHFplusEta4+hiHFminusEta4<" + m6Str + " && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut41 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>="+ m6Str +" && hiHFplusEta4+hiHFminusEta4< 90 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut31 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=0 && hiHFplusEta4+hiHFminusEta4<25 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut21 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=25 && hiHFplusEta4+hiHFminusEta4<50 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";
  std::string cut11 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && hiHFplusEta4+hiHFminusEta4>=50 && hiHFplusEta4+hiHFminusEta4<90 && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) < 1.0472";// && pt2<30";

  //cuts for phi correlations for pPb data
  std::string phicut0_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus";
  std::string phicut1_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus && hiHFplusEta4+hiHFminusEta4<"+m3Str;
  std::string phicut2_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus && hiHFplusEta4+hiHFminusEta4>="+m3Str+" && hiHFplusEta4+hiHFminusEta4<"+m4Str;
  std::string phicut3_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus && hiHFplusEta4+hiHFminusEta4>="+m4Str+" && hiHFplusEta4+hiHFminusEta4<"+m5Str;
  std::string phicut4_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus && hiHFplusEta4+hiHFminusEta4>="+m5Str+" && hiHFplusEta4+hiHFminusEta4<"+m6Str;
  std::string phicut5_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus && hiHFplusEta4+hiHFminusEta4>="+m6Str;
  std::string phicut6_0 = "pt1*1.0>"+ p1Str + " && pt2*1.0>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGplus && hiHFplusEta4+hiHFminusEta4>=40";

  //cuts for phi correlations for pp data
  std::string ppphicut0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";
  std::string ppphicut1 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";
  std::string ppphicut2 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";
  std::string ppphicut3 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";
  std::string ppphicut4 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";
  std::string ppphicut5 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";

  //cuts for phi correlations for PbPb data
  std::string phicut90 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15";
  std::string phicut80 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4<"+m3Str;
  std::string phicut70 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m3Str+" && hiHFplusEta4+hiHFminusEta4<"+m4Str;
  std::string phicut60 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m4Str+" && hiHFplusEta4+hiHFminusEta4<"+m5Str;
  std::string phicut50 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m5Str+" && hiHFplusEta4+hiHFminusEta4<"+m6Str;
  std::string phicut40 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m6Str+" && hiHFplusEta4+hiHFminusEta4< 90";
  std::string phicut30 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>=0 && hiHFplusEta4+hiHFminusEta4<25";
  std::string phicut20 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>=25 && hiHFplusEta4+hiHFminusEta4<50";
  std::string phicut10 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>=50 && hiHFplusEta4+hiHFminusEta4<90";

  //phi correlations for MC
  std::string hMCphicut0_0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat>30 && rawPt1>15 && rawPt2>15)";
  std::string hMCphicut1_0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat>30 && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4<"+m3Str+")";
  std::string hMCphicut2_0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat>30 && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m3Str+" && hiHFplusEta4+hiHFminusEta4<"+m4Str+")";
  std::string hMCphicut3_0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat>30 && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m4Str+" && hiHFplusEta4+hiHFminusEta4<"+m5Str+")";
  std::string hMCphicut4_0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat>30 && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m5Str+" && hiHFplusEta4+hiHFminusEta4<"+m6Str+")";
  std::string hMCphicut5_0 = "(weight/MCpthatEntries)*(pt1>"+ p1Str + " && pt2>" + p2Str + " && pthat>30 && rawPt1>15 && rawPt2>15 && hiHFplusEta4+hiHFminusEta4>="+m6Str+")";

  int nJets[6][10];
  double ptRatio[6][10];
  double ptRatioErr[6][10];
  for(int i=0; i<6; i++){
    for(int j=0; j<10; j++){
      ptRatio[i][j] = 0;
      nJets[i][j] = 0;
      ptRatioErr[i][j] = 0;
    }
  }
  double pt1,pt2,phi1,phi2,eta1,eta2,hiHF,hiHFminus;
  int tracks;
  bool PU;
  dijetTree->SetBranchAddress("pt1",&pt1);
  dijetTree->SetBranchAddress("pt2",&pt2);
  dijetTree->SetBranchAddress("phi1",&phi1);
  dijetTree->SetBranchAddress("phi2",&phi2);
  dijetTree->SetBranchAddress("eta1",&eta1);
  dijetTree->SetBranchAddress("eta2",&eta2);
  dijetTree->SetBranchAddress("tracks",&tracks);
  dijetTree->SetBranchAddress("hiHFplusEta4",&hiHF);
  dijetTree->SetBranchAddress("hiHFminusEta4",&hiHFminus);
  dijetTree->SetBranchAddress("PUFilterGplus",&PU);
  for(int i=0; i<dijetTree->GetEntries(); i++){
    dijetTree->GetEntry(i);
    if(pt1 >= p1 && pt2 >= p2 && PU){
      int j=0;
      while((hiHF+hiHFminus)>multbins[j+1] && j<5) j++;
      int k=1;
      while(acos(cos(phi1-phi2))>(k*PI/10.)) k++;
      if(j>5 || k-1>9){ cout << "warning! J: " << j << " k: " << k-1 << endl; cout << "dphi: " << acos(cos(phi1-phi2)) << endl; }
      ptRatio[j][k-1] += pt2/pt1;
      nJets[j][k-1]++;

      if(acos(cos(phi1-phi2)) > deltaPhiCut){ 
	if(eta2>0){
	  mult_etapos[j]->Fill(pt2/pt1);
	}
	if(eta2<0){
	  mult_etaneg[j]->Fill(pt2/pt1);
	}
      }
    }
  }
  for(int i=0; i<6; i++){
    for(int j=0; j<10; j++){
      ptRatioErr[i][j] = TMath::Sqrt(ptRatio[i][j]);
      ptRatioErr[i][j] = ptRatioErr[i][j]/(double)nJets[i][j];
      ptRatio[i][j] = ptRatio[i][j]/(double)nJets[i][j];
      avgPt[i]->SetBinContent(j+1, ptRatio[i][j]);
      avgPt[i]->SetBinError(j+1,ptRatioErr[i][j]);
    }
    //avgPt[i]->Scale(1./avgPt[i]->Integral());
    avgPt[i]->SetXTitle("#Delta#phi");
    avgPt[i]->SetYTitle("<p_{T,2}/p_{T,1}>");
    avgPt[i]->SetMaximum(1.3);
    avgPt[i]->SetMinimum(0);
  }

  int PbnJets[6][10];
  double PbptRatio[6][10];
  double PbptRatioErr[6][10];
  for(int i=0; i<6; i++){
    for(int j=0; j<10; j++){
      PbptRatio[i][j] = 0;
      PbnJets[i][j] = 0;
      PbptRatioErr[i][j] = 0;
    }
  }
  Double_t Pbpt1,Pbpt2,Pbphi1,Pbphi2,Pbtracks,Pbminus;
  ntree->SetBranchAddress("pt1",&Pbpt1);
  ntree->SetBranchAddress("pt2",&Pbpt2);
  ntree->SetBranchAddress("phi1",&Pbphi1);
  ntree->SetBranchAddress("phi2",&Pbphi2);
  ntree->SetBranchAddress("hiHFplusEta4",&Pbtracks);
  ntree->SetBranchAddress("hiHFminusEta4",&Pbminus);
  for(int i=0; i<ntree->GetEntries(); i++){
    ntree->GetEntry(i);
    if(Pbpt1 >= p1 && Pbpt2 >= p2){
      int j=0;
      while((Pbtracks+Pbminus)>multbins[j+1] && j<5) j++;
      int k=1;
      while(acos(cos(Pbphi1-Pbphi2))>(k*PI/10.)) k++;
      PbptRatio[j][k-1] += (Pbpt2/Pbpt1);
      PbnJets[j][k-1]++;
    }
  }
  for(int i=0; i<6; i++){
    for(int j=0; j<10; j++){
      PbptRatioErr[i][j] = TMath::Sqrt(PbptRatio[i][j]);
      if(PbnJets[i][j] != 0){
	PbptRatioErr[i][j] = PbptRatioErr[i][j]/(double)PbnJets[i][j];
	PbptRatio[i][j] = PbptRatio[i][j]/(double)PbnJets[i][j];
      }
      else{
	PbptRatioErr[i][j] = 0;
	PbptRatio[i][j] = 0;
      }
      PbavgPt[i]->SetBinContent(j+1,PbptRatio[i][j]);
      PbavgPt[i]->SetBinError(j+1, PbptRatioErr[i][j]);
    }
    mult_etapos[i]->Scale(1./mult_etapos[i]->Integral());
    mult_etaneg[i]->Scale(1./mult_etaneg[i]->Integral());
    mult_etapos[i]->SetMaximum(0.3);
    mult_etapos[i]->SetMinimum(0);
  }
      
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi0_0",phicut0_0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi1_0",phicut1_0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi2_0",phicut2_0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi3_0",phicut3_0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi4_0",phicut4_0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi5_0",phicut5_0.c_str());
  dijetTree->Draw("acos(cos(phi1-phi2))>>delphi6_0",phicut6_0.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi90",phicut90.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi80",phicut80.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi70",phicut70.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi60",phicut60.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi50",phicut50.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi40",phicut40.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi30",phicut30.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi20",phicut20.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi10",phicut10.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi0_0",hMCphicut0_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi1_0",hMCphicut1_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi2_0",hMCphicut2_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi3_0",hMCphicut3_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi4_0",hMCphicut4_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi5_0",hMCphicut5_0.c_str());
  if(jetcoll=="akPu3PF"){
    ppTree->Draw("(acos(cos(phi1-phi2)))>>ppdphi_0",ppphicut0.c_str());
    ppTree->Draw("(acos(cos(phi1-phi2)))>>ppdphi_1",ppphicut1.c_str());
    ppTree->Draw("(acos(cos(phi1-phi2)))>>ppdphi_2",ppphicut2.c_str());
    ppTree->Draw("(acos(cos(phi1-phi2)))>>ppdphi_3",ppphicut3.c_str());
    ppTree->Draw("(acos(cos(phi1-phi2)))>>ppdphi_4",ppphicut4.c_str());
    ppTree->Draw("(acos(cos(phi1-phi2)))>>ppdphi_5",ppphicut5.c_str());
  }
  for(int i=0; i<6; i++){
    ppdphi[i]->Scale(1./ppdphi[i]->Integral());
    ppdphi[i]->SetMarkerColor(4);
    ppdphi[i]->SetLineColor(4);
    ppdphi[i]->SetMarkerStyle(24);
  }
  for(int i=0; i<6; i++){
    MCdphi[i]->Scale(1./MCdphi[i]->Integral());
    MCdphi[i]->SetFillColor(2);
    MCdphi[i]->SetMarkerColor(2);
    MCdphi[i]->SetFillStyle(3004);
    MCdphi[i]->SetLineColor(2);
  }
  for(int i=0; i<7; i++){
    delphi0[i]->Scale(1./delphi0[i]->Integral());
    delphi0[i]->SetYTitle("Event Fraction");
    delphi0[i]->SetMaximum(3);
  }
  for(int i=0; i<9; i++){
    delphi[i]->Scale(1./delphi[i]->Integral());
    delphi[i]->SetMarkerColor(kGreen+1);
    delphi[i]->SetMarkerStyle(25);
    delphi[i]->SetLineColor(kGreen+1);
  }
  
  ntree->Draw("pt2/pt1>>mult90",cut90.c_str());
  ntree->Draw("pt2/pt1>>mult80",cut80.c_str());
  ntree->Draw("pt2/pt1>>mult70",cut70.c_str());
  ntree->Draw("pt2/pt1>>mult60",cut60.c_str());
  ntree->Draw("pt2/pt1>>mult50",cut50.c_str());
  ntree->Draw("pt2/pt1>>mult40",cut40.c_str());
  ntree->Draw("pt2/pt1>>mult30",cut30.c_str());
  ntree->Draw("pt2/pt1>>mult20",cut20.c_str());
  ntree->Draw("pt2/pt1>>mult10",cut10.c_str());
  ntree->Draw("pt2/pt1>>mult91",cut91.c_str());
  ntree->Draw("pt2/pt1>>mult81",cut81.c_str());
  ntree->Draw("pt2/pt1>>mult71",cut71.c_str());
  ntree->Draw("pt2/pt1>>mult61",cut61.c_str());
  ntree->Draw("pt2/pt1>>mult51",cut51.c_str());
  ntree->Draw("pt2/pt1>>mult41",cut41.c_str());
  ntree->Draw("pt2/pt1>>mult31",cut31.c_str());
  ntree->Draw("pt2/pt1>>mult21",cut21.c_str());
  ntree->Draw("pt2/pt1>>mult11",cut11.c_str());
  mcTree->Draw("pt2/pt1>>MC0_0",hMCcut0.c_str());
  mcTree->Draw("pt2/pt1>>MC1_0",hMCcut1.c_str());
  mcTree->Draw("pt2/pt1>>MC2_0",hMCcut2.c_str());
  mcTree->Draw("pt2/pt1>>MC3_0",hMCcut3.c_str());
  mcTree->Draw("pt2/pt1>>MC4_0",hMCcut4.c_str());
  mcTree->Draw("pt2/pt1>>MC5_0",hMCcut5.c_str());
  dijetTree->Draw("pt2/pt1>>mult0_0",cut0_0.c_str());
  dijetTree->Draw("pt2/pt1>>mult1_0",cut1_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult2_0",cut2_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult3_0",cut3_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult4_0",cut4_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult5_0",cut5_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult6_0",cut6_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>vz0",cutvz0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>vz1",cutvz1.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>vz2",cutvz2.c_str(),"same");
  //if(jetcoll=="akPu3PF"){
    ppTree->Draw("pt2/pt1>>pp_0",cutpp0.c_str(),"same");
    ppTree->Draw("pt2/pt1>>pp_1",cutpp1.c_str(),"same");
    ppTree->Draw("pt2/pt1>>pp_2",cutpp2.c_str(),"same");
    ppTree->Draw("pt2/pt1>>pp_3",cutpp3.c_str(),"same");
    ppTree->Draw("pt2/pt1>>pp_4",cutpp4.c_str(),"same");
    ppTree->Draw("pt2/pt1>>pp_5",cutpp5.c_str(),"same");
    //}
  for(int i=0; i<6; i++){
    pp[i]->Scale(1./pp[i]->Integral());
    pp[i]->SetMarkerColor(4);
    pp[i]->SetLineColor(4);
    pp[i]->SetMarkerStyle(24);
    MC[i]->SetFillColor(2);
    MC[i]->SetMarkerColor(2);
    MC[i]->SetLineColor(2);
    MC[i]->SetFillStyle(3004);
    MC[i]->Scale(1./MC[i]->Integral());
  }
  for(int i=0; i<9; i++){
    mult[i]->Scale(1./mult[i]->Integral());
    mult[i]->Add(multbg[i],-1);
    mult[i]->SetMarkerColor(kGreen+1);
    mult[i]->SetMarkerStyle(25);
    mult[i]->SetLineColor(kGreen+1);
  }
  std::string histXtitle("p_{T,2}/p_{T,1}");
  std::string histYtitle("Event Fraction");
  for(int i=0; i<7; i++){
    mult0[i]->Scale(1./mult0[i]->Integral());
    mult0[i]->SetXTitle(histXtitle.c_str());
    mult0[i]->SetYTitle(histYtitle.c_str());
    mult0[i]->SetAxisRange(0,0.30,"Y");
    mult0[i]->SetMaximum(0.30);

  }

  TGraphErrors* gr[6];
  Double_t avg0[6]  = {mult0[0]->GetMean(), mult0[1]->GetMean(), mult0[2]->GetMean(), mult0[3]->GetMean(), mult0[4]->GetMean(), mult0[5]->GetMean()};
  Double_t avg1[6]  = {0.012, 0.012, 0.012, 0.012, 0.012, 0.012};
  Double_t avg2[6]  = {mult0[0]->GetMeanError(), mult0[1]->GetMeanError(), mult0[2]->GetMeanError(), mult0[3]->GetMeanError(), mult0[4]->GetMeanError(), mult[5]->GetMeanError()};
  Double_t avg3[6]  = {0,0,0,0,0,0};
  for(int i=0; i<6; i++){
    gr[i] = new TGraphErrors(1,(avg0+i),(avg1+i),(avg2+i),(avg3+i));
    gr[i]->SetMarkerColor(1);
    gr[i]->SetLineColor(1);
    gr[i]->SetMarkerStyle(23);
  }

  Double_t Pbavg1[8]  = {0.012, 0.012, 0.012, 0.012, 0.012, 0.012, 0.012, 0.012};
  Double_t Pbavg3[8]  = {0,0,0,0,0,0,0,0};
  Double_t Pbavg0[8] = {mult[8]->GetMean(), mult[7]->GetMean(), mult[6]->GetMean(), mult[5]->GetMean(), mult[4]->GetMean(), mult[3]->GetMean(), mult[2]->GetMean(), mult[1]->GetMean()};
  Double_t Pbavg2[8] = {mult[8]->GetMeanError(), mult[7]->GetMeanError(), mult[6]->GetMeanError(), mult[5]->GetMeanError(), mult[4]->GetMeanError(), mult[3]->GetMeanError(), mult[2]->GetMeanError(), mult[1]->GetMeanError()};
  TGraphErrors* Pbgr[8];
  for(int i=0; i<6; i++){
    Pbgr[i] = new TGraphErrors(1,(Pbavg0+i),(Pbavg1+i),(Pbavg2+i),(Pbavg3+i));
    Pbgr[i]->SetMarkerColor(kGreen+1);
    Pbgr[i]->SetLineColor(kGreen+1);
    Pbgr[i]->SetMarkerStyle(23);
  }

  Double_t MCavg0[6] = {MC[0]->GetMean(), MC[1]->GetMean(), MC[2]->GetMean(), MC[3]->GetMean(), MC[4]->GetMean(), MC[5]->GetMean()};
  Double_t MCavg2[6] = {MC[0]->GetMeanError(), MC[1]->GetMeanError(), MC[2]->GetMeanError(), MC[3]->GetMeanError(), MC[4]->GetMeanError(), MC[5]->GetMeanError()};
  TGraphErrors* MCgr[6];
  for(int i=0; i<6; i++){
    MCgr[i] = new TGraphErrors(1,(MCavg0+i),(avg1+i),(MCavg2+i),(avg3+i));
    MCgr[i]->SetMarkerColor(2);
    MCgr[i]->SetLineColor(2);
    MCgr[i]->SetMarkerStyle(23);
  }
    
  std::string mult0_0name = std::string("X (") + p1Str + "/" + p2Str + "), p+Pb, #sqrt{s}= 5 TeV, tracks<"+m2Str;
  std::string mult1_0name = std::string("X (")+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, "+m2Str+"<tracks<"+m3Str;
  std::string mult2_0name = std::string("X (")+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, "+m3Str+"<tracks<"+m4Str;
  std::string mult3_0name = std::string("X (")+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, "+m4Str+"<tracks<"+m5Str;
  std::string mult4_0name = std::string("X (")+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, "+m5Str+"<tracks<"+m6Str;
  std::string mult5_0name = std::string("X (")+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, tracks>"+m6Str;
  
  std::string mult3name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 70-100%";
  std::string mult5name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 50-70%";
  std::string mult7name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 0-20%";

  std::string mult0_1name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 90-100%";
  std::string mult1_1name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 80-90%";
  std::string mult2_1name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 70-80%";
  std::string mult3_1name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 60-70%";
  std::string mult4_1name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 50-60%";
  std::string mult5_1name = std::string("X (") + p1Str + "/" + p2Str + "), Pb+Pb #sqrt{s} = 2.76 TeV, 40-50%";
  
  TLatex* plum = new TLatex(0.1,0.22,"pPb #int L dt=17.3 nb^{-1}");
  plum->SetTextSize(0.04);
  TLatex* PbLum = new TLatex(0.1,0.19,"PbPb #int L dt=150 #mub^{-1}");
  PbLum->SetTextSize(0.04);
  std::string ptcutname = std::string("p_{T,1}>")+p1Str+" GeV & p_{T,2}>"+p2Str+" GeV";
  TLatex *JetPtCut = new TLatex(0.1,0.22,ptcutname.c_str());
  JetPtCut->SetTextSize(0.04);
  std::string phicutname = std::string("#Delta#phi_{1,2} > (")+ptop.str()+"#pi/"+pbot.str()+")";
  TLatex *DeltaPhiCut = new TLatex(0.1,0.19,phicutname.c_str());
  DeltaPhiCut->SetTextSize(0.04);
  std::string jetcollName = jetcoll+ " Jets in pPb";
  TLatex* leg4 = new TLatex(0.1,0.19,jetcollName.c_str());
  leg4->SetTextSize(0.035);
  TLatex* leg5 = new TLatex(0.1,0.17,"akPu3PF Jets in PbPb");
  leg5->SetTextSize(0.035);

  TCanvas *c1 = new TCanvas("c10","",1200,800);
  makeMultiPanelCanvas(c1,3,2,0.,0.,0.2,0.2,0.05);
  std::string m0s=std::string("Inclusive E_{T}^{|#eta|<4}");
  std::string m1s=std::string("E_{T}^{|#eta|<4}<"+m3Str);      
  std::string m2s=std::string(m3Str+"#leqE_{T}^{|#eta|<4}<"+m4Str);
  std::string m3s=std::string(m4Str+"#leqE_{T}^{|#eta|<4}<"+m5Str);
  std::string m4s=std::string(m5Str+"#leqE_{T}^{|#eta|<4}<"+m6Str);
  std::string m5s=std::string("E_{T}^{|#eta|<4} >"+m6Str);
  TLatex* legm0 = new TLatex(0.1,0.22,m0s.c_str());
  TLatex* legm1 = new TLatex(0.1,0.25,m1s.c_str());
  TLatex* legm2 = new TLatex(0.1,0.25,m2s.c_str());
  TLatex* legm3 = new TLatex(0.1,0.25,m3s.c_str());
  TLatex* legm4 = new TLatex(0.1,0.25,m4s.c_str());
  TLatex* legm5 = new TLatex(0.1,0.25,m5s.c_str());
  TLatex* t1 = new TLatex(0.1,0.27,"CMS Preliminary");
  for(int i=0; i<6; i++){
    c1->cd(i+1);
    mult0[i]->SetXTitle(histXtitle.c_str());
    mult0[i]->SetYTitle(histYtitle.c_str());
    mult0[i]->Draw();
    MC[i]->Draw("hist,e,same");
    gr[i]->Draw("P,same");
    //Pbgr[i]->Draw("P,same");
    MCgr[i]->Draw("P,same");
    // mult[8-i]->Draw("same");
    mult0[i]->Draw("same");
    if(i==0){
      // pp[i]->Draw("same");
      TLegend *leg = new TLegend(0.2,0.77,0.80,0.91);
      leg->AddEntry(mult0[0],"2013 pPb Data, #sqrt{s}=5 TeV");
      leg->AddEntry(MC[0],"2013 PYTHIA+HIJING pPb MC, #sqrt{s}=5.02 TeV");
      //leg->AddEntry(mult[8],"2011 PbPb Data, #sqrt{s}=2.76 TeV");
      //leg->AddEntry(pp[0], "2011 pp Data, #sqrt{s}=2.76 TeV");
      leg->SetBorderSize(0);
      leg->SetFillStyle(0);
      leg->Draw();
      leg4->Draw();
      //leg5->Draw();
      legm0->Draw();
    }
    if(i==1){
      legm1->Draw();
      t1->SetTextSize(0.045);
      t1->Draw();
      plum->Draw();
      //PbLum->Draw();
    }
    if(i==2){
      legm2->Draw();
      JetPtCut->Draw();
      DeltaPhiCut->Draw();
    }
    if(i==3) legm3->Draw();
    if(i==4) legm4->Draw();
    if(i==5) legm5->Draw();
  }
  c1->Update();
  //c1->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_X-akPu3PF_etaShift.gif");
  //c1->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_X-akPu3PF_etaShift.pdf");

  histXtitle = "#Delta#phi_{1,2}";
  TCanvas *c2 = new TCanvas("c2","",1200,800);
  makeMultiPanelCanvas(c2,3,2,0.,0.,0.2,0.2,0.05);
  for(int i=0; i<6; i++){
    c2->cd(i+1);
    gPad->SetLogy();
    delphi0[i]->SetXTitle(histXtitle.c_str());
    delphi0[i]->SetYTitle(histYtitle.c_str());
    delphi0[i]->Draw();
    //delphi[8-i]->Draw("same");
    MCdphi[i]->Draw("hist,e,same");
    delphi0[i]->Draw("same");
    if(i==0){
      //ppdphi[i]->Draw("same");
      TLegend *legphi = new TLegend(0.2,0.77,0.80,0.91);
      legphi->AddEntry(delphi0[0],"2013 pPb Data, #sqrt{s}=5 TeV");
      legphi->AddEntry(MCdphi[0],"2013 PYTHIA+HIJING pPb MC, #sqrt{s}=5.02 TeV");
      // legphi->AddEntry(delphi[0],"2011 PbPb Data, #sqrt{s}=2.76 TeV");
      // legphi->AddEntry(ppdphi[0],"2011 pp data, #sqrt{s}=2.76 TeV");
      legphi->SetBorderSize(0);
      legphi->SetFillStyle(0);
      legphi->Draw();
      leg4->Draw();
      //leg5->Draw();
      legm0->SetY(0.22);
      legm0->SetX(0.1);
      legm0->Draw();
    }
    if(i==1){
      t1->SetTextSize(0.045);
      t1->Draw();
      legm1->Draw();
    }
    if(i==2){
      plum->Draw();
      legm2->SetY(0.25);
      legm2->SetX(0.1);
      legm2->Draw();
    }
    if(i==3){
      JetPtCut->Draw();
      legm3->SetY(0.25);
      legm3->SetX(0.1);
      legm3->Draw();
    }
    if(i==4){
      legm4->SetY(0.25);
      legm4->SetX(0.1);
      legm4->Draw();
    }
    if(i==5){
      legm5->SetY(0.25);
      legm5->SetX(0.1);
      legm5->Draw();
    }
  }
  c2->Update();
  //c2->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_delPhi-akPu3PF.gif");
  //c2->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_delPhi-akPu3PF.pdf");

  TCanvas *c6 = new TCanvas("c6","",1200,400);
  makeMultiPanelCanvas(c6,3,1,0.,0.,0.2,0.2,0.05);
  c6->cd(1);
  mult0[5]->Draw();
  vz0->SetLineColor(2);
  vz0->SetMarkerColor(2);
  vz0->Scale(1./vz0->Integral());
  vz0->Draw("same");
  TLatex* vztitle = new TLatex(0.1,0.22,"3 <|z_{vtx}|< 20 cm");
  vztitle->Draw();
  TLatex* multtit = new TLatex(0.1,0.25,"N_{trk}^{offline}>180");
  multtit->Draw();
  c6->cd(2);
  mult0[5]->Draw();
  vz1->SetLineColor(2);
  vz1->SetMarkerColor(2);
  vz1->Scale(1./vz1->Integral());
  vz1->Draw("same");
  TLegend *header = new TLegend(0.1,0.8,0.9,0.94);
  header->AddEntry(vz1,"<p_{T,2}/p_{T,1}> as a function of zvtx");
  header->AddEntry(mult0[5],"Inclusive zvtx reference");
  header->SetFillColor(0);
  header->SetBorderSize(0);
  header->Draw();
  TLatex* vztitle1 = new TLatex(0.1,0.21,"5 <|z_{vtx}|< 20 cm");
  vztitle1->Draw();
  c6->cd(3);
  mult0[5]->Draw();
  vz2->SetLineColor(2);
  vz2->SetMarkerColor(2);
  vz2->Scale(1./vz2->Integral());
  vz2->Draw("same");
  TLatex* vztitle2 = new TLatex(0.1,0.21,"10 <|z_{vtx}|< 20 cm");
  vztitle2->Draw();

  TCanvas *c4 = new TCanvas("c4","",1200,600);
  c4->Divide(3,1);
  c4->cd(1);
  TH1D *tmp = new TH1D("tmp","",1,0,80);
  tmp->SetMaximum(0.8);
  tmp->SetMinimum(0.62);
  tmp->SetXTitle("E_{T}^{HF[|#eta|>4]}");
  tmp->SetYTitle("<p_{T,2}/p_{T,1}>");
  tmp->GetXaxis()->CenterTitle(true);
  tmp->GetYaxis()->CenterTitle(true);
  tmp->GetYaxis()->SetTitleOffset(1.6);
  TGraphErrors *centr[4];
  Double_t pPb_nmult[5] = {12.699,22.424,27.356,34.192,47.624};
  Double_t pPb_avgPt[5] = {mult0[1]->GetMean(), mult0[2]->GetMean(), mult0[3]->GetMean(), mult0[4]->GetMean(), mult0[5]->GetMean()};
  Double_t pPb_nmultErr[5] = {0.012, 0.0296, 0.0375, 0.0406, 0.0715};
  Double_t pPb_avgPtErr[5] = {mult0[1]->GetMeanError(), mult0[2]->GetMeanError(), mult0[3]->GetMeanError(), mult0[4]->GetMeanError(), mult0[5]->GetMeanError()};

  Double_t PbPb_nmult[5] = {15.1924, 37.45, 71.267}; //cap on HFsum<90 
  Double_t PbPb_avgPt[5] = {mult[2]->GetMean(), mult[1]->GetMean(), mult[0]->GetMean()};//,mult[2]->GetMean(),mult[1]->GetMean()};
  Double_t PbPb_nmultErr[5] = {0.274, 0.296, 0.262};//0.190,0.213,0.354};
  Double_t PbPb_avgPtErr[5] = {mult[2]->GetMeanError(), mult[1]->GetMeanError(), mult[0]->GetMeanError()};

  Double_t MC_nmult[5] = {11.9707, 22.4454, 27.4279, 34.4833, 47.2613};
  Double_t MC_avgPt[5] = {MC[1]->GetMean(), MC[2]->GetMean(), MC[3]->GetMean(), MC[4]->GetMean(), MC[5]->GetMean()};
  Double_t MC_nmultErr[5] = {0.004,0.013,0.015,0.015,0.022};
  Double_t MC_avgPtErr[5] = {MC[1]->GetMeanError(), MC[2]->GetMeanError(), MC[3]->GetMeanError(), MC[4]->GetMeanError(), MC[5]->GetMeanError()};

  //Double_t pp_nmult[5] = {2.95567, 7.50071, 12.3948, 17.3344, 24.0483, 33.8478};
  Double_t pp_nmult[1] = {6.578};
  Double_t pp_avgPt[5] = {pp[0]->GetMean(), pp[1]->GetMean(), pp[2]->GetMean(), pp[3]->GetMean(), pp[4]->GetMean()};
  Double_t pp_nmultErr[5] = {0.003,0.01,0.0105,0.0154,0.0201};
  Double_t pp_avgPtErr[5] = {pp[0]->GetMeanError(), pp[1]->GetMeanError(), pp[2]->GetMeanError(), pp[3]->GetMeanError(), pp[4]->GetMeanError()};

  centr[0] = new TGraphErrors(5,pPb_nmult, pPb_avgPt, pPb_nmultErr, pPb_avgPtErr);
  centr[1] = new TGraphErrors(3,PbPb_nmult, PbPb_avgPt, PbPb_nmultErr, PbPb_avgPtErr);
  centr[2] = new TGraphErrors(5,MC_nmult, MC_avgPt, MC_nmultErr, MC_avgPtErr);
  centr[3] = new TGraphErrors(1,pp_nmult, pp_avgPt, pp_nmultErr, pp_avgPtErr);

  tmp->Draw();
  TLegend *mleg = new TLegend(0.15,0.78,0.99,0.91);
  mleg->AddEntry(centr[0], "2013 pPb data #sqrt{s}=5 TeV","pL");
  mleg->AddEntry(centr[1], "2011 PbPb data #sqrt{s}=2.76 TeV","pL");
  mleg->AddEntry(centr[2], "PYTHIA+HIJING pPb MC #sqrt{s}=5.02 TeV","pL");
  mleg->AddEntry(centr[3], "2011 pp data #sqrt{s}=2.76 TeV","pL");
  mleg->SetBorderSize(0);
  mleg->SetFillStyle(0);
  mleg->Draw();
  //t1->Draw();
  centr[0]->Draw("P,same");
  centr[1]->SetLineColor(kGreen+1);
  centr[1]->SetMarkerColor(kGreen+1);
  centr[1]->SetMarkerStyle(25);
  centr[2]->SetLineColor(2);
  centr[2]->SetMarkerColor(2);
  centr[3]->SetLineColor(4);
  centr[3]->SetMarkerColor(4);
  centr[3]->SetMarkerStyle(24);
  centr[1]->Draw("P,same");
  centr[2]->Draw("P,same");
  centr[3]->Draw("P,same");

  c4->cd(2);
  TH1D *tmp2 = new TH1D("tmp2","",1,0,80);
  tmp2->SetMaximum(0.4);
  tmp2->SetMinimum(0);
  tmp2->SetXTitle("E_{T}^{HF[|#eta|>4]}");
  tmp2->SetYTitle("Parameterized #Delta#phi");
  tmp2->GetXaxis()->CenterTitle(true);
  tmp2->GetYaxis()->CenterTitle(true);
  tmp2->GetYaxis()->SetTitleOffset(1.6);
  TGraphErrors *centr2[3];
  /*Double_t pPb_avgPt[7] = {delphi0_0->GetMean(), delphi1_0->GetMean(), delphi2_0->GetMean(), delphi3_0->GetMean(), delphi4_0->GetMean(), delphi5_0->GetMean(), delphi6_0->GetMean()};
    Double_t pPb_avgPtErr[7] = {delphi0_0->GetMeanError(), delphi1_0->GetMeanError(), delphi2_0->GetMeanError(), delphi3_0->GetMeanError(), delphi4_0->GetMeanError(), delphi5_0->GetMeanError(), delphi6_0->GetMeanError()};*/
  Double_t pPb_avgPtdphi[5] = {findDelPhiAngle(delphi0[1],1), findDelPhiAngle(delphi0[2],1), findDelPhiAngle(delphi0[3],1), findDelPhiAngle(delphi0[4],1), findDelPhiAngle(delphi0[5],1)};
  Double_t pPb_avgPtErrdphi[5] = {findDelPhiAngle(delphi0[1],2), findDelPhiAngle(delphi0[2],2), findDelPhiAngle(delphi0[3],2), findDelPhiAngle(delphi0[4],2), findDelPhiAngle(delphi0[5],2)};

  Double_t PbPb_avgPtdphi[5] = {findDelPhiAngle(delphi[2],1), findDelPhiAngle(delphi[1],1), findDelPhiAngle(delphi[0],1)};
  Double_t PbPb_avgPtErrdphi[5] = {findDelPhiAngle(delphi[2],2), findDelPhiAngle(delphi[1],2), findDelPhiAngle(delphi[0],2)};

  Double_t MC_avgPtdphi[5] = {findDelPhiAngle(MCdphi[1],1), findDelPhiAngle(MCdphi[2],1), findDelPhiAngle(MCdphi[3],1), findDelPhiAngle(MCdphi[4],1), findDelPhiAngle(MCdphi[5],1)};
  Double_t MC_avgPtErrdphi[5] = {findDelPhiAngle(MCdphi[1],2), findDelPhiAngle(MCdphi[2],2), findDelPhiAngle(MCdphi[3],2), findDelPhiAngle(MCdphi[4],2), findDelPhiAngle(MCdphi[5],2)};

  Double_t pp_avgPtdphi[5] = {findDelPhiAngle(ppdphi[0],1), findDelPhiAngle(ppdphi[1],1), findDelPhiAngle(ppdphi[2],1), findDelPhiAngle(ppdphi[3],1), findDelPhiAngle(ppdphi[4],1)};
  Double_t pp_avgPtErrdphi[5] = {findDelPhiAngle(ppdphi[0],2), findDelPhiAngle(ppdphi[1],2), findDelPhiAngle(ppdphi[2],2), findDelPhiAngle(ppdphi[3],2), findDelPhiAngle(ppdphi[4],2)};

  centr2[0] = new TGraphErrors(5,pPb_nmult, pPb_avgPtdphi, pPb_nmultErr, pPb_avgPtErrdphi);
  centr2[1] = new TGraphErrors(3,PbPb_nmult, PbPb_avgPtdphi, PbPb_nmultErr, PbPb_avgPtErrdphi);
  centr2[2] = new TGraphErrors(5,MC_nmult, MC_avgPtdphi, MC_nmultErr, MC_avgPtErrdphi);
  centr2[3] = new TGraphErrors(1,pp_nmult, pp_avgPtdphi, pp_nmultErr, pp_avgPtErrdphi);
  
  tmp2->Draw();
  TLatex* JetPtCut2 = new TLatex(10,0.31,ptcutname.c_str());
  JetPtCut2->SetTextSize(0.04);
  JetPtCut2->Draw();
  t1->SetTextSize(0.04);
  t1->Draw();
  centr2[0]->Draw("P,same");
  centr2[1]->SetLineColor(kGreen+1);
  centr2[1]->SetMarkerColor(kGreen+1);
  centr2[1]->SetMarkerStyle(25);
  centr2[2]->SetLineColor(2);
  centr2[2]->SetMarkerColor(2);
  centr2[3]->SetMarkerColor(4);
  centr2[3]->SetLineColor(4);
  centr2[3]->SetMarkerStyle(24);
  centr2[1]->Draw("P,same");
  centr2[2]->Draw("P,same");
  centr2[3]->Draw("P,same");

  TLegend *mleg2 = new TLegend(0.19,0.78,0.61,0.91);
  mleg2->AddEntry(centr[0], "pPb Data (2013) #sqrt{s}=5 TeV","pL");
  mleg2->AddEntry(centr[1], "PbPb Data (2011) #sqrt{s}=2.76 TeV","pL");
  mleg2->AddEntry(centr[2], "HIJING + PYTHIA (tune Z2) #sqrt{s}=5.02 TeV","pL");
  mleg2->SetBorderSize(0);
  mleg2->SetFillStyle(0);

  c4->cd(3);
  gROOT->ProcessLine(".x dijeteta-kurt_hf_wratiocuts.C");
  TLatex* DeltaPhiCut2 = new TLatex(10,0.1,phicutname.c_str());
  DeltaPhiCut2->SetTextSize(0.04);
  DeltaPhiCut2->Draw();

  TCanvas *c8 = new TCanvas("c8","",1200,800);
  makeMultiPanelCanvas(c8,3,2,0.,0.,0.2,0.2,0.05);
  for(int i=0; i<6; i++){
    c8->cd(i+1);
    avgPt[i]->Draw();
    PbavgPt[i]->Draw("same");
    if(i==0){
      TLegend *ptdphi = new TLegend(0.25,0.75,0.9,0.94);
      ptdphi->AddEntry(avgPt[0],"pPb #sqrt{s}=5 TeV, <p_{T,2}/p_{T,1}> vs #Delta#phi");
      ptdphi->AddEntry(PbavgPt[0],"PbPb #sqrt{s}=2.76 TeV, <p_{T,2}/p_{T,1}> vs #Delta#phi");
      ptdphi->SetBorderSize(0);
      ptdphi->SetFillColor(0);
      legm0->Draw();
      ptdphi->Draw();
    }
    if(i==1){ legm1->Draw(); JetPtCut->Draw();}
    if(i==2){ legm2->Draw(); }
    if(i==3){ legm3->Draw(); }
    if(i==4){ legm4->Draw(); }
    if(i==5){ legm5->Draw(); }
  }
  
  TCanvas *c5 = new TCanvas("c5","",800,600);
  makeMultiPanelCanvas(c5,3,2,0.,0.,0.2,0.2,0.05);
  for(int i=0; i<6; i++){
    c5->cd(i+1);
    mult_etapos[i]->Draw();
    mult_etaneg[i]->Draw("same");
    if(i==0){
      TLegend *eleg = new TLegend(0.19,0.77,0.72,0.91);
      std::string poseta=std::string("X ("+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, tracks>"+m4Str+", eta>0");
      std::string negeta=std::string("X ("+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, tracks>"+m4Str+", eta<0");
      eleg->AddEntry(mult_etapos[0], poseta.c_str());
      eleg->AddEntry(mult_etaneg[0], negeta.c_str());
      eleg->SetBorderSize(0);
      eleg->SetFillStyle(0);
      eleg->Draw();
      legm0->Draw();
    }
    if(i==1){ legm1->Draw(); JetPtCut->Draw(); }
    if(i==2){ legm2->Draw(); }
    if(i==3){ legm3->Draw(); }
    if(i==4){ legm4->Draw(); }
    if(i==5){ legm5->Draw(); }
  }
  
  if(write_output){
    TFile *output = new TFile(outputname.c_str(),"recreate");
    output->cd();
    for(int i=0; i<9; i++){
      mult[i]->Write();
      delphi[i]->Write();
    }
    for(int i=0; i<7; i++){
      mult0[i]->Write();
      delphi0[i]->Write();
    }
    for(int i=0; i<6; i++){
      MCdphi[i]->Write();
      MC[i]->Write();
    }
    output->Close();
  }
}
