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

#include "leptonSF.cc"

using namespace std;



void split_tree(TString filename_in, TString filename_out,
		int i_split1=0, int i_split2=0,
		bool isMC=true, bool isReHLT=true){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }

  TH1F* h=new TH1F("h_counter","h_counter",3,0,3);


  //Old branches used
  
  int _n_recolep_mvasel;
  int _n_recolep_fakeable;

  vector<int> *_recolep_charge;
  vector<int> *_recolep_pdg;
  vector<float> *_recolep_e;
  vector<float> *_recolep_px;
  vector<float> *_recolep_py;
  vector<float> *_recolep_pz;
  vector<float> *_recolep_pt;
  vector<float> *_recolep_conept;
  vector<float> *_recolep_eta;
  vector<float> *_recolep_phi;
  vector<float> *_recolep_fakerate;
  vector<float> *_recolep_fakerate_QCD_MC;
  vector<float> *_recolep_fakerate_ttbar_MC;
  vector<float> *_recolep_QFrate; 
  vector<bool> *_recolep_ismvasel;
  vector<bool> *_recolep_tightcharge;
  vector<bool> *_recolep_isGenMatched;
  vector<int> *_recolep_genMatchInd;

  vector<float> *_recomu_e;
  vector<float> *_recomu_px;
  vector<float> *_recomu_py;
  vector<float> *_recomu_pz;

  vector<float> *_recoele_e;
  vector<float> *_recoele_px;
  vector<float> *_recoele_py;
  vector<float> *_recoele_pz;

  float _ETmissLD;
  int _n_recoPFJet;
  int _n_recoPFJet_btag_medium;
  int _n_recoPFJet_btag_loose;

  int _n_recotauh;
  vector<int> *_recotauh_charge;
  vector<int> *_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> *_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> *_recotauh_againstMuonLoose3;
  vector<int> *_recotauh_againstMuonTight3;
  vector<int> *_recotauh_againstElectronVLooseMVA6;
  vector<int> *_recotauh_againstElectronLooseMVA6;
  vector<int> *_recotauh_againstElectronMediumMVA6;
  vector<int> *_recotauh_againstElectronTightMVA6;
  vector<int> *_recotauh_againstElectronVTightMVA6;
  vector<int> *_recotauh_decayMode;
  vector<float> *_recotauh_e;
  vector<float> *_recotauh_px;
  vector<float> *_recotauh_py;
  vector<float> *_recotauh_pz;
  vector<bool> *_recotauh_isGenMatched;
  vector<int> *_recotauh_genMatchInd;
  vector<float> *_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float> *_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;


  tree->SetBranchAddress("n_recolep_mvasel",&_n_recolep_mvasel);
  tree->SetBranchAddress("n_recolep_fakeable",&_n_recolep_fakeable);

  tree->SetBranchAddress("recolep_charge",&_recolep_charge);
  tree->SetBranchAddress("recolep_pdg",&_recolep_pdg);
  tree->SetBranchAddress("recolep_e",&_recolep_e);
  tree->SetBranchAddress("recolep_px",&_recolep_px);
  tree->SetBranchAddress("recolep_py",&_recolep_py);
  tree->SetBranchAddress("recolep_pz",&_recolep_pz);
  tree->SetBranchAddress("recolep_pt",&_recolep_pt);
  tree->SetBranchAddress("recolep_conept",&_recolep_conept);
  tree->SetBranchAddress("recolep_eta",&_recolep_eta);
  tree->SetBranchAddress("recolep_phi",&_recolep_phi);
  tree->SetBranchAddress("recolep_fakerate",&_recolep_fakerate);
  tree->SetBranchAddress("recolep_fakerate_QCD_MC",&_recolep_fakerate_QCD_MC);
  tree->SetBranchAddress("recolep_fakerate_ttbar_MC",&_recolep_fakerate_ttbar_MC);
  tree->SetBranchAddress("recolep_QFrate",&_recolep_QFrate);
  tree->SetBranchAddress("recolep_ismvasel",&_recolep_ismvasel);
  tree->SetBranchAddress("recolep_tightcharge",&_recolep_tightcharge);
  tree->SetBranchAddress("recolep_isGenMatched",&_recolep_isGenMatched);
  tree->SetBranchAddress("recolep_genMatchInd",&_recolep_genMatchInd);

  tree->SetBranchAddress("recomu_e",&_recomu_e);
  tree->SetBranchAddress("recomu_px",&_recomu_px);
  tree->SetBranchAddress("recomu_py",&_recomu_py);
  tree->SetBranchAddress("recomu_pz",&_recomu_pz);

  tree->SetBranchAddress("recoele_e",&_recoele_e);
  tree->SetBranchAddress("recoele_px",&_recoele_px);
  tree->SetBranchAddress("recoele_py",&_recoele_py);
  tree->SetBranchAddress("recoele_pz",&_recoele_pz);

  tree->SetBranchAddress("ETmissLD",&_ETmissLD);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("n_recotauh",&_n_recotauh);
  tree->SetBranchAddress("recotauh_charge",&_recotauh_charge);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_againstMuonLoose3",&_recotauh_againstMuonLoose3);
  tree->SetBranchAddress("recotauh_againstMuonTight3",&_recotauh_againstMuonTight3);
  tree->SetBranchAddress("recotauh_againstElectronVLooseMVA6",&_recotauh_againstElectronVLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronLooseMVA6",&_recotauh_againstElectronLooseMVA6);
  tree->SetBranchAddress("recotauh_againstElectronMediumMVA6",&_recotauh_againstElectronMediumMVA6);
  tree->SetBranchAddress("recotauh_againstElectronTightMVA6",&_recotauh_againstElectronTightMVA6);
  tree->SetBranchAddress("recotauh_againstElectronVTightMVA6",&_recotauh_againstElectronVTightMVA6);
  tree->SetBranchAddress("recotauh_decayMode",&_recotauh_decayMode);
  tree->SetBranchAddress("recotauh_e",&_recotauh_e);
  tree->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree->SetBranchAddress("recotauh_pz",&_recotauh_pz);
  tree->SetBranchAddress("recotauh_isGenMatched",&_recotauh_isGenMatched);
  tree->SetBranchAddress("recotauh_genMatchInd",&_recotauh_genMatchInd);
  tree->SetBranchAddress("recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  
  Long64_t nentries = tree->GetEntries();

  //TFile* f_new = TFile::Open(dir_out+file);
  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_2lSS=tree->GetTree()->CloneTree(0);
  tree_2lSS->SetNameTitle("HTauTauTree_2lSS","HTauTauTree_2lSS");
  TTree* tree_2lOS_CR=tree->GetTree()->CloneTree(0);
  tree_2lOS_CR->SetNameTitle("HTauTauTree_2lOS_CR","HTauTauTree_2lOS_CR");
  TTree* tree_2lSS_lepMVA_CR=tree->GetTree()->CloneTree(0);
  tree_2lSS_lepMVA_CR->SetNameTitle("HTauTauTree_2lSS_lepMVA_CR","HTauTauTree_2lSS_lepMVA_CR");
  TTree* tree_2lSS_jetmult_CR=tree->GetTree()->CloneTree(0);
  tree_2lSS_jetmult_CR->SetNameTitle("HTauTauTree_2lSS_jetmult_CR","HTauTauTree_2lSS_jetmult_CR");
  TTree* tree_2lSS_ttbarOF_CR=tree->GetTree()->CloneTree(0);
  tree_2lSS_ttbarOF_CR->SetNameTitle("HTauTauTree_2lSS_ttbarOF_CR","HTauTauTree_2lSS_ttbarOF_CR");
  TTree* tree_2lSS_2jet_CR=tree->GetTree()->CloneTree(0);
  tree_2lSS_2jet_CR->SetNameTitle("HTauTauTree_2lSS_2jet_CR","HTauTauTree_2lSS_2jet_CR");

  TTree* tree_3l=tree->GetTree()->CloneTree(0);
  tree_3l->SetNameTitle("HTauTauTree_3l","HTauTauTree_3l");
  TTree* tree_3l_lepMVA_CR=tree->GetTree()->CloneTree(0);
  tree_3l_lepMVA_CR->SetNameTitle("HTauTauTree_3l_lepMVA_CR","HTauTauTree_3l_lepMVA_CR");
  TTree* tree_3l_WZ_CR=tree->GetTree()->CloneTree(0);
  tree_3l_WZ_CR->SetNameTitle("HTauTauTree_3l_WZ_CR","HTauTauTree_3l_WZ_CR");
  TTree* tree_3l_ttZ_CR=tree->GetTree()->CloneTree(0);
  tree_3l_ttZ_CR->SetNameTitle("HTauTauTree_3l_ttZ_CR","HTauTauTree_3l_ttZ_CR");
  TTree* tree_3l_ttZ_lepMVA_CR=tree->GetTree()->CloneTree(0);
  tree_3l_ttZ_lepMVA_CR->SetNameTitle("HTauTauTree_3l_ttZ_lepMVA_CR","HTauTauTree_3l_ttZ_lepMVA_CR");

  TTree* tree_1l_2tau=tree->GetTree()->CloneTree(0);
  tree_1l_2tau->SetNameTitle("HTauTauTree_1l_2tau","HTauTauTree_1l_2tau");
  TTree* tree_1l_2tau_fake_CR=tree->GetTree()->CloneTree(0);
  tree_1l_2tau_fake_CR->SetNameTitle("HTauTauTree_1l_2tau_fake_CR","HTauTauTree_1l_2tau_fake_CR");
  TTree* tree_1l_2tau_2jet_CR=tree->GetTree()->CloneTree(0);
  tree_1l_2tau_2jet_CR->SetNameTitle("HTauTauTree_1l_2tau_2jet_CR","HTauTauTree_1l_2tau_2jet_CR");

  vector<TTree*> tree_new;
  tree_new.push_back(tree_2lSS);
  tree_new.push_back(tree_2lOS_CR);
  tree_new.push_back(tree_2lSS_lepMVA_CR);
  tree_new.push_back(tree_2lSS_jetmult_CR);
  tree_new.push_back(tree_2lSS_ttbarOF_CR);
  tree_new.push_back(tree_2lSS_2jet_CR);

 
  tree_new.push_back(tree_3l);
  tree_new.push_back(tree_3l_lepMVA_CR);
  tree_new.push_back(tree_3l_WZ_CR);
  tree_new.push_back(tree_3l_ttZ_CR);
  tree_new.push_back(tree_3l_ttZ_lepMVA_CR);

  tree_new.push_back(tree_1l_2tau);
  tree_new.push_back(tree_1l_2tau_fake_CR);
  tree_new.push_back(tree_1l_2tau_2jet_CR);



  //New branches

  int _category;

  /*
    1: mumu+, btight
    2: mumu-, btight
    3: mumu+, bloose
    4: mumu-, bloose
    5: emu+, btight
    6: emu-, btight
    7: emu+, bloose
    8: emu-, bloose
    9: ee+
    10: ee-
    11: 2lSS + tauh
    12: 3l+, btight
    13: 3l-, btight
    14: 3l+, bloose
    15: 3l-, bloose
    16: 3l + tauh
    20: 1l + 2tauh
    

    -1: mumu OS, btight
    -3: mumu OS, bloose
    -5: emu OS, mu+ btight
    -6: emu OS, mu-  btight
    -7: emu OS, mu+ bloose
    -8: emu OS, mu- bloose
    -9: ee OS, lead. e+
    -10: ee OS, lead. e-
    -11: 2lOS + tauh

    31: mumu+, btight, lepMVA CR
    32: mumu-, btight, lepMVA CR
    33: mumu+, bloose, lepMVA CR
    34: mumu-, bloose, lepMVA CR
    35: emu+, btight, lepMVA CR
    36: emu-, btight, lepMVA CR
    37: emu+, bloose, lepMVA CR
    38: emu-, bloose, lepMVA CR
    39: ee+, lepMVA CR
    40: ee-, lepMVA CR
    41: 2lSS + tauh, lepMVA + tau CR
    42: 3l+, btight, lepMVA CR
    43: 3l-, btight, lepMVA CR
    44: 3l+, bloose, lepMVA CR
    45: 3l-, bloose, lepMVA CR
    46: 3l- + tauh, lepMVA + tau CR
    50: 1l + 2tauh, lepMVA + tau CR

   */

  vector<int> _recolep_sel_charge;
  vector<int> _recolep_sel_pdg;
  vector<float> _recolep_sel_e;
  vector<float> _recolep_sel_px;
  vector<float> _recolep_sel_py;
  vector<float> _recolep_sel_pz;
  vector<float> _recolep_sel_pt;
  vector<float> _recolep_sel_conept;
  vector<float> _recolep_sel_eta;
  vector<float> _recolep_sel_phi;
  vector<float> _recolep_sel_fakerate;
  vector<float> _recolep_sel_fakerate_QCD_MC;
  vector<float> _recolep_sel_fakerate_ttbar_MC;
  vector<float> _recolep_sel_QFrate; 
  vector<bool>  _recolep_sel_ismvasel;
  vector<bool>  _recolep_sel_tightcharge;
  vector<bool>  _recolep_sel_isGenMatched;
  vector<int>  _recolep_sel_genMatchInd;

  vector<int> _recotauh_sel_charge;
  vector<int> _recotauh_sel_decayMode;
  vector<float> _recotauh_sel_e;
  vector<float> _recotauh_sel_px;
  vector<float> _recotauh_sel_py;
  vector<float> _recotauh_sel_pz;
  vector<float> _recotauh_sel_pt;
  vector<float> _recotauh_sel_eta;
  vector<float> _recotauh_sel_phi;
  vector<int> _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> _recotauh_sel_againstMuonLoose3;
  vector<int> _recotauh_sel_againstMuonTight3;
  vector<int> _recotauh_sel_againstElectronVLooseMVA6;
  vector<int> _recotauh_sel_againstElectronLooseMVA6;
  vector<int> _recotauh_sel_againstElectronMediumMVA6;
  vector<int> _recotauh_sel_againstElectronTightMVA6;
  vector<int> _recotauh_sel_againstElectronVTightMVA6;
  vector<bool> _recotauh_sel_isGenMatched;
  vector<int> _recotauh_sel_genMatchInd;
  vector<float> _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float> _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;

  int _n_fake_lep;
  int _n_fake_tau;

  float _event_weight_ttH;
  float _event_weight_ttH_FR_QCD_MC;
  float _event_weight_ttH_FR_TT_MC;
  float _event_weight_ttH_ele_FR_QCD_MC;
  float _event_weight_ttH_ele_FR_TT_MC;
  float _event_weight_ttH_mu_FR_QCD_MC;
  float _event_weight_ttH_mu_FR_TT_MC;


  float _triggerSF_weight;
  float _triggerSF_weight_up;
  float _triggerSF_weight_down;

  float _leptonSF_ttH_weight;
  float _tauSF_weight;

  bool _isGenMatched;


  for(unsigned int i=0; i<tree_new.size();i++){

    tree_new[i]->Branch("category",&_category,"category/I");
    
    tree_new[i]->Branch("recolep_sel_charge",&_recolep_sel_charge);
    tree_new[i]->Branch("recolep_sel_pdg",&_recolep_sel_pdg);
    tree_new[i]->Branch("recolep_sel_e",&_recolep_sel_e);
    tree_new[i]->Branch("recolep_sel_px",&_recolep_sel_px);
    tree_new[i]->Branch("recolep_sel_py",&_recolep_sel_py);
    tree_new[i]->Branch("recolep_sel_pz",&_recolep_sel_pz);
    tree_new[i]->Branch("recolep_sel_pt",&_recolep_sel_pt);
    tree_new[i]->Branch("recolep_sel_conept",&_recolep_sel_conept);
    tree_new[i]->Branch("recolep_sel_eta",&_recolep_sel_eta);
    tree_new[i]->Branch("recolep_sel_phi",&_recolep_sel_phi);
    tree_new[i]->Branch("recolep_sel_fakerate",&_recolep_sel_fakerate);
    tree_new[i]->Branch("recolep_sel_fakerate_QCD_MC",&_recolep_sel_fakerate_QCD_MC);
    tree_new[i]->Branch("recolep_sel_fakerate_ttbar_MC",&_recolep_sel_fakerate_ttbar_MC);
    tree_new[i]->Branch("recolep_sel_QFrate",&_recolep_sel_QFrate);
    tree_new[i]->Branch("recolep_sel_ismvasel",&_recolep_sel_ismvasel);
    tree_new[i]->Branch("recolep_sel_tightcharge",&_recolep_sel_tightcharge);
    tree_new[i]->Branch("recolep_sel_isGenMatched",&_recolep_sel_isGenMatched);
    tree_new[i]->Branch("recolep_sel_genMatchInd",&_recolep_sel_genMatchInd);

    tree_new[i]->Branch("recotauh_sel_charge",&_recotauh_sel_charge);
    tree_new[i]->Branch("recotauh_sel_decayMode",&_recotauh_sel_decayMode);
    tree_new[i]->Branch("recotauh_sel_e",&_recotauh_sel_e);
    tree_new[i]->Branch("recotauh_sel_px",&_recotauh_sel_px);
    tree_new[i]->Branch("recotauh_sel_py",&_recotauh_sel_py);
    tree_new[i]->Branch("recotauh_sel_pz",&_recotauh_sel_pz);
    tree_new[i]->Branch("recotauh_sel_pt",&_recotauh_sel_pt);
    tree_new[i]->Branch("recotauh_sel_eta",&_recotauh_sel_eta);
    tree_new[i]->Branch("recotauh_sel_phi",&_recotauh_sel_phi);
    tree_new[i]->Branch("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree_new[i]->Branch("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree_new[i]->Branch("recotauh_sel_againstMuonLoose3",&_recotauh_sel_againstMuonLoose3);
    tree_new[i]->Branch("recotauh_sel_againstMuonTight3",&_recotauh_sel_againstMuonTight3);
    tree_new[i]->Branch("recotauh_sel_againstElectronVLooseMVA6",&_recotauh_sel_againstElectronVLooseMVA6);
    tree_new[i]->Branch("recotauh_sel_againstElectronLooseMVA6",&_recotauh_sel_againstElectronLooseMVA6);
    tree_new[i]->Branch("recotauh_sel_againstElectronMediumMVA6",&_recotauh_sel_againstElectronMediumMVA6);
    tree_new[i]->Branch("recotauh_sel_againstElectronTightMVA6",&_recotauh_sel_againstElectronTightMVA6);
    tree_new[i]->Branch("recotauh_sel_againstElectronVTightMVA6",&_recotauh_sel_againstElectronVTightMVA6);
    tree_new[i]->Branch("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);
    tree_new[i]->Branch("recotauh_sel_genMatchInd",&_recotauh_sel_genMatchInd);

    tree_new[i]->Branch("recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree_new[i]->Branch("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);

    tree_new[i]->Branch("n_fake_lep",&_n_fake_lep,"n_fake_lep/I");
    tree_new[i]->Branch("n_fake_tau",&_n_fake_tau,"n_fake_tau/I");

    tree_new[i]->Branch("event_weight_ttH",&_event_weight_ttH,"event_weight_ttH/F");
    tree_new[i]->Branch("event_weight_ttH_FR_QCD_MC",&_event_weight_ttH_FR_QCD_MC,"event_weight_ttH_FR_QCD_MC/F");
    tree_new[i]->Branch("event_weight_ttH_FR_TT_MC",&_event_weight_ttH_FR_TT_MC,"event_weight_ttH_FR_TT_MC/F");
    tree_new[i]->Branch("event_weight_ttH_ele_FR_QCD_MC",&_event_weight_ttH_ele_FR_QCD_MC,"event_weight_ttH_ele_FR_QCD_MC/F");
    tree_new[i]->Branch("event_weight_ttH_ele_FR_TT_MC",&_event_weight_ttH_ele_FR_TT_MC,"event_weight_ttH_ele_FR_TT_MC/F");
    tree_new[i]->Branch("event_weight_ttH_mu_FR_QCD_MC",&_event_weight_ttH_mu_FR_QCD_MC,"event_weight_ttH_mu_FR_QCD_MC/F");
    tree_new[i]->Branch("event_weight_ttH_mu_FR_TT_MC",&_event_weight_ttH_mu_FR_TT_MC,"event_weight_ttH_mu_FR_TT_MC/F");

    tree_new[i]->Branch("triggerSF_weight",&_triggerSF_weight,"triggerSF_weight/F");
    tree_new[i]->Branch("triggerSF_weight_up",&_triggerSF_weight_up,"triggerSF_weight_up/F");
    tree_new[i]->Branch("triggerSF_weight_down",&_triggerSF_weight_down,"triggerSF_weight_down/F");
    tree_new[i]->Branch("leptonSF_ttH_weight",&_leptonSF_ttH_weight,"leptonSF_ttH_weight/F");
    tree_new[i]->Branch("tauSF_weight",&_tauSF_weight,"tauSF_weight/F");

    tree_new[i]->Branch("isGenMatched",&_isGenMatched,"isGenMatched/O");

  }



  cout<<"nentries="<<nentries<<endl;

  int skip_entries=0;
  if(i_split1>0){
    skip_entries = nentries/i_split1 * i_split2;
    nentries = nentries/i_split1 * (i_split2+1);
  }


  //skip_entries=44583;
  //nentries = 1;

  for (int i=skip_entries;i<skip_entries+nentries;i++) {

    h->Fill(1);

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _category = -1;

    _recolep_sel_charge.clear();
    _recolep_sel_pdg.clear();
    _recolep_sel_e.clear();
    _recolep_sel_px.clear();
    _recolep_sel_py.clear();
    _recolep_sel_pz.clear();
    _recolep_sel_pt.clear();
    _recolep_sel_conept.clear();
    _recolep_sel_eta.clear();
    _recolep_sel_phi.clear();
    _recolep_sel_fakerate.clear();
    _recolep_sel_fakerate_QCD_MC.clear();
    _recolep_sel_fakerate_ttbar_MC.clear();
    _recolep_sel_QFrate.clear(); 
    _recolep_sel_ismvasel.clear();
    _recolep_sel_tightcharge.clear();
    _recolep_sel_isGenMatched.clear();
    _recolep_sel_genMatchInd.clear();

    _recotauh_sel_charge.clear();
    _recotauh_sel_decayMode.clear();
    _recotauh_sel_e.clear();
    _recotauh_sel_px.clear();
    _recotauh_sel_py.clear();
    _recotauh_sel_pz.clear();
    _recotauh_sel_pt.clear();
    _recotauh_sel_eta.clear();
    _recotauh_sel_phi.clear();
    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_sel_againstMuonLoose3.clear();
    _recotauh_sel_againstMuonTight3.clear();
    _recotauh_sel_againstElectronVLooseMVA6.clear();
    _recotauh_sel_againstElectronLooseMVA6.clear();
    _recotauh_sel_againstElectronMediumMVA6.clear();
    _recotauh_sel_againstElectronTightMVA6.clear();
    _recotauh_sel_againstElectronVTightMVA6.clear();
    _recotauh_sel_isGenMatched.clear();
    _recotauh_sel_genMatchInd.clear();
    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();

    _n_fake_lep = 0;
    _n_fake_tau = 0;

    _event_weight_ttH = 0;
    _event_weight_ttH_FR_QCD_MC = 0;
    _event_weight_ttH_FR_TT_MC = 0;
    _event_weight_ttH_ele_FR_QCD_MC = 0;
    _event_weight_ttH_ele_FR_TT_MC = 0;
    _event_weight_ttH_mu_FR_QCD_MC = 0;
    _event_weight_ttH_mu_FR_TT_MC = 0;

    _triggerSF_weight = 0;
    _triggerSF_weight_up = 0;
    _triggerSF_weight_down = 0;
    _leptonSF_ttH_weight = 0;
    _tauSF_weight = 0;
    _isGenMatched = 0;

    _n_recolep_mvasel = 0;
    _n_recolep_fakeable = 0;

    _recolep_charge = 0;
    _recolep_pdg = 0;
    _recolep_e = 0;
    _recolep_px = 0;
    _recolep_py = 0;
    _recolep_pz = 0;
    _recolep_pt = 0;
    _recolep_conept = 0;
    _recolep_eta = 0;
    _recolep_phi = 0;
    _recolep_fakerate = 0;
    _recolep_fakerate_QCD_MC = 0;
    _recolep_fakerate_ttbar_MC = 0;
    _recolep_QFrate = 0; 
    _recolep_ismvasel = 0;
    _recolep_tightcharge = 0;
    _recolep_isGenMatched = 0;
    _recolep_genMatchInd = 0;
  
    _recomu_e = 0;
    _recomu_px = 0;
    _recomu_py = 0;
    _recomu_pz = 0;
  
    _recoele_e = 0;
    _recoele_px = 0;
    _recoele_py = 0;
    _recoele_pz = 0;

    _ETmissLD = 0;
    _n_recoPFJet = 0;
    _n_recoPFJet_btag_medium = 0;
    _n_recoPFJet_btag_loose = 0;

    _n_recotauh = 0;
    _recotauh_charge = 0;
    _recotauh_decayMode = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
    _recotauh_againstMuonLoose3 = 0;
    _recotauh_againstMuonTight3 = 0;
    _recotauh_againstElectronVLooseMVA6 = 0;
    _recotauh_againstElectronLooseMVA6 = 0;
    _recotauh_againstElectronMediumMVA6 = 0;
    _recotauh_againstElectronTightMVA6 = 0;
    _recotauh_againstElectronVTightMVA6 = 0;
    _recotauh_e = 0;
    _recotauh_px = 0;
    _recotauh_py = 0;
    _recotauh_pz = 0;
    _recotauh_isGenMatched = 0;
    _recotauh_genMatchInd = 0;
    _recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
    _recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;

    tree->GetEntry(i);

    // 1l+2tau
    if(_n_recolep_fakeable>=1 && _n_recolep_mvasel<=1 && _n_recotauh>=2){     
	  
      TLorentzVector lep1((*_recolep_px)[0],(*_recolep_py)[0],(*_recolep_pz)[0],(*_recolep_e)[0]);
	  	    
      _recolep_sel_charge.push_back((*_recolep_charge)[0]);
      _recolep_sel_pdg.push_back((*_recolep_pdg)[0]);
      _recolep_sel_e.push_back(lep1.E());
      _recolep_sel_px.push_back(lep1.Px());
      _recolep_sel_py.push_back(lep1.Py());
      _recolep_sel_pz.push_back(lep1.Pz());
      _recolep_sel_pt.push_back(lep1.Pt());
      _recolep_sel_conept.push_back((*_recolep_conept)[0]);
      _recolep_sel_eta.push_back(lep1.Eta());
      _recolep_sel_phi.push_back(lep1.Phi());
      _recolep_sel_fakerate.push_back((*_recolep_fakerate)[0]);
      _recolep_sel_fakerate_QCD_MC.push_back((*_recolep_fakerate_QCD_MC)[0]);
      _recolep_sel_fakerate_ttbar_MC.push_back((*_recolep_fakerate_ttbar_MC)[0]);
      _recolep_sel_QFrate.push_back((*_recolep_QFrate)[0]);
      _recolep_sel_ismvasel.push_back((*_recolep_ismvasel)[0]);
      _recolep_sel_tightcharge.push_back((*_recolep_tightcharge)[0]);
      if(isMC){
	_recolep_sel_isGenMatched.push_back((*_recolep_isGenMatched)[0]);
	_recolep_sel_genMatchInd.push_back((*_recolep_genMatchInd)[0]);
      }


      for(unsigned int i_tau=0; i_tau<(*_recotauh_charge).size(); i_tau++){
	  
	if((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]>0.5){
	    
	    _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
	    _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
	    
	    TLorentzVector tau_tlv((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
	    
	    _recotauh_sel_e.push_back(tau_tlv.E());
	    _recotauh_sel_px.push_back(tau_tlv.Px());
	    _recotauh_sel_py.push_back(tau_tlv.Py());
	    _recotauh_sel_pz.push_back(tau_tlv.Pz());
	    _recotauh_sel_pt.push_back(tau_tlv.Pt());
	    _recotauh_sel_eta.push_back(tau_tlv.Eta());
	    _recotauh_sel_phi.push_back(tau_tlv.Phi());
	    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	    _recotauh_sel_againstMuonTight3.push_back((*_recotauh_againstMuonTight3)[i_tau]);
	    _recotauh_sel_againstElectronVLooseMVA6.push_back((*_recotauh_againstElectronVLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronMediumMVA6.push_back((*_recotauh_againstElectronMediumMVA6)[i_tau]);
	    _recotauh_sel_againstElectronTightMVA6.push_back((*_recotauh_againstElectronTightMVA6)[i_tau]);
	    _recotauh_sel_againstElectronVTightMVA6.push_back((*_recotauh_againstElectronVTightMVA6)[i_tau]);
	    if(isMC){
	      _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);	    
	      _recotauh_sel_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);	    
	    }
	    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);

	}

      }	  

      bool tau = _recotauh_sel_e.size()>=2;

      
      if(!tau){

	_recotauh_sel_charge.clear();
	_recotauh_sel_decayMode.clear();
	_recotauh_sel_e.clear();
	_recotauh_sel_px.clear();
	_recotauh_sel_py.clear();
	_recotauh_sel_pz.clear();
	_recotauh_sel_pt.clear();
	_recotauh_sel_eta.clear();
	_recotauh_sel_phi.clear();
	_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
	_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
	_recotauh_sel_againstMuonLoose3.clear();
	_recotauh_sel_againstMuonTight3.clear();
	_recotauh_sel_againstElectronVLooseMVA6.clear();
	_recotauh_sel_againstElectronLooseMVA6.clear();
	_recotauh_sel_againstElectronMediumMVA6.clear();
	_recotauh_sel_againstElectronTightMVA6.clear();
	_recotauh_sel_againstElectronVTightMVA6.clear();
	_recotauh_sel_isGenMatched.clear();
	_recotauh_sel_genMatchInd.clear();
	_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
	_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
	
	for(unsigned int i_tau=0; i_tau<2; i_tau++){
	  	    
	  _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
	  _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
	  
	  TLorentzVector tau_tlv((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
	  
	  _recotauh_sel_e.push_back(tau_tlv.E());
	  _recotauh_sel_px.push_back(tau_tlv.Px());
	  _recotauh_sel_py.push_back(tau_tlv.Py());
	  _recotauh_sel_pz.push_back(tau_tlv.Pz());
	  _recotauh_sel_pt.push_back(tau_tlv.Pt());
	  _recotauh_sel_eta.push_back(tau_tlv.Eta());
	  _recotauh_sel_phi.push_back(tau_tlv.Phi());
	  _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	  _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	  _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	  _recotauh_sel_againstMuonTight3.push_back((*_recotauh_againstMuonTight3)[i_tau]);
	  _recotauh_sel_againstElectronVLooseMVA6.push_back((*_recotauh_againstElectronVLooseMVA6)[i_tau]);
	  _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	  _recotauh_sel_againstElectronMediumMVA6.push_back((*_recotauh_againstElectronMediumMVA6)[i_tau]);
	  _recotauh_sel_againstElectronTightMVA6.push_back((*_recotauh_againstElectronTightMVA6)[i_tau]);
	  _recotauh_sel_againstElectronVTightMVA6.push_back((*_recotauh_againstElectronVTightMVA6)[i_tau]);
	  if(isMC){
	    _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
	    _recotauh_sel_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);
	  }
	  _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	  _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    	
	}	

      }


	  

      bool tight_mvasel = _recolep_sel_ismvasel[0];
      //bool pt_lep = ((_recolep_sel_conept[0]>25 && abs(_recolep_sel_pdg[0])==13) || (_recolep_sel_conept[0]>30 && abs(_recolep_sel_pdg[0])==11));
      //bool pt_lep = ((_recolep_sel_pt[0]>25 && abs(_recolep_sel_pdg[0])==13) || (_recolep_sel_pt[0]>30 && abs(_recolep_sel_pdg[0])==11));      
      bool pt_lep = ((_recolep_sel_pt[0]>20 && abs(_recolep_sel_pdg[0])==13) || (_recolep_sel_pt[0]>25 && abs(_recolep_sel_pdg[0])==11));
      bool taus = _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT[1];
      bool jetmult_sig = _n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2);
      if(isMC)
	_isGenMatched = _recolep_sel_isGenMatched[0] && _recotauh_sel_isGenMatched[0] && _recotauh_sel_isGenMatched[1];
      bool tau_charge = _recotauh_sel_charge[0]*_recotauh_sel_charge[1]<0;
      bool jetmult_2jet_CR = _n_recoPFJet>=2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2);

      bool sig_1l2tau = tight_mvasel && pt_lep && taus && jetmult_sig && tau_charge;
      bool fake_CR = !(tight_mvasel && taus) && pt_lep && jetmult_sig && tau_charge;
      bool CR_2jet_tight_lep = tight_mvasel && taus && pt_lep && jetmult_2jet_CR && tau_charge;
      bool CR_2jet_fake_lep = !(tight_mvasel && taus) && pt_lep && jetmult_2jet_CR && tau_charge;


      /*cout<<"tight_mvasel="<<tight_mvasel<<endl;
      cout<<"taus="<<taus<<endl;
      cout<<"jetmult_sig="<<jetmult_sig<<endl;
      cout<<"tau_charge="<<tau_charge<<endl;
      cout<<"pt_lep="<<pt_lep<<endl;
      cout<<"fake_CR="<<fake_CR<<endl;*/

      _event_weight_ttH = 1;
      _event_weight_ttH_FR_QCD_MC = 1;
      _event_weight_ttH_FR_TT_MC = 1;
      _event_weight_ttH_ele_FR_QCD_MC = 1;
      _event_weight_ttH_ele_FR_TT_MC = 1;
      _event_weight_ttH_mu_FR_QCD_MC = 1;
      _event_weight_ttH_mu_FR_TT_MC = 1;
      _triggerSF_weight = 1;
      _triggerSF_weight_up = 1;
      _triggerSF_weight_down = 1;
      _leptonSF_ttH_weight = 1;
      _tauSF_weight = 1;

      _triggerSF_weight = triggerSF_ttH_1l(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0]);
      _triggerSF_weight_up = triggerSF_ttH_1l(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0], +1.);
      _triggerSF_weight_down = triggerSF_ttH_1l(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0], -1.);

      if(tight_mvasel)
	_leptonSF_ttH_weight = leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],3); //No tight-charge criteria for 1l2tau	      
      else
	_leptonSF_ttH_weight = _get_recoToLoose_leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],3);

      if(isMC)
	_tauSF_weight = (1-0.1*_recotauh_sel_isGenMatched[0])*(1-0.1*_recotauh_sel_isGenMatched[1]);
      
      int n_fake = 0;

      if(!_recolep_sel_ismvasel[0]){
	_event_weight_ttH *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	_event_weight_ttH_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	_event_weight_ttH_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);

	if(abs(_recolep_sel_pdg[0])==11){
	  _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	  _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);
	  _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	  _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	}
	
	else if(abs(_recolep_sel_pdg[0])==13){
	  _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	  _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	  _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	  _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);
	}


	n_fake++;
	_n_fake_lep++;
      }

      if(!_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT[0]){
	float weight_tau = _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT[0]/(1-_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT[0]);
	_event_weight_ttH *= weight_tau;
	_event_weight_ttH_FR_QCD_MC *= weight_tau;
	_event_weight_ttH_FR_TT_MC *= weight_tau;
	_event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	_event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	_event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	_event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	
	n_fake++;
	_n_fake_tau++;
      }

      if(!_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT[1]){
	float weight_tau = _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT[1]/(1-_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT[1]);
	_event_weight_ttH *= weight_tau;
	_event_weight_ttH_FR_QCD_MC *= weight_tau;
	_event_weight_ttH_FR_TT_MC *= weight_tau;
	_event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	_event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	_event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	_event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	
	n_fake++;
	_n_fake_tau++;
      }

      if(n_fake>0 && n_fake%2==0){
	_event_weight_ttH *=-1;
	_event_weight_ttH_FR_QCD_MC *=-1;
	_event_weight_ttH_FR_TT_MC *=-1;
	_event_weight_ttH_ele_FR_QCD_MC *= -1;
	_event_weight_ttH_ele_FR_TT_MC *= -1;
	_event_weight_ttH_mu_FR_TT_MC *= -1;
	_event_weight_ttH_mu_FR_TT_MC *= -1;
      }

      if(sig_1l2tau){

	_category = 20;
	tree_1l_2tau->Fill();

      }

      else if(fake_CR){

	_category = 50;
	tree_1l_2tau_fake_CR->Fill();

      }

      else if(CR_2jet_tight_lep){

	_category = 20;
	tree_1l_2tau_2jet_CR->Fill();

      }

      else if(CR_2jet_fake_lep){

	_category = 50;
	tree_1l_2tau_2jet_CR->Fill();

      }



    }


    _recolep_sel_charge.clear();
    _recolep_sel_pdg.clear();
    _recolep_sel_e.clear();
    _recolep_sel_px.clear();
    _recolep_sel_py.clear();
    _recolep_sel_pz.clear();
    _recolep_sel_pt.clear();
    _recolep_sel_conept.clear();
    _recolep_sel_eta.clear();
    _recolep_sel_phi.clear();
    _recolep_sel_fakerate.clear();
    _recolep_sel_fakerate_QCD_MC.clear();
    _recolep_sel_fakerate_ttbar_MC.clear();
    _recolep_sel_QFrate.clear(); 
    _recolep_sel_ismvasel.clear();
    _recolep_sel_tightcharge.clear();
    _recolep_sel_isGenMatched.clear();      
    _recolep_sel_genMatchInd.clear();      


    _recotauh_sel_charge.clear();
    _recotauh_sel_decayMode.clear();    
    _recotauh_sel_e.clear();
    _recotauh_sel_px.clear();
    _recotauh_sel_py.clear();
    _recotauh_sel_pz.clear();
    _recotauh_sel_pt.clear();
    _recotauh_sel_eta.clear();
    _recotauh_sel_phi.clear();
    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_sel_againstMuonLoose3.clear();
    _recotauh_sel_againstMuonTight3.clear();
    _recotauh_sel_againstElectronVLooseMVA6.clear();
    _recotauh_sel_againstElectronLooseMVA6.clear();
    _recotauh_sel_againstElectronMediumMVA6.clear();
    _recotauh_sel_againstElectronTightMVA6.clear();
    _recotauh_sel_againstElectronVTightMVA6.clear();
    _recotauh_sel_isGenMatched.clear();
    _recotauh_sel_genMatchInd.clear();
    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();

    _n_fake_lep = 0;
    _n_fake_tau = 0;


    if(_n_recolep_fakeable>=2){

      bool inv_mass_lep_pairs=true;
      
      vector<TLorentzVector> loose_leptons;
      
      for(unsigned int i_mu=0; i_mu<(*_recomu_e).size(); i_mu++){
	TLorentzVector mu((*_recomu_px)[i_mu], (*_recomu_py)[i_mu], (*_recomu_pz)[i_mu], (*_recomu_e)[i_mu]);
	loose_leptons.push_back(mu);
      }
      
      for(unsigned int i_ele=0; i_ele<(*_recoele_e).size(); i_ele++){
	TLorentzVector ele((*_recoele_px)[i_ele], (*_recoele_py)[i_ele], (*_recoele_pz)[i_ele], (*_recoele_e)[i_ele]);
	loose_leptons.push_back(ele);
      }
      
      for(unsigned int i_lep=0; i_lep<loose_leptons.size(); i_lep++){
	TLorentzVector lep1 = loose_leptons[i_lep];
	for(unsigned int i_lep2=i_lep+1; i_lep2<loose_leptons.size(); i_lep2++){
	  TLorentzVector lep2 = loose_leptons[i_lep2];
	  if((lep1+lep2).M()<12){
	    //lep1.Print();
	    //lep2.Print();
	    inv_mass_lep_pairs=false;
	  }
	}
      }
      
      //cout<<"inv_mass_lep_pairs="<<inv_mass_lep_pairs<<endl;
      //if(!inv_mass_lep_pairs) continue;
      
      
      if(_n_recolep_mvasel<=2){
	
	bool inv_mass_Zee=true;
	
	for(unsigned int i_lep=0;i_lep<(*_recolep_charge).size();i_lep++){
	  
	  TLorentzVector lep1((*_recolep_px)[i_lep],(*_recolep_py)[i_lep],(*_recolep_pz)[i_lep],(*_recolep_e)[i_lep]);
	  
	  if(i_lep<2){
	    
	    _recolep_sel_charge.push_back((*_recolep_charge)[i_lep]);
	    _recolep_sel_pdg.push_back((*_recolep_pdg)[i_lep]);
	    _recolep_sel_e.push_back(lep1.E());
	    _recolep_sel_px.push_back(lep1.Px());
	    _recolep_sel_py.push_back(lep1.Py());
	    _recolep_sel_pz.push_back(lep1.Pz());
	    _recolep_sel_pt.push_back(lep1.Pt());
	    _recolep_sel_conept.push_back((*_recolep_conept)[i_lep]);
	    _recolep_sel_eta.push_back(lep1.Eta());
	    _recolep_sel_phi.push_back(lep1.Phi());
	    _recolep_sel_fakerate.push_back((*_recolep_fakerate)[i_lep]);
	    _recolep_sel_fakerate_QCD_MC.push_back((*_recolep_fakerate_QCD_MC)[i_lep]);
	    _recolep_sel_fakerate_ttbar_MC.push_back((*_recolep_fakerate_ttbar_MC)[i_lep]);
	    _recolep_sel_QFrate.push_back((*_recolep_QFrate)[i_lep]);
	    _recolep_sel_ismvasel.push_back((*_recolep_ismvasel)[i_lep]);
	    _recolep_sel_tightcharge.push_back((*_recolep_tightcharge)[i_lep]);
	    if(isMC){
	      _recolep_sel_isGenMatched.push_back((*_recolep_isGenMatched)[i_lep]);
	      _recolep_sel_genMatchInd.push_back((*_recolep_genMatchInd)[i_lep]);
	    }

	  }
	  
	  for(unsigned int i_lep2=i_lep+1; i_lep2<(*_recolep_charge).size();i_lep2++){
	    TLorentzVector lep2((*_recolep_px)[i_lep2],(*_recolep_py)[i_lep2],(*_recolep_pz)[i_lep2],(*_recolep_e)[i_lep2]);
	    float m_ll = (lep1 + lep2).M();
	    if(abs((*_recolep_pdg)[i_lep])==11 && abs((*_recolep_pdg)[i_lep2])==11 && fabs(m_ll-91.2)<10) inv_mass_Zee=false;
	    
	  }
	  
	}		
	
	
	for(unsigned int i_tau=0; i_tau<(*_recotauh_charge).size(); i_tau++){
	  
	  if((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]>0.5){
	    
	    _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
	    _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
	    
	    TLorentzVector tau_tlv((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
	    
	    _recotauh_sel_e.push_back(tau_tlv.E());
	    _recotauh_sel_px.push_back(tau_tlv.Px());
	    _recotauh_sel_py.push_back(tau_tlv.Py());
	    _recotauh_sel_pz.push_back(tau_tlv.Pz());
	    _recotauh_sel_pt.push_back(tau_tlv.Pt());
	    _recotauh_sel_eta.push_back(tau_tlv.Eta());
	    _recotauh_sel_phi.push_back(tau_tlv.Phi());
	    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	    _recotauh_sel_againstMuonTight3.push_back((*_recotauh_againstMuonTight3)[i_tau]);
	    _recotauh_sel_againstElectronVLooseMVA6.push_back((*_recotauh_againstElectronVLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronMediumMVA6.push_back((*_recotauh_againstElectronMediumMVA6)[i_tau]);
	    _recotauh_sel_againstElectronTightMVA6.push_back((*_recotauh_againstElectronTightMVA6)[i_tau]);
	    _recotauh_sel_againstElectronVTightMVA6.push_back((*_recotauh_againstElectronVTightMVA6)[i_tau]);
	    if(isMC){
	      _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);	  	  
	      _recotauh_sel_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);	  	  
	    }
	    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);

	  }

	}	  

	bool tau = _recotauh_sel_e.size()>0;

  
	if(!tau){

	  _recotauh_sel_charge.clear();
	  _recotauh_sel_decayMode.clear();
	  _recotauh_sel_e.clear();
	  _recotauh_sel_px.clear();
	  _recotauh_sel_py.clear();
	  _recotauh_sel_pz.clear();
	  _recotauh_sel_pt.clear();
	  _recotauh_sel_eta.clear();
	  _recotauh_sel_phi.clear();
	  _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  _recotauh_sel_againstMuonLoose3.clear();
	  _recotauh_sel_againstMuonTight3.clear();
	  _recotauh_sel_againstElectronVLooseMVA6.clear();
	  _recotauh_sel_againstElectronLooseMVA6.clear();
	  _recotauh_sel_againstElectronMediumMVA6.clear();
	  _recotauh_sel_againstElectronTightMVA6.clear();
	  _recotauh_sel_againstElectronVTightMVA6.clear();
	  _recotauh_sel_isGenMatched.clear();
	  _recotauh_sel_genMatchInd.clear();
	  _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  
	  for(unsigned int i_tau=0; i_tau<(*_recotauh_charge).size(); i_tau++){
	  	    
	    _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
	    _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
	    
	    TLorentzVector tau_tlv((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
	    
	    _recotauh_sel_e.push_back(tau_tlv.E());
	    _recotauh_sel_px.push_back(tau_tlv.Px());
	    _recotauh_sel_py.push_back(tau_tlv.Py());
	    _recotauh_sel_pz.push_back(tau_tlv.Pz());
	    _recotauh_sel_pt.push_back(tau_tlv.Pt());
	    _recotauh_sel_eta.push_back(tau_tlv.Eta());
	    _recotauh_sel_phi.push_back(tau_tlv.Phi());
	    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	    _recotauh_sel_againstMuonTight3.push_back((*_recotauh_againstMuonTight3)[i_tau]);
	    _recotauh_sel_againstElectronVLooseMVA6.push_back((*_recotauh_againstElectronVLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronMediumMVA6.push_back((*_recotauh_againstElectronMediumMVA6)[i_tau]);
	    _recotauh_sel_againstElectronTightMVA6.push_back((*_recotauh_againstElectronTightMVA6)[i_tau]);
	    _recotauh_sel_againstElectronVTightMVA6.push_back((*_recotauh_againstElectronVTightMVA6)[i_tau]);
	    if(isMC){
	      _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
	      _recotauh_sel_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);
	    }
	    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    
	    
	  }	

	}

	bool tau_fake = _recotauh_sel_e.size()>0;
	

	bool tight_mvasel = _recolep_sel_ismvasel[0]==1 && _recolep_sel_ismvasel[1]==1;
	bool lep_quality = _recolep_sel_tightcharge[0] && _recolep_sel_tightcharge[1];
	//bool pt_lep = ((_recolep_sel_conept[0]>25 && abs(_recolep_sel_pdg[0])==13) || (_recolep_sel_conept[0]>25 && abs(_recolep_sel_pdg[0])==11)) && ((_recolep_sel_conept[1]>10 && abs(_recolep_sel_pdg[1])==13) || (_recolep_sel_conept[1]>15 && abs(_recolep_sel_pdg[1])==11));
	bool pt_lep = ((_recolep_sel_pt[0]>25 && abs(_recolep_sel_pdg[0])==13) || (_recolep_sel_pt[0]>25 && abs(_recolep_sel_pdg[0])==11)) && ((_recolep_sel_pt[1]>10 && abs(_recolep_sel_pdg[1])==13) || (_recolep_sel_pt[1]>15 && abs(_recolep_sel_pdg[1])==11));
	bool SS_lep = _recolep_sel_charge[0]*_recolep_sel_charge[1]>0;
	bool SF_lep = abs(_recolep_sel_pdg[0])==abs(_recolep_sel_pdg[1]);
	bool metLD = (abs(_recolep_sel_pdg[0])==13 || abs(_recolep_sel_pdg[1])==13 || _ETmissLD>0.2);
	bool jetmult_sig = _n_recoPFJet>=3 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2);
	bool jetmult_CR_jets = _n_recoPFJet==2 && (_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2);
	bool jetmult_ttbar_OF = _n_recoPFJet>=2 && _n_recoPFJet_btag_medium>=1;
	if(isMC && tau_fake)
	  _isGenMatched = _recolep_sel_isGenMatched[0] && _recolep_sel_isGenMatched[1] && _recotauh_sel_isGenMatched[0];
	
	bool sig_2lSS = tight_mvasel && lep_quality && pt_lep && SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_sig;
	bool sig_2lSS_1tau = tight_mvasel && lep_quality && pt_lep && SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_sig && tau;
	bool lepMVA_CR = !tight_mvasel && lep_quality && pt_lep && SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_sig;
	bool tau_fake_CR = tau_fake && !tau && lep_quality && pt_lep && SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_sig;
	bool sig_2lOS_CR = tight_mvasel && lep_quality && pt_lep && !SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_sig;
	bool jetmult_CR = tight_mvasel && lep_quality && pt_lep && SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_CR_jets;
	bool ttbarOF_CR = tight_mvasel && lep_quality && pt_lep && !SS_lep && !SF_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_ttbar_OF;
	
	bool CR_2jets_tau = tau_fake && lep_quality && pt_lep && SS_lep && inv_mass_lep_pairs && inv_mass_Zee && metLD && jetmult_CR_jets;

	/*cout<<"tight_mvasel="<<tight_mvasel<<endl;
	cout<<"lep_quality="<<lep_quality<<endl;
	cout<<"pt_lep="<<pt_lep<<endl;
	cout<<"SS_lep="<<SS_lep<<endl;
	cout<<"inv_mass_lep_pairs="<<inv_mass_lep_pairs<<endl;
	cout<<"inv_mass_Zee="<<inv_mass_Zee<<endl;
	cout<<"metLD="<<metLD<<endl;
	cout<<"jetmult_sig="<<jetmult_sig<<endl;*/
	
	_event_weight_ttH = 1;
	_event_weight_ttH_FR_QCD_MC = 1;
	_event_weight_ttH_FR_TT_MC = 1;
	_event_weight_ttH_ele_FR_QCD_MC = 1;
	_event_weight_ttH_ele_FR_TT_MC = 1;
	_event_weight_ttH_mu_FR_QCD_MC = 1;
	_event_weight_ttH_mu_FR_TT_MC = 1;
	_triggerSF_weight = 1;
	_triggerSF_weight_up = 1;
	_triggerSF_weight_down = 1;
	_leptonSF_ttH_weight = 1;
	_tauSF_weight = 1;

	
	if(_recolep_sel_charge[0]*_recolep_sel_charge[1]<0)
	  _event_weight_ttH = _recolep_sel_QFrate[0]+_recolep_sel_QFrate[1];
	

	int n_fake = 0;

	if(!_recolep_sel_ismvasel[0]){
	    _event_weight_ttH *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	    _event_weight_ttH_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	    _event_weight_ttH_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);

	    if(abs(_recolep_sel_pdg[0])==11){
	      _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	      _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);
	      _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	      _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	    }
	    
	    else if(abs(_recolep_sel_pdg[0])==13){
	      _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	      _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	      _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	      _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);
	    }
	    
	    
	    n_fake++;
	    _n_fake_lep++;
	}


	if(!_recolep_sel_ismvasel[1]){
	    _event_weight_ttH *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	    _event_weight_ttH_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[1]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	    _event_weight_ttH_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[1]/(1-_recolep_sel_fakerate_ttbar_MC[1]);

	    if(abs(_recolep_sel_pdg[1])==11){
	      _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[1]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	      _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[1]/(1-_recolep_sel_fakerate_ttbar_MC[1]);
	      _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	      _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	    }
	    
	    else if(abs(_recolep_sel_pdg[1])==13){
	      _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	      _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	      _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[1]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	      _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[1]/(1-_recolep_sel_fakerate_ttbar_MC[1]);
	    }

	    n_fake++;
	    _n_fake_lep++;
	}	
	
	
	if(tau_fake){
	  if(!_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0]){
	    float weight_tau = _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0]/(1-_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0]);
	    _event_weight_ttH *= weight_tau;
	    _event_weight_ttH_FR_QCD_MC *= weight_tau;
	    _event_weight_ttH_FR_TT_MC *= weight_tau;
	    _event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	    _event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	    _event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	    _event_weight_ttH_mu_FR_TT_MC *= weight_tau;

	    n_fake++;
	    _n_fake_tau++;
	  }
	}
      
	if(n_fake>0 && n_fake%2==0){
	  _event_weight_ttH *=-1;
	  _event_weight_ttH_FR_QCD_MC *=-1;
	  _event_weight_ttH_FR_TT_MC *=-1;
	  _event_weight_ttH_ele_FR_QCD_MC *= -1;
	  _event_weight_ttH_ele_FR_TT_MC *= -1;
	  _event_weight_ttH_mu_FR_TT_MC *= -1;
	  _event_weight_ttH_mu_FR_TT_MC *= -1;
	}

	
	if(!isReHLT)
	  _triggerSF_weight = triggerSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],
					    _recolep_sel_pdg[1],_recolep_sel_pt[1],
					    2);
	else{
	  if(abs(_recolep_sel_pdg[0])==11 && abs(_recolep_sel_pdg[1])==11){
	    _triggerSF_weight = 1.02;
	    _triggerSF_weight_up = 1.04;
	    _triggerSF_weight_down = 1.0;
	  }
	  else if(abs(_recolep_sel_pdg[0])==11 || abs(_recolep_sel_pdg[1])==11){
	    _triggerSF_weight = 1.02;
	    _triggerSF_weight_up = 1.03;
	    _triggerSF_weight_down = 1.01;
	  }
	  else{
	    _triggerSF_weight = 1.01;
	    _triggerSF_weight_up = 1.02;
	    _triggerSF_weight_down = 1.0;
	  }
	}


	/*if(tight_mvasel)
	  _leptonSF_ttH_weight = leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],2)
	  * leptonSF_ttH(_recolep_sel_pdg[1],_recolep_sel_pt[1],_recolep_sel_eta[1],2);*/

	if(_recolep_sel_ismvasel[0])
	  _leptonSF_ttH_weight *= leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],2);
	else
	  _leptonSF_ttH_weight *= _get_recoToLoose_leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],2);

	if(_recolep_sel_ismvasel[1])
	  _leptonSF_ttH_weight *= leptonSF_ttH(_recolep_sel_pdg[1],_recolep_sel_pt[1],_recolep_sel_eta[1],2);
	else
	  _leptonSF_ttH_weight *= _get_recoToLoose_leptonSF_ttH(_recolep_sel_pdg[1],_recolep_sel_pt[1],_recolep_sel_eta[1],2);
	

	if(isMC && tau_fake)
	  _tauSF_weight = (1-0.1*_recotauh_sel_isGenMatched[0]);

	
	//2lSS + tauh
	if(tau_fake){
	  
	  if(_recolep_sel_charge[0]*_recolep_sel_charge[1]>0){
	    if(tight_mvasel && tau)
	      _category = 11;
	    else
	      _category = 41;	    
	  }
	  
	  else if(_recolep_sel_charge[0]*_recolep_sel_charge[1]<0 && tight_mvasel && tau)
	    _category = -11;
	  
	}
	
	//MuMu
	else if(abs(_recolep_sel_pdg[0])==13 && abs(_recolep_sel_pdg[1])==13){
	  
	  if(_n_recoPFJet_btag_medium>=2){
	    
	    if(_recolep_sel_charge[0]+_recolep_sel_charge[1]>0){
	      if(tight_mvasel)
		_category = 1;
	      else
		_category = 31;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]<0){
	      if(tight_mvasel)
		_category = 2;
	      else
		_category = 32;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]==0 && tight_mvasel)
	      _category = -1;
	    
	  }
	  
	  else{
	    
	    if(_recolep_sel_charge[0]+_recolep_sel_charge[1]>0){
	      if(tight_mvasel)
		_category = 3;
	      else
		_category = 33;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]<0){
	      if(tight_mvasel)
		_category = 4;
	      else
		_category = 34;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]==0 && tight_mvasel)
	      _category = -3;
	    
	  }
	}
	
	//EMu
	else if((abs(_recolep_sel_pdg[0])==13 && abs(_recolep_sel_pdg[1])==11) || (abs(_recolep_sel_pdg[0])==11 && abs(_recolep_sel_pdg[1])==13)){
	  
	  if(_n_recoPFJet_btag_medium>=2){
	    
	    if(_recolep_sel_charge[0]+_recolep_sel_charge[1]>0){
	      if(tight_mvasel)
		_category = 5;
	      else
		_category = 35;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]<0){
	      if(tight_mvasel)
		_category = 6;
	      else
		_category = 36;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]==0 && tight_mvasel){
	      if(_recolep_sel_pdg[0]==-13 || _recolep_sel_pdg[1]==-13)
		_category = -5;
	      else if(_recolep_sel_pdg[0]==13 || _recolep_sel_pdg[1]==13)
		_category = -6;
	    }
	  }
	  
	  else{
	    
	    if(_recolep_sel_charge[0]+_recolep_sel_charge[1]>0){
	      if(tight_mvasel)
		_category = 7;
	      else
		_category = 37;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]<0){
	      if(tight_mvasel)
		_category = 8;
	      else
		_category = 38;
	    }
	    
	    else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]==0 && tight_mvasel){
	      if(_recolep_sel_pdg[0]==-13 || _recolep_sel_pdg[1]==-13)
		_category = -7;
	      else if(_recolep_sel_pdg[0]==13 || _recolep_sel_pdg[1]==13)
		_category = -8;
	    }
	    
	  }
	}
	
	//EE
	else if(abs(_recolep_sel_pdg[0])==11 && abs(_recolep_sel_pdg[1])==11){
	  
	  if(_recolep_sel_charge[0]+_recolep_sel_charge[1]>0){
	    if(tight_mvasel)
	      _category = 9;
	    else
	      _category = 39;
	  }
	  
	  else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]<0){
	    if(tight_mvasel)
	      _category = 10;
	    else
	      _category = 40;
	  }
	  
	  else if(_recolep_sel_charge[0]+_recolep_sel_charge[1]==0 && tight_mvasel){
	    if(_recolep_sel_charge[0]>0)
	      _category = -9;
	    else
	      _category = -10;
	  }
	  
	}
	
	
	
	/*if(sig_2lSS_1tau)
	  tree_2lSS->Fill();
	else if(lepMVA_CR || tau_fake_CR)
	  tree_2lSS_lepMVA_CR->Fill();
	else if(sig_2lOS_CR)
	  tree_2lOS_CR->Fill();
	else if(jetmult_CR)
	  tree_2lSS_jetmult_CR->Fill(); 
	else if(ttbarOF_CR)
	  tree_2lSS_ttbarOF_CR->Fill();      
	
	if(CR_2jets_tau)
	tree_2lSS_2jet_CR->Fill();*/

	_category = 11;
	if(_recotauh_sel_pt.size()>0)
	  tree_2lSS->Fill();
	
      }
         

      
      _recolep_sel_charge.clear();
      _recolep_sel_pdg.clear();
      _recolep_sel_e.clear();
      _recolep_sel_px.clear();
      _recolep_sel_py.clear();
      _recolep_sel_pz.clear();
      _recolep_sel_pt.clear();
      _recolep_sel_conept.clear();
      _recolep_sel_eta.clear();
      _recolep_sel_phi.clear();
      _recolep_sel_fakerate.clear();
      _recolep_sel_fakerate_QCD_MC.clear();
      _recolep_sel_fakerate_ttbar_MC.clear();
      _recolep_sel_QFrate.clear(); 
      _recolep_sel_ismvasel.clear();
      _recolep_sel_tightcharge.clear();
      _recolep_sel_isGenMatched.clear();
      _recolep_sel_genMatchInd.clear();

      _recotauh_sel_charge.clear();
      _recotauh_sel_decayMode.clear();    
      _recotauh_sel_e.clear();
      _recotauh_sel_px.clear();
      _recotauh_sel_py.clear();
      _recotauh_sel_pz.clear();
      _recotauh_sel_pt.clear();
      _recotauh_sel_eta.clear();
      _recotauh_sel_phi.clear();
      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_againstMuonLoose3.clear();
      _recotauh_sel_againstMuonTight3.clear();
      _recotauh_sel_againstElectronVLooseMVA6.clear();
      _recotauh_sel_againstElectronLooseMVA6.clear();
      _recotauh_sel_againstElectronMediumMVA6.clear();
      _recotauh_sel_againstElectronTightMVA6.clear();
      _recotauh_sel_againstElectronVTightMVA6.clear();
      _recotauh_sel_isGenMatched.clear();
      _recotauh_sel_genMatchInd.clear();
      _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
      
      _n_fake_lep = 0;
      _n_fake_tau = 0;
     
     

      if(_n_recolep_fakeable>=3){  
                 
	bool inv_mass_Z=true;
	bool SFOS_pair=false;
	
	for(unsigned int i_lep=0;i_lep<(*_recolep_charge).size();i_lep++){
	  
	  TLorentzVector lep1((*_recolep_px)[i_lep],(*_recolep_py)[i_lep],(*_recolep_pz)[i_lep],(*_recolep_e)[i_lep]);
	  
	  if(i_lep<3){
	    
	    _recolep_sel_charge.push_back((*_recolep_charge)[i_lep]);
	    _recolep_sel_pdg.push_back((*_recolep_pdg)[i_lep]);
	    _recolep_sel_e.push_back(lep1.E());
	    _recolep_sel_px.push_back(lep1.Px());
	    _recolep_sel_py.push_back(lep1.Py());
	    _recolep_sel_pz.push_back(lep1.Pz());
	    _recolep_sel_pt.push_back(lep1.Pt());
	    _recolep_sel_conept.push_back((*_recolep_conept)[i_lep]);
	    _recolep_sel_eta.push_back(lep1.Eta());
	    _recolep_sel_phi.push_back(lep1.Phi());
	    _recolep_sel_fakerate.push_back((*_recolep_fakerate)[i_lep]);
	    _recolep_sel_fakerate_QCD_MC.push_back((*_recolep_fakerate_QCD_MC)[i_lep]);
	    _recolep_sel_fakerate_ttbar_MC.push_back((*_recolep_fakerate_ttbar_MC)[i_lep]);
	    _recolep_sel_QFrate.push_back((*_recolep_QFrate)[i_lep]);
	    _recolep_sel_ismvasel.push_back((*_recolep_ismvasel)[i_lep]);
	    if(isMC){	      
	      _recolep_sel_isGenMatched.push_back((*_recolep_isGenMatched)[i_lep]);	    
	      _recolep_sel_genMatchInd.push_back((*_recolep_genMatchInd)[i_lep]);	    
	    }
	    
	  }
	  
	  for(unsigned int i_lep2=i_lep+1; i_lep2<(*_recolep_charge).size();i_lep2++){
	    TLorentzVector lep2((*_recolep_px)[i_lep2],(*_recolep_py)[i_lep2],(*_recolep_pz)[i_lep2],(*_recolep_e)[i_lep2]);
	    float m_ll = (lep1 + lep2).M();
	    if((*_recolep_pdg)[i_lep]==-(*_recolep_pdg)[i_lep2]){
	      SFOS_pair=true;
	      if(fabs(m_ll-91.2)<10) inv_mass_Z=false;
	    }
	  }
	  
	}
	

	for(unsigned int i_tau=0; i_tau<(*_recotauh_charge).size(); i_tau++){
	  
	  if((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]>0.5){
	    
	    _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
	    _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
	    
	    TLorentzVector tau_tlv((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
	    
	    _recotauh_sel_e.push_back(tau_tlv.E());
	    _recotauh_sel_px.push_back(tau_tlv.Px());
	    _recotauh_sel_py.push_back(tau_tlv.Py());
	    _recotauh_sel_pz.push_back(tau_tlv.Pz());
	    _recotauh_sel_pt.push_back(tau_tlv.Pt());
	    _recotauh_sel_eta.push_back(tau_tlv.Eta());
	    _recotauh_sel_phi.push_back(tau_tlv.Phi());
	    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	    _recotauh_sel_againstMuonTight3.push_back((*_recotauh_againstMuonTight3)[i_tau]);
	    _recotauh_sel_againstElectronVLooseMVA6.push_back((*_recotauh_againstElectronVLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronMediumMVA6.push_back((*_recotauh_againstElectronMediumMVA6)[i_tau]);
	    _recotauh_sel_againstElectronTightMVA6.push_back((*_recotauh_againstElectronTightMVA6)[i_tau]);
	    _recotauh_sel_againstElectronVTightMVA6.push_back((*_recotauh_againstElectronVTightMVA6)[i_tau]);
	    if(isMC){	      
	      _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);	  	  
	      _recotauh_sel_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);	  	  
	    }
	    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);

	  }

	}	  

	bool tau = _recotauh_sel_e.size()>0;

  
	if(!tau){

	  _recotauh_sel_charge.clear();
	  _recotauh_sel_decayMode.clear();
	  _recotauh_sel_e.clear();
	  _recotauh_sel_px.clear();
	  _recotauh_sel_py.clear();
	  _recotauh_sel_pz.clear();
	  _recotauh_sel_pt.clear();
	  _recotauh_sel_eta.clear();
	  _recotauh_sel_phi.clear();
	  _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  _recotauh_sel_againstMuonLoose3.clear();
	  _recotauh_sel_againstMuonTight3.clear();
	  _recotauh_sel_againstElectronVLooseMVA6.clear();
	  _recotauh_sel_againstElectronLooseMVA6.clear();
	  _recotauh_sel_againstElectronMediumMVA6.clear();
	  _recotauh_sel_againstElectronTightMVA6.clear();
	  _recotauh_sel_againstElectronVTightMVA6.clear();
	  _recotauh_sel_isGenMatched.clear();
	  _recotauh_sel_genMatchInd.clear();
	  _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
	  _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();

	  for(unsigned int i_tau=0; i_tau<(*_recotauh_charge).size(); i_tau++){
	  	    
	    _recotauh_sel_charge.push_back((*_recotauh_charge)[i_tau]);
	    _recotauh_sel_decayMode.push_back((*_recotauh_decayMode)[i_tau]);
	    
	    TLorentzVector tau_tlv((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);
	    
	    _recotauh_sel_e.push_back(tau_tlv.E());
	    _recotauh_sel_px.push_back(tau_tlv.Px());
	    _recotauh_sel_py.push_back(tau_tlv.Py());
	    _recotauh_sel_pz.push_back(tau_tlv.Pz());
	    _recotauh_sel_pt.push_back(tau_tlv.Pt());
	    _recotauh_sel_eta.push_back(tau_tlv.Eta());
	    _recotauh_sel_phi.push_back(tau_tlv.Phi());
	    _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	    _recotauh_sel_againstMuonTight3.push_back((*_recotauh_againstMuonTight3)[i_tau]);
	    _recotauh_sel_againstElectronVLooseMVA6.push_back((*_recotauh_againstElectronVLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	    _recotauh_sel_againstElectronMediumMVA6.push_back((*_recotauh_againstElectronMediumMVA6)[i_tau]);
	    _recotauh_sel_againstElectronTightMVA6.push_back((*_recotauh_againstElectronTightMVA6)[i_tau]);
	    _recotauh_sel_againstElectronVTightMVA6.push_back((*_recotauh_againstElectronVTightMVA6)[i_tau]);
	    if(isMC){
	      _recotauh_sel_isGenMatched.push_back((*_recotauh_isGenMatched)[i_tau]);
	      _recotauh_sel_genMatchInd.push_back((*_recotauh_genMatchInd)[i_tau]);
	    }
	    _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);
	    _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back((*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]);	    
      
	    
	  }	

	}

	bool tau_fake = _recotauh_sel_e.size()>0;
	
	bool tight_mvasel = _recolep_sel_ismvasel[0]==1 && _recolep_sel_ismvasel[1]==1 && _recolep_sel_ismvasel[2]==1;
	//bool pt_lep = _recolep_sel_conept[0]>20 && _recolep_sel_conept[1]>10 && _recolep_sel_conept[2]>10;
	bool pt_lep = _recolep_sel_pt[0]>20 && _recolep_sel_pt[1]>10 && _recolep_sel_pt[2]>10;
	bool metLD = _ETmissLD>0.2 || _n_recoPFJet>=4;
	if(SFOS_pair)
	  metLD = _ETmissLD>0.3 || _n_recoPFJet>=4;
	bool three_charge = abs(_recolep_sel_charge[0]+_recolep_sel_charge[1]+_recolep_sel_charge[2])==1;
	bool jetmult_sig = _n_recoPFJet>=2 && (_n_recoPFJet_btag_loose>=2 || _n_recoPFJet_btag_medium>=1);
	bool jetmult_WZ = _n_recoPFJet>=2 && _n_recoPFJet_btag_medium==0;
	bool jetmult_ttZ = _n_recoPFJet>=2 && _n_recoPFJet_btag_medium>=1 && _n_recoPFJet_btag_loose>=2;
	if(isMC && tau_fake)
	  _isGenMatched = _recolep_sel_isGenMatched[0] && _recolep_sel_isGenMatched[1] && _recolep_sel_isGenMatched[2] && _recotauh_sel_isGenMatched[0];
	

	bool sig_3l = tight_mvasel && pt_lep && inv_mass_lep_pairs && inv_mass_Z && metLD && three_charge && jetmult_sig; //&& isGenMatched;
	bool sig_3l_1tau = tight_mvasel && pt_lep && inv_mass_lep_pairs && inv_mass_Z && metLD && three_charge && jetmult_sig && tau; //&& isGenMatched;
	bool lepMVA_CR = !tight_mvasel && pt_lep && inv_mass_lep_pairs && inv_mass_Z && metLD && three_charge && jetmult_sig;
	bool tau_fake_CR = !tau && tau_fake && pt_lep && inv_mass_lep_pairs && inv_mass_Z && metLD && three_charge && jetmult_sig;
	bool WZ_CR = tight_mvasel && pt_lep && inv_mass_lep_pairs && !inv_mass_Z && metLD && three_charge && jetmult_WZ;
	bool ttZ_CR = tight_mvasel && pt_lep && inv_mass_lep_pairs && !inv_mass_Z && metLD && three_charge && jetmult_ttZ;
	bool ttZ_lepMVA_CR = !tight_mvasel && pt_lep && inv_mass_lep_pairs && !inv_mass_Z && metLD && three_charge && jetmult_ttZ;
	
	_event_weight_ttH = 1;
	_event_weight_ttH_FR_QCD_MC = 1;
	_event_weight_ttH_FR_TT_MC = 1;
	_event_weight_ttH_ele_FR_QCD_MC = 1;
	_event_weight_ttH_ele_FR_TT_MC = 1;
	_event_weight_ttH_mu_FR_QCD_MC = 1;
	_event_weight_ttH_mu_FR_TT_MC = 1;
	_triggerSF_weight = 1;
	_triggerSF_weight_up = 1;
	_triggerSF_weight_down = 1;
	_leptonSF_ttH_weight = 1;
	_tauSF_weight = 1;

	int n_fake = 0;

	if(!_recolep_sel_ismvasel[0]){
	  _event_weight_ttH *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	  _event_weight_ttH_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	  _event_weight_ttH_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);

	  if(abs(_recolep_sel_pdg[0])==11){
	    _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	    _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);
	    _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	    _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	  }
	  
	  else if(abs(_recolep_sel_pdg[0])==13){
	    _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	    _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate[0]/(1-_recolep_sel_fakerate[0]);
	    _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[0]/(1-_recolep_sel_fakerate_QCD_MC[0]);
	    _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[0]/(1-_recolep_sel_fakerate_ttbar_MC[0]);
	  }

	  n_fake++;
	  _n_fake_lep++;
	}


	if(!_recolep_sel_ismvasel[1]){
	  _event_weight_ttH *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	  _event_weight_ttH_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[1]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	  _event_weight_ttH_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[1]/(1-_recolep_sel_fakerate_ttbar_MC[1]);

	  if(abs(_recolep_sel_pdg[1])==11){
	    _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[1]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	    _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[1]/(1-_recolep_sel_fakerate_ttbar_MC[1]);
	    _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	    _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	  }
	  
	  else if(abs(_recolep_sel_pdg[1])==13){
	    _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	    _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate[1]/(1-_recolep_sel_fakerate[1]);
	    _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[1]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	    _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[1]/(1-_recolep_sel_fakerate_ttbar_MC[1]);
	  }

	  n_fake++;
	  _n_fake_lep++;
	}

	if(!_recolep_sel_ismvasel[2]){
	  _event_weight_ttH *= _recolep_sel_fakerate[2]/(1-_recolep_sel_fakerate[2]);
	  _event_weight_ttH_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[2]/(1-_recolep_sel_fakerate_QCD_MC[1]);
	  _event_weight_ttH_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[2]/(1-_recolep_sel_fakerate_ttbar_MC[1]);

	  if(abs(_recolep_sel_pdg[2])==11){
	    _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[2]/(1-_recolep_sel_fakerate_QCD_MC[2]);
	    _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[2]/(1-_recolep_sel_fakerate_ttbar_MC[2]);
	    _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate[2]/(1-_recolep_sel_fakerate[2]);
	    _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate[2]/(1-_recolep_sel_fakerate[2]);
	  }

	  else if(abs(_recolep_sel_pdg[2])==13){
	    _event_weight_ttH_ele_FR_QCD_MC *= _recolep_sel_fakerate[2]/(1-_recolep_sel_fakerate[2]);
	    _event_weight_ttH_ele_FR_TT_MC *= _recolep_sel_fakerate[2]/(1-_recolep_sel_fakerate[2]);
	    _event_weight_ttH_mu_FR_QCD_MC *= _recolep_sel_fakerate_QCD_MC[2]/(1-_recolep_sel_fakerate_QCD_MC[2]);
	    _event_weight_ttH_mu_FR_TT_MC *= _recolep_sel_fakerate_ttbar_MC[2]/(1-_recolep_sel_fakerate_ttbar_MC[2]);
	  }

	  n_fake++;
	  _n_fake_lep++;
	}	
	
	if(tau_fake){	
	  if(!_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0]){
	    float weight_tau = _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0]/(1-_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0]);
	    _event_weight_ttH *= weight_tau;
	    _event_weight_ttH_FR_QCD_MC *= weight_tau;
	    _event_weight_ttH_FR_TT_MC *= weight_tau;
	    _event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	    _event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	    _event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	    _event_weight_ttH_mu_FR_TT_MC *= weight_tau;
	    n_fake++;
	    _n_fake_tau++;
	  }
	}	  

	if(n_fake>0 && n_fake%2==0){
	  _event_weight_ttH *=-1;
	  _event_weight_ttH_FR_QCD_MC *=-1;
	  _event_weight_ttH_FR_TT_MC *=-1;
	  _event_weight_ttH_ele_FR_QCD_MC *= -1;
	  _event_weight_ttH_ele_FR_TT_MC *= -1;
	  _event_weight_ttH_mu_FR_TT_MC *= -1;
	  _event_weight_ttH_mu_FR_TT_MC *= -1;
	}

	if(!isReHLT)
	  _triggerSF_weight = triggerSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],
					    _recolep_sel_pdg[1],_recolep_sel_pt[1],
					    3);
	
	else{
	  _triggerSF_weight = 1.;
	  _triggerSF_weight_up = 1.06;
	  _triggerSF_weight_down = 0.94;
	}

	/*if(tight_mvasel)
	  _leptonSF_ttH_weight = leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],3)
	    * leptonSF_ttH(_recolep_sel_pdg[1],_recolep_sel_pt[1],_recolep_sel_eta[1],3)
	    * leptonSF_ttH(_recolep_sel_pdg[2],_recolep_sel_pt[2],_recolep_sel_eta[2],3);*/

	if(_recolep_sel_ismvasel[0])
	  _leptonSF_ttH_weight *= leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],2);
	else
	  _leptonSF_ttH_weight *= _get_recoToLoose_leptonSF_ttH(_recolep_sel_pdg[0],_recolep_sel_pt[0],_recolep_sel_eta[0],2);


	if(_recolep_sel_ismvasel[1])
	  _leptonSF_ttH_weight *= leptonSF_ttH(_recolep_sel_pdg[1],_recolep_sel_pt[1],_recolep_sel_eta[1],2);
	else
	  _leptonSF_ttH_weight *= _get_recoToLoose_leptonSF_ttH(_recolep_sel_pdg[1],_recolep_sel_pt[1],_recolep_sel_eta[1],2);


	if(_recolep_sel_ismvasel[2])
	  _leptonSF_ttH_weight *= leptonSF_ttH(_recolep_sel_pdg[2],_recolep_sel_pt[2],_recolep_sel_eta[2],2);
	else
	  _leptonSF_ttH_weight *= _get_recoToLoose_leptonSF_ttH(_recolep_sel_pdg[2],_recolep_sel_pt[2],_recolep_sel_eta[2],2);

		
	if(isMC && tau_fake)
	  _tauSF_weight = (1-0.1*_recotauh_sel_isGenMatched[0]);
      
      

	//if(tau){
	if(tau_fake){
	  
	  if(tight_mvasel && tau)
	    _category = 16;
	  else
	    _category = 46;	    
	  
	}
      
      
	else{
	  
	  if(_n_recoPFJet_btag_medium>=2){
	    
	    if(_recolep_sel_charge[0]+_recolep_sel_charge[1]+_recolep_sel_charge[2]>0){
	      if(tight_mvasel)
		_category = 12;
	      else
		_category = 42;
	    }
	    
	    else{
	      if(tight_mvasel)
		_category = 13;
	      else
		_category = 43;
	    }
	    
	  }
	
	  else{
	    
	    if(_recolep_sel_charge[0]+_recolep_sel_charge[1]+_recolep_sel_charge[2]>0){
	      if(tight_mvasel)
		_category = 14;
	      else
		_category = 44;
	    }
	    
	    else{
	      if(tight_mvasel)
		_category = 15;
	      else
		_category = 45;
	    }
	    
	  }
	  
	}
	
      
	
	if(sig_3l_1tau)
	  tree_3l->Fill();
	else if(lepMVA_CR || tau_fake_CR){
	  tree_3l_lepMVA_CR->Fill();
	}
	else if(WZ_CR)
	  tree_3l_WZ_CR->Fill(); 
	else if(ttZ_CR)
	  tree_3l_ttZ_CR->Fill(); 
	else if(ttZ_lepMVA_CR)
	  tree_3l_ttZ_lepMVA_CR->Fill(); 
	
      }

    

    }

  }


  f_new->cd();
  
  h->Write();

  for(unsigned int i=0; i<tree_new.size();i++)
    tree_new[i]->Write();



  f_new->Close();
  return;

}
