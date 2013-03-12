#include "commonUtility.h"
#include "TFile.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TTree.h"
#include <stdio.h>
#include <iostream>

using namespace std;

const double PI=3.1415926;

const Int_t nbins=6;
const Double_t xbins[nbins+1] = {0,5,10,15,20,30,100};
const Int_t nbinsy=20;
const Double_t ybins[nbinsy+1] = {-2,-1.8,-1.6,-1.4,-1.2,-1,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1,1.2,1.4,1.6,1.8,2};
const float cutoff[5] = {0, 0.5, 0.6, 0.7, 0.8};

void dohaXchk(int p1){

  char* histoname = new char[50];
  TH2D* histos[5];
  for(int i=0; i<5; i++){
    sprintf(histoname,"%s%d","histos_",i);
    histos[i] = new TH2D(histoname,"",nbins,xbins,nbinsy,ybins);
  }
  
  std::string infile = "FullForest_highPt_v71_akPu3PF.root";
  TFile *f0 = new TFile(infile.c_str(),"OLD");
  TTree *dijetTree = (TTree*)f0->Get("dijetTree");
  
  double pt1,pt2,phi1,phi2,eta1,eta2,rpt1,rpt2,hiHF,hiHFminus;
  int tracks;
  bool PU;
  dijetTree->SetBranchAddress("pt1",&pt1);
  dijetTree->SetBranchAddress("pt2",&pt2);
  dijetTree->SetBranchAddress("phi1",&phi1);
  dijetTree->SetBranchAddress("phi2",&phi2);
  dijetTree->SetBranchAddress("eta1",&eta1);
  dijetTree->SetBranchAddress("eta2",&eta2);
  dijetTree->SetBranchAddress("rawPt1",&rpt1);
  dijetTree->SetBranchAddress("rawPt2",&rpt2);
  dijetTree->SetBranchAddress("tracks",&tracks);
  dijetTree->SetBranchAddress("hiHFplusEta4",&hiHF);
  dijetTree->SetBranchAddress("hiHFminusEta4",&hiHFminus);
  dijetTree->SetBranchAddress("PUFilterGplus",&PU);
  for(int i=0; i<dijetTree->GetEntries(); i++){
    dijetTree->GetEntry(i);
    if(pt1 >= p1 && pt2 >= 30 && PU && rpt1>15 && rpt2>15 && acos(cos(phi1-phi2))>2.09433){
      if(pt2/pt1 > cutoff[0]) histos[0]->Fill(hiHF,(eta1+eta2)/2);
      if(pt2/pt1 > cutoff[1]) histos[1]->Fill(hiHF,(eta1+eta2)/2);
      if(pt2/pt1 > cutoff[2]) histos[2]->Fill(hiHF,(eta1+eta2)/2);
      if(pt2/pt1 > cutoff[3]) histos[3]->Fill(hiHF,(eta1+eta2)/2);
      if(pt2/pt1 > cutoff[4]) histos[4]->Fill(hiHF,(eta1+eta2)/2);
    }

    if(pt1 >= p1 && pt2 >= 30 && PU && rpt1>15 && rpt2>15){
      if(
  }

  TProfile *f1[5];
  char* legname = new char[50];
  TLegend *leg = new TLegend(0.2,0.77,0.80,0.91);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  for(int i=0; i<5; i++){
    f1[i]= (TProfile*)histos[i]->ProfileX();
    if(i==0) {f1[i]->SetXTitle("hiHF Energy"); f1[i]->SetYTitle("<(#eta_{1}+#eta_{2})/2>"); f1[i]->Draw();}
    else{
      f1[i]->SetLineColor(2*i);
      f1[i]->SetMarkerColor(2*i);
    }
    sprintf(legname,"%s%d","pt2/pt1 > ",(int)cutoff[i]);
    leg->AddEntry(f1[i],legname);
    f1[i]->Draw("same");
  }
  leg->Draw();
}

