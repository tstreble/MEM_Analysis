#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLorentzVector.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TLatex.h>
#include <iostream>
#include <TF1.h>

using namespace std;





//--- Jet TFs 
vector<TF1> getlightJetTFresolution(  TLorentzVector &quark4P)  {
  
  TF1 res1("res1", "TMath::Sqrt( [0]**2 + ([1]*TMath::Sqrt(x))**2 + ([2]*x)**2 )");
  TF1 res2("res2", "TMath::Sqrt( [0]**2 + ([1]*TMath::Sqrt(x))**2 + ([2]*x)**2 )");

  if(fabs(quark4P.Eta())<1.5){
    res1.FixParameter(0,0);
    res1.FixParameter(1,1.53);
    res1.FixParameter(2,0.13);
    
    res2.FixParameter(0,0);
    res2.FixParameter(1,0.78);
    res2.FixParameter(2,0.05);
  }
  
  else if( fabs(quark4P.Eta())>1.5 && fabs(quark4P.Eta())<3.0){
    res1.FixParameter(0,4.26);
    res1.FixParameter(1,0.58);
    res1.FixParameter(2,0.);
    
    res2.FixParameter(0,2.56);
    res2.FixParameter(1,1.99);
    res2.FixParameter(2,0.);
  }
  
  else{
    res1.FixParameter(0,0.);
    res1.FixParameter(1,0.58);
    res1.FixParameter(2,0.12);
    
    res2.FixParameter(0,0.);
    res2.FixParameter(1,0.6);
    res2.FixParameter(2,0.05);
  }


  vector<TF1> res;
  res.push_back(res1);
  res.push_back(res2);

  return res;
}




vector<TF1> getlightJetTFmean(  TLorentzVector &quark4P)  {
  TF1 mean1("mean1", "[0]+[1]*x");
  TF1 mean2("mean2", "[0]+[1]*x");
  
  if(fabs(quark4P.Eta())<1.5){   
    mean1.FixParameter(0,-2.33);
    mean1.FixParameter(1,0.99);
    
    mean2.FixParameter(0,9.39);
    mean2.FixParameter(1,0.94);
  }
  
  else if(fabs(quark4P.Eta())>1.5 && fabs(quark4P.Eta())<3.0){
    mean1.FixParameter(0,10.79);
    mean1.FixParameter(1,0.94);
    
    mean2.FixParameter(0,51.65);
    mean2.FixParameter(1,0.82);
  }
  
  else{
    mean1.FixParameter(0,-1.83);
    mean1.FixParameter(1,0.64);
    
    mean2.FixParameter(0,3.52);
    mean2.FixParameter(1,0.62);
  }
  
  vector <TF1> mean;
  mean.push_back(mean1);
  mean.push_back(mean2);

  return mean;
}



double getlightJetTFfraction(  TLorentzVector &quark4P)  {

  double f=0.;
  if(fabs(quark4P.Eta())<1.5)  
    f=0.81;
  else if(fabs(quark4P.Eta())>1.5 && fabs(quark4P.Eta())<3.0)
    f=0.8;
  else
    f=0.63;

  return f;

}



double getlightJetTF(  TLorentzVector &quark4P,  TLorentzVector &evJet4P)  {

  double f=getlightJetTFfraction(quark4P);

  vector<TF1> res  = getlightJetTFresolution(quark4P);
  vector<TF1> mean = getlightJetTFmean(quark4P);

  double Egen=quark4P.Pt();
  double Erec=evJet4P.Pt();

  double sigmaV0 = res[0].Eval(Egen); 
  double sigmaV1 = res[1].Eval(Egen); 
  double mu0=mean[0].Eval(Egen); 
  double mu1=mean[1].Eval(Egen); 
  
  TF1 gaus0("gaus0", "gaus",0,4000);
  gaus0.FixParameter(0, 1/(sigmaV0*TMath::Sqrt(2*TMath::Pi()) ) );
  gaus0.FixParameter(1, mu0);
  gaus0.FixParameter(2, sigmaV0);
    
  TF1 gaus1("gaus1", "gaus",0,4000);
  gaus1.FixParameter(0, 1/(sigmaV1*TMath::Sqrt(2*TMath::Pi()) ) );
  gaus1.FixParameter(1, mu1);
  gaus1.FixParameter(2, sigmaV1);
  
  double TFgaus= f * gaus0.Eval(Erec) + (1-f) * gaus1.Eval(Erec);

  return TFgaus;  
}




vector<TF1> getBJetTFresolution(  TLorentzVector &quark4P)  {
  TF1 res1("res1", "TMath::Sqrt( [0]**2 + ([1]*TMath::Sqrt(x))**2 + ([2]*x)**2 )");
  TF1 res2("res2", "TMath::Sqrt( [0]**2 + ([1]*TMath::Sqrt(x))**2 + ([2]*x)**2 )");
  
  if(fabs(quark4P.Eta())<1.5){
    res1.FixParameter(0,0.);
    res1.FixParameter(1,1.07);
    res1.FixParameter(2,0.05);
    
    res2.FixParameter(0,0.);
    res2.FixParameter(1,0.);
    res2.FixParameter(2,0.23);
  }
  
  else if(fabs(quark4P.Eta())>1.5 && fabs(quark4P.Eta())<3.0){
    res1.FixParameter(0,0.);
    res1.FixParameter(1,1.14);
    res1.FixParameter(2,0.);
    
    res2.FixParameter(0,3.86);
    res2.FixParameter(1,0.47);
    res2.FixParameter(2,0.21);     
  }
  
  else{
    res1.FixParameter(0,0.);
    res1.FixParameter(1,0.);
    res1.FixParameter(2,0.);
    
    res2.FixParameter(0,0.);
    res2.FixParameter(1,0.);
    res2.FixParameter(2,0.);  
  }
      

  vector<TF1> res;
  res.push_back(res1);
  res.push_back(res2);
  
  return res;
}



vector<TF1> getBJetTFmean(  TLorentzVector &quark4P)  {
  TF1 mean1("mean1", "[0]+[1]*x");
  TF1 mean2("mean2", "[0]+[1]*x");
  
  if(fabs(quark4P.Eta())<1.5){
    mean1.FixParameter(0,-6.24);
    mean1.FixParameter(1,0.99);
    
    mean2.FixParameter(0,-8.12);
    mean2.FixParameter(1,0.97);
  }
  
  else if(fabs(quark4P.Eta())>1.5 && fabs(quark4P.Eta())<2.5){
    mean1.FixParameter(0,-6.24);
    mean1.FixParameter(1,0.98);
    
    mean2.FixParameter(0,-10.31);
    mean2.FixParameter(1,0.94);
  }
  
  else{
    mean1.FixParameter(0,0.);
    mean1.FixParameter(1,0.);
    
    mean2.FixParameter(0,0.);
    mean2.FixParameter(1,0.);
  }
  

  vector <TF1> mean;
  mean.push_back(mean1);
  mean.push_back(mean2);

  return mean;
}


double getBJetTFfraction(  TLorentzVector &quark4P)  {

 double f=0.;
 if(fabs(quark4P.Eta())<1.5)  
   f=0.72;
 else if(fabs(quark4P.Eta())>1.5 && fabs(quark4P.Eta())<3.0)
   f=0.71;

  return f;

}



double getBJetTF(  TLorentzVector &quark4P,  TLorentzVector &evJet4P)  {


  double f=getBJetTFfraction(quark4P);

  vector<TF1> res  = getBJetTFresolution(quark4P);
  vector<TF1> mean = getBJetTFmean(quark4P);

  double Egen=quark4P.Pt();
  double Erec=evJet4P.Pt();

  double sigmaV0 = res[0].Eval(Egen); 
  double sigmaV1 = res[1].Eval(Egen); 
  double mu0=mean[0].Eval(Egen); 
  double mu1=mean[1].Eval(Egen);   

  TF1 gaus0("gaus0", "gaus",0,4000);
  gaus0.FixParameter(0, 1/(sigmaV0*TMath::Sqrt(2*TMath::Pi()) ) );
  gaus0.FixParameter(1, mu0);
  gaus0.FixParameter(2, sigmaV0);
    
  TF1 gaus1("gaus1", "gaus",0,4000);
  gaus1.FixParameter(0, 1/(sigmaV1*TMath::Sqrt(2*TMath::Pi()) ) );
  gaus1.FixParameter(1, mu1);
  gaus1.FixParameter(2, sigmaV1);

  double TFgaus= f * gaus0.Eval(Erec) + (1-f) * gaus1.Eval(Erec);

  return TFgaus;

}



