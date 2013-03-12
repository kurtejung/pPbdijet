#include "commonUtility.h"

double findDelPhiAngle(TH1D *input, int parorErr){
  
  TF1 *fitter = new TF1("fitter","[1]*exp((x-3.1415)/[0])/((1-exp(-3.1415/[0]))*[0])",0,4);
  fitter->SetParameters(1.0/input->GetMaximum(),0.2);
  fitter->SetParLimits(0,0.15,0.35);
  input->Fit("fitter","q,N,0","0",2.0944,3.1415);
  if(parorErr==1){
    return fitter->GetParameter(0);
    inClone->Delete();
  }
  else if(parorErr==2){
    return fitter->GetParError(0);
    inClone->Delete();
  }
  else return 0;
  inClone->Delete();
}

TH1D* rebinHisto(TH1D* input){
  
  Double_t xbins[14] = {0, 0.5234, 1.152, 1.466, 1.7802, 1.9897, 2.1991, 2.4086, 2.618, 2.7227, 2.8274, 2.93215, 3.0368, 3.145}; 
  input = (TH1D*)input->Rebin(13,input->GetName(),xbins);
  for(int i=0; i<input->GetNbinsX(); i++){
    input->SetBinContent(i,input->GetBinContent(i)/input->GetBinWidth(i));
    input->SetBinError(i,input->GetBinError(i)/input->GetBinWidth(i));
  }
  return input;
}

double CalcError(double A, double B, double sigA, double sigB){
  double num = pow((A+B),2)*(pow(sigA,2)+pow(sigB,2))+pow(sigA,2);
  double tot = num/pow(A,2);
  tot = sqrt(tot);

  return tot;
}

