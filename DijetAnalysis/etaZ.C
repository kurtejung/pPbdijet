{

  std::string infile = "FullForest_highPt_v71_akPu3PF.root";
  TFile *f0 = new TFile(infile.c_str(),"OLD");
  if(!f0){ cout << "You don't have this jet collection yet!!" << endl; exit(0);}
  TTree *dijetTree = (TTree*)f0->Get("dijetTree");

  int nZs[6] = {204, 356, 341, 259, 276, 92};
  TH1D *etaDistr[6];
  char* histoname = new char[50];
  for(int i=0; i<6; i++){
    sprintf(histoname,"%s%d","etaDistr_",i);
    etaDistr[i] = new TH1D(histoname,"",20,-2,2);
    etaDistr[i]->Sumw2();
  }
  dijetTree->Draw("eta1>>etaDistr_0","pt1>120 && pt2>30 && hiHFplusEta4>=0 && hiHFplusEta4<5 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0943");
  dijetTree->Draw("eta1>>etaDistr_1","pt1>120 && pt2>30 && hiHFplusEta4>=5 && hiHFplusEta4<10 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0943");
  dijetTree->Draw("eta1>>etaDistr_2","pt1>120 && pt2>30 && hiHFplusEta4>=10 && hiHFplusEta4<15 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0943");
  dijetTree->Draw("eta1>>etaDistr_3","pt1>120 && pt2>30 && hiHFplusEta4>=15 && hiHFplusEta4<20 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0943");
  dijetTree->Draw("eta1>>etaDistr_4","pt1>120 && pt2>30 && hiHFplusEta4>=20 && hiHFplusEta4<25 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0943");
  dijetTree->Draw("eta1>>etaDistr_5","pt1>120 && pt2>30 && hiHFplusEta4>=30 && PUFilterGplus && rawPt1>15 && rawPt2>15 && acos(cos(phi1-phi2)) > 2.0943");

  TH1D *sum = (TH1D*)etaDistr[0]->Clone("sum");
  for(int i=1; i<6; i++){
    sum->Add(etaDistr[i]);
  }
  sum->Scale(1./1528.); //total #Z's
  for(int i=0; i<6; i++){
    etaDistr[i]->Scale(1./(double)nZs[i]);
    etaDistr[i]->Divide(sum);
    etaDistr[i]->SetXTitle("#eta");
    etaDistr[i]->SetYTitle("#frac{1}{N_{Z}} #frac{#Sigma Z}{#Sigma #frac{dN}{d#eta}} #frac{dN}{d#eta}"); 
  }
  
  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->Divide(3,2);
  c1_1->cd();
  etaDistr[0]->Draw();
  legm0 = new TLatex(0,1.6,"0#leqHF<5");
  legm0->Draw();
  c1_2->cd();
  etaDistr[1]->Draw();
  legm1 = new TLatex(0,1.26,"5#leqHF<10");
  legm1->Draw();
  c1_3->cd();
  etaDistr[2]->Draw();
  legm2 = new TLatex(0,1.12,"10#leqHF<15");
  legm2->Draw();
  c1_4->cd();
  etaDistr[3]->Draw();
  legm3 = new TLatex(-1.8,1.05,"15#leqHF<20");
  legm3->Draw();
  c1_5->cd();
  etaDistr[4]->Draw();
  legm4 = new TLatex(-1.8,0.62,"20#leqHF<30");
  legm4->Draw();
  c1_6->cd();
  etaDistr[5]->Draw();
  legm2 = new TLatex(-1.8,0.9,"30#leqHF");
  legm2->Draw();

}