pair<double,double> getE_Quark_Boundaries(TLorentzVector jet4P, TString flavor) {

  float quantile = 0.95;

  double Elow1 = 0.;
  double Ehigh1 = 0.;
  double Elow2 = 0.;
  double Ehigh2 = 0.;

  float mu = 0. ;
  float sigma = 0. ;

  float chi2cut = TMath::ChisquareQuantile(quantile ,1);

  vector<TF1> jetTFresolution;
  vector<TF1> jetTFmean;
  if(flavor=="light"){
    jetTFresolution = getlightJetTFresolution(jet4P);
    jetTFmean = getlightJetTFmean(jet4P);
  }
  else if(flavor=="b"){
    jetTFresolution = getBJetTFresolution(jet4P);
    jetTFmean = getBJetTFmean(jet4P);
  }

  float Erec=jet4P.Pt();
  float Egen = Erec;

  mu = jetTFmean[0].Eval(Egen);
  sigma = jetTFresolution[0].Eval(Egen);

  float GeVStep = sigma/10. ;
  while( pow((Erec-mu)/sigma,2) < chi2cut && Egen>0. && Egen<8000.){
    Egen -= GeVStep;
    mu = jetTFmean[0].Eval(Egen);
    sigma = jetTFresolution[0].Eval(Egen);
  }
  Elow1 = Egen;

  Egen = Erec;
  mu = jetTFmean[0].Eval(Egen);
  sigma = jetTFresolution[0].Eval(Egen);
  while( pow((Erec-mu)/sigma,2) < chi2cut && Egen>0. && Egen<8000.){
    Egen += GeVStep;
    mu = jetTFmean[0].Eval(Egen);
    sigma = jetTFresolution[0].Eval(Egen);
  }
  Ehigh1 = Egen;

  Egen = Erec;
  mu = jetTFmean[1].Eval(Egen);
  sigma = jetTFresolution[1].Eval(Egen);
  GeVStep = sigma/10. ;
  while( pow((Erec-mu)/sigma,2) < chi2cut && Egen>0. && Egen<8000.){
    Egen -= GeVStep;
    mu = jetTFmean[1].Eval(Egen);
    sigma = jetTFresolution[1].Eval(Egen);
  }
  Elow2 = Egen;

  Egen = Erec;
  mu = jetTFmean[1].Eval(Egen);
  sigma = jetTFresolution[1].Eval(Egen);
  while( pow((Erec-mu)/sigma,2) < chi2cut && Egen>0. && Egen<8000.){
    Egen += GeVStep;
    mu = jetTFmean[1].Eval(Egen);
    sigma = jetTFresolution[1].Eval(Egen);
  }
  Ehigh2 = Egen;

  double Emin=min(Elow1,Elow2);
  if(Emin<0)
    Emin=0;
  double Emax=max(Ehigh1,Ehigh2);

  pair<double,double> E_Bound=make_pair(Emin,Emax);
  E_Bound.first*=cosh(jet4P.Eta());
  E_Bound.second*=cosh(jet4P.Eta());

  return E_Bound;


}





pair<double,double> mLow_mUp_WHad(TLorentzVector evJet1_4P_, TLorentzVector evJet2_4P_){

  pair<double,double> boundsJet1 = getE_Quark_Boundaries(evJet1_4P_, "light");
  pair<double,double> boundsJet2 = getE_Quark_Boundaries(evJet2_4P_, "light");

  TLorentzVector jet1Low, jet2Low;
  jet1Low.SetPtEtaPhiE ( boundsJet1.first/cosh(evJet1_4P_.Eta()), evJet1_4P_.Eta(), evJet1_4P_.Phi(), boundsJet1.first );
  jet2Low.SetPtEtaPhiE ( boundsJet2.first/cosh(evJet2_4P_.Eta()), evJet2_4P_.Eta(), evJet2_4P_.Phi(), boundsJet2.first );

  TLorentzVector jet1High, jet2High;
  jet1High.SetPtEtaPhiE ( boundsJet1.second/cosh(evJet1_4P_.Eta()), evJet1_4P_.Eta(), evJet1_4P_.Phi(), boundsJet1.second );
  jet2High.SetPtEtaPhiE ( boundsJet2.second/cosh(evJet2_4P_.Eta()), evJet2_4P_.Eta(), evJet2_4P_.Phi(), boundsJet2.second );

  
  double massLow = (jet1Low+jet2Low).M();
  double massHigh = (jet1High+jet2High).M();
  
  return make_pair(massLow,massHigh);

}



pair<double,double> mLow_mUp_TopHad(TLorentzVector evBJet_hadtop_4P_, TLorentzVector evJet1_4P_, TLorentzVector evJet2_4P_){

  pair<double,double> boundsJet1 = getE_Quark_Boundaries(evJet1_4P_, "light");
  pair<double,double> boundsJet2 = getE_Quark_Boundaries(evJet2_4P_, "light");

  TLorentzVector jet1Low, jet2Low;
  jet1Low.SetPtEtaPhiE ( boundsJet1.first/cosh(evJet1_4P_.Eta()), evJet1_4P_.Eta(), evJet1_4P_.Phi(), boundsJet1.first );
  jet2Low.SetPtEtaPhiE ( boundsJet2.first/cosh(evJet2_4P_.Eta()), evJet2_4P_.Eta(), evJet2_4P_.Phi(), boundsJet2.first );

  TLorentzVector jet1High, jet2High;
  jet1High.SetPtEtaPhiE ( boundsJet1.second/cosh(evJet1_4P_.Eta()), evJet1_4P_.Eta(), evJet1_4P_.Phi(), boundsJet1.second );
  jet2High.SetPtEtaPhiE ( boundsJet2.second/cosh(evJet2_4P_.Eta()), evJet2_4P_.Eta(), evJet2_4P_.Phi(), boundsJet2.second );


  pair<double,double> boundsBJet = getE_Quark_Boundaries(evBJet_hadtop_4P_, "b");

  TLorentzVector BJetLow, BJetHigh;
  
  BJetLow.SetPtEtaPhiE ( boundsBJet.first/cosh(evBJet_hadtop_4P_.Eta()), evBJet_hadtop_4P_.Eta(), evBJet_hadtop_4P_.Phi(), boundsBJet.first );
  BJetHigh.SetPtEtaPhiE ( boundsBJet.second/cosh(evBJet_hadtop_4P_.Eta()), evBJet_hadtop_4P_.Eta(), evBJet_hadtop_4P_.Phi(), boundsBJet.second );
  
  double massLow = (jet1Low+jet2Low+BJetLow).M();
  double massHigh = (jet1High+jet2High+BJetHigh).M();
  
  return make_pair(massLow,massHigh);

}






double mLow_TopHad_missing_jet(TLorentzVector evBJet_hadtop_4P_, TLorentzVector evJet1_4P_){

  pair<double,double> boundsJet1 = getE_Quark_Boundaries(evJet1_4P_, "light");
  TLorentzVector jet1Low;
  jet1Low.SetPtEtaPhiE ( boundsJet1.first/cosh(evJet1_4P_.Eta()), evJet1_4P_.Eta(), evJet1_4P_.Phi(), boundsJet1.first );


  pair<double,double> boundsBJet = getE_Quark_Boundaries(evBJet_hadtop_4P_, "b");
  TLorentzVector BJetLow;
  BJetLow.SetPtEtaPhiE ( boundsBJet.first/cosh(evBJet_hadtop_4P_.Eta()), evBJet_hadtop_4P_.Eta(), evBJet_hadtop_4P_.Phi(), boundsBJet.first );
  
  double massLow = (jet1Low+BJetLow).M();
  
  return massLow;

}






double mLow_blep_TopLep(TLorentzVector evBJet_leptop_4P_, TLorentzVector evLep_top_4P_){

  pair<double,double> boundsBJet = getE_Quark_Boundaries(evBJet_leptop_4P_, "b");
  
  TLorentzVector BJetLow;
  BJetLow.SetPtEtaPhiE ( boundsBJet.first/cosh(evBJet_leptop_4P_.Eta()), evBJet_leptop_4P_.Eta(), evBJet_leptop_4P_.Phi(), boundsBJet.first );
  
  double MblLow=(BJetLow+evLep_top_4P_).M();

  return MblLow;

}








