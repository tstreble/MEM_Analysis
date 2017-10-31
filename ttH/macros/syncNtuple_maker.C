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



void create_syncNtuple(){

  //TString dir_in="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_06_2016/";
  //TString dir_out="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/";
  /*TString dir_in="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttV/";
    TString dir_out="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/";*/
  TString dir_in="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/";
  TString dir_out="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/syncNtuples/";

  //TString file="syncNtuple_ttW_multilep.root";
  TString file="syncNtuple_ttH.root";


  vector<TString> list;
  //list.push_back(dir_in+"syncNtuple_ttW_multilep_0_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  list.push_back(dir_in+"syncNtuple_ttH_tautau_prod012017_0_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");


  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }



  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");

  TTree* tree_new=new TTree("syncTree","syncTree");


  //New branches
  ULong64_t _nEvent;
  int _ls;
  int _run;

  int _n_presel_mu;
  int _n_fakeablesel_mu;
  int _n_mvasel_mu;

  int _n_presel_ele;
  int _n_fakeablesel_ele;
  int _n_mvasel_ele;

  int _n_presel_tau;
  int _n_presel_jet;

  float _mu0_pt;
  float _mu0_conept;
  float _mu0_eta;
  float _mu0_phi;
  float _mu0_E;
  int _mu0_charge;
  int _mu0_jetNDauChargedMVASel;
  float _mu0_miniRelIso;
  float _mu0_miniIsoCharged;
  float _mu0_miniIsoNeutral;
  float _mu0_jetPtRel;
  float _mu0_jetPtRatio;
  float _mu0_jetCSV;
  float _mu0_sip3D;
  float _mu0_dxy;
  float _mu0_dz;
  float _mu0_segmentCompatibility;
  float _mu0_leptonMVA;
  bool _mu0_mediumID;
  float _mu0_dpt_div_pt;
  bool _mu0_isfakeablesel;
  bool _mu0_ismvasel;


  float _mu1_pt;
  float _mu1_conept;
  float _mu1_eta;
  float _mu1_phi;
  float _mu1_E;
  int _mu1_charge;
  int _mu1_jetNDauChargedMVASel;
  float _mu1_miniRelIso;
  float _mu1_miniIsoCharged;
  float _mu1_miniIsoNeutral;
  float _mu1_jetPtRel;
  float _mu1_jetPtRatio;
  float _mu1_jetCSV;
  float _mu1_sip3D;
  float _mu1_dxy;
  float _mu1_dz;
  float _mu1_segmentCompatibility;
  float _mu1_leptonMVA;
  bool _mu1_mediumID;
  float _mu1_dpt_div_pt;
  bool _mu1_isfakeablesel;
  bool _mu1_ismvasel;

  float _ele0_pt;
  float _ele0_conept;
  float _ele0_eta;
  float _ele0_phi;
  float _ele0_E;
  int   _ele0_charge;
  int   _ele0_jetNDauChargedMVASel;
  float _ele0_miniRelIso;
  float _ele0_miniIsoCharged;
  float _ele0_miniIsoNeutral;
  float _ele0_jetPtRel;
  float _ele0_jetPtRatio;
  float _ele0_jetCSV;
  float _ele0_sip3D;
  float _ele0_dxy;
  float _ele0_dz;
  float _ele0_ntMVAeleID;
  float _ele0_leptonMVA;
  bool _ele0_isChargeConsistent;
  bool _ele0_passesConversionVeto;
  int _ele0_nMissingHits;
  bool _ele0_isfakeablesel;
  bool _ele0_ismvasel;

  float _ele1_pt;
  float _ele1_conept;
  float _ele1_eta;
  float _ele1_phi;
  float _ele1_E;
  int   _ele1_charge;
  int   _ele1_jetNDauChargedMVASel;
  float _ele1_miniRelIso;
  float _ele1_miniIsoCharged;
  float _ele1_miniIsoNeutral;
  float _ele1_jetPtRel;
  float _ele1_jetPtRatio;
  float _ele1_jetCSV;
  float _ele1_sip3D;
  float _ele1_dxy;
  float _ele1_dz;
  float _ele1_ntMVAeleID;
  float _ele1_leptonMVA;
  bool _ele1_isChargeConsistent;
  bool _ele1_passesConversionVeto;
  int _ele1_nMissingHits;
  bool _ele1_isfakeablesel;
  bool _ele1_ismvasel;

  float _tau0_pt;
  float _tau0_eta;
  float _tau0_phi;
  float _tau0_E;
  int _tau0_charge;
  float _tau0_dxy;
  float _tau0_dz;
  int _tau0_decayModeFindingOldDMs;
  int _tau0_decayModeFindingNewDMs;
  float _tau0_byCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_againstMuonLoose3;
  int _tau0_againstMuonTight3;
  int _tau0_againstElectronVLooseMVA6;
  int _tau0_againstElectronLooseMVA6;
  int _tau0_againstElectronMediumMVA6;
  int _tau0_againstElectronTightMVA6;
  int _tau0_againstElectronVTightMVA6;

  float _tau1_pt;
  float _tau1_eta;
  float _tau1_phi;
  float _tau1_E;
  int _tau1_charge;
  float _tau1_dxy;
  float _tau1_dz;
  int _tau1_decayModeFindingOldDMs;
  int _tau1_decayModeFindingNewDMs;
  float _tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_againstMuonLoose3;
  int _tau1_againstMuonTight3;
  int _tau1_againstElectronVLooseMVA6;
  int _tau1_againstElectronLooseMVA6;
  int _tau1_againstElectronMediumMVA6;
  int _tau1_againstElectronTightMVA6;
  int _tau1_againstElectronVTightMVA6;

  float _jet0_pt;
  float _jet0_eta;
  float _jet0_phi;
  float _jet0_E;
  float _jet0_CSV;
	
  float _jet1_pt;
  float _jet1_eta;
  float _jet1_phi;
  float _jet1_E;
  float _jet1_CSV;
	
  float _jet2_pt;
  float _jet2_eta;
  float _jet2_phi;
  float _jet2_E;
  float _jet2_CSV;
	
  float _jet3_pt;
  float _jet3_eta;
  float _jet3_phi;
  float _jet3_E;
  float _jet3_CSV;

  float _PFMET;
  float _PFMETphi;
  float _MHT;
  float _metLD;

  float _lep0_conept;
  float _lep1_conept;
  float _mindr_lep0_jet;
  float _mindr_lep1_jet;
  float _MT_met_lep0;
  float _avg_dr_jet;
  float _MVA_2lss_ttV;
  float _MVA_2lss_ttbar;


  tree_new->Branch("nEvent",        &_nEvent,         "nEvent/L");
  tree_new->Branch("ls",            &_ls,             "ls/I");
  tree_new->Branch("run",           &_run,            "run/I");

  tree_new->Branch("n_presel_mu",      &_n_presel_mu,      "n_presel_mu/I");
  tree_new->Branch("n_fakeablesel_mu", &_n_fakeablesel_mu, "n_fakeablesel_mu/I");
  tree_new->Branch("n_mvasel_mu",      &_n_mvasel_mu,      "n_mvasel_mu/I");

  tree_new->Branch("n_presel_ele",      &_n_presel_ele,      "n_presel_ele/I");
  tree_new->Branch("n_fakeablesel_ele", &_n_fakeablesel_ele, "n_fakeablesel_ele/I");
  tree_new->Branch("n_mvasel_ele",      &_n_mvasel_ele,      "n_mvasel_ele/I");

  tree_new->Branch("n_presel_tau",  &_n_presel_tau,   "n_presel_tau/I");
  tree_new->Branch("n_presel_jet",  &_n_presel_jet,   "n_presel_jet/I");

  tree_new->Branch("mu0_pt",        &_mu0_pt,         "mu0_pt/F");
  tree_new->Branch("mu0_conept",    &_mu0_conept,     "mu0_conept/F");
  tree_new->Branch("mu0_eta",       &_mu0_eta,        "mu0_eta/F");
  tree_new->Branch("mu0_phi",       &_mu0_phi,        "mu0_phi/F");
  tree_new->Branch("mu0_E",         &_mu0_E,          "mu0_E/F");
  tree_new->Branch("mu0_charge",    &_mu0_charge,     "mu0_charge/I");
  tree_new->Branch("mu0_jetNDauChargedMVASel",&_mu0_jetNDauChargedMVASel,"mu0_jetNDauChargedMVASel/I");
  tree_new->Branch("mu0_miniRelIso",          &_mu0_miniRelIso,          "mu0_miniRelIso/F");
  tree_new->Branch("mu0_miniIsoCharged",      &_mu0_miniIsoCharged,      "mu0_miniIsoCharged/F");
  tree_new->Branch("mu0_miniIsoNeutral",      &_mu0_miniIsoNeutral,      "mu0_miniIsoNeutral/F");
  tree_new->Branch("mu0_jetPtRel",  &_mu0_jetPtRel,   "mu0_jetPtRel/F");
  tree_new->Branch("mu0_jetPtRatio",&_mu0_jetPtRatio, "mu0_jetPtRatio/F");
  tree_new->Branch("mu0_jetCSV",    &_mu0_jetCSV,     "mu0_jetCSV/F");
  tree_new->Branch("mu0_sip3D",     &_mu0_sip3D,      "mu0_sip3D/F");
  tree_new->Branch("mu0_dxy",       &_mu0_dxy,        "mu0_dxy/F");
  tree_new->Branch("mu0_dz",        &_mu0_dz,         "mu0_dz/F");
  tree_new->Branch("mu0_segmentCompatibility",&_mu0_segmentCompatibility,"mu0_segmentCompatibility/F");
  tree_new->Branch("mu0_leptonMVA",     &_mu0_leptonMVA,     "mu0_leptonMVA/F");
  tree_new->Branch("mu0_mediumID",      &_mu0_mediumID,      "mu0_mediumID/O");
  tree_new->Branch("mu0_dpt_div_pt",    &_mu0_dpt_div_pt,    "mu0_dpt_div_pt/F");
  tree_new->Branch("mu0_isfakeablesel", &_mu0_isfakeablesel, "mu0_isfakeablesel/O");
  tree_new->Branch("mu0_ismvasel",      &_mu0_ismvasel,      "mu0_ismvasel/O");


  tree_new->Branch("mu1_pt",        &_mu1_pt,         "mu1_pt/F");
  tree_new->Branch("mu1_conept",    &_mu1_conept,     "mu1_conept/F");
  tree_new->Branch("mu1_eta",       &_mu1_eta,        "mu1_eta/F");
  tree_new->Branch("mu1_phi",       &_mu1_phi,        "mu1_phi/F");
  tree_new->Branch("mu1_E",         &_mu1_E,          "mu1_E/F");
  tree_new->Branch("mu1_charge",    &_mu1_charge,     "mu1_charge/I");
  tree_new->Branch("mu1_jetNDauChargedMVASel",&_mu1_jetNDauChargedMVASel,"mu1_jetNDauChargedMVASel/I");
  tree_new->Branch("mu1_miniRelIso",          &_mu1_miniRelIso,          "mu1_miniRelIso/F");
  tree_new->Branch("mu1_miniIsoCharged",      &_mu1_miniIsoCharged,      "mu1_miniIsoCharged/F");
  tree_new->Branch("mu1_miniIsoNeutral",      &_mu1_miniIsoNeutral,      "mu1_miniIsoNeutral/F");
  tree_new->Branch("mu1_jetPtRel",  &_mu1_jetPtRel,   "mu1_jetPtRel/F");
  tree_new->Branch("mu1_jetPtRatio",&_mu1_jetPtRatio, "mu1_jetPtRatio/F");
  tree_new->Branch("mu1_jetCSV",    &_mu1_jetCSV,     "mu1_jetCSV/F");
  tree_new->Branch("mu1_sip3D",     &_mu1_sip3D,      "mu1_sip3D/F");
  tree_new->Branch("mu1_dxy",       &_mu1_dxy,        "mu1_dxy/F");
  tree_new->Branch("mu1_dz",        &_mu1_dz,         "mu1_dz/F");
  tree_new->Branch("mu1_segmentCompatibility",&_mu1_segmentCompatibility,"mu1_segmentCompatibility/F");
  tree_new->Branch("mu1_leptonMVA",&_mu1_leptonMVA,"mu1_leptonMVA/F");
  tree_new->Branch("mu1_mediumID",      &_mu1_mediumID,      "mu1_mediumID/O");
  tree_new->Branch("mu1_dpt_div_pt",    &_mu1_dpt_div_pt,    "mu1_dpt_div_pt/F");
  tree_new->Branch("mu1_isfakeablesel", &_mu1_isfakeablesel, "mu1_isfakeablesel/O");
  tree_new->Branch("mu1_ismvasel",      &_mu1_ismvasel,      "mu1_ismvasel/O");

  tree_new->Branch("ele0_pt",        &_ele0_pt,         "ele0_pt/F");
  tree_new->Branch("ele0_conept",    &_ele0_conept,     "ele0_conept/F");
  tree_new->Branch("ele0_eta",       &_ele0_eta,        "ele0_eta/F");
  tree_new->Branch("ele0_phi",       &_ele0_phi,        "ele0_phi/F");
  tree_new->Branch("ele0_E",         &_ele0_E,          "ele0_E/F");
  tree_new->Branch("ele0_charge",    &_ele0_charge,     "ele0_charge/I");
  tree_new->Branch("ele0_jetNDauChargedMVASel",&_ele0_jetNDauChargedMVASel,"ele0_jetNDauChargedMVASel/I");
  tree_new->Branch("ele0_miniRelIso",          &_ele0_miniRelIso,          "ele0_miniRelIso/F");
  tree_new->Branch("ele0_miniIsoCharged",      &_ele0_miniIsoCharged,      "ele0_miniIsoCharged/F");
  tree_new->Branch("ele0_miniIsoNeutral",      &_ele0_miniIsoNeutral,      "ele0_miniIsoNeutral/F");
  tree_new->Branch("ele0_jetPtRel",  &_ele0_jetPtRel,   "ele0_jetPtRel/F");
  tree_new->Branch("ele0_jetPtRatio",&_ele0_jetPtRatio, "ele0_jetPtRatio/F");
  tree_new->Branch("ele0_jetCSV",    &_ele0_jetCSV,     "ele0_jetCSV/F");
  tree_new->Branch("ele0_sip3D",     &_ele0_sip3D,      "ele0_sip3D/F");
  tree_new->Branch("ele0_dxy",       &_ele0_dxy,        "ele0_dxy/F");
  tree_new->Branch("ele0_dz",        &_ele0_dz,         "ele0_dz/F");
  tree_new->Branch("ele0_ntMVAeleID",&_ele0_ntMVAeleID, "ele0_ntMVAeleID/F");
  tree_new->Branch("ele0_leptonMVA", &_ele0_leptonMVA,  "ele0_leptonMVA/F");
  tree_new->Branch("ele0_isChargeConsistent",   &_ele0_isChargeConsistent,    "ele0_isChargeConsistent/O");
  tree_new->Branch("ele0_passesConversionVeto", &_ele0_passesConversionVeto,  "ele0_passesConversionVeto/O");
  tree_new->Branch("ele0_nMissingHits",  &_ele0_nMissingHits,  "ele0_nMissingHits/I");
  tree_new->Branch("ele0_isfakeablesel", &_ele0_isfakeablesel, "ele0_isfakeablesel/O");
  tree_new->Branch("ele0_ismvasel",      &_ele0_ismvasel,      "ele0_ismvasel/O");

  tree_new->Branch("ele1_pt",        &_ele1_pt,         "ele1_pt/F");
  tree_new->Branch("ele1_conept",    &_ele1_conept,     "ele1_conept/F");
  tree_new->Branch("ele1_eta",       &_ele1_eta,        "ele1_eta/F");
  tree_new->Branch("ele1_phi",       &_ele1_phi,        "ele1_phi/F");
  tree_new->Branch("ele1_E",         &_ele1_E,          "ele1_E/F");
  tree_new->Branch("ele1_charge",    &_ele1_charge,     "ele1_charge/I");
  tree_new->Branch("ele1_jetNDauChargedMVASel",&_ele1_jetNDauChargedMVASel,"ele1_jetNDauChargedMVASel/I");
  tree_new->Branch("ele1_miniRelIso",          &_ele1_miniRelIso,          "ele1_miniRelIso/F");
  tree_new->Branch("ele1_miniIsoCharged",      &_ele1_miniIsoCharged,      "ele1_miniIsoCharged/F");
  tree_new->Branch("ele1_miniIsoNeutral",      &_ele1_miniIsoNeutral,      "ele1_miniIsoNeutral/F");
  tree_new->Branch("ele1_jetPtRel",  &_ele1_jetPtRel,   "ele1_jetPtRel/F");
  tree_new->Branch("ele1_jetPtRatio",&_ele1_jetPtRatio, "ele1_jetPtRatio/F");
  tree_new->Branch("ele1_jetCSV",    &_ele1_jetCSV,     "ele1_jetCSV/F");
  tree_new->Branch("ele1_sip3D",     &_ele1_sip3D,      "ele1_sip3D/F");
  tree_new->Branch("ele1_dxy",       &_ele1_dxy,        "ele1_dxy/F");
  tree_new->Branch("ele1_dz",        &_ele1_dz,         "ele1_dz/F");
  tree_new->Branch("ele1_ntMVAeleID",&_ele1_ntMVAeleID, "ele1_ntMVAeleID/F");
  tree_new->Branch("ele1_leptonMVA", &_ele1_leptonMVA,  "ele1_leptonMVA/F");
  tree_new->Branch("ele1_isChargeConsistent",   &_ele1_isChargeConsistent,    "ele1_isChargeConsistent/O");
  tree_new->Branch("ele1_passesConversionVeto", &_ele1_passesConversionVeto,  "ele1_passesConversionVeto/O");
  tree_new->Branch("ele1_nMissingHits",  &_ele1_nMissingHits,  "ele1_nMissingHits/I");
  tree_new->Branch("ele1_isfakeablesel", &_ele1_isfakeablesel, "ele1_isfakeablesel/O");
  tree_new->Branch("ele1_ismvasel",      &_ele1_ismvasel,      "ele1_ismvasel/O");

  tree_new->Branch("tau0_pt",        &_tau0_pt,         "tau0_pt/F");
  tree_new->Branch("tau0_eta",       &_tau0_eta,        "tau0_eta/F");
  tree_new->Branch("tau0_phi",       &_tau0_phi,        "tau0_phi/F");
  tree_new->Branch("tau0_E",         &_tau0_E,          "tau0_E/F");
  tree_new->Branch("tau0_charge",    &_tau0_charge,     "tau0_charge/I");
  tree_new->Branch("tau0_dxy",       &_tau0_dxy,        "tau0_dxy/F");
  tree_new->Branch("tau0_dz",        &_tau0_dz,         "tau0_dz/F");
  tree_new->Branch("tau0_decayModeFindingOldDMs",                       &_tau0_decayModeFindingOldDMs,                       "tau0_decayModeFindingOldDMs/I");
  tree_new->Branch("tau0_decayModeFindingNewDMs",                       &_tau0_decayModeFindingNewDMs,                       "tau0_decayModeFindingNewDMs/I");
  tree_new->Branch("tau0_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau0_byCombinedIsolationDeltaBetaCorr3Hits,        "tau0_byCombinedIsolationDeltaBetaCorr3Hits/F");
  tree_new->Branch("tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau0_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau0_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau0_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau0_againstMuonLoose3",         &_tau0_againstMuonLoose3,         "tau0_againstMuonLoose3/I");                         
  tree_new->Branch("tau0_againstMuonTight3",         &_tau0_againstMuonTight3,         "tau0_againstMuonTight3/I");                         
  tree_new->Branch("tau0_againstElectronVLooseMVA6", &_tau0_againstElectronVLooseMVA6, "tau0_againstElectronVLooseMVA6/I");                         
  tree_new->Branch("tau0_againstElectronLooseMVA6",  &_tau0_againstElectronLooseMVA6,  "tau0_againstElectronLooseMVA6/I");                         
  tree_new->Branch("tau0_againstElectronMediumMVA6", &_tau0_againstElectronMediumMVA6, "tau0_againstElectronMediumMVA6/I");                         
  tree_new->Branch("tau0_againstElectronTightMVA6",  &_tau0_againstElectronTightMVA6,  "tau0_againstElectronTightMVA6/I");   
  tree_new->Branch("tau0_againstElectronVTightMVA6", &_tau0_againstElectronVTightMVA6, "tau0_againstElectronVTightMVA6/I");   

  tree_new->Branch("tau1_pt",        &_tau1_pt,         "tau1_pt/F");
  tree_new->Branch("tau1_eta",       &_tau1_eta,        "tau1_eta/F");
  tree_new->Branch("tau1_phi",       &_tau1_phi,        "tau1_phi/F");
  tree_new->Branch("tau1_E",         &_tau1_E,          "tau1_E/F");
  tree_new->Branch("tau1_charge",    &_tau1_charge,     "tau1_charge/I");
  tree_new->Branch("tau1_dxy",       &_tau1_dxy,        "tau1_dxy/F");
  tree_new->Branch("tau1_dz",        &_tau1_dz,         "tau1_dz/F");
  tree_new->Branch("tau1_decayModeFindingOldDMs",                       &_tau1_decayModeFindingOldDMs,                       "tau1_decayModeFindingOldDMs/I");
  tree_new->Branch("tau1_decayModeFindingNewDMs",                       &_tau1_decayModeFindingNewDMs,                       "tau1_decayModeFindingNewDMs/I");
  tree_new->Branch("tau1_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau1_byCombinedIsolationDeltaBetaCorr3Hits,        "tau1_byCombinedIsolationDeltaBetaCorr3Hits/F");
  tree_new->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
  tree_new->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
  tree_new->Branch("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
  tree_new->Branch("tau1_againstMuonLoose3",         &_tau1_againstMuonLoose3,         "tau1_againstMuonLoose3/I");                         
  tree_new->Branch("tau1_againstMuonTight3",         &_tau1_againstMuonTight3,         "tau1_againstMuonTight3/I");                         
  tree_new->Branch("tau1_againstElectronVLooseMVA6", &_tau1_againstElectronVLooseMVA6, "tau1_againstElectronVLooseMVA6/I");                         
  tree_new->Branch("tau1_againstElectronLooseMVA6",  &_tau1_againstElectronLooseMVA6,  "tau1_againstElectronLooseMVA6/I");                         
  tree_new->Branch("tau1_againstElectronMediumMVA6", &_tau1_againstElectronMediumMVA6, "tau1_againstElectronMediumMVA6/I");                         
  tree_new->Branch("tau1_againstElectronTightMVA6",  &_tau1_againstElectronTightMVA6,  "tau1_againstElectronTightMVA6/I");   
  tree_new->Branch("tau1_againstElectronVTightMVA6", &_tau1_againstElectronVTightMVA6,  "tau1_againstElectronVTightMVA6/I");   
                      
  tree_new->Branch("jet0_pt",  &_jet0_pt,  "jet0_pt/F");
  tree_new->Branch("jet0_eta", &_jet0_eta, "jet0_eta/F");
  tree_new->Branch("jet0_phi", &_jet0_phi, "jet0_phi/F");
  tree_new->Branch("jet0_E",   &_jet0_E,   "jet0_E/F");
  tree_new->Branch("jet0_CSV", &_jet0_CSV, "jet0_CSV/F");
			       
  tree_new->Branch("jet1_pt",  &_jet1_pt,  "jet1_pt/F");
  tree_new->Branch("jet1_eta", &_jet1_eta, "jet1_eta/F");
  tree_new->Branch("jet1_phi", &_jet1_phi, "jet1_phi/F");
  tree_new->Branch("jet1_E",   &_jet1_E,   "jet1_E/F");
  tree_new->Branch("jet1_CSV", &_jet1_CSV, "jet1_CSV/F");
  			       
  tree_new->Branch("jet2_pt",  &_jet2_pt,  "jet2_pt/F");
  tree_new->Branch("jet2_eta", &_jet2_eta, "jet2_eta/F");
  tree_new->Branch("jet2_phi", &_jet2_phi, "jet2_phi/F");
  tree_new->Branch("jet2_E",   &_jet2_E,   "jet2_E/F");
  tree_new->Branch("jet2_CSV", &_jet2_CSV, "jet2_CSV/F");
			       
  tree_new->Branch("jet3_pt",  &_jet3_pt,  "jet3_pt/F");
  tree_new->Branch("jet3_eta", &_jet3_eta, "jet3_eta/F");
  tree_new->Branch("jet3_phi", &_jet3_phi, "jet3_phi/F");
  tree_new->Branch("jet3_E",   &_jet3_E,   "jet3_E/F");
  tree_new->Branch("jet3_CSV", &_jet3_CSV, "jet3_CSV/F");
  			       
  tree_new->Branch("PFMET",    &_PFMET,    "PFMET/F");
  tree_new->Branch("PFMETphi", &_PFMETphi, "PFMETphi/F");
  tree_new->Branch("MHT",      &_MHT,       "MHT/F");
  tree_new->Branch("metLD",    &_metLD,     "metLD/F");

  tree_new->Branch("lep0_conept",    &_lep0_conept,     "lep0_conept/F");
  tree_new->Branch("lep1_conept",    &_lep1_conept,     "lep1_conept/F");
  tree_new->Branch("mindr_lep0_jet", &_mindr_lep0_jet,  "mindr_lep0_jet/F");
  tree_new->Branch("mindr_lep1_jet", &_mindr_lep1_jet,  "mindr_lep1_jet/F");
  tree_new->Branch("MT_met_lep0",    &_MT_met_lep0,     "MT_met_lep0/F");
  tree_new->Branch("avg_dr_jet",     &_avg_dr_jet,      "avg_dr_jet/F");
  tree_new->Branch("MVA_2lss_ttV",   &_MVA_2lss_ttV,    "MVA_2lss_ttV/F");
  tree_new->Branch("MVA_2lss_ttbar", &_MVA_2lss_ttbar,  "MVA_2lss_ttbar/F");


  //Old branches used
  tree->SetBranchAddress("EventNumber",&_nEvent);
  tree->SetBranchAddress("lumi",&_ls);
  tree->SetBranchAddress("RunNumber",&_run);

  tree->SetBranchAddress("n_recomu_presel",&_n_presel_mu);
  tree->SetBranchAddress("n_recomu_fakeable",&_n_fakeablesel_mu);
  tree->SetBranchAddress("n_recomu_mvasel",&_n_mvasel_mu);

  tree->SetBranchAddress("n_recoele_presel",&_n_presel_ele);
  tree->SetBranchAddress("n_recoele_fakeable",&_n_fakeablesel_ele);
  tree->SetBranchAddress("n_recoele_mvasel",&_n_mvasel_ele);

  tree->SetBranchAddress("n_recotauh",&_n_presel_tau);
  tree->SetBranchAddress("n_recoPFJet",&_n_presel_jet);

  vector<float> *_recomu_pt;
  vector<float> *_recomu_conept;
  vector<float> *_recomu_eta;
  vector<float> *_recomu_phi;
  vector<float> *_recomu_e;
  vector<int>   *_recomu_charge;
  vector<int>   *_recomu_jetNDauChargedMVASel;
  vector<float> *_recomu_miniRelIso;
  vector<float> *_recomu_miniIsoCharged;
  vector<float> *_recomu_miniIsoNeutral;
  vector<float> *_recomu_jetPtRel;
  vector<float> *_recomu_jetPtRatio;
  vector<float> *_recomu_jetCSV;
  vector<float> *_recomu_sip3D;
  vector<float> *_recomu_dxy;
  vector<float> *_recomu_dz;
  vector<float> *_recomu_lepMVA_mvaId;
  vector<float> *_recomu_leptonMVA;
  vector<bool>  *_recomu_mediumID;
  vector<float> *_recomu_rel_error_trackpt;
  vector<bool>  *_recomu_isfakeable;
  vector<bool>  *_recomu_ismvasel;

  vector<float> *_recoele_pt;
  vector<float> *_recoele_conept;
  vector<float> *_recoele_eta;
  vector<float> *_recoele_phi;
  vector<float> *_recoele_e;
  vector<int>   *_recoele_charge;
  vector<int>   *_recoele_jetNDauChargedMVASel;
  vector<float> *_recoele_miniRelIso;
  vector<float> *_recoele_miniIsoCharged;
  vector<float> *_recoele_miniIsoNeutral;
  vector<float> *_recoele_jetPtRel;
  vector<float> *_recoele_jetPtRatio;
  vector<float> *_recoele_jetCSV;
  vector<float> *_recoele_sip3D;
  vector<float> *_recoele_dxy;
  vector<float> *_recoele_dz;
  vector<float> *_recoele_lepMVA_mvaId;
  vector<float> *_recoele_leptonMVA;
  vector<bool>  *_recoele_isChargeConsistent;
  vector<bool>  *_recoele_passConversionVeto;
  vector<int>   *_recoele_nMissingHits;
  vector<bool>  *_recoele_isfakeable;
  vector<bool>  *_recoele_ismvasel;

  vector<float> *_recotauh_pt;
  vector<float> *_recotauh_eta;
  vector<float> *_recotauh_phi;
  vector<float> *_recotauh_e;
  vector<int>   *_recotauh_charge;
  vector<float> *_recotauh_dxy;
  vector<float> *_recotauh_dz;
  vector<float> *_recotauh_iso;
  vector<int>  *_recotauh_decayModeFindingOldDMs;
  vector<int>  *_recotauh_decayModeFindingNewDMs;
  vector<int>  *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_againstMuonLoose3;
  vector<int>  *_recotauh_againstMuonTight3;
  vector<int>  *_recotauh_againstElectronVLooseMVA6;
  vector<int>  *_recotauh_againstElectronLooseMVA6;
  vector<int>  *_recotauh_againstElectronMediumMVA6;
  vector<int>  *_recotauh_againstElectronTightMVA6;
  vector<int>  *_recotauh_againstElectronVTightMVA6;

  vector<float> *_recoPFJet_pt;
  vector<float> *_recoPFJet_eta;
  vector<float> *_recoPFJet_phi;
  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_CSVscore;
  

  tree->SetBranchAddress("recomu_pt",                   &_recomu_pt);
  tree->SetBranchAddress("recomu_conept",               &_recomu_conept);
  tree->SetBranchAddress("recomu_eta",                  &_recomu_eta);
  tree->SetBranchAddress("recomu_phi",                  &_recomu_phi);
  tree->SetBranchAddress("recomu_e",                    &_recomu_e);
  tree->SetBranchAddress("recomu_charge",               &_recomu_charge);
  tree->SetBranchAddress("recomu_jetNDauChargedMVASel", &_recomu_jetNDauChargedMVASel);
  tree->SetBranchAddress("recomu_miniRelIso",           &_recomu_miniRelIso);
  tree->SetBranchAddress("recomu_miniIsoCharged",       &_recomu_miniIsoCharged);
  tree->SetBranchAddress("recomu_miniIsoNeutral",       &_recomu_miniIsoNeutral);
  tree->SetBranchAddress("recomu_jetPtRel",             &_recomu_jetPtRel);
  tree->SetBranchAddress("recomu_jetPtRatio",           &_recomu_jetPtRatio);
  tree->SetBranchAddress("recomu_jetCSV",               &_recomu_jetCSV);
  tree->SetBranchAddress("recomu_sip3D",                &_recomu_sip3D);
  tree->SetBranchAddress("recomu_dxy",                  &_recomu_dxy);
  tree->SetBranchAddress("recomu_dz",                   &_recomu_dz);
  tree->SetBranchAddress("recomu_lepMVA_mvaId",         &_recomu_lepMVA_mvaId);
  tree->SetBranchAddress("recomu_leptonMVA",            &_recomu_leptonMVA);
  tree->SetBranchAddress("recomu_mediumID",             &_recomu_mediumID);
  tree->SetBranchAddress("recomu_rel_error_trackpt",    &_recomu_rel_error_trackpt);
  tree->SetBranchAddress("recomu_isfakeable",           &_recomu_isfakeable);
  tree->SetBranchAddress("recomu_ismvasel",             &_recomu_ismvasel);

  tree->SetBranchAddress("recoele_pt",                  &_recoele_pt);
  tree->SetBranchAddress("recoele_conept",              &_recoele_conept);
  tree->SetBranchAddress("recoele_eta",                 &_recoele_eta);
  tree->SetBranchAddress("recoele_phi",                 &_recoele_phi);
  tree->SetBranchAddress("recoele_e",                   &_recoele_e);
  tree->SetBranchAddress("recoele_charge",              &_recoele_charge);
  tree->SetBranchAddress("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
  tree->SetBranchAddress("recoele_miniRelIso",          &_recoele_miniRelIso);
  tree->SetBranchAddress("recoele_miniIsoCharged",      &_recoele_miniIsoCharged);
  tree->SetBranchAddress("recoele_miniIsoNeutral",      &_recoele_miniIsoNeutral);
  tree->SetBranchAddress("recoele_jetPtRel",            &_recoele_jetPtRel);
  tree->SetBranchAddress("recoele_jetPtRatio",          &_recoele_jetPtRatio);
  tree->SetBranchAddress("recoele_jetCSV",              &_recoele_jetCSV);
  tree->SetBranchAddress("recoele_sip3D",               &_recoele_sip3D);
  tree->SetBranchAddress("recoele_dxy",                 &_recoele_dxy);
  tree->SetBranchAddress("recoele_dz",                  &_recoele_dz);
  tree->SetBranchAddress("recoele_lepMVA_mvaId",        &_recoele_lepMVA_mvaId);
  tree->SetBranchAddress("recoele_leptonMVA",           &_recoele_leptonMVA);
  tree->SetBranchAddress("recoele_isChargeConsistent",  &_recoele_isChargeConsistent);
  tree->SetBranchAddress("recoele_passConversionVeto",  &_recoele_passConversionVeto);
  tree->SetBranchAddress("recoele_nMissingHits",        &_recoele_nMissingHits);
  tree->SetBranchAddress("recoele_isfakeable",          &_recoele_isfakeable);
  tree->SetBranchAddress("recoele_ismvasel",            &_recoele_ismvasel);


  tree->SetBranchAddress("recotauh_pt",                 &_recotauh_pt);
  tree->SetBranchAddress("recotauh_eta",                &_recotauh_eta);
  tree->SetBranchAddress("recotauh_phi",                &_recotauh_phi);
  tree->SetBranchAddress("recotauh_e",                  &_recotauh_e);
  tree->SetBranchAddress("recotauh_charge",             &_recotauh_charge);
  tree->SetBranchAddress("recotauh_dxy",                &_recotauh_dxy);
  tree->SetBranchAddress("recotauh_dz",                 &_recotauh_dz);
  tree->SetBranchAddress("recotauh_iso",                &_recotauh_iso);
  tree->SetBranchAddress("recotauh_decayModeFindingOldDMs", &_recotauh_decayModeFindingOldDMs);
  tree->SetBranchAddress("recotauh_decayModeFindingNewDMs", &_recotauh_decayModeFindingNewDMs);
  tree->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  tree->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",     &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  tree->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
  tree->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree->SetBranchAddress("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_againstMuonLoose3",           &_recotauh_againstMuonLoose3);
  tree->SetBranchAddress("recotauh_againstMuonTight3",           &_recotauh_againstMuonTight3);
  tree->SetBranchAddress("recotauh_againstElectronVLooseMVA6",   &_recotauh_againstElectronVLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronLooseMVA6",    &_recotauh_againstElectronLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronMediumMVA6",   &_recotauh_againstElectronMediumMVA6);
  tree->SetBranchAddress("recotauh_againstElectronTightMVA6",    &_recotauh_againstElectronTightMVA6);
  tree->SetBranchAddress("recotauh_againstElectronVTightMVA6",   &_recotauh_againstElectronVTightMVA6);

  tree->SetBranchAddress("recoPFJet_pt",       &_recoPFJet_pt);
  tree->SetBranchAddress("recoPFJet_eta",      &_recoPFJet_eta);
  tree->SetBranchAddress("recoPFJet_phi",      &_recoPFJet_phi);
  tree->SetBranchAddress("recoPFJet_e",        &_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_CSVscore", &_recoPFJet_CSVscore);

  tree->SetBranchAddress("PFMET",&_PFMET);
  tree->SetBranchAddress("PFMET_phi",&_PFMETphi);
  tree->SetBranchAddress("HTmiss",&_MHT);
  tree->SetBranchAddress("ETmissLD",&_metLD);

  tree->SetBranchAddress("lep0_conept",&_lep0_conept);
  tree->SetBranchAddress("lep1_conept",&_lep1_conept);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindr_lep0_jet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindr_lep1_jet);
  tree->SetBranchAddress("MT_lep0",&_MT_met_lep0);
  tree->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lss_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lss_ttbar);


  //nentries = 100;
  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _nEvent       = -9999;
    _ls           = -9999;
    _run          = -9999;

    _n_presel_mu  = -9999;
    _n_fakeablesel_mu  = -9999;
    _n_mvasel_mu  = -9999;

    _n_presel_ele = -9999;
    _n_fakeablesel_ele  = -9999;
    _n_mvasel_ele  = -9999;

    _n_presel_tau = -9999;
    _n_presel_jet = -9999;

    _mu0_pt       = -9999;
    _mu0_conept   = -9999;
    _mu0_eta      = -9999;
    _mu0_phi      = -9999;
    _mu0_E        = -9999;
    _mu0_charge   = -9999;
    _mu0_jetNDauChargedMVASel = -9999;
    _mu0_miniRelIso           = -9999;
    _mu0_miniIsoCharged       = -9999;
    _mu0_miniIsoNeutral       = -9999;
    _mu0_jetPtRel             = -9999;
    _mu0_jetPtRatio           = -9999;
    _mu0_jetCSV               = -9999;
    _mu0_sip3D                = -9999;
    _mu0_dxy                  = -9999;
    _mu0_dz                   = -9999;
    _mu0_segmentCompatibility = -9999;
    _mu0_leptonMVA            = -9999;
    _mu0_mediumID = 0;
    _mu0_dpt_div_pt = -9999;
    _mu0_isfakeablesel = 0;
    _mu0_ismvasel = 0;

    _mu1_pt       = -9999;
    _mu1_conept   = -9999;
    _mu1_eta      = -9999;
    _mu1_phi      = -9999;
    _mu1_E        = -9999;
    _mu1_charge   = -9999;
    _mu1_jetNDauChargedMVASel = -9999;
    _mu1_miniRelIso           = -9999;
    _mu1_miniIsoCharged       = -9999;
    _mu1_miniIsoNeutral       = -9999;
    _mu1_jetPtRel             = -9999;
    _mu1_jetPtRatio           = -9999;
    _mu1_jetCSV               = -9999;
    _mu1_sip3D                = -9999;
    _mu1_dxy                  = -9999;
    _mu1_dz                   = -9999;
    _mu1_segmentCompatibility = -9999;
    _mu1_leptonMVA            = -9999;
    _mu1_mediumID = 0;
    _mu1_dpt_div_pt = -9999;
    _mu1_isfakeablesel = 0;
    _mu1_ismvasel = 0;

    _ele0_pt       = -9999;
    _ele0_conept   = -9999;
    _ele0_eta      = -9999;
    _ele0_phi      = -9999;
    _ele0_E        = -9999;
    _ele0_charge   = -9999;
    _ele0_jetNDauChargedMVASel = -9999;
    _ele0_miniRelIso           = -9999;
    _ele0_miniIsoCharged       = -9999;
    _ele0_miniIsoNeutral       = -9999;
    _ele0_jetPtRel             = -9999;
    _ele0_jetPtRatio           = -9999;
    _ele0_jetCSV               = -9999;
    _ele0_sip3D                = -9999;
    _ele0_dxy                  = -9999;
    _ele0_dz                   = -9999;
    _ele0_ntMVAeleID           = -9999;
    _ele0_leptonMVA            = -9999;
    _ele0_isChargeConsistent   = 0;
    _ele0_passesConversionVeto = 0;
    _ele0_nMissingHits         = -9999;
    _ele0_isfakeablesel       = 0;
    _ele0_ismvasel            = 0;


    _ele1_pt       = -9999;
    _ele1_conept   = -9999;
    _ele1_eta      = -9999;
    _ele1_phi      = -9999;
    _ele1_E        = -9999;
    _ele1_charge   = -9999;
    _ele1_jetNDauChargedMVASel = -9999;
    _ele1_miniRelIso           = -9999;
    _ele1_miniIsoCharged       = -9999;
    _ele1_miniIsoNeutral       = -9999;
    _ele1_jetPtRel             = -9999;
    _ele1_jetPtRatio           = -9999;
    _ele1_jetCSV               = -9999;
    _ele1_sip3D                = -9999;
    _ele1_dxy                  = -9999;
    _ele1_dz                   = -9999;
    _ele1_ntMVAeleID           = -9999;
    _ele1_leptonMVA            = -9999;
    _ele1_isChargeConsistent   = 0;
    _ele1_passesConversionVeto = 0;
    _ele1_nMissingHits         = -9999;
    _ele1_isfakeablesel       = 0;
    _ele1_ismvasel            = 0;

    _tau0_pt       = -9999;
    _tau0_eta      = -9999;
    _tau0_phi      = -9999;
    _tau0_E        = -9999;
    _tau0_charge   = -9999;    
    _tau0_dxy      = -9999;
    _tau0_dz       = -9999;
    _tau0_decayModeFindingOldDMs                           = -9999;
    _tau0_decayModeFindingNewDMs                           = -9999;
    _tau0_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau0_againstMuonLoose3          = -9999;
    _tau0_againstMuonTight3          = -9999;
    _tau0_againstElectronVLooseMVA6  = -9999;
    _tau0_againstElectronLooseMVA6   = -9999;
    _tau0_againstElectronMediumMVA6  = -9999;
    _tau0_againstElectronTightMVA6   = -9999;
    _tau0_againstElectronVTightMVA6  = -9999;

    _tau1_pt       = -9999;
    _tau1_eta      = -9999;
    _tau1_phi      = -9999;
    _tau1_E        = -9999;
    _tau1_charge   = -9999;    
    _tau1_dxy      = -9999;
    _tau1_dz       = -9999;
    _tau1_decayModeFindingOldDMs                           = -9999;
    _tau1_decayModeFindingNewDMs                           = -9999;
    _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_againstMuonLoose3          = -9999;
    _tau1_againstMuonTight3          = -9999;
    _tau1_againstElectronVLooseMVA6  = -9999;
    _tau1_againstElectronLooseMVA6   = -9999;
    _tau1_againstElectronMediumMVA6  = -9999;
    _tau1_againstElectronTightMVA6   = -9999;
    _tau1_againstElectronVTightMVA6  = -9999;
        
    _jet0_pt   = -9999;
    _jet0_eta  = -9999;
    _jet0_phi  = -9999;
    _jet0_E    = -9999;
    _jet0_CSV  = -9999;

    _jet1_pt   = -9999;
    _jet1_eta  = -9999;
    _jet1_phi  = -9999;
    _jet1_E    = -9999;
    _jet1_CSV  = -9999;

    _jet2_pt   = -9999;
    _jet2_eta  = -9999;
    _jet2_phi  = -9999;
    _jet2_E    = -9999;
    _jet2_CSV  = -9999;
	
    _jet3_pt   = -9999;
    _jet3_eta  = -9999;
    _jet3_phi  = -9999;
    _jet3_E    = -9999;
    _jet3_CSV  = -9999;

    _PFMET     = -9999;
    _PFMETphi  = -9999;    
    _MHT       = -9999;
    _metLD     = -9999;    

    _lep0_conept    = -9999;
    _lep1_conept    = -9999;
    _mindr_lep0_jet = -9999;
    _mindr_lep1_jet = -9999;
    _MT_met_lep0    = -9999;
    _avg_dr_jet     = -9999;
    _MVA_2lss_ttV   = -9999;
    _MVA_2lss_ttbar   = -9999;
    

    ////
    
    _recomu_pt      = 0;
    _recomu_conept  = 0;
    _recomu_eta     = 0;
    _recomu_phi     = 0;
    _recomu_e       = 0;
    _recomu_charge  = 0;
    _recomu_jetNDauChargedMVASel = 0;
    _recomu_miniRelIso           = 0;
    _recomu_miniIsoCharged       = 0;
    _recomu_miniIsoNeutral       = 0;
    _recomu_jetPtRel             = 0;
    _recomu_jetPtRatio           = 0;
    _recomu_jetCSV               = 0;
    _recomu_sip3D                = 0;
    _recomu_dxy                  = 0;
    _recomu_dz                   = 0;
    _recomu_lepMVA_mvaId         = 0;
    _recomu_leptonMVA            = 0;
    _recomu_mediumID             = 0;
    _recomu_rel_error_trackpt    = 0;
    _recomu_isfakeable           = 0;
    _recomu_ismvasel             = 0;

    _recoele_pt      = 0;
    _recoele_conept  = 0;
    _recoele_eta     = 0;
    _recoele_phi     = 0;
    _recoele_e       = 0;
    _recoele_charge  = 0;
    _recoele_jetNDauChargedMVASel = 0;
    _recoele_miniRelIso           = 0;
    _recoele_miniIsoCharged       = 0;
    _recoele_miniIsoNeutral       = 0;
    _recoele_jetPtRel             = 0;
    _recoele_jetPtRatio           = 0;
    _recoele_jetCSV               = 0;
    _recoele_sip3D                = 0;
    _recoele_dxy                  = 0;
    _recoele_dz                   = 0;
    _recoele_lepMVA_mvaId         = 0;
    _recoele_leptonMVA            = 0;    
    _recoele_isChargeConsistent   = 0;
    _recoele_passConversionVeto   = 0;
    _recoele_nMissingHits         = 0;
    _recoele_isfakeable           = 0;
    _recoele_ismvasel             = 0;    

    _recotauh_pt     = 0;
    _recotauh_eta    = 0;
    _recotauh_phi    = 0;
    _recotauh_e      = 0;
    _recotauh_charge = 0;
    _recotauh_dxy    = 0;
    _recotauh_dz     = 0;
    _recotauh_iso    = 0;
    _recotauh_decayModeFindingOldDMs                             = 0;
    _recotauh_decayModeFindingNewDMs                             = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits        = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03    = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_againstMuonLoose3           = 0;
    _recotauh_againstMuonTight3           = 0;
    _recotauh_againstElectronVLooseMVA6   = 0;
    _recotauh_againstElectronLooseMVA6    = 0;
    _recotauh_againstElectronMediumMVA6   = 0;
    _recotauh_againstElectronTightMVA6    = 0;
    _recotauh_againstElectronVTightMVA6   = 0;

    _recoPFJet_pt       = 0;
    _recoPFJet_eta      = 0;
    _recoPFJet_phi      = 0;
    _recoPFJet_e        = 0;
    _recoPFJet_CSVscore = 0;
   
    tree->GetEntry(i);

    if(_n_presel_mu>0){

      _mu0_pt     = (*_recomu_pt)[0];
      _mu0_conept = (*_recomu_conept)[0];
      _mu0_eta    = (*_recomu_eta)[0];
      _mu0_phi    = (*_recomu_phi)[0];
      _mu0_E      = (*_recomu_e)[0];
      _mu0_charge = (*_recomu_charge)[0];
      _mu0_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel)[0];
      _mu0_miniRelIso           = (*_recomu_miniRelIso)[0];
      _mu0_miniIsoCharged       = (*_recomu_miniIsoCharged)[0];
      _mu0_miniIsoNeutral       = (*_recomu_miniIsoNeutral)[0];
      _mu0_jetPtRel             = (*_recomu_jetPtRel)[0];
      _mu0_jetPtRatio           = (*_recomu_jetPtRatio)[0];
      _mu0_jetCSV               = (*_recomu_jetCSV)[0];
      _mu0_sip3D                = (*_recomu_sip3D)[0];
      _mu0_dxy                  = (*_recomu_dxy)[0];
      _mu0_dz                   = (*_recomu_dz)[0];
      _mu0_segmentCompatibility = (*_recomu_lepMVA_mvaId)[0];
      _mu0_leptonMVA            = (*_recomu_leptonMVA)[0];
      _mu0_mediumID             = (*_recomu_mediumID)[0];
      _mu0_dpt_div_pt           = (*_recomu_rel_error_trackpt)[0];
      _mu0_isfakeablesel        = (*_recomu_isfakeable)[0];      
      _mu0_ismvasel             = (*_recomu_ismvasel)[0];

    }

    if(_n_presel_mu>1){
      _mu1_pt     = (*_recomu_pt)[1];
      _mu1_conept = (*_recomu_conept)[1];
      _mu1_eta    = (*_recomu_eta)[1];
      _mu1_phi    = (*_recomu_phi)[1];
      _mu1_E      = (*_recomu_e)[1];
      _mu1_charge = (*_recomu_charge)[1];
      _mu1_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel)[1];
      _mu1_miniRelIso           = (*_recomu_miniRelIso)[1];
      _mu1_miniIsoCharged       = (*_recomu_miniIsoCharged)[1];
      _mu1_miniIsoNeutral       = (*_recomu_miniIsoNeutral)[1];
      _mu1_jetPtRel             = (*_recomu_jetPtRel)[1];
      _mu1_jetPtRatio           = (*_recomu_jetPtRatio)[1];
      _mu1_jetCSV               = (*_recomu_jetCSV)[1];
      _mu1_sip3D                = (*_recomu_sip3D)[1];
      _mu1_dxy                  = (*_recomu_dxy)[1];
      _mu1_dz                   = (*_recomu_dz)[1];
      _mu1_segmentCompatibility = (*_recomu_lepMVA_mvaId)[1];
      _mu1_leptonMVA            = (*_recomu_leptonMVA)[1];
      _mu1_mediumID             = (*_recomu_mediumID)[1];
      _mu1_dpt_div_pt           = (*_recomu_rel_error_trackpt)[1];
      _mu1_isfakeablesel        = (*_recomu_isfakeable)[1];      
      _mu1_ismvasel             = (*_recomu_ismvasel)[1];
    }


    if(_n_presel_ele>0){
      _ele0_pt     = (*_recoele_pt)[0];
      _ele0_conept = (*_recoele_conept)[0];
      _ele0_eta    = (*_recoele_eta)[0];
      _ele0_phi    = (*_recoele_phi)[0];
      _ele0_E      = (*_recoele_e)[0];
      _ele0_charge = (*_recoele_charge)[0];
      _ele0_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel)[0];
      _ele0_miniRelIso           = (*_recoele_miniRelIso)[0];
      _ele0_miniIsoCharged       = (*_recoele_miniIsoCharged)[0];
      _ele0_miniIsoNeutral       = (*_recoele_miniIsoNeutral)[0];
      _ele0_jetPtRel             = (*_recoele_jetPtRel)[0];
      _ele0_jetPtRatio           = (*_recoele_jetPtRatio)[0];
      _ele0_jetCSV               = (*_recoele_jetCSV)[0];
      _ele0_sip3D                = (*_recoele_sip3D)[0];
      _ele0_dxy                  = (*_recoele_dxy)[0];
      _ele0_dz                   = (*_recoele_dz)[0];
      _ele0_ntMVAeleID           = (*_recoele_lepMVA_mvaId)[0];
      _ele0_leptonMVA            = (*_recoele_leptonMVA)[0];
      _ele0_isChargeConsistent   = (*_recoele_isChargeConsistent)[0];      
      _ele0_passesConversionVeto = (*_recoele_passConversionVeto)[0];
      _ele0_nMissingHits         = (*_recoele_nMissingHits)[0];
      _ele0_isfakeablesel        = (*_recoele_isfakeable)[0];
      _ele0_ismvasel             = (*_recoele_ismvasel)[0];
    }

    if(_n_presel_ele>1){
      _ele1_pt     = (*_recoele_pt)[1];
      _ele1_conept = (*_recoele_conept)[1];
      _ele1_eta    = (*_recoele_eta)[1];
      _ele1_phi    = (*_recoele_phi)[1];
      _ele1_E      = (*_recoele_e)[1];
      _ele1_charge = (*_recoele_charge)[1];
      _ele1_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel)[1];
      _ele1_miniRelIso           = (*_recoele_miniRelIso)[1];
      _ele1_miniIsoCharged       = (*_recoele_miniIsoCharged)[1];
      _ele1_miniIsoNeutral       = (*_recoele_miniIsoNeutral)[1];
      _ele1_jetPtRel             = (*_recoele_jetPtRel)[1];
      _ele1_jetPtRatio           = (*_recoele_jetPtRatio)[1];
      _ele1_jetCSV               = (*_recoele_jetCSV)[1];
      _ele1_sip3D                = (*_recoele_sip3D)[1];
      _ele1_dxy                  = (*_recoele_dxy)[1];
      _ele1_dz                   = (*_recoele_dz)[1];
      _ele1_ntMVAeleID           = (*_recoele_lepMVA_mvaId)[1];
      _ele1_leptonMVA            = (*_recoele_leptonMVA)[1];
      _ele1_isChargeConsistent   = (*_recoele_isChargeConsistent)[1];      
      _ele1_passesConversionVeto = (*_recoele_passConversionVeto)[1];
      _ele1_nMissingHits         = (*_recoele_nMissingHits)[1];
      _ele1_isfakeablesel        = (*_recoele_isfakeable)[1];
      _ele1_ismvasel             = (*_recoele_ismvasel)[1];
    }


    if(_n_presel_tau>0){
      _tau0_pt     = (*_recotauh_pt)[0];
      _tau0_eta    = (*_recotauh_eta)[0];
      _tau0_phi    = (*_recotauh_phi)[0];
      _tau0_E      = (*_recotauh_e)[0];
      _tau0_charge = (*_recotauh_charge)[0]; 
      _tau0_dxy    = (*_recotauh_dxy)[0]; 
      _tau0_dz     = (*_recotauh_dz)[0]; 
      _tau0_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[0];
      _tau0_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[0];
      _tau0_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[0];
      _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[0];
      _tau0_againstMuonTight3          = (*_recotauh_againstMuonTight3)[0];
      _tau0_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[0];
      _tau0_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[0];
      _tau0_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[0];
      _tau0_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[0];
      _tau0_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[0];

    }

    if(_n_presel_tau>1){
      _tau1_pt     = (*_recotauh_pt)[1];
      _tau1_eta    = (*_recotauh_eta)[1];
      _tau1_phi    = (*_recotauh_phi)[1];
      _tau1_E      = (*_recotauh_e)[1];
      _tau1_charge = (*_recotauh_charge)[1];
      _tau1_dxy    = (*_recotauh_dxy)[1]; 
      _tau1_dz     = (*_recotauh_dz)[1];     
      _tau1_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[1];
      _tau1_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[1];
      _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[1];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[1];
      _tau1_againstMuonTight3          = (*_recotauh_againstMuonTight3)[1];
      _tau1_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[1];
      _tau1_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[1];
      _tau1_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[1];
      _tau1_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[1];
      _tau1_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[1];

    }
    
    if(_n_presel_jet>0){

      _jet0_pt   = (*_recoPFJet_pt)[0];
      _jet0_eta  = (*_recoPFJet_eta)[0];
      _jet0_phi  = (*_recoPFJet_phi)[0];
      _jet0_E    = (*_recoPFJet_e)[0];
      _jet0_CSV  = (*_recoPFJet_CSVscore)[0];

    }

    if(_n_presel_jet>1){

      _jet1_pt   = (*_recoPFJet_pt)[1];
      _jet1_eta  = (*_recoPFJet_eta)[1];
      _jet1_phi  = (*_recoPFJet_phi)[1];
      _jet1_E    = (*_recoPFJet_e)[1];
      _jet1_CSV  = (*_recoPFJet_CSVscore)[1];

    }

    if(_n_presel_jet>2){

      _jet2_pt   = (*_recoPFJet_pt)[2];
      _jet2_eta  = (*_recoPFJet_eta)[2];
      _jet2_phi  = (*_recoPFJet_phi)[2];
      _jet2_E    = (*_recoPFJet_e)[2];
      _jet2_CSV  = (*_recoPFJet_CSVscore)[2];

    }
  
    if(_n_presel_jet>3){

      _jet3_pt   = (*_recoPFJet_pt)[3];
      _jet3_eta  = (*_recoPFJet_eta)[3];
      _jet3_phi  = (*_recoPFJet_phi)[3];
      _jet3_E    = (*_recoPFJet_e)[3];
      _jet3_CSV  = (*_recoPFJet_CSVscore)[3];

    }

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}









