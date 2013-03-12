#include "commonUtility.h"

double findDelPhiAngle(TH1D *input, int parorErr){
  
  TF1 *fitter = new TF1("fitter","gaus",-2,2);
  //input->Scale(1./(input->GetEntries()));
  fitter->SetParameters(1./input->GetMaximum(),-0.1,1.0);
  input->Fit("fitter","qN0","",-1.5,1.5);
  if(parorErr==1){
    return fitter->GetParameter(1);
  }
  else if(parorErr==2){
    return fitter->GetParError(1);
  }
  else return 0;
}

void etaPlotter(){

  double HFbins[6] = {0,10,15,20,30,70};
  double multBins[7] = {0,35,60,90,110,150,1000};
  
  TFile *f0 = new TFile("FullForest_v77_etaLT3_akPu3PF.root","OLD");
  if(!f0){ cout << "You don't have this jet collection yet!!" << endl; exit(0);}
  TTree *dijetTree = (TTree*)f0->Get("dijetTree");

  TFile *f2 = new TFile("PythiaPP_MC_akPu3PF.root","OLD");
  TTree *ppTree = (TTree*)f2->Get("dijetTree");

  TFile *f3 = new TFile("YaxianPPData_etaLT3_akPu3PF.root","OLD");
  TTree *ppDatTree = (TTree*)f3->Get("dijetTree");
  
  TFile *f4 = new TFile("PythiaMIT_out_v77_etaLT3_akPu3PF.root","OLD");
  TTree *mcTree = (TTree*)f4->Get("dijetTree");

  TFile *f5 = new TFile("PbPb_ReReco_Full_etaLT3_akPu3PF.root","OLD");
  TTree *pbpbtree = (TTree*)f5->Get("dijetTree");

  TH1D *etaDistropPb[6];
  TH1D *etaDistroppData[6];
  TH1D *etaDistroppMC[6];
  TH1D *etaDistropPbMC[6];
  TH1D *etaDistroPbPb[6];

  TH2D *avgEtapPb[3];
  TH2D *avgEtapp[3];
  TH2D *avgEtapPbMC[3];
  TH2D *avgEtappMC[3];

  char* histoname = new char[30];
  char* histotitle = new char[50];
  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d","etaDistropPb_",i+1);
    sprintf(histotitle,"%s%d","Dijet Eta distro, HF bin",i+1);
    if(i==5){ sprintf(histoname,"%s%d","etaDistropPb_",0); sprintf(histotitle,"%s%d","Dijet Eta distro, HF bin",0); }
    etaDistropPb[i] = new TH1D(histoname,histotitle,12,-3,3);
    etaDistropPb[i]->Sumw2();
    sprintf(histoname,"%s%d","etaDistroppData_",i);
    etaDistroppData[i] = new TH1D(histoname,"",12,-3,3);
    etaDistroppData[i]->Sumw2();
    etaDistroppData[i]->SetMarkerColor(2);
    etaDistroppData[i]->SetLineColor(2);
    sprintf(histoname,"%s%d","etaDistroppMC_",i);
    etaDistroppMC[i] = new TH1D(histoname,"",12,-3,3);
    etaDistroppMC[i]->Sumw2();
    etaDistroppMC[i]->SetMarkerColor(4);
    etaDistroppMC[i]->SetLineColor(4);
    sprintf(histoname,"%s%d","etaDistropPbMC_",i);
    etaDistropPbMC[i] = new TH1D(histoname,"",12,-3,3);
    etaDistropPbMC[i]->Sumw2();
    etaDistropPbMC[i]->SetMarkerColor(8);
    etaDistropPbMC[i]->SetLineColor(8);
    sprintf(histoname,"%s%d","etaDistroPbPb_",i);
    etaDistroPbPb[i] = new TH1D(histoname,"",12,-3,3);
    etaDistroPbPb[i]->Sumw2();
    etaDistroPbPb[i]->SetMarkerColor(8);
    etaDistroPbPb[i]->SetLineColor(8);
  }
  for(int i=0; i<3; i++){
    sprintf(histoname,"%s%d","avgEtapPb_",i);
    avgEtapPb[i] = new TH2D(histoname,"",6,-2,2,30,0,3.1415);
    avgEtapPb[i]->Sumw2();
    sprintf(histoname,"%s%d","avgEtapp_",i);
    avgEtapp[i] = new TH2D(histoname,"",6,-2,2,30,0,3.1415);
    avgEtapp[i]->Sumw2();
    sprintf(histoname,"%s%d","avgEtapPbMC_",i);
    avgEtapPbMC[i] = new TH2D(histoname,"",6,-2,2,30,0,3.1415);
    avgEtapPbMC[i]->Sumw2();
    sprintf(histoname,"%s%d","avgEtappMC_",i);
    avgEtappMC[i] = new TH2D(histoname,"",6,-2,2,30,0,3.1415);
    avgEtappMC[i]->Sumw2();
  }
  
  //pPb Data
  double pt1,pt2,phi1,phi2,eta1,eta2,hiHF,rawPt1,rawPt2, hiHFminus;
  bool PU;
  int tracks;
  dijetTree->SetBranchAddress("pt1",&pt1);
  dijetTree->SetBranchAddress("pt2",&pt2);
  dijetTree->SetBranchAddress("rawPt1",&rawPt1);
  dijetTree->SetBranchAddress("rawPt2",&rawPt2);
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
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && hiHF<70){
      avgEtapPb[0]->Fill(eta1,acos(cos(phi1-phi2)));
      avgEtapPb[1]->Fill(eta2,acos(cos(phi1-phi2)));
      avgEtapPb[2]->Fill((eta1+eta2)/2,acos(cos(phi1-phi2)));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && /*tracks>=multBins[0] && tracks<multBins[1] && */hiHF+hiHFminus>=0 && hiHF+hiHFminus<20 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPb[0]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && /*tracks>=multBins[2] && tracks<multBins[3] && */hiHF+hiHFminus>=20 && hiHF+hiHFminus<25 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPb[1]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && /*tracks>=multBins[3] && tracks<multBins[4] && */hiHF+hiHFminus>=25 && hiHF+hiHFminus<30 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPb[2]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && /*tracks>=multBins[4] && tracks<multBins[5] && */hiHF+hiHFminus>=30 && hiHF+hiHFminus<40 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPb[3]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && /*tracks>=multBins[5] && tracks<multBins[6] && */hiHF+hiHFminus>=40 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPb[4]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && PU && acos(cos(phi1-phi2))>2.0944){
      etaDistropPb[5]->Fill((eta1+eta2)/2);
    }
  }

  //pPb MC
  double weight, MCentries, pthat;
  mcTree->SetBranchAddress("pt1",&pt1);
  mcTree->SetBranchAddress("pt2",&pt2);
  mcTree->SetBranchAddress("rawPt1",&rawPt1);
  mcTree->SetBranchAddress("rawPt2",&rawPt2);
  mcTree->SetBranchAddress("tracks",&tracks);
  mcTree->SetBranchAddress("pthat",&pthat);
  mcTree->SetBranchAddress("phi1",&phi1);
  mcTree->SetBranchAddress("phi2",&phi2);
  mcTree->SetBranchAddress("eta1",&eta1);
  mcTree->SetBranchAddress("eta2",&eta2);
  mcTree->SetBranchAddress("hiHFplusEta4",&hiHF);
  mcTree->SetBranchAddress("hiHFminusEta4",&hiHFminus);
  mcTree->SetBranchAddress("weight",&weight);
  mcTree->SetBranchAddress("MCpthatEntries",&MCentries);
  for(int i=0; i<mcTree->GetEntries(); i++){
    mcTree->GetEntry(i);
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>50 && hiHF<70){
      avgEtapPbMC[0]->Fill(eta1,acos(cos(phi1-phi2)),(weight/MCentries));
      avgEtapPbMC[1]->Fill(eta2,acos(cos(phi1-phi2)),(weight/MCentries));
      avgEtapPbMC[2]->Fill((eta1+eta2)/2,acos(cos(phi1-phi2)),(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>30 && /*tracks>=multBins[0] && tracks<multBins[1] &&*/ hiHF+hiHFminus>=0 && hiHF+hiHFminus<20 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPbMC[0]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>30 && /*tracks>=multBins[2] && tracks<multBins[3] && */hiHF+hiHFminus>=20 && hiHF+hiHFminus<25 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPbMC[1]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>30 && /*tracks>=multBins[3] && tracks<multBins[4] && */hiHF+hiHFminus>=25 && hiHF+hiHFminus<30 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPbMC[2]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>30 && /*tracks>=multBins[4] && tracks<multBins[5] && */hiHF+hiHFminus>=30 && hiHF+hiHFminus<40 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPbMC[3]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>30 && /*tracks>=multBins[5] && tracks<multBins[6] && */hiHF+hiHFminus>=40 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistropPbMC[4]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
  }

  //pp MC
  ppTree->SetBranchAddress("pt1",&pt1);
  ppTree->SetBranchAddress("pt2",&pt2);
  ppTree->SetBranchAddress("rawPt1",&rawPt1);
  ppTree->SetBranchAddress("rawPt2",&rawPt2);
  ppTree->SetBranchAddress("weight",&weight);
  ppTree->SetBranchAddress("MCpthatEntries",&MCentries);
  ppTree->SetBranchAddress("phi1",&phi1);
  ppTree->SetBranchAddress("phi2",&phi2);
  ppTree->SetBranchAddress("eta1",&eta1);
  ppTree->SetBranchAddress("eta2",&eta2);
  ppTree->SetBranchAddress("hiHFplusEta4",&hiHF);
  ppTree->SetBranchAddress("hiHFminusEta4",&hiHFminus);
  for(int i=0; i<ppTree->GetEntries(); i++){
    ppTree->GetEntry(i);
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && pthat>50 && hiHF<70 && acos(cos(phi1-phi2)>2.0944)){
      avgEtappMC[0]->Fill(eta1,acos(cos(phi1-phi2)),(weight/MCentries));
      avgEtappMC[1]->Fill(eta2,acos(cos(phi1-phi2)),(weight/MCentries));
      avgEtappMC[2]->Fill((eta1+eta2)/2,acos(cos(phi1-phi2)),(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=0 && hiHF+hiHFminus<20 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppMC[0]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=20 && hiHF+hiHFminus<25 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppMC[1]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=25 && hiHF+hiHFminus<30 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppMC[2]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=30 && hiHF+hiHFminus<40 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppMC[3]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=40 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppMC[4]->Fill((eta1+eta2)/2,(weight/MCentries));
    }
  }

  //pp data
  ppDatTree->SetBranchAddress("pt1",&pt1);
  ppDatTree->SetBranchAddress("pt2",&pt2);
  ppDatTree->SetBranchAddress("rawPt1",&rawPt1);
  ppDatTree->SetBranchAddress("rawPt2",&rawPt2);
  ppDatTree->SetBranchAddress("phi1",&phi1);
  ppDatTree->SetBranchAddress("phi2",&phi2);
  ppDatTree->SetBranchAddress("eta1",&eta1);
  ppDatTree->SetBranchAddress("eta2",&eta2);
  ppDatTree->SetBranchAddress("hiHFplusEta4",&hiHF);
  ppDatTree->SetBranchAddress("hiHFminusEta4",&hiHFminus);
  for(int i=0; i<ppDatTree->GetEntries(); i++){
    ppDatTree->GetEntry(i);
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF<70){
      avgEtapp[0]->Fill(eta1,acos(cos(phi1-phi2)));
      avgEtapp[1]->Fill(eta2,acos(cos(phi1-phi2)));
      avgEtapp[2]->Fill((eta1+eta2)/2,acos(cos(phi1-phi2)));
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=0 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppData[0]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=20 && hiHF+hiHFminus<25 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppData[1]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=25 && hiHF+hiHFminus<30 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppData[2]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=30 && hiHF+hiHFminus<40 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppData[3]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=40 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroppData[4]->Fill((eta1+eta2)/2);
    }
  }

  pbpbtree->SetBranchAddress("pt1",&pt1);
  pbpbtree->SetBranchAddress("pt2",&pt2);
  pbpbtree->SetBranchAddress("rawPt1",&rawPt1);
  pbpbtree->SetBranchAddress("rawPt2",&rawPt2);
  pbpbtree->SetBranchAddress("phi1",&phi1);
  pbpbtree->SetBranchAddress("phi2",&phi2);
  pbpbtree->SetBranchAddress("eta1",&eta1);
  pbpbtree->SetBranchAddress("eta2",&eta2);
  pbpbtree->SetBranchAddress("hiHFplusEta4",&hiHF);
  pbpbtree->SetBranchAddress("hiHFminusEta4",&hiHFminus);
  for(int i=0; i<pbpbtree->GetEntries(); i++){
    pbpbtree->GetEntry(i);
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=0 && hiHF+hiHFminus<25 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroPbPb[0]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=25 && hiHF+hiHFminus<50 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroPbPb[1]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=50 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroPbPb[2]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=30 && hiHF+hiHFminus<40 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroPbPb[3]->Fill((eta1+eta2)/2);
    }
    if(pt1>120 && pt2>30 && rawPt1>15 && rawPt2>15 && hiHF+hiHFminus>=40 && hiHF+hiHFminus<90 && acos(cos(phi1-phi2)) > 2.0944){
      etaDistroPbPb[4]->Fill((eta1+eta2)/2);
    }
  }

  TCanvas *c2 = new TCanvas("c2","",1400,800);
  c2->cd();
  makeMultiPanelCanvas(c2,3,2,0.,0.,0.2,0.2,0.05);
  for(int i=0; i<5; i++){
    c2->cd(i+1);
    cout << "pPb:  " << etaDistropPb[i]->Integral() << endl;
    etaDistropPb[i]->Scale(1./etaDistropPb[i]->Integral());
    etaDistropPb[i]->SetMaximum(0.2);
    etaDistropPb[i]->SetYTitle("Event Fraction");
    etaDistropPb[i]->SetXTitle("(#eta_{1}+#eta_{2})/2");
    //etaDistropPb[i]->SetXTitle("#eta_{leading}");
    etaDistropPb[i]->Draw();
    cout << "ppMC:  " << etaDistroppMC[i]->Integral() << endl;
    etaDistroppMC[i]->Scale(1./etaDistroppMC[i]->Integral());
    etaDistroppMC[i]->Draw("same");
    etaDistropPbMC[i]->Scale(1./etaDistropPbMC[i]->Integral());
    etaDistropPbMC[i]->Draw("same");
    //if(etaDistroppData[i]->Integral() != 0){
    cout << "pp:  " << etaDistroppData[i]->Integral() << endl;
    etaDistroppData[i]->Scale(1./etaDistroppData[i]->Integral());
    etaDistroppData[i]->Draw("same");
    //}
    if(i==0){
      TLatex *l1 = new TLatex(0.5, 0.15,"E_{T}^{|#eta|<4}<20");
      l1->Draw();
    }
    if(i==1){
      TLatex *l2 = new TLatex(0.5, 0.15, "20#leqE_{T}^{|#eta|<4}<25");
      l2->Draw();
    }
    if(i==2){
      TLatex *l3 = new TLatex(0.5, 0.15, "25#leqE_{T}^{|#eta|<4}<30");
      l3->Draw();
    }
    if(i==3){
      TLatex *l4 = new TLatex(0.5, 0.15, "30#leqE_{T}^{|#eta|<4}<40");
      l4->Draw();
    }
    if(i==4){
      TLatex *l5 = new TLatex(0.5, 0.15, "40#leqE_{T}^{|#eta|<4}");
      l5->Draw();
    }
    if(i==0){
      TLegend *leg = new TLegend(0.2,0.77,0.80,0.91);
      leg->AddEntry(etaDistropPb[i],"pPb Data, #sqrt{s}=5 TeV");
      leg->AddEntry(etaDistroppMC[i], "pp PYTHIA MC, #sqrt{s}=5 TeV");
      leg->AddEntry(etaDistropPbMC[i], "pPb HIJING+PYTHIA MC, #sqrt{s}=5 TeV");
      leg->AddEntry(etaDistroppData[i], "pp Data, #sqrt{s}=2.76 TeV");
      leg->SetFillColor(0);
      leg->SetBorderSize(0);
      leg->Draw();
    }
  }
  
  TCanvas *c3 = new TCanvas("c3","",1400,600);
  c3->Divide(3,1);
  TH1D *profpPb[3];
  TH1D *profpp[3];
  TH1D *profpPbMC[3];
  TH1D *profppMC[3];
  for(int i=0; i<3; i++){
    c3->cd(i+1);
    profpPb[i] = avgEtapPb[i]->ProfileX();
    profpPb[i]->SetMaximum(3.0);
    profpPb[i]->SetMinimum(2.81);
    if(i==0) profpPb[i]->SetXTitle("#eta_{leading}");
    if(i==1) profpPb[i]->SetXTitle("#eta_{subleading}");
    if(i==2) profpPb[i]->SetXTitle("(#eta_{1}+#eta_{2})/2");
    profpPb[i]->SetYTitle("<#Delta#phi>");
    //profpPb[i]->Scale(1./profpPb[i]->Integral());
    profpPb[i]->Draw();
    profpp[i] = avgEtapp[i]->ProfileX();
    //profpp[i]->Scale(1./profpp[i]->Integral());
    profpp[i]->SetMarkerColor(4);
    profpp[i]->SetLineColor(4);
    profpp[i]->Draw("same");
    profpPbMC[i] = avgEtapPbMC[i]->ProfileX();
    //profpPbMC[i]->Scale(1./profpPbMC[i]->Integral());
    profpPbMC[i]->SetMarkerColor(2);
    profpPbMC[i]->SetLineColor(2);
    profpPbMC[i]->Draw("same");
    profppMC[i] = avgEtappMC[i]->ProfileX();
    // profppMC[i]->Scale(1./profppMC[i]->Integral());
    profppMC[i]->SetMarkerColor(8);
    profppMC[i]->SetLineColor(8);
    profppMC[i]->Draw("same");
  }

  //Plot mean
  /*Double_t pPb_nmult[5] = {5.658, 12.3924,17.3349,24.0448,36.3906};
  Double_t pPb_avgPt[5] = {etaDistropPb[0]->GetMean(), etaDistropPb[1]->GetMean(), etaDistropPb[2]->GetMean(), etaDistropPb[3]->GetMean(), etaDistropPb[4]->GetMean()};
  Double_t pPb_nmultErr[5] = {0.0097,0.01997,0.028038,0.0343,0.07198};
  Double_t pPb_avgPtErr[5] = {etaDistropPb[0]->GetMeanError(), etaDistropPb[1]->GetMeanError(), etaDistropPb[2]->GetMeanError(), etaDistropPb[3]->GetMeanError(), etaDistropPb[4]->GetMeanError()};

  Double_t MC_nmult[5] = {5.20261,12.3461,17.3005,23.8401,34.7769};
  Double_t MC_avgPt[5] = {etaDistropPbMC[0]->GetMean(), etaDistropPbMC[1]->GetMean(), etaDistropPbMC[2]->GetMean(), etaDistropPbMC[3]->GetMean(), etaDistropPbMC[4]->GetMean()};
  Double_t MC_nmultErr[5] = {0.0043,0.01139,0.01656.0.0211,0.0549};
  Double_t MC_avgPtErr[5] = {etaDistropPbMC[0]->GetMeanError(), etaDistropPbMC[1]->GetMeanError(), etaDistropPbMC[2]->GetMeanError(), etaDistropPbMC[3]->GetMeanError(), etaDistropPbMC[4]->GetMeanError()};

  Double_t PbPb_nmult[4] = {11.6405,30.6015,49.7908,64.897};
  Double_t PbPb_avgPt[4] = {etaDistroPbPb[0]->GetMean(), etaDistroPbPb[1]->GetMean(), etaDistroPbPb[2]->GetMean(), etaDistroPbPb[3]->GetMean()};
  Double_t PbPb_nmultErr[4] = {0.2618,0.2188,0.1961,0.1493};
  Double_t PbPb_avgPtErr[4] = {etaDistroPbPb[0]->GetMeanError(), etaDistroPbPb[1]->GetMeanError(), etaDistroPbPb[2]->GetMeanError(), etaDistroPbPb[3]->GetMeanError()};*/

 
  //Double_t pPb_nmult[5] = {5.658, 12.3924,17.3349,24.0448,36.3906}; //for hiHFplusEta4
  Double_t pPb_nmult[5] = {12.699,22.424,27.356,34.192,47.624}; //for HFplusEta4 + HFminusEta4
  Double_t pPb_avgPt[5] = {findDelPhiAngle(etaDistropPb[0],1), findDelPhiAngle(etaDistropPb[1],1), findDelPhiAngle(etaDistropPb[2],1), findDelPhiAngle(etaDistropPb[3],1), findDelPhiAngle(etaDistropPb[4],1)};
  Double_t pPb_nmultErr[5] = {0.012, 0.0296, 0.0375, 0.0406, 0.0715};
  Double_t pPb_avgPtErr[5] = {findDelPhiAngle(etaDistropPb[0],2), findDelPhiAngle(etaDistropPb[1],2), findDelPhiAngle(etaDistropPb[2],2), findDelPhiAngle(etaDistropPb[3],2), findDelPhiAngle(etaDistropPb[4],2)};

  //Double_t MC_nmult[5] = {5.20261,12.3461,17.3005,23.8401,34.7769}; //for hiHFplusEta4
  Double_t MC_nmult[5] = {11.9707, 22.4454, 27.4279, 34.4833, 47.2613}; //for hiHFplusEta4 + hiHFminusEta4
  //Double_t MC_nmult[5] = {1,3,5,8,12}; //for signal only sample
  Double_t MC_avgPt[5] = {findDelPhiAngle(etaDistropPbMC[0],1), findDelPhiAngle(etaDistropPbMC[1],1), findDelPhiAngle(etaDistropPbMC[2],1), findDelPhiAngle(etaDistropPbMC[3],1), findDelPhiAngle(etaDistropPbMC[4],1)};
  Double_t MC_nmultErr[5] = {0.004,0.013,0.015,0.015,0.022};
  Double_t MC_avgPtErr[5] = {findDelPhiAngle(etaDistropPbMC[0],2), findDelPhiAngle(etaDistropPbMC[1],2), findDelPhiAngle(etaDistropPbMC[2],2), findDelPhiAngle(etaDistropPbMC[3],2), findDelPhiAngle(etaDistropPbMC[4],2)};

  Double_t PbPb_nmult[3] = {15.1924, 37.45, 71.267};
  Double_t PbPb_avgPt[3] = {findDelPhiAngle(etaDistroPbPb[0],1), findDelPhiAngle(etaDistroPbPb[1],1), findDelPhiAngle(etaDistroPbPb[2],1)};
  Double_t PbPb_nmultErr[3] = {0.274, 0.296, 0.262};
  Double_t PbPb_avgPtErr[3] = {findDelPhiAngle(etaDistroPbPb[0],2), findDelPhiAngle(etaDistroPbPb[1],2), findDelPhiAngle(etaDistroPbPb[2],2)};

  Double_t pp_nmult[4] = {6.504, 21.78, 26.17, 31.65};
  Double_t pp_avgPt[4] = {findDelPhiAngle(etaDistroppData[0],1), findDelPhiAngle(etaDistroppData[1],1), findDelPhiAngle(etaDistroppData[2],1), findDelPhiAngle(etaDistroppData[3],1)};
  Double_t pp_nmultErr[4] = {0.04, 1.29, 3.62, 5.63};
  Double_t pp_avgPtErr[4] = {findDelPhiAngle(etaDistroppData[0],2), findDelPhiAngle(etaDistroppData[1],2), findDelPhiAngle(etaDistroppData[2],2), findDelPhiAngle(etaDistroppData[3],2)};

  /* TH1D *ppSum = etaDistroppData[0]->Clone("ppSum");
  for(int i=1; i<5; i++){
    ppSum->Add(etaDistroppData[i]);
  }
  Double_t pp_nmult[1] = {3.5};
  Double_t pp_nmultErr[1] = {0.1};
  Double_t pp_avgPt[1] = {findDelPhiAngle(ppSum,1)};
  Double_t pp_avgPtErr[1] = {findDelPhiAngle(ppSum,2)};*/

  TGraphErrors *centr2[3];
  centr2[0] = new TGraphErrors(5,pPb_nmult, pPb_avgPt, pPb_nmultErr, pPb_avgPtErr);
  centr2[1] = new TGraphErrors(3,PbPb_nmult, PbPb_avgPt, PbPb_nmultErr, PbPb_avgPtErr);
  centr2[2] = new TGraphErrors(5,MC_nmult, MC_avgPt, MC_nmultErr, MC_avgPtErr);
  centr2[3] = new TGraphErrors(1,pp_nmult, pp_avgPt, pp_nmultErr, pp_avgPtErr);
  TLatex *label1 = new TLatex(40,0.1,"|#eta|< 3");
  TH1D *temp = new TH1D("temp","",1,0,60);
  temp->SetMaximum(-0.1);
  temp->SetMinimum(-0.7);
  temp->SetXTitle("E_{T}^{HF[|#eta|>4]}");
  temp->SetYTitle("((#eta_{1}+#eta_{2})/2)_{#mu}");
  temp->GetXaxis()->CenterTitle();
  temp->GetYaxis()->CenterTitle();
  temp->GetYaxis()->SetLabelSize(0.08);
  temp->GetYaxis()->SetTitleOffset(0.5);
  temp->SetTitleSize(0.1, "y");
  temp->GetXaxis()->SetLabelSize(0.08);
  //temp->GetXaxis()->SetTitleOffset(0.5);
  temp->SetTitleSize(0.1, "x");
  TCanvas *c4 = new TCanvas("c4","",600,600);
  c4->cd();
  temp->Draw();
  centr2[0]->Draw("P,same");
  centr2[1]->SetLineColor(8);
  centr2[1]->SetMarkerColor(8);
  centr2[1]->SetMarkerStyle(25);
  //centr2[1]->Draw("P,same");
  centr2[2]->SetLineColor(2);
  centr2[2]->SetMarkerColor(2);
  centr2[2]->Draw("P,same");
  centr2[3]->SetMarkerColor(4);
  centr2[3]->SetLineColor(4);
  centr2[3]->SetMarkerStyle(24);
  //centr2[3]->Draw("P,same");
  //label1->Draw();

  etaDistropPb[0]->Scale(1./etaDistropPb[0]->Integral());
  TFile *fout = new TFile("hist_output_etaLT3_akPu3PF_ForPawan.root","UPDATE");
  fout->cd();
  for(int i=0; i<6; i++){
    etaDistropPb[i]->Write();
  }
  centr2[0]->SetNameTitle("dijEta","Dijet Eta vs Hf");
  centr2[0]->Write();
  fout->Close();
}
