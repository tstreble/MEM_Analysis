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


bool pT_comparison_pairs(pair<int,TLorentzVector> pair1, pair<int,TLorentzVector> pair2){

  return (pair1.second).Pt()>(pair2.second).Pt();

}


bool CSV_comparison_pairs(pair<int,float> pair1, pair<int,float> pair2){

  return pair1.second>pair2.second;

}



void convert_tree(TString sample){

  TString dir_in;
  TString dir_out;
  TString file;    

  if(sample=="VBF"){
    file="ntuple_VBF_dRveto_gen.root";
    dir_in="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/";
    dir_out="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/";
  }


  vector<TString> list;
  list.push_back(dir_in+"HTauTauAnalysis.root");
 

  TChain * tree = new TChain("HTauTauTree/HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }
  //tree->Add(list[0]);


  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");


  TTree* tree_new=tree->GetTree()->CloneTree(0);
  //TTree* tree_new=tree->CloneTree(0);

  //New branches
  //int _EventNumber;
  //int _RunNumber;
  //int _lumi;
  //float _MC_weight;

  vector<float> _daughters_pt;
  vector<float> _daughters_eta;
  vector<float> _daughters_phi;

  int _n_recolep;
  vector<int> _recolep_ID;
  vector<int> _recolep_charge;
  vector<float> _recolep_e;
  vector<float> _recolep_px;
  vector<float> _recolep_py;
  vector<float> _recolep_pz;
  vector<float> _recolep_pt;
  vector<float> _recolep_eta;
  vector<float> _recolep_phi;
 
  int _n_recotauh;
  vector<int> _recotauh_charge;
  vector<int> _recotauh_decayMode;
  vector<float> _recotauh_e;
  vector<float> _recotauh_px;
  vector<float> _recotauh_py;
  vector<float> _recotauh_pz;
  vector<float> _recotauh_pt;
  vector<float> _recotauh_eta;
  vector<float> _recotauh_phi;

  int _n_recoPFJet30;
  vector<float> _recoPFJet30_e;
  vector<float> _recoPFJet30_pt;
  vector<float> _recoPFJet30_px;
  vector<float> _recoPFJet30_py;
  vector<float> _recoPFJet30_pz;
  vector<float> _recoPFJet30_eta;
  vector<float> _recoPFJet30_phi;
  vector<float> _recoPFJet30_CSVscore;
  vector<int> _recoPFJet30_Flavour; 

  float _PFMET;
  float _PFMET_phi;
  float _PFMETx;
  float _PFMETy;

  float _PFMET_cov00;
  float _PFMET_cov01;
  float _PFMET_cov10;
  float _PFMET_cov11;


  //Gen information

  int _n_genlep;
  int _n_genlep10;
  int _n_genlep20;
  int _n_genlep_fromTau;
  vector<int> _genlep_pdg;
  vector<int> _genlep_charge;
  vector<float> _genlep_e;
  vector<float> _genlep_px;
  vector<float> _genlep_py;
  vector<float> _genlep_pz;
  vector<float> _genlep_pt;
  vector<float> _genlep_eta;
  vector<float> _genlep_phi;
  vector<int> _genlep_flags;  
  vector<int> _genlep_TauMothInd; //-1 if not from tau

  int _n_gentauh;
  int _n_gentauh10;
  int _n_gentauh30;
  int _n_gentauh30_eta21;
  int _n_gentauh_fromTau;
  vector<int> _gentauh_charge;
  vector<float> _gentauh_e;
  vector<float> _gentauh_px;
  vector<float> _gentauh_py;
  vector<float> _gentauh_pz;
  vector<float> _gentauh_pt;
  vector<float> _gentauh_eta;
  vector<float> _gentauh_phi;
  vector<int> _gentauh_flags;  
  vector<int> _gentauh_TauMothInd;


  int _n_gentau;
  int _n_gentau_fromH;
  vector<int> _gentau_decayMode; //0 muon, 1 electron, 2 had
  vector<int> _gentau_charge;
  vector<float> _gentau_e;
  vector<float> _gentau_px;
  vector<float> _gentau_py;
  vector<float> _gentau_pz;
  vector<float> _gentau_pt;
  vector<float> _gentau_eta;
  vector<float> _gentau_phi;
  vector<int> _gentau_flags;  
  vector<int> _gentau_HMothInd;

  int _n_genH;
  vector<int> _genH_decayMode; //0 mu+tauh, 1 e+tauh, 2 tauh+tauh, 3 mu+mu, 4 e+e, 5 e+mu
  vector<float> _genH_e;
  vector<float> _genH_px;
  vector<float> _genH_py;
  vector<float> _genH_pz;
  vector<float> _genH_pt;
  vector<float> _genH_eta;
  vector<float> _genH_phi;
  vector<int> _genH_flags;  


  int _n_genb;
  int _n_genb10;
  vector<int> _genb_pdg;
  vector<float> _genb_e;
  vector<float> _genb_px;
  vector<float> _genb_py;
  vector<float> _genb_pz;
  vector<float> _genb_pt;
  vector<float> _genb_eta;
  vector<float> _genb_phi;
  vector<int> _genb_flags;  


  int _n_genq;
  int _n_genq10;
  vector<int> _genq_pdg;
  vector<float> _genq_e;
  vector<float> _genq_px;
  vector<float> _genq_py;
  vector<float> _genq_pz;
  vector<float> _genq_pt;
  vector<float> _genq_eta;
  vector<float> _genq_phi;
  vector<int> _genq_flags;  

  int _n_gennu;
  int _n_gennu_fromTau;
  vector<int> _gennu_pdg;
  vector<float> _gennu_e;
  vector<float> _gennu_px;
  vector<float> _gennu_py;
  vector<float> _gennu_pz;
  vector<float> _gennu_pt;
  vector<float> _gennu_eta;
  vector<float> _gennu_phi;
  vector<int> _gennu_flags;  
  vector<int> _gennu_TauMothInd; //-1 if not from tau

  tree_new->Branch("daughters_pt",&_daughters_pt);
  tree_new->Branch("daughters_eta",&_daughters_eta);
  tree_new->Branch("daughters_phi",&_daughters_phi);

  tree_new->Branch("n_recolep",&_n_recolep,"n_recolep/I");
  tree_new->Branch("recolep_ID",&_recolep_ID);
  tree_new->Branch("recolep_charge",&_recolep_charge);
  tree_new->Branch("recolep_e",&_recolep_e);
  tree_new->Branch("recolep_px",&_recolep_px);
  tree_new->Branch("recolep_py",&_recolep_py);
  tree_new->Branch("recolep_pz",&_recolep_pz);
  tree_new->Branch("recolep_pt",&_recolep_pt);
  tree_new->Branch("recolep_eta",&_recolep_eta);
  tree_new->Branch("recolep_phi",&_recolep_phi);

  tree_new->Branch("n_recotauh",&_n_recotauh,"n_recotauh/I");
  tree_new->Branch("recotauh_decayMode",&_recotauh_decayMode);
  tree_new->Branch("recotauh_charge",&_recotauh_charge);
  tree_new->Branch("recotauh_e",&_recotauh_e);
  tree_new->Branch("recotauh_px",&_recotauh_px);
  tree_new->Branch("recotauh_py",&_recotauh_py);
  tree_new->Branch("recotauh_pz",&_recotauh_pz);
  tree_new->Branch("recotauh_pt",&_recotauh_pt);
  tree_new->Branch("recotauh_eta",&_recotauh_eta);
  tree_new->Branch("recotauh_phi",&_recotauh_phi);

  tree_new->Branch("n_recoPFJet30",&_n_recoPFJet30,"n_recoPFJet30/I");
  tree_new->Branch("recoPFJet30_e",&_recoPFJet30_e);
  tree_new->Branch("recoPFJet30_pt",&_recoPFJet30_pt);
  tree_new->Branch("recoPFJet30_px",&_recoPFJet30_px);
  tree_new->Branch("recoPFJet30_py",&_recoPFJet30_py);
  tree_new->Branch("recoPFJet30_pz",&_recoPFJet30_pz);
  tree_new->Branch("recoPFJet30_eta",&_recoPFJet30_eta);
  tree_new->Branch("recoPFJet30_phi",&_recoPFJet30_phi);
  tree_new->Branch("recoPFJet30_CSVscore",&_recoPFJet30_CSVscore);
  tree_new->Branch("recoPFJet30_Flavour",&_recoPFJet30_Flavour);

  tree_new->Branch("PFMETx",&_PFMETx,"PFMETx/F");
  tree_new->Branch("PFMETy",&_PFMETy,"PFMETy/F");
  tree_new->Branch("PFMET",&_PFMET,"PFMET/F");
  tree_new->Branch("PFMET_phi",&_PFMET_phi,"PFMET_phi/F");

  tree_new->Branch("PFMET_cov00",&_PFMET_cov00,"PFMET_cov00/F");
  tree_new->Branch("PFMET_cov01",&_PFMET_cov01,"PFMET_cov01/F");
  tree_new->Branch("PFMET_cov10",&_PFMET_cov10,"PFMET_cov10/F");
  tree_new->Branch("PFMET_cov11",&_PFMET_cov11,"PFMET_cov11/F");

  tree_new->Branch("n_genlep",&_n_genlep,"n_genlep/I");
  tree_new->Branch("n_genlep10",&_n_genlep10,"n_genlep10/I");
  tree_new->Branch("n_genlep20",&_n_genlep20,"n_genlep20/I");
  tree_new->Branch("n_genlep_fromTau",&_n_genlep_fromTau,"n_genlep_fromTau/I");
  tree_new->Branch("genlep_pdg",&_genlep_pdg);
  tree_new->Branch("genlep_charge",&_genlep_charge);
  tree_new->Branch("genlep_e",&_genlep_e);
  tree_new->Branch("genlep_px",&_genlep_px);
  tree_new->Branch("genlep_py",&_genlep_py);
  tree_new->Branch("genlep_pz",&_genlep_pz);
  tree_new->Branch("genlep_pt",&_genlep_pt);
  tree_new->Branch("genlep_eta",&_genlep_eta);
  tree_new->Branch("genlep_phi",&_genlep_phi);
  tree_new->Branch("genlep_flags",&_genlep_flags);
  tree_new->Branch("genlep_TauMothInd",&_genlep_TauMothInd);


  tree_new->Branch("n_gentauh",&_n_gentauh,"n_gentauh/I");
  tree_new->Branch("n_gentauh10",&_n_gentauh10,"n_gentauh10/I");
  tree_new->Branch("n_gentauh30",&_n_gentauh30,"n_gentauh30/I");
  tree_new->Branch("n_gentauh30_eta21",&_n_gentauh30_eta21,"n_gentauh30_eta21/I");
  tree_new->Branch("n_gentauh_fromTau",&_n_gentauh_fromTau,"n_gentauh_fromTau/I");
  tree_new->Branch("gentauh_charge",&_gentauh_charge);
  tree_new->Branch("gentauh_e",&_gentauh_e);
  tree_new->Branch("gentauh_px",&_gentauh_px);
  tree_new->Branch("gentauh_py",&_gentauh_py);
  tree_new->Branch("gentauh_pz",&_gentauh_pz);
  tree_new->Branch("gentauh_pt",&_gentauh_pt);
  tree_new->Branch("gentauh_eta",&_gentauh_eta);
  tree_new->Branch("gentauh_phi",&_gentauh_phi);
  tree_new->Branch("gentauh_flags",&_gentauh_flags);
  tree_new->Branch("gentauh_TauMothInd",&_gentauh_TauMothInd);

  tree_new->Branch("n_gentau",&_n_gentau,"n_gentau/I");
  tree_new->Branch("n_gentau_fromH",&_n_gentau_fromH,"n_gentau_fromH/I");
  tree_new->Branch("gentau_decayMode",&_gentau_decayMode);
  tree_new->Branch("gentau_charge",&_gentau_charge);
  tree_new->Branch("gentau_e",&_gentau_e);
  tree_new->Branch("gentau_px",&_gentau_px);
  tree_new->Branch("gentau_py",&_gentau_py);
  tree_new->Branch("gentau_pz",&_gentau_pz);
  tree_new->Branch("gentau_pt",&_gentau_pt);
  tree_new->Branch("gentau_eta",&_gentau_eta);
  tree_new->Branch("gentau_phi",&_gentau_phi);
  tree_new->Branch("gentau_flags",&_gentau_flags);
  tree_new->Branch("gentau_HMothInd",&_gentau_HMothInd);

  tree_new->Branch("n_genH",&_n_genH,"n_genH/I");
  tree_new->Branch("genH_decayMode",&_genH_decayMode);
  tree_new->Branch("genH_e",&_genH_e);
  tree_new->Branch("genH_px",&_genH_px);
  tree_new->Branch("genH_py",&_genH_py);
  tree_new->Branch("genH_pz",&_genH_pz);
  tree_new->Branch("genH_pt",&_genH_pt);
  tree_new->Branch("genH_eta",&_genH_eta);
  tree_new->Branch("genH_phi",&_genH_phi);
  tree_new->Branch("genH_flags",&_genH_flags);


  tree_new->Branch("n_genb",&_n_genb,"n_genb/I");
  tree_new->Branch("n_genb10",&_n_genb10,"n_genb10/I");
  tree_new->Branch("genb_pdg",&_genb_pdg);
  tree_new->Branch("genb_e",&_genb_e);
  tree_new->Branch("genb_px",&_genb_px);
  tree_new->Branch("genb_py",&_genb_py);
  tree_new->Branch("genb_pz",&_genb_pz);
  tree_new->Branch("genb_pt",&_genb_pt);
  tree_new->Branch("genb_eta",&_genb_eta);
  tree_new->Branch("genb_phi",&_genb_phi);
  tree_new->Branch("genb_flags",&_genb_flags);

  tree_new->Branch("n_genq",&_n_genq,"n_genq/I");
  tree_new->Branch("n_genq10",&_n_genq10,"n_genq10/I");
  tree_new->Branch("genq_pdg",&_genq_pdg);
  tree_new->Branch("genq_e",&_genq_e);
  tree_new->Branch("genq_px",&_genq_px);
  tree_new->Branch("genq_py",&_genq_py);
  tree_new->Branch("genq_pz",&_genq_pz);
  tree_new->Branch("genq_pt",&_genq_pt);
  tree_new->Branch("genq_eta",&_genq_eta);
  tree_new->Branch("genq_phi",&_genq_phi);
  tree_new->Branch("genq_flags",&_genq_flags);

  tree_new->Branch("n_gennu",&_n_gennu,"n_gennu/I");
  tree_new->Branch("n_gennu_fromTau",&_n_gennu_fromTau,"n_gennu_fromTau/I");
  tree_new->Branch("gennu_pdg",&_gennu_pdg);
  tree_new->Branch("gennu_e",&_gennu_e);
  tree_new->Branch("gennu_px",&_gennu_px);
  tree_new->Branch("gennu_py",&_gennu_py);
  tree_new->Branch("gennu_pz",&_gennu_pz);
  tree_new->Branch("gennu_pt",&_gennu_pt);
  tree_new->Branch("gennu_eta",&_gennu_eta);
  tree_new->Branch("gennu_phi",&_gennu_phi);
  tree_new->Branch("gennu_flags",&_gennu_flags);
  tree_new->Branch("gennu_TauMothInd",&_gennu_TauMothInd);

  //Old branches used
  vector<float> *_jets_e;
  vector<float> *_jets_px;
  vector<float> *_jets_py;
  vector<float> *_jets_pz;
  vector<int> *_jets_Flavour;
  vector<float> *_bCSVscore;

  vector<float> *_daughters_e;
  vector<float> *_daughters_px;
  vector<float> *_daughters_py;
  vector<float> *_daughters_pz;
  vector<int> *_PDGIdDaughters;
  vector<int> *_decayMode;
  vector<float> *_combreliso;
  vector<float> *_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits;
  vector<int> *_daughters_decayModeFindingOldDMs;
  vector<int> *_daughters_againstMuonTight3;
  vector<int> *_daughters_againstElectronVLooseMVA5;

  vector<float> *_METx_vect;
  vector<float> *_METy_vect;

  vector<float> *_MET_cov00_vect;
  vector<float> *_MET_cov01_vect;
  vector<float> *_MET_cov10_vect;
  vector<float> *_MET_cov11_vect;

  vector<float> *_genpart_px;
  vector<float> *_genpart_py;
  vector<float> *_genpart_pz;
  vector<float> *_genpart_e;
  vector<int> *_genpart_pdg;
  vector<int> *_genpart_HMothInd;
  vector<int> *_genpart_TauMothInd;
  vector<int> *_genpart_HZDecayMode;
  vector<int> *_genpart_TauGenDecayMode;
  vector<int> *_genpart_flags;

  tree->SetBranchAddress("jets_px",&_jets_px);
  tree->SetBranchAddress("jets_py",&_jets_py);
  tree->SetBranchAddress("jets_pz",&_jets_pz);
  tree->SetBranchAddress("jets_e",&_jets_e);
  tree->SetBranchAddress("jets_Flavour",&_jets_Flavour);
  tree->SetBranchAddress("bCSVscore",&_bCSVscore);

  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree->SetBranchAddress("decayMode",&_decayMode);
  tree->SetBranchAddress("combreliso",&_combreliso);
  tree->SetBranchAddress("daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits",&_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits);
  tree->SetBranchAddress("daughters_decayModeFindingOldDMs",&_daughters_decayModeFindingOldDMs);
  tree->SetBranchAddress("daughters_againstMuonTight3",&_daughters_againstMuonTight3);
  tree->SetBranchAddress("daughters_againstElectronVLooseMVA5",&_daughters_againstElectronVLooseMVA5);

  tree->SetBranchAddress("METx",&_METx_vect);
  tree->SetBranchAddress("METy",&_METy_vect);
  tree->SetBranchAddress("MET_cov00",&_MET_cov00_vect);
  tree->SetBranchAddress("MET_cov01",&_MET_cov01_vect);
  tree->SetBranchAddress("MET_cov10",&_MET_cov10_vect);
  tree->SetBranchAddress("MET_cov11",&_MET_cov11_vect);

  tree->SetBranchAddress("genpart_px",&_genpart_px);
  tree->SetBranchAddress("genpart_py",&_genpart_py);
  tree->SetBranchAddress("genpart_pz",&_genpart_pz);
  tree->SetBranchAddress("genpart_e",&_genpart_e);
  tree->SetBranchAddress("genpart_pdg",&_genpart_pdg);
  tree->SetBranchAddress("genpart_HMothInd",&_genpart_HMothInd);
  tree->SetBranchAddress("genpart_TauMothInd",&_genpart_TauMothInd);
  tree->SetBranchAddress("genpart_HZDecayMode",&_genpart_HZDecayMode);
  tree->SetBranchAddress("genpart_TauGenDecayMode",&_genpart_TauGenDecayMode);
  tree->SetBranchAddress("genpart_flags",&_genpart_flags);
  

  cout<<"nentries="<<nentries<<endl;

  //nentries=15;
  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _daughters_pt.clear();
    _daughters_eta.clear();
    _daughters_phi.clear();

    _n_recolep = 0;
    _recolep_ID.clear();
    _recolep_charge.clear();
    _recolep_e.clear();
    _recolep_px.clear();
    _recolep_py.clear();
    _recolep_pz.clear();
    _recolep_pt.clear();
    _recolep_eta.clear();
    _recolep_phi.clear();
 
    _n_recotauh = 0;
    _recotauh_charge.clear();
    _recotauh_decayMode.clear();
    _recotauh_e.clear();
    _recotauh_px.clear();
    _recotauh_py.clear();
    _recotauh_pz.clear();
    _recotauh_pt.clear();
    _recotauh_eta.clear();
    _recotauh_phi.clear();

    _n_recoPFJet30 = 0;
    _recoPFJet30_e.clear();
    _recoPFJet30_pt.clear();
    _recoPFJet30_px.clear();
    _recoPFJet30_py.clear();
    _recoPFJet30_pz.clear();
    _recoPFJet30_eta.clear();
    _recoPFJet30_phi.clear();
    _recoPFJet30_CSVscore.clear();    
    _recoPFJet30_Flavour.clear(); 

    _PFMETx = 0;
    _PFMETy = 0;
    _PFMET = 0;
    _PFMET_phi = 0;

    _PFMET_cov00 = 0;
    _PFMET_cov01 = 0;
    _PFMET_cov10 = 0;
    _PFMET_cov11 = 0;

    _n_genlep = 0;
    _n_genlep10 = 0;
    _n_genlep20 = 0;
    _n_genlep_fromTau = 0;
    _genlep_pdg.clear();
    _genlep_charge.clear();
    _genlep_e.clear();
    _genlep_px.clear();
    _genlep_py.clear();
    _genlep_pz.clear();
    _genlep_pt.clear();
    _genlep_eta.clear();
    _genlep_phi.clear();
    _genlep_flags.clear();
    _genlep_TauMothInd.clear();

    _n_gentauh = 0;
    _n_gentauh10 = 0;
    _n_gentauh30 = 0;
    _n_gentauh30_eta21 = 0;
    _n_gentauh_fromTau = 0;
    _gentauh_charge.clear();
    _gentauh_e.clear();
    _gentauh_px.clear();
    _gentauh_py.clear();
    _gentauh_pz.clear();
    _gentauh_pt.clear();
    _gentauh_eta.clear();
    _gentauh_phi.clear();
    _gentauh_flags.clear();
    _gentauh_TauMothInd.clear();

    _n_gentau = 0;
    _n_gentau_fromH = 0;
    _gentau_decayMode.clear();
    _gentau_charge.clear();
    _gentau_e.clear();
    _gentau_px.clear();
    _gentau_py.clear();
    _gentau_pz.clear();
    _gentau_pt.clear();
    _gentau_eta.clear();
    _gentau_phi.clear();
    _gentau_flags.clear();
    _gentau_HMothInd.clear();

    _n_genH = 0;
    _genH_decayMode.clear();
    _genH_e.clear();
    _genH_px.clear();
    _genH_py.clear();
    _genH_pz.clear();
    _genH_pt.clear();
    _genH_eta.clear();
    _genH_phi.clear();
    _genH_flags.clear();


    _n_genb = 0;
    _n_genb10 = 0;
    _genb_pdg.clear();
    _genb_e.clear();
    _genb_px.clear();
    _genb_py.clear();
    _genb_pz.clear();
    _genb_pt.clear();
    _genb_eta.clear();
    _genb_phi.clear();
    _genb_flags.clear();
 

    _n_genq = 0;
    _n_genq10 = 0;
    _genq_pdg.clear();
    _genq_e.clear();
    _genq_px.clear();
    _genq_py.clear();
    _genq_pz.clear();
    _genq_pt.clear();
    _genq_eta.clear();
    _genq_phi.clear();
    _genq_flags.clear();

    _n_gennu = 0;
    _n_gennu_fromTau = 0;
    _gennu_pdg.clear();
    _gennu_e.clear();
    _gennu_px.clear();
    _gennu_py.clear();
    _gennu_pz.clear();
    _gennu_pt.clear();
    _gennu_eta.clear();
    _gennu_phi.clear();
    _gennu_flags.clear();
    _gennu_TauMothInd.clear();

    _jets_e = 0;
    _jets_px = 0;
    _jets_py = 0;
    _jets_pz = 0;
    _jets_Flavour = 0;
    _bCSVscore = 0;

    _daughters_e = 0;
    _daughters_px = 0;
    _daughters_py = 0;
    _daughters_pz = 0;
    _PDGIdDaughters = 0;
    _decayMode = 0;
    _combreliso = 0;
    _daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
    _daughters_decayModeFindingOldDMs = 0;
    _daughters_againstMuonTight3 = 0;
    _daughters_againstElectronVLooseMVA5 = 0;

    _METx_vect = 0;
    _METy_vect = 0;
    _MET_cov00_vect = 0;
    _MET_cov01_vect = 0;
    _MET_cov10_vect = 0;
    _MET_cov11_vect = 0;

    _genpart_px = 0;
    _genpart_py = 0;
    _genpart_pz = 0;
    _genpart_e = 0;
    _genpart_pdg = 0;
    _genpart_HMothInd = 0;
    _genpart_TauMothInd = 0;
    _genpart_HZDecayMode = 0;
    _genpart_TauGenDecayMode = 0;
    _genpart_flags = 0;

    tree->GetEntry(i);

    ///Leptons   
    
    vector< pair<int,TLorentzVector> > reco_leptons;
   	
    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){




      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );
      
      pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
     
      _daughters_pt.push_back(daughter.Pt());
      _daughters_eta.push_back(daughter.Eta());
      _daughters_phi.push_back(daughter.Phi());      


      if( fabs(PDGId)==11 || fabs(PDGId)==13){

	float rel_iso=(*_combreliso)[i_daughter];
	if(daughter.Pt()>20 && fabs(daughter.Eta())<2.1 &&  rel_iso<0.1)
	  reco_leptons.push_back(daughter_pair);

      }

    }

    sort(reco_leptons.begin(), reco_leptons.end(), pT_comparison_pairs);
       
    _n_recolep = reco_leptons.size();

    for(unsigned int i_lepton=0; i_lepton<reco_leptons.size(); i_lepton++){
      
      int i_daughter=reco_leptons[i_lepton].first;
      TLorentzVector lepton=reco_leptons[i_lepton].second;

      _recolep_ID.push_back( (*_PDGIdDaughters)[i_daughter] );
      _recolep_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recolep_e.push_back( lepton.E() );
      _recolep_px.push_back( lepton.Px() );
      _recolep_py.push_back( lepton.Py() );
      _recolep_pz.push_back( lepton.Pz() );
      _recolep_pt.push_back( lepton.Pt() );
      _recolep_eta.push_back( lepton.Eta() );
      _recolep_phi.push_back( lepton.Phi() );

    }



    ///Taus   
    
    vector< pair<int,TLorentzVector> > reco_taus;
   	
    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){
      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );
      
      pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
     
      float iso=(*_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits)[i_daughter];
      int decayModeFinding=(*_daughters_decayModeFindingOldDMs)[i_daughter];
      int antiMu=(*_daughters_againstMuonTight3)[i_daughter];
      int antiE=(*_daughters_againstElectronVLooseMVA5)[i_daughter];

      if(fabs(PDGId)==15 && daughter.Pt()>30 && fabs(daughter.Eta())<2.1 && iso<1.5 && decayModeFinding>0.5 && antiMu>0 && antiE>0){
	
	bool dR_veto=false;
	
	for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){

	  TLorentzVector lep=reco_leptons[i_lep].second;
	  float dR_lep_tau=lep.DeltaR(daughter);
	  if(dR_lep_tau<0.1){
	    dR_veto=true;
	    break;
	  }
	}

	if(dR_veto)
	  continue;

	reco_taus.push_back(daughter_pair);
	

      }

    }


    sort(reco_taus.begin(), reco_taus.end(), pT_comparison_pairs);    


    _n_recotauh = reco_taus.size();

    for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){
      
      int i_daughter=reco_taus[i_tauh].first;
      TLorentzVector tauh=reco_taus[i_tauh].second;

      _recotauh_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recotauh_decayMode.push_back( (*_decayMode)[i_daughter] );
      _recotauh_e.push_back( tauh.E() );
      _recotauh_px.push_back( tauh.Px() );
      _recotauh_py.push_back( tauh.Py() );
      _recotauh_pz.push_back( tauh.Pz() );
      _recotauh_pt.push_back( tauh.Pt() );
      _recotauh_eta.push_back( tauh.Eta() );
      _recotauh_phi.push_back( tauh.Phi() );

    }

    
    ///Jets
    
    vector< pair<int,TLorentzVector> > reco_jets;
    vector< pair<int,float> > i_jet_CSV_pairs;

    for(unsigned int i_jet=0; i_jet<(*_jets_e).size(); i_jet++){

      TLorentzVector jet ( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );

      pair<int,TLorentzVector> jet_pair = make_pair(i_jet,jet);

      if(jet.Pt()>30 && fabs(jet.Eta())<2.5){

	bool dR_veto=false;

	for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){

	  TLorentzVector lep=reco_leptons[i_lep].second;
	  float dR_lep_jet=lep.DeltaR(jet);
	  if(dR_lep_jet<0.4){
	    dR_veto=true;
	    break;
	  }
	
	}

	for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){

	  TLorentzVector tauh=reco_taus[i_tauh].second;
	  float dR_tauh_jet=tauh.DeltaR(jet);
	  if(dR_tauh_jet<0.4){
	    dR_veto=true;
	    break;
	  }
	
	}

	if(dR_veto)
	  continue;

      }

    }


    sort(reco_jets.begin(), reco_jets.end(), pT_comparison_pairs);    

    _n_recoPFJet30 = reco_jets.size();
    

    for(unsigned int i_PFJet30=0; i_PFJet30<reco_jets.size(); i_PFJet30++){

      int i_jet = reco_jets[i_PFJet30].first;
      TLorentzVector jet =  reco_jets[i_PFJet30].second;
      
      _recoPFJet30_e.push_back( jet.E() );
      _recoPFJet30_pt.push_back( jet.Pt() );
      _recoPFJet30_px.push_back( jet.Px() );
      _recoPFJet30_py.push_back( jet.Py() );
      _recoPFJet30_pz.push_back( jet.Pz() );
      _recoPFJet30_eta.push_back( jet.Eta() );
      _recoPFJet30_phi.push_back( jet.Phi() );
      _recoPFJet30_CSVscore.push_back(  (*_bCSVscore)[i_jet] );
      _recoPFJet30_Flavour.push_back(  (*_jets_Flavour)[i_jet] );

    }


    

    ///MET

   
    if( (*_MET_cov00_vect).size() > 0 ){

      _PFMETx = (*_METx_vect)[0];
      _PFMETy = (*_METy_vect)[0];

      _PFMET_cov00 = (*_MET_cov00_vect)[0];
      _PFMET_cov01 = (*_MET_cov01_vect)[0];
      _PFMET_cov10 = (*_MET_cov10_vect)[0];
      _PFMET_cov11 = (*_MET_cov11_vect)[0];
      
      for(unsigned int i_MET=0;i_MET<(*_MET_cov00_vect).size();i_MET++){
	
	if( (*_METx_vect)[i_MET]!=_PFMETx || (*_METy_vect)[i_MET]!=_PFMETy || (*_MET_cov00_vect)[i_MET]!=_PFMET_cov00 || (*_MET_cov01_vect)[i_MET]!=_PFMET_cov01 || (*_MET_cov10_vect)[i_MET]!=_PFMET_cov10 || (*_MET_cov11_vect)[i_MET]!=_PFMET_cov11 ){
	  cout<<"Problem with MET"<<endl;
	  return;
	}

      }
      
    }

    TVector3 PFMET_tv3;
    PFMET_tv3.SetXYZ(_PFMETx,_PFMETy,0);
    _PFMET = PFMET_tv3.Pt();    
    _PFMET_phi = PFMET_tv3.Phi();


    // Gen information

    vector<int> genlep_index;
    vector<int> gentauh_index;
    vector<int> gentau_index;
    vector<int> genH_index;
    vector<int> genb_index;
    vector<int> genq_index;
    vector<int> gennu_index;


    for(unsigned int i_gen=0; i_gen<(*_genpart_e).size(); i_gen++){

      TLorentzVector genpart_tlv( (*_genpart_px)[i_gen], (*_genpart_py)[i_gen], (*_genpart_pz)[i_gen], (*_genpart_e)[i_gen]);

      int TauMothInd = (*_genpart_TauMothInd)[i_gen];
      int HMothInd = (*_genpart_HMothInd)[i_gen];
      int flags = (*_genpart_flags)[i_gen];


      if( abs( (*_genpart_pdg)[i_gen] )==11 || abs( (*_genpart_pdg)[i_gen] )==13){

	_genlep_pdg.push_back( (*_genpart_pdg)[i_gen] );
	_genlep_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
	
	_genlep_e.push_back( genpart_tlv.E() );
	_genlep_px.push_back( genpart_tlv.Px() );
	_genlep_py.push_back( genpart_tlv.Py() );
	_genlep_pz.push_back( genpart_tlv.Pz() );
	_genlep_pt.push_back( genpart_tlv.Pt() );
	_genlep_eta.push_back( genpart_tlv.Eta() );
	_genlep_phi.push_back( genpart_tlv.Phi() );
	_genlep_flags.push_back(flags);

	if( TauMothInd>-1 )
	  _n_genlep_fromTau++;
	if( genpart_tlv.Pt()>10)
	  _n_genlep10++;
	if( genpart_tlv.Pt()>20)
	  _n_genlep20++;

	genlep_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==66615){

	_gentauh_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
	
	_gentauh_e.push_back( genpart_tlv.E() );
	_gentauh_px.push_back( genpart_tlv.Px() );
	_gentauh_py.push_back( genpart_tlv.Py() );
	_gentauh_pz.push_back( genpart_tlv.Pz() );
	_gentauh_pt.push_back( genpart_tlv.Pt() );
	_gentauh_eta.push_back( genpart_tlv.Eta() );
	_gentauh_phi.push_back( genpart_tlv.Phi() );
	_gentauh_flags.push_back(flags);

	if( TauMothInd>-1 )
	  _n_gentauh_fromTau++;
	if( genpart_tlv.Pt()>10)
	  _n_gentauh10++;
	if( genpart_tlv.Pt()>30)
	  _n_gentauh30++;
	if( genpart_tlv.Pt()>30 && abs(genpart_tlv.Eta())<2.1)
	  _n_gentauh30_eta21++;

	gentauh_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==15){

	_gentau_decayMode.push_back( (*_genpart_TauGenDecayMode)[i_gen] );
	_gentau_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );

	_gentau_e.push_back( genpart_tlv.E() );
	_gentau_px.push_back( genpart_tlv.Px() );
	_gentau_py.push_back( genpart_tlv.Py() );
	_gentau_pz.push_back( genpart_tlv.Pz() );
	_gentau_pt.push_back( genpart_tlv.Pt() );
	_gentau_eta.push_back( genpart_tlv.Eta() );
	_gentau_phi.push_back( genpart_tlv.Phi() );
	_gentau_flags.push_back(flags);

	if( HMothInd>-1 )
	  _n_gentau_fromH++;

	gentau_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==25){

	_genH_decayMode.push_back( (*_genpart_HZDecayMode)[i_gen] );

	_genH_e.push_back( genpart_tlv.E() );
	_genH_px.push_back( genpart_tlv.Px() );
	_genH_py.push_back( genpart_tlv.Py() );
	_genH_pz.push_back( genpart_tlv.Pz() );
	_genH_pt.push_back( genpart_tlv.Pt() );
	_genH_eta.push_back( genpart_tlv.Eta() );
	_genH_phi.push_back( genpart_tlv.Phi() );
	_genH_flags.push_back(flags);

	genH_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==5){

	_genb_pdg.push_back( (*_genpart_pdg)[i_gen] );

	_genb_e.push_back( genpart_tlv.E() );
	_genb_px.push_back( genpart_tlv.Px() );
	_genb_py.push_back( genpart_tlv.Py() );
	_genb_pz.push_back( genpart_tlv.Pz() );
	_genb_pt.push_back( genpart_tlv.Pt() );
	_genb_eta.push_back( genpart_tlv.Eta() );
	_genb_phi.push_back( genpart_tlv.Phi() );
	_genb_flags.push_back(flags);

	if( genpart_tlv.Pt()>10)
	  _n_genb10++;

	genb_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )<5){

	_genq_pdg.push_back( (*_genpart_pdg)[i_gen] );

	_genq_e.push_back( genpart_tlv.E() );
	_genq_px.push_back( genpart_tlv.Px() );
	_genq_py.push_back( genpart_tlv.Py() );
	_genq_pz.push_back( genpart_tlv.Pz() );
	_genq_pt.push_back( genpart_tlv.Pt() );
	_genq_eta.push_back( genpart_tlv.Eta() );
	_genq_phi.push_back( genpart_tlv.Phi() );
	_genq_flags.push_back(flags);

	if( genpart_tlv.Pt()>10)
	  _n_genq10++;

	genq_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==12 || abs( (*_genpart_pdg)[i_gen] )==14 || abs( (*_genpart_pdg)[i_gen] )==16){

	_gennu_pdg.push_back( (*_genpart_pdg)[i_gen] );

	_gennu_e.push_back( genpart_tlv.E() );
	_gennu_px.push_back( genpart_tlv.Px() );
	_gennu_py.push_back( genpart_tlv.Py() );
	_gennu_pz.push_back( genpart_tlv.Pz() );
	_gennu_pt.push_back( genpart_tlv.Pt() );
	_gennu_eta.push_back( genpart_tlv.Eta() );
	_gennu_phi.push_back( genpart_tlv.Phi() );
	_gennu_flags.push_back(flags);

	//Only count lep from tau from Higgs
	if( TauMothInd>-1 &&  HMothInd>-1 )
	  _n_gennu_fromTau++;

	gennu_index.push_back(i_gen);


      }


    }

    _n_genlep = _genlep_e.size();
    _n_gentauh = _gentauh_e.size();
    _n_gentau = _gentau_e.size();
    _n_genH = _genH_e.size();
    _n_genb = _genb_e.size();
    _n_genq = _genq_e.size();
    _n_gennu = _gennu_e.size();


    for(int i_lep=0; i_lep<_n_genlep; i_lep++){

      int i_gen = genlep_index[i_lep];
      
      int i_tau_Moth = -1;
      int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
      if( i_gen_TauMoth > -1 ){
	for(int i_tau=0; i_tau<_n_gentau; i_tau++){
	  if( gentau_index[i_tau]==i_gen_TauMoth){
	    i_tau_Moth = i_tau;
	    break;
	  }
	}
      }
      _genlep_TauMothInd.push_back(i_tau_Moth);


    }


    for(int i_tauh=0; i_tauh<_n_gentauh; i_tauh++){

      int i_gen = gentauh_index[i_tauh];
      
      int i_tau_Moth = -1;
      int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
      if( i_gen_TauMoth > -1 ){
	for(int i_tau=0; i_tau<_n_gentau; i_tau++){
	  if( gentau_index[i_tau]==i_gen_TauMoth){
	    i_tau_Moth = i_tau;
	    break;
	  }
	}
      }
      _gentauh_TauMothInd.push_back(i_tau_Moth);


    }

    
    for(int i_tau=0; i_tau<_n_gentau; i_tau++){

      int i_gen = gentau_index[i_tau];     

      int i_H_Moth = -1;
      int i_gen_HMoth = (*_genpart_HMothInd)[i_gen];
      if( i_gen_HMoth > -1 ){
	for(int i_H=0; i_H<_n_genH; i_H++){
	  if( genH_index[i_H]==i_gen_HMoth){
	    i_H_Moth = i_H;
	    break;
	  }
	}
      }      
      _gentau_HMothInd.push_back(i_H_Moth);


    }


    for(int i_nu=0; i_nu<_n_gennu; i_nu++){

      int i_gen = gennu_index[i_nu];
      
      int i_tau_Moth = -1;
      int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
      if( i_gen_TauMoth > -1 ){
	for(int i_tau=0; i_tau<_n_gentau; i_tau++){
	  if( gentau_index[i_tau]==i_gen_TauMoth){
	    i_tau_Moth = i_tau;
	    break;
	  }
	}
      }
      _gennu_TauMothInd.push_back(i_tau_Moth);



    }

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}