void create_syncNtuple_eventbased(){


  TString dir_in="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/";
  TString dir_out="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/";
  TString file="syncNtuple_event_ttW_multilep.root";

  vector<TString> list;
  list.push_back(dir_in+"syncNtuple_ttW_multilep_split.root");


  TChain * tree_2lSS = new TChain("HTauTauTree_2lSS");
  TChain * tree_2lOS_CR = new TChain("HTauTauTree_2lOS_CR");
  TChain * tree_2lSS_lepMVA_CR = new TChain("HTauTauTree_2lSS_lepMVA_CR");
  TChain * tree_3l = new TChain("HTauTauTree_3l");
  TChain * tree_3l_lepMVA_CR = new TChain("HTauTauTree_3l_lepMVA_CR");

  vector<TChain*> tree;
  tree.push_back(tree_2lSS);
  tree.push_back(tree_2lOS_CR);
  tree.push_back(tree_2lSS_lepMVA_CR);
  tree.push_back(tree_3l);
  tree.push_back(tree_3l_lepMVA_CR);


  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree_2lSS->Add(list[i]);
      tree_2lOS_CR->Add(list[i]);
      tree_2lSS_lepMVA_CR->Add(list[i]);
      tree_3l->Add(list[i]);
      tree_3l_lepMVA_CR->Add(list[i]);
    }

  //Old branches
  ULong64_t _EventNumber;
  float _event_weight_ttH;
  vector<float> *_recolep_sel_eta;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _PFMET;
  float _HTmiss;
  float _avg_dr_jet;
  float _MT_lep0;
  float _lep0_conept;
  float _lep1_conept;
  float _lep2_conept;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;
  float _MVA_3l_ttV;
  float _MVA_3l_ttbar;
  int _category;

  vector<float> *_recoPFJet_mindR_lep;
  vector<float> *_recoPFJet_CSVscore;
  vector<float> *_recoPFJet_QGdiscr;
  vector<float> *_recoPFJet_maxdR_lep;
  vector<float> *_recoPFJet_pt;
  vector<float> *_recoPFJet_HjBDT;
		
  vector<float> *_recoPFJet_pair_Mjjlep;
  vector<float> *_recoPFJet_pair_SumHjBDT;
  vector<float> *_recoPFJet_pair_dRjj;
  vector<float> *_recoPFJet_pair_min_dRjj_jets;
  vector<float> *_recoPFJet_pair_Mjj;
  vector<float> *_recoPFJet_pair_ratio_dRjj_jets;
  vector<float> *_recoPFJet_pair_HjjBDT;


  for(unsigned int i=0;i<tree.size();i++){

    tree[i]->SetBranchAddress("EventNumber",&_EventNumber);
    tree[i]->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
    tree[i]->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree[i]->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
    tree[i]->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
    tree[i]->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
    tree[i]->SetBranchAddress("PFMET",&_PFMET);
    tree[i]->SetBranchAddress("HTmiss",&_HTmiss);
    tree[i]->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
    tree[i]->SetBranchAddress("MT_lep0",&_MT_lep0);
    tree[i]->SetBranchAddress("lep0_conept",&_lep0_conept);
    tree[i]->SetBranchAddress("lep1_conept",&_lep1_conept);
    tree[i]->SetBranchAddress("lep2_conept",&_lep2_conept);
    tree[i]->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
    tree[i]->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
    tree[i]->SetBranchAddress("MVA_3l_ttV",&_MVA_3l_ttV);
    tree[i]->SetBranchAddress("MVA_3l_ttbar",&_MVA_3l_ttbar);
    tree[i]->SetBranchAddress("category",&_category);

    tree[i]->SetBranchAddress("recoPFJet_mindR_lep",&_recoPFJet_mindR_lep);
    tree[i]->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);
    tree[i]->SetBranchAddress("recoPFJet_QGdiscr",&_recoPFJet_QGdiscr);
    tree[i]->SetBranchAddress("recoPFJet_maxdR_lep",&_recoPFJet_maxdR_lep);
    tree[i]->SetBranchAddress("recoPFJet_pt",&_recoPFJet_pt);
    tree[i]->SetBranchAddress("recoPFJet_HjBDT",&_recoPFJet_HjBDT);

    tree[i]->SetBranchAddress("recoPFJet_pair_Mjjlep",&_recoPFJet_pair_Mjjlep);
    tree[i]->SetBranchAddress("recoPFJet_pair_SumHjBDT",&_recoPFJet_pair_SumHjBDT);
    tree[i]->SetBranchAddress("recoPFJet_pair_dRjj",&_recoPFJet_pair_dRjj);
    tree[i]->SetBranchAddress("recoPFJet_pair_min_dRjj_jets",&_recoPFJet_pair_min_dRjj_jets);
    tree[i]->SetBranchAddress("recoPFJet_pair_Mjj",&_recoPFJet_pair_Mjj);
    tree[i]->SetBranchAddress("recoPFJet_pair_ratio_dRjj_jets",&_recoPFJet_pair_ratio_dRjj_jets);
    tree[i]->SetBranchAddress("recoPFJet_pair_HjjBDT",&_recoPFJet_pair_HjjBDT);

  }

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");

  TTree* tree_new_2lSS_mumu=new TTree("syncTree_2lSS_mumu","syncTree_2lSS_mumu");
  TTree* tree_new_2lOS_CR_mumu=new TTree("syncTree_2lOS_CR_mumu","syncTree_2lOS_CR_mumu");
  TTree* tree_new_2lSS_lepMVA_CR_mumu=new TTree("syncTree_2lSS_lepMVA_CR_mumu","syncTree_2lSS_lepMVA_CR_mumu");

  TTree* tree_new_2lSS_emu=new TTree("syncTree_2lSS_emu","syncTree_2lSS_emu");
  TTree* tree_new_2lOS_CR_emu=new TTree("syncTree_2lOS_CR_emu","syncTree_2lOS_CR_emu");
  TTree* tree_new_2lSS_lepMVA_CR_emu=new TTree("syncTree_2lSS_lepMVA_CR_emu","syncTree_2lSS_lepMVA_CR_emu");

  TTree* tree_new_2lSS_ee=new TTree("syncTree_2lSS_ee","syncTree_2lSS_ee");
  TTree* tree_new_2lOS_CR_ee=new TTree("syncTree_2lOS_CR_ee","syncTree_2lOS_CR_ee");
  TTree* tree_new_2lSS_lepMVA_CR_ee=new TTree("syncTree_2lSS_lepMVA_CR_ee","syncTree_2lSS_lepMVA_CR_ee");

  TTree* tree_new_2lSS_tau=new TTree("syncTree_2lSS_tau","syncTree_2lSS_tau");
  TTree* tree_new_2lOS_CR_tau=new TTree("syncTree_2lOS_CR_tau","syncTree_2lOS_CR_tau");
  TTree* tree_new_2lSS_lepMVA_CR_tau=new TTree("syncTree_2lSS_lepMVA_CR_tau","syncTree_2lSS_lepMVA_CR_tau");

  TTree* tree_new_3l=new TTree("syncTree_3l","syncTree_3l");
  TTree* tree_new_3l_lepMVA_CR=new TTree("syncTree_3l_lepMVA_CR","syncTree_3l_lepMVA_CR");

  TTree* tree_new_2lSS=new TTree("syncTree_2lSS","syncTree_2lSS");


  vector<TTree*> tree_new;
  tree_new.push_back(tree_new_2lSS_mumu);
  tree_new.push_back(tree_new_2lOS_CR_mumu);
  tree_new.push_back(tree_new_2lSS_lepMVA_CR_mumu);
  tree_new.push_back(tree_new_2lSS_emu);
  tree_new.push_back(tree_new_2lOS_CR_emu);
  tree_new.push_back(tree_new_2lSS_lepMVA_CR_emu);
  tree_new.push_back(tree_new_2lSS_ee);
  tree_new.push_back(tree_new_2lOS_CR_ee);
  tree_new.push_back(tree_new_2lSS_lepMVA_CR_ee);
  tree_new.push_back(tree_new_2lSS_tau);
  tree_new.push_back(tree_new_2lOS_CR_tau);
  tree_new.push_back(tree_new_2lSS_lepMVA_CR_tau);
  tree_new.push_back(tree_new_3l);
  tree_new.push_back(tree_new_3l_lepMVA_CR);
  tree_new.push_back(tree_new_2lSS);


  //New branches
  float _max_eta_lep;

  float _jet0_mindR_lep;
  float _jet0_CSVscore;
  float _jet0_QGdiscr;
  float _jet0_maxdR_lep;
  float _jet0_pt;
  float _jet0_HjBDT;

  float _jet01_Mjjlep;
  float _jet01_SumHjBDT;
  float _jet01_dRjj;
  float _jet01_min_dRjj_jets;
  float _jet01_Mjj;
  float _jet01_ratio_dRjj_jets;
  float _jet01_HjjBDT;

  
  for(unsigned int i=0;i<tree_new.size();i++){

    tree_new[i]->Branch("nEvent",           &_EventNumber,            "nEvent/I");
    tree_new[i]->Branch("event_weight_ttH",     &_event_weight_ttH,      "event_weight/F");
    tree_new[i]->Branch("max_eta_lep",      &_max_eta_lep,       "max_eta_lep/F");
    tree_new[i]->Branch("n_recoPFJet",      &_n_recoPFJet,       "n_recoPFJet/I");
    tree_new[i]->Branch("mindR_lep0_recoPFjet",   &_mindR_lep0_recoPFjet,    "mindR_lep0_recoPFjet/F");
    tree_new[i]->Branch("mindR_lep1_recoPFjet",   &_mindR_lep1_recoPFjet,    "mindR_lep1_recoPFjet/F");
    tree_new[i]->Branch("MET",              &_PFMET,               "PFMET/F");
    tree_new[i]->Branch("MHT",              &_HTmiss,              "HTmiss/F");
    tree_new[i]->Branch("avg_dR_jets",      &_avg_dr_jet,          "avg_dR_jets/F");
    tree_new[i]->Branch("mT_lep0",          &_MT_lep0,           "mT_lep0/F");
    tree_new[i]->Branch("pT_lep0",          &_lep0_conept,           "pT_lep0/F");
    tree_new[i]->Branch("pT_lep1",          &_lep1_conept,           "pT_lep1/F");
    tree_new[i]->Branch("pT_lep2",          &_lep2_conept,           "pT_lep2/F");
    tree_new[i]->Branch("MVA_2lSS_ttV",     &_MVA_2lSS_ttV,      "MVA_2lSS_ttV/F");
    tree_new[i]->Branch("MVA_2lSS_ttbar",   &_MVA_2lSS_ttbar,    "MVA_2lSS_ttbar/F");
    tree_new[i]->Branch("MVA_3l_ttV",       &_MVA_3l_ttV,        "MVA_3l_ttV/F");
    tree_new[i]->Branch("MVA_3l_ttbar",     &_MVA_3l_ttbar,      "MVA_3l_ttbar/F");

    tree_new[i]->Branch("jet0_mindR_lep",   &_jet0_mindR_lep,      "jet0_mindR_lep/F");
    tree_new[i]->Branch("jet0_CSVscore",    &_jet0_CSVscore,       "jet0_CSVscore/F");
    tree_new[i]->Branch("jet0_QGdiscr",     &_jet0_QGdiscr,         "jet0_QGdiscr/F");
    tree_new[i]->Branch("jet0_maxdR_lep",   &_jet0_maxdR_lep,       "jet0_maxdR_lep/F");
    tree_new[i]->Branch("jet0_pt",          &_jet0_pt,              "jet0_pt/F");
    tree_new[i]->Branch("jet0_HjBDT",       &_jet0_HjBDT,           "jet0_HjBDT/F");

    tree_new[i]->Branch("jet01_Mjjlep",     &_jet01_Mjjlep,      "jet01_Mjjlep/F");
    tree_new[i]->Branch("jet01_SumHjBDT",   &_jet01_SumHjBDT,    "jet01_SumHjBDT/F");
    tree_new[i]->Branch("jet01_dRjj",       &_jet01_dRjj,        "jet01_dRjj/F");
    tree_new[i]->Branch("jet01_min_dRjj_jets",   &_jet01_min_dRjj_jets,    "jet01_min_dRjj_jets/F");
    tree_new[i]->Branch("jet01_Mjj",   &_jet01_Mjj,    "jet01_Mjj/F");
    tree_new[i]->Branch("jet01_ratio_dRjj_jets",   &_jet01_ratio_dRjj_jets,    "jet01_ratio_dRjj_jets/F");
    tree_new[i]->Branch("jet01_HjjBDT",   &_jet01_HjjBDT,    "jet01_HjjBDT/F");

  }


  // 2lSS

  int nentries = tree_2lSS->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _EventNumber = 0;
    _event_weight_ttH = 0;
    _recolep_sel_eta = 0;
    _n_recoPFJet = 0;
    _mindR_lep0_recoPFjet = 0;
    _mindR_lep1_recoPFjet = 0;
    _PFMET = 0;
    _HTmiss = 0;
    _avg_dr_jet = 0;
    _MT_lep0 = 0;
    _lep0_conept = 0;
    _lep1_conept = 0;
    _lep2_conept = 0;
    _MVA_2lSS_ttV = 0;
    _MVA_2lSS_ttbar = 0;
    _MVA_3l_ttV = 0;
    _MVA_3l_ttbar = 0;
    _category = 0;

    _recoPFJet_mindR_lep = 0;
    _recoPFJet_CSVscore = 0;
    _recoPFJet_QGdiscr = 0;
    _recoPFJet_maxdR_lep = 0;
    _recoPFJet_pt = 0;
    _recoPFJet_HjBDT = 0;
    
    _recoPFJet_pair_Mjjlep = 0;
    _recoPFJet_pair_SumHjBDT = 0;
    _recoPFJet_pair_dRjj = 0;
    _recoPFJet_pair_min_dRjj_jets = 0;
    _recoPFJet_pair_Mjj = 0;
    _recoPFJet_pair_ratio_dRjj_jets = 0;
    _recoPFJet_pair_HjjBDT = 0;

    _max_eta_lep = 0;

    _jet0_mindR_lep = 0;
    _jet0_CSVscore = 0;
    _jet0_QGdiscr = 0;
    _jet0_maxdR_lep = 0;
    _jet0_pt = 0;
    _jet0_HjBDT = 0;
    
    _jet01_Mjjlep = 0;
    _jet01_SumHjBDT = 0;
    _jet01_dRjj = 0;
    _jet01_min_dRjj_jets = 0;
    _jet01_Mjj = 0;
    _jet01_ratio_dRjj_jets = 0;
    _jet01_HjjBDT = 0;
   
    tree_2lSS->GetEntry(i);

    _max_eta_lep = max(fabs((*_recolep_sel_eta)[0]), fabs((*_recolep_sel_eta)[1]));

    _jet0_mindR_lep = (*_recoPFJet_mindR_lep)[0];
    _jet0_CSVscore = (*_recoPFJet_CSVscore)[0];
    _jet0_QGdiscr = (*_recoPFJet_QGdiscr)[0];
    _jet0_maxdR_lep = (*_recoPFJet_maxdR_lep)[0];
    _jet0_pt = (*_recoPFJet_pt)[0];
    _jet0_HjBDT = (*_recoPFJet_HjBDT)[0];
  
    _jet01_Mjjlep = (*_recoPFJet_pair_Mjjlep)[0];
    _jet01_SumHjBDT = (*_recoPFJet_pair_SumHjBDT)[0];
    _jet01_dRjj = (*_recoPFJet_pair_dRjj)[0];
    _jet01_min_dRjj_jets = (*_recoPFJet_pair_min_dRjj_jets)[0];
    _jet01_Mjj = (*_recoPFJet_pair_Mjj)[0];
    _jet01_ratio_dRjj_jets = (*_recoPFJet_pair_ratio_dRjj_jets)[0];
    _jet01_HjjBDT = (*_recoPFJet_pair_HjjBDT)[0];
    
    if(_category>=1 && _category<=4)
      tree_new_2lSS_mumu->Fill();
    else if(_category>=5 && _category<=8)
      tree_new_2lSS_emu->Fill();
    else if(_category>=9 && _category<=10)
      tree_new_2lSS_ee->Fill();
    else if(_category==11)
      tree_new_2lSS_tau->Fill();

    if(_category!=11)
      tree_new_2lSS->Fill();

  }


  // 2lOS

  nentries = tree_2lOS_CR->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _EventNumber = 0;
    _event_weight_ttH = 0;
    _recolep_sel_eta = 0;
    _n_recoPFJet = 0;
    _mindR_lep0_recoPFjet = 0;
    _mindR_lep1_recoPFjet = 0;
    _PFMET = 0;
    _HTmiss = 0;
    _avg_dr_jet = 0;
    _MT_lep0 = 0;
    _lep0_conept = 0;
    _lep1_conept = 0;
    _lep2_conept = 0;
    _MVA_2lSS_ttV = 0;
    _MVA_2lSS_ttbar = 0;
    _MVA_3l_ttV = 0;
    _MVA_3l_ttbar = 0;
    _category = 0;

    _max_eta_lep = 0;

    tree_2lOS_CR->GetEntry(i);
 
    _max_eta_lep = max(fabs((*_recolep_sel_eta)[0]), fabs((*_recolep_sel_eta)[1]));

    if(_category==-1 || _category==-3)
      tree_new_2lOS_CR_mumu->Fill();
    else if(_category<=-5 && _category>=-8)
      tree_new_2lOS_CR_emu->Fill();
    else if(_category==-9 || _category==-10)
      tree_new_2lOS_CR_ee->Fill();
    else if(_category==-11)
      tree_new_2lOS_CR_tau->Fill();
    

  }



  // 2lSS lepMVA CR

  nentries = tree_2lSS_lepMVA_CR->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _EventNumber = 0;
    _event_weight_ttH = 0;
    _recolep_sel_eta = 0;
    _n_recoPFJet = 0;
    _mindR_lep0_recoPFjet = 0;
    _mindR_lep1_recoPFjet = 0;
    _PFMET = 0;
    _HTmiss = 0;
    _avg_dr_jet = 0;
    _MT_lep0 = 0;
    _lep0_conept = 0;
    _lep1_conept = 0;
    _lep2_conept = 0;
    _MVA_2lSS_ttV = 0;
    _MVA_2lSS_ttbar = 0;
    _MVA_3l_ttV = 0;
    _MVA_3l_ttbar = 0;
    _category = 0;

    _max_eta_lep = 0;
    

    tree_2lSS_lepMVA_CR->GetEntry(i);
 
    _max_eta_lep = max(fabs((*_recolep_sel_eta)[0]), fabs((*_recolep_sel_eta)[1]));

    if(_category>=31 && _category<=34)
      tree_new_2lSS_lepMVA_CR_mumu->Fill();
    else if(_category>=35 && _category<=38)
      tree_new_2lSS_lepMVA_CR_emu->Fill();
    else if(_category>=39 && _category<=40)
      tree_new_2lSS_lepMVA_CR_ee->Fill();
    else if(_category==41)
      tree_new_2lSS_lepMVA_CR_tau->Fill();


  }



  // 3l

  nentries = tree_3l->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _EventNumber = 0;
    _event_weight_ttH = 0;
    _recolep_sel_eta = 0;
    _n_recoPFJet = 0;
    _mindR_lep0_recoPFjet = 0;
    _mindR_lep1_recoPFjet = 0;
    _PFMET = 0;
    _HTmiss = 0;
    _avg_dr_jet = 0;
    _MT_lep0 = 0;
    _lep0_conept = 0;
    _lep1_conept = 0;
    _lep2_conept = 0;
    _MVA_2lSS_ttV = 0;
    _MVA_2lSS_ttbar = 0;
    _MVA_3l_ttV = 0;
    _MVA_3l_ttbar = 0;
    _category = 0;

    _max_eta_lep = 0;
   
    tree_3l->GetEntry(i);
 
    _max_eta_lep = max(fabs((*_recolep_sel_eta)[0]), fabs((*_recolep_sel_eta)[1]));

    if(_category>=12 && _category<=15)
      tree_new_3l->Fill();


  }


  
  // 3l lepMVA CR

  nentries = tree_3l_lepMVA_CR->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _EventNumber = 0;
    _event_weight_ttH = 0;
    _recolep_sel_eta = 0;
    _n_recoPFJet = 0;
    _mindR_lep0_recoPFjet = 0;
    _mindR_lep1_recoPFjet = 0;
    _PFMET = 0;
    _HTmiss = 0;
    _avg_dr_jet = 0;
    _MT_lep0 = 0;
    _lep0_conept = 0;
    _lep1_conept = 0;
    _lep2_conept = 0;
    _MVA_2lSS_ttV = 0;
    _MVA_2lSS_ttbar = 0;
    _MVA_3l_ttV = 0;
    _MVA_3l_ttbar = 0;
    _category = 0;

    _max_eta_lep = 0;
   
    tree_3l_lepMVA_CR->GetEntry(i);
 
    _max_eta_lep = max(fabs((*_recolep_sel_eta)[0]), fabs((*_recolep_sel_eta)[1]));

    if(_category>=42 && _category<=45)
      tree_new_3l_lepMVA_CR->Fill();

  }

  
  f_new->cd();

  for(unsigned int i=0; i<tree_new.size();i++)
    tree_new[i]->Write();

  f_new->Close();


  return;

}









