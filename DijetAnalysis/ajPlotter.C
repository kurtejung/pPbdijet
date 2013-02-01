#include "commonUtility.h"

const double PI=3.1415926;

void ajPlotter(int p1, int p2){

  //double multbins[4] = {0,47,66,90}; //(~equal integration)
  double multbins[6] = {0,5,10,15,20,30}; //hiHFplusEta4 binning???
  //double multbins[6] = {0,60,90,110,150,180}; //mult binning
  double phitop=2, phibot=3;
  double deltaPhiCut = (phitop*PI/phibot);
  std::string jetcoll = "akPu3PF";

  //std::string infile = "Dijet_Jet80_5Run_"+jetcoll+".root";
  std::string infile = "test_HighPt_akPu3PF.root";
  TFile *f0 = new TFile(infile.c_str(),"OLD");
  if(!f0){ cout << "You don't have this jet collection yet!!" << endl; exit(0);}
  TFile *f1 = new TFile("PbPb-2012-Dijet.root","OLD");
  TTree *ntree = (TTree*)f1->Get("nt");
  TTree *dijetTree = (TTree*)f0->Get("dijetTree");

  //TFile *fMC = new TFile("mix_hydjet.root");
  //TTree *mcTree = (TTree*)fMC->Get("ntdijet");
  //TTree *evtTree = (TTree*)fMC->Get("ntevt");
  //TFile *fWeight = new TFile("weights_hydjet.root");
  //TTree *wTree = (TTree*)fWeight->Get("ntw");

  //mcTree->AddFriend(wTree);
  //mcTree->AddFriend(evtTree);

  TFile *fMC = new TFile("Pythia_FullInter_akPu3PF.root");
  TTree *mcTree = (TTree*)fMC->Get("dijetTree");
  
  TCanvas *c1 = new TCanvas("c1","",1200,800);
  c1->cd();

  TH1D *mult0_0 = new TH1D("mult0_0","",10,0,1);
  TH1D *mult1_0 = new TH1D("mult1_0","",10,0,1);
  TH1D *mult2_0 = new TH1D("mult2_0","",10,0,1);
  TH1D *mult3_0 = new TH1D("mult3_0","",10,0,1);
  TH1D *mult4_0 = new TH1D("mult4_0","",10,0,1);
  TH1D *mult5_0 = new TH1D("mult5_0","",10,0,1);
  mult0_0->Sumw2();
  mult1_0->Sumw2();
  mult2_0->Sumw2();
  mult3_0->Sumw2();
  mult4_0->Sumw2();
  mult5_0->Sumw2();

  TH1D *MC0_0 = new TH1D("MC0_0","",10,0,1);
  TH1D *MC1_0 = new TH1D("MC1_0","",10,0,1);
  TH1D *MC2_0 = new TH1D("MC2_0","",10,0,1);
  TH1D *MC3_0 = new TH1D("MC3_0","",10,0,1);
  TH1D *MC4_0 = new TH1D("MC4_0","",10,0,1);
  TH1D *MC5_0 = new TH1D("MC5_0","",10,0,1);
  MC0_0->Sumw2();
  MC1_0->Sumw2();
  MC2_0->Sumw2();
  MC3_0->Sumw2();
  MC4_0->Sumw2();
  MC5_0->Sumw2();
  TH1D *MC0_1 = new TH1D("MC0_1","",10,0,1);
  TH1D *MC1_1 = new TH1D("MC1_1","",10,0,1);
  TH1D *MC2_1 = new TH1D("MC2_1","",10,0,1);
  TH1D *MC3_1 = new TH1D("MC3_1","",10,0,1);
  TH1D *MC4_1 = new TH1D("MC4_1","",10,0,1);
  TH1D *MC5_1 = new TH1D("MC5_1","",10,0,1);
  MC0_1->Sumw2();
  MC1_1->Sumw2();
  MC2_1->Sumw2();
  MC3_1->Sumw2();
  MC4_1->Sumw2();
  MC5_1->Sumw2();

  TH1D *MCdphi0_0 = new TH1D("MCdphi0_0","",30,0,PI);
  TH1D *MCdphi1_0 = new TH1D("MCdphi1_0","",30,0,PI);
  TH1D *MCdphi2_0 = new TH1D("MCdphi2_0","",30,0,PI);
  TH1D *MCdphi3_0 = new TH1D("MCdphi3_0","",30,0,PI);
  TH1D *MCdphi4_0 = new TH1D("MCdphi4_0","",30,0,PI);
  TH1D *MCdphi5_0 = new TH1D("MCdphi5_0","",30,0,PI);
  MCdphi0_0->Sumw2();
  MCdphi1_0->Sumw2();
  MCdphi2_0->Sumw2();
  MCdphi3_0->Sumw2();
  MCdphi4_0->Sumw2();
  MCdphi5_0->Sumw2();

  TH1D *mult90 = new TH1D("mult90","",10,0,1);
  TH1D *mult80 = new TH1D("mult80","",10,0,1);
  TH1D *mult70 = new TH1D("mult70","",10,0,1);
  TH1D *mult60 = new TH1D("mult60","",10,0,1);
  TH1D *mult50 = new TH1D("mult50","",10,0,1);
  TH1D *mult40 = new TH1D("mult40","",10,0,1);
  mult90->Sumw2();
  mult80->Sumw2();
  mult70->Sumw2();
  mult60->Sumw2();
  mult50->Sumw2();
  mult40->Sumw2();
  TH1D *mult91 = new TH1D("mult91","",10,0,1);
  TH1D *mult81 = new TH1D("mult81","",10,0,1);
  TH1D *mult71 = new TH1D("mult71","",10,0,1);
  TH1D *mult61 = new TH1D("mult61","",10,0,1);
  TH1D *mult51 = new TH1D("mult51","",10,0,1);
  TH1D *mult41 = new TH1D("mult41","",10,0,1);
  mult91->Sumw2();
  mult81->Sumw2();
  mult71->Sumw2();
  mult61->Sumw2();
  mult51->Sumw2();
  mult41->Sumw2();

  TH1D *delphi90 = new TH1D("delphi90","",30,0,PI);
  TH1D *delphi80 = new TH1D("delphi80","",30,0,PI);
  TH1D *delphi70 = new TH1D("delphi70","",30,0,PI);
  TH1D *delphi60 = new TH1D("delphi60","",30,0,PI);
  TH1D *delphi50 = new TH1D("delphi50","",30,0,PI);
  TH1D *delphi40 = new TH1D("delphi40","",30,0,PI);
  delphi90->Sumw2();
  delphi80->Sumw2();
  delphi70->Sumw2();
  delphi60->Sumw2();
  delphi50->Sumw2();
  delphi40->Sumw2();

  TH1D *delphi1_0 = new TH1D("delphi1_0","",30,0,PI);
  TH1D *delphi2_0 = new TH1D("delphi2_0","",30,0,PI);
  TH1D *delphi3_0 = new TH1D("delphi3_0","",30,0,PI);
  TH1D *delphi4_0 = new TH1D("delphi4_0","",30,0,PI);
  TH1D *delphi5_0 = new TH1D("delphi5_0","",30,0,PI);
  TH1D *delphi0_0 = new TH1D("delphi0_0","",30,0,PI);
  delphi1_0->Sumw2();
  delphi2_0->Sumw2();
  delphi3_0->Sumw2();
  delphi4_0->Sumw2();
  delphi5_0->Sumw2();
  delphi0_0->Sumw2();

  char* histoname = new char[50];
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

  stringstream s1, s2, m1, m2, m3, m4, m5, m6, delphi, ptop, pbot;
  s1 << p1;
  s2 << p2;
  m1 << multbins[0];
  m2 << multbins[1];
  m3 << multbins[2];
  m4 << multbins[3];
  m5 << multbins[4];
  m6 << multbins[5];
  delphi << deltaPhiCut;
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
  string dphiStr = delphi.str();
  //cuts for pPb Data
  std::string cut0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>"+ m1Str +" && hiHFplusEta4<" + m2Str + " && vecPt3Pt2!=-999 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut1 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>=" + m2Str +" && hiHFplusEta4<" + m3Str + " && vecPt3Pt2!=-999 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut15 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>="+m3Str+" && hiHFplusEta4<"+m4Str+" && vecPt3Pt2!=-999 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut2 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>="+m4Str+" && vecPt3Pt2!=-999 && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";

  std::string cut0_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>"+ m1Str +" && hiHFplusEta4<" + m2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut1_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>=" + m2Str +" && hiHFplusEta4<" + m3Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut2_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>="+m3Str+" && hiHFplusEta4<"+m4Str+" && rawPt1>15 && rawPt2>15 && PUFilterGloose && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut3_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>=" + m4Str +" && hiHFplusEta4<" + m5Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut4_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>="+m5Str+" && hiHFplusEta4<"+m6Str+" && rawPt1>15 && rawPt2>15 && PUFilterGloose && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";
  std::string cut5_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>="+m6Str+" && rawPt1>15 && rawPt2>15 && PUFilterGloose && acos(cos(phi1-phi2)) > "+dphiStr;//+" && pt3<30";

  //cuts for vz dependence study
  std::string cutvz0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>=" + m6Str +" && abs(zvtx)<20 && abs(zvtx)>3 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutvz1 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>=" + m6Str +" && abs(zvtx)<20 && abs(zvtx)>5 && acos(cos(phi1-phi2)) > "+dphiStr;
  std::string cutvz2 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && hiHFplusEta4>=" + m6Str +" && abs(zvtx)<20 && abs(zvtx)>10 && acos(cos(phi1-phi2)) > "+dphiStr;
  
  //cuts for Hijing + Pythia MC
  std::string hMCcut0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>"+m1Str+" && hiHFplusEta4<"+m2Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt3<30)";
  std::string hMCcut1 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m2Str+" && hiHFplusEta4<"+m3Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt3<30)";
  std::string hMCcut2 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m3Str+" && hiHFplusEta4<"+m4Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt3<30)";
  std::string hMCcut3 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m4Str+" && hiHFplusEta4<"+m5Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt3<30)";
  std::string hMCcut4 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m5Str+" && hiHFplusEta4<"+m6Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt3<30)";
  std::string hMCcut5 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m6Str+" && acos(cos(phi1-phi2)) > "+dphiStr+")";// && jtpt3<30)";

  //cuts for PbPb data
  std::string cut3 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 28 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";
  std::string cut4 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 28 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";
  std::string cut5 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin < 28 && bin >= 20 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";
  std::string cut6 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin < 28 && bin >= 20 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";
  std::string cut7 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin < 4 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";
  std::string cut8 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin < 4 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";
  
  //cuts for PbPb comparison study
  std::string cut90 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 31 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut80 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 29 && bin < 31 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut70 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 28 && bin < 29 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut60 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 27 && bin < 28 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut50 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 26 && bin < 27 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut40 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 20 && bin < 26 && acos(cos(phi1-phi2)) > "+dphiStr+" && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut91 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 31 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0 && pt3<30";
  std::string cut81 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 29 && bin < 31 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut71 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 28 && bin < 29 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut61 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 27 && bin < 28 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut51 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 26 && bin < 27 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";// && pt3<30";
  std::string cut41 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 20 && bin < 26 && acos(cos(phi1-phi2)) < 1.0472 && (trk1+trk2) > 0 && noise < 0";// && pt3<30";

  //cuts for MC comparison
  std::string MCcut90 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 31 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) > "+dphiStr+" && noise < 0)";// && jtpt3<30)";
  std::string MCcut80 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 29 && bin < 31 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) > "+dphiStr+" && noise < 0)";// && jtpt3<30)";
  std::string MCcut70 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 28 && bin < 29 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) > "+dphiStr+" && noise < 0)";// && jtpt3<30)";
  std::string MCcut60 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 27 && bin < 28 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) > "+dphiStr+" && noise < 0)";// && jtpt3<30)";
  std::string MCcut50 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 26 && bin < 27 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) > "+dphiStr+" && noise < 0)";// && jtpt3<30)";
  std::string MCcut40 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 20 && bin < 26 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) > "+dphiStr+" && noise < 0)";// && jtpt3<30)";
  std::string MCcut91 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 31 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) < 1.0472 && noise < 0)";// && jtpt3<30)";
  std::string MCcut81 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 29 && bin < 31 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) < 1.0472 && noise < 0)";// && jtpt3<30)";
  std::string MCcut71 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 28 && bin < 29 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) < 1.0472 && noise < 0)";// && jtpt3<30)";
  std::string MCcut61 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 27 && bin < 28 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) < 1.0472 && noise < 0)";// && jtpt3<30)";
  std::string MCcut51 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 26 && bin < 27 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) < 1.0472 && noise < 0)";// && jtpt3<30)";
  std::string MCcut41 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 20 && bin < 26 && rawPt1>15 && rawPt2>15 && acos(cos(jtphi1-jtphi2)) < 1.0472 && noise < 0)";// && jtpt3<30)";

  //cuts for phi correlations
  std::string phicut0_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && hiHFplusEta4>"+m1Str+" && hiHFplusEta4<"+m2Str;
  std::string phicut1_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && hiHFplusEta4>="+m2Str+" && hiHFplusEta4<"+m3Str;
  std::string phicut2_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && hiHFplusEta4>="+m3Str+" && hiHFplusEta4<"+m4Str;
  std::string phicut3_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && hiHFplusEta4>="+m4Str+" && hiHFplusEta4<"+m5Str;
  std::string phicut4_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && hiHFplusEta4>="+m5Str+" && hiHFplusEta4<"+m6Str;
  std::string phicut5_0 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && PUFilterGloose && hiHFplusEta4>="+m6Str;
  
  std::string phicut90 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 31 && (trk1+trk2) > 0 && noise < 0";
  std::string phicut80 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 29 && bin < 31 && (trk1+trk2) > 0 && noise < 0";
  std::string phicut70 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 28 && bin < 29 && (trk1+trk2) > 0 && noise < 0";
  std::string phicut60 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 27 && bin < 28 && (trk1+trk2) > 0 && noise < 0";
  std::string phicut50 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 26 && bin < 27 && (trk1+trk2) > 0 && noise < 0";
  std::string phicut40 = "pt1>"+ p1Str + " && pt2>" + p2Str + " && bin >= 20 && bin < 26 && (trk1+trk2) > 0 && noise < 0";

  std::string MCphicut90 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 31)";
  std::string MCphicut80 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 29 && bin < 31)";
  std::string MCphicut70 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 28 && bin < 29)";
  std::string MCphicut60 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 27 && bin < 28)";
  std::string MCphicut50 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 26 && bin < 27)";
  std::string MCphicut40 = "weight*(jtpt1>"+ p1Str + " && jtpt2>" + p2Str + " && bin >= 20 && bin < 26)";

  std::string hMCphicut0_0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>"+m1Str+" && hiHFplusEta4<"+m2Str+")";
  std::string hMCphicut1_0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m2Str+" && hiHFplusEta4<"+m3Str+")";
  std::string hMCphicut2_0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m3Str+" && hiHFplusEta4<"+m4Str+")";
  std::string hMCphicut3_0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m4Str+" && hiHFplusEta4<"+m5Str+")";
  std::string hMCphicut4_0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m5Str+" && hiHFplusEta4<"+m6Str+")";
  std::string hMCphicut5_0 = "weight*(pt1>"+ p1Str + " && pt2>" + p2Str + " && rawPt1>15 && rawPt2>15 && hiHFplusEta4>="+m6Str+")";

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
  double pt1,pt2,phi1,phi2,eta1,eta2,hiHF;
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
  dijetTree->SetBranchAddress("PUFilterGloose",&PU);
  for(int i=0; i<dijetTree->GetEntries(); i++){
    dijetTree->GetEntry(i);
    if(pt1 >= p1 && pt2 >= p2 && PU){
      int j=0;
      while(hiHF>multbins[j+1] && j<5) j++;
      int k=1;
      while(acos(cos(phi1-phi2))>(k*PI/10.)) k++;
      if(j>5 || k-1>9) cout << "warning! J: " << j << " k: " << k-1 << endl;
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
  Float_t Pbpt1,Pbpt2,Pbphi1,Pbphi2,Pbtracks;
  ntree->SetBranchAddress("pt1",&Pbpt1);
  ntree->SetBranchAddress("pt2",&Pbpt2);
  ntree->SetBranchAddress("phi1",&Pbphi1);
  ntree->SetBranchAddress("phi2",&Pbphi2);
  ntree->SetBranchAddress("bin",&Pbtracks);
  for(int i=0; i<ntree->GetEntries(); i++){
    ntree->GetEntry(i);
    if(Pbpt1 >= p1 && Pbpt2 >= p2){
      int j;
      if(Pbtracks >= 31) j=0;
      else if(Pbtracks >= 29 && Pbtracks < 31) j=1;
      else if(Pbtracks >= 28 && Pbtracks < 29) j=2;
      else if(Pbtracks >= 27 && Pbtracks < 28) j=3;
      else if(Pbtracks >= 26 && Pbtracks < 27) j=4;
      else if(Pbtracks >= 20 && Pbtracks < 26) j=5;
      else continue;
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
  ntree->Draw("acos(cos(phi1-phi2))>>delphi90",phicut90.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi80",phicut80.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi70",phicut70.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi60",phicut60.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi50",phicut50.c_str());
  ntree->Draw("acos(cos(phi1-phi2))>>delphi40",phicut40.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi0_0",hMCphicut0_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi1_0",hMCphicut1_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi2_0",hMCphicut2_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi3_0",hMCphicut3_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi4_0",hMCphicut4_0.c_str());
  mcTree->Draw("(acos(cos(phi1-phi2)))>>MCdphi5_0",hMCphicut5_0.c_str());
  MCdphi0_0->Scale(1./MCdphi0_0->Integral());
  MCdphi1_0->Scale(1./MCdphi1_0->Integral());
  MCdphi2_0->Scale(1./MCdphi2_0->Integral());
  MCdphi3_0->Scale(1./MCdphi3_0->Integral());
  MCdphi4_0->Scale(1./MCdphi4_0->Integral());
  MCdphi5_0->Scale(1./MCdphi5_0->Integral());
  delphi3_0->Scale(1./delphi3_0->Integral());
  delphi4_0->Scale(1./delphi4_0->Integral());
  delphi5_0->Scale(1./delphi5_0->Integral());
  delphi1_0->SetYTitle("Event Fraction");
  delphi0_0->Scale(1./delphi0_0->Integral());
  delphi1_0->Scale(1./delphi1_0->Integral());
  delphi2_0->Scale(1./delphi2_0->Integral());

  delphi90->Scale(1./delphi90->Integral());
  delphi80->Scale(1./delphi80->Integral());
  delphi70->Scale(1./delphi70->Integral());
  delphi60->Scale(1./delphi60->Integral());
  delphi50->Scale(1./delphi50->Integral());
  delphi40->Scale(1./delphi40->Integral());
  delphi90->SetMarkerColor(4);
  delphi80->SetMarkerColor(4);
  delphi70->SetMarkerColor(4);
  delphi60->SetMarkerColor(4);
  delphi50->SetMarkerColor(4);
  delphi40->SetMarkerColor(4);
  delphi90->SetMarkerStyle(25);
  delphi80->SetMarkerStyle(25);
  delphi70->SetMarkerStyle(25);
  delphi60->SetMarkerStyle(25);
  delphi50->SetMarkerStyle(25);
  delphi40->SetMarkerStyle(25);
  delphi90->SetLineColor(4);
  delphi80->SetLineColor(4);
  delphi70->SetLineColor(4);
  delphi60->SetLineColor(4);
  delphi50->SetLineColor(4);
  delphi40->SetLineColor(4);
  MCdphi0_0->SetFillColor(2);
  MCdphi1_0->SetFillColor(2);
  MCdphi2_0->SetFillColor(2);
  MCdphi3_0->SetFillColor(2);
  MCdphi4_0->SetFillColor(2);
  MCdphi5_0->SetFillColor(2);
  MCdphi0_0->SetMarkerColor(2);
  MCdphi1_0->SetMarkerColor(2);
  MCdphi2_0->SetMarkerColor(2);
  MCdphi3_0->SetMarkerColor(2);
  MCdphi4_0->SetMarkerColor(2);
  MCdphi5_0->SetMarkerColor(2);
  MCdphi0_0->SetLineColor(2);
  MCdphi1_0->SetLineColor(2);
  MCdphi2_0->SetLineColor(2);
  MCdphi3_0->SetLineColor(2);
  MCdphi4_0->SetLineColor(2);
  MCdphi5_0->SetLineColor(2);
  MCdphi0_0->SetFillStyle(3335);
  MCdphi1_0->SetFillStyle(3335);
  MCdphi2_0->SetFillStyle(3335);
  MCdphi3_0->SetFillStyle(3335);
  MCdphi4_0->SetFillStyle(3335);
  MCdphi5_0->SetFillStyle(3335);
  
  ntree->Draw("pt2/pt1>>mult90",cut90.c_str());
  ntree->Draw("pt2/pt1>>mult80",cut80.c_str());
  ntree->Draw("pt2/pt1>>mult70",cut70.c_str());
  ntree->Draw("pt2/pt1>>mult60",cut60.c_str());
  ntree->Draw("pt2/pt1>>mult50",cut50.c_str());
  ntree->Draw("pt2/pt1>>mult40",cut40.c_str());
  ntree->Draw("pt2/pt1>>mult91",cut91.c_str());
  ntree->Draw("pt2/pt1>>mult81",cut81.c_str());
  ntree->Draw("pt2/pt1>>mult71",cut71.c_str());
  ntree->Draw("pt2/pt1>>mult61",cut61.c_str());
  ntree->Draw("pt2/pt1>>mult51",cut51.c_str());
  ntree->Draw("pt2/pt1>>mult41",cut41.c_str());
  mcTree->Draw("pt2/pt1>>MC0_0",hMCcut0.c_str());
  mcTree->Draw("pt2/pt1>>MC1_0",hMCcut1.c_str());
  mcTree->Draw("pt2/pt1>>MC2_0",hMCcut2.c_str());
  mcTree->Draw("pt2/pt1>>MC3_0",hMCcut3.c_str());
  mcTree->Draw("pt2/pt1>>MC4_0",hMCcut4.c_str());
  mcTree->Draw("pt2/pt1>>MC5_0",hMCcut5.c_str());
  /*mcTree->Draw("jtpt2/jtpt1>>MC0_1",MCcut91.c_str());
  mcTree->Draw("jtpt2/jtpt1>>MC1_1",MCcut81.c_str());
  mcTree->Draw("jtpt2/jtpt1>>MC2_1",MCcut71.c_str());
  mcTree->Draw("jtpt2/jtpt1>>MC3_1",MCcut61.c_str());
  mcTree->Draw("jtpt2/jtpt1>>MC4_1",MCcut51.c_str());
  mcTree->Draw("jtpt2/jtpt1>>MC5_1",MCcut41.c_str());*/
  dijetTree->Draw("pt2/pt1>>mult0_0",cut0_0.c_str());
  dijetTree->Draw("pt2/pt1>>mult1_0",cut1_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult2_0",cut2_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult3_0",cut3_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult4_0",cut4_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>mult5_0",cut5_0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>vz0",cutvz0.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>vz1",cutvz1.c_str(),"same");
  dijetTree->Draw("pt2/pt1>>vz2",cutvz2.c_str(),"same");

  mult90->Add(mult91,-1);
  mult80->Add(mult81,-1);
  mult70->Add(mult71,-1);
  mult60->Add(mult61,-1);
  mult50->Add(mult51,-1);
  mult40->Add(mult41,-1);
  /* MC0_0->Add(MC0_1,-1);
  MC1_0->Add(MC1_1,-1);
  MC2_0->Add(MC2_1,-1);
  MC3_0->Add(MC3_1,-1);
  MC4_0->Add(MC4_1,-1);
  MC5_0->Add(MC5_1,-1);*/
  mult90->SetMarkerColor(4);
  mult80->SetMarkerColor(4);
  mult70->SetMarkerColor(4);
  mult60->SetMarkerColor(4);
  mult50->SetMarkerColor(4);
  mult40->SetMarkerColor(4);
  mult90->SetMarkerStyle(25);
  mult80->SetMarkerStyle(25);
  mult70->SetMarkerStyle(25);
  mult60->SetMarkerStyle(25);
  mult50->SetMarkerStyle(25);
  mult40->SetMarkerStyle(25);
  mult90->SetLineColor(4);
  mult80->SetLineColor(4);
  mult70->SetLineColor(4);
  mult60->SetLineColor(4);
  mult50->SetLineColor(4);
  mult40->SetLineColor(4);
  MC0_0->SetFillColor(2);
  MC1_0->SetFillColor(2);
  MC2_0->SetFillColor(2);
  MC3_0->SetFillColor(2);
  MC4_0->SetFillColor(2);
  MC5_0->SetFillColor(2);
  MC0_0->SetMarkerColor(2);
  MC1_0->SetMarkerColor(2);
  MC2_0->SetMarkerColor(2);
  MC3_0->SetMarkerColor(2);
  MC4_0->SetMarkerColor(2);
  MC5_0->SetMarkerColor(2);
  MC0_0->SetLineColor(2);
  MC1_0->SetLineColor(2);
  MC2_0->SetLineColor(2);
  MC3_0->SetLineColor(2);
  MC4_0->SetLineColor(2);
  MC5_0->SetLineColor(2);
  MC0_0->SetFillStyle(3335);
  MC1_0->SetFillStyle(3335);
  MC2_0->SetFillStyle(3335);
  MC3_0->SetFillStyle(3335);
  MC4_0->SetFillStyle(3335);
  MC5_0->SetFillStyle(3335);
  MC0_0->Scale(1./MC0_0->Integral());
  MC1_0->Scale(1./MC1_0->Integral());
  MC2_0->Scale(1./MC2_0->Integral());
  MC3_0->Scale(1./MC3_0->Integral());
  MC4_0->Scale(1./MC4_0->Integral());
  MC5_0->Scale(1./MC5_0->Integral());
  mult90->Scale(1./mult90->Integral());
  mult80->Scale(1./mult80->Integral());
  mult70->Scale(1./mult70->Integral());
  mult60->Scale(1./mult60->Integral());
  mult50->Scale(1./mult50->Integral());
  mult40->Scale(1./mult40->Integral());
  std::string histXtitle("p_{T,2}/p_{T,1}");
  std::string histYtitle("Event Fraction");
  mult1_0->SetXTitle(histXtitle.c_str());
  mult1_0->SetYTitle(histYtitle.c_str());
  mult1_0->SetAxisRange(0,0.30,"Y");
  mult0_0->Scale(1./mult0_0->Integral());
  mult1_0->Scale(1./mult1_0->Integral());
  mult2_0->Scale(1./mult2_0->Integral());
  mult3_0->Scale(1./mult3_0->Integral());
  mult4_0->Scale(1./mult4_0->Integral());
  mult5_0->Scale(1./mult5_0->Integral());
  /* mult1_0->SetMarkerColor(2);
  mult1_0->SetLineColor(2);
  mult2_0->SetMarkerColor(kGreen+2);
  mult2_0->SetLineColor(kGreen+2);
  mult3_0->SetLineColor(4);
  mult3_0->SetMarkerColor(4);
  mult4_0->SetLineColor(8);
  mult4_0->SetMarkerColor(8);
  mult5_0->SetLineColor(16);
  mult5_0->SetMarkerColor(16);
  mult3->SetMarkerColor(8);
  mult3->SetLineColor(8);
  mult5->SetMarkerColor(6);
  mult5->SetLineColor(6);
  mult7->SetMarkerColor(40);
  mult7->SetLineColor(40);*/

  MC0_0->SetMarkerColor(2);
  MC0_0->SetLineColor(2);

  TGraphErrors* gr[6];
  Double_t avg0[6]  = {mult0_0->GetMean(), mult1_0->GetMean(), mult2_0->GetMean(), mult3_0->GetMean(), mult4_0->GetMean(), mult5_0->GetMean()};
  Double_t avg1[6]  = {0.012, 0.012, 0.012, 0.012, 0.012, 0.012};
  Double_t avg2[6]  = {mult0_0->GetMeanError(), mult1_0->GetMeanError(), mult2_0->GetMeanError(), mult3_0->GetMeanError(), mult4_0->GetMeanError(), mult5_0->GetMeanError()};
  Double_t avg3[6]  = {0,0,0,0,0,0};
  for(int i=0; i<6; i++){
    gr[i] = new TGraphErrors(1,(avg0+i),(avg1+i),(avg2+i),(avg3+i));
    gr[i]->SetMarkerColor(1);
    gr[i]->SetLineColor(1);
    gr[i]->SetMarkerStyle(23);
  }

  Double_t Pbavg0[6] = {mult90->GetMean(), mult80->GetMean(), mult70->GetMean(), mult60->GetMean(), mult50->GetMean(), mult40->GetMean()};
  Double_t Pbavg2[6] = {mult90->GetMeanError(), mult80->GetMeanError(), mult70->GetMeanError(), mult60->GetMeanError(), mult50->GetMeanError(), mult40->GetMeanError()};
  TGraphErrors* Pbgr[6];
  for(int i=0; i<6; i++){
    Pbgr[i] = new TGraphErrors(1,(Pbavg0+i),(avg1+i),(Pbavg2+i),(avg3+i));
    Pbgr[i]->SetMarkerColor(4);
    Pbgr[i]->SetLineColor(4);
    Pbgr[i]->SetMarkerStyle(23);
  }

  Double_t MCavg0[6] = {MC0_0->GetMean(), MC1_0->GetMean(), MC2_0->GetMean(), MC3_0->GetMean(), MC4_0->GetMean(), MC5_0->GetMean()};
  Double_t MCavg2[6] = {MC0_0->GetMeanError(), MC1_0->GetMeanError(), MC2_0->GetMeanError(), MC3_0->GetMeanError(), MC4_0->GetMeanError(), MC5_0->GetMeanError()};
  TGraphErrors* MCgr[6];
  for(int i=0; i<6; i++){
    MCgr[i] = new TGraphErrors(1,(MCavg0+i),(avg1+i),(MCavg2+i),(avg3+i));
    MCgr[i]->SetMarkerColor(2);
    MCgr[i]->SetLineColor(2);
    MCgr[i]->SetMarkerStyle(23);
  }

  mult1_0->SetMaximum(0.30);
  delphi1_0->SetMaximum(3);

  //for(int i=0; i<6; i++){
  //  gr[i]->Draw("P,same");
  //}
    
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
  
  plum = new TLatex(0.1,0.22,"pPb #int L dt=11.6 nb^{-1}");
  plum->SetTextSize(0.04);
  PbLum = new TLatex(0.1,0.19,"PbPb #int L dt=150 #mub^{-1}");
  PbLum->SetTextSize(0.04);
  std::string ptcutname = std::string("p_{T,1}>")+p1Str+" GeV & p_{T,2}>"+p2Str+" GeV";
  JetPtCut = new TLatex(0.1,0.22,ptcutname.c_str());
  JetPtCut->SetTextSize(0.04);
  std::string phicutname = std::string("#Delta#phi_{1,2} > (")+ptop.str()+"#pi/"+pbot.str()+")";
  DeltaPhiCut = new TLatex(0.1,0.19,phicutname.c_str());
  DeltaPhiCut->SetTextSize(0.04);
  std::string jetcollName = jetcoll+ " Jets in pPb";
  leg4 = new TLatex(0.1,0.19,jetcollName.c_str());
  leg4->SetTextSize(0.035);
  leg5 = new TLatex(0.1,0.17,"akPu3PF Jets in PbPb");
  leg5->SetTextSize(0.035);

  
  TFile *fout = new TFile("kurtpPbHistos.root","recreate");
  fout->cd();
  mult0_0->Write();
  mult1_0->Write();
  mult2_0->Write();
  mult3_0->Write();
  mult4_0->Write();
  mult5_0->Write();
  fout->Close();

  makeMultiPanelCanvas(c1,3,2,0.,0.,0.2,0.2,0.05);
  p_0_0->cd();
  mult0_0->SetMaximum(mult1_0->GetMaximum());
  mult0_0->SetXTitle(histXtitle.c_str());
  mult0_0->SetYTitle(histYtitle.c_str());
  mult0_0->Draw();
  // MC0_0->Draw("hist,e,same");
  gr[0]->Draw("P,same");
  //Pbgr[0]->Draw("P,same");
  //MCgr[0]->Draw("P,same");
  // mult90->Draw("same");
  mult0_0->Draw("same");
  TLegend *leg = new TLegend(0.2,0.77,0.80,0.91);
  leg->AddEntry(mult0_0,"CMS pPb Data, #sqrt{s}=5 TeV");
  //leg->AddEntry(MC0_0,"2013 HIJING+PYTHIA MC");
  //leg->AddEntry(mult90,"CMS PbPb Data, #sqrt{s}=2.76 TeV");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();
  leg4->Draw();
  //leg5->Draw();
  std::string m0s=std::string("HFplusEta4<"+m2Str);
  legm0 = new TLatex(0.1,0.22,m0s.c_str());
  legm0->Draw();
  p_1_0->cd();
  mult1_0->Draw();
  // MC1_0->Draw("hist,e,same");
  // mult80->Draw("same");
  gr[1]->Draw("P,same");
  //Pbgr[1]->Draw("P,same");
  //MCgr[1]->Draw("P,same");
  mult1_0->Draw("same");
  std::string m1s=std::string(m2Str+"#leqHFplusEta4<"+m3Str);
  legm1 = new TLatex(0.1,0.25,m1s.c_str());
  legm1->Draw();
  plum->Draw();
  //PbLum->Draw();
  p_2_0->cd();
  mult2_0->SetMaximum(mult1_0->GetMaximum());
  mult2_0->SetXTitle(histXtitle.c_str());
  mult2_0->SetYTitle(histYtitle.c_str());
  mult2_0->Draw();
  // MC2_0->Draw("hist,e,same");
  gr[2]->Draw("P,same");
  //Pbgr[2]->Draw("P,same");
  //MCgr[2]->Draw("P,same");
  // mult70->Draw("same");
  mult2_0->Draw("same");
  std::string m2s=std::string(m3Str+"#leqHFplusEta4<"+m4Str);
  legm2 = new TLatex(0.1,0.25,m2s.c_str());
  legm2->Draw();
  JetPtCut->Draw();
  DeltaPhiCut->Draw();
  p_0_1->cd();
  mult3_0->SetMaximum(mult1_0->GetMaximum());
  mult3_0->SetXTitle(histXtitle.c_str());
  mult3_0->SetYTitle(histYtitle.c_str());
  mult3_0->Draw();
  //MC3_0->Draw("hist,e,same");
  gr[3]->Draw("P,same");
  //Pbgr[3]->Draw("P,same");
  //MCgr[3]->Draw("P,same");
  //mult60->Draw("same");
  mult3_0->Draw("same");
  std::string m3s=std::string(m4Str+"#leqHFplusEta4<"+m5Str);
  legm3 = new TLatex(0.1,0.25,m3s.c_str());
  legm3->Draw();
  p_1_1->cd();
  mult4_0->SetMaximum(mult1_0->GetMaximum());
  mult4_0->SetXTitle(histXtitle.c_str());
  mult4_0->SetYTitle(histYtitle.c_str());
  mult4_0->Draw();
  // MC4_0->Draw("hist,e,same");
  gr[4]->Draw("P,same");
  //Pbgr[4]->Draw("P,same");
  //MCgr[4]->Draw("P,same");
  // mult50->Draw("same");
  mult4_0->Draw("same");
  std::string m4s=std::string(m5Str+"#leqHFplusEta4<"+m6Str);
  legm4 = new TLatex(0.1,0.25,m4s.c_str());
  legm4->Draw();
  p_2_1->cd();
  mult5_0->SetMaximum(mult1_0->GetMaximum());
  mult5_0->SetXTitle(histXtitle.c_str());
  mult5_0->SetYTitle(histYtitle.c_str());
  mult5_0->Draw();
  //MC5_0->Draw("hist,e,same");
  gr[5]->Draw("P,same");
  //Pbgr[5]->Draw("P,same");
  //MCgr[5]->Draw("P,same");
  // mult40->Draw("same");
  mult5_0->Draw("same");
  std::string m5s=std::string("HFplusEta4>"+m6Str);
  legm5 = new TLatex(0.1,0.25,m5s.c_str());
  legm5->Draw();
  //c1->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_X-akPu3PF_etaShift.gif");
  //c1->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_X-akPu3PF_etaShift.pdf");

  histXtitle = "#Delta#phi_{1,2}";
  TCanvas *c2 = new TCanvas("c2","",1200,800);
  makeMultiPanelCanvas(c2,3,2,0.,0.,0.2,0.2,0.05);
  p_0_0->cd();
  p_0_0->SetLogy();
  delphi0_0->SetMaximum(delphi1_0->GetMaximum());
  delphi0_0->SetXTitle(histXtitle.c_str());
  delphi0_0->SetYTitle(histYtitle.c_str());
  delphi0_0->Draw();
  delphi90->Draw("same");
  MCdphi0_0->Draw("hist,e,same");
  delphi0_0->Draw("same");
  TLegend *legphi = new TLegend(0.2,0.77,0.80,0.91);
  legphi->AddEntry(delphi0_0,"CMS pPb Data, #sqrt{s}=5 TeV");
  legphi->AddEntry(MC0_0,"HIJING+PYTHIA MC");
  legphi->AddEntry(delphi90,"CMS PbPb Data, #sqrt{s}=2.76 TeV");
  legphi->SetBorderSize(0);
  legphi->SetFillStyle(0);
  legphi->Draw();
  leg4->Draw();
  leg5->Draw();
  legm0->SetY(0.22);
  legm0->SetX(0.1);
  legm0->Draw();
  p_1_0->cd();
  p_1_0->SetLogy();
  delphi1_0->Draw();
  MCdphi1_0->Draw("hist,e,same");
  delphi80->Draw("same");
  delphi1_0->Draw("same");
  PbLum->Draw();
  legm1->SetY(0.25);
  legm1->SetX(0.1);
  legm1->Draw();
  p_2_0->cd();
  p_2_0->SetLogy();
  delphi2_0->SetMaximum(delphi1_0->GetMaximum());
  delphi2_0->SetXTitle(histXtitle.c_str());
  delphi2_0->SetYTitle(histYtitle.c_str());
  delphi2_0->Draw();
  MCdphi2_0->Draw("hist,e,same");
  delphi70->Draw("same");
  delphi2_0->Draw("same");
  plum->Draw();
  legm2->SetY(0.25);
  legm2->SetX(0.1);
  legm2->Draw();
  p_0_1->cd();
  p_0_1->SetLogy();
  delphi3_0->SetMaximum(delphi1_0->GetMaximum());
  delphi3_0->SetXTitle(histXtitle.c_str());
  delphi3_0->SetYTitle(histYtitle.c_str());
  delphi3_0->Draw();
  MCdphi3_0->Draw("hist,e,same");
  delphi60->Draw("same");
  delphi3_0->Draw("same");
  JetPtCut->Draw();
  legm3->SetY(0.25);
  legm3->SetX(0.1);
  legm3->Draw();
  p_1_1->cd();
  p_1_1->SetLogy();
  delphi4_0->SetMaximum(delphi1_0->GetMaximum());
  delphi4_0->SetXTitle(histXtitle.c_str());
  delphi4_0->SetYTitle(histYtitle.c_str());
  delphi4_0->Draw();
  MCdphi4_0->Draw("hist,e,same");
  delphi50->Draw("same");
  delphi4_0->Draw("same");
  legm4->SetY(0.25);
  legm4->SetX(0.1);
  legm4->Draw();
  p_2_1->cd();
  p_2_1->SetLogy();
  delphi5_0->SetMaximum(delphi1_0->GetMaximum());
  delphi5_0->SetXTitle(histXtitle.c_str());
  delphi5_0->SetYTitle(histYtitle.c_str());
  delphi5_0->Draw();
  MCdphi5_0->Draw("hist,e,same");
  delphi40->Draw("same");
  delphi5_0->Draw("same");
  legm5->SetY(0.25);
  legm5->SetX(0.1);
  legm5->Draw();
  c2->Update();
  //c2->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_delPhi-akPu3PF.gif");
  //c2->SaveAs("Desktop/AjEtaDep/pPb_to_PbPb_delPhi-akPu3PF.pdf");

  TCanvas *c6 = new TCanvas("c6","",1200,400);
  makeMultiPanelCanvas(c6,3,1,0.,0.,0.2,0.2,0.05);
  p_0_0->cd();
  mult5_0->Draw();
  vz0->SetLineColor(2);
  vz0->SetMarkerColor(2);
  vz0->Scale(1./vz0->Integral());
  vz0->Draw("same");
  vztitle = new TLatex(0.1,0.22,"3 <|z_{vtx}|< 20 cm");
  vztitle->Draw();
  multtit = new TLatex(0.1,0.25,"N_{trk}^{offline}>180");
  multtit->Draw();
  p_1_0->cd();
  mult5_0->Draw();
  vz1->SetLineColor(2);
  vz1->SetMarkerColor(2);
  vz1->Scale(1./vz1->Integral());
  vz1->Draw("same");
  header = new TLegend(0.1,0.8,0.9,0.94);
  header->AddEntry(vz1,"<p_{T,2}/p_{T,1}> as a function of zvtx");
  header->AddEntry(mult5_0,"Inclusive zvtx reference");
  header->SetFillColor(0);
  header->SetBorderSize(0);
  header->Draw();
  vztitle1 = new TLatex(0.1,0.21,"5 <|z_{vtx}|< 20 cm");
  vztitle1->Draw();
  p_2_0->cd();
  mult5_0->Draw();
  vz2->SetLineColor(2);
  vz2->SetMarkerColor(2);
  vz2->Scale(1./vz2->Integral());
  vz2->Draw("same");
  vztitle2 = new TLatex(0.1,0.21,"10 <|z_{vtx}|< 20 cm");
  vztitle2->Draw();

  TCanvas *c4 = new TCanvas("c4","",800,600);
  c4->cd();
  TH1D *tmp = new TH1D("tmp","",1,0,250);
  tmp->SetMaximum(0.8);
  tmp->SetMinimum(0.62);
  tmp->SetXTitle("Avg N_{trk}^{offline}");
  tmp->SetYTitle("<p_{T,2}/p_{T,1}>");
  TGraphErrors *centr[2];
  Double_t pPb_nmult[6] = {47.7939, 75.7926, 99.9849, 127.956, 164.362, 198.252};
  Double_t pPb_avgPt[6] = {mult0_0->GetMean(), mult1_0->GetMean(), mult2_0->GetMean(), mult3_0->GetMean(), mult4_0->GetMean(), mult5_0->GetMean()};
  Double_t pPb_nmultErr[6] = {6.7,8.5,10.,12.,13.5,16.};
  Double_t pPb_avgPtErr[6] = {mult0_0->GetMeanError(), mult1_0->GetMeanError(), mult2_0->GetMeanError(), mult3_0->GetMeanError(), mult4_0->GetMeanError(), mult5_0->GetMeanError()};

  Double_t PbPb_nmult[6] = {47.7939, 75.7926, 99.9849, 127.956, 164.362, 198.252};
  Double_t PbPb_avgPt[6] = {mult90->GetMean(), mult80->GetMean(), mult70->GetMean(), mult60->GetMean(), mult50->GetMean(), mult40->GetMean()};
  Double_t PbPb_nmultErr[6] = {9.,13.,15.,17.,19.5,21.};
  Double_t PbPb_avgPtErr[6] = {mult90->GetMeanError(), mult80->GetMeanError(), mult70->GetMeanError(), mult60->GetMeanError(), mult50->GetMeanError(), mult40->GetMeanError()};

  centr[0] = new TGraphErrors(6,pPb_nmult, pPb_avgPt, pPb_nmultErr, pPb_avgPtErr);
  centr[1] = new TGraphErrors(6,PbPb_nmult, PbPb_avgPt, PbPb_nmultErr, PbPb_avgPtErr);

  tmp->Draw();
  centr[0]->Draw("P,same");
  centr[1]->SetLineColor(4);
  centr[1]->SetMarkerColor(4);
  centr[1]->SetMarkerStyle(25);
  centr[1]->Draw("P,same");
  
  TLegend *mleg = new TLegend(0.19,0.78,0.61,0.91);
  mleg->AddEntry(centr[0], "pPb 2013 Data","pL");
  mleg->AddEntry(centr[1], "PbPb 2011 Data","pL");
  mleg->SetBorderSize(0);
  mleg->SetFillStyle(0);
  mleg->Draw();
  leg4->Draw();
  leg5->Draw();
  plum->Draw();
  PbLum->Draw("same");
  JetPtCut->Draw("same");
  DeltaPhiCut->Draw("same");
  //c4->SaveAs("Desktop/AjEtaDep/AvgPtRatio_vs_AvgNtrkOff-akPu3PF.pdf");
  //c4->SaveAs("Desktop/AjEtaDep/AvgPtRatio_vs_AvgNtrkOff-akPu3PF.gif");

  TCanvas *c8 = new TCanvas("c8","",1200,800);
  makeMultiPanelCanvas(c8,3,2,0.,0.,0.2,0.2,0.05);
  p_0_0->cd();
  TLegend *ptdphi = new TLegend(0.25,0.75,0.9,0.94);
  ptdphi->AddEntry(avgPt[0],"pPb #sqrt{s}=5 TeV, <p_{T,2}/p_{T,1}> vs #Delta#phi");
  ptdphi->AddEntry(PbavgPt[0],"PbPb #sqrt{s}=2.76 TeV, <p_{T,2}/p_{T,1}> vs #Delta#phi");
  ptdphi->SetBorderSize(0);
  ptdphi->SetFillColor(0);
  avgPt[0]->Draw();
  PbavgPt[0]->Draw("same");
  legm0->Draw();
  ptdphi->Draw();
  p_1_0->cd();
  //avgPt[1]->Divide(avgPt[0]);
  avgPt[1]->Draw();
  PbavgPt[1]->Draw("same");
  legm1->Draw();
  JetPtCut->Draw();
  p_2_0->cd();
  //avgPt[2]->Divide(avgPt[0]);
  avgPt[2]->Draw();
  PbavgPt[2]->Draw("same");
  legm2->Draw();
  p_0_1->cd();
  //avgPt[3]->Divide(avgPt[0]);
  avgPt[3]->Draw();
  PbavgPt[3]->Draw("same");
  legm3->Draw();
  p_1_1->cd();
  //avgPt[4]->Divide(avgPt[0]);
  avgPt[4]->Draw();
  PbavgPt[4]->Draw("same");
  legm4->Draw();
  p_2_1->cd();
  //avgPt[5]->Divide(avgPt[0]);
  avgPt[5]->Draw();
  PbavgPt[5]->Draw("same");
  legm5->Draw();

  TCanvas *c5 = new TCanvas("c5","",800,600);
  makeMultiPanelCanvas(c5,3,2,0.,0.,0.2,0.2,0.05);
  p_0_0->cd();
  TLegend *eleg = new TLegend(0.19,0.77,0.72,0.91);
  std::string poseta=std::string("X ("+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, tracks>"+m4Str+", eta>0");
  std::string negeta=std::string("X ("+p1Str+"/"+p2Str+"), p+Pb, #sqrt{s} = 5 TeV, tracks>"+m4Str+", eta<0");
  eleg->AddEntry(mult_etapos[0], poseta.c_str());
  eleg->AddEntry(mult_etaneg[0], negeta.c_str());
  eleg->SetBorderSize(0);
  eleg->SetFillStyle(0);
  mult_etapos[0]->Draw();
  mult_etaneg[0]->Draw("same");
  legm0->Draw();
  eleg->Draw();
  p_1_0->cd();
  //mult_etapos[1]->Divide(mult_etapos[0]);
  mult_etapos[1]->Draw();
  mult_etaneg[1]->Draw("same");
  legm1->Draw();
  JetPtCut->Draw();
  p_2_0->cd();
  //mult_etapos[2]->Divide(mult_etapos[0]);
  mult_etapos[2]->Draw();
  mult_etaneg[2]->Draw("same");
  legm2->Draw();
  p_0_1->cd();
  //mult_etapos[3]->Divide(mult_etapos[0]);
  mult_etapos[3]->Draw();
  mult_etaneg[3]->Draw("same");
  legm3->Draw();
  p_1_1->cd();
  //mult_etapos[4]->Divide(mult_etapos[0]);
  mult_etapos[4]->Draw();
  mult_etaneg[4]->Draw("same");
  legm4->Draw();
  p_2_1->cd();
  //mult_etapos[5]->Divide(mult_etapos[0]);
  mult_etapos[5]->Draw();
  mult_etaneg[5]->Draw("same");
  legm5->Draw();

  
}