void make_tree(TString sample, TString treename){

  TString filename_in;
  TString filename_out;

  if(sample=="ttH_76X"){
    filename_in="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Htautau_split.root";
    filename_out="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_perm/ttH/HTauTauTree_ttH_Htautau_perm.root";
  }

  if(sample=="ttH_80X"){
    filename_in="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root";
    filename_out="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_perm/ttH/HTauTauTree_ttH_Hnonbb_perm.root";
  }

  TChain * tree = new TChain(treename);
  tree->Add(filename_in);

  vector<float> *_gentop_e = 0;
  vector<float> *_gentop_px = 0;
  vector<float> *_gentop_py = 0;
  vector<float> *_gentop_pz = 0;
  vector<int> *_gentop_decayMode = 0;

  vector<int> *_genW_TopMothInd = 0;

  vector<float> *_genH_e = 0;
  vector<float> *_genH_px = 0;
  vector<float> *_genH_py = 0;
  vector<float> *_genH_pz = 0;
  vector<int> *_genH_decayMode = 0;

  vector<float> *_genb_e = 0;
  vector<float> *_genb_px = 0;
  vector<float> *_genb_py = 0;
  vector<float> *_genb_pz = 0;
  vector<int> *_genb_TopMothInd = 0;
  vector<int> *_genb_WMothInd = 0;
  vector<int> *_genb_flags = 0;

  vector<float> *_genq_e = 0;
  vector<float> *_genq_px = 0;
  vector<float> *_genq_py = 0;
  vector<float> *_genq_pz = 0;
  vector<float> *_genq_pt = 0;
  vector<int> *_genq_pdg = 0;
  vector<int> *_genq_TopMothInd = 0;
  vector<int> *_genq_WMothInd = 0;
  vector<int> *_genq_flags = 0;

  vector<int> *_gentau_flags = 0;
  vector<int> *_gentau_HMothInd = 0;
  vector<int> *_gentau_TopMothInd = 0;
  vector<int> *_gentau_decayMode = 0;

  vector<float> *_genlep_e = 0;
  vector<float> *_genlep_px = 0;
  vector<float> *_genlep_py = 0;
  vector<float> *_genlep_pz = 0;
  vector<int> *_genlep_TopMothInd = 0;
  vector<int> *_genlep_WMothInd = 0;
  vector<int> *_genlep_TauMothInd = 0;
  vector<int> *_genlep_flags = 0;
  vector<int> *_genlep_pdg = 0;
  
  vector<float> *_gentauh_e = 0;
  vector<float> *_gentauh_px = 0;
  vector<float> *_gentauh_py = 0;
  vector<float> *_gentauh_pz = 0;
  vector<int> *_gentauh_TauMothInd = 0;
  vector<int> *_gentauh_flags = 0;

  vector<float> *_recoPFJet_btag_e = 0;
  vector<float> *_recoPFJet_btag_px = 0;
  vector<float> *_recoPFJet_btag_py = 0;
  vector<float> *_recoPFJet_btag_pz = 0;
  vector<float> *_recoPFJet_btag_CSVscore = 0;

  vector<float> *_recoPFJet_untag_e = 0;
  vector<float> *_recoPFJet_untag_px = 0;
  vector<float> *_recoPFJet_untag_py = 0;
  vector<float> *_recoPFJet_untag_pz = 0;
  vector<float> *_recoPFJet_untag_CSVscore = 0;

  vector<float> *_recoPFJet_untag_Wtag_e = 0;
  vector<float> *_recoPFJet_untag_Wtag_px = 0;
  vector<float> *_recoPFJet_untag_Wtag_py = 0;
  vector<float> *_recoPFJet_untag_Wtag_pz = 0;
  vector<float> *_recoPFJet_untag_Wtag_CSVscore = 0;

  vector<float> *_recolep_sel_e = 0;
  vector<float> *_recolep_sel_px = 0;
  vector<float> *_recolep_sel_py = 0;
  vector<float> *_recolep_sel_pz = 0;
  vector<int> *_recolep_sel_pdg = 0;

  vector<float> *_recotauh_sel_e = 0;
  vector<float> *_recotauh_sel_px = 0;
  vector<float> *_recotauh_sel_py = 0;
  vector<float> *_recotauh_sel_pz = 0;

  int _n_pair_Wtag_recoPFJet_untag;

  int _category;

  tree->SetBranchAddress("gentop_e",&_gentop_e);
  tree->SetBranchAddress("gentop_px",&_gentop_px);
  tree->SetBranchAddress("gentop_py",&_gentop_py);
  tree->SetBranchAddress("gentop_pz",&_gentop_pz);
  tree->SetBranchAddress("gentop_decayMode",&_gentop_decayMode);

  tree->SetBranchAddress("genW_TopMothInd",&_genW_TopMothInd);

  tree->SetBranchAddress("genH_e",&_genH_e);
  tree->SetBranchAddress("genH_px",&_genH_px);
  tree->SetBranchAddress("genH_py",&_genH_py);
  tree->SetBranchAddress("genH_pz",&_genH_pz);
  tree->SetBranchAddress("genH_decayMode",&_genH_decayMode);

  tree->SetBranchAddress("genb_e",&_genb_e);
  tree->SetBranchAddress("genb_px",&_genb_px);
  tree->SetBranchAddress("genb_py",&_genb_py);
  tree->SetBranchAddress("genb_pz",&_genb_pz);
  tree->SetBranchAddress("genb_WMothInd",&_genb_WMothInd);
  tree->SetBranchAddress("genb_TopMothInd",&_genb_TopMothInd);
  tree->SetBranchAddress("genb_flags",&_genb_flags);

  tree->SetBranchAddress("genq_e",&_genq_e);
  tree->SetBranchAddress("genq_px",&_genq_px);
  tree->SetBranchAddress("genq_py",&_genq_py);
  tree->SetBranchAddress("genq_pz",&_genq_pz);
  tree->SetBranchAddress("genq_pt",&_genq_pt);
  tree->SetBranchAddress("genq_pdg",&_genq_pdg);
  tree->SetBranchAddress("genq_WMothInd",&_genq_WMothInd);
  tree->SetBranchAddress("genq_TopMothInd",&_genq_TopMothInd);
  tree->SetBranchAddress("genq_flags",&_genq_flags);

  tree->SetBranchAddress("gentau_flags",&_gentau_flags);
  tree->SetBranchAddress("gentau_HMothInd",&_gentau_HMothInd);
  tree->SetBranchAddress("gentau_TopMothInd",&_gentau_TopMothInd);
  tree->SetBranchAddress("gentau_decayMode",&_gentau_decayMode);

  tree->SetBranchAddress("genlep_e",&_genlep_e);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_WMothInd",&_genlep_WMothInd);
  tree->SetBranchAddress("genlep_TopMothInd",&_genlep_TopMothInd);
  tree->SetBranchAddress("genlep_TauMothInd",&_genlep_TauMothInd);
  tree->SetBranchAddress("genlep_flags",&_genlep_flags);
  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);

  tree->SetBranchAddress("gentauh_e",&_gentauh_e);
  tree->SetBranchAddress("gentauh_px",&_gentauh_px);
  tree->SetBranchAddress("gentauh_py",&_gentauh_py);
  tree->SetBranchAddress("gentauh_pz",&_gentauh_pz);
  tree->SetBranchAddress("gentauh_TauMothInd",&_gentauh_TauMothInd);
  tree->SetBranchAddress("gentauh_flags",&_gentauh_flags);

  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);
  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree->SetBranchAddress("recoPFJet_btag_CSVscore",&_recoPFJet_btag_CSVscore);

  tree->SetBranchAddress("recoPFJet_untag_e",&_recoPFJet_untag_e);
  tree->SetBranchAddress("recoPFJet_untag_px",&_recoPFJet_untag_px);
  tree->SetBranchAddress("recoPFJet_untag_py",&_recoPFJet_untag_py);
  tree->SetBranchAddress("recoPFJet_untag_pz",&_recoPFJet_untag_pz);
  tree->SetBranchAddress("recoPFJet_untag_CSVscore",&_recoPFJet_untag_CSVscore);

  tree->SetBranchAddress("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_CSVscore",&_recoPFJet_untag_Wtag_CSVscore);

  tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
  tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
  tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
  tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
  tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);

  tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
  tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);

  tree->SetBranchAddress("n_pair_Wtag_recoPFJet_untag",&_n_pair_Wtag_recoPFJet_untag);

  tree->SetBranchAddress("category",&_category);

  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_event=tree->GetTree()->CloneTree(0);
  tree_event->SetNameTitle(treename,treename);
  TTree* tree_goodperm=tree->GetTree()->CloneTree(0);
  tree_goodperm->SetNameTitle(treename+"_goodperm",treename+"_goodperm");
  TTree* tree_badperm=tree->GetTree()->CloneTree(0);
  tree_badperm->SetNameTitle(treename+"_badperm",treename+"_badperm");

  vector<TTree*> tree_new;
  tree_new.push_back(tree_goodperm);
  tree_new.push_back(tree_badperm);


  //New branches

  float _genbh_e;
  float _genbh_px;
  float _genbh_py;
  float _genbh_pz;
  float _genbh_pt;
  float _genbh_eta;
  float _genbh_phi;
  int _genbh_i_recoPFJet_btag_matched;

  int _genq1_pdg;
  float _genq1_e;
  float _genq1_px;
  float _genq1_py;
  float _genq1_pz;
  float _genq1_pt;
  float _genq1_eta;
  float _genq1_phi;
  int _genq1_i_recoPFJet_untag_matched;

  int _genq2_pdg;
  float _genq2_e;
  float _genq2_px;
  float _genq2_py;
  float _genq2_pz;
  float _genq2_pt;
  float _genq2_eta;
  float _genq2_phi;
  int _genq2_i_recoPFJet_untag_matched;
  
  float _genbl_e;
  float _genbl_px;
  float _genbl_py;
  float _genbl_pz;
  float _genbl_pt;
  float _genbl_eta;
  float _genbl_phi;
  int _genbl_i_recoPFJet_btag_matched;

  int _genlt_pdg;
  float _genlt_e;
  float _genlt_px;
  float _genlt_py;
  float _genlt_pz;
  float _genlt_pt;
  float _genlt_eta;
  float _genlt_phi;
  int _genlt_i_recolep_sel_matched;


  int _genltau_pdg;
  float _genltau_e;
  float _genltau_px;
  float _genltau_py;
  float _genltau_pz;
  float _genltau_pt;
  float _genltau_eta;
  float _genltau_phi;
  int _genltau_i_recolep_sel_matched;

  float _genpi_e;
  float _genpi_px;
  float _genpi_py;
  float _genpi_pz;
  float _genpi_pt;
  float _genpi_eta;
  float _genpi_phi;
  int _genpi_i_recotauh_sel_matched;


  float _recoPFJet_bh_e;
  float _recoPFJet_bh_px;
  float _recoPFJet_bh_py;
  float _recoPFJet_bh_pz;
  float _recoPFJet_bh_pt; 
  float _recoPFJet_bh_eta;
  float _recoPFJet_bh_phi;
  float _recoPFJet_bh_CSVscore;

  float _recoPFJet_q1_e;
  float _recoPFJet_q1_px;
  float _recoPFJet_q1_py;
  float _recoPFJet_q1_pz;
  float _recoPFJet_q1_pt; 
  float _recoPFJet_q1_eta;
  float _recoPFJet_q1_phi;
  float _recoPFJet_q1_CSVscore;

  float _recoPFJet_q2_e;
  float _recoPFJet_q2_px;
  float _recoPFJet_q2_py;
  float _recoPFJet_q2_pz;
  float _recoPFJet_q2_pt; 
  float _recoPFJet_q2_eta;
  float _recoPFJet_q2_phi;
  float _recoPFJet_q2_CSVscore;

  float _recoPFJet_bl_e;
  float _recoPFJet_bl_px;
  float _recoPFJet_bl_py;
  float _recoPFJet_bl_pz;
  float _recoPFJet_bl_pt; 
  float _recoPFJet_bl_eta;
  float _recoPFJet_bl_phi;
  float _recoPFJet_bl_CSVscore;

  int _recolep_lt_pdg;
  float _recolep_lt_e;
  float _recolep_lt_px;
  float _recolep_lt_py;
  float _recolep_lt_pz;
  float _recolep_lt_pt; 
  float _recolep_lt_eta;
  float _recolep_lt_phi;

  int _recolep_tauH_pdg;
  float _recolep_tauH_e;
  float _recolep_tauH_px;
  float _recolep_tauH_py;
  float _recolep_tauH_pz;
  float _recolep_tauH_pt; 
  float _recolep_tauH_eta;
  float _recolep_tauH_phi;

  float _recotauh_tauH_e;
  float _recotauh_tauH_px;
  float _recotauh_tauH_py;
  float _recotauh_tauH_pz;
  float _recotauh_tauH_pt; 
  float _recotauh_tauH_eta;
  float _recotauh_tauH_phi;

  float _m_top_had;
  float _m_top_had_low;
  float _m_top_had_high;
  float _m_W_had;
  float _m_W_had_low;
  float _m_W_had_high;
  float _m_blep_top;
  float _m_blep_top_low;
  float _m_taulep_H;

  int _missing_jet_perm;
  bool _perm_passing_cuts;
  bool _perm_MEM_sel;

  int _n_perm_full;
  int _n_perm_full_passing_cuts;
  int _n_perm_missing;
  int _n_perm_missing_passing_cuts;

  int _MEM_category;
  int _n_perm_MEM_sel_passing_cuts;
  int _good_perm_category;

  for(unsigned int i=0; i<tree_new.size();i++){

    tree_new[i]->Branch("genbh_e",&_genbh_e,"genbh_e/F");
    tree_new[i]->Branch("genbh_px",&_genbh_px,"genbh_px/F");
    tree_new[i]->Branch("genbh_py",&_genbh_py,"genbh_py/F");
    tree_new[i]->Branch("genbh_pz",&_genbh_pz,"genbh_pz/F");
    tree_new[i]->Branch("genbh_pt",&_genbh_pt,"genbh_pt/F");
    tree_new[i]->Branch("genbh_eta",&_genbh_eta,"genbh_eta/F");
    tree_new[i]->Branch("genbh_phi",&_genbh_phi,"genbh_phi/F");
    tree_new[i]->Branch("genbh_i_recoPFJet_btag_matched",&_genbh_i_recoPFJet_btag_matched,"genbh_i_recoPFJet_btag_matched/I");

    tree_new[i]->Branch("genq1_pdg",&_genq1_pdg,"genq1_pdg/I");
    tree_new[i]->Branch("genq1_e",&_genq1_e,"genq1_e/F");
    tree_new[i]->Branch("genq1_px",&_genq1_px,"genq1_px/F");
    tree_new[i]->Branch("genq1_py",&_genq1_py,"genq1_py/F");
    tree_new[i]->Branch("genq1_pz",&_genq1_pz,"genq1_pz/F");
    tree_new[i]->Branch("genq1_pt",&_genq1_pt,"genq1_pt/F");
    tree_new[i]->Branch("genq1_eta",&_genq1_eta,"genq1_eta/F");
    tree_new[i]->Branch("genq1_phi",&_genq1_phi,"genq1_phi/F");
    tree_new[i]->Branch("genq1_i_recoPFJet_untag_matched",&_genq1_i_recoPFJet_untag_matched,"genq1_i_recoPFJet_untag_matched/I");
	    
    tree_new[i]->Branch("genq2_pdg",&_genq2_pdg,"genq2_pdg/I");
    tree_new[i]->Branch("genq2_e",&_genq2_e,"genq2_e/F");
    tree_new[i]->Branch("genq2_px",&_genq2_px,"genq2_px/F");
    tree_new[i]->Branch("genq2_py",&_genq2_py,"genq2_py/F");
    tree_new[i]->Branch("genq2_pz",&_genq2_pz,"genq2_pz/F");
    tree_new[i]->Branch("genq2_pt",&_genq2_pt,"genq2_pt/F");
    tree_new[i]->Branch("genq2_eta",&_genq2_eta,"genq2_eta/F");
    tree_new[i]->Branch("genq2_phi",&_genq2_phi,"genq2_phi/F");
    tree_new[i]->Branch("genq2_i_recoPFJet_untag_matched",&_genq2_i_recoPFJet_untag_matched,"genq2_i_recoPFJet_untag_matched/I");

    tree_new[i]->Branch("genbl_e",&_genbl_e,"genbl_e/F");
    tree_new[i]->Branch("genbl_px",&_genbl_px,"genbl_px/F");
    tree_new[i]->Branch("genbl_py",&_genbl_py,"genbl_py/F");
    tree_new[i]->Branch("genbl_pz",&_genbl_pz,"genbl_pz/F");
    tree_new[i]->Branch("genbl_pt",&_genbl_pt,"genbl_pt/F");
    tree_new[i]->Branch("genbl_eta",&_genbl_eta,"genbl_eta/F");
    tree_new[i]->Branch("genbl_phi",&_genbl_phi,"genbl_phi/F");
    tree_new[i]->Branch("genbl_i_recoPFJet_btag_matched",&_genbl_i_recoPFJet_btag_matched,"genbl_i_recoPFJet_btag_matched/I");
	    
    tree_new[i]->Branch("genlt_pdg",&_genlt_pdg,"genlt_pdg/I");
    tree_new[i]->Branch("genlt_e",&_genlt_e,"genlt_e/F");
    tree_new[i]->Branch("genlt_px",&_genlt_px,"genlt_px/F");
    tree_new[i]->Branch("genlt_py",&_genlt_py,"genlt_py/F");
    tree_new[i]->Branch("genlt_pz",&_genlt_pz,"genlt_pz/F");
    tree_new[i]->Branch("genlt_pt",&_genlt_pt,"genlt_pt/F");
    tree_new[i]->Branch("genlt_eta",&_genlt_eta,"genlt_eta/F");
    tree_new[i]->Branch("genlt_phi",&_genlt_phi,"genlt_phi/F");
    tree_new[i]->Branch("genlt_i_recolep_sel_matched",&_genlt_i_recolep_sel_matched,"genlt_i_recolep_sel_matched/I");

    tree_new[i]->Branch("genltau_pdg",&_genltau_pdg,"genltau_pdg/I");
    tree_new[i]->Branch("genltau_e",&_genltau_e,"genltau_e/F");
    tree_new[i]->Branch("genltau_px",&_genltau_px,"genltau_px/F");
    tree_new[i]->Branch("genltau_py",&_genltau_py,"genltau_py/F");
    tree_new[i]->Branch("genltau_pz",&_genltau_pz,"genltau_pz/F");
    tree_new[i]->Branch("genltau_pt",&_genltau_pt,"genltau_pt/F");
    tree_new[i]->Branch("genltau_eta",&_genltau_eta,"genltau_eta/F");
    tree_new[i]->Branch("genltau_phi",&_genltau_phi,"genltau_phi/F");
    tree_new[i]->Branch("genltau_i_recolep_sel_matched",&_genltau_i_recolep_sel_matched,"genltau_i_recolep_sel_matched/I");

    tree_new[i]->Branch("genpi_e",&_genpi_e,"genpi_e/F");
    tree_new[i]->Branch("genpi_px",&_genpi_px,"genpi_px/F");
    tree_new[i]->Branch("genpi_py",&_genpi_py,"genpi_py/F");
    tree_new[i]->Branch("genpi_pz",&_genpi_pz,"genpi_pz/F");
    tree_new[i]->Branch("genpi_pt",&_genpi_pt,"genpi_pt/F");
    tree_new[i]->Branch("genpi_eta",&_genpi_eta,"genpi_eta/F");
    tree_new[i]->Branch("genpi_phi",&_genpi_phi,"genpi_phi/F");
    tree_new[i]->Branch("genpi_i_recotauh_sel_matched",&_genpi_i_recotauh_sel_matched,"genpi_i_recotauh_sel_matched/I");



    tree_new[i]->Branch("recoPFJet_bh_e",        &_recoPFJet_bh_e,        "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_px",       &_recoPFJet_bh_px,       "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_py",       &_recoPFJet_bh_py,       "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_pz",       &_recoPFJet_bh_pz,       "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_pt",       &_recoPFJet_bh_pt,       "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_eta",      &_recoPFJet_bh_eta,      "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_phi",      &_recoPFJet_bh_phi,      "recoPFJet_bh_e/F");
    tree_new[i]->Branch("recoPFJet_bh_CSVscore", &_recoPFJet_bh_CSVscore, "recoPFJet_bh_e/F");
 
    tree_new[i]->Branch("recoPFJet_q1_e",        &_recoPFJet_q1_e,        "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_px",       &_recoPFJet_q1_px,       "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_py",       &_recoPFJet_q1_py,       "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_pz",       &_recoPFJet_q1_pz,       "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_pt",       &_recoPFJet_q1_pt,       "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_eta",      &_recoPFJet_q1_eta,      "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_phi",      &_recoPFJet_q1_phi,      "recoPFJet_q1_e/F");
    tree_new[i]->Branch("recoPFJet_q1_CSVscore", &_recoPFJet_q1_CSVscore, "recoPFJet_q1_e/F");

    tree_new[i]->Branch("recoPFJet_q2_e",        &_recoPFJet_q2_e,        "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_px",       &_recoPFJet_q2_px,       "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_py",       &_recoPFJet_q2_py,       "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_pz",       &_recoPFJet_q2_pz,       "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_pt",       &_recoPFJet_q2_pt,       "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_eta",      &_recoPFJet_q2_eta,      "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_phi",      &_recoPFJet_q2_phi,      "recoPFJet_q2_e/F");
    tree_new[i]->Branch("recoPFJet_q2_CSVscore", &_recoPFJet_q2_CSVscore, "recoPFJet_q2_e/F");

    tree_new[i]->Branch("recoPFJet_bl_e",        &_recoPFJet_bl_e,        "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_px",       &_recoPFJet_bl_px,       "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_py",       &_recoPFJet_bl_py,       "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_pz",       &_recoPFJet_bl_pz,       "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_pt",       &_recoPFJet_bl_pt,       "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_eta",      &_recoPFJet_bl_eta,      "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_phi",      &_recoPFJet_bl_phi,      "recoPFJet_bl_e/F");
    tree_new[i]->Branch("recoPFJet_bl_CSVscore", &_recoPFJet_bl_CSVscore, "recoPFJet_bl_e/F");

    tree_new[i]->Branch("recolep_lt_pdg",   &_recolep_lt_pdg,   "recolep_lt_pdg/I");
    tree_new[i]->Branch("recolep_lt_e",   &_recolep_lt_e,   "recolep_lt_e/F");
    tree_new[i]->Branch("recolep_lt_px",  &_recolep_lt_px,  "recolep_lt_e/F");
    tree_new[i]->Branch("recolep_lt_py",  &_recolep_lt_py,  "recolep_lt_e/F");
    tree_new[i]->Branch("recolep_lt_pz",  &_recolep_lt_pz,  "recolep_lt_e/F");
    tree_new[i]->Branch("recolep_lt_pt",  &_recolep_lt_pt,  "recolep_lt_e/F");
    tree_new[i]->Branch("recolep_lt_eta", &_recolep_lt_eta, "recolep_lt_e/F");
    tree_new[i]->Branch("recolep_lt_phi", &_recolep_lt_phi, "recolep_lt_e/F");

    tree_new[i]->Branch("recolep_tauH_pdg",   &_recolep_tauH_pdg,   "recolep_tauH_pdg/I");
    tree_new[i]->Branch("recolep_tauH_e",   &_recolep_tauH_e,   "recolep_tauH_e/F");
    tree_new[i]->Branch("recolep_tauH_px",  &_recolep_tauH_px,  "recolep_tauH_e/F");
    tree_new[i]->Branch("recolep_tauH_py",  &_recolep_tauH_py,  "recolep_tauH_e/F");
    tree_new[i]->Branch("recolep_tauH_pz",  &_recolep_tauH_pz,  "recolep_tauH_e/F");
    tree_new[i]->Branch("recolep_tauH_pt",  &_recolep_tauH_pt,  "recolep_tauH_e/F");
    tree_new[i]->Branch("recolep_tauH_eta", &_recolep_tauH_eta, "recolep_tauH_e/F");
    tree_new[i]->Branch("recolep_tauH_phi", &_recolep_tauH_phi, "recolep_tauH_e/F");

    tree_new[i]->Branch("recotauh_tauH_e",   &_recotauh_tauH_e,   "recotauh_tauH_e/F");
    tree_new[i]->Branch("recotauh_tauH_px",  &_recotauh_tauH_px,  "recotauh_tauH_e/F");
    tree_new[i]->Branch("recotauh_tauH_py",  &_recotauh_tauH_py,  "recotauh_tauH_e/F");
    tree_new[i]->Branch("recotauh_tauH_pz",  &_recotauh_tauH_pz,  "recotauh_tauH_e/F");
    tree_new[i]->Branch("recotauh_tauH_pt",  &_recotauh_tauH_pt,  "recotauh_tauH_e/F");
    tree_new[i]->Branch("recotauh_tauH_eta", &_recotauh_tauH_eta, "recotauh_tauH_e/F");
    tree_new[i]->Branch("recotauh_tauH_phi", &_recotauh_tauH_phi, "recotauh_tauH_e/F");

    tree_new[i]->Branch("m_top_had", &_m_top_had, "m_top_had/F");
    tree_new[i]->Branch("m_top_had_low", &_m_top_had_low, "m_top_had_low/F");
    tree_new[i]->Branch("m_top_had_high", &_m_top_had_high, "m_top_had_high/F");
    tree_new[i]->Branch("m_W_had", &_m_W_had, "m_W_had/F");
    tree_new[i]->Branch("m_W_had_low", &_m_W_had_low, "m_W_had_low/F");
    tree_new[i]->Branch("m_W_had_high", &_m_W_had_high, "m_W_had_high/F");
    tree_new[i]->Branch("m_blep_top", &_m_blep_top, "m_blep_top/F");
    tree_new[i]->Branch("m_blep_top_low", &_m_blep_top_low, "m_blep_top_low/F");
    tree_new[i]->Branch("m_taulep_H", &_m_taulep_H, "m_taulep_H/F");
	    
    tree_new[i]->Branch("missing_jet_perm", &_missing_jet_perm, "missing_jet_perm/I");
    tree_new[i]->Branch("perm_passing_cuts", &_perm_passing_cuts, "perm_passing_cuts/O");
    tree_new[i]->Branch("perm_MEM_sel", &_perm_MEM_sel, "perm_MEM_sel/O");



  }

  tree_event->Branch("n_perm_full", &_n_perm_full, "n_perm_full/I");
  tree_event->Branch("n_perm_full_passing_cuts", &_n_perm_full_passing_cuts, "n_perm_full_passing_cuts/I");
  tree_event->Branch("n_perm_missing", &_n_perm_missing, "n_perm_missing/I");
  tree_event->Branch("n_perm_missing_passing_cuts", &_n_perm_missing_passing_cuts, "n_perm_missing_passing_cuts/I");

  tree_event->Branch("MEM_category", &_MEM_category, "MEM_category/I");
  tree_event->Branch("n_perm_MEM_sel_passing_cuts", &_n_perm_MEM_sel_passing_cuts, "n_perm_MEM_sel_passing_cuts/I");
  tree_event->Branch("good_perm_category", &_good_perm_category, "good_perm_category/I");


  cout<<"nentries="<<nentries<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _genbh_e = -9999;
    _genbh_px = -9999;
    _genbh_py = -9999;
    _genbh_pz = -9999;
    _genbh_pt = -9999;
    _genbh_eta = -9999;
    _genbh_phi = -9999;
    _genbh_i_recoPFJet_btag_matched = -9999;

    _genq1_pdg = -9999;
    _genq1_e = -9999;
    _genq1_px = -9999;
    _genq1_py = -9999;
    _genq1_pz = -9999;
    _genq1_pt = -9999;
    _genq1_eta = -9999;
    _genq1_i_recoPFJet_untag_matched = -9999;

    _genq2_pdg = -9999;
    _genq2_e = -9999;
    _genq2_px = -9999;
    _genq2_py = -9999;
    _genq2_pz = -9999;
    _genq2_pt = -9999;
    _genq2_eta = -9999;
    _genq2_phi = -9999;
    _genq2_i_recoPFJet_untag_matched = -9999;

    _genbl_e = -9999;
    _genbl_px = -9999;
    _genbl_py = -9999;
    _genbl_pz = -9999;
    _genbl_pt = -9999;
    _genbl_eta = -9999;
    _genbl_phi = -9999;
    _genbl_i_recoPFJet_btag_matched = -9999;

    _genlt_pdg = -9999;
    _genlt_e = -9999;
    _genlt_px = -9999;
    _genlt_py = -9999;
    _genlt_pz = -9999;
    _genlt_pt = -9999;
    _genlt_eta = -9999;
    _genlt_phi = -9999;
    _genlt_i_recolep_sel_matched = -9999;

    _genltau_pdg = -9999;
    _genltau_e = -9999;
    _genltau_px = -9999;
    _genltau_py = -9999;
    _genltau_pz = -9999;
    _genltau_pt = -9999;
    _genltau_eta = -9999;
    _genltau_phi = -9999;
    _genltau_i_recolep_sel_matched = -9999;

    _genpi_e = -9999;
    _genpi_px = -9999;
    _genpi_py = -9999;
    _genpi_pz = -9999;
    _genpi_pt = -9999;
    _genpi_eta = -9999;
    _genpi_phi = -9999;
    _genpi_i_recotauh_sel_matched = -9999;



    _recoPFJet_bh_e = -9999;
    _recoPFJet_bh_px = -9999;
    _recoPFJet_bh_py = -9999;
    _recoPFJet_bh_pz = -9999;
    _recoPFJet_bh_pt = -9999; 
    _recoPFJet_bh_eta = -9999;
    _recoPFJet_bh_phi = -9999;
    _recoPFJet_bh_CSVscore = -9999;
     
    _recoPFJet_q1_e = -9999;
    _recoPFJet_q1_px = -9999;
    _recoPFJet_q1_py = -9999;
    _recoPFJet_q1_pz = -9999;
    _recoPFJet_q1_pt = -9999; 
    _recoPFJet_q1_eta = -9999;
    _recoPFJet_q1_phi = -9999;
    _recoPFJet_q1_CSVscore = -9999;
    
    _recoPFJet_q2_e = -9999;
    _recoPFJet_q2_px = -9999;
    _recoPFJet_q2_py = -9999;
    _recoPFJet_q2_pz = -9999;
    _recoPFJet_q2_pt = -9999; 
    _recoPFJet_q2_eta = -9999;
    _recoPFJet_q2_phi = -9999;
    _recoPFJet_q2_CSVscore = -9999;
    
    _recoPFJet_bl_e = -9999;
    _recoPFJet_bl_px = -9999;
    _recoPFJet_bl_py = -9999;
    _recoPFJet_bl_pz = -9999;
    _recoPFJet_bl_pt = -9999; 
    _recoPFJet_bl_eta = -9999;
    _recoPFJet_bl_phi = -9999;
    _recoPFJet_bl_CSVscore = -9999;
    
    _recolep_lt_pdg = -9999;
    _recolep_lt_e = -9999;
    _recolep_lt_px = -9999;
    _recolep_lt_py = -9999;
    _recolep_lt_pz = -9999;
    _recolep_lt_pt = -9999; 
    _recolep_lt_eta = -9999;
    _recolep_lt_phi = -9999;
    
    _recolep_tauH_pdg = -9999;
    _recolep_tauH_e = -9999;
    _recolep_tauH_px = -9999;
    _recolep_tauH_py = -9999;
    _recolep_tauH_pz = -9999;
    _recolep_tauH_pt = -9999; 
    _recolep_tauH_eta = -9999;
    _recolep_tauH_phi = -9999;
    
    _recotauh_tauH_e = -9999;
    _recotauh_tauH_px = -9999;
    _recotauh_tauH_py = -9999;
    _recotauh_tauH_pz = -9999;
    _recotauh_tauH_pt = -9999; 
    _recotauh_tauH_eta = -9999;
    _recotauh_tauH_phi = -9999;
    
    _m_top_had = -9999;
    _m_W_had = -9999;
    _m_blep_top = -9999;
    _m_taulep_H = -9999;
     
    _missing_jet_perm = -9999;
    _perm_passing_cuts = 0;
    _perm_MEM_sel = 0;
    
    _n_perm_full = -9999;
    _n_perm_full_passing_cuts = -9999;
    _n_perm_missing = -9999;
    _n_perm_missing_passing_cuts = -9999;

    _MEM_category = -9999;
    _n_perm_MEM_sel_passing_cuts = -9999;
    _good_perm_category = -9999;


    _gentop_e = 0;
    _gentop_px = 0;
    _gentop_py = 0;
    _gentop_pz = 0;
    _gentop_decayMode = 0;

    _genW_TopMothInd = 0;

    _genH_e = 0;
    _genH_px = 0;
    _genH_py = 0;
    _genH_pz = 0;
    _genH_decayMode = 0;

    _genb_e = 0;
    _genb_px = 0;
    _genb_py = 0;
    _genb_pz = 0;
    _genb_TopMothInd = 0;
    _genb_WMothInd = 0;
    _genb_flags = 0;

    _genq_e = 0;
    _genq_px = 0;
    _genq_py = 0;
    _genq_pz = 0;
    _genq_pt = 0;
    _genq_pdg = 0;
    _genq_TopMothInd = 0;
    _genq_WMothInd = 0;
    _genq_flags = 0;
    
    _gentau_flags = 0;
    _gentau_HMothInd = 0;
    _gentau_TopMothInd = 0;
    _gentau_decayMode = 0;
    
    _genlep_e = 0;
    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_TopMothInd = 0;
    _genlep_WMothInd = 0;
    _genlep_TauMothInd = 0;
    _genlep_flags = 0;
    _genlep_pdg = 0;
  
    _gentauh_e = 0;
    _gentauh_px = 0;
    _gentauh_py = 0;
    _gentauh_pz = 0;
    _gentauh_TauMothInd = 0;
    _gentauh_flags = 0;

    _recoPFJet_btag_e = 0;
    _recoPFJet_btag_px = 0;
    _recoPFJet_btag_py = 0;
    _recoPFJet_btag_pz = 0;
    _recoPFJet_btag_CSVscore = 0;

    _recoPFJet_untag_e = 0;
    _recoPFJet_untag_px = 0;
    _recoPFJet_untag_py = 0;
    _recoPFJet_untag_pz = 0;
    _recoPFJet_untag_CSVscore = 0;

    _recoPFJet_untag_Wtag_e = 0;
    _recoPFJet_untag_Wtag_px = 0;
    _recoPFJet_untag_Wtag_py = 0;
    _recoPFJet_untag_Wtag_pz = 0;
    _recoPFJet_untag_Wtag_CSVscore = 0;
    
    _recolep_sel_e = 0;
    _recolep_sel_px = 0;
    _recolep_sel_py = 0;
    _recolep_sel_pz = 0;
    _recolep_sel_pdg = 0;

    _recotauh_sel_e = 0;
    _recotauh_sel_px = 0;
    _recotauh_sel_py = 0;
    _recotauh_sel_pz = 0;

    _category = 0;


    tree->GetEntry(i);

    bool top0_had = (*_gentop_decayMode)[0]==0;
    bool top1_had = (*_gentop_decayMode)[1]==0;
    bool top0_lep = (*_gentop_decayMode)[0]==1 || (*_gentop_decayMode)[0]==2 ;
    bool top1_lep = (*_gentop_decayMode)[1]==1 || (*_gentop_decayMode)[1]==2 ;
    bool H_to_ltau =  (*_genH_decayMode)[1]==0 || (*_genH_decayMode)[1]==1 ;
    

    if( ! ( ( (top0_had && top1_lep) || (top1_had && top0_lep) ) && H_to_ltau ) )
      continue;

    if( _category!=11 )
      continue;



    //Tops

    int itop_tl = 0;
    int itop_th = 1;
    if( (*_gentop_decayMode)[0]==0 ){
      itop_tl = 1;
      itop_th = 0;
    }

    //b's

    int ibl = -1;
    int ibh = -1;

    for(unsigned int ib=0; ib<(*_genb_e).size(); ib++){

      bool isFromHardProcess = ( (*_genb_flags)[ib] >> 8 ) & 1;
      int TopMothInd = (*_genb_TopMothInd)[ib];
      int WMothInd = (*_genb_WMothInd)[ib];

      if( !( TopMothInd>-1 && WMothInd==-1 && isFromHardProcess ) )
	continue;
      
      if(TopMothInd==itop_tl)
	ibl = ib;
      else if(TopMothInd==itop_th)
	ibh = ib;

    }
    

    TLorentzVector genbl_tlv((*_genb_px)[ibl],(*_genb_py)[ibl],(*_genb_pz)[ibl],(*_genb_e)[ibl]);
    
    _genbl_e = genbl_tlv.E();
    _genbl_px = genbl_tlv.Px();
    _genbl_py = genbl_tlv.Py();
    _genbl_pz = genbl_tlv.Pz();
    _genbl_pt = genbl_tlv.Pt();
    _genbl_eta = genbl_tlv.Eta();
    _genbl_phi = genbl_tlv.Phi();

    TLorentzVector genbh_tlv((*_genb_px)[ibh],(*_genb_py)[ibh],(*_genb_pz)[ibh],(*_genb_e)[ibh]);
    
    _genbh_e = genbh_tlv.E();
    _genbh_px = genbh_tlv.Px();
    _genbh_py = genbh_tlv.Py();
    _genbh_pz = genbh_tlv.Pz();
    _genbh_pt = genbh_tlv.Pt();
    _genbh_eta = genbh_tlv.Eta();
    _genbh_phi = genbh_tlv.Phi();


    float min_dR_bh_bjet = 9999.;
    float min_dR_bl_bjet = 9999.;

    for(unsigned int i_bjet=0; i_bjet<(*_recoPFJet_btag_e).size(); i_bjet++){

      TLorentzVector bjet_tlv((*_recoPFJet_btag_px)[i_bjet], (*_recoPFJet_btag_py)[i_bjet], (*_recoPFJet_btag_pz)[i_bjet], (*_recoPFJet_btag_e)[i_bjet]);

      float dR = bjet_tlv.DeltaR(genbh_tlv);

      if(dR<min(float(0.4),min_dR_bh_bjet)){
	min_dR_bh_bjet = dR;
	_genbh_i_recoPFJet_btag_matched = i_bjet;
      }

      dR = bjet_tlv.DeltaR(genbl_tlv);

      if(dR<min(float(0.4),min_dR_bl_bjet)){
	min_dR_bl_bjet = dR;
	_genbl_i_recoPFJet_btag_matched = i_bjet;
      }

    }


    //W's

    int iWl = 0;
    int iWh = 1;
    if( (*_genW_TopMothInd)[0]==itop_th ){
      iWl = 1;
      iWh = 0;
    }
    
    

    //Light quarks

    int iq1=-1;
    int iq2=-1;

    for(unsigned int iq=0; iq<(*_genq_e).size(); iq++){

      bool isFromHardProcess = ( (*_genq_flags)[iq] >> 8 ) & 1;
      int WMothInd = (*_genq_TopMothInd)[iq];

      if( !( WMothInd==iWh && isFromHardProcess ) )
	continue;
     
      if(iq1==-1)
	iq1=iq;
      else
	iq2=iq;

    }    

    if( (*_genq_pt)[iq1] < (*_genq_pt)[iq2] ){
      int iq_temp = iq2;
      iq2 = iq1;
      iq1 = iq_temp;
    }

    TLorentzVector genq1_tlv((*_genq_px)[iq1],(*_genq_py)[iq1],(*_genq_pz)[iq1],(*_genq_e)[iq1]);

    _genq1_pdg = (*_genq_pdg)[iq1];
    _genq1_e = genq1_tlv.E();
    _genq1_px = genq1_tlv.Px();
    _genq1_py = genq1_tlv.Py();
    _genq1_pz = genq1_tlv.Pz();
    _genq1_eta = genq1_tlv.Pt();
    _genq1_phi = genq1_tlv.Eta();


    TLorentzVector genq2_tlv((*_genq_px)[iq2],(*_genq_py)[iq2],(*_genq_pz)[iq2],(*_genq_e)[iq2]);

    _genq2_pdg = (*_genq_pdg)[iq2];
    _genq2_e = genq2_tlv.E();
    _genq2_px = genq2_tlv.Px();
    _genq2_py = genq2_tlv.Py();
    _genq2_pz = genq2_tlv.Pz();
    _genq2_eta = genq2_tlv.Pt();
    _genq2_phi = genq2_tlv.Eta();


    float min_dR_q1_jet = 9999.;
    float min_dR_q2_jet = 9999.;

    for(unsigned int i_jet=0; i_jet<(*_recoPFJet_untag_e).size(); i_jet++){

      TLorentzVector jet_tlv((*_recoPFJet_untag_px)[i_jet], (*_recoPFJet_untag_py)[i_jet], (*_recoPFJet_untag_pz)[i_jet], (*_recoPFJet_untag_e)[i_jet]);

      float dR = jet_tlv.DeltaR(genq1_tlv);

      if(dR<min(float(0.4),min_dR_q1_jet)){
	min_dR_q1_jet = dR;
	_genq1_i_recoPFJet_untag_matched = i_jet;
      }

      dR = jet_tlv.DeltaR(genq2_tlv);

      if(dR<min(float(0.4),min_dR_q2_jet)){
	min_dR_q2_jet = dR;
	_genq2_i_recoPFJet_untag_matched = i_jet;
      }

    }


    //tau's

    int itaulep=-1;
    int itauhad=-1;

    for(unsigned int itau=0; itau<(*_gentau_flags).size(); itau++){

      bool isFromHardProcess = ( (*_gentau_flags)[itau] >> 8 ) & 1;
      int HMothInd = (*_gentau_HMothInd)[itau];
      int decayMode = (*_gentau_decayMode)[itau];

      if( !( HMothInd==1 && isFromHardProcess ) )
	continue;
     
      if(decayMode==0 || decayMode==1)
	itaulep = itau;
      else
	itauhad = itau;

    }    

 


    // Leptons

    int ilep_top=-1;
    int ilep_tau=-1;

    for(unsigned int ilep=0; ilep<(*_genlep_e).size(); ilep++){

      bool isFromHardProcess = ( (*_genlep_flags)[ilep] >> 8 ) & 1;
      bool isDirectTauDecayProduct = ( (*_genlep_flags)[ilep] >> 4) & 1;
      bool isHardProcessTauDecayProduct = ( (*_genlep_flags)[ilep] >> 9) & 1;
      int TauMothInd = (*_genlep_TauMothInd)[ilep];
      int TopMothInd = (*_genlep_TopMothInd)[ilep];
     
      if( TopMothInd == itop_tl && isFromHardProcess)
	ilep_top = ilep;
      else if( TauMothInd == itaulep && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
	ilep_tau = ilep;

    }    

    TLorentzVector genlt_tlv((*_genlep_px)[ilep_top], (*_genlep_py)[ilep_top], (*_genlep_pz)[ilep_top], (*_genlep_e)[ilep_top]);

    _genlt_pdg = (*_genlep_pdg)[ilep_top];
    _genlt_e = genlt_tlv.E();
    _genlt_px = genlt_tlv.Px();
    _genlt_py = genlt_tlv.Py();
    _genlt_pz = genlt_tlv.Pz();
    _genlt_pt = genlt_tlv.Pt();
    _genlt_eta = genlt_tlv.Eta();
    _genlt_phi = genlt_tlv.Phi();

    TLorentzVector genltau_tlv((*_genlep_px)[ilep_tau], (*_genlep_py)[ilep_tau], (*_genlep_pz)[ilep_tau], (*_genlep_e)[ilep_tau]);

    _genltau_pdg = (*_genlep_pdg)[ilep_tau];
    _genltau_e = genltau_tlv.E();
    _genltau_px = genltau_tlv.Px();
    _genltau_py = genltau_tlv.Py();
    _genltau_pz = genltau_tlv.Pz();
    _genltau_pt = genltau_tlv.Pt();
    _genltau_eta = genltau_tlv.Eta();
    _genltau_phi = genltau_tlv.Phi();


    float min_dR_lt_lep = 9999.;
    float min_dR_ltau_lep = 9999.;

    for(unsigned int i_lep=0; i_lep<(*_recolep_sel_e).size(); i_lep++){

      TLorentzVector lep_tlv((*_recolep_sel_px)[i_lep], (*_recolep_sel_py)[i_lep], (*_recolep_sel_pz)[i_lep], (*_recolep_sel_e)[i_lep]);

      float dR = lep_tlv.DeltaR(genlt_tlv);

      if(dR<min(float(0.4),min_dR_lt_lep)){
	min_dR_lt_lep = dR;
	_genlt_i_recolep_sel_matched = i_lep;
      }

      dR = lep_tlv.DeltaR(genltau_tlv);

      if(dR<min(float(0.4),min_dR_ltau_lep)){
	min_dR_ltau_lep = dR;
	_genltau_i_recolep_sel_matched = i_lep;
      }

    }

    // Tauh

    int ipi=-1;

    for(unsigned int itauh=0; itauh<(*_gentauh_e).size(); itauh++){

      int flag_Mother = (*_gentau_flags)[(*_gentauh_TauMothInd)[itauh]];
      bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
      int TauMothInd = (*_gentauh_TauMothInd)[itauh];
     
      if( TauMothInd == itauhad && isMotherFromHardProcess )
	ipi = itauh;

    }    

    TLorentzVector genpi_tlv((*_gentauh_px)[ipi], (*_gentauh_py)[ipi], (*_gentauh_pz)[ipi], (*_gentauh_e)[ipi]);

    _genpi_e = genpi_tlv.E();
    _genpi_px = genpi_tlv.Px();
    _genpi_py = genpi_tlv.Py();
    _genpi_pz = genpi_tlv.Pz();
    _genpi_pt = genpi_tlv.Pt();
    _genpi_eta = genpi_tlv.Eta();
    _genpi_phi = genpi_tlv.Phi();


    float min_dR_pi_tauh = 9999.;

    for(unsigned int i_tauh=0; i_tauh<(*_recotauh_sel_e).size(); i_tauh++){

      TLorentzVector tauh_tlv((*_recotauh_sel_px)[i_tauh], (*_recotauh_sel_py)[i_tauh], (*_recotauh_sel_pz)[i_tauh], (*_recotauh_sel_e)[i_tauh]);

      float dR = tauh_tlv.DeltaR(genpi_tlv);

      if(dR<min(float(0.4),min_dR_pi_tauh)){
	min_dR_pi_tauh = dR;
	_genpi_i_recotauh_sel_matched = i_tauh;
      }

    }
    

    
    _n_perm_full = TMath::Binomial((*_recoPFJet_untag_e).size(),2) * 4;
    _n_perm_missing = (*_recoPFJet_untag_e).size() * 4;

    _n_perm_full_passing_cuts = 0;
    _n_perm_missing_passing_cuts = 0;
    _n_perm_MEM_sel_passing_cuts = 0;


    TLorentzVector jet1_MEM_sel((*_recoPFJet_untag_Wtag_px)[0],(*_recoPFJet_untag_Wtag_py)[0],(*_recoPFJet_untag_Wtag_pz)[0],(*_recoPFJet_untag_Wtag_e)[0]);
    TLorentzVector jet2_MEM_sel((*_recoPFJet_untag_Wtag_px)[1],(*_recoPFJet_untag_Wtag_py)[1],(*_recoPFJet_untag_Wtag_pz)[1],(*_recoPFJet_untag_Wtag_e)[1]);


    for(unsigned int i_bjet_bh=0; i_bjet_bh<(*_recoPFJet_btag_e).size(); i_bjet_bh++){
      
      TLorentzVector bjet_bh((*_recoPFJet_btag_px)[i_bjet_bh],(*_recoPFJet_btag_py)[i_bjet_bh],(*_recoPFJet_btag_pz)[i_bjet_bh],(*_recoPFJet_btag_e)[i_bjet_bh]);
      
      _recoPFJet_bh_e = bjet_bh.E();
      _recoPFJet_bh_px = bjet_bh.Px();
      _recoPFJet_bh_py = bjet_bh.Py();
      _recoPFJet_bh_pz = bjet_bh.Pz();
      _recoPFJet_bh_pt = bjet_bh.Pt(); 
      _recoPFJet_bh_eta = bjet_bh.Eta();
      _recoPFJet_bh_phi = bjet_bh.Phi();
      _recoPFJet_bh_CSVscore = (*_recoPFJet_btag_CSVscore)[i_bjet_bh];
      
      
      for(unsigned int i_bjet_bl=0; i_bjet_bl<(*_recoPFJet_btag_e).size(); i_bjet_bl++){
	if(i_bjet_bh==i_bjet_bl) continue;
	
	TLorentzVector bjet_bl((*_recoPFJet_btag_px)[i_bjet_bl],(*_recoPFJet_btag_py)[i_bjet_bl],(*_recoPFJet_btag_pz)[i_bjet_bl],(*_recoPFJet_btag_e)[i_bjet_bl]);
	
	_recoPFJet_bl_e = bjet_bl.E();
	_recoPFJet_bl_px = bjet_bl.Px();
	_recoPFJet_bl_py = bjet_bl.Py();
	_recoPFJet_bl_pz = bjet_bl.Pz();
	_recoPFJet_bl_pt = bjet_bl.Pt(); 
	_recoPFJet_bl_eta = bjet_bl.Eta();
	_recoPFJet_bl_phi = bjet_bl.Phi();
	_recoPFJet_bl_CSVscore = (*_recoPFJet_btag_CSVscore)[i_bjet_bl];
	

	for(unsigned int i_lep_lt=0; i_lep_lt<(*_recolep_sel_e).size(); i_lep_lt++){
	  
	  TLorentzVector lep_lt((*_recolep_sel_px)[i_lep_lt], (*_recolep_sel_py)[i_lep_lt], (*_recolep_sel_pz)[i_lep_lt], (*_recolep_sel_e)[i_lep_lt]);
	  
	  _recolep_lt_pdg = (*_recolep_sel_pdg)[i_lep_lt];
	  _recolep_lt_e = lep_lt.E();
	  _recolep_lt_px = lep_lt.Px();
	  _recolep_lt_py = lep_lt.Py();
	  _recolep_lt_pz = lep_lt.Pz();
	  _recolep_lt_pt = lep_lt.Pt();
	  _recolep_lt_eta = lep_lt.Eta();
	  _recolep_lt_phi = lep_lt.Phi();
	  
	  
	  for(unsigned int i_lep_ltau=0; i_lep_ltau<(*_recolep_sel_e).size(); i_lep_ltau++){
	    if(i_lep_ltau==i_lep_lt) continue;
	    
	    TLorentzVector lep_ltau((*_recolep_sel_px)[i_lep_ltau], (*_recolep_sel_py)[i_lep_ltau], (*_recolep_sel_pz)[i_lep_ltau], (*_recolep_sel_e)[i_lep_ltau]);
	     
	    _recolep_tauH_pdg = (*_recolep_sel_pdg)[i_lep_ltau];
	    _recolep_tauH_e = lep_ltau.E();
	    _recolep_tauH_px = lep_ltau.Px();
	    _recolep_tauH_py = lep_ltau.Py();
	    _recolep_tauH_pz = lep_ltau.Pz();
	    _recolep_tauH_pt = lep_ltau.Pt();
	    _recolep_tauH_eta = lep_ltau.Eta();
	    _recolep_tauH_phi = lep_ltau.Phi();
	    

	    for(unsigned int i_tauh=0; i_tauh<(*_recotauh_sel_e).size(); i_tauh++){
	      
	      TLorentzVector tauh((*_recotauh_sel_px)[i_tauh], (*_recotauh_sel_py)[i_tauh], (*_recotauh_sel_pz)[i_tauh], (*_recotauh_sel_e)[i_tauh]);
	      
	      _recotauh_tauH_e = tauh.E();
	      _recotauh_tauH_px = tauh.Px();
	      _recotauh_tauH_py = tauh.Py();
	      _recotauh_tauH_pz = tauh.Pz();
	      _recotauh_tauH_pt = tauh.Pt();
	      _recotauh_tauH_eta = tauh.Eta();
	      _recotauh_tauH_phi = tauh.Phi();
	      
	      for(unsigned int i_jet1=0; i_jet1<(*_recoPFJet_untag_e).size(); i_jet1++){
		
		TLorentzVector jet1((*_recoPFJet_untag_px)[i_jet1],(*_recoPFJet_untag_py)[i_jet1],(*_recoPFJet_untag_pz)[i_jet1],(*_recoPFJet_untag_e)[i_jet1]);
		
		_recoPFJet_q1_e = jet1.E();
		_recoPFJet_q1_px = jet1.Px();
		_recoPFJet_q1_py = jet1.Py();
		_recoPFJet_q1_pz = jet1.Pz();
		_recoPFJet_q1_pt = jet1.Pt();
		_recoPFJet_q1_eta = jet1.Eta();
		_recoPFJet_q1_phi = jet1.Phi();
		_recoPFJet_q1_CSVscore = (*_recoPFJet_untag_CSVscore)[i_jet1];


      
		//No missing jet

		for(unsigned int i_jet2=i_jet1+1; i_jet2<(*_recoPFJet_untag_e).size(); i_jet2++){
		  
		  TLorentzVector jet2((*_recoPFJet_untag_px)[i_jet2],(*_recoPFJet_untag_py)[i_jet2],(*_recoPFJet_untag_pz)[i_jet2],(*_recoPFJet_untag_e)[i_jet2]);
		  
		  _recoPFJet_q2_e = jet2.E();
		  _recoPFJet_q2_px = jet2.Px();
		  _recoPFJet_q2_py = jet2.Py();
		  _recoPFJet_q2_pz = jet2.Pz();
		  _recoPFJet_q2_pt = jet2.Pt();
		  _recoPFJet_q2_eta = jet2.Eta();
		  _recoPFJet_q2_phi = jet2.Phi();
		  _recoPFJet_q2_CSVscore = (*_recoPFJet_untag_CSVscore)[i_jet2];
		  
		  
		  _m_top_had = (jet1+jet2+bjet_bh).M();
		  pair<double,double> m_top_had_low_up = mLow_mUp_TopHad(bjet_bh,jet1,jet2);
		  _m_top_had_low = m_top_had_low_up.first;
		  _m_top_had_high = m_top_had_low_up.second;
		  
		  _m_W_had = (jet1+jet2).M();
		  pair<double,double> m_W_had_low_up = mLow_mUp_WHad(jet1,jet2);
		  _m_W_had_low = m_W_had_low_up.first;
		  _m_W_had_high = m_W_had_low_up.second;

		  _m_blep_top = (bjet_bl+lep_lt).M();
		  _m_blep_top_low = mLow_blep_TopLep(bjet_bl,lep_lt);

		  _m_taulep_H = (lep_ltau+tauh).M();

		  _missing_jet_perm = 0;

		  if(_n_pair_Wtag_recoPFJet_untag>0 && ((jet1_MEM_sel.DeltaR(jet1)<0.1 && jet2_MEM_sel.DeltaR(jet2)<0.1) || (jet1_MEM_sel.DeltaR(jet2)<0.1 && jet2_MEM_sel.DeltaR(jet1)<0.1)) )
		      _perm_MEM_sel = true;
		    else
		      _perm_MEM_sel = false;

		  if(_m_top_had_low<173.2 && 173.2<_m_top_had_high && _m_W_had_low<80.4 && 80.4<_m_W_had_high && _m_blep_top_low<173.2 && _m_taulep_H<125){
		    _perm_passing_cuts = true;
		    _n_perm_full_passing_cuts++;
		  }
		  else
		    _perm_passing_cuts = false;

		  if(_perm_MEM_sel && _perm_passing_cuts)
		    _n_perm_MEM_sel_passing_cuts++;

		  if( _genbh_i_recoPFJet_btag_matched == i_bjet_bh
		      && _genbl_i_recoPFJet_btag_matched == i_bjet_bl
		      && _genlt_i_recolep_sel_matched == i_lep_lt
		      && _genltau_i_recolep_sel_matched == i_lep_ltau
		      && _genpi_i_recotauh_sel_matched == i_tauh
		      && ((_genq1_i_recoPFJet_untag_matched == i_jet1 && _genq2_i_recoPFJet_untag_matched == i_jet2) || (_genq1_i_recoPFJet_untag_matched == i_jet2 && _genq2_i_recoPFJet_untag_matched == i_jet1) ) ){		    

		    _good_perm_category=0;
		    tree_goodperm->Fill();

		  }
		  
		  else{		  

		    tree_badperm->Fill();

		  }

		  
		}


		//Missing jet

		_recoPFJet_q2_e = -9999;
		_recoPFJet_q2_px = -9999;
		_recoPFJet_q2_py = -9999;
		_recoPFJet_q2_pz = -9999;
		_recoPFJet_q2_pt = -9999;
		_recoPFJet_q2_eta = -9999;
		_recoPFJet_q2_phi = -9999;
		_recoPFJet_q2_CSVscore = -9999;
		  
		_m_top_had = (jet1+bjet_bh).M();
		_m_top_had_low = mLow_TopHad_missing_jet(bjet_bh,jet1);
		_m_top_had_high = -9999;

		_m_W_had = -9999;
		_m_blep_top = (bjet_bl+lep_lt).M();
		_m_blep_top_low = mLow_blep_TopLep(bjet_bl,lep_lt);
		_m_taulep_H = (lep_ltau+tauh).M();
		  
		_missing_jet_perm = 1;

		if(_n_pair_Wtag_recoPFJet_untag==0)
		    _perm_MEM_sel = true;
		  else
		    _perm_MEM_sel = false;

		if(_perm_MEM_sel && _perm_passing_cuts)
		    _n_perm_MEM_sel_passing_cuts++;

		if(_m_top_had_low<173.2 && _m_blep_top_low<173.2 && _m_taulep_H<125){
		    _perm_passing_cuts = true;
		    _n_perm_missing_passing_cuts++;
		  }
		  else
		    _perm_passing_cuts = false;

		if( _genbh_i_recoPFJet_btag_matched == i_bjet_bh
		    && _genbl_i_recoPFJet_btag_matched == i_bjet_bl
		    && _genlt_i_recolep_sel_matched == i_lep_lt
		    && _genltau_i_recolep_sel_matched == i_lep_ltau
		    && _genpi_i_recotauh_sel_matched == i_tauh
		    && ((_genq1_i_recoPFJet_untag_matched == i_jet1 && _genq2_i_recoPFJet_untag_matched<0) || (_genq1_i_recoPFJet_untag_matched<0 && _genq2_i_recoPFJet_untag_matched == i_jet1) ) ){	  
		  
		    _good_perm_category=1;
		    tree_goodperm->Fill();

		}
		  
		else
		  
		  tree_badperm->Fill();

 
	      }
	      
	    }
	    
	  }
	  
	}

      }

    }

    _MEM_category = (_n_pair_Wtag_recoPFJet_untag==0);    

    tree_event->Fill();

  }

  tree_event->Write();
  tree_goodperm->Write();
  tree_badperm->Write();

  f_new->Close();


  return;


}