void create_syncNtuple_eventbased_ttH_tautau(){

  TString dir_in="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/";
  TString dir_out="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/syncNtuples/";

  TString file="syncNtuple_event_ttH_tautau.root";    

  vector<TString> list;
  list.push_back(dir_in+"syncNtuple_ttH_tautau_prod012017_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3_BDT_3l1tau.root");
 

  TChain * tree_1l_2tau = new TChain("HTauTauTree_1l_2tau");
  TChain * tree_1l_2tau_fake_CR = new TChain("HTauTauTree_1l_2tau_fake_CR");
  TChain * tree_2lSS = new TChain("HTauTauTree_2lSS");
  TChain * tree_2lOS_CR = new TChain("HTauTauTree_2lOS_CR");
  TChain * tree_2lSS_lepMVA_CR = new TChain("HTauTauTree_2lSS_lepMVA_CR");
  TChain * tree_3l = new TChain("HTauTauTree_3l");
  TChain * tree_3l_lepMVA_CR = new TChain("HTauTauTree_3l_lepMVA_CR");

  vector<TChain*> tree;
  tree.push_back(tree_1l_2tau);
  tree.push_back(tree_1l_2tau_fake_CR);
  tree.push_back(tree_2lSS);
  tree.push_back(tree_2lOS_CR);
  tree.push_back(tree_2lSS_lepMVA_CR);
  tree.push_back(tree_3l);
  tree.push_back(tree_3l_lepMVA_CR);


  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree_1l_2tau->Add(list[i]);
      tree_1l_2tau_fake_CR->Add(list[i]);
      tree_2lSS->Add(list[i]);
      tree_2lOS_CR->Add(list[i]);
      tree_2lSS_lepMVA_CR->Add(list[i]);
      tree_3l->Add(list[i]);
      tree_3l_lepMVA_CR->Add(list[i]);
    }



  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");


  TTree* tree_new_1l_2tau=new TTree("syncTree_1l2tau_SR","syncTree_1l2tau_SR");
  TTree* tree_new_1l_2tau_fake_CR=new TTree("syncTree_1l2tau_Fake","syncTree_1l2tau_Fake");
  TTree* tree_new_2lSS_tau=new TTree("syncTree_2lSS1tau_SR","syncTree_2lSS1tau_SR");
  TTree* tree_new_2lOS_CR_tau=new TTree("syncTree_2lSS1tau_Flip","syncTree_2lSS_1tau_Flip");
  TTree* tree_new_2lSS_lepMVA_CR_tau=new TTree("syncTree_2lSS1tau_Fake","syncTree_2lSS1tau_Fake");
  TTree* tree_new_3l_tau=new TTree("syncTree_3l1tau_SR","syncTree_3l1tau_SR");
  TTree* tree_new_3l_lepMVA_CR_tau=new TTree("syncTree_3l1tau_Fake","syncTree_3l1tau_Fake");

  vector<TTree*> tree_new;
  tree_new.push_back(tree_new_1l_2tau);
  tree_new.push_back(tree_new_1l_2tau_fake_CR);
  tree_new.push_back(tree_new_2lSS_tau);
  tree_new.push_back(tree_new_2lOS_CR_tau);
  tree_new.push_back(tree_new_2lSS_lepMVA_CR_tau);
  tree_new.push_back(tree_new_3l_tau);
  tree_new.push_back(tree_new_3l_lepMVA_CR_tau);


  //New branches
  ULong64_t _nEvent;
  int _ls;
  int _run;

  int _n_presel_mu;
  int _n_fakeablesel_mu;
  int _n_mvasel_mu;

  int _n_presel_ele;
  int _n_fakeablesel_ele;
  int _n_mvasel_ele;

  int _n_presel_tau;
  int _n_presel_jet;

  float _mu0_pt;
  float _mu0_conept;
  float _mu0_eta;
  float _mu0_phi;
  float _mu0_E;
  int _mu0_charge;
  int _mu0_jetNDauChargedMVASel;
  float _mu0_miniRelIso;
  float _mu0_miniIsoCharged;
  float _mu0_miniIsoNeutral;
  float _mu0_jetPtRel;
  float _mu0_jetPtRatio;
  float _mu0_jetCSV;
  float _mu0_sip3D;
  float _mu0_dxy;
  float _mu0_dz;
  float _mu0_segmentCompatibility;
  float _mu0_leptonMVA;
  bool _mu0_mediumID;
  float _mu0_dpt_div_pt;
  bool _mu0_isfakeablesel;
  bool _mu0_ismvasel;


  float _mu1_pt;
  float _mu1_conept;
  float _mu1_eta;
  float _mu1_phi;
  float _mu1_E;
  int _mu1_charge;
  int _mu1_jetNDauChargedMVASel;
  float _mu1_miniRelIso;
  float _mu1_miniIsoCharged;
  float _mu1_miniIsoNeutral;
  float _mu1_jetPtRel;
  float _mu1_jetPtRatio;
  float _mu1_jetCSV;
  float _mu1_sip3D;
  float _mu1_dxy;
  float _mu1_dz;
  float _mu1_segmentCompatibility;
  float _mu1_leptonMVA;
  bool _mu1_mediumID;
  float _mu1_dpt_div_pt;
  bool _mu1_isfakeablesel;
  bool _mu1_ismvasel;

  float _ele0_pt;
  float _ele0_conept;
  float _ele0_eta;
  float _ele0_phi;
  float _ele0_E;
  int   _ele0_charge;
  int   _ele0_jetNDauChargedMVASel;
  float _ele0_miniRelIso;
  float _ele0_miniIsoCharged;
  float _ele0_miniIsoNeutral;
  float _ele0_jetPtRel;
  float _ele0_jetPtRatio;
  float _ele0_jetCSV;
  float _ele0_sip3D;
  float _ele0_dxy;
  float _ele0_dz;
  float _ele0_ntMVAeleID;
  float _ele0_leptonMVA;
  bool _ele0_isChargeConsistent;
  bool _ele0_passesConversionVeto;
  int _ele0_nMissingHits;
  bool _ele0_isfakeablesel;
  bool _ele0_ismvasel;

  float _ele1_pt;
  float _ele1_conept;
  float _ele1_eta;
  float _ele1_phi;
  float _ele1_E;
  int   _ele1_charge;
  int   _ele1_jetNDauChargedMVASel;
  float _ele1_miniRelIso;
  float _ele1_miniIsoCharged;
  float _ele1_miniIsoNeutral;
  float _ele1_jetPtRel;
  float _ele1_jetPtRatio;
  float _ele1_jetCSV;
  float _ele1_sip3D;
  float _ele1_dxy;
  float _ele1_dz;
  float _ele1_ntMVAeleID;
  float _ele1_leptonMVA;
  bool _ele1_isChargeConsistent;
  bool _ele1_passesConversionVeto;
  int _ele1_nMissingHits;
  bool _ele1_isfakeablesel;
  bool _ele1_ismvasel;

  float _tau0_pt;
  float _tau0_eta;
  float _tau0_phi;
  float _tau0_E;
  int _tau0_charge;
  float _tau0_dxy;
  float _tau0_dz;
  int _tau0_decayModeFindingOldDMs;
  int _tau0_decayModeFindingNewDMs;
  float _tau0_byCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_againstMuonLoose3;
  int _tau0_againstMuonTight3;
  int _tau0_againstElectronVLooseMVA6;
  int _tau0_againstElectronLooseMVA6;
  int _tau0_againstElectronMediumMVA6;
  int _tau0_againstElectronTightMVA6;
  int _tau0_againstElectronVTightMVA6;

  float _tau1_pt;
  float _tau1_eta;
  float _tau1_phi;
  float _tau1_E;
  int _tau1_charge;
  float _tau1_dxy;
  float _tau1_dz;
  int _tau1_decayModeFindingOldDMs;
  int _tau1_decayModeFindingNewDMs;
  float _tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_againstMuonLoose3;
  int _tau1_againstMuonTight3;
  int _tau1_againstElectronVLooseMVA6;
  int _tau1_againstElectronLooseMVA6;
  int _tau1_againstElectronMediumMVA6;
  int _tau1_againstElectronTightMVA6;
  int _tau1_againstElectronVTightMVA6;

  float _jet0_pt;
  float _jet0_eta;
  float _jet0_phi;
  float _jet0_E;
  float _jet0_CSV;
	
  float _jet1_pt;
  float _jet1_eta;
  float _jet1_phi;
  float _jet1_E;
  float _jet1_CSV;
	
  float _jet2_pt;
  float _jet2_eta;
  float _jet2_phi;
  float _jet2_E;
  float _jet2_CSV;
	
  float _jet3_pt;
  float _jet3_eta;
  float _jet3_phi;
  float _jet3_E;
  float _jet3_CSV;

  float _PFMET;
  float _PFMETphi;
  float _MHT;
  float _metLD;

  float _lep0_conept;
  float _lep1_conept;
  float _mindr_lep0_jet;
  float _mindr_lep1_jet;
  float _mindr_lep2_jet;
  float _mindr_tau_jet;
  float _MT_met_lep0;
  float _avg_dr_jet;
  float _MVA_2lss_ttV;
  float _MVA_2lss_ttbar;

  float _tt_deltaR;
  float _ntags;
  float _ntags_loose;
  float _tt_mvis;
  float _tt_pt;
  float _max_dr_jet;
  float _HT;
  float _MVA_1l2tau_ttbar;
  float _MVA_1l2tau_ttbar_v2;
  float _MVA_1l2tau_ttZ_v2;
  float _MVA_1l2tau_2Dbin_v2;

  float _MT_met_lep2;
  float _mvis_l1tau;
  float _dR_l0tau;
  float _dR_l1tau;
  float _dR_l2tau;


  float _MVA_3l1tau_ttbar;
  float _MVA_3l1tau_ttV;
  float _MVA_3l1tau_2Dbin;

  float _FR_weight;
  float _triggerSF_weight;
  float _leptonSF_weight;
  float _tauSF_weight;
  float _bTagSF_CSVshape_weight;
  float _PU_weight;
  float _MC_weight;

  bool _isGenMatched;




  for(unsigned int i=0;i<tree_new.size();i++){

    tree_new[i]->Branch("nEvent",        &_nEvent,         "nEvent/L");
    tree_new[i]->Branch("ls",            &_ls,             "ls/I");
    tree_new[i]->Branch("run",           &_run,            "run/I");

    tree_new[i]->Branch("n_presel_mu",      &_n_presel_mu,      "n_presel_mu/I");
    tree_new[i]->Branch("n_fakeablesel_mu", &_n_fakeablesel_mu, "n_fakeablesel_mu/I");
    tree_new[i]->Branch("n_mvasel_mu",      &_n_mvasel_mu,      "n_mvasel_mu/I");

    tree_new[i]->Branch("n_presel_ele",      &_n_presel_ele,      "n_presel_ele/I");
    tree_new[i]->Branch("n_fakeablesel_ele", &_n_fakeablesel_ele, "n_fakeablesel_ele/I");
    tree_new[i]->Branch("n_mvasel_ele",      &_n_mvasel_ele,      "n_mvasel_ele/I");

    tree_new[i]->Branch("n_presel_tau",  &_n_presel_tau,   "n_presel_tau/I");
    tree_new[i]->Branch("n_presel_jet",  &_n_presel_jet,   "n_presel_jet/I");
	   
    tree_new[i]->Branch("mu0_pt",        &_mu0_pt,         "mu0_pt/F");
    tree_new[i]->Branch("mu0_conept",    &_mu0_conept,     "mu0_conept/F");
    tree_new[i]->Branch("mu0_eta",       &_mu0_eta,        "mu0_eta/F");
    tree_new[i]->Branch("mu0_phi",       &_mu0_phi,        "mu0_phi/F");
    tree_new[i]->Branch("mu0_E",         &_mu0_E,          "mu0_E/F");
    tree_new[i]->Branch("mu0_charge",    &_mu0_charge,     "mu0_charge/I");
    tree_new[i]->Branch("mu0_jetNDauChargedMVASel",&_mu0_jetNDauChargedMVASel,"mu0_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("mu0_miniRelIso",          &_mu0_miniRelIso,          "mu0_miniRelIso/F");
    tree_new[i]->Branch("mu0_miniIsoCharged",      &_mu0_miniIsoCharged,      "mu0_miniIsoCharged/F");
    tree_new[i]->Branch("mu0_miniIsoNeutral",      &_mu0_miniIsoNeutral,      "mu0_miniIsoNeutral/F");
    tree_new[i]->Branch("mu0_jetPtRel",  &_mu0_jetPtRel,   "mu0_jetPtRel/F");
    tree_new[i]->Branch("mu0_jetPtRatio",&_mu0_jetPtRatio, "mu0_jetPtRatio/F");
    tree_new[i]->Branch("mu0_jetCSV",    &_mu0_jetCSV,     "mu0_jetCSV/F");
    tree_new[i]->Branch("mu0_sip3D",     &_mu0_sip3D,      "mu0_sip3D/F");
    tree_new[i]->Branch("mu0_dxy",       &_mu0_dxy,        "mu0_dxy/F");
    tree_new[i]->Branch("mu0_dz",        &_mu0_dz,         "mu0_dz/F");
    tree_new[i]->Branch("mu0_segmentCompatibility",&_mu0_segmentCompatibility,"mu0_segmentCompatibility/F");
    tree_new[i]->Branch("mu0_leptonMVA",     &_mu0_leptonMVA,     "mu0_leptonMVA/F");
    tree_new[i]->Branch("mu0_mediumID",      &_mu0_mediumID,      "mu0_mediumID/O");
    tree_new[i]->Branch("mu0_dpt_div_pt",    &_mu0_dpt_div_pt,    "mu0_dpt_div_pt/F");
    tree_new[i]->Branch("mu0_isfakeablesel", &_mu0_isfakeablesel, "mu0_isfakeablesel/O");
    tree_new[i]->Branch("mu0_ismvasel",      &_mu0_ismvasel,      "mu0_ismvasel/O");

    tree_new[i]->Branch("mu1_pt",        &_mu1_pt,         "mu1_pt/F");
    tree_new[i]->Branch("mu1_conept",    &_mu1_conept,     "mu1_conept/F");
    tree_new[i]->Branch("mu1_eta",       &_mu1_eta,        "mu1_eta/F");
    tree_new[i]->Branch("mu1_phi",       &_mu1_phi,        "mu1_phi/F");
    tree_new[i]->Branch("mu1_E",         &_mu1_E,          "mu1_E/F");
    tree_new[i]->Branch("mu1_charge",    &_mu1_charge,     "mu1_charge/I");
    tree_new[i]->Branch("mu1_jetNDauChargedMVASel",&_mu1_jetNDauChargedMVASel,"mu1_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("mu1_miniRelIso",          &_mu1_miniRelIso,          "mu1_miniRelIso/F");
    tree_new[i]->Branch("mu1_miniIsoCharged",      &_mu1_miniIsoCharged,      "mu1_miniIsoCharged/F");
    tree_new[i]->Branch("mu1_miniIsoNeutral",      &_mu1_miniIsoNeutral,      "mu1_miniIsoNeutral/F");
    tree_new[i]->Branch("mu1_jetPtRel",  &_mu1_jetPtRel,   "mu1_jetPtRel/F");
    tree_new[i]->Branch("mu1_jetPtRatio",&_mu1_jetPtRatio, "mu1_jetPtRatio/F");
    tree_new[i]->Branch("mu1_jetCSV",    &_mu1_jetCSV,     "mu1_jetCSV/F");
    tree_new[i]->Branch("mu1_sip3D",     &_mu1_sip3D,      "mu1_sip3D/F");
    tree_new[i]->Branch("mu1_dxy",       &_mu1_dxy,        "mu1_dxy/F");
    tree_new[i]->Branch("mu1_dz",        &_mu1_dz,         "mu1_dz/F");
    tree_new[i]->Branch("mu1_segmentCompatibility",&_mu1_segmentCompatibility,"mu1_segmentCompatibility/F");
    tree_new[i]->Branch("mu1_leptonMVA",&_mu1_leptonMVA,"mu1_leptonMVA/F");
    tree_new[i]->Branch("mu1_mediumID",      &_mu1_mediumID,      "mu1_mediumID/O");
    tree_new[i]->Branch("mu1_dpt_div_pt",    &_mu1_dpt_div_pt,    "mu1_dpt_div_pt/F");
    tree_new[i]->Branch("mu1_isfakeablesel", &_mu1_isfakeablesel, "mu1_isfakeablesel/O");
    tree_new[i]->Branch("mu1_ismvasel",      &_mu1_ismvasel,      "mu1_ismvasel/O");

    tree_new[i]->Branch("ele0_pt",        &_ele0_pt,         "ele0_pt/F");
    tree_new[i]->Branch("ele0_conept",    &_ele0_conept,     "ele0_conept/F");
    tree_new[i]->Branch("ele0_eta",       &_ele0_eta,        "ele0_eta/F");
    tree_new[i]->Branch("ele0_phi",       &_ele0_phi,        "ele0_phi/F");
    tree_new[i]->Branch("ele0_E",         &_ele0_E,          "ele0_E/F");
    tree_new[i]->Branch("ele0_charge",    &_ele0_charge,     "ele0_charge/I");
    tree_new[i]->Branch("ele0_jetNDauChargedMVASel",&_ele0_jetNDauChargedMVASel,"ele0_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("ele0_miniRelIso",          &_ele0_miniRelIso,          "ele0_miniRelIso/F");
    tree_new[i]->Branch("ele0_miniIsoCharged",      &_ele0_miniIsoCharged,      "ele0_miniIsoCharged/F");
    tree_new[i]->Branch("ele0_miniIsoNeutral",      &_ele0_miniIsoNeutral,      "ele0_miniIsoNeutral/F");
    tree_new[i]->Branch("ele0_jetPtRel",  &_ele0_jetPtRel,   "ele0_jetPtRel/F");
    tree_new[i]->Branch("ele0_jetPtRatio",&_ele0_jetPtRatio, "ele0_jetPtRatio/F");
    tree_new[i]->Branch("ele0_jetCSV",    &_ele0_jetCSV,     "ele0_jetCSV/F");
    tree_new[i]->Branch("ele0_sip3D",     &_ele0_sip3D,      "ele0_sip3D/F");
    tree_new[i]->Branch("ele0_dxy",       &_ele0_dxy,        "ele0_dxy/F");
    tree_new[i]->Branch("ele0_dz",        &_ele0_dz,         "ele0_dz/F");
    tree_new[i]->Branch("ele0_ntMVAeleID",&_ele0_ntMVAeleID, "ele0_ntMVAeleID/F");
    tree_new[i]->Branch("ele0_leptonMVA", &_ele0_leptonMVA,  "ele0_leptonMVA/F");
    tree_new[i]->Branch("ele0_isChargeConsistent",   &_ele0_isChargeConsistent,    "ele0_isChargeConsistent/O");
    tree_new[i]->Branch("ele0_passesConversionVeto", &_ele0_passesConversionVeto,  "ele0_passesConversionVeto/O");
    tree_new[i]->Branch("ele0_nMissingHits",  &_ele0_nMissingHits,  "ele0_nMissingHits/I");
    tree_new[i]->Branch("ele0_isfakeablesel", &_ele0_isfakeablesel, "ele0_isfakeablesel/O");
    tree_new[i]->Branch("ele0_ismvasel",      &_ele0_ismvasel,      "ele0_ismvasel/O");

    tree_new[i]->Branch("ele1_pt",        &_ele1_pt,         "ele1_pt/F");
    tree_new[i]->Branch("ele1_conept",    &_ele1_conept,     "ele1_conept/F");
    tree_new[i]->Branch("ele1_eta",       &_ele1_eta,        "ele1_eta/F");
    tree_new[i]->Branch("ele1_phi",       &_ele1_phi,        "ele1_phi/F");
    tree_new[i]->Branch("ele1_E",         &_ele1_E,          "ele1_E/F");
    tree_new[i]->Branch("ele1_charge",    &_ele1_charge,     "ele1_charge/I");
    tree_new[i]->Branch("ele1_jetNDauChargedMVASel",&_ele1_jetNDauChargedMVASel,"ele1_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("ele1_miniRelIso",          &_ele1_miniRelIso,          "ele1_miniRelIso/F");
    tree_new[i]->Branch("ele1_miniIsoCharged",      &_ele1_miniIsoCharged,      "ele1_miniIsoCharged/F");
    tree_new[i]->Branch("ele1_miniIsoNeutral",      &_ele1_miniIsoNeutral,      "ele1_miniIsoNeutral/F");
    tree_new[i]->Branch("ele1_jetPtRel",  &_ele1_jetPtRel,   "ele1_jetPtRel/F");
    tree_new[i]->Branch("ele1_jetPtRatio",&_ele1_jetPtRatio, "ele1_jetPtRatio/F");
    tree_new[i]->Branch("ele1_jetCSV",    &_ele1_jetCSV,     "ele1_jetCSV/F");
    tree_new[i]->Branch("ele1_sip3D",     &_ele1_sip3D,      "ele1_sip3D/F");
    tree_new[i]->Branch("ele1_dxy",       &_ele1_dxy,        "ele1_dxy/F");
    tree_new[i]->Branch("ele1_dz",        &_ele1_dz,         "ele1_dz/F");
    tree_new[i]->Branch("ele1_ntMVAeleID",&_ele1_ntMVAeleID, "ele1_ntMVAeleID/F");
    tree_new[i]->Branch("ele1_leptonMVA", &_ele1_leptonMVA,  "ele1_leptonMVA/F");
    tree_new[i]->Branch("ele1_isChargeConsistent",   &_ele1_isChargeConsistent,    "ele1_isChargeConsistent/O");
    tree_new[i]->Branch("ele1_passesConversionVeto", &_ele1_passesConversionVeto,  "ele1_passesConversionVeto/O");
    tree_new[i]->Branch("ele1_nMissingHits",  &_ele1_nMissingHits,  "ele1_nMissingHits/I");
    tree_new[i]->Branch("ele1_isfakeablesel", &_ele1_isfakeablesel, "ele1_isfakeablesel/O");
    tree_new[i]->Branch("ele1_ismvasel",      &_ele1_ismvasel,      "ele1_ismvasel/O");

    tree_new[i]->Branch("tau0_pt",        &_tau0_pt,         "tau0_pt/F");
    tree_new[i]->Branch("tau0_eta",       &_tau0_eta,        "tau0_eta/F");
    tree_new[i]->Branch("tau0_phi",       &_tau0_phi,        "tau0_phi/F");
    tree_new[i]->Branch("tau0_E",         &_tau0_E,          "tau0_E/F");
    tree_new[i]->Branch("tau0_charge",    &_tau0_charge,     "tau0_charge/I");
    tree_new[i]->Branch("tau0_dxy",       &_tau0_dxy,        "tau0_dxy/F");
    tree_new[i]->Branch("tau0_dz",        &_tau0_dz,         "tau0_dz/F");
    tree_new[i]->Branch("tau0_decayModeFindingOldDMs",                       &_tau0_decayModeFindingOldDMs,                       "tau0_decayModeFindingOldDMs/I");
    tree_new[i]->Branch("tau0_decayModeFindingNewDMs",                       &_tau0_decayModeFindingNewDMs,                       "tau0_decayModeFindingNewDMs/I");
    tree_new[i]->Branch("tau0_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau0_byCombinedIsolationDeltaBetaCorr3Hits,        "tau0_byCombinedIsolationDeltaBetaCorr3Hits/F");
    tree_new[i]->Branch("tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau0_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau0_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau0_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_againstMuonLoose3",         &_tau0_againstMuonLoose3,         "tau0_againstMuonLoose3/I");                         
    tree_new[i]->Branch("tau0_againstMuonTight3",         &_tau0_againstMuonTight3,         "tau0_againstMuonTight3/I");                         
    tree_new[i]->Branch("tau0_againstElectronVLooseMVA6", &_tau0_againstElectronVLooseMVA6, "tau0_againstElectronVLooseMVA6/I");                         
    tree_new[i]->Branch("tau0_againstElectronLooseMVA6",  &_tau0_againstElectronLooseMVA6,  "tau0_againstElectronLooseMVA6/I");                         
    tree_new[i]->Branch("tau0_againstElectronMediumMVA6", &_tau0_againstElectronMediumMVA6, "tau0_againstElectronMediumMVA6/I");                         
    tree_new[i]->Branch("tau0_againstElectronTightMVA6",  &_tau0_againstElectronTightMVA6,  "tau0_againstElectronTightMVA6/I");   
    tree_new[i]->Branch("tau0_againstElectronVTightMVA6", &_tau0_againstElectronVTightMVA6, "tau0_againstElectronVTightMVA6/I");   

    tree_new[i]->Branch("tau1_pt",        &_tau1_pt,         "tau1_pt/F");
    tree_new[i]->Branch("tau1_eta",       &_tau1_eta,        "tau1_eta/F");
    tree_new[i]->Branch("tau1_phi",       &_tau1_phi,        "tau1_phi/F");
    tree_new[i]->Branch("tau1_E",         &_tau1_E,          "tau1_E/F");
    tree_new[i]->Branch("tau1_charge",    &_tau1_charge,     "tau1_charge/I");
    tree_new[i]->Branch("tau1_dxy",       &_tau1_dxy,        "tau1_dxy/F");
    tree_new[i]->Branch("tau1_dz",        &_tau1_dz,         "tau1_dz/F");
    tree_new[i]->Branch("tau1_decayModeFindingOldDMs",                       &_tau1_decayModeFindingOldDMs,                       "tau1_decayModeFindingOldDMs/I");
    tree_new[i]->Branch("tau1_decayModeFindingNewDMs",                       &_tau1_decayModeFindingNewDMs,                       "tau1_decayModeFindingNewDMs/I");
    tree_new[i]->Branch("tau1_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau1_byCombinedIsolationDeltaBetaCorr3Hits,        "tau1_byCombinedIsolationDeltaBetaCorr3Hits/F");
    tree_new[i]->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_againstMuonLoose3",         &_tau1_againstMuonLoose3,         "tau1_againstMuonLoose3/I");                         
    tree_new[i]->Branch("tau1_againstMuonTight3",         &_tau1_againstMuonTight3,         "tau1_againstMuonTight3/I");                         
    tree_new[i]->Branch("tau1_againstElectronVLooseMVA6", &_tau1_againstElectronVLooseMVA6, "tau1_againstElectronVLooseMVA6/I");                         
    tree_new[i]->Branch("tau1_againstElectronLooseMVA6",  &_tau1_againstElectronLooseMVA6,  "tau1_againstElectronLooseMVA6/I");                         
    tree_new[i]->Branch("tau1_againstElectronMediumMVA6", &_tau1_againstElectronMediumMVA6, "tau1_againstElectronMediumMVA6/I");                         
    tree_new[i]->Branch("tau1_againstElectronTightMVA6",  &_tau1_againstElectronTightMVA6,  "tau1_againstElectronTightMVA6/I");   
    tree_new[i]->Branch("tau1_againstElectronVTightMVA6", &_tau1_againstElectronVTightMVA6,  "tau1_againstElectronVTightMVA6/I");   

    tree_new[i]->Branch("jet0_pt",  &_jet0_pt,  "jet0_pt/F");
    tree_new[i]->Branch("jet0_eta", &_jet0_eta, "jet0_eta/F");
    tree_new[i]->Branch("jet0_phi", &_jet0_phi, "jet0_phi/F");
    tree_new[i]->Branch("jet0_E",   &_jet0_E,   "jet0_E/F");
    tree_new[i]->Branch("jet0_CSV", &_jet0_CSV, "jet0_CSV/F");

    tree_new[i]->Branch("jet1_pt",  &_jet1_pt,  "jet1_pt/F");
    tree_new[i]->Branch("jet1_eta", &_jet1_eta, "jet1_eta/F");
    tree_new[i]->Branch("jet1_phi", &_jet1_phi, "jet1_phi/F");
    tree_new[i]->Branch("jet1_E",   &_jet1_E,   "jet1_E/F");
    tree_new[i]->Branch("jet1_CSV", &_jet1_CSV, "jet1_CSV/F");

    tree_new[i]->Branch("jet2_pt",  &_jet2_pt,  "jet2_pt/F");
    tree_new[i]->Branch("jet2_eta", &_jet2_eta, "jet2_eta/F");
    tree_new[i]->Branch("jet2_phi", &_jet2_phi, "jet2_phi/F");
    tree_new[i]->Branch("jet2_E",   &_jet2_E,   "jet2_E/F");
    tree_new[i]->Branch("jet2_CSV", &_jet2_CSV, "jet2_CSV/F");

    tree_new[i]->Branch("jet3_pt",  &_jet3_pt,  "jet3_pt/F");
    tree_new[i]->Branch("jet3_eta", &_jet3_eta, "jet3_eta/F");
    tree_new[i]->Branch("jet3_phi", &_jet3_phi, "jet3_phi/F");
    tree_new[i]->Branch("jet3_E",   &_jet3_E,   "jet3_E/F");
    tree_new[i]->Branch("jet3_CSV", &_jet3_CSV, "jet3_CSV/F");

    tree_new[i]->Branch("PFMET",    &_PFMET,    "PFMET/F");
    tree_new[i]->Branch("PFMETphi", &_PFMETphi, "PFMETphi/F");
    tree_new[i]->Branch("MHT",      &_MHT,       "MHT/F");
    tree_new[i]->Branch("metLD",    &_metLD,     "metLD/F");
	  
    tree_new[i]->Branch("lep0_conept",    &_lep0_conept,     "lep0_conept/F");
    tree_new[i]->Branch("lep1_conept",    &_lep1_conept,     "lep1_conept/F");
    tree_new[i]->Branch("mindr_lep0_jet", &_mindr_lep0_jet,  "mindr_lep0_jet/F");
    tree_new[i]->Branch("mindr_lep1_jet", &_mindr_lep1_jet,  "mindr_lep1_jet/F");
    tree_new[i]->Branch("mindr_lep2_jet",  &_mindr_lep2_jet,  "mindr_lep2_jet/F");
    tree_new[i]->Branch("mindr_tau_jet",   &_mindr_tau_jet,   "mindr_tau_jet/F");
    tree_new[i]->Branch("MT_met_lep0",    &_MT_met_lep0,     "MT_met_lep0/F");
    tree_new[i]->Branch("avg_dr_jet",     &_avg_dr_jet,      "avg_dr_jet/F");
    tree_new[i]->Branch("MVA_2lss_ttV",   &_MVA_2lss_ttV,    "MVA_2lss_ttV/F");
    tree_new[i]->Branch("MVA_2lss_ttbar", &_MVA_2lss_ttbar,  "MVA_2lss_ttbar/F");
    tree_new[i]->Branch("tt_deltaR",      &_tt_deltaR,       "tt_deltaR/F");
    tree_new[i]->Branch("ntags",          &_ntags,           "ntags/I");
    tree_new[i]->Branch("ntags_loose",    &_ntags_loose,     "ntags_loose/I");
    tree_new[i]->Branch("tt_mvis",        &_tt_mvis,         "tt_mvis/F");
    tree_new[i]->Branch("tt_pt",          &_tt_pt,           "tt_pt/F");
    tree_new[i]->Branch("max_dr_jet",     &_max_dr_jet,      "max_dr_jet/F");
    tree_new[i]->Branch("HT",             &_HT,              "HT/F");
    tree_new[i]->Branch("MVA_1l2tau_ttbar",        &_MVA_1l2tau_ttbar,         "MVA_1l2tau_ttbar/F");
    tree_new[i]->Branch("MVA_1l2tau_ttbar_v2",     &_MVA_1l2tau_ttbar_v2,         "MVA_1l2tau_ttbar_v2/F");
    tree_new[i]->Branch("MVA_1l2tau_ttZ_v2",     &_MVA_1l2tau_ttZ_v2,         "MVA_1l2tau_ttZ_v2/F");
    tree_new[i]->Branch("MVA_1l2tau_2Dbin_v2",     &_MVA_1l2tau_2Dbin_v2,         "MVA_1l2tau_2Dbin_v2/I");

    tree_new[i]->Branch("mvis_l1tau",   &_mvis_l1tau,    "mvis_l1tau/F");
    tree_new[i]->Branch("dR_l0tau",     &_dR_l0tau,      "dR_l0tau/F");
    tree_new[i]->Branch("dR_l1tau",        &_dR_l1tau,        "dR_l1tau/F");
    tree_new[i]->Branch("dR_l2tau",        &_dR_l2tau,        "dR_l2tau/F");
    tree_new[i]->Branch("MT_met_lep2",    &_MT_met_lep2,     "MT_met_lep2/F");

    tree_new[i]->Branch("MVA_3l1tau_ttbar",  &_MVA_3l1tau_ttbar,      "MVA_3l1tau_ttbar/F");
    tree_new[i]->Branch("MVA_3l1tau_ttV",    &_MVA_3l1tau_ttV,        "MVA_3l1tau_ttV/F");
    tree_new[i]->Branch("MVA_3l1tau_2Dbin",  &_MVA_3l1tau_2Dbin,      "MVA_3l1tau_2Dbin/I");

    tree_new[i]->Branch("FR_weight", &_FR_weight,  "FR_weight/F");
    tree_new[i]->Branch("triggerSF_weight", &_triggerSF_weight,  "triggerSF_weight/F");
    tree_new[i]->Branch("leptonSF_weight", &_leptonSF_weight,  "leptonSF_weight/F");
    tree_new[i]->Branch("tauSF_weight", &_tauSF_weight,  "tauSF_weight/F");
    tree_new[i]->Branch("bTagSF_weight", &_bTagSF_CSVshape_weight,  "bTagSF_weight/F");
    tree_new[i]->Branch("PU_weight", &_PU_weight,  "PU_weight/F");
    tree_new[i]->Branch("MC_weight", &_MC_weight,  "MC_weight/F");

    tree_new[i]->Branch("isGenMatched", &_isGenMatched, "isGenMatched/O");

  }


  //Old branches used
  vector<float> *_recomu_pt;
  vector<float> *_recomu_conept;
  vector<float> *_recomu_eta;
  vector<float> *_recomu_phi;
  vector<float> *_recomu_e;
  vector<int>   *_recomu_charge;
  vector<int>   *_recomu_jetNDauChargedMVASel;
  vector<float> *_recomu_miniRelIso;
  vector<float> *_recomu_miniIsoCharged;
  vector<float> *_recomu_miniIsoNeutral;
  vector<float> *_recomu_jetPtRel;
  vector<float> *_recomu_jetPtRatio;
  vector<float> *_recomu_jetCSV;
  vector<float> *_recomu_sip3D;
  vector<float> *_recomu_dxy;
  vector<float> *_recomu_dz;
  vector<float> *_recomu_lepMVA_mvaId;
  vector<float> *_recomu_leptonMVA;
  vector<bool>  *_recomu_mediumID;
  vector<float> *_recomu_rel_error_trackpt;
  vector<bool>  *_recomu_isfakeable;
  vector<bool>  *_recomu_ismvasel;

  vector<float> *_recoele_pt;
  vector<float> *_recoele_conept;
  vector<float> *_recoele_eta;
  vector<float> *_recoele_phi;
  vector<float> *_recoele_e;
  vector<int>   *_recoele_charge;
  vector<int>   *_recoele_jetNDauChargedMVASel;
  vector<float> *_recoele_miniRelIso;
  vector<float> *_recoele_miniIsoCharged;
  vector<float> *_recoele_miniIsoNeutral;
  vector<float> *_recoele_jetPtRel;
  vector<float> *_recoele_jetPtRatio;
  vector<float> *_recoele_jetCSV;
  vector<float> *_recoele_sip3D;
  vector<float> *_recoele_dxy;
  vector<float> *_recoele_dz;
  vector<float> *_recoele_lepMVA_mvaId;
  vector<float> *_recoele_leptonMVA;
  vector<bool>  *_recoele_isChargeConsistent;
  vector<bool>  *_recoele_passConversionVeto;
  vector<int>   *_recoele_nMissingHits;
  vector<bool>  *_recoele_isfakeable;
  vector<bool>  *_recoele_ismvasel;

  vector<float> *_recotauh_pt;
  vector<float> *_recotauh_eta;
  vector<float> *_recotauh_phi;
  vector<float> *_recotauh_e;
  vector<int>   *_recotauh_charge;
  vector<float> *_recotauh_dxy;
  vector<float> *_recotauh_dz;
  vector<float> *_recotauh_iso;
  vector<int>  *_recotauh_decayModeFindingOldDMs;
  vector<int>  *_recotauh_decayModeFindingNewDMs;
  vector<int>  *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_againstMuonLoose3;
  vector<int>  *_recotauh_againstMuonTight3;
  vector<int>  *_recotauh_againstElectronVLooseMVA6;
  vector<int>  *_recotauh_againstElectronLooseMVA6;
  vector<int>  *_recotauh_againstElectronMediumMVA6;
  vector<int>  *_recotauh_againstElectronTightMVA6;
  vector<int>  *_recotauh_againstElectronVTightMVA6;
  vector<bool> *_recotauh_sel_isGenMatched;
  vector<int> *_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;


  vector<float> *_recoPFJet_pt;
  vector<float> *_recoPFJet_eta;
  vector<float> *_recoPFJet_phi;
  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_CSVscore;

  vector<int> *_recolep_sel_pdg;
  vector<int> *_recolep_sel_charge;
  vector<int> *_recotauh_sel_charge;
  vector<float> *_recotauh_sel_pt;
  vector<float> *_recolep_sel_eta;

  int _category;
  bool _low_mass_lep;

  for(unsigned int i=0;i<tree.size();i++){

    tree[i]->SetBranchAddress("EventNumber",&_nEvent);
    tree[i]->SetBranchAddress("lumi",&_ls);
    tree[i]->SetBranchAddress("RunNumber",&_run);

    tree[i]->SetBranchAddress("n_recomu_presel",&_n_presel_mu);
    tree[i]->SetBranchAddress("n_recomu_fakeable",&_n_fakeablesel_mu);
    tree[i]->SetBranchAddress("n_recomu_mvasel",&_n_mvasel_mu);

    tree[i]->SetBranchAddress("n_recoele_presel",&_n_presel_ele);
    tree[i]->SetBranchAddress("n_recoele_fakeable",&_n_fakeablesel_ele);
    tree[i]->SetBranchAddress("n_recoele_mvasel",&_n_mvasel_ele);

    tree[i]->SetBranchAddress("n_recotauh",&_n_presel_tau);
    tree[i]->SetBranchAddress("n_recoPFJet",&_n_presel_jet);

    tree[i]->SetBranchAddress("recomu_pt",                   &_recomu_pt);
    tree[i]->SetBranchAddress("recomu_conept",               &_recomu_conept);
    tree[i]->SetBranchAddress("recomu_eta",                  &_recomu_eta);
    tree[i]->SetBranchAddress("recomu_phi",                  &_recomu_phi);
    tree[i]->SetBranchAddress("recomu_e",                    &_recomu_e);
    tree[i]->SetBranchAddress("recomu_charge",               &_recomu_charge);
    tree[i]->SetBranchAddress("recomu_jetNDauChargedMVASel", &_recomu_jetNDauChargedMVASel);
    tree[i]->SetBranchAddress("recomu_miniRelIso",           &_recomu_miniRelIso);
    tree[i]->SetBranchAddress("recomu_miniIsoCharged",       &_recomu_miniIsoCharged);
    tree[i]->SetBranchAddress("recomu_miniIsoNeutral",       &_recomu_miniIsoNeutral);
    tree[i]->SetBranchAddress("recomu_jetPtRel",             &_recomu_jetPtRel);
    tree[i]->SetBranchAddress("recomu_jetPtRatio",           &_recomu_jetPtRatio);
    tree[i]->SetBranchAddress("recomu_jetCSV",               &_recomu_jetCSV);
    tree[i]->SetBranchAddress("recomu_sip3D",                &_recomu_sip3D);
    tree[i]->SetBranchAddress("recomu_dxy",                  &_recomu_dxy);
    tree[i]->SetBranchAddress("recomu_dz",                   &_recomu_dz);
    tree[i]->SetBranchAddress("recomu_lepMVA_mvaId",         &_recomu_lepMVA_mvaId);
    tree[i]->SetBranchAddress("recomu_leptonMVA",            &_recomu_leptonMVA);
    tree[i]->SetBranchAddress("recomu_mediumID",             &_recomu_mediumID);
    tree[i]->SetBranchAddress("recomu_rel_error_trackpt",    &_recomu_rel_error_trackpt);
    tree[i]->SetBranchAddress("recomu_isfakeable",           &_recomu_isfakeable);
    tree[i]->SetBranchAddress("recomu_ismvasel",             &_recomu_ismvasel);

    tree[i]->SetBranchAddress("recoele_pt",                  &_recoele_pt);
    tree[i]->SetBranchAddress("recoele_conept",              &_recoele_conept);
    tree[i]->SetBranchAddress("recoele_eta",                 &_recoele_eta);
    tree[i]->SetBranchAddress("recoele_phi",                 &_recoele_phi);
    tree[i]->SetBranchAddress("recoele_e",                   &_recoele_e);
    tree[i]->SetBranchAddress("recoele_charge",              &_recoele_charge);
    tree[i]->SetBranchAddress("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
    tree[i]->SetBranchAddress("recoele_miniRelIso",          &_recoele_miniRelIso);
    tree[i]->SetBranchAddress("recoele_miniIsoCharged",      &_recoele_miniIsoCharged);
    tree[i]->SetBranchAddress("recoele_miniIsoNeutral",      &_recoele_miniIsoNeutral);
    tree[i]->SetBranchAddress("recoele_jetPtRel",            &_recoele_jetPtRel);
    tree[i]->SetBranchAddress("recoele_jetPtRatio",          &_recoele_jetPtRatio);
    tree[i]->SetBranchAddress("recoele_jetCSV",              &_recoele_jetCSV);
    tree[i]->SetBranchAddress("recoele_sip3D",               &_recoele_sip3D);
    tree[i]->SetBranchAddress("recoele_dxy",                 &_recoele_dxy);
    tree[i]->SetBranchAddress("recoele_dz",                  &_recoele_dz);
    tree[i]->SetBranchAddress("recoele_lepMVA_mvaId",        &_recoele_lepMVA_mvaId);
    tree[i]->SetBranchAddress("recoele_leptonMVA",           &_recoele_leptonMVA);
    tree[i]->SetBranchAddress("recoele_isChargeConsistent",  &_recoele_isChargeConsistent);
    tree[i]->SetBranchAddress("recoele_passConversionVeto",  &_recoele_passConversionVeto);
    tree[i]->SetBranchAddress("recoele_nMissingHits",        &_recoele_nMissingHits);
    tree[i]->SetBranchAddress("recoele_isfakeable",          &_recoele_isfakeable);
    tree[i]->SetBranchAddress("recoele_ismvasel",            &_recoele_ismvasel);

    tree[i]->SetBranchAddress("recotauh_pt",                 &_recotauh_pt);
    tree[i]->SetBranchAddress("recotauh_eta",                &_recotauh_eta);
    tree[i]->SetBranchAddress("recotauh_phi",                &_recotauh_phi);
    tree[i]->SetBranchAddress("recotauh_e",                  &_recotauh_e);
    tree[i]->SetBranchAddress("recotauh_charge",             &_recotauh_charge);
    tree[i]->SetBranchAddress("recotauh_dxy",                &_recotauh_dxy);
    tree[i]->SetBranchAddress("recotauh_dz",                 &_recotauh_dz);
    tree[i]->SetBranchAddress("recotauh_iso",                &_recotauh_iso);
    tree[i]->SetBranchAddress("recotauh_decayModeFindingOldDMs", &_recotauh_decayModeFindingOldDMs);
    tree[i]->SetBranchAddress("recotauh_decayModeFindingNewDMs", &_recotauh_decayModeFindingNewDMs);
    tree[i]->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",     &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_againstMuonLoose3",           &_recotauh_againstMuonLoose3);
    tree[i]->SetBranchAddress("recotauh_againstMuonTight3",           &_recotauh_againstMuonTight3);
    tree[i]->SetBranchAddress("recotauh_againstElectronVLooseMVA6",   &_recotauh_againstElectronVLooseMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronLooseMVA6",    &_recotauh_againstElectronLooseMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronMediumMVA6",   &_recotauh_againstElectronMediumMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronTightMVA6",    &_recotauh_againstElectronTightMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronVTightMVA6",   &_recotauh_againstElectronVTightMVA6);
    tree[i]->SetBranchAddress("recotauh_sel_isGenMatched",   &_recotauh_sel_isGenMatched);
    tree[i]->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",   &_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    
    tree[i]->SetBranchAddress("recoPFJet_pt",       &_recoPFJet_pt);
    tree[i]->SetBranchAddress("recoPFJet_eta",      &_recoPFJet_eta);
    tree[i]->SetBranchAddress("recoPFJet_phi",      &_recoPFJet_phi);
    tree[i]->SetBranchAddress("recoPFJet_e",        &_recoPFJet_e);
    tree[i]->SetBranchAddress("recoPFJet_CSVscore", &_recoPFJet_CSVscore);

    tree[i]->SetBranchAddress("PFMET",&_PFMET);
    tree[i]->SetBranchAddress("PFMET_phi",&_PFMETphi);
    tree[i]->SetBranchAddress("HTmiss",&_MHT);
    tree[i]->SetBranchAddress("ETmissLD",&_metLD);

    tree[i]->SetBranchAddress("lep0_conept",&_lep0_conept);
    tree[i]->SetBranchAddress("lep1_conept",&_lep1_conept);
    tree[i]->SetBranchAddress("mindR_lep0_recoPFjet",&_mindr_lep0_jet);
    tree[i]->SetBranchAddress("mindR_lep1_recoPFjet",&_mindr_lep1_jet);
    tree[i]->SetBranchAddress("mindR_lep3_jet",&_mindr_lep2_jet);
    tree[i]->SetBranchAddress("mindR_tau_jet",&_mindr_tau_jet);
    tree[i]->SetBranchAddress("MT_lep0",&_MT_met_lep0);
    tree[i]->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
    tree[i]->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lss_ttV);
    tree[i]->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lss_ttbar);

    tree[i]->SetBranchAddress("deltaR_tautau",&_tt_deltaR);
    tree[i]->SetBranchAddress("n_recoPFJet_btag_medium",&_ntags);
    tree[i]->SetBranchAddress("n_recoPFJet_btag_loose",&_ntags_loose);
    tree[i]->SetBranchAddress("mvis_tautau",&_tt_mvis);
    tree[i]->SetBranchAddress("sumpT_tautau",&_tt_pt);
    tree[i]->SetBranchAddress("deltaRmax_jet",&_max_dr_jet);
    tree[i]->SetBranchAddress("HT",&_HT);
    tree[i]->SetBranchAddress("MVA_1l2tau_ttbar",&_MVA_1l2tau_ttbar);
    tree[i]->SetBranchAddress("MVA_1l2tau_ttbar_v2",&_MVA_1l2tau_ttbar_v2);
    tree[i]->SetBranchAddress("MVA_1l2tau_ttZ_v2",&_MVA_1l2tau_ttZ_v2);
    tree[i]->SetBranchAddress("MVA_1l2tau_2Dbin_v2",&_MVA_1l2tau_2Dbin_v2);  

    tree[i]->SetBranchAddress("mTauTauVis2",&_mvis_l1tau);
    tree[i]->SetBranchAddress("dR_lep1_tau",&_dR_l0tau);
    tree[i]->SetBranchAddress("dR_lep2_tau",&_dR_l1tau);
    tree[i]->SetBranchAddress("dR_lep3_tau",&_dR_l2tau);
    tree[i]->SetBranchAddress("mT_lep3",&_MT_met_lep2);
    tree[i]->SetBranchAddress("MVA_3l1tau_ttbar",&_MVA_3l1tau_ttbar);
    tree[i]->SetBranchAddress("MVA_3l1tau_ttV",&_MVA_3l1tau_ttV);
    tree[i]->SetBranchAddress("MVA_3l1tau_2Dbin",&_MVA_3l1tau_2Dbin);  

    tree[i]->SetBranchAddress("category",&_category);
    tree[i]->SetBranchAddress("isGenMatched",&_isGenMatched);

    tree[i]->SetBranchAddress("event_weight_ttH_v2",&_FR_weight);
    tree[i]->SetBranchAddress("triggerSF_weight_v2",&_triggerSF_weight);
    tree[i]->SetBranchAddress("leptonSF_ttH_weight_v3",&_leptonSF_weight);
    tree[i]->SetBranchAddress("tauSF_weight_v3",&_tauSF_weight);
    tree[i]->SetBranchAddress("bTagSF_CSVshape_weight_v2",&_bTagSF_CSVshape_weight);
    tree[i]->SetBranchAddress("PU_weight_MCSummer2016",&_PU_weight);
    tree[i]->SetBranchAddress("MC_weight",&_MC_weight);

    tree[i]->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree[i]->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);
    tree[i]->SetBranchAddress("recotauh_sel_charge",&_recotauh_sel_charge);
    tree[i]->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
    tree[i]->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);

    tree[i]->SetBranchAddress("low_mass_lep",&_low_mass_lep);


  }

  
  for(unsigned int i_tree=0; i_tree<tree.size(); i_tree++){

  Long64_t nentries = tree[i_tree]->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _nEvent       = -9999;
    _ls           = -9999;
    _run          = -9999;

    _n_presel_mu  = -9999;
    _n_fakeablesel_mu  = -9999;
    _n_mvasel_mu  = -9999;

    _n_presel_ele = -9999;
    _n_fakeablesel_ele  = -9999;
    _n_mvasel_ele  = -9999;

    _n_presel_tau = -9999;
    _n_presel_jet = -9999;

    _mu0_pt       = -9999;
    _mu0_conept   = -9999;
    _mu0_eta      = -9999;
    _mu0_phi      = -9999;
    _mu0_E        = -9999;
    _mu0_charge   = -9999;
    _mu0_jetNDauChargedMVASel = -9999;
    _mu0_miniRelIso           = -9999;
    _mu0_miniIsoCharged       = -9999;
    _mu0_miniIsoNeutral       = -9999;
    _mu0_jetPtRel             = -9999;
    _mu0_jetPtRatio           = -9999;
    _mu0_jetCSV               = -9999;
    _mu0_sip3D                = -9999;
    _mu0_dxy                  = -9999;
    _mu0_dz                   = -9999;
    _mu0_segmentCompatibility = -9999;
    _mu0_leptonMVA            = -9999;
    _mu0_mediumID = 0;
    _mu0_dpt_div_pt = -9999;
    _mu0_isfakeablesel = 0;
    _mu0_ismvasel = 0;

    _mu1_pt       = -9999;
    _mu1_conept   = -9999;
    _mu1_eta      = -9999;
    _mu1_phi      = -9999;
    _mu1_E        = -9999;
    _mu1_charge   = -9999;
    _mu1_jetNDauChargedMVASel = -9999;
    _mu1_miniRelIso           = -9999;
    _mu1_miniIsoCharged       = -9999;
    _mu1_miniIsoNeutral       = -9999;
    _mu1_jetPtRel             = -9999;
    _mu1_jetPtRatio           = -9999;
    _mu1_jetCSV               = -9999;
    _mu1_sip3D                = -9999;
    _mu1_dxy                  = -9999;
    _mu1_dz                   = -9999;
    _mu1_segmentCompatibility = -9999;
    _mu1_leptonMVA            = -9999;
    _mu1_mediumID = 0;
    _mu1_dpt_div_pt = -9999;
    _mu1_isfakeablesel = 0;
    _mu1_ismvasel = 0;

    _ele0_pt       = -9999;
    _ele0_conept   = -9999;
    _ele0_eta      = -9999;
    _ele0_phi      = -9999;
    _ele0_E        = -9999;
    _ele0_charge   = -9999;
    _ele0_jetNDauChargedMVASel = -9999;
    _ele0_miniRelIso           = -9999;
    _ele0_miniIsoCharged       = -9999;
    _ele0_miniIsoNeutral       = -9999;
    _ele0_jetPtRel             = -9999;
    _ele0_jetPtRatio           = -9999;
    _ele0_jetCSV               = -9999;
    _ele0_sip3D                = -9999;
    _ele0_dxy                  = -9999;
    _ele0_dz                   = -9999;
    _ele0_ntMVAeleID           = -9999;
    _ele0_leptonMVA            = -9999;
    _ele0_isChargeConsistent   = 0;
    _ele0_passesConversionVeto = 0;
    _ele0_nMissingHits         = -9999;
    _ele0_isfakeablesel       = 0;
    _ele0_ismvasel            = 0;


    _ele1_pt       = -9999;
    _ele1_conept   = -9999;
    _ele1_eta      = -9999;
    _ele1_phi      = -9999;
    _ele1_E        = -9999;
    _ele1_charge   = -9999;
    _ele1_jetNDauChargedMVASel = -9999;
    _ele1_miniRelIso           = -9999;
    _ele1_miniIsoCharged       = -9999;
    _ele1_miniIsoNeutral       = -9999;
    _ele1_jetPtRel             = -9999;
    _ele1_jetPtRatio           = -9999;
    _ele1_jetCSV               = -9999;
    _ele1_sip3D                = -9999;
    _ele1_dxy                  = -9999;
    _ele1_dz                   = -9999;
    _ele1_ntMVAeleID           = -9999;
    _ele1_leptonMVA            = -9999;
    _ele1_isChargeConsistent   = 0;
    _ele1_passesConversionVeto = 0;
    _ele1_nMissingHits         = -9999;
    _ele1_isfakeablesel       = 0;
    _ele1_ismvasel            = 0;

    _tau0_pt       = -9999;
    _tau0_eta      = -9999;
    _tau0_phi      = -9999;
    _tau0_E        = -9999;
    _tau0_charge   = -9999;    
    _tau0_dxy      = -9999;
    _tau0_dz       = -9999;
    _tau0_decayModeFindingOldDMs                           = -9999;
    _tau0_decayModeFindingNewDMs                           = -9999;
    _tau0_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau0_againstMuonLoose3          = -9999;
    _tau0_againstMuonTight3          = -9999;
    _tau0_againstElectronVLooseMVA6  = -9999;
    _tau0_againstElectronLooseMVA6   = -9999;
    _tau0_againstElectronMediumMVA6  = -9999;
    _tau0_againstElectronTightMVA6   = -9999;
    _tau0_againstElectronVTightMVA6  = -9999;

    _tau1_pt       = -9999;
    _tau1_eta      = -9999;
    _tau1_phi      = -9999;
    _tau1_E        = -9999;
    _tau1_charge   = -9999;    
    _tau1_dxy      = -9999;
    _tau1_dz       = -9999;
    _tau1_decayModeFindingOldDMs                           = -9999;
    _tau1_decayModeFindingNewDMs                           = -9999;
    _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_againstMuonLoose3          = -9999;
    _tau1_againstMuonTight3          = -9999;
    _tau1_againstElectronVLooseMVA6  = -9999;
    _tau1_againstElectronLooseMVA6   = -9999;
    _tau1_againstElectronMediumMVA6  = -9999;
    _tau1_againstElectronTightMVA6   = -9999;
    _tau1_againstElectronVTightMVA6  = -9999;
        
    _jet0_pt   = -9999;
    _jet0_eta  = -9999;
    _jet0_phi  = -9999;
    _jet0_E    = -9999;
    _jet0_CSV  = -9999;

    _jet1_pt   = -9999;
    _jet1_eta  = -9999;
    _jet1_phi  = -9999;
    _jet1_E    = -9999;
    _jet1_CSV  = -9999;

    _jet2_pt   = -9999;
    _jet2_eta  = -9999;
    _jet2_phi  = -9999;
    _jet2_E    = -9999;
    _jet2_CSV  = -9999;
	
    _jet3_pt   = -9999;
    _jet3_eta  = -9999;
    _jet3_phi  = -9999;
    _jet3_E    = -9999;
    _jet3_CSV  = -9999;

    _PFMET     = -9999;
    _PFMETphi  = -9999;    
    _MHT       = -9999;
    _metLD     = -9999;    

    _lep0_conept    = -9999;
    _lep1_conept    = -9999;
    _mindr_lep0_jet = -9999;
    _mindr_lep1_jet = -9999;
    _MT_met_lep0    = -9999;
    _avg_dr_jet     = -9999;
    _MVA_2lss_ttV   = -9999;
    _MVA_2lss_ttbar   = -9999;

    _tt_deltaR = -9999;
    _ntags = -9999;
    _ntags_loose = -9999;
    _tt_mvis = -9999;
    _tt_pt = -9999;
    _max_dr_jet = -9999;
    _HT = -9999;
    _MVA_1l2tau_ttbar = -9999;
    _MVA_1l2tau_ttbar_v2 = -9999;
    _MVA_1l2tau_ttZ_v2 = -9999;
    _MVA_1l2tau_2Dbin_v2 = -9999;

    _mvis_l1tau = -9999;
    _dR_l0tau = -9999;
    
    _mindr_lep2_jet = -9999;
    _mindr_tau_jet = -9999;
    _MT_met_lep2 = -9999;
    _dR_l1tau = -9999;
    _dR_l2tau = -9999;
    _MVA_3l1tau_ttbar = -9999;
    _MVA_3l1tau_ttV = -9999;
    _MVA_3l1tau_2Dbin = -9999;


    ////
    
    _recomu_pt      = 0;
    _recomu_conept  = 0;
    _recomu_eta     = 0;
    _recomu_phi     = 0;
    _recomu_e       = 0;
    _recomu_charge  = 0;
    _recomu_jetNDauChargedMVASel = 0;
    _recomu_miniRelIso           = 0;
    _recomu_miniIsoCharged       = 0;
    _recomu_miniIsoNeutral       = 0;
    _recomu_jetPtRel             = 0;
    _recomu_jetPtRatio           = 0;
    _recomu_jetCSV               = 0;
    _recomu_sip3D                = 0;
    _recomu_dxy                  = 0;
    _recomu_dz                   = 0;
    _recomu_lepMVA_mvaId         = 0;
    _recomu_leptonMVA            = 0;
    _recomu_mediumID             = 0;
    _recomu_rel_error_trackpt    = 0;
    _recomu_isfakeable           = 0;
    _recomu_ismvasel             = 0;

    _recoele_pt      = 0;
    _recoele_conept  = 0;
    _recoele_eta     = 0;
    _recoele_phi     = 0;
    _recoele_e       = 0;
    _recoele_charge  = 0;
    _recoele_jetNDauChargedMVASel = 0;
    _recoele_miniRelIso           = 0;
    _recoele_miniIsoCharged       = 0;
    _recoele_miniIsoNeutral       = 0;
    _recoele_jetPtRel             = 0;
    _recoele_jetPtRatio           = 0;
    _recoele_jetCSV               = 0;
    _recoele_sip3D                = 0;
    _recoele_dxy                  = 0;
    _recoele_dz                   = 0;
    _recoele_lepMVA_mvaId         = 0;
    _recoele_leptonMVA            = 0;    
    _recoele_isChargeConsistent   = 0;
    _recoele_passConversionVeto   = 0;
    _recoele_nMissingHits         = 0;
    _recoele_isfakeable           = 0;
    _recoele_ismvasel             = 0;    

    _recotauh_pt     = 0;
    _recotauh_eta    = 0;
    _recotauh_phi    = 0;
    _recotauh_e      = 0;
    _recotauh_charge = 0;
    _recotauh_dxy    = 0;
    _recotauh_dz     = 0;
    _recotauh_iso    = 0;
    _recotauh_decayModeFindingOldDMs                             = 0;
    _recotauh_decayModeFindingNewDMs                             = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits        = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03    = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_againstMuonLoose3           = 0;
    _recotauh_againstMuonTight3           = 0;
    _recotauh_againstElectronVLooseMVA6   = 0;
    _recotauh_againstElectronLooseMVA6    = 0;
    _recotauh_againstElectronMediumMVA6   = 0;
    _recotauh_againstElectronTightMVA6    = 0;
    _recotauh_againstElectronVTightMVA6   = 0;
    _recotauh_sel_isGenMatched   = 0;
    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;

    _recoPFJet_pt       = 0;
    _recoPFJet_eta      = 0;
    _recoPFJet_phi      = 0;
    _recoPFJet_e        = 0;
    _recoPFJet_CSVscore = 0;

    _recolep_sel_pdg = 0;
    _recolep_sel_charge = 0;
    _recotauh_sel_charge = 0;
    _recotauh_sel_pt = 0;
    _recolep_sel_eta = 0;

    _low_mass_lep = 0;

    _category = 0;
    _isGenMatched = 0;

    _FR_weight = 0;
    _triggerSF_weight = 0;
    _leptonSF_weight = 0;
    _tauSF_weight = 0;
    _bTagSF_CSVshape_weight = 0;
    _PU_weight = 0;
    _MC_weight = 0;
    
    tree[i_tree]->GetEntry(i);

    if(_n_presel_mu>0){

      _mu0_pt     = (*_recomu_pt)[0];
      _mu0_conept = (*_recomu_conept)[0];
      _mu0_eta    = (*_recomu_eta)[0];
      _mu0_phi    = (*_recomu_phi)[0];
      _mu0_E      = (*_recomu_e)[0];
      _mu0_charge = (*_recomu_charge)[0];
      _mu0_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel)[0];
      _mu0_miniRelIso           = (*_recomu_miniRelIso)[0];
      _mu0_miniIsoCharged       = (*_recomu_miniIsoCharged)[0];
      _mu0_miniIsoNeutral       = (*_recomu_miniIsoNeutral)[0];
      _mu0_jetPtRel             = (*_recomu_jetPtRel)[0];
      _mu0_jetPtRatio           = (*_recomu_jetPtRatio)[0];
      _mu0_jetCSV               = (*_recomu_jetCSV)[0];
      _mu0_sip3D                = (*_recomu_sip3D)[0];
      _mu0_dxy                  = (*_recomu_dxy)[0];
      _mu0_dz                   = (*_recomu_dz)[0];
      _mu0_segmentCompatibility = (*_recomu_lepMVA_mvaId)[0];
      _mu0_leptonMVA            = (*_recomu_leptonMVA)[0];
      _mu0_mediumID             = (*_recomu_mediumID)[0];
      _mu0_dpt_div_pt           = (*_recomu_rel_error_trackpt)[0];
      _mu0_isfakeablesel        = (*_recomu_isfakeable)[0];      
      _mu0_ismvasel             = (*_recomu_ismvasel)[0];

    }

    if(_n_presel_mu>1){
      _mu1_pt     = (*_recomu_pt)[1];
      _mu1_conept = (*_recomu_conept)[1];
      _mu1_eta    = (*_recomu_eta)[1];
      _mu1_phi    = (*_recomu_phi)[1];
      _mu1_E      = (*_recomu_e)[1];
      _mu1_charge = (*_recomu_charge)[1];
      _mu1_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel)[1];
      _mu1_miniRelIso           = (*_recomu_miniRelIso)[1];
      _mu1_miniIsoCharged       = (*_recomu_miniIsoCharged)[1];
      _mu1_miniIsoNeutral       = (*_recomu_miniIsoNeutral)[1];
      _mu1_jetPtRel             = (*_recomu_jetPtRel)[1];
      _mu1_jetPtRatio           = (*_recomu_jetPtRatio)[1];
      _mu1_jetCSV               = (*_recomu_jetCSV)[1];
      _mu1_sip3D                = (*_recomu_sip3D)[1];
      _mu1_dxy                  = (*_recomu_dxy)[1];
      _mu1_dz                   = (*_recomu_dz)[1];
      _mu1_segmentCompatibility = (*_recomu_lepMVA_mvaId)[1];
      _mu1_leptonMVA            = (*_recomu_leptonMVA)[1];
      _mu1_mediumID             = (*_recomu_mediumID)[1];
      _mu1_dpt_div_pt           = (*_recomu_rel_error_trackpt)[1];
      _mu1_isfakeablesel        = (*_recomu_isfakeable)[1];      
      _mu1_ismvasel             = (*_recomu_ismvasel)[1];
    }


    if(_n_presel_ele>0){
      _ele0_pt     = (*_recoele_pt)[0];
      _ele0_conept = (*_recoele_conept)[0];
      _ele0_eta    = (*_recoele_eta)[0];
      _ele0_phi    = (*_recoele_phi)[0];
      _ele0_E      = (*_recoele_e)[0];
      _ele0_charge = (*_recoele_charge)[0];
      _ele0_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel)[0];
      _ele0_miniRelIso           = (*_recoele_miniRelIso)[0];
      _ele0_miniIsoCharged       = (*_recoele_miniIsoCharged)[0];
      _ele0_miniIsoNeutral       = (*_recoele_miniIsoNeutral)[0];
      _ele0_jetPtRel             = (*_recoele_jetPtRel)[0];
      _ele0_jetPtRatio           = (*_recoele_jetPtRatio)[0];
      _ele0_jetCSV               = (*_recoele_jetCSV)[0];
      _ele0_sip3D                = (*_recoele_sip3D)[0];
      _ele0_dxy                  = (*_recoele_dxy)[0];
      _ele0_dz                   = (*_recoele_dz)[0];
      _ele0_ntMVAeleID           = (*_recoele_lepMVA_mvaId)[0];
      _ele0_leptonMVA            = (*_recoele_leptonMVA)[0];
      _ele0_isChargeConsistent   = (*_recoele_isChargeConsistent)[0];      
      _ele0_passesConversionVeto = (*_recoele_passConversionVeto)[0];
      _ele0_nMissingHits         = (*_recoele_nMissingHits)[0];
      _ele0_isfakeablesel        = (*_recoele_isfakeable)[0];
      _ele0_ismvasel             = (*_recoele_ismvasel)[0];
    }

    if(_n_presel_ele>1){
      _ele1_pt     = (*_recoele_pt)[1];
      _ele1_conept = (*_recoele_conept)[1];
      _ele1_eta    = (*_recoele_eta)[1];
      _ele1_phi    = (*_recoele_phi)[1];
      _ele1_E      = (*_recoele_e)[1];
      _ele1_charge = (*_recoele_charge)[1];
      _ele1_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel)[1];
      _ele1_miniRelIso           = (*_recoele_miniRelIso)[1];
      _ele1_miniIsoCharged       = (*_recoele_miniIsoCharged)[1];
      _ele1_miniIsoNeutral       = (*_recoele_miniIsoNeutral)[1];
      _ele1_jetPtRel             = (*_recoele_jetPtRel)[1];
      _ele1_jetPtRatio           = (*_recoele_jetPtRatio)[1];
      _ele1_jetCSV               = (*_recoele_jetCSV)[1];
      _ele1_sip3D                = (*_recoele_sip3D)[1];
      _ele1_dxy                  = (*_recoele_dxy)[1];
      _ele1_dz                   = (*_recoele_dz)[1];
      _ele1_ntMVAeleID           = (*_recoele_lepMVA_mvaId)[1];
      _ele1_leptonMVA            = (*_recoele_leptonMVA)[1];
      _ele1_isChargeConsistent   = (*_recoele_isChargeConsistent)[1];      
      _ele1_passesConversionVeto = (*_recoele_passConversionVeto)[1];
      _ele1_nMissingHits         = (*_recoele_nMissingHits)[1];
      _ele1_isfakeablesel        = (*_recoele_isfakeable)[1];
      _ele1_ismvasel             = (*_recoele_ismvasel)[1];
    }


    if(_n_presel_tau>0){
      _tau0_pt     = (*_recotauh_pt)[0];
      _tau0_eta    = (*_recotauh_eta)[0];
      _tau0_phi    = (*_recotauh_phi)[0];
      _tau0_E      = (*_recotauh_e)[0];
      _tau0_charge = (*_recotauh_charge)[0]; 
      _tau0_dxy    = (*_recotauh_dxy)[0]; 
      _tau0_dz     = (*_recotauh_dz)[0]; 
      _tau0_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[0];
      _tau0_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[0];
      _tau0_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[0];
      _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[0];
      _tau0_againstMuonTight3          = (*_recotauh_againstMuonTight3)[0];
      _tau0_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[0];
      _tau0_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[0];
      _tau0_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[0];
      _tau0_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[0];
      _tau0_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[0];

    }

    if(_n_presel_tau>1){
      _tau1_pt     = (*_recotauh_pt)[1];
      _tau1_eta    = (*_recotauh_eta)[1];
      _tau1_phi    = (*_recotauh_phi)[1];
      _tau1_E      = (*_recotauh_e)[1];
      _tau1_charge = (*_recotauh_charge)[1];
      _tau1_dxy    = (*_recotauh_dxy)[1]; 
      _tau1_dz     = (*_recotauh_dz)[1];     
      _tau1_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[1];
      _tau1_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[1];
      _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[1];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[1];
      _tau1_againstMuonTight3          = (*_recotauh_againstMuonTight3)[1];
      _tau1_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[1];
      _tau1_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[1];
      _tau1_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[1];
      _tau1_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[1];
      _tau1_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[1];

    }
    
    if(_n_presel_jet>0){

      _jet0_pt   = (*_recoPFJet_pt)[0];
      _jet0_eta  = (*_recoPFJet_eta)[0];
      _jet0_phi  = (*_recoPFJet_phi)[0];
      _jet0_E    = (*_recoPFJet_e)[0];
      _jet0_CSV  = (*_recoPFJet_CSVscore)[0];

    }

    if(_n_presel_jet>1){

      _jet1_pt   = (*_recoPFJet_pt)[1];
      _jet1_eta  = (*_recoPFJet_eta)[1];
      _jet1_phi  = (*_recoPFJet_phi)[1];
      _jet1_E    = (*_recoPFJet_e)[1];
      _jet1_CSV  = (*_recoPFJet_CSVscore)[1];

    }

    if(_n_presel_jet>2){

      _jet2_pt   = (*_recoPFJet_pt)[2];
      _jet2_eta  = (*_recoPFJet_eta)[2];
      _jet2_phi  = (*_recoPFJet_phi)[2];
      _jet2_E    = (*_recoPFJet_e)[2];
      _jet2_CSV  = (*_recoPFJet_CSVscore)[2];

    }
  
    if(_n_presel_jet>3){

      _jet3_pt   = (*_recoPFJet_pt)[3];
      _jet3_eta  = (*_recoPFJet_eta)[3];
      _jet3_phi  = (*_recoPFJet_phi)[3];
      _jet3_E    = (*_recoPFJet_e)[3];
      _jet3_CSV  = (*_recoPFJet_CSVscore)[3];

    }

    

    bool medium_tau = false;
    if(_n_presel_tau>0)
      medium_tau = (*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0];
    

    if(_category==20 && _isGenMatched && !_low_mass_lep){
      if((*_recotauh_sel_pt)[0]>30 && abs((*_recolep_sel_eta)[0])<2.1)
         tree_new_1l_2tau->Fill();
    }
    else if(_category==50 && !_low_mass_lep){
      if((*_recotauh_sel_pt)[0]>30 && abs((*_recolep_sel_eta)[0])<2.1)
         tree_new_1l_2tau_fake_CR->Fill();
    }
    else if(_category==11){
      if(((*_recolep_sel_charge)[0]+(*_recotauh_sel_charge)[0])==0)
	tree_new_2lSS_tau->Fill();
    }
    else if(_category==41 && medium_tau){
      if(((*_recolep_sel_charge)[0]+(*_recotauh_sel_charge)[0])==0)
	tree_new_2lSS_lepMVA_CR_tau->Fill();
    }
    else if(_category==-11){
      if( (abs((*_recolep_sel_pdg)[0])==11 && (*_recolep_sel_charge)[0]*(*_recotauh_sel_charge)[0]>0) || (abs((*_recolep_sel_pdg)[1])==11 && (*_recolep_sel_charge)[1]*(*_recotauh_sel_charge)[0]>0)   )
	tree_new_2lOS_CR_tau->Fill();
    }
    else if(_category==16){
      if(((*_recolep_sel_charge)[0]+(*_recolep_sel_charge)[1]+(*_recolep_sel_charge)[2]+(*_recotauh_sel_charge)[0])==0)
	tree_new_3l_tau->Fill();
    }
    else if(_category==46 && medium_tau){
      if(((*_recolep_sel_charge)[0]+(*_recolep_sel_charge)[1]+(*_recolep_sel_charge)[2]+(*_recotauh_sel_charge)[0])==0)
	tree_new_3l_lepMVA_CR_tau->Fill();
    }

  }
  
  }
  
  for(unsigned int i=0;i<tree_new.size();i++)
    tree_new[i]->Write();
  f_new->Close();


  return;

}






