#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>

#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"



using namespace std;





void tau_tree_maker(TString filename_in, TString filename_out, TString treename){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  //Old branches used

  vector<float> *_genpart_e;
  vector<float> *_genpart_px;
  vector<float> *_genpart_py;
  vector<float> *_genpart_pz;
  vector<int> *_genpart_pdg;
  vector<int> *_genpart_TauGenDetailedDecayMode;
  vector<int> *_genpart_TauMothInd;

  tree->SetBranchAddress("genpart_e",&_genpart_e);
  tree->SetBranchAddress("genpart_px",&_genpart_px);
  tree->SetBranchAddress("genpart_py",&_genpart_py);
  tree->SetBranchAddress("genpart_pz",&_genpart_pz);
  tree->SetBranchAddress("genpart_pdg",&_genpart_pdg);
  tree->SetBranchAddress("genpart_TauGenDetailedDecayMode",&_genpart_TauGenDetailedDecayMode);
  tree->SetBranchAddress("genpart_TauMothInd",&_genpart_TauMothInd);


  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_new=new TTree("tau_tree","tau_tree");

  float _gentau_e;
  float _gentau_px;
  float _gentau_py;
  float _gentau_pz;
  float _gentau_pt;
  int _gentau_decayMode;
	
  float _gentauh_e;
  float _gentauh_px;
  float _gentauh_py;
  float _gentauh_pz;
  float _gentauh_pt;
  float _gentauh_m;
  int _gentauh_decayMode;
	
  float _gennu_e;
  float _gennu_px;
  float _gennu_py;
  float _gennu_pz;
  float _gennu_pt;
	
  float _gentauh_CM_e;
  float _gennu_CM_e;

  tree_new->Branch("gentau_e",&_gentau_e,"gentau_e/F");
  tree_new->Branch("gentau_px",&_gentau_px,"gentau_px/F");
  tree_new->Branch("gentau_py",&_gentau_py,"gentau_py/F");
  tree_new->Branch("gentau_pz",&_gentau_pz,"gentau_pz/F");
  tree_new->Branch("gentau_pt",&_gentau_pt,"gentau_pt/F");
  tree_new->Branch("gentau_decayMode",&_gentau_decayMode,"gentau_decayMode/I");

  tree_new->Branch("gentauh_e",&_gentauh_e,"gentauh_e/F");
  tree_new->Branch("gentauh_px",&_gentauh_px,"gentauh_px/F");
  tree_new->Branch("gentauh_py",&_gentauh_py,"gentauh_py/F");
  tree_new->Branch("gentauh_pz",&_gentauh_pz,"gentauh_pz/F");
  tree_new->Branch("gentauh_pt",&_gentauh_pt,"gentauh_pt/F");
  tree_new->Branch("gentauh_m",&_gentauh_m,"gentauh_m/F");
  tree_new->Branch("gentauh_decayMode",&_gentauh_decayMode,"gentauh_decayMode/I");

  tree_new->Branch("gennu_e",&_gennu_e,"gennu_e/F");
  tree_new->Branch("gennu_px",&_gennu_px,"gennu_px/F");
  tree_new->Branch("gennu_py",&_gennu_py,"gennu_py/F");
  tree_new->Branch("gennu_pz",&_gennu_pz,"gennu_pz/F");
  tree_new->Branch("gennu_pt",&_gennu_pt,"gennu_pt/F");

  tree_new->Branch("gentauh_CM_e",&_gentauh_CM_e,"gentauh_CM_e/F");
  tree_new->Branch("gennu_CM_e",&_gennu_CM_e,"gennu_CM_e/F");



  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _genpart_e = 0;
    _genpart_px = 0;
    _genpart_py = 0;
    _genpart_pz = 0;
    _genpart_pdg = 0;
    _genpart_TauGenDetailedDecayMode = 0;
    _genpart_TauMothInd = 0;

    _gentau_e = 0;
    _gentau_px = 0;
    _gentau_py = 0;
    _gentau_pz = 0;
    _gentau_pt = 0;
    _gentau_decayMode = 0;
    
    _gentauh_e = 0;
    _gentauh_px = 0;
    _gentauh_py = 0;
    _gentauh_pz = 0;
    _gentauh_m = 0;
    _gentauh_decayMode = 0;
    
    _gennu_e = 0;
    _gennu_px = 0;
    _gennu_py = 0;
    _gennu_pz = 0;
    _gennu_pt = 0;
     
    _gentauh_CM_e = 0;
    _gennu_CM_e = 0;

    tree->GetEntry(i);

    for(unsigned int j=0;j<(*_genpart_pdg).size();j++){

      if(abs((*_genpart_pdg)[j])!=66615) continue;

      TLorentzVector tauh((*_genpart_px)[j],(*_genpart_py)[j],(*_genpart_pz)[j],(*_genpart_e)[j]);
      
      int i_tau = (*_genpart_TauMothInd)[j];
      TLorentzVector tau((*_genpart_px)[i_tau],(*_genpart_py)[i_tau],(*_genpart_pz)[i_tau],(*_genpart_e)[i_tau]);

      TLorentzVector nu;

      for(unsigned int k=0;k<(*_genpart_pdg).size();k++){
	if(abs((*_genpart_pdg)[k])==16 && (*_genpart_TauMothInd)[k]==i_tau){
	    nu = TLorentzVector((*_genpart_px)[k],(*_genpart_py)[k],(*_genpart_pz)[k],(*_genpart_e)[k]);
	    break;
	  }
      }

      
      _gentau_e = tau.E();
      _gentau_px = tau.Px();
      _gentau_py = tau.Py();
      _gentau_pz = tau.Pz();
      _gentau_pt = tau.Pt();
      _gentau_decayMode = (*_genpart_TauGenDetailedDecayMode)[i_tau];
    
      _gentauh_e = tauh.E();
      _gentauh_px = tauh.Px();
      _gentauh_py = tauh.Py();
      _gentauh_pz = tauh.Pz();
      _gentauh_m = tauh.M();
      _gentauh_decayMode = (*_genpart_TauGenDetailedDecayMode)[i_tau];
    
      _gennu_e = nu.E();
      _gennu_px = nu.Px();
      _gennu_py = nu.Py();
      _gennu_pz = nu.Pz();
      _gennu_pt = nu.Pt();
     
      TVector3 boost = tau.BoostVector();
      TLorentzVector tauh_boosted=tauh;
      tauh_boosted.Boost(-boost);
      TLorentzVector nu_boosted=nu;
      nu_boosted.Boost(-boost);



      _gentauh_CM_e = tauh_boosted.E();
      _gennu_CM_e = nu_boosted.E();

      tree_new->Fill();

    }  

  }

  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}