void plotRatiosPU(){

  bool removeErr = false;
  double trend[6];
  double trendErr[6];
  //std::string title = "Leading p_{T}[ >150 GeV / >120 GeV]";
  //std::string title = "Subleading p_{T} [ >50 GeV / >30 GeV]";
  //std::string title = "Reco(p_{T}) / Raw(p_{T})";
  //std::string title = "ak_{T} UE-sub R=0.3 / ak_{T} R=0.3";
  //std::string title = "ak_{T}, R=0.3 / ak_{T}, R=0.5";
  //std::string title = "Reco(p_{T}) / Gen(p_{T})";
  //std::string title = "True JEC / 5% Artificial JEC Error";
  std::string title = "PUFilterGplus / No PU Selection";
  //std::string title = "PF / Calo Jets [anti k_{T}, R=0.3]";
  line = new TLine(0,1,3,1);
  line->SetLineStyle(2);
  TCanvas *c1 = new TCanvas("c1","",1000,600);
  makeMultiPanelCanvas(c1,3,2,0.,0.,0.2,0.2,0.05);
  p_0_0->cd();

  //_______________________________________-

  TH1D *ppb0 = delphi0_0;
  _file0->cd();
  //trend[0] = (ppb0->GetMean() - mult0_0->GetMean()) / ppb0->GetMean();
  //trendErr[0] = CalcError(ppb0->GetMean(), mult0_0->GetMean(), ppb0->GetMeanError(), mult0_0->GetMeanError());
  trend[0] = ((findDelPhiAngle(ppb0,1) - findDelPhiAngle(delphi0_0,1))/findDelPhiAngle(ppb0,1));
  trendErr[0] = CalcError(findDelPhiAngle(ppb0,1), findDelPhiAngle(delphi0_0,1), findDelPhiAngle(ppb0,2), findDelPhiAngle(delphi0_0,2));
  ppb0 = rebinHisto(ppb0);
  delphi0_0 = rebinHisto(delphi0_0);
  cout << "d(Mean) (%): " << trend[0] << endl;
  TGraphAsymmErrors *asym1 = new TGraphAsymmErrors();
  asym1->BayesDivide(ppb0,delphi0_0);
  double sclfactor = delphi0_0->Integral()/ppb0->Integral();
  for (int i=0;i<asym1->GetN();i++) asym1->GetY()[i] *= sclfactor;
  TH1D *dummy1 = new TH1D("dummy1","",1,0,3.15);
  dummy1->SetMaximum(1.10);
  dummy1->SetMinimum(0.95);
  dummy1->SetTitleOffset(1.2,"y");
  dummy1->SetYTitle(title.c_str());
  dummy1->Draw();
  asym1->Draw("P,same");
  legm0 = new TLatex(0.5,1.03,"Inclusive E_{T}^{HF[|#eta|>4]}");
  legm0->SetTextSize(0.06);
  legm0->Draw();
  line->Draw("same");

  //_______________________________________-

  _file1->cd(); 
  TH1D *ppb1 = delphi1_0;
  _file0->cd();
  //trend[1] = (ppb1->GetMean() - mult1_0->GetMean()) / ppb1->GetMean();
  //trendErr[1] = CalcError(ppb1->GetMean(), mult1_0->GetMean(), ppb1->GetMeanError(), mult1_0->GetMeanError());
  trend[1] = (findDelPhiAngle(ppb1,1) - findDelPhiAngle(delphi1_0,1))/findDelPhiAngle(ppb1,1);
  trendErr[1] = CalcError(findDelPhiAngle(ppb1,1), findDelPhiAngle(delphi1_0,1), findDelPhiAngle(ppb1,2), findDelPhiAngle(delphi1_0,2));
  cout << "d(Mean) (%): " << trend[1] << endl;
  ppb1 = rebinHisto(ppb1);
  delphi1_0 = rebinHisto(delphi1_0);
  p_1_0->cd();
  TGraphAsymmErrors *asym2 = new TGraphAsymmErrors();
  asym2->BayesDivide(ppb1,delphi1_0);
  double sclfactor = delphi1_0->Integral()/ppb1->Integral();
  for (int i=0;i<asym2->GetN();i++) asym2->GetY()[i] *= sclfactor;
  TH1D *dummy2 = new TH1D("dummy2","",1,0,3.15);
  dummy2->SetMaximum(1.10);
  dummy2->SetMinimum(0.95);
  dummy2->SetYTitle(title.c_str());
  dummy2->Draw();
  asym2->Draw("P,same");
  legm1 = new TLatex(0.5,1.03,"E_{T}^{HF[|#eta|>4]}<20");
  legm1->SetTextSize(0.06);
  legm1->Draw();
   line->Draw();

   //_______________________________________-

  _file1->cd();
   TH1D *ppb2 = delphi2_0;
  _file0->cd();
  //trend[2] = (ppb2->GetMean() - mult2_0->GetMean()) / ppb2->GetMean();
  //trendErr[2] = CalcError(ppb1->GetMean(), mult2_0->GetMean(), ppb2->GetMeanError(), mult2_0->GetMeanError());
  trend[2] = (findDelPhiAngle(ppb2,1) - findDelPhiAngle(delphi2_0,1))/findDelPhiAngle(ppb2,1);
  trendErr[2] = CalcError(findDelPhiAngle(ppb2,1), findDelPhiAngle(delphi2_0,1), findDelPhiAngle(ppb2,2), findDelPhiAngle(delphi2_0,2));
  cout << "d(Mean) (%): " << trend[2] << endl;
  ppb2 = rebinHisto(ppb2);
  delphi2_0 = rebinHisto(delphi2_0);
  p_2_0->cd();
  TGraphAsymmErrors *asym3 = new TGraphAsymmErrors();
  asym3->BayesDivide(ppb2,delphi2_0);
  double sclfactor = delphi2_0->Integral()/ppb2->Integral();
  for (int i=0;i<asym3->GetN();i++) asym3->GetY()[i] *= sclfactor;
  TH1D *dummy3 = new TH1D("dummy3","",1,0,3.15);
  dummy3->SetMaximum(1.10);
  dummy3->SetMinimum(0.95);
  dummy3->SetYTitle(title.c_str());
  dummy3->Draw();
  asym3->Draw("P,same");
  legm2 = new TLatex(0.5,1.03,"20#leqE_{T}^{HF[|#eta|>4]}<25");
  legm2->SetTextSize(0.06);
  legm2->Draw();
  line->Draw();
  
  //_______________________________________-

  _file1->cd();
  TH1D *ppb3 = delphi3_0;
  _file0->cd();
  //trend[3] = (ppb3->GetMean() - mult3_0->GetMean()) / ppb3->GetMean();
  //trendErr[3] = CalcError(ppb3->GetMean(), mult3_0->GetMean(), ppb3->GetMeanError(), mult3_0->GetMeanError());
  trend[3] = (findDelPhiAngle(ppb3,1) - findDelPhiAngle(delphi3_0,1))/findDelPhiAngle(ppb3,1);
  trendErr[3] = CalcError(findDelPhiAngle(ppb3,1), findDelPhiAngle(delphi3_0,1), findDelPhiAngle(ppb3,2), findDelPhiAngle(delphi3_0,2));
  cout << "d(Mean) (%): " << trend[3] << endl;
  ppb3 = rebinHisto(ppb3);
  delphi3_0 = rebinHisto(delphi3_0);
  p_0_1->cd();
  TGraphAsymmErrors *asym4 = new TGraphAsymmErrors();
  asym4->BayesDivide(ppb3,delphi3_0);
  double sclfactor = delphi3_0->Integral()/ppb3->Integral();
  for (int i=0;i<asym4->GetN();i++) asym4->GetY()[i] *= sclfactor;
  TH1D *dummy4 = new TH1D("dummy4","",1,0,3.15);
  dummy4->SetMaximum(1.10);
  dummy4->SetMinimum(0.95);
  dummy4->SetTitleOffset(1.2,"y");
  dummy4->SetYTitle(title.c_str());
  dummy4->Draw();
  asym4->Draw("P,same");
  legm3 = new TLatex(0.5,1.03,"25#leqE_{T}^{HF[|#eta|>4]}<30");
  legm3->SetTextSize(0.06);
  legm3->Draw();
  line->Draw();

  //_______________________________________-

  _file1->cd();
   TH1D *ppb4 = delphi4_0;
  _file0->cd();
  //trend[4] = (ppb4->GetMean() - mult4_0->GetMean()) / ppb4->GetMean();
  //trendErr[4] = CalcError(ppb4->GetMean(), mult4_0->GetMean(), ppb4->GetMeanError(), mult4_0->GetMeanError());
  trend[4] = (findDelPhiAngle(ppb4,1) - findDelPhiAngle(delphi4_0,1))/findDelPhiAngle(ppb4,1);
  trendErr[4] = CalcError(findDelPhiAngle(ppb4,1), findDelPhiAngle(delphi4_0,1), findDelPhiAngle(ppb4,2), findDelPhiAngle(delphi4_0,2));
  cout << "d(Mean) (%): " << trend[4] << endl;
  ppb4 = rebinHisto(ppb4);
  delphi4_0 = rebinHisto(delphi4_0);
  p_1_1->cd();
  TGraphAsymmErrors *asym5 = new TGraphAsymmErrors();
  asym5->BayesDivide(ppb4,delphi4_0);
  double sclfactor = delphi4_0->Integral()/ppb4->Integral();
  for (int i=0;i<asym5->GetN();i++) asym5->GetY()[i] *= sclfactor;
  TH1D *dummy5 = new TH1D("dummy5","",1,0,3.15);
  dummy5->SetMaximum(1.10);
  dummy5->SetMinimum(0.95);
  dummy5->SetYTitle(title.c_str());
  dummy5->SetXTitle("#Delta#phi");
  dummy5->SetTitleSize(0.09,"x");
  dummy5->GetXaxis()->CenterTitle(true);
  dummy5->Draw();
  asym5->Draw("P,same");
  legm4 = new TLatex(0.5,1.03,"30#leqE_{T}^{HF[|#eta|>4]}<40");
  legm4->SetTextSize(0.06);
  legm4->Draw();
  line->Draw();

  //_______________________________________-

  _file1->cd();
   TH1D *ppb5 = delphi5_0;
  _file0->cd();
  //trend[5] = (ppb5->GetMean() - mult5_0->GetMean()) / ppb5->GetMean();
  //trendErr[5] = CalcError(ppb5->GetMean(), mult5_0->GetMean(), ppb5->GetMeanError(), mult5_0->GetMeanError());
  trend[5] = (findDelPhiAngle(ppb5,1) - findDelPhiAngle(delphi5_0,1))/findDelPhiAngle(ppb5,1);
  trendErr[5] = CalcError(findDelPhiAngle(ppb5,1), findDelPhiAngle(delphi5_0,1), findDelPhiAngle(ppb5,2), findDelPhiAngle(delphi5_0,2));
  cout << "d(Mean) (%): " << trend[5] << endl;
  ppb5 = rebinHisto(ppb5);
  delphi5_0 = rebinHisto(delphi5_0);
  p_2_1->cd();
  TGraphAsymmErrors *asym6 = new TGraphAsymmErrors();
  asym6->BayesDivide(ppb5,delphi5_0);
  double sclfactor = delphi5_0->Integral()/ppb5->Integral();
  for (int i=0;i<asym6->GetN();i++) asym6->GetY()[i] *= sclfactor;
  TH1D *dummy6 = new TH1D("dummy6","",1,0,3.15);
  dummy6->SetMaximum(1.10);
  dummy6->SetMinimum(0.95);
  dummy6->SetYTitle(title.c_str());
  dummy6->Draw();
  asym6->Draw("P,same");
  legm5 = new TLatex(0.5,1.03,"40#leqE_{T}^{HF[|#eta|>4]}");
  legm5->SetTextSize(0.06);
  legm5->Draw();
  line->Draw();

  TH1D *trender = new TH1D("trender","",6,0,6);
  for(int i=0; i<trender->GetNbinsX(); i++){
    trender->SetBinContent(i+1,trend[i]);
    trender->SetBinError(i+1, trendErr[i]);
  }
  trender->Fit("pol0","N0","",1,6);
  //TCanvas *c2 = new TCanvas("c2","",600,400);
  //c2->cd();
  //trender->Draw();
}