void create_syncNtuple_eventbased_ttH_tautau_MEM(){

  TString dir_in="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/";
  TString dir_out="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/syncNtuples/";

  TString file="syncNtuple_event_ttH_tautau_MEM.root";    

  vector<TString> list;
  list.push_back(dir_in+"syncNtuple_ttH_tautau_split_2lSS_MEM_170301_btagSF_trig_lepTauSF_new_leptauSF3_BDT.root");
 
  TChain * tree_2lSS = new TChain("T");
  //TChain * tree_2lOS_CR = new TChain("HTauTauTree_2lOS_CR");
  //TChain * tree_2lSS_lepMVA_CR = new TChain("HTauTauTree_2lSS_lepMVA_CR");

  vector<TChain*> tree;
  tree.push_back(tree_2lSS);
  //tree.push_back(tree_2lOS_CR);
  //tree.push_back(tree_2lSS_lepMVA_CR);


  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree_2lSS->Add(list[i]);
      //tree_2lOS_CR->Add(list[i]);
      //tree_2lSS_lepMVA_CR->Add(list[i]);
    }



  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");


  TTree* tree_new_2lSS_tau=new TTree("syncTree_2lSS1tau_SR","syncTree_2lSS1tau_SR");
  //TTree* tree_new_2lOS_CR_tau=new TTree("syncTree_2lSS1tau_Flip","syncTree_2lSS_1tau_Flip");
  //TTree* tree_new_2lSS_lepMVA_CR_tau=new TTree("syncTree_2lSS1tau_Fake","syncTree_2lSS1tau_Fake");


  vector<TTree*> tree_new;
  tree_new.push_back(tree_new_2lSS_tau);
  //tree_new.push_back(tree_new_2lOS_CR_tau);
  //tree_new.push_back(tree_new_2lSS_lepMVA_CR_tau);


  //New branches
  ULong64_t _nEvent;
  int _ls;
  int _run;

  int _n_presel_mu;
  int _n_fakeablesel_mu;
  int _n_mvasel_mu;

  int _n_presel_ele;
  int _n_fakeablesel_ele;
  int _n_mvasel_ele;

  int _n_presel_tau;
  int _n_presel_jet;

  float _mu0_pt;
  float _mu0_conept;
  float _mu0_eta;
  float _mu0_phi;
  float _mu0_E;
  int _mu0_charge;
  int _mu0_jetNDauChargedMVASel;
  float _mu0_miniRelIso;
  float _mu0_miniIsoCharged;
  float _mu0_miniIsoNeutral;
  float _mu0_jetPtRel;
  float _mu0_jetPtRatio;
  float _mu0_jetCSV;
  float _mu0_sip3D;
  float _mu0_dxy;
  float _mu0_dz;
  float _mu0_segmentCompatibility;
  float _mu0_leptonMVA;
  bool _mu0_mediumID;
  float _mu0_dpt_div_pt;
  bool _mu0_isfakeablesel;
  bool _mu0_ismvasel;


  float _mu1_pt;
  float _mu1_conept;
  float _mu1_eta;
  float _mu1_phi;
  float _mu1_E;
  int _mu1_charge;
  int _mu1_jetNDauChargedMVASel;
  float _mu1_miniRelIso;
  float _mu1_miniIsoCharged;
  float _mu1_miniIsoNeutral;
  float _mu1_jetPtRel;
  float _mu1_jetPtRatio;
  float _mu1_jetCSV;
  float _mu1_sip3D;
  float _mu1_dxy;
  float _mu1_dz;
  float _mu1_segmentCompatibility;
  float _mu1_leptonMVA;
  bool _mu1_mediumID;
  float _mu1_dpt_div_pt;
  bool _mu1_isfakeablesel;
  bool _mu1_ismvasel;

  float _ele0_pt;
  float _ele0_conept;
  float _ele0_eta;
  float _ele0_phi;
  float _ele0_E;
  int   _ele0_charge;
  int   _ele0_jetNDauChargedMVASel;
  float _ele0_miniRelIso;
  float _ele0_miniIsoCharged;
  float _ele0_miniIsoNeutral;
  float _ele0_jetPtRel;
  float _ele0_jetPtRatio;
  float _ele0_jetCSV;
  float _ele0_sip3D;
  float _ele0_dxy;
  float _ele0_dz;
  float _ele0_ntMVAeleID;
  float _ele0_leptonMVA;
  bool _ele0_isChargeConsistent;
  bool _ele0_passesConversionVeto;
  int _ele0_nMissingHits;
  bool _ele0_isfakeablesel;
  bool _ele0_ismvasel;

  float _ele1_pt;
  float _ele1_conept;
  float _ele1_eta;
  float _ele1_phi;
  float _ele1_E;
  int   _ele1_charge;
  int   _ele1_jetNDauChargedMVASel;
  float _ele1_miniRelIso;
  float _ele1_miniIsoCharged;
  float _ele1_miniIsoNeutral;
  float _ele1_jetPtRel;
  float _ele1_jetPtRatio;
  float _ele1_jetCSV;
  float _ele1_sip3D;
  float _ele1_dxy;
  float _ele1_dz;
  float _ele1_ntMVAeleID;
  float _ele1_leptonMVA;
  bool _ele1_isChargeConsistent;
  bool _ele1_passesConversionVeto;
  int _ele1_nMissingHits;
  bool _ele1_isfakeablesel;
  bool _ele1_ismvasel;

  float _tau0_pt;
  float _tau0_eta;
  float _tau0_phi;
  float _tau0_E;
  int _tau0_charge;
  float _tau0_dxy;
  float _tau0_dz;
  int _tau0_decayModeFindingOldDMs;
  int _tau0_decayModeFindingNewDMs;
  float _tau0_byCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau0_againstMuonLoose3;
  int _tau0_againstMuonTight3;
  int _tau0_againstElectronVLooseMVA6;
  int _tau0_againstElectronLooseMVA6;
  int _tau0_againstElectronMediumMVA6;
  int _tau0_againstElectronTightMVA6;
  int _tau0_againstElectronVTightMVA6;

  float _tau1_pt;
  float _tau1_eta;
  float _tau1_phi;
  float _tau1_E;
  int _tau1_charge;
  float _tau1_dxy;
  float _tau1_dz;
  int _tau1_decayModeFindingOldDMs;
  int _tau1_decayModeFindingNewDMs;
  float _tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _tau1_againstMuonLoose3;
  int _tau1_againstMuonTight3;
  int _tau1_againstElectronVLooseMVA6;
  int _tau1_againstElectronLooseMVA6;
  int _tau1_againstElectronMediumMVA6;
  int _tau1_againstElectronTightMVA6;
  int _tau1_againstElectronVTightMVA6;

  float _jet0_pt;
  float _jet0_eta;
  float _jet0_phi;
  float _jet0_E;
  float _jet0_CSV;
	
  float _jet1_pt;
  float _jet1_eta;
  float _jet1_phi;
  float _jet1_E;
  float _jet1_CSV;
	
  float _jet2_pt;
  float _jet2_eta;
  float _jet2_phi;
  float _jet2_E;
  float _jet2_CSV;
	
  float _jet3_pt;
  float _jet3_eta;
  float _jet3_phi;
  float _jet3_E;
  float _jet3_CSV;

  float _PFMET;
  float _PFMETphi;
  float _MHT;
  float _metLD;

  float _lep0_conept;
  float _lep1_conept;
  float _mindr_lep0_jet;
  float _mindr_lep1_jet;
  float _MT_met_lep0;
  float _avg_dr_jet;
  float _MVA_2lss_ttV;
  float _MVA_2lss_ttbar;


  float _FR_weight;
  float _triggerSF_weight;
  float _leptonSF_weight;
  float _tauSF_weight;
  float _bTagSF_CSVshape_weight;
  float _PU_weight;
  float _MC_weight;

  bool _isGenMatched;

  int _integration_type;
  float _Integral_ttH;
  float _Integral_ttZ;
  float _Integral_ttZ_Zll;
  float _Integral_ttbar;
  float _MEM_LR;

  float _dR_leps;
  float _mvis_l0tau;

  float _MVA_2lSS1tau_noMEM_ttbar;
  float _MVA_2lSS1tau_noMEM_ttV;
  float _MVA_2lSS1tau_noMEM_2Dbin;
  float _MVA_2lSS1tau_MEM_LR_ttbar;
  float _MVA_2lSS1tau_MEM_LR_ttV;
  float _MVA_2lSS1tau_MEM_LR_2Dbin;


  for(unsigned int i=0;i<tree_new.size();i++){

    tree_new[i]->Branch("nEvent",        &_nEvent,         "nEvent/L");
    tree_new[i]->Branch("ls",            &_ls,             "ls/I");
    tree_new[i]->Branch("run",           &_run,            "run/I");

    tree_new[i]->Branch("n_presel_mu",      &_n_presel_mu,      "n_presel_mu/I");
    tree_new[i]->Branch("n_fakeablesel_mu", &_n_fakeablesel_mu, "n_fakeablesel_mu/I");
    tree_new[i]->Branch("n_mvasel_mu",      &_n_mvasel_mu,      "n_mvasel_mu/I");

    tree_new[i]->Branch("n_presel_ele",      &_n_presel_ele,      "n_presel_ele/I");
    tree_new[i]->Branch("n_fakeablesel_ele", &_n_fakeablesel_ele, "n_fakeablesel_ele/I");
    tree_new[i]->Branch("n_mvasel_ele",      &_n_mvasel_ele,      "n_mvasel_ele/I");

    tree_new[i]->Branch("n_presel_tau",  &_n_presel_tau,   "n_presel_tau/I");
    tree_new[i]->Branch("n_presel_jet",  &_n_presel_jet,   "n_presel_jet/I");
	   
    tree_new[i]->Branch("mu0_pt",        &_mu0_pt,         "mu0_pt/F");
    tree_new[i]->Branch("mu0_conept",    &_mu0_conept,     "mu0_conept/F");
    tree_new[i]->Branch("mu0_eta",       &_mu0_eta,        "mu0_eta/F");
    tree_new[i]->Branch("mu0_phi",       &_mu0_phi,        "mu0_phi/F");
    tree_new[i]->Branch("mu0_E",         &_mu0_E,          "mu0_E/F");
    tree_new[i]->Branch("mu0_charge",    &_mu0_charge,     "mu0_charge/I");
    tree_new[i]->Branch("mu0_jetNDauChargedMVASel",&_mu0_jetNDauChargedMVASel,"mu0_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("mu0_miniRelIso",          &_mu0_miniRelIso,          "mu0_miniRelIso/F");
    tree_new[i]->Branch("mu0_miniIsoCharged",      &_mu0_miniIsoCharged,      "mu0_miniIsoCharged/F");
    tree_new[i]->Branch("mu0_miniIsoNeutral",      &_mu0_miniIsoNeutral,      "mu0_miniIsoNeutral/F");
    tree_new[i]->Branch("mu0_jetPtRel",  &_mu0_jetPtRel,   "mu0_jetPtRel/F");
    tree_new[i]->Branch("mu0_jetPtRatio",&_mu0_jetPtRatio, "mu0_jetPtRatio/F");
    tree_new[i]->Branch("mu0_jetCSV",    &_mu0_jetCSV,     "mu0_jetCSV/F");
    tree_new[i]->Branch("mu0_sip3D",     &_mu0_sip3D,      "mu0_sip3D/F");
    tree_new[i]->Branch("mu0_dxy",       &_mu0_dxy,        "mu0_dxy/F");
    tree_new[i]->Branch("mu0_dz",        &_mu0_dz,         "mu0_dz/F");
    tree_new[i]->Branch("mu0_segmentCompatibility",&_mu0_segmentCompatibility,"mu0_segmentCompatibility/F");
    tree_new[i]->Branch("mu0_leptonMVA",     &_mu0_leptonMVA,     "mu0_leptonMVA/F");
    tree_new[i]->Branch("mu0_mediumID",      &_mu0_mediumID,      "mu0_mediumID/O");
    tree_new[i]->Branch("mu0_dpt_div_pt",    &_mu0_dpt_div_pt,    "mu0_dpt_div_pt/F");
    tree_new[i]->Branch("mu0_isfakeablesel", &_mu0_isfakeablesel, "mu0_isfakeablesel/O");
    tree_new[i]->Branch("mu0_ismvasel",      &_mu0_ismvasel,      "mu0_ismvasel/O");

    tree_new[i]->Branch("mu1_pt",        &_mu1_pt,         "mu1_pt/F");
    tree_new[i]->Branch("mu1_conept",    &_mu1_conept,     "mu1_conept/F");
    tree_new[i]->Branch("mu1_eta",       &_mu1_eta,        "mu1_eta/F");
    tree_new[i]->Branch("mu1_phi",       &_mu1_phi,        "mu1_phi/F");
    tree_new[i]->Branch("mu1_E",         &_mu1_E,          "mu1_E/F");
    tree_new[i]->Branch("mu1_charge",    &_mu1_charge,     "mu1_charge/I");
    tree_new[i]->Branch("mu1_jetNDauChargedMVASel",&_mu1_jetNDauChargedMVASel,"mu1_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("mu1_miniRelIso",          &_mu1_miniRelIso,          "mu1_miniRelIso/F");
    tree_new[i]->Branch("mu1_miniIsoCharged",      &_mu1_miniIsoCharged,      "mu1_miniIsoCharged/F");
    tree_new[i]->Branch("mu1_miniIsoNeutral",      &_mu1_miniIsoNeutral,      "mu1_miniIsoNeutral/F");
    tree_new[i]->Branch("mu1_jetPtRel",  &_mu1_jetPtRel,   "mu1_jetPtRel/F");
    tree_new[i]->Branch("mu1_jetPtRatio",&_mu1_jetPtRatio, "mu1_jetPtRatio/F");
    tree_new[i]->Branch("mu1_jetCSV",    &_mu1_jetCSV,     "mu1_jetCSV/F");
    tree_new[i]->Branch("mu1_sip3D",     &_mu1_sip3D,      "mu1_sip3D/F");
    tree_new[i]->Branch("mu1_dxy",       &_mu1_dxy,        "mu1_dxy/F");
    tree_new[i]->Branch("mu1_dz",        &_mu1_dz,         "mu1_dz/F");
    tree_new[i]->Branch("mu1_segmentCompatibility",&_mu1_segmentCompatibility,"mu1_segmentCompatibility/F");
    tree_new[i]->Branch("mu1_leptonMVA",&_mu1_leptonMVA,"mu1_leptonMVA/F");
    tree_new[i]->Branch("mu1_mediumID",      &_mu1_mediumID,      "mu1_mediumID/O");
    tree_new[i]->Branch("mu1_dpt_div_pt",    &_mu1_dpt_div_pt,    "mu1_dpt_div_pt/F");
    tree_new[i]->Branch("mu1_isfakeablesel", &_mu1_isfakeablesel, "mu1_isfakeablesel/O");
    tree_new[i]->Branch("mu1_ismvasel",      &_mu1_ismvasel,      "mu1_ismvasel/O");

    tree_new[i]->Branch("ele0_pt",        &_ele0_pt,         "ele0_pt/F");
    tree_new[i]->Branch("ele0_conept",    &_ele0_conept,     "ele0_conept/F");
    tree_new[i]->Branch("ele0_eta",       &_ele0_eta,        "ele0_eta/F");
    tree_new[i]->Branch("ele0_phi",       &_ele0_phi,        "ele0_phi/F");
    tree_new[i]->Branch("ele0_E",         &_ele0_E,          "ele0_E/F");
    tree_new[i]->Branch("ele0_charge",    &_ele0_charge,     "ele0_charge/I");
    tree_new[i]->Branch("ele0_jetNDauChargedMVASel",&_ele0_jetNDauChargedMVASel,"ele0_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("ele0_miniRelIso",          &_ele0_miniRelIso,          "ele0_miniRelIso/F");
    tree_new[i]->Branch("ele0_miniIsoCharged",      &_ele0_miniIsoCharged,      "ele0_miniIsoCharged/F");
    tree_new[i]->Branch("ele0_miniIsoNeutral",      &_ele0_miniIsoNeutral,      "ele0_miniIsoNeutral/F");
    tree_new[i]->Branch("ele0_jetPtRel",  &_ele0_jetPtRel,   "ele0_jetPtRel/F");
    tree_new[i]->Branch("ele0_jetPtRatio",&_ele0_jetPtRatio, "ele0_jetPtRatio/F");
    tree_new[i]->Branch("ele0_jetCSV",    &_ele0_jetCSV,     "ele0_jetCSV/F");
    tree_new[i]->Branch("ele0_sip3D",     &_ele0_sip3D,      "ele0_sip3D/F");
    tree_new[i]->Branch("ele0_dxy",       &_ele0_dxy,        "ele0_dxy/F");
    tree_new[i]->Branch("ele0_dz",        &_ele0_dz,         "ele0_dz/F");
    tree_new[i]->Branch("ele0_ntMVAeleID",&_ele0_ntMVAeleID, "ele0_ntMVAeleID/F");
    tree_new[i]->Branch("ele0_leptonMVA", &_ele0_leptonMVA,  "ele0_leptonMVA/F");
    tree_new[i]->Branch("ele0_isChargeConsistent",   &_ele0_isChargeConsistent,    "ele0_isChargeConsistent/O");
    tree_new[i]->Branch("ele0_passesConversionVeto", &_ele0_passesConversionVeto,  "ele0_passesConversionVeto/O");
    tree_new[i]->Branch("ele0_nMissingHits",  &_ele0_nMissingHits,  "ele0_nMissingHits/I");
    tree_new[i]->Branch("ele0_isfakeablesel", &_ele0_isfakeablesel, "ele0_isfakeablesel/O");
    tree_new[i]->Branch("ele0_ismvasel",      &_ele0_ismvasel,      "ele0_ismvasel/O");

    tree_new[i]->Branch("ele1_pt",        &_ele1_pt,         "ele1_pt/F");
    tree_new[i]->Branch("ele1_conept",    &_ele1_conept,     "ele1_conept/F");
    tree_new[i]->Branch("ele1_eta",       &_ele1_eta,        "ele1_eta/F");
    tree_new[i]->Branch("ele1_phi",       &_ele1_phi,        "ele1_phi/F");
    tree_new[i]->Branch("ele1_E",         &_ele1_E,          "ele1_E/F");
    tree_new[i]->Branch("ele1_charge",    &_ele1_charge,     "ele1_charge/I");
    tree_new[i]->Branch("ele1_jetNDauChargedMVASel",&_ele1_jetNDauChargedMVASel,"ele1_jetNDauChargedMVASel/I");
    tree_new[i]->Branch("ele1_miniRelIso",          &_ele1_miniRelIso,          "ele1_miniRelIso/F");
    tree_new[i]->Branch("ele1_miniIsoCharged",      &_ele1_miniIsoCharged,      "ele1_miniIsoCharged/F");
    tree_new[i]->Branch("ele1_miniIsoNeutral",      &_ele1_miniIsoNeutral,      "ele1_miniIsoNeutral/F");
    tree_new[i]->Branch("ele1_jetPtRel",  &_ele1_jetPtRel,   "ele1_jetPtRel/F");
    tree_new[i]->Branch("ele1_jetPtRatio",&_ele1_jetPtRatio, "ele1_jetPtRatio/F");
    tree_new[i]->Branch("ele1_jetCSV",    &_ele1_jetCSV,     "ele1_jetCSV/F");
    tree_new[i]->Branch("ele1_sip3D",     &_ele1_sip3D,      "ele1_sip3D/F");
    tree_new[i]->Branch("ele1_dxy",       &_ele1_dxy,        "ele1_dxy/F");
    tree_new[i]->Branch("ele1_dz",        &_ele1_dz,         "ele1_dz/F");
    tree_new[i]->Branch("ele1_ntMVAeleID",&_ele1_ntMVAeleID, "ele1_ntMVAeleID/F");
    tree_new[i]->Branch("ele1_leptonMVA", &_ele1_leptonMVA,  "ele1_leptonMVA/F");
    tree_new[i]->Branch("ele1_isChargeConsistent",   &_ele1_isChargeConsistent,    "ele1_isChargeConsistent/O");
    tree_new[i]->Branch("ele1_passesConversionVeto", &_ele1_passesConversionVeto,  "ele1_passesConversionVeto/O");
    tree_new[i]->Branch("ele1_nMissingHits",  &_ele1_nMissingHits,  "ele1_nMissingHits/I");
    tree_new[i]->Branch("ele1_isfakeablesel", &_ele1_isfakeablesel, "ele1_isfakeablesel/O");
    tree_new[i]->Branch("ele1_ismvasel",      &_ele1_ismvasel,      "ele1_ismvasel/O");

    tree_new[i]->Branch("tau0_pt",        &_tau0_pt,         "tau0_pt/F");
    tree_new[i]->Branch("tau0_eta",       &_tau0_eta,        "tau0_eta/F");
    tree_new[i]->Branch("tau0_phi",       &_tau0_phi,        "tau0_phi/F");
    tree_new[i]->Branch("tau0_E",         &_tau0_E,          "tau0_E/F");
    tree_new[i]->Branch("tau0_charge",    &_tau0_charge,     "tau0_charge/I");
    tree_new[i]->Branch("tau0_dxy",       &_tau0_dxy,        "tau0_dxy/F");
    tree_new[i]->Branch("tau0_dz",        &_tau0_dz,         "tau0_dz/F");
    tree_new[i]->Branch("tau0_decayModeFindingOldDMs",                       &_tau0_decayModeFindingOldDMs,                       "tau0_decayModeFindingOldDMs/I");
    tree_new[i]->Branch("tau0_decayModeFindingNewDMs",                       &_tau0_decayModeFindingNewDMs,                       "tau0_decayModeFindingNewDMs/I");
    tree_new[i]->Branch("tau0_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau0_byCombinedIsolationDeltaBetaCorr3Hits,        "tau0_byCombinedIsolationDeltaBetaCorr3Hits/F");
    tree_new[i]->Branch("tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau0_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau0_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau0_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau0_againstMuonLoose3",         &_tau0_againstMuonLoose3,         "tau0_againstMuonLoose3/I");                         
    tree_new[i]->Branch("tau0_againstMuonTight3",         &_tau0_againstMuonTight3,         "tau0_againstMuonTight3/I");                         
    tree_new[i]->Branch("tau0_againstElectronVLooseMVA6", &_tau0_againstElectronVLooseMVA6, "tau0_againstElectronVLooseMVA6/I");                         
    tree_new[i]->Branch("tau0_againstElectronLooseMVA6",  &_tau0_againstElectronLooseMVA6,  "tau0_againstElectronLooseMVA6/I");                         
    tree_new[i]->Branch("tau0_againstElectronMediumMVA6", &_tau0_againstElectronMediumMVA6, "tau0_againstElectronMediumMVA6/I");                         
    tree_new[i]->Branch("tau0_againstElectronTightMVA6",  &_tau0_againstElectronTightMVA6,  "tau0_againstElectronTightMVA6/I");   
    tree_new[i]->Branch("tau0_againstElectronVTightMVA6", &_tau0_againstElectronVTightMVA6, "tau0_againstElectronVTightMVA6/I");   

    tree_new[i]->Branch("tau1_pt",        &_tau1_pt,         "tau1_pt/F");
    tree_new[i]->Branch("tau1_eta",       &_tau1_eta,        "tau1_eta/F");
    tree_new[i]->Branch("tau1_phi",       &_tau1_phi,        "tau1_phi/F");
    tree_new[i]->Branch("tau1_E",         &_tau1_E,          "tau1_E/F");
    tree_new[i]->Branch("tau1_charge",    &_tau1_charge,     "tau1_charge/I");
    tree_new[i]->Branch("tau1_dxy",       &_tau1_dxy,        "tau1_dxy/F");
    tree_new[i]->Branch("tau1_dz",        &_tau1_dz,         "tau1_dz/F");
    tree_new[i]->Branch("tau1_decayModeFindingOldDMs",                       &_tau1_decayModeFindingOldDMs,                       "tau1_decayModeFindingOldDMs/I");
    tree_new[i]->Branch("tau1_decayModeFindingNewDMs",                       &_tau1_decayModeFindingNewDMs,                       "tau1_decayModeFindingNewDMs/I");
    tree_new[i]->Branch("tau1_byCombinedIsolationDeltaBetaCorr3Hits",        &_tau1_byCombinedIsolationDeltaBetaCorr3Hits,        "tau1_byCombinedIsolationDeltaBetaCorr3Hits/F");
    tree_new[i]->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3Hits",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3Hits,   "tau1_byTightCombinedIsolationDeltaBetaCorr3Hits/I");
    tree_new[i]->Branch("tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",  &_tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03,  "tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",   &_tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03,   "tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03/I");
    tree_new[i]->Branch("tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT",      &_tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT,      "tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT",     &_tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT,     "tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT/I");
    tree_new[i]->Branch("tau1_againstMuonLoose3",         &_tau1_againstMuonLoose3,         "tau1_againstMuonLoose3/I");                         
    tree_new[i]->Branch("tau1_againstMuonTight3",         &_tau1_againstMuonTight3,         "tau1_againstMuonTight3/I");                         
    tree_new[i]->Branch("tau1_againstElectronVLooseMVA6", &_tau1_againstElectronVLooseMVA6, "tau1_againstElectronVLooseMVA6/I");                         
    tree_new[i]->Branch("tau1_againstElectronLooseMVA6",  &_tau1_againstElectronLooseMVA6,  "tau1_againstElectronLooseMVA6/I");                         
    tree_new[i]->Branch("tau1_againstElectronMediumMVA6", &_tau1_againstElectronMediumMVA6, "tau1_againstElectronMediumMVA6/I");                         
    tree_new[i]->Branch("tau1_againstElectronTightMVA6",  &_tau1_againstElectronTightMVA6,  "tau1_againstElectronTightMVA6/I");   
    tree_new[i]->Branch("tau1_againstElectronVTightMVA6", &_tau1_againstElectronVTightMVA6,  "tau1_againstElectronVTightMVA6/I");   

    tree_new[i]->Branch("jet0_pt",  &_jet0_pt,  "jet0_pt/F");
    tree_new[i]->Branch("jet0_eta", &_jet0_eta, "jet0_eta/F");
    tree_new[i]->Branch("jet0_phi", &_jet0_phi, "jet0_phi/F");
    tree_new[i]->Branch("jet0_E",   &_jet0_E,   "jet0_E/F");
    tree_new[i]->Branch("jet0_CSV", &_jet0_CSV, "jet0_CSV/F");

    tree_new[i]->Branch("jet1_pt",  &_jet1_pt,  "jet1_pt/F");
    tree_new[i]->Branch("jet1_eta", &_jet1_eta, "jet1_eta/F");
    tree_new[i]->Branch("jet1_phi", &_jet1_phi, "jet1_phi/F");
    tree_new[i]->Branch("jet1_E",   &_jet1_E,   "jet1_E/F");
    tree_new[i]->Branch("jet1_CSV", &_jet1_CSV, "jet1_CSV/F");

    tree_new[i]->Branch("jet2_pt",  &_jet2_pt,  "jet2_pt/F");
    tree_new[i]->Branch("jet2_eta", &_jet2_eta, "jet2_eta/F");
    tree_new[i]->Branch("jet2_phi", &_jet2_phi, "jet2_phi/F");
    tree_new[i]->Branch("jet2_E",   &_jet2_E,   "jet2_E/F");
    tree_new[i]->Branch("jet2_CSV", &_jet2_CSV, "jet2_CSV/F");

    tree_new[i]->Branch("jet3_pt",  &_jet3_pt,  "jet3_pt/F");
    tree_new[i]->Branch("jet3_eta", &_jet3_eta, "jet3_eta/F");
    tree_new[i]->Branch("jet3_phi", &_jet3_phi, "jet3_phi/F");
    tree_new[i]->Branch("jet3_E",   &_jet3_E,   "jet3_E/F");
    tree_new[i]->Branch("jet3_CSV", &_jet3_CSV, "jet3_CSV/F");

    tree_new[i]->Branch("PFMET",    &_PFMET,    "PFMET/F");
    tree_new[i]->Branch("PFMETphi", &_PFMETphi, "PFMETphi/F");
    tree_new[i]->Branch("MHT",      &_MHT,       "MHT/F");
    tree_new[i]->Branch("metLD",    &_metLD,     "metLD/F");
	  
    tree_new[i]->Branch("lep0_conept",    &_lep0_conept,     "lep0_conept/F");
    tree_new[i]->Branch("lep1_conept",    &_lep1_conept,     "lep1_conept/F");
    tree_new[i]->Branch("mindr_lep0_jet", &_mindr_lep0_jet,  "mindr_lep0_jet/F");
    tree_new[i]->Branch("mindr_lep1_jet", &_mindr_lep1_jet,  "mindr_lep1_jet/F");
    tree_new[i]->Branch("MT_met_lep0",    &_MT_met_lep0,     "MT_met_lep0/F");
    tree_new[i]->Branch("avg_dr_jet",     &_avg_dr_jet,      "avg_dr_jet/F");
    tree_new[i]->Branch("MVA_2lss_ttV",   &_MVA_2lss_ttV,    "MVA_2lss_ttV/F");
    tree_new[i]->Branch("MVA_2lss_ttbar", &_MVA_2lss_ttbar,  "MVA_2lss_ttbar/F");
    /*tree_new[i]->Branch("tt_deltaR",      &_tt_deltaR,       "tt_deltaR/F");
    tree_new[i]->Branch("ntags",          &_ntags,           "ntags/I");
    tree_new[i]->Branch("ntags_loose",    &_ntags_loose,     "ntags_loose/I");
    tree_new[i]->Branch("tt_mvis",        &_tt_mvis,         "tt_mvis/F");
    tree_new[i]->Branch("HT",             &_HT,              "HT/F");
    tree_new[i]->Branch("MVA_1l2tau_ttbar",        &_MVA_1l2tau_ttbar,         "MVA_1l2tau_ttbar/F");*/

    tree_new[i]->Branch("FR_weight", &_FR_weight,  "FR_weight/F");
    tree_new[i]->Branch("triggerSF_weight", &_triggerSF_weight,  "triggerSF_weight/F");
    //tree_new[i]->Branch("leptonSF_weight", &_leptonSF_weight,  "leptonSF_weight/F");
    tree_new[i]->Branch("leptonSF_weight", &_leptonSF_weight,  "leptonSF_weight/F");
    tree_new[i]->Branch("tauSF_weight", &_tauSF_weight,  "tauSF_weight/F");
    tree_new[i]->Branch("bTagSF_weight", &_bTagSF_CSVshape_weight,  "bTagSF_weight/F");
    tree_new[i]->Branch("PU_weight", &_PU_weight,  "PU_weight/F");
    tree_new[i]->Branch("MC_weight", &_MC_weight,  "MC_weight/F");

    tree_new[i]->Branch("isGenMatched", &_isGenMatched, "isGenMatched/O");

    tree_new[i]->Branch("integration_type", &_integration_type, "integration_type/I");
    tree_new[i]->Branch("Integral_ttH", &_Integral_ttH, "Integral_ttH/F");
    tree_new[i]->Branch("Integral_ttZ", &_Integral_ttZ, "Integral_ttZ/F");
    tree_new[i]->Branch("Integral_ttZ_Zll", &_Integral_ttZ_Zll, "Integral_ttZ_Zll/F");
    tree_new[i]->Branch("Integral_ttbar", &_Integral_ttbar, "Integral_ttbar/F");
    tree_new[i]->Branch("MEM_LR", &_MEM_LR, "MEM_LR/F");

    tree_new[i]->Branch("dR_leps", &_dR_leps, "dR_leps/F");
    tree_new[i]->Branch("mvis_l0tau", &_mvis_l0tau, "mvis_l0tau/F");

    tree_new[i]->Branch("MVA_2lSS1tau_noMEM_ttbar",  &_MVA_2lSS1tau_noMEM_ttbar,      "MVA_2lSS1tau_noMEM_ttbar/F");
    tree_new[i]->Branch("MVA_2lSS1tau_noMEM_ttV",    &_MVA_2lSS1tau_noMEM_ttV,        "MVA_2lSS1tau_noMEM_ttV/F");
    tree_new[i]->Branch("MVA_2lSS1tau_noMEM_2Dbin",  &_MVA_2lSS1tau_noMEM_2Dbin,      "MVA_2lSS1tau_noMEM_2Dbin/I");
    tree_new[i]->Branch("MVA_2lSS1tau_MEM_LR_ttbar",  &_MVA_2lSS1tau_MEM_LR_ttbar,      "MVA_2lSS1tau_MEM_LR_ttbar/F");
    tree_new[i]->Branch("MVA_2lSS1tau_MEM_LR_ttV",    &_MVA_2lSS1tau_MEM_LR_ttV,        "MVA_2lSS1tau_MEM_LR_ttV/F");
    tree_new[i]->Branch("MVA_2lSS1tau_MEM_LR_2Dbin",  &_MVA_2lSS1tau_MEM_LR_2Dbin,      "MVA_2lSS1tau_MEM_LR_2Dbin/I");

  }


  //Old branches used
  vector<float> *_recomu_pt;
  vector<float> *_recomu_conept;
  vector<float> *_recomu_eta;
  vector<float> *_recomu_phi;
  vector<float> *_recomu_e;
  vector<int>   *_recomu_charge;
  vector<int>   *_recomu_jetNDauChargedMVASel;
  vector<float> *_recomu_miniRelIso;
  vector<float> *_recomu_miniIsoCharged;
  vector<float> *_recomu_miniIsoNeutral;
  vector<float> *_recomu_jetPtRel;
  vector<float> *_recomu_jetPtRatio;
  vector<float> *_recomu_jetCSV;
  vector<float> *_recomu_sip3D;
  vector<float> *_recomu_dxy;
  vector<float> *_recomu_dz;
  vector<float> *_recomu_lepMVA_mvaId;
  vector<float> *_recomu_leptonMVA;
  vector<bool>  *_recomu_mediumID;
  vector<float> *_recomu_rel_error_trackpt;
  vector<bool>  *_recomu_isfakeable;
  vector<bool>  *_recomu_ismvasel;

  vector<float> *_recoele_pt;
  vector<float> *_recoele_conept;
  vector<float> *_recoele_eta;
  vector<float> *_recoele_phi;
  vector<float> *_recoele_e;
  vector<int>   *_recoele_charge;
  vector<int>   *_recoele_jetNDauChargedMVASel;
  vector<float> *_recoele_miniRelIso;
  vector<float> *_recoele_miniIsoCharged;
  vector<float> *_recoele_miniIsoNeutral;
  vector<float> *_recoele_jetPtRel;
  vector<float> *_recoele_jetPtRatio;
  vector<float> *_recoele_jetCSV;
  vector<float> *_recoele_sip3D;
  vector<float> *_recoele_dxy;
  vector<float> *_recoele_dz;
  vector<float> *_recoele_lepMVA_mvaId;
  vector<float> *_recoele_leptonMVA;
  vector<bool>  *_recoele_isChargeConsistent;
  vector<bool>  *_recoele_passConversionVeto;
  vector<int>   *_recoele_nMissingHits;
  vector<bool>  *_recoele_isfakeable;
  vector<bool>  *_recoele_ismvasel;

  vector<float> *_recotauh_pt;
  vector<float> *_recotauh_eta;
  vector<float> *_recotauh_phi;
  vector<float> *_recotauh_e;
  vector<int>   *_recotauh_charge;
  vector<float> *_recotauh_dxy;
  vector<float> *_recotauh_dz;
  vector<float> *_recotauh_iso;
  vector<int>  *_recotauh_decayModeFindingOldDMs;
  vector<int>  *_recotauh_decayModeFindingNewDMs;
  vector<int>  *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int>  *_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int>  *_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>  *_recotauh_againstMuonLoose3;
  vector<int>  *_recotauh_againstMuonTight3;
  vector<int>  *_recotauh_againstElectronVLooseMVA6;
  vector<int>  *_recotauh_againstElectronLooseMVA6;
  vector<int>  *_recotauh_againstElectronMediumMVA6;
  vector<int>  *_recotauh_againstElectronTightMVA6;
  vector<int>  *_recotauh_againstElectronVTightMVA6;
  vector<bool> *_recotauh_sel_isGenMatched;
  vector<int> *_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;


  vector<float> *_recoPFJet_pt;
  vector<float> *_recoPFJet_eta;
  vector<float> *_recoPFJet_phi;
  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_CSVscore;

  vector<int> *_recolep_sel_pdg;
  vector<int> *_recolep_sel_charge;
  vector<int> *_recotauh_sel_charge;
  vector<float> *_recotauh_sel_pt;
  vector<float> *_recolep_sel_eta;

  int _category;
  //bool _low_mass_lep;

  float _Integral_ttbar_DL_fakelep_tlep;
  float _Integral_ttbar_DL_fakelep_ttau;

  for(unsigned int i=0;i<tree.size();i++){

    tree[i]->SetBranchAddress("EventNumber",&_nEvent);
    tree[i]->SetBranchAddress("lumi",&_ls);
    tree[i]->SetBranchAddress("RunNumber",&_run);

    tree[i]->SetBranchAddress("n_recomu_presel",&_n_presel_mu);
    tree[i]->SetBranchAddress("n_recomu_fakeable",&_n_fakeablesel_mu);
    tree[i]->SetBranchAddress("n_recomu_mvasel",&_n_mvasel_mu);

    tree[i]->SetBranchAddress("n_recoele_presel",&_n_presel_ele);
    tree[i]->SetBranchAddress("n_recoele_fakeable",&_n_fakeablesel_ele);
    tree[i]->SetBranchAddress("n_recoele_mvasel",&_n_mvasel_ele);

    tree[i]->SetBranchAddress("n_recotauh",&_n_presel_tau);
    tree[i]->SetBranchAddress("n_recoPFJet",&_n_presel_jet);

    tree[i]->SetBranchAddress("recomu_pt",                   &_recomu_pt);
    tree[i]->SetBranchAddress("recomu_conept",               &_recomu_conept);
    tree[i]->SetBranchAddress("recomu_eta",                  &_recomu_eta);
    tree[i]->SetBranchAddress("recomu_phi",                  &_recomu_phi);
    tree[i]->SetBranchAddress("recomu_e",                    &_recomu_e);
    tree[i]->SetBranchAddress("recomu_charge",               &_recomu_charge);
    tree[i]->SetBranchAddress("recomu_jetNDauChargedMVASel", &_recomu_jetNDauChargedMVASel);
    tree[i]->SetBranchAddress("recomu_miniRelIso",           &_recomu_miniRelIso);
    tree[i]->SetBranchAddress("recomu_miniIsoCharged",       &_recomu_miniIsoCharged);
    tree[i]->SetBranchAddress("recomu_miniIsoNeutral",       &_recomu_miniIsoNeutral);
    tree[i]->SetBranchAddress("recomu_jetPtRel",             &_recomu_jetPtRel);
    tree[i]->SetBranchAddress("recomu_jetPtRatio",           &_recomu_jetPtRatio);
    tree[i]->SetBranchAddress("recomu_jetCSV",               &_recomu_jetCSV);
    tree[i]->SetBranchAddress("recomu_sip3D",                &_recomu_sip3D);
    tree[i]->SetBranchAddress("recomu_dxy",                  &_recomu_dxy);
    tree[i]->SetBranchAddress("recomu_dz",                   &_recomu_dz);
    tree[i]->SetBranchAddress("recomu_lepMVA_mvaId",         &_recomu_lepMVA_mvaId);
    tree[i]->SetBranchAddress("recomu_leptonMVA",            &_recomu_leptonMVA);
    tree[i]->SetBranchAddress("recomu_mediumID",             &_recomu_mediumID);
    tree[i]->SetBranchAddress("recomu_rel_error_trackpt",    &_recomu_rel_error_trackpt);
    tree[i]->SetBranchAddress("recomu_isfakeable",           &_recomu_isfakeable);
    tree[i]->SetBranchAddress("recomu_ismvasel",             &_recomu_ismvasel);

    tree[i]->SetBranchAddress("recoele_pt",                  &_recoele_pt);
    tree[i]->SetBranchAddress("recoele_conept",              &_recoele_conept);
    tree[i]->SetBranchAddress("recoele_eta",                 &_recoele_eta);
    tree[i]->SetBranchAddress("recoele_phi",                 &_recoele_phi);
    tree[i]->SetBranchAddress("recoele_e",                   &_recoele_e);
    tree[i]->SetBranchAddress("recoele_charge",              &_recoele_charge);
    tree[i]->SetBranchAddress("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
    tree[i]->SetBranchAddress("recoele_miniRelIso",          &_recoele_miniRelIso);
    tree[i]->SetBranchAddress("recoele_miniIsoCharged",      &_recoele_miniIsoCharged);
    tree[i]->SetBranchAddress("recoele_miniIsoNeutral",      &_recoele_miniIsoNeutral);
    tree[i]->SetBranchAddress("recoele_jetPtRel",            &_recoele_jetPtRel);
    tree[i]->SetBranchAddress("recoele_jetPtRatio",          &_recoele_jetPtRatio);
    tree[i]->SetBranchAddress("recoele_jetCSV",              &_recoele_jetCSV);
    tree[i]->SetBranchAddress("recoele_sip3D",               &_recoele_sip3D);
    tree[i]->SetBranchAddress("recoele_dxy",                 &_recoele_dxy);
    tree[i]->SetBranchAddress("recoele_dz",                  &_recoele_dz);
    tree[i]->SetBranchAddress("recoele_lepMVA_mvaId",        &_recoele_lepMVA_mvaId);
    tree[i]->SetBranchAddress("recoele_leptonMVA",           &_recoele_leptonMVA);
    tree[i]->SetBranchAddress("recoele_isChargeConsistent",  &_recoele_isChargeConsistent);
    tree[i]->SetBranchAddress("recoele_passConversionVeto",  &_recoele_passConversionVeto);
    tree[i]->SetBranchAddress("recoele_nMissingHits",        &_recoele_nMissingHits);
    tree[i]->SetBranchAddress("recoele_isfakeable",          &_recoele_isfakeable);
    tree[i]->SetBranchAddress("recoele_ismvasel",            &_recoele_ismvasel);

    tree[i]->SetBranchAddress("recotauh_pt",                 &_recotauh_pt);
    tree[i]->SetBranchAddress("recotauh_eta",                &_recotauh_eta);
    tree[i]->SetBranchAddress("recotauh_phi",                &_recotauh_phi);
    tree[i]->SetBranchAddress("recotauh_e",                  &_recotauh_e);
    tree[i]->SetBranchAddress("recotauh_charge",             &_recotauh_charge);
    tree[i]->SetBranchAddress("recotauh_dxy",                &_recotauh_dxy);
    tree[i]->SetBranchAddress("recotauh_dz",                 &_recotauh_dz);
    tree[i]->SetBranchAddress("recotauh_iso",                &_recotauh_iso);
    tree[i]->SetBranchAddress("recotauh_decayModeFindingOldDMs", &_recotauh_decayModeFindingOldDMs);
    tree[i]->SetBranchAddress("recotauh_decayModeFindingNewDMs", &_recotauh_decayModeFindingNewDMs);
    tree[i]->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",     &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",      &_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
    tree[i]->SetBranchAddress("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03", &_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",  &_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
    tree[i]->SetBranchAddress("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",         &_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",        &_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree[i]->SetBranchAddress("recotauh_againstMuonLoose3",           &_recotauh_againstMuonLoose3);
    tree[i]->SetBranchAddress("recotauh_againstMuonTight3",           &_recotauh_againstMuonTight3);
    tree[i]->SetBranchAddress("recotauh_againstElectronVLooseMVA6",   &_recotauh_againstElectronVLooseMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronLooseMVA6",    &_recotauh_againstElectronLooseMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronMediumMVA6",   &_recotauh_againstElectronMediumMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronTightMVA6",    &_recotauh_againstElectronTightMVA6);
    tree[i]->SetBranchAddress("recotauh_againstElectronVTightMVA6",   &_recotauh_againstElectronVTightMVA6);
    tree[i]->SetBranchAddress("recotauh_sel_isGenMatched",   &_recotauh_sel_isGenMatched);
    tree[i]->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",   &_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    
    tree[i]->SetBranchAddress("recoPFJet_pt",       &_recoPFJet_pt);
    tree[i]->SetBranchAddress("recoPFJet_eta",      &_recoPFJet_eta);
    tree[i]->SetBranchAddress("recoPFJet_phi",      &_recoPFJet_phi);
    tree[i]->SetBranchAddress("recoPFJet_e",        &_recoPFJet_e);
    tree[i]->SetBranchAddress("recoPFJet_CSVscore", &_recoPFJet_CSVscore);

    tree[i]->SetBranchAddress("PFMET",&_PFMET);
    tree[i]->SetBranchAddress("PFMET_phi",&_PFMETphi);
    tree[i]->SetBranchAddress("HTmiss",&_MHT);
    tree[i]->SetBranchAddress("ETmissLD",&_metLD);

    tree[i]->SetBranchAddress("lep0_conept",&_lep0_conept);
    tree[i]->SetBranchAddress("lep1_conept",&_lep1_conept);
    tree[i]->SetBranchAddress("mindR_lep0_recoPFjet",&_mindr_lep0_jet);
    tree[i]->SetBranchAddress("mindR_lep1_recoPFjet",&_mindr_lep1_jet);
    tree[i]->SetBranchAddress("MT_lep0",&_MT_met_lep0);
    tree[i]->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
    tree[i]->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lss_ttV);
    tree[i]->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lss_ttbar);

    tree[i]->SetBranchAddress("dR_leps",&_dR_leps);
    tree[i]->SetBranchAddress("mTauTauVis1",&_mvis_l0tau);

    tree[i]->SetBranchAddress("MVA_2lSS1tau_noMEM_ttbar", &_MVA_2lSS1tau_noMEM_ttbar);
    tree[i]->SetBranchAddress("MVA_2lSS1tau_noMEM_ttV",   &_MVA_2lSS1tau_noMEM_ttV);
    tree[i]->SetBranchAddress("MVA_2lSS1tau_noMEM_2Dbin", &_MVA_2lSS1tau_noMEM_2Dbin);
    tree[i]->SetBranchAddress("MVA_2lSS1tau_MEM_LR_ttbar",&_MVA_2lSS1tau_MEM_LR_ttbar);
    tree[i]->SetBranchAddress("MVA_2lSS1tau_MEM_LR_ttV",  &_MVA_2lSS1tau_MEM_LR_ttV);
    tree[i]->SetBranchAddress("MVA_2lSS1tau_MEM_LR_2Dbin",&_MVA_2lSS1tau_MEM_LR_2Dbin);

    tree[i]->SetBranchAddress("category",&_category);
    tree[i]->SetBranchAddress("isGenMatched",&_isGenMatched);

    tree[i]->SetBranchAddress("event_weight_ttH_v2",&_FR_weight);
    tree[i]->SetBranchAddress("triggerSF_weight_v2",&_triggerSF_weight);
    tree[i]->SetBranchAddress("leptonSF_ttH_weight_v3",&_leptonSF_weight);
    tree[i]->SetBranchAddress("tauSF_weight_v3",&_tauSF_weight);
    tree[i]->SetBranchAddress("bTagSF_CSVshape_weight_v2",&_bTagSF_CSVshape_weight);
    tree[i]->SetBranchAddress("PU_weight_MCSummer2016",&_PU_weight);
    tree[i]->SetBranchAddress("MC_weight",&_MC_weight);

    tree[i]->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree[i]->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);
    tree[i]->SetBranchAddress("recotauh_sel_charge",&_recotauh_sel_charge);
    tree[i]->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
    tree[i]->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);

    tree[i]->SetBranchAddress("integration_type",&_integration_type);
    tree[i]->SetBranchAddress("Integral_ttH",&_Integral_ttH);
    tree[i]->SetBranchAddress("Integral_ttZ",&_Integral_ttZ);
    tree[i]->SetBranchAddress("Integral_ttZ_Zll",&_Integral_ttZ_Zll);
    tree[i]->SetBranchAddress("Integral_ttbar_DL_fakelep_tlep",&_Integral_ttbar_DL_fakelep_tlep);
    tree[i]->SetBranchAddress("Integral_ttbar_DL_fakelep_ttau",&_Integral_ttbar_DL_fakelep_ttau);


  }

  
  for(unsigned int i_tree=0; i_tree<tree.size(); i_tree++){

  Long64_t nentries = tree[i_tree]->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _nEvent       = -9999;
    _ls           = -9999;
    _run          = -9999;

    _n_presel_mu  = -9999;
    _n_fakeablesel_mu  = -9999;
    _n_mvasel_mu  = -9999;

    _n_presel_ele = -9999;
    _n_fakeablesel_ele  = -9999;
    _n_mvasel_ele  = -9999;

    _n_presel_tau = -9999;
    _n_presel_jet = -9999;

    _mu0_pt       = -9999;
    _mu0_conept   = -9999;
    _mu0_eta      = -9999;
    _mu0_phi      = -9999;
    _mu0_E        = -9999;
    _mu0_charge   = -9999;
    _mu0_jetNDauChargedMVASel = -9999;
    _mu0_miniRelIso           = -9999;
    _mu0_miniIsoCharged       = -9999;
    _mu0_miniIsoNeutral       = -9999;
    _mu0_jetPtRel             = -9999;
    _mu0_jetPtRatio           = -9999;
    _mu0_jetCSV               = -9999;
    _mu0_sip3D                = -9999;
    _mu0_dxy                  = -9999;
    _mu0_dz                   = -9999;
    _mu0_segmentCompatibility = -9999;
    _mu0_leptonMVA            = -9999;
    _mu0_mediumID = 0;
    _mu0_dpt_div_pt = -9999;
    _mu0_isfakeablesel = 0;
    _mu0_ismvasel = 0;

    _mu1_pt       = -9999;
    _mu1_conept   = -9999;
    _mu1_eta      = -9999;
    _mu1_phi      = -9999;
    _mu1_E        = -9999;
    _mu1_charge   = -9999;
    _mu1_jetNDauChargedMVASel = -9999;
    _mu1_miniRelIso           = -9999;
    _mu1_miniIsoCharged       = -9999;
    _mu1_miniIsoNeutral       = -9999;
    _mu1_jetPtRel             = -9999;
    _mu1_jetPtRatio           = -9999;
    _mu1_jetCSV               = -9999;
    _mu1_sip3D                = -9999;
    _mu1_dxy                  = -9999;
    _mu1_dz                   = -9999;
    _mu1_segmentCompatibility = -9999;
    _mu1_leptonMVA            = -9999;
    _mu1_mediumID = 0;
    _mu1_dpt_div_pt = -9999;
    _mu1_isfakeablesel = 0;
    _mu1_ismvasel = 0;

    _ele0_pt       = -9999;
    _ele0_conept   = -9999;
    _ele0_eta      = -9999;
    _ele0_phi      = -9999;
    _ele0_E        = -9999;
    _ele0_charge   = -9999;
    _ele0_jetNDauChargedMVASel = -9999;
    _ele0_miniRelIso           = -9999;
    _ele0_miniIsoCharged       = -9999;
    _ele0_miniIsoNeutral       = -9999;
    _ele0_jetPtRel             = -9999;
    _ele0_jetPtRatio           = -9999;
    _ele0_jetCSV               = -9999;
    _ele0_sip3D                = -9999;
    _ele0_dxy                  = -9999;
    _ele0_dz                   = -9999;
    _ele0_ntMVAeleID           = -9999;
    _ele0_leptonMVA            = -9999;
    _ele0_isChargeConsistent   = 0;
    _ele0_passesConversionVeto = 0;
    _ele0_nMissingHits         = -9999;
    _ele0_isfakeablesel       = 0;
    _ele0_ismvasel            = 0;


    _ele1_pt       = -9999;
    _ele1_conept   = -9999;
    _ele1_eta      = -9999;
    _ele1_phi      = -9999;
    _ele1_E        = -9999;
    _ele1_charge   = -9999;
    _ele1_jetNDauChargedMVASel = -9999;
    _ele1_miniRelIso           = -9999;
    _ele1_miniIsoCharged       = -9999;
    _ele1_miniIsoNeutral       = -9999;
    _ele1_jetPtRel             = -9999;
    _ele1_jetPtRatio           = -9999;
    _ele1_jetCSV               = -9999;
    _ele1_sip3D                = -9999;
    _ele1_dxy                  = -9999;
    _ele1_dz                   = -9999;
    _ele1_ntMVAeleID           = -9999;
    _ele1_leptonMVA            = -9999;
    _ele1_isChargeConsistent   = 0;
    _ele1_passesConversionVeto = 0;
    _ele1_nMissingHits         = -9999;
    _ele1_isfakeablesel       = 0;
    _ele1_ismvasel            = 0;

    _tau0_pt       = -9999;
    _tau0_eta      = -9999;
    _tau0_phi      = -9999;
    _tau0_E        = -9999;
    _tau0_charge   = -9999;    
    _tau0_dxy      = -9999;
    _tau0_dz       = -9999;
    _tau0_decayModeFindingOldDMs                           = -9999;
    _tau0_decayModeFindingNewDMs                           = -9999;
    _tau0_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau0_againstMuonLoose3          = -9999;
    _tau0_againstMuonTight3          = -9999;
    _tau0_againstElectronVLooseMVA6  = -9999;
    _tau0_againstElectronLooseMVA6   = -9999;
    _tau0_againstElectronMediumMVA6  = -9999;
    _tau0_againstElectronTightMVA6   = -9999;
    _tau0_againstElectronVTightMVA6  = -9999;

    _tau1_pt       = -9999;
    _tau1_eta      = -9999;
    _tau1_phi      = -9999;
    _tau1_E        = -9999;
    _tau1_charge   = -9999;    
    _tau1_dxy      = -9999;
    _tau1_dz       = -9999;
    _tau1_decayModeFindingOldDMs                           = -9999;
    _tau1_decayModeFindingNewDMs                           = -9999;
    _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = -9999;
    _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = -9999;
    _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = -9999;
    _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = -9999;
    _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = -9999;
    _tau1_againstMuonLoose3          = -9999;
    _tau1_againstMuonTight3          = -9999;
    _tau1_againstElectronVLooseMVA6  = -9999;
    _tau1_againstElectronLooseMVA6   = -9999;
    _tau1_againstElectronMediumMVA6  = -9999;
    _tau1_againstElectronTightMVA6   = -9999;
    _tau1_againstElectronVTightMVA6  = -9999;
        
    _jet0_pt   = -9999;
    _jet0_eta  = -9999;
    _jet0_phi  = -9999;
    _jet0_E    = -9999;
    _jet0_CSV  = -9999;

    _jet1_pt   = -9999;
    _jet1_eta  = -9999;
    _jet1_phi  = -9999;
    _jet1_E    = -9999;
    _jet1_CSV  = -9999;

    _jet2_pt   = -9999;
    _jet2_eta  = -9999;
    _jet2_phi  = -9999;
    _jet2_E    = -9999;
    _jet2_CSV  = -9999;
	
    _jet3_pt   = -9999;
    _jet3_eta  = -9999;
    _jet3_phi  = -9999;
    _jet3_E    = -9999;
    _jet3_CSV  = -9999;

    _PFMET     = -9999;
    _PFMETphi  = -9999;    
    _MHT       = -9999;
    _metLD     = -9999;    

    _lep0_conept    = -9999;
    _lep1_conept    = -9999;
    _mindr_lep0_jet = -9999;
    _mindr_lep1_jet = -9999;
    _MT_met_lep0    = -9999;
    _avg_dr_jet     = -9999;
    _MVA_2lss_ttV   = -9999;
    _MVA_2lss_ttbar   = -9999;

    _integration_type = -1;
    _Integral_ttH = -9999;
    _Integral_ttZ = -9999;
    _Integral_ttZ_Zll = -9999;
    _Integral_ttbar = -9999;
    _MEM_LR = -9999;

    _dR_leps = -9999;
    _mvis_l0tau = -9999;

    _MVA_2lSS1tau_noMEM_ttbar = -9999;
    _MVA_2lSS1tau_noMEM_ttV = -9999;
    _MVA_2lSS1tau_noMEM_2Dbin = -9999;
    _MVA_2lSS1tau_MEM_LR_ttbar = -9999;
    _MVA_2lSS1tau_MEM_LR_ttV = -9999;
    _MVA_2lSS1tau_MEM_LR_2Dbin = -9999;

    ////
    
    _recomu_pt      = 0;
    _recomu_conept  = 0;
    _recomu_eta     = 0;
    _recomu_phi     = 0;
    _recomu_e       = 0;
    _recomu_charge  = 0;
    _recomu_jetNDauChargedMVASel = 0;
    _recomu_miniRelIso           = 0;
    _recomu_miniIsoCharged       = 0;
    _recomu_miniIsoNeutral       = 0;
    _recomu_jetPtRel             = 0;
    _recomu_jetPtRatio           = 0;
    _recomu_jetCSV               = 0;
    _recomu_sip3D                = 0;
    _recomu_dxy                  = 0;
    _recomu_dz                   = 0;
    _recomu_lepMVA_mvaId         = 0;
    _recomu_leptonMVA            = 0;
    _recomu_mediumID             = 0;
    _recomu_rel_error_trackpt    = 0;
    _recomu_isfakeable           = 0;
    _recomu_ismvasel             = 0;

    _recoele_pt      = 0;
    _recoele_conept  = 0;
    _recoele_eta     = 0;
    _recoele_phi     = 0;
    _recoele_e       = 0;
    _recoele_charge  = 0;
    _recoele_jetNDauChargedMVASel = 0;
    _recoele_miniRelIso           = 0;
    _recoele_miniIsoCharged       = 0;
    _recoele_miniIsoNeutral       = 0;
    _recoele_jetPtRel             = 0;
    _recoele_jetPtRatio           = 0;
    _recoele_jetCSV               = 0;
    _recoele_sip3D                = 0;
    _recoele_dxy                  = 0;
    _recoele_dz                   = 0;
    _recoele_lepMVA_mvaId         = 0;
    _recoele_leptonMVA            = 0;    
    _recoele_isChargeConsistent   = 0;
    _recoele_passConversionVeto   = 0;
    _recoele_nMissingHits         = 0;
    _recoele_isfakeable           = 0;
    _recoele_ismvasel             = 0;    

    _recotauh_pt     = 0;
    _recotauh_eta    = 0;
    _recotauh_phi    = 0;
    _recotauh_e      = 0;
    _recotauh_charge = 0;
    _recotauh_dxy    = 0;
    _recotauh_dz     = 0;
    _recotauh_iso    = 0;
    _recotauh_decayModeFindingOldDMs                             = 0;
    _recotauh_decayModeFindingNewDMs                             = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits        = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits         = 0;
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03    = 0;
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03     = 0;
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT            = 0;
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT           = 0;
    _recotauh_againstMuonLoose3           = 0;
    _recotauh_againstMuonTight3           = 0;
    _recotauh_againstElectronVLooseMVA6   = 0;
    _recotauh_againstElectronLooseMVA6    = 0;
    _recotauh_againstElectronMediumMVA6   = 0;
    _recotauh_againstElectronTightMVA6    = 0;
    _recotauh_againstElectronVTightMVA6   = 0;
    _recotauh_sel_isGenMatched   = 0;
    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;

    _recoPFJet_pt       = 0;
    _recoPFJet_eta      = 0;
    _recoPFJet_phi      = 0;
    _recoPFJet_e        = 0;
    _recoPFJet_CSVscore = 0;

    _recolep_sel_pdg = 0;
    _recolep_sel_charge = 0;
    _recotauh_sel_charge = 0;
    _recotauh_sel_pt = 0;
    _recolep_sel_eta = 0;

    //_low_mass_lep = 0;

    _category = 0;
    _isGenMatched = 0;

    _FR_weight = 0;
    _triggerSF_weight = 0;
    _leptonSF_weight = 0;
    _tauSF_weight = 0;
    _bTagSF_CSVshape_weight = 0;
    _PU_weight = 0;
    _MC_weight = 0;

    _Integral_ttbar_DL_fakelep_tlep = 0;
    _Integral_ttbar_DL_fakelep_ttau = 0;

    
    tree[i_tree]->GetEntry(i);

    if(_n_presel_mu>0){

      _mu0_pt     = (*_recomu_pt)[0];
      _mu0_conept = (*_recomu_conept)[0];
      _mu0_eta    = (*_recomu_eta)[0];
      _mu0_phi    = (*_recomu_phi)[0];
      _mu0_E      = (*_recomu_e)[0];
      _mu0_charge = (*_recomu_charge)[0];
      _mu0_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel)[0];
      _mu0_miniRelIso           = (*_recomu_miniRelIso)[0];
      _mu0_miniIsoCharged       = (*_recomu_miniIsoCharged)[0];
      _mu0_miniIsoNeutral       = (*_recomu_miniIsoNeutral)[0];
      _mu0_jetPtRel             = (*_recomu_jetPtRel)[0];
      _mu0_jetPtRatio           = (*_recomu_jetPtRatio)[0];
      _mu0_jetCSV               = (*_recomu_jetCSV)[0];
      _mu0_sip3D                = (*_recomu_sip3D)[0];
      _mu0_dxy                  = (*_recomu_dxy)[0];
      _mu0_dz                   = (*_recomu_dz)[0];
      _mu0_segmentCompatibility = (*_recomu_lepMVA_mvaId)[0];
      _mu0_leptonMVA            = (*_recomu_leptonMVA)[0];
      _mu0_mediumID             = (*_recomu_mediumID)[0];
      _mu0_dpt_div_pt           = (*_recomu_rel_error_trackpt)[0];
      _mu0_isfakeablesel        = (*_recomu_isfakeable)[0];      
      _mu0_ismvasel             = (*_recomu_ismvasel)[0];

    }

    if(_n_presel_mu>1){
      _mu1_pt     = (*_recomu_pt)[1];
      _mu1_conept = (*_recomu_conept)[1];
      _mu1_eta    = (*_recomu_eta)[1];
      _mu1_phi    = (*_recomu_phi)[1];
      _mu1_E      = (*_recomu_e)[1];
      _mu1_charge = (*_recomu_charge)[1];
      _mu1_jetNDauChargedMVASel = (*_recomu_jetNDauChargedMVASel)[1];
      _mu1_miniRelIso           = (*_recomu_miniRelIso)[1];
      _mu1_miniIsoCharged       = (*_recomu_miniIsoCharged)[1];
      _mu1_miniIsoNeutral       = (*_recomu_miniIsoNeutral)[1];
      _mu1_jetPtRel             = (*_recomu_jetPtRel)[1];
      _mu1_jetPtRatio           = (*_recomu_jetPtRatio)[1];
      _mu1_jetCSV               = (*_recomu_jetCSV)[1];
      _mu1_sip3D                = (*_recomu_sip3D)[1];
      _mu1_dxy                  = (*_recomu_dxy)[1];
      _mu1_dz                   = (*_recomu_dz)[1];
      _mu1_segmentCompatibility = (*_recomu_lepMVA_mvaId)[1];
      _mu1_leptonMVA            = (*_recomu_leptonMVA)[1];
      _mu1_mediumID             = (*_recomu_mediumID)[1];
      _mu1_dpt_div_pt           = (*_recomu_rel_error_trackpt)[1];
      _mu1_isfakeablesel        = (*_recomu_isfakeable)[1];      
      _mu1_ismvasel             = (*_recomu_ismvasel)[1];
    }


    if(_n_presel_ele>0){
      _ele0_pt     = (*_recoele_pt)[0];
      _ele0_conept = (*_recoele_conept)[0];
      _ele0_eta    = (*_recoele_eta)[0];
      _ele0_phi    = (*_recoele_phi)[0];
      _ele0_E      = (*_recoele_e)[0];
      _ele0_charge = (*_recoele_charge)[0];
      _ele0_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel)[0];
      _ele0_miniRelIso           = (*_recoele_miniRelIso)[0];
      _ele0_miniIsoCharged       = (*_recoele_miniIsoCharged)[0];
      _ele0_miniIsoNeutral       = (*_recoele_miniIsoNeutral)[0];
      _ele0_jetPtRel             = (*_recoele_jetPtRel)[0];
      _ele0_jetPtRatio           = (*_recoele_jetPtRatio)[0];
      _ele0_jetCSV               = (*_recoele_jetCSV)[0];
      _ele0_sip3D                = (*_recoele_sip3D)[0];
      _ele0_dxy                  = (*_recoele_dxy)[0];
      _ele0_dz                   = (*_recoele_dz)[0];
      _ele0_ntMVAeleID           = (*_recoele_lepMVA_mvaId)[0];
      _ele0_leptonMVA            = (*_recoele_leptonMVA)[0];
      _ele0_isChargeConsistent   = (*_recoele_isChargeConsistent)[0];      
      _ele0_passesConversionVeto = (*_recoele_passConversionVeto)[0];
      _ele0_nMissingHits         = (*_recoele_nMissingHits)[0];
      _ele0_isfakeablesel        = (*_recoele_isfakeable)[0];
      _ele0_ismvasel             = (*_recoele_ismvasel)[0];
    }

    if(_n_presel_ele>1){
      _ele1_pt     = (*_recoele_pt)[1];
      _ele1_conept = (*_recoele_conept)[1];
      _ele1_eta    = (*_recoele_eta)[1];
      _ele1_phi    = (*_recoele_phi)[1];
      _ele1_E      = (*_recoele_e)[1];
      _ele1_charge = (*_recoele_charge)[1];
      _ele1_jetNDauChargedMVASel = (*_recoele_jetNDauChargedMVASel)[1];
      _ele1_miniRelIso           = (*_recoele_miniRelIso)[1];
      _ele1_miniIsoCharged       = (*_recoele_miniIsoCharged)[1];
      _ele1_miniIsoNeutral       = (*_recoele_miniIsoNeutral)[1];
      _ele1_jetPtRel             = (*_recoele_jetPtRel)[1];
      _ele1_jetPtRatio           = (*_recoele_jetPtRatio)[1];
      _ele1_jetCSV               = (*_recoele_jetCSV)[1];
      _ele1_sip3D                = (*_recoele_sip3D)[1];
      _ele1_dxy                  = (*_recoele_dxy)[1];
      _ele1_dz                   = (*_recoele_dz)[1];
      _ele1_ntMVAeleID           = (*_recoele_lepMVA_mvaId)[1];
      _ele1_leptonMVA            = (*_recoele_leptonMVA)[1];
      _ele1_isChargeConsistent   = (*_recoele_isChargeConsistent)[1];      
      _ele1_passesConversionVeto = (*_recoele_passConversionVeto)[1];
      _ele1_nMissingHits         = (*_recoele_nMissingHits)[1];
      _ele1_isfakeablesel        = (*_recoele_isfakeable)[1];
      _ele1_ismvasel             = (*_recoele_ismvasel)[1];
    }


    if(_n_presel_tau>0){
      _tau0_pt     = (*_recotauh_pt)[0];
      _tau0_eta    = (*_recotauh_eta)[0];
      _tau0_phi    = (*_recotauh_phi)[0];
      _tau0_E      = (*_recotauh_e)[0];
      _tau0_charge = (*_recotauh_charge)[0]; 
      _tau0_dxy    = (*_recotauh_dxy)[0]; 
      _tau0_dz     = (*_recotauh_dz)[0]; 
      _tau0_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[0];
      _tau0_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[0];
      _tau0_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[0];
      _tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[0];
      _tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[0];
      _tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0];
      _tau0_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[0];
      _tau0_againstMuonTight3          = (*_recotauh_againstMuonTight3)[0];
      _tau0_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[0];
      _tau0_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[0];
      _tau0_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[0];
      _tau0_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[0];
      _tau0_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[0];

    }

    if(_n_presel_tau>1){
      _tau1_pt     = (*_recotauh_pt)[1];
      _tau1_eta    = (*_recotauh_eta)[1];
      _tau1_phi    = (*_recotauh_phi)[1];
      _tau1_E      = (*_recotauh_e)[1];
      _tau1_charge = (*_recotauh_charge)[1];
      _tau1_dxy    = (*_recotauh_dxy)[1]; 
      _tau1_dz     = (*_recotauh_dz)[1];     
      _tau1_decayModeFindingOldDMs                           = (*_recotauh_decayModeFindingOldDMs)[1];
      _tau1_decayModeFindingNewDMs                           = (*_recotauh_decayModeFindingNewDMs)[1];
      _tau1_byCombinedIsolationDeltaBetaCorr3Hits            = (*_recotauh_iso)[1];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits      = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3Hits       = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits)[1];
      _tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03  = (*_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03   = (*_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03)[1];
      _tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT          = (*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT         = (*_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[1];
      _tau1_againstMuonLoose3          = (*_recotauh_againstMuonLoose3)[1];
      _tau1_againstMuonTight3          = (*_recotauh_againstMuonTight3)[1];
      _tau1_againstElectronVLooseMVA6  = (*_recotauh_againstElectronVLooseMVA6)[1];
      _tau1_againstElectronLooseMVA6   = (*_recotauh_againstElectronLooseMVA6)[1];
      _tau1_againstElectronMediumMVA6  = (*_recotauh_againstElectronMediumMVA6)[1];
      _tau1_againstElectronTightMVA6   = (*_recotauh_againstElectronTightMVA6)[1];
      _tau1_againstElectronVTightMVA6  = (*_recotauh_againstElectronVTightMVA6)[1];

    }
    
    if(_n_presel_jet>0){

      _jet0_pt   = (*_recoPFJet_pt)[0];
      _jet0_eta  = (*_recoPFJet_eta)[0];
      _jet0_phi  = (*_recoPFJet_phi)[0];
      _jet0_E    = (*_recoPFJet_e)[0];
      _jet0_CSV  = (*_recoPFJet_CSVscore)[0];

    }

    if(_n_presel_jet>1){

      _jet1_pt   = (*_recoPFJet_pt)[1];
      _jet1_eta  = (*_recoPFJet_eta)[1];
      _jet1_phi  = (*_recoPFJet_phi)[1];
      _jet1_E    = (*_recoPFJet_e)[1];
      _jet1_CSV  = (*_recoPFJet_CSVscore)[1];

    }

    if(_n_presel_jet>2){

      _jet2_pt   = (*_recoPFJet_pt)[2];
      _jet2_eta  = (*_recoPFJet_eta)[2];
      _jet2_phi  = (*_recoPFJet_phi)[2];
      _jet2_E    = (*_recoPFJet_e)[2];
      _jet2_CSV  = (*_recoPFJet_CSVscore)[2];

    }
  
    if(_n_presel_jet>3){

      _jet3_pt   = (*_recoPFJet_pt)[3];
      _jet3_eta  = (*_recoPFJet_eta)[3];
      _jet3_phi  = (*_recoPFJet_phi)[3];
      _jet3_E    = (*_recoPFJet_e)[3];
      _jet3_CSV  = (*_recoPFJet_CSVscore)[3];

    }


    _Integral_ttbar = _Integral_ttbar_DL_fakelep_tlep + _Integral_ttbar_DL_fakelep_ttau;

    if(_integration_type==0)
      _MEM_LR = _Integral_ttH/(_Integral_ttH+1e-18*(_Integral_ttbar_DL_fakelep_tlep+_Integral_ttbar_DL_fakelep_ttau)+1e-1*_Integral_ttZ+2e-1*_Integral_ttZ_Zll);
    else if(_integration_type==1)
      _MEM_LR = _Integral_ttH/(_Integral_ttH+5e-15*(_Integral_ttbar_DL_fakelep_tlep+_Integral_ttbar_DL_fakelep_ttau)+5e-2*_Integral_ttZ+5e-1*_Integral_ttZ_Zll);
    

    bool medium_tau = false;
    if(_n_presel_tau>0)
      medium_tau = (*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0];

    /*_tauSF_weight = 1;
    if(_category==20 || _category==50)
      _tauSF_weight = (1-0.1*(*_recotauh_sel_isGenMatched)[0]) * (1-0.1*(*_recotauh_sel_isGenMatched)[1]);
    else if(_category==11 || _category==41 || _category==-11 || _category==16 || _category==46)
    _tauSF_weight = (1-0.1*(*_recotauh_sel_isGenMatched)[0]);*/
    

    if(_category==11){
      if(((*_recolep_sel_charge)[0]+(*_recotauh_sel_charge)[0])==0)
	tree_new_2lSS_tau->Fill();
    }
    /*else if(_category==41 && medium_tau){
      if(((*_recolep_sel_charge)[0]+(*_recotauh_sel_charge)[0])==0)
	tree_new_2lSS_lepMVA_CR_tau->Fill();
    }
    else if(_category==-11){
      if( (abs((*_recolep_sel_pdg)[0])==11 && (*_recolep_sel_charge)[0]*(*_recotauh_sel_charge)[0]>0) || (abs((*_recolep_sel_pdg)[1])==11 && (*_recolep_sel_charge)[1]*(*_recotauh_sel_charge)[0]>0)   )
	tree_new_2lOS_CR_tau->Fill();
	}*/

  }
  
  }
  
  for(unsigned int i=0;i<tree_new.size();i++)
    tree_new[i]->Write();
  f_new->Close();


  return;

}


