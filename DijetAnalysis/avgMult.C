{
  double tot[6] = {0,0,0,0,0,0};
  double totErr[6] = {0.,0.,0.,0.,0.,0.};
  double multBins[8] = {0,20,25,30,40,90,1000};
  int nEvts[6] = {0,0,0,0,0,0};
  Double_t ntrks, mntrks, hfplus, hfminus;
  Double_t pt1;
  dijetTree->SetBranchAddress("pt1",&pt1);
  dijetTree->SetBranchAddress("hiHFplusEta4",&ntrks);
  dijetTree->SetBranchAddress("hiHFminusEta4",&mntrks);
  dijetTree->SetBranchAddress("hiHFplus",&hfplus);
  dijetTree->SetBranchAddress("hiHFminus",&hfminus);
  for(int i=0; i<dijetTree->GetEntries(); i++){
    dijetTree->GetEntry(i);
    int j=0;
    while(ntrks+mntrks > multBins[j+1]){
      j++;
    }
    if(pt1>120){
      totErr[j] = sqrt(pow(totErr[j],2) + (mntrks+ntrks));
      tot[j] += (mntrks+ntrks);
      nEvts[j]++;
    }
  }
  for(int j=0; j<6; j++){
    tot[j] = tot[j]/nEvts[j];
    totErr[j] = totErr[j]/nEvts[j];
    cout << "mult bin " << multBins[j] << " to " << multBins[j+1] << ": <hiHFplusEta4 + hiHFminusEta4 Energy> = " << tot[j] << ", with err: " << totErr[j] << endl;
    //cout << "nEvts bin " << j << ": " << nEvts[j] << endl;
  }
}
