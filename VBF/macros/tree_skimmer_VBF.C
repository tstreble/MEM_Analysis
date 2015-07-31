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


#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;




void skim_tree(TString sample){

  TString file_in="ntuple_VBF_dRveto_gen.root";    
  TString file_out="ntuple_VBF_dRveto_gen_skimmed.root";    
  TString dir;

  if(sample=="VBF"){
    dir="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/";
  }


  TChain * tree = new TChain("HTauTauTree");
  tree->Add(dir+file_in);

  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir+file_out);
  if(f_new!=0){
    cout<<dir+file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir+file_out,"RECREATE");



  //Old branches used
  int _n_genlep;
  vector<int>* _genlep_pdg;
  vector<int>* _genlep_charge;
  vector<float>* _genlep_e;
  vector<float>* _genlep_px;
  vector<float>* _genlep_py;
  vector<float>* _genlep_pz;
  vector<float>* _genlep_pt;
  vector<float>* _genlep_eta;
  vector<float>* _genlep_phi;
  vector<int>* _genlep_flags;  
  vector<int>* _genlep_TauMothInd;

  int _n_gentauh;
  vector<int>* _gentauh_charge;
  vector<float>* _gentauh_e;
  vector<float>* _gentauh_px;
  vector<float>* _gentauh_py;
  vector<float>* _gentauh_pz;
  vector<float>* _gentauh_pt;
  vector<float>* _gentauh_eta;
  vector<float>* _gentauh_phi;
  vector<int>* _gentauh_flags;  
  vector<int>* _gentauh_TauMothInd;

  vector<int>* _genH_decayMode;

  int _n_gentau;
  vector<int>* _gentau_decayMode;
  vector<int>* _gentau_charge;
  vector<float>* _gentau_e;
  vector<float>* _gentau_px;
  vector<float>* _gentau_py;
  vector<float>* _gentau_pz;
  vector<float>* _gentau_pt;
  vector<float>* _gentau_eta;
  vector<float>* _gentau_phi;
  vector<int>* _gentau_flags;  
  vector<int>* _gentau_HMothInd;

 
  int _n_genb;
  vector<int>* _genb_pdg;
  vector<float>* _genb_e;
  vector<float>* _genb_px;
  vector<float>* _genb_py;
  vector<float>* _genb_pz;
  vector<float>* _genb_pt;
  vector<float>* _genb_eta;
  vector<float>* _genb_phi;
  vector<int>* _genb_flags;  

  int _n_genq;
  vector<int>* _genq_pdg;
  vector<float>* _genq_e;
  vector<float>* _genq_px;
  vector<float>* _genq_py;
  vector<float>* _genq_pz;
  vector<float>* _genq_pt;
  vector<float>* _genq_eta;
  vector<float>* _genq_phi;
  vector<int>* _genq_flags;  

  int _n_gennu;
  vector<int>* _gennu_pdg;
  vector<float>* _gennu_e;
  vector<float>* _gennu_px;
  vector<float>* _gennu_py;
  vector<float>* _gennu_pz;
  vector<float>* _gennu_pt;
  vector<float>* _gennu_eta;
  vector<float>* _gennu_phi;
  vector<int>* _gennu_flags;  
  vector<int>* _gennu_TauMothInd; //-1 if not from tau

  vector<float> *_daughters_e;
  vector<float> *_daughters_px;
  vector<float> *_daughters_py;
  vector<float> *_daughters_pz;
  vector<int> *_PDGIdDaughters;

  tree->SetBranchAddress("n_genlep",&_n_genlep);
  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);
  tree->SetBranchAddress("genlep_charge",&_genlep_charge);
  tree->SetBranchAddress("genlep_e",&_genlep_e);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_pt",&_genlep_pt);
  tree->SetBranchAddress("genlep_eta",&_genlep_eta);
  tree->SetBranchAddress("genlep_phi",&_genlep_phi);
  tree->SetBranchAddress("genlep_flags",&_genlep_flags);
  tree->SetBranchAddress("genlep_TauMothInd",&_genlep_TauMothInd);

  tree->SetBranchAddress("n_gentauh",&_n_gentauh);
  tree->SetBranchAddress("gentauh_charge",&_gentauh_charge);
  tree->SetBranchAddress("gentauh_e",&_gentauh_e);
  tree->SetBranchAddress("gentauh_px",&_gentauh_px);
  tree->SetBranchAddress("gentauh_py",&_gentauh_py);
  tree->SetBranchAddress("gentauh_pz",&_gentauh_pz);
  tree->SetBranchAddress("gentauh_pt",&_gentauh_pt);
  tree->SetBranchAddress("gentauh_eta",&_gentauh_eta);
  tree->SetBranchAddress("gentauh_phi",&_gentauh_phi);
  tree->SetBranchAddress("gentauh_flags",&_gentauh_flags);
  tree->SetBranchAddress("gentauh_TauMothInd",&_gentauh_TauMothInd);

  tree->SetBranchAddress("genH_decayMode",&_genH_decayMode);

  tree->SetBranchAddress("n_gentau",&_n_gentau);
  tree->SetBranchAddress("gentau_charge",&_gentau_charge);
  tree->SetBranchAddress("gentau_decayMode",&_gentau_decayMode);
  tree->SetBranchAddress("gentau_e",&_gentau_e);
  tree->SetBranchAddress("gentau_px",&_gentau_px);
  tree->SetBranchAddress("gentau_py",&_gentau_py);
  tree->SetBranchAddress("gentau_pz",&_gentau_pz);
  tree->SetBranchAddress("gentau_pt",&_gentau_pt);
  tree->SetBranchAddress("gentau_eta",&_gentau_eta);
  tree->SetBranchAddress("gentau_phi",&_gentau_phi);
  tree->SetBranchAddress("gentau_flags",&_gentau_flags);
  tree->SetBranchAddress("gentau_HMothInd",&_gentau_HMothInd);


  tree->SetBranchAddress("n_genb",&_n_genb);
  tree->SetBranchAddress("genb_pdg",&_genb_pdg);
  tree->SetBranchAddress("genb_e",&_genb_e);
  tree->SetBranchAddress("genb_px",&_genb_px);
  tree->SetBranchAddress("genb_py",&_genb_py);
  tree->SetBranchAddress("genb_pz",&_genb_pz);
  tree->SetBranchAddress("genb_pt",&_genb_pt);
  tree->SetBranchAddress("genb_eta",&_genb_eta);
  tree->SetBranchAddress("genb_phi",&_genb_phi);
  tree->SetBranchAddress("genb_flags",&_genb_flags);

  tree->SetBranchAddress("n_genq",&_n_genq);
  tree->SetBranchAddress("genq_pdg",&_genq_pdg);
  tree->SetBranchAddress("genq_e",&_genq_e);
  tree->SetBranchAddress("genq_px",&_genq_px);
  tree->SetBranchAddress("genq_py",&_genq_py);
  tree->SetBranchAddress("genq_pz",&_genq_pz);
  tree->SetBranchAddress("genq_pt",&_genq_pt);
  tree->SetBranchAddress("genq_eta",&_genq_eta);
  tree->SetBranchAddress("genq_phi",&_genq_phi);
  tree->SetBranchAddress("genq_flags",&_genq_flags);

  tree->SetBranchAddress("n_gennu",&_n_gennu);
  tree->SetBranchAddress("gennu_pdg",&_gennu_pdg);
  tree->SetBranchAddress("gennu_e",&_gennu_e);
  tree->SetBranchAddress("gennu_px",&_gennu_px);
  tree->SetBranchAddress("gennu_py",&_gennu_py);
  tree->SetBranchAddress("gennu_pz",&_gennu_pz);
  tree->SetBranchAddress("gennu_pt",&_gennu_pt);
  tree->SetBranchAddress("gennu_eta",&_gennu_eta);
  tree->SetBranchAddress("gennu_phi",&_gennu_phi);
  tree->SetBranchAddress("gennu_flags",&_gennu_flags);
  tree->SetBranchAddress("gennu_TauMothInd",&_gennu_TauMothInd);

  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);




  TTree* tree_new=tree->GetTree()->CloneTree(0);


  int _gentaulep_fromH_charge;
  float _gentaulep_fromH_e;
  float _gentaulep_fromH_px;
  float _gentaulep_fromH_py;
  float _gentaulep_fromH_pz;
  float _gentaulep_fromH_pt;
  float _gentaulep_fromH_eta;
  float _gentaulep_fromH_phi;
  int _gentaulep_fromH_flags;

  int _gentauhad_fromH_charge;
  float _gentauhad_fromH_e;
  float _gentauhad_fromH_px;
  float _gentauhad_fromH_py;
  float _gentauhad_fromH_pz;
  float _gentauhad_fromH_pt;
  float _gentauhad_fromH_eta;
  float _gentauhad_fromH_phi;
  int _gentauhad_fromH_flags;
  
  int _genltau_pdg;
  int _genltau_charge;
  float _genltau_e;
  float _genltau_px;
  float _genltau_py;
  float _genltau_pz;
  float _genltau_pt;
  float _genltau_eta;
  float _genltau_phi;
  int _genltau_flags;
  int _genltau_i_daughter_matched;
  float _genltau_dR_daughter_matched;

  int _gennu1taul_pdg;
  float _gennu1taul_e;
  float _gennu1taul_px;
  float _gennu1taul_py;
  float _gennu1taul_pz;
  float _gennu1taul_pt;
  float _gennu1taul_eta;
  float _gennu1taul_phi;
  int _gennu1taul_flags;

  int _gennu2taul_pdg;
  float _gennu2taul_e;
  float _gennu2taul_px;
  float _gennu2taul_py;
  float _gennu2taul_pz;
  float _gennu2taul_pt;
  float _gennu2taul_eta;
  float _gennu2taul_phi;
  int _gennu2taul_flags;

  int _genpi_charge;
  float _genpi_e;
  float _genpi_px;
  float _genpi_py;
  float _genpi_pz;
  float _genpi_pt;
  float _genpi_eta;
  float _genpi_phi;
  int _genpi_flags;
  int _genpi_i_daughter_matched;
  float _genpi_dR_daughter_matched;

  int _gennutauh_pdg;
  float _gennutauh_e;
  float _gennutauh_px;
  float _gennutauh_py;
  float _gennutauh_pz;
  float _gennutauh_pt;
  float _gennutauh_eta;
  float _gennutauh_phi;
  int _gennutauh_flags;

  float _genMET;
  float _genMET_phi;

  tree_new->Branch("gentaulep_fromH_charge",&_gentaulep_fromH_charge,"gentaulep_fromH_charge/I");
  tree_new->Branch("gentaulep_fromH_e",&_gentaulep_fromH_e,"gentaulep_fromH_e/F");
  tree_new->Branch("gentaulep_fromH_px",&_gentaulep_fromH_px,"gentaulep_fromH_px/F");
  tree_new->Branch("gentaulep_fromH_py",&_gentaulep_fromH_py,"gentaulep_fromH_py/F");
  tree_new->Branch("gentaulep_fromH_pz",&_gentaulep_fromH_pz,"gentaulep_fromH_pz/F");
  tree_new->Branch("gentaulep_fromH_pt",&_gentaulep_fromH_pt,"gentaulep_fromH_pt/F");
  tree_new->Branch("gentaulep_fromH_eta",&_gentaulep_fromH_eta,"gentaulep_fromH_eta/F");
  tree_new->Branch("gentaulep_fromH_phi",&_gentaulep_fromH_phi,"gentaulep_fromH_phi/F");
  tree_new->Branch("gentaulep_fromH_flags",&_gentaulep_fromH_flags,"gentaulep_fromH_flags/I");

  tree_new->Branch("gentauhad_fromH_charge",&_gentauhad_fromH_charge,"gentauhad_fromH_charge/I");
  tree_new->Branch("gentauhad_fromH_e",&_gentauhad_fromH_e,"gentauhad_fromH_e/F");
  tree_new->Branch("gentauhad_fromH_px",&_gentauhad_fromH_px,"gentauhad_fromH_px/F");
  tree_new->Branch("gentauhad_fromH_py",&_gentauhad_fromH_py,"gentauhad_fromH_py/F");
  tree_new->Branch("gentauhad_fromH_pz",&_gentauhad_fromH_pz,"gentauhad_fromH_pz/F");
  tree_new->Branch("gentauhad_fromH_pt",&_gentauhad_fromH_pt,"gentauhad_fromH_pt/F");
  tree_new->Branch("gentauhad_fromH_eta",&_gentauhad_fromH_eta,"gentauhad_fromH_eta/F");
  tree_new->Branch("gentauhad_fromH_phi",&_gentauhad_fromH_phi,"gentauhad_fromH_phi/F");
  tree_new->Branch("gentauhad_fromH_flags",&_gentauhad_fromH_flags,"gentauhad_fromH_flags/I");

  tree_new->Branch("genltau_pdg",&_genltau_pdg,"genltau_pdg/I");
  tree_new->Branch("genltau_charge",&_genltau_charge,"genltau_charge/I");
  tree_new->Branch("genltau_e",&_genltau_e,"genltau_e/F");
  tree_new->Branch("genltau_px",&_genltau_px,"genltau_px/F");
  tree_new->Branch("genltau_py",&_genltau_py,"genltau_py/F");
  tree_new->Branch("genltau_pz",&_genltau_pz,"genltau_pz/F");
  tree_new->Branch("genltau_pt",&_genltau_pt,"genltau_pt/F");
  tree_new->Branch("genltau_eta",&_genltau_eta,"genltau_eta/F");
  tree_new->Branch("genltau_phi",&_genltau_phi,"genltau_phi/F");
  tree_new->Branch("genltau_flags",&_genltau_flags,"genltau_flags/I");
  tree_new->Branch("genltau_i_daughter_matched",&_genltau_i_daughter_matched,"genltau_i_daughter_matched/I");
  tree_new->Branch("genltau_dR_daughter_matched",&_genltau_dR_daughter_matched,"genltau_dR_daughter_matched/F");

  tree_new->Branch("gennu1taul_pdg",&_gennu1taul_pdg,"gennu1taul_pdg/I");
  tree_new->Branch("gennu1taul_e",&_gennu1taul_e,"gennu1taul_e/F");
  tree_new->Branch("gennu1taul_px",&_gennu1taul_px,"gennu1taul_px/F");
  tree_new->Branch("gennu1taul_py",&_gennu1taul_py,"gennu1taul_py/F");
  tree_new->Branch("gennu1taul_pz",&_gennu1taul_pz,"gennu1taul_pz/F");
  tree_new->Branch("gennu1taul_pt",&_gennu1taul_pt,"gennu1taul_pt/F");
  tree_new->Branch("gennu1taul_eta",&_gennu1taul_eta,"gennu1taul_eta/F");
  tree_new->Branch("gennu1taul_phi",&_gennu1taul_phi,"gennu1taul_phi/F");
  tree_new->Branch("gennu1taul_flags",&_gennu1taul_flags,"gennu1taul_flags/I");

  tree_new->Branch("gennu2taul_pdg",&_gennu2taul_pdg,"gennu2taul_pdg/I");
  tree_new->Branch("gennu2taul_e",&_gennu2taul_e,"gennu2taul_e/F");
  tree_new->Branch("gennu2taul_px",&_gennu2taul_px,"gennu2taul_px/F");
  tree_new->Branch("gennu2taul_py",&_gennu2taul_py,"gennu2taul_py/F");
  tree_new->Branch("gennu2taul_pz",&_gennu2taul_pz,"gennu2taul_pz/F");
  tree_new->Branch("gennu2taul_pt",&_gennu2taul_pt,"gennu2taul_pt/F");
  tree_new->Branch("gennu2taul_eta",&_gennu2taul_eta,"gennu2taul_eta/F");
  tree_new->Branch("gennu2taul_phi",&_gennu2taul_phi,"gennu2taul_phi/F");
  tree_new->Branch("gennu2taul_flags",&_gennu2taul_flags,"gennu2taul_flags/I");

  tree_new->Branch("genpi_charge",&_genpi_charge,"genpi_charge/I");
  tree_new->Branch("genpi_e",&_genpi_e,"genpi_e/F");
  tree_new->Branch("genpi_px",&_genpi_px,"genpi_px/F");
  tree_new->Branch("genpi_py",&_genpi_py,"genpi_py/F");
  tree_new->Branch("genpi_pz",&_genpi_pz,"genpi_pz/F");
  tree_new->Branch("genpi_pt",&_genpi_pt,"genpi_pt/F");
  tree_new->Branch("genpi_eta",&_genpi_eta,"genpi_eta/F");
  tree_new->Branch("genpi_phi",&_genpi_phi,"genpi_phi/F");
  tree_new->Branch("genpi_flags",&_genpi_flags,"genpi_flags/I");
  tree_new->Branch("genpi_i_daughter_matched",&_genpi_i_daughter_matched,"genpi_i_daughter_matched/I");
  tree_new->Branch("genpi_dR_daughter_matched",&_genpi_dR_daughter_matched,"genpi_dR_daughter_matched/F");

  tree_new->Branch("gennutauh_pdg",&_gennutauh_pdg,"gennutauh_pdg/I");
  tree_new->Branch("gennutauh_e",&_gennutauh_e,"gennutauh_e/F");
  tree_new->Branch("gennutauh_px",&_gennutauh_px,"gennutauh_px/F");
  tree_new->Branch("gennutauh_py",&_gennutauh_py,"gennutauh_py/F");
  tree_new->Branch("gennutauh_pz",&_gennutauh_pz,"gennutauh_pz/F");
  tree_new->Branch("gennutauh_pt",&_gennutauh_pt,"gennutauh_pt/F");
  tree_new->Branch("gennutauh_eta",&_gennutauh_eta,"gennutauh_eta/F");
  tree_new->Branch("gennutauh_phi",&_gennutauh_phi,"gennutauh_phi/F");
  tree_new->Branch("gennutauh_flags",&_gennutauh_flags,"gennutauh_flags/I");

  tree_new->Branch("genMET",&_genMET,"genMET/F");
  tree_new->Branch("genMET_phi",&_genMET_phi,"genMET_phi/F");
  

  cout<<"nentries="<<nentries<<endl;

  //nentries=10;
  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _gentaulep_fromH_charge = 0;
    _gentaulep_fromH_e = 0;
    _gentaulep_fromH_px = 0;
    _gentaulep_fromH_py = 0;
    _gentaulep_fromH_pz = 0;
    _gentaulep_fromH_pt = 0;
    _gentaulep_fromH_eta = 0;
    _gentaulep_fromH_phi = 0;
    _gentaulep_fromH_flags = 0;

    _gentauhad_fromH_charge = 0;
    _gentauhad_fromH_e = 0;
    _gentauhad_fromH_px = 0;
    _gentauhad_fromH_py = 0;
    _gentauhad_fromH_pz = 0;
    _gentauhad_fromH_pt = 0;
    _gentauhad_fromH_eta = 0;
    _gentauhad_fromH_phi = 0;
    _gentauhad_fromH_flags = 0;
  
    _genltau_pdg = 0;
    _genltau_charge = 0;
    _genltau_e = 0;
    _genltau_px = 0;
    _genltau_py = 0;
    _genltau_pz = 0;
    _genltau_pt = 0;
    _genltau_eta = 0;
    _genltau_phi = 0;
    _genltau_flags = 0;

    _genltau_i_daughter_matched = -1;
    _genltau_dR_daughter_matched = 9999;

    _gennu1taul_pdg = 0;
    _gennu1taul_e = 0;
    _gennu1taul_px = 0;
    _gennu1taul_py = 0;
    _gennu1taul_pz = 0;
    _gennu1taul_pt = 0;
    _gennu1taul_eta = 0;
    _gennu1taul_phi = 0;
    _gennu1taul_flags = 0;

    _gennu2taul_pdg = 0;
    _gennu2taul_e = 0;
    _gennu2taul_px = 0;
    _gennu2taul_py = 0;
    _gennu2taul_pz = 0;
    _gennu2taul_pt = 0;
    _gennu2taul_eta = 0;
    _gennu2taul_phi = 0;
    _gennu2taul_flags = 0;

    _genpi_charge = 0;
    _genpi_e = 0;
    _genpi_px = 0;
    _genpi_py = 0;
    _genpi_pz = 0;
    _genpi_pt = 0;
    _genpi_eta = 0;
    _genpi_phi = 0;
    _genpi_flags = 0;

    _genpi_i_daughter_matched = -1;
    _genpi_dR_daughter_matched = 9999;

    _gennutauh_pdg = 0;
    _gennutauh_e = 0;
    _gennutauh_px = 0;
    _gennutauh_py = 0;
    _gennutauh_pz = 0;
    _gennutauh_pt = 0;
    _gennutauh_eta = 0;
    _gennutauh_phi = 0;
    _gennutauh_flags = 0;

    _genMET = 0;
    _genMET_phi = 0;

    _genlep_pdg = 0;
    _genlep_charge = 0;
    _genlep_e = 0;
    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_pt = 0;
    _genlep_eta = 0;
    _genlep_phi = 0;
    _genlep_flags = 0;  
    _genlep_TauMothInd = 0;

    _gentauh_charge = 0;
    _gentauh_e = 0;
    _gentauh_px = 0;
    _gentauh_py = 0;
    _gentauh_pz = 0;
    _gentauh_pt = 0;
    _gentauh_eta = 0;
    _gentauh_phi = 0;
    _gentauh_flags = 0;  
    _gentauh_TauMothInd = 0;

    _genH_decayMode = 0;

    _gentau_charge = 0;
    _gentau_decayMode = 0;
    _gentau_e = 0;
    _gentau_px = 0;
    _gentau_py = 0;
    _gentau_pz = 0;
    _gentau_pt = 0;
    _gentau_eta = 0;
    _gentau_phi = 0;
    _gentau_flags = 0;  
    _gentau_HMothInd = 0;


    _genb_pdg = 0;
    _genb_e = 0;
    _genb_px = 0;
    _genb_py = 0;
    _genb_pz = 0;
    _genb_pt = 0;
    _genb_eta = 0;
    _genb_phi = 0;
    _genb_flags = 0;  

    _genq_pdg = 0;
    _genq_e = 0;
    _genq_px = 0;
    _genq_py = 0;
    _genq_pz = 0;
    _genq_pt = 0;
    _genq_eta = 0;
    _genq_phi = 0;
    _genq_flags = 0;  

    _gennu_pdg = 0;
    _gennu_e = 0;
    _gennu_px = 0;
    _gennu_py = 0;
    _gennu_pz = 0;
    _gennu_pt = 0;
    _gennu_eta = 0;
    _gennu_phi = 0;
    _gennu_flags = 0;  
    _gennu_TauMothInd = 0;

    _daughters_e = 0;
    _daughters_px = 0;
    _daughters_py = 0;
    _daughters_pz = 0;
    _PDGIdDaughters = 0;

    tree->GetEntry(i);

    bool H_to_ltau =  (*_genH_decayMode)[0]==0 || (*_genH_decayMode)[0]==1 ;


    if( !H_to_ltau )
      continue;



    //tau's

    int itaulep=-1;
    int itauhad=-1;

    for(int itau=0; itau<_n_gentau; itau++){

      int HMothInd = (*_gentau_HMothInd)[itau];
      int decayMode = (*_gentau_decayMode)[itau];

      if( !HMothInd==0 )
	continue;
     
      if(decayMode==0 || decayMode==1)
	itaulep = itau;
      else
	itauhad = itau;

    }    

    _gentaulep_fromH_charge = (*_gentau_charge)[itaulep];
    _gentaulep_fromH_e = (*_gentau_e)[itaulep];
    _gentaulep_fromH_px = (*_gentau_px)[itaulep];
    _gentaulep_fromH_py = (*_gentau_py)[itaulep];
    _gentaulep_fromH_pz = (*_gentau_pz)[itaulep];
    _gentaulep_fromH_pt = (*_gentau_pt)[itaulep];
    _gentaulep_fromH_eta = (*_gentau_eta)[itaulep];
    _gentaulep_fromH_phi = (*_gentau_phi)[itaulep];
    _gentaulep_fromH_flags = (*_gentau_flags)[itaulep];

    _gentauhad_fromH_charge = (*_gentau_charge)[itauhad];
    _gentauhad_fromH_e = (*_gentau_e)[itauhad];
    _gentauhad_fromH_px = (*_gentau_px)[itauhad];
    _gentauhad_fromH_py = (*_gentau_py)[itauhad];
    _gentauhad_fromH_pz = (*_gentau_pz)[itauhad];
    _gentauhad_fromH_pt = (*_gentau_pt)[itauhad];
    _gentauhad_fromH_eta = (*_gentau_eta)[itauhad];
    _gentauhad_fromH_phi = (*_gentau_phi)[itauhad];
    _gentauhad_fromH_flags = (*_gentau_flags)[itauhad];


    // Leptons

    int ilep_tau=-1;

    for(int ilep=0; ilep<_n_genlep; ilep++){

      int TauMothInd = (*_genlep_TauMothInd)[ilep];
     
      if( TauMothInd == itaulep )
	ilep_tau = ilep;

    }    


    _genltau_pdg = (*_genlep_pdg)[ilep_tau];
    _genltau_charge = (*_genlep_charge)[ilep_tau];
    _genltau_e = (*_genlep_e)[ilep_tau];
    _genltau_px = (*_genlep_px)[ilep_tau];
    _genltau_py = (*_genlep_py)[ilep_tau];
    _genltau_pz = (*_genlep_pz)[ilep_tau];
    _genltau_pt = (*_genlep_pt)[ilep_tau];
    _genltau_eta = (*_genlep_eta)[ilep_tau];
    _genltau_phi = (*_genlep_phi)[ilep_tau];
    _genltau_flags = (*_genlep_flags)[ilep_tau];

    TLorentzVector genltau_tlv(_genltau_px, _genltau_py, _genltau_pz, _genltau_e);

    for(int ireco=0; ireco<(*_daughters_e).size(); ireco++){

      TLorentzVector recolep_tlv((*_daughters_px)[ireco],(*_daughters_py)[ireco],(*_daughters_pz)[ireco],(*_daughters_e)[ireco]);

      float dR=genltau_tlv.DeltaR(recolep_tlv);
      if( (*_PDGIdDaughters)[ireco]==_genltau_pdg && dR< _genltau_dR_daughter_matched ){
	_genltau_dR_daughter_matched = dR;
	_genltau_i_daughter_matched = ireco;
      }

    }


    // Tauh (=pi)

    int ipi=-1;

    for(int itauh=0; itauh<_n_gentauh; itauh++){

      int TauMothInd = (*_gentauh_TauMothInd)[itauh];
     
      if( TauMothInd == itauhad )
	ipi = itauh;

    }    

    _genpi_charge = (*_gentauh_charge)[ipi];
    _genpi_e = (*_gentauh_e)[ipi];
    _genpi_px = (*_gentauh_px)[ipi];
    _genpi_py = (*_gentauh_py)[ipi];
    _genpi_pz = (*_gentauh_pz)[ipi];
    _genpi_pt = (*_gentauh_pt)[ipi];
    _genpi_eta = (*_gentauh_eta)[ipi];
    _genpi_phi = (*_gentauh_phi)[ipi];
    _genpi_flags = (*_gentauh_flags)[ipi];


    TLorentzVector genpi_tlv(_genpi_px, _genpi_py, _genpi_pz, _genpi_e);

    for(int ireco=0; ireco<(*_daughters_e).size(); ireco++){

      if( abs((*_PDGIdDaughters)[ireco])!=15)
	continue;

      TLorentzVector recotauh_tlv((*_daughters_px)[ireco],(*_daughters_py)[ireco],(*_daughters_pz)[ireco],(*_daughters_e)[ireco]);

      float dR=genpi_tlv.DeltaR(recotauh_tlv);
      if( dR< _genpi_dR_daughter_matched ){
	_genpi_dR_daughter_matched = dR;
	_genpi_i_daughter_matched = ireco;
      }

    }

    //Nu's

    int inu1taul = -1;
    int inu2taul = -1;
    int inutauh = -1;

    for(int inu=0; inu<_n_gennu; inu++){

      int TauMothInd = (*_gennu_TauMothInd)[inu];
     
      if( TauMothInd == itaulep ){
	if(abs( (*_gennu_pdg)[inu] ) == 16)
	  inu1taul = inu;
	else
	  inu2taul = inu;
      }
      else if( TauMothInd == itauhad )
	inutauh = inu;

    }

    _gennu1taul_pdg = (*_gennu_pdg)[inu1taul];
    _gennu1taul_e = (*_gennu_e)[inu1taul];
    _gennu1taul_px = (*_gennu_px)[inu1taul];
    _gennu1taul_py = (*_gennu_py)[inu1taul];
    _gennu1taul_pz = (*_gennu_pz)[inu1taul];
    _gennu1taul_pt = (*_gennu_pt)[inu1taul];
    _gennu1taul_eta = (*_gennu_eta)[inu1taul];
    _gennu1taul_phi = (*_gennu_phi)[inu1taul];
    _gennu1taul_flags = (*_gennu_flags)[inu1taul];

    TLorentzVector gennu1taul_tlv(_gennu1taul_px,_gennu1taul_py,_gennu1taul_pz,_gennu1taul_e);

    _gennu2taul_pdg = (*_gennu_pdg)[inu2taul];
    _gennu2taul_e = (*_gennu_e)[inu2taul];
    _gennu2taul_px = (*_gennu_px)[inu2taul];
    _gennu2taul_py = (*_gennu_py)[inu2taul];
    _gennu2taul_pz = (*_gennu_pz)[inu2taul];
    _gennu2taul_pt = (*_gennu_pt)[inu2taul];
    _gennu2taul_eta = (*_gennu_eta)[inu2taul];
    _gennu2taul_phi = (*_gennu_phi)[inu2taul];
    _gennu2taul_flags = (*_gennu_flags)[inu2taul];

    TLorentzVector gennu2taul_tlv(_gennu2taul_px,_gennu2taul_py,_gennu2taul_pz,_gennu2taul_e);

    _gennutauh_pdg = (*_gennu_pdg)[inutauh];
    _gennutauh_e = (*_gennu_e)[inutauh];
    _gennutauh_px = (*_gennu_px)[inutauh];
    _gennutauh_py = (*_gennu_py)[inutauh];
    _gennutauh_pz = (*_gennu_pz)[inutauh];
    _gennutauh_pt = (*_gennu_pt)[inutauh];
    _gennutauh_eta = (*_gennu_eta)[inutauh];
    _gennutauh_phi = (*_gennu_phi)[inutauh];
    _gennutauh_flags = (*_gennu_flags)[inutauh];

    TLorentzVector gennutauh_tlv(_gennutauh_px,_gennutauh_py,_gennutauh_pz,_gennutauh_e);


    TLorentzVector genMET_tlv = gennu1taul_tlv + gennu2taul_tlv + gennutauh_tlv ;
    _genMET = genMET_tlv.Pt();
    _genMET_phi = genMET_tlv.Phi();

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}
