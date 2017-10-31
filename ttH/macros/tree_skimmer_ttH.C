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

#include "Helpers_RecoVegas_ttH.C"

#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;




void skim_tree(){


  TString file_in = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
  TString file_out = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";


  TChain * tree = new TChain("HTauTauTree");
  tree->Add(file_in);

  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(file_out);
  if(f_new!=0){
    cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(file_out,"RECREATE");



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
  vector<int>* _genlep_TopMothInd;

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

  vector<int>* _gentop_pdg;
  vector<int>* _gentop_decayMode;
  vector<float>* _gentop_e;
  vector<float>* _gentop_px;
  vector<float>* _gentop_py;
  vector<float>* _gentop_pz;
  vector<float>* _gentop_pt;
  vector<float>* _gentop_eta;
  vector<float>* _gentop_phi;
  vector<int>* _gentop_flags; 

  vector<int>* _genW_pdg;
  vector<float>* _genW_e;
  vector<float>* _genW_px;
  vector<float>* _genW_py;
  vector<float>* _genW_pz;
  vector<float>* _genW_pt;
  vector<float>* _genW_eta;
  vector<float>* _genW_phi;
  vector<int>* _genW_flags;  
  vector<int>* _genW_TopMothInd;

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
  vector<int>* _genb_TopMothInd;
  vector<int>* _genb_WMothInd;

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
  vector<int>* _genq_TopMothInd;

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
  vector<int>* _gennu_TopMothInd; //-1 if not from top

  vector<float> *_daughters_e;
  vector<float> *_daughters_px;
  vector<float> *_daughters_py;
  vector<float> *_daughters_pz;
  vector<int> *_PDGIdDaughters;

  vector<float> *_recolep_e;
  vector<float> *_recolep_px;
  vector<float> *_recolep_py;
  vector<float> *_recolep_pz;

  vector<float> *_recotauh_e;
  vector<float> *_recotauh_px;
  vector<float> *_recotauh_py;
  vector<float> *_recotauh_pz;

  vector<float> *_recoPFJet_btag_e;
  vector<float> *_recoPFJet_btag_px;
  vector<float> *_recoPFJet_btag_py;
  vector<float> *_recoPFJet_btag_pz;

  vector<float> *_recoPFJet_untag_Wtag_e;
  vector<float> *_recoPFJet_untag_Wtag_px;
  vector<float> *_recoPFJet_untag_Wtag_py;
  vector<float> *_recoPFJet_untag_Wtag_pz;

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
  tree->SetBranchAddress("genlep_TopMothInd",&_genlep_TopMothInd);

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

  tree->SetBranchAddress("gentop_pdg",&_gentop_pdg);
  tree->SetBranchAddress("gentop_decayMode",&_gentop_decayMode);
  tree->SetBranchAddress("gentop_e",&_gentop_e);
  tree->SetBranchAddress("gentop_px",&_gentop_px);
  tree->SetBranchAddress("gentop_py",&_gentop_py);
  tree->SetBranchAddress("gentop_pz",&_gentop_pz);
  tree->SetBranchAddress("gentop_pt",&_gentop_pt);
  tree->SetBranchAddress("gentop_eta",&_gentop_eta);
  tree->SetBranchAddress("gentop_phi",&_gentop_phi);
  tree->SetBranchAddress("gentop_flags",&_gentop_flags);

  tree->SetBranchAddress("genW_pdg",&_genW_pdg);
  tree->SetBranchAddress("genW_e",&_genW_e);
  tree->SetBranchAddress("genW_px",&_genW_px);
  tree->SetBranchAddress("genW_py",&_genW_py);
  tree->SetBranchAddress("genW_pz",&_genW_pz);
  tree->SetBranchAddress("genW_pt",&_genW_pt);
  tree->SetBranchAddress("genW_eta",&_genW_eta);
  tree->SetBranchAddress("genW_phi",&_genW_phi);
  tree->SetBranchAddress("genW_flags",&_genW_flags);
  tree->SetBranchAddress("genW_TopMothInd",&_genW_TopMothInd);

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
  tree->SetBranchAddress("genb_TopMothInd",&_genb_TopMothInd);
  tree->SetBranchAddress("genb_WMothInd",&_genb_WMothInd);

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
  tree->SetBranchAddress("genq_TopMothInd",&_genq_TopMothInd);

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
  tree->SetBranchAddress("gennu_TopMothInd",&_gennu_TopMothInd);

  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);

  tree->SetBranchAddress("recolep_px",&_recolep_px);
  tree->SetBranchAddress("recolep_py",&_recolep_py);
  tree->SetBranchAddress("recolep_pz",&_recolep_pz);
  tree->SetBranchAddress("recolep_e",&_recolep_e);

  tree->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree->SetBranchAddress("recotauh_pz",&_recotauh_pz);
  tree->SetBranchAddress("recotauh_e",&_recotauh_e);

  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);

  tree->SetBranchAddress("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  
  int _gentl_pdg;
  float _gentl_e;
  float _gentl_px;
  float _gentl_py;
  float _gentl_pz;
  float _gentl_pt;
  float _gentl_eta;
  float _gentl_phi;
  int _gentl_flags; 

  int _genbl_pdg;
  float _genbl_e;
  float _genbl_px;
  float _genbl_py;
  float _genbl_pz;
  float _genbl_pt;
  float _genbl_eta;
  float _genbl_phi;
  int _genbl_flags;
  float _genbl_e_Vegas;

  int _genWl_pdg;
  float _genWl_e;
  float _genWl_px;
  float _genWl_py;
  float _genWl_pz;
  float _genWl_pt;
  float _genWl_eta;
  float _genWl_phi;
  int _genWl_flags; 
  
  int _genlt_pdg;
  int _genlt_charge;
  float _genlt_e;
  float _genlt_px;
  float _genlt_py;
  float _genlt_pz;
  float _genlt_pt;
  float _genlt_eta;
  float _genlt_phi;
  int _genlt_flags; 
  int _genlt_i_daughter_matched;
  float _genlt_dR_daughter_matched;

  int _gennult_pdg;
  float _gennult_e;
  float _gennult_px;
  float _gennult_py;
  float _gennult_pz;
  float _gennult_pt;
  float _gennult_eta;
  float _gennult_phi;
  int _gennult_flags; 
  float _gennult_e_Vegas;

  int _genth_pdg;
  float _genth_e;
  float _genth_px;
  float _genth_py;
  float _genth_pz;
  float _genth_pt;
  float _genth_eta;
  float _genth_phi;
  int _genth_flags; 

  int _genbh_pdg;
  float _genbh_e;
  float _genbh_px;
  float _genbh_py;
  float _genbh_pz;
  float _genbh_pt;
  float _genbh_eta;
  float _genbh_phi;
  int _genbh_flags;

  int _genWh_pdg;
  float _genWh_e;
  float _genWh_px;
  float _genWh_py;
  float _genWh_pz;
  float _genWh_pt;
  float _genWh_eta;
  float _genWh_phi;
  int _genWh_flags; 
  
  int _genq1_pdg;
  float _genq1_e;
  float _genq1_px;
  float _genq1_py;
  float _genq1_pz;
  float _genq1_pt;
  float _genq1_eta;
  float _genq1_phi;
  int _genq1_flags; 
  int _genq1_i_daughter_matched;
  float _genq1_dR_daughter_matched;

  int _genq2_pdg;
  float _genq2_e;
  float _genq2_px;
  float _genq2_py;
  float _genq2_pz;
  float _genq2_pt;
  float _genq2_eta;
  float _genq2_phi;
  int _genq2_flags; 
  int _genq2_i_daughter_matched;
  float _genq2_dR_daughter_matched;

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

  vector<float> _recotauh_dR_genpi;
  vector<float> _recolep_dR_genlt;
  vector<float> _recolep_dR_genltau;
  vector<float> _recoPFJet_btag_dR_genbh;
  vector<float> _recoPFJet_btag_dR_genbl;
  vector<float> _recoPFJet_untag_Wtag_dR_genq1;
  vector<float> _recoPFJet_untag_Wtag_dR_genq2;
  int _perm_match;
  int _perm_gen_match;

  tree_new->Branch("gentl_pdg",&_gentl_pdg,"gentl_pdg/I");
  tree_new->Branch("gentl_e",&_gentl_e,"gentl_e/F");
  tree_new->Branch("gentl_px",&_gentl_px,"gentl_px/F");
  tree_new->Branch("gentl_py",&_gentl_py,"gentl_py/F");
  tree_new->Branch("gentl_pz",&_gentl_pz,"gentl_pz/F");
  tree_new->Branch("gentl_pt",&_gentl_pt,"gentl_pt/F");
  tree_new->Branch("gentl_eta",&_gentl_eta,"gentl_eta/F");
  tree_new->Branch("gentl_phi",&_gentl_phi,"gentl_phi/F");
  tree_new->Branch("gentl_flags",&_gentl_flags,"gentl_flags/I");

  tree_new->Branch("genbl_pdg",&_genbl_pdg,"genbl_pdg/I");
  tree_new->Branch("genbl_e",&_genbl_e,"genbl_e/F");
  tree_new->Branch("genbl_px",&_genbl_px,"genbl_px/F");
  tree_new->Branch("genbl_py",&_genbl_py,"genbl_py/F");
  tree_new->Branch("genbl_pz",&_genbl_pz,"genbl_pz/F");
  tree_new->Branch("genbl_pt",&_genbl_pt,"genbl_pt/F");
  tree_new->Branch("genbl_eta",&_genbl_eta,"genbl_eta/F");
  tree_new->Branch("genbl_phi",&_genbl_phi,"genbl_phi/F");
  tree_new->Branch("genbl_flags",&_genbl_flags,"genbl_flags/I");
  tree_new->Branch("genbl_e_Vegas",&_genbl_e_Vegas,"genbl_e_Vegas/F");

  tree_new->Branch("genWl_pdg",&_genWl_pdg,"genWl_pdg/I");
  tree_new->Branch("genWl_e",&_genWl_e,"genWl_e/F");
  tree_new->Branch("genWl_px",&_genWl_px,"genWl_px/F");
  tree_new->Branch("genWl_py",&_genWl_py,"genWl_py/F");
  tree_new->Branch("genWl_pz",&_genWl_pz,"genWl_pz/F");
  tree_new->Branch("genWl_pt",&_genWl_pt,"genWl_pt/F");
  tree_new->Branch("genWl_eta",&_genWl_eta,"genWl_eta/F");
  tree_new->Branch("genWl_phi",&_genWl_phi,"genWl_phi/F");
  tree_new->Branch("genWl_flags",&_genWl_flags,"genWl_flags/I");

  tree_new->Branch("genlt_pdg",&_genlt_pdg,"genlt_pdg/I");
  tree_new->Branch("genlt_charge",&_genlt_charge,"genlt_charge/I");
  tree_new->Branch("genlt_e",&_genlt_e,"genlt_e/F");
  tree_new->Branch("genlt_px",&_genlt_px,"genlt_px/F");
  tree_new->Branch("genlt_py",&_genlt_py,"genlt_py/F");
  tree_new->Branch("genlt_pz",&_genlt_pz,"genlt_pz/F");
  tree_new->Branch("genlt_pt",&_genlt_pt,"genlt_pt/F");
  tree_new->Branch("genlt_eta",&_genlt_eta,"genlt_eta/F");
  tree_new->Branch("genlt_phi",&_genlt_phi,"genlt_phi/F");
  tree_new->Branch("genlt_flags",&_genlt_flags,"genlt_flags/I");
  tree_new->Branch("genlt_i_daughter_matched",&_genlt_i_daughter_matched,"genlt_i_daughter_matched/I");
  tree_new->Branch("genlt_dR_daughter_matched",&_genlt_dR_daughter_matched,"genlt_dR_daughter_matched/F");

  tree_new->Branch("gennult_pdg",&_gennult_pdg,"gennult_pdg/I");
  tree_new->Branch("gennult_e",&_gennult_e,"gennult_e/F");
  tree_new->Branch("gennult_px",&_gennult_px,"gennult_px/F");
  tree_new->Branch("gennult_py",&_gennult_py,"gennult_py/F");
  tree_new->Branch("gennult_pz",&_gennult_pz,"gennult_pz/F");
  tree_new->Branch("gennult_pt",&_gennult_pt,"gennult_pt/F");
  tree_new->Branch("gennult_eta",&_gennult_eta,"gennult_eta/F");
  tree_new->Branch("gennult_phi",&_gennult_phi,"gennult_phi/F");
  tree_new->Branch("gennult_flags",&_gennult_flags,"gennult_flags/I");
  tree_new->Branch("gennult_e_Vegas",&_gennult_e_Vegas,"gennult_e_Vegas/F");

  tree_new->Branch("genth_pdg",&_genth_pdg,"genth_pdg/I");
  tree_new->Branch("genth_e",&_genth_e,"genth_e/F");
  tree_new->Branch("genth_px",&_genth_px,"genth_px/F");
  tree_new->Branch("genth_py",&_genth_py,"genth_py/F");
  tree_new->Branch("genth_pz",&_genth_pz,"genth_pz/F");
  tree_new->Branch("genth_pt",&_genth_pt,"genth_pt/F");
  tree_new->Branch("genth_eta",&_genth_eta,"genth_eta/F");
  tree_new->Branch("genth_phi",&_genth_phi,"genth_phi/F");
  tree_new->Branch("genth_flags",&_genth_flags,"genth_flags/I");

  tree_new->Branch("genbh_pdg",&_genbh_pdg,"genbh_pdg/I");
  tree_new->Branch("genbh_e",&_genbh_e,"genbh_e/F");
  tree_new->Branch("genbh_px",&_genbh_px,"genbh_px/F");
  tree_new->Branch("genbh_py",&_genbh_py,"genbh_py/F");
  tree_new->Branch("genbh_pz",&_genbh_pz,"genbh_pz/F");
  tree_new->Branch("genbh_pt",&_genbh_pt,"genbh_pt/F");
  tree_new->Branch("genbh_eta",&_genbh_eta,"genbh_eta/F");
  tree_new->Branch("genbh_phi",&_genbh_phi,"genbh_phi/F");
  tree_new->Branch("genbh_flags",&_genbh_flags,"genbh_flags/I");

  tree_new->Branch("genWh_pdg",&_genWh_pdg,"genWh_pdg/I");
  tree_new->Branch("genWh_e",&_genWh_e,"genWh_e/F");
  tree_new->Branch("genWh_px",&_genWh_px,"genWh_px/F");
  tree_new->Branch("genWh_py",&_genWh_py,"genWh_py/F");
  tree_new->Branch("genWh_pz",&_genWh_pz,"genWh_pz/F");
  tree_new->Branch("genWh_pt",&_genWh_pt,"genWh_pt/F");
  tree_new->Branch("genWh_eta",&_genWh_eta,"genWh_eta/F");
  tree_new->Branch("genWh_phi",&_genWh_phi,"genWh_phi/F");
  tree_new->Branch("genWh_flags",&_genWh_flags,"genWh_flags/I");

  tree_new->Branch("genq1_pdg",&_genq1_pdg,"genq1_pdg/I");
  tree_new->Branch("genq1_e",&_genq1_e,"genq1_e/F");
  tree_new->Branch("genq1_px",&_genq1_px,"genq1_px/F");
  tree_new->Branch("genq1_py",&_genq1_py,"genq1_py/F");
  tree_new->Branch("genq1_pz",&_genq1_pz,"genq1_pz/F");
  tree_new->Branch("genq1_pt",&_genq1_pt,"genq1_pt/F");
  tree_new->Branch("genq1_eta",&_genq1_eta,"genq1_eta/F");
  tree_new->Branch("genq1_phi",&_genq1_phi,"genq1_phi/F");
  tree_new->Branch("genq1_flags",&_genq1_flags,"genq1_flags/I");
  tree_new->Branch("genq1_i_daughter_matched",&_genq1_i_daughter_matched,"genq1_i_daughter_matched/I");
  tree_new->Branch("genq1_dR_daughter_matched",&_genq1_dR_daughter_matched,"genq1_dR_daughter_matched/F");

  tree_new->Branch("genq2_pdg",&_genq2_pdg,"genq2_pdg/I");
  tree_new->Branch("genq2_e",&_genq2_e,"genq2_e/F");
  tree_new->Branch("genq2_px",&_genq2_px,"genq2_px/F");
  tree_new->Branch("genq2_py",&_genq2_py,"genq2_py/F");
  tree_new->Branch("genq2_pz",&_genq2_pz,"genq2_pz/F");
  tree_new->Branch("genq2_pt",&_genq2_pt,"genq2_pt/F");
  tree_new->Branch("genq2_eta",&_genq2_eta,"genq2_eta/F");
  tree_new->Branch("genq2_phi",&_genq2_phi,"genq2_phi/F");
  tree_new->Branch("genq2_flags",&_genq2_flags,"genq2_flags/I");
  tree_new->Branch("genq2_i_daughter_matched",&_genq2_i_daughter_matched,"genq2_i_daughter_matched/I");
  tree_new->Branch("genq2_dR_daughter_matched",&_genq2_dR_daughter_matched,"genq2_dR_daughter_matched/F");

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
 

  tree_new->Branch("recotauh_dR_genpi",&_recotauh_dR_genpi);
  tree_new->Branch("recolep_dR_genlt",&_recolep_dR_genlt);
  tree_new->Branch("recolep_dR_genltau",&_recolep_dR_genltau);
  tree_new->Branch("recoPFJet_btag_dR_genbh",&_recoPFJet_btag_dR_genbh);
  tree_new->Branch("recoPFJet_btag_dR_genbl",&_recoPFJet_btag_dR_genbl);
  tree_new->Branch("recoPFJet_untag_Wtag_dR_genq1",&_recoPFJet_untag_Wtag_dR_genq1);
  tree_new->Branch("recoPFJet_untag_Wtag_dR_genq2",&_recoPFJet_untag_Wtag_dR_genq2);
  tree_new->Branch("perm_match",&_perm_match,"perm_match/I");
  tree_new->Branch("perm_gen_match",&_perm_gen_match,"perm_gen_match/I");


  cout<<"nentries="<<nentries<<endl;

  //nentries=100;
  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;


    _gentl_pdg = 0;
    _gentl_e = 0;
    _gentl_px = 0;
    _gentl_py = 0;
    _gentl_pz = 0;
    _gentl_pt = 0;
    _gentl_eta = 0;
    _gentl_phi = 0;
    _gentl_flags = 0; 
    
    _genbl_pdg = 0;
    _genbl_e = 0;
    _genbl_px = 0;
    _genbl_py = 0;
    _genbl_pz = 0;
    _genbl_pt = 0;
    _genbl_eta = 0;
    _genbl_phi = 0;
    _genbl_flags = 0;
    _genbl_e_Vegas = 0;

    _genWl_pdg = 0;
    _genWl_e = 0;
    _genWl_px = 0;
    _genWl_py = 0;
    _genWl_pz = 0;
    _genWl_pt = 0;
    _genWl_eta = 0;
    _genWl_phi = 0;
    _genWl_flags = 0; 
  
    _genlt_pdg = 0;
    _genlt_charge = 0;
    _genlt_e = 0;
    _genlt_px = 0;
    _genlt_py = 0;
    _genlt_pz = 0;
    _genlt_pt = 0;
    _genlt_eta = 0;
    _genlt_phi = 0;
    _genlt_flags = 0; 

    _genlt_i_daughter_matched = -1;
    _genlt_dR_daughter_matched = 9999;

    _gennult_pdg = 0;
    _gennult_e = 0;
    _gennult_px = 0;
    _gennult_py = 0;
    _gennult_pz = 0;
    _gennult_pt = 0;
    _gennult_eta = 0;
    _gennult_phi = 0;
    _gennult_flags = 0; 
    _gennult_e_Vegas = 0;

    _genth_pdg = 0;
    _genth_e = 0;
    _genth_px = 0;
    _genth_py = 0;
    _genth_pz = 0;
    _genth_pt = 0;
    _genth_eta = 0;
    _genth_phi = 0;
    _genth_flags = 0; 

    _genbh_pdg = 0;
    _genbh_e = 0;
    _genbh_px = 0;
    _genbh_py = 0;
    _genbh_pz = 0;
    _genbh_pt = 0;
    _genbh_eta = 0;
    _genbh_phi = 0;
    _genbh_flags = 0;

    _genWh_pdg = 0;
    _genWh_e = 0;
    _genWh_px = 0;
    _genWh_py = 0;
    _genWh_pz = 0;
    _genWh_pt = 0;
    _genWh_eta = 0;
    _genWh_phi = 0;
    _genWh_flags = 0; 
  
    _genq1_pdg = 0;
    _genq1_e = 0;
    _genq1_px = 0;
    _genq1_py = 0;
    _genq1_pz = 0;
    _genq1_pt = 0;
    _genq1_eta = 0;
    _genq1_phi = 0;
    _genq1_flags = 0;

    _genq1_i_daughter_matched = -1;
    _genq1_dR_daughter_matched = 9999; 

    _genq2_pdg = 0;
    _genq2_e = 0;
    _genq2_px = 0;
    _genq2_py = 0;
    _genq2_pz = 0;
    _genq2_pt = 0;
    _genq2_eta = 0;
    _genq2_phi = 0;
    _genq2_flags = 0; 

    _genq2_i_daughter_matched = -1;
    _genq2_dR_daughter_matched = 9999;

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

    _recotauh_dR_genpi.clear();
    _recolep_dR_genlt.clear();
    _recolep_dR_genltau.clear();
    _recoPFJet_btag_dR_genbh.clear();
    _recoPFJet_btag_dR_genbl.clear();
    _recoPFJet_untag_Wtag_dR_genq1.clear();
    _recoPFJet_untag_Wtag_dR_genq2.clear();
    _perm_match = -1;
    _perm_gen_match = -1;


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
    _genlep_TopMothInd = 0;

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

    _gentop_pdg = 0;
    _gentop_decayMode = 0;
    _gentop_e = 0;
    _gentop_px = 0;
    _gentop_py = 0;
    _gentop_pz = 0;
    _gentop_pt = 0;
    _gentop_eta = 0;
    _gentop_phi = 0;
    _gentop_flags = 0; 

    _genW_pdg = 0;
    _genW_e = 0;
    _genW_px = 0;
    _genW_py = 0;
    _genW_pz = 0;
    _genW_pt = 0;
    _genW_eta = 0;
    _genW_phi = 0;
    _genW_flags = 0;  
    _genW_TopMothInd = 0;

    _genb_pdg = 0;
    _genb_e = 0;
    _genb_px = 0;
    _genb_py = 0;
    _genb_pz = 0;
    _genb_pt = 0;
    _genb_eta = 0;
    _genb_phi = 0;
    _genb_flags = 0;  
    _genb_TopMothInd = 0;
    _genb_WMothInd = 0;

    _genq_pdg = 0;
    _genq_e = 0;
    _genq_px = 0;
    _genq_py = 0;
    _genq_pz = 0;
    _genq_pt = 0;
    _genq_eta = 0;
    _genq_phi = 0;
    _genq_flags = 0;  
    _genq_TopMothInd = 0;

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
    _gennu_TopMothInd = 0;

    _daughters_e = 0;
    _daughters_px = 0;
    _daughters_py = 0;
    _daughters_pz = 0;
    _PDGIdDaughters = 0;

    _recolep_e = 0;
    _recolep_px = 0;
    _recolep_py = 0;
    _recolep_pz = 0;
    
    _recotauh_e = 0;
    _recotauh_px = 0;
    _recotauh_py = 0;
    _recotauh_pz = 0;

    _recoPFJet_btag_e = 0;
    _recoPFJet_btag_px = 0;
    _recoPFJet_btag_py = 0;
    _recoPFJet_btag_pz = 0;
    
    _recoPFJet_untag_Wtag_e = 0;
    _recoPFJet_untag_Wtag_px = 0;
    _recoPFJet_untag_Wtag_py = 0;
    _recoPFJet_untag_Wtag_pz = 0;
  
    tree->GetEntry(i);

    bool top0_had = (*_gentop_decayMode)[0]==0;
    bool top1_had = (*_gentop_decayMode)[1]==0;
    bool top0_lep = (*_gentop_decayMode)[0]==1 || (*_gentop_decayMode)[0]==2 ;
    bool top1_lep = (*_gentop_decayMode)[1]==1 || (*_gentop_decayMode)[1]==2 ;
    bool H_to_ltau =  (*_genH_decayMode)[1]==0 || (*_genH_decayMode)[1]==1 ;

    if( ! ( ( (top0_had && top1_lep) || (top1_had && top0_lep) ) && H_to_ltau ) )
      continue;


    //Tops

    int itop_tl = 0;
    int itop_th = 1;
    if( (*_gentop_decayMode)[0]==0 ){
      itop_tl = 1;
      itop_th = 0;
    }

    _gentl_pdg = (*_gentop_pdg)[itop_tl];
    _gentl_e = (*_gentop_e)[itop_tl];
    _gentl_px = (*_gentop_px)[itop_tl];
    _gentl_py = (*_gentop_py)[itop_tl];
    _gentl_pz = (*_gentop_pz)[itop_tl];
    _gentl_pt = (*_gentop_pt)[itop_tl];
    _gentl_eta = (*_gentop_eta)[itop_tl];
    _gentl_phi = (*_gentop_phi)[itop_tl];
    _gentl_flags = (*_gentop_flags)[itop_tl];

    _genth_pdg = (*_gentop_pdg)[itop_th];
    _genth_e = (*_gentop_e)[itop_th];
    _genth_px = (*_gentop_px)[itop_th];
    _genth_py = (*_gentop_py)[itop_th];
    _genth_pz = (*_gentop_pz)[itop_th];
    _genth_pt = (*_gentop_pt)[itop_th];
    _genth_eta = (*_gentop_eta)[itop_th];
    _genth_phi = (*_gentop_phi)[itop_th];
    _genth_flags = (*_gentop_flags)[itop_th];


    //b's

    int ibl = -1;
    int ibh = -1;

    for(int ib=0; ib<_n_genb; ib++){

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
    

    _genbl_pdg = (*_genb_pdg)[ibl];
    _genbl_e = (*_genb_e)[ibl];
    _genbl_px = (*_genb_px)[ibl];
    _genbl_py = (*_genb_py)[ibl];
    _genbl_pz = (*_genb_pz)[ibl];
    _genbl_pt = (*_genb_pt)[ibl];
    _genbl_eta = (*_genb_eta)[ibl];
    _genbl_phi = (*_genb_phi)[ibl];
    _genbl_flags = (*_genb_flags)[ibl];

    TLorentzVector genbl_tlv(_genbl_px,_genbl_py,_genbl_pz,_genbl_e);
    
    _genbh_pdg = (*_genb_pdg)[ibh];
    _genbh_e = (*_genb_e)[ibh];
    _genbh_px = (*_genb_px)[ibh];
    _genbh_py = (*_genb_py)[ibh];
    _genbh_pz = (*_genb_pz)[ibh];
    _genbh_pt = (*_genb_pt)[ibh];
    _genbh_eta = (*_genb_eta)[ibh];
    _genbh_phi = (*_genb_phi)[ibh];
    _genbh_flags = (*_genb_flags)[ibh];

    TLorentzVector genbh_tlv(_genbl_px,_genbl_py,_genbl_pz,_genbl_e);


    //W's

    int iWl = 0;
    int iWh = 1;
    if( (*_genW_TopMothInd)[0]==itop_th ){
      iWl = 1;
      iWh = 0;
    }
    
    _genWl_pdg = (*_genW_pdg)[iWl];
    _genWl_e = (*_genW_e)[iWl];
    _genWl_px = (*_genW_px)[iWl];
    _genWl_py = (*_genW_py)[iWl];
    _genWl_pz = (*_genW_pz)[iWl];
    _genWl_pt = (*_genW_pt)[iWl];
    _genWl_eta = (*_genW_eta)[iWl];
    _genWl_phi = (*_genW_phi)[iWl];
    _genWl_flags = (*_genW_flags)[iWl];

    _genWh_pdg = (*_genW_pdg)[iWh];
    _genWh_e = (*_genW_e)[iWh];
    _genWh_px = (*_genW_px)[iWh];
    _genWh_py = (*_genW_py)[iWh];
    _genWh_pz = (*_genW_pz)[iWh];
    _genWh_pt = (*_genW_pt)[iWh];
    _genWh_eta = (*_genW_eta)[iWh];
    _genWh_phi = (*_genW_phi)[iWh];
    _genWh_flags = (*_genW_flags)[iWh];
    

    //Light quarks

    int iq1=-1;
    int iq2=-1;

    for(int iq=0; iq<_n_genq; iq++){

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

    _genq1_pdg = (*_genq_pdg)[iq1];
    _genq1_e = (*_genq_e)[iq1];
    _genq1_px = (*_genq_px)[iq1];
    _genq1_py = (*_genq_py)[iq1];
    _genq1_pz = (*_genq_pz)[iq1];
    _genq1_pt = (*_genq_pt)[iq1];
    _genq1_eta = (*_genq_eta)[iq1];
    _genq1_phi = (*_genq_phi)[iq1];
    _genq1_flags = (*_genq_flags)[iq1];

    TLorentzVector genq1_tlv(_genq1_px,_genq1_py,_genq1_pz,_genq1_e);

    for(unsigned int ireco=0; ireco<(*_daughters_e).size(); ireco++){

      if( abs((*_PDGIdDaughters)[ireco])!=15)
	continue;

      TLorentzVector recotauh_tlv((*_daughters_px)[ireco],(*_daughters_py)[ireco],(*_daughters_pz)[ireco],(*_daughters_e)[ireco]);

      float dR=genq1_tlv.DeltaR(recotauh_tlv);
      if( dR< _genq1_dR_daughter_matched ){
	_genq1_dR_daughter_matched = dR;
	_genq1_i_daughter_matched = ireco;
      }

    }

    _genq2_pdg = (*_genq_pdg)[iq2];
    _genq2_e = (*_genq_e)[iq2];
    _genq2_px = (*_genq_px)[iq2];
    _genq2_py = (*_genq_py)[iq2];
    _genq2_pz = (*_genq_pz)[iq2];
    _genq2_pt = (*_genq_pt)[iq2];
    _genq2_eta = (*_genq_eta)[iq2];
    _genq2_phi = (*_genq_phi)[iq2];
    _genq2_flags = (*_genq_flags)[iq2];

    TLorentzVector genq2_tlv(_genq2_px,_genq2_py,_genq2_pz,_genq2_e);

    for(unsigned int ireco=0; ireco<(*_daughters_e).size(); ireco++){

      if( abs((*_PDGIdDaughters)[ireco])!=15)
	continue;

      TLorentzVector recotauh_tlv((*_daughters_px)[ireco],(*_daughters_py)[ireco],(*_daughters_pz)[ireco],(*_daughters_e)[ireco]);

      float dR=genq2_tlv.DeltaR(recotauh_tlv);
      if( dR< _genq2_dR_daughter_matched ){
	_genq2_dR_daughter_matched = dR;
	_genq2_i_daughter_matched = ireco;
      }

    }

    //tau's

    int itaulep=-1;
    int itauhad=-1;

    for(int itau=0; itau<_n_gentau; itau++){

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

    int ilep_top=-1;
    int ilep_tau=-1;

    for(int ilep=0; ilep<_n_genlep; ilep++){

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


    _genlt_pdg = (*_genlep_pdg)[ilep_top];
    _genlt_charge = (*_genlep_charge)[ilep_top];
    _genlt_e = (*_genlep_e)[ilep_top];
    _genlt_px = (*_genlep_px)[ilep_top];
    _genlt_py = (*_genlep_py)[ilep_top];
    _genlt_pz = (*_genlep_pz)[ilep_top];
    _genlt_pt = (*_genlep_pt)[ilep_top];
    _genlt_eta = (*_genlep_eta)[ilep_top];
    _genlt_phi = (*_genlep_phi)[ilep_top];
    _genlt_flags = (*_genlep_flags)[ilep_top];

    TLorentzVector genlt_tlv(_genlt_px, _genlt_py, _genlt_pz, _genlt_e);

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

    for(unsigned int ireco=0; ireco<(*_daughters_e).size(); ireco++){

      TLorentzVector recolep_tlv((*_daughters_px)[ireco],(*_daughters_py)[ireco],(*_daughters_pz)[ireco],(*_daughters_e)[ireco]);

      float dR=genlt_tlv.DeltaR(recolep_tlv);
      if( (*_PDGIdDaughters)[ireco]==_genlt_pdg && dR< _genlt_dR_daughter_matched ){
	_genlt_dR_daughter_matched = dR;
	_genlt_i_daughter_matched = ireco;
      }

      dR=genltau_tlv.DeltaR(recolep_tlv);
      if( (*_PDGIdDaughters)[ireco]==_genltau_pdg && dR< _genltau_dR_daughter_matched ){
	_genltau_dR_daughter_matched = dR;
	_genltau_i_daughter_matched = ireco;
      }

    }


    // Tauh (=pi)

    int ipi=-1;

    for(int itauh=0; itauh<_n_gentauh; itauh++){

      int flag_Mother = (*_gentau_flags)[(*_gentauh_TauMothInd)[itauh]];
      bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
      int TauMothInd = (*_gentauh_TauMothInd)[itauh];
     
      if( TauMothInd == itauhad && isMotherFromHardProcess )
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

    for(unsigned int ireco=0; ireco<(*_daughters_e).size(); ireco++){

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

    int inult = -1;
    int inu1taul = -1;
    int inu2taul = -1;
    int inutauh = -1;

    for(int inu=0; inu<_n_gennu; inu++){

      bool isFromHardProcess = ( (*_gennu_flags)[inu] >> 8 ) & 1;
      bool isDirectTauDecayProduct = ( (*_gennu_flags)[inu] >> 4) & 1;
      bool isHardProcessTauDecayProduct = ( (*_gennu_flags)[inu] >> 9) & 1;
      int TauMothInd = (*_gennu_TauMothInd)[inu];
      int TopMothInd = (*_gennu_TopMothInd)[inu];
     
      if( TopMothInd == itop_tl && isFromHardProcess)
	inult = inu;
      else if( TauMothInd == itaulep && isDirectTauDecayProduct && isHardProcessTauDecayProduct ){
	if(abs( (*_gennu_pdg)[inu] ) == 16)
	  inu1taul = inu;
	else
	  inu2taul = inu;
      }
      else if( TauMothInd == itauhad && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
	inutauh = inu;

    }

    _gennult_pdg = (*_gennu_pdg)[inult];
    _gennult_e = (*_gennu_e)[inult];
    _gennult_px = (*_gennu_px)[inult];
    _gennult_py = (*_gennu_py)[inult];
    _gennult_pz = (*_gennu_pz)[inult];
    _gennult_pt = (*_gennu_pt)[inult];
    _gennult_eta = (*_gennu_eta)[inult];
    _gennult_phi = (*_gennu_phi)[inult];
    _gennult_flags = (*_gennu_flags)[inult];

    TLorentzVector gennult_tlv(_gennult_px,_gennult_py,_gennult_pz,_gennult_e);
    TLorentzVector gennult_RecoVegas = Vegas_nult_4P(genlt_tlv, gennult_tlv.Phi(), gennult_tlv.CosTheta() );
    _gennult_e_Vegas = gennult_RecoVegas.E();

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


    TLorentzVector genbl_RecoVegas = Vegas_blep_4P(genlt_tlv, genbl_tlv, gennult_tlv.Phi(), gennult_tlv.CosTheta() );
    _genbl_e_Vegas = genbl_RecoVegas.E();

    TLorentzVector genMET_tlv = gennu1taul_tlv + gennu2taul_tlv + gennutauh_tlv + gennult_tlv;
    _genMET = genMET_tlv.Pt();
    _genMET_phi = genMET_tlv.Phi();

    
    for(unsigned int itau=0; itau<(*_recotauh_e).size(); itau++){

      TLorentzVector recotauh_tlv( (*_recotauh_px)[itau], (*_recotauh_py)[itau], (*_recotauh_pz)[itau], (*_recotauh_e)[itau]);
      _recotauh_dR_genpi.push_back( recotauh_tlv.DeltaR(genpi_tlv) );

    }

    for(unsigned int ilep=0; ilep<(*_recolep_e).size(); ilep++){

      TLorentzVector recolep_tlv( (*_recolep_px)[ilep], (*_recolep_py)[ilep], (*_recolep_pz)[ilep], (*_recolep_e)[ilep]);
      _recolep_dR_genlt.push_back( recolep_tlv.DeltaR(genlt_tlv) );
      _recolep_dR_genltau.push_back( recolep_tlv.DeltaR(genltau_tlv) );

    }

    for(unsigned int ib=0; ib<(*_recoPFJet_btag_e).size(); ib++){

      TLorentzVector recoPFJet_btag_tlv( (*_recoPFJet_btag_px)[ib], (*_recoPFJet_btag_py)[ib], (*_recoPFJet_btag_pz)[ib], (*_recoPFJet_btag_e)[ib]);
      _recoPFJet_btag_dR_genbh.push_back( recoPFJet_btag_tlv.DeltaR(genbh_tlv) );
      _recoPFJet_btag_dR_genbl.push_back( recoPFJet_btag_tlv.DeltaR(genbl_tlv) );

    }

    for(unsigned int ijet=0; ijet<(*_recoPFJet_untag_Wtag_e).size(); ijet++){

      TLorentzVector recoPFJet_untag_Wtag_tlv( (*_recoPFJet_untag_Wtag_px)[ijet], (*_recoPFJet_untag_Wtag_py)[ijet], (*_recoPFJet_untag_Wtag_pz)[ijet], (*_recoPFJet_untag_Wtag_e)[ijet]);
      _recoPFJet_untag_Wtag_dR_genq1.push_back( recoPFJet_untag_Wtag_tlv.DeltaR(genq1_tlv) );
      _recoPFJet_untag_Wtag_dR_genq2.push_back( recoPFJet_untag_Wtag_tlv.DeltaR(genq2_tlv) );

    }

    
    //Permutation matching

    if( _recotauh_dR_genpi.size()>0
	&& _recolep_dR_genlt.size()>1
	&& _recoPFJet_btag_dR_genbh.size()>1
	&& _recoPFJet_untag_Wtag_dR_genq1.size()>1 ){

      if( _recotauh_dR_genpi[0]<0.1
	  && ( ( _recoPFJet_untag_Wtag_dR_genq1[0]<0.5 && _recoPFJet_untag_Wtag_dR_genq2[1]<0.5 )
	       || ( _recoPFJet_untag_Wtag_dR_genq1[1]<0.5 && _recoPFJet_untag_Wtag_dR_genq2[0]<0.5 ) ) ){
	
	    if( _recolep_dR_genlt[0]<0.1 &&  _recolep_dR_genltau[1]<0.1
		&& _recoPFJet_btag_dR_genbl[0]<0.5 && _recoPFJet_btag_dR_genbl[1]<0.5 )
	      _perm_match = 0;
	    
	    else if( _recolep_dR_genlt[1]<0.1 &&  _recolep_dR_genltau[0]<0.1
		     && _recoPFJet_btag_dR_genbl[0]<0.5 && _recoPFJet_btag_dR_genbl[1]<0.5 )
	      _perm_match = 1;

	    else if( _recolep_dR_genlt[0]<0.1 &&  _recolep_dR_genltau[1]<0.1
		     && _recoPFJet_btag_dR_genbl[1]<0.5 && _recoPFJet_btag_dR_genbl[0]<0.5 )
	      _perm_match = 2;
	    
	    else if( _recolep_dR_genlt[1]<0.1 &&  _recolep_dR_genltau[0]<0.1
		     && _recoPFJet_btag_dR_genbl[1]<0.5 && _recoPFJet_btag_dR_genbl[0]<0.5 )
	      _perm_match = 3;

      }
	  
    }


    //Gen permutation matching
    if(_genbl_pt>_genbh_pt){
      if(_genlt_pt>_genltau_pt)
	_perm_gen_match = 0;
      else
	_perm_gen_match = 1;
    }

    else{
      if(_genlt_pt>_genltau_pt)
	_perm_gen_match = 2;
      else
	_perm_gen_match = 3;
    }


    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}
