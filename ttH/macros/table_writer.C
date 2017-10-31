#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <TString.h>
#include <TChain.h>

using namespace std;

void write_mu_log(){

  std::ofstream out("mu_8020_ttW.txt");

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_ttW_multilep.root";

  TChain * tree = new TChain("syncTree");
  tree->Add(file);

  ULong64_t _nEvent;
  int _n_presel_mu;
  float _mu0_pt;
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

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("n_presel_mu",&_n_presel_mu);
  tree->SetBranchAddress("mu0_pt",&_mu0_pt);
  tree->SetBranchAddress("mu0_eta",&_mu0_eta);
  tree->SetBranchAddress("mu0_phi",&_mu0_phi);
  tree->SetBranchAddress("mu0_E",&_mu0_E);
  tree->SetBranchAddress("mu0_charge",&_mu0_charge);
  tree->SetBranchAddress("mu0_jetNDauChargedMVASel",&_mu0_jetNDauChargedMVASel);
  tree->SetBranchAddress("mu0_miniRelIso",&_mu0_miniRelIso);
  tree->SetBranchAddress("mu0_miniIsoCharged",&_mu0_miniIsoCharged);
  tree->SetBranchAddress("mu0_miniIsoNeutral",&_mu0_miniIsoNeutral);
  tree->SetBranchAddress("mu0_jetPtRel",&_mu0_jetPtRel);
  tree->SetBranchAddress("mu0_jetPtRatio",&_mu0_jetPtRatio);
  tree->SetBranchAddress("mu0_jetCSV",&_mu0_jetCSV);
  tree->SetBranchAddress("mu0_sip3D",&_mu0_sip3D);
  tree->SetBranchAddress("mu0_dxy",&_mu0_dxy);
  tree->SetBranchAddress("mu0_dz",&_mu0_dz);
  tree->SetBranchAddress("mu0_segmentCompatibility",&_mu0_segmentCompatibility);
  tree->SetBranchAddress("mu0_leptonMVA",&_mu0_leptonMVA);



  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);
  
    if(_n_presel_mu==0) continue;

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_pt<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_eta<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_phi<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_E<<" ";
    out<<(-13*_mu0_charge)<<" ";
    out<<_mu0_charge<<" ";
    out<<_mu0_jetNDauChargedMVASel<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_miniRelIso<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_miniIsoCharged<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_miniIsoNeutral<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_jetPtRel<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_jetCSV<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_jetPtRatio<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_sip3D<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_dxy<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_dz<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_segmentCompatibility<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mu0_leptonMVA<<endl;
    
  }


  return;


}






void write_ele_log(){

  std::ofstream out("ele_8020_ttW.txt");


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_ttW_multilep.root";

  TChain * tree = new TChain("syncTree");
  tree->Add(file);

  ULong64_t _nEvent;
  int _n_presel_ele;
  float _ele0_pt;
  float _ele0_eta;
  float _ele0_phi;
  float _ele0_E;
  int _ele0_charge;
  int _ele0_jetNDauChargedMVASel;
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

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("n_presel_ele",&_n_presel_ele);
  tree->SetBranchAddress("ele0_pt",&_ele0_pt);
  tree->SetBranchAddress("ele0_eta",&_ele0_eta);
  tree->SetBranchAddress("ele0_phi",&_ele0_phi);
  tree->SetBranchAddress("ele0_E",&_ele0_E);
  tree->SetBranchAddress("ele0_charge",&_ele0_charge);
  tree->SetBranchAddress("ele0_jetNDauChargedMVASel",&_ele0_jetNDauChargedMVASel);
  tree->SetBranchAddress("ele0_miniRelIso",&_ele0_miniRelIso);
  tree->SetBranchAddress("ele0_miniIsoCharged",&_ele0_miniIsoCharged);
  tree->SetBranchAddress("ele0_miniIsoNeutral",&_ele0_miniIsoNeutral);
  tree->SetBranchAddress("ele0_jetPtRel",&_ele0_jetPtRel);
  tree->SetBranchAddress("ele0_jetPtRatio",&_ele0_jetPtRatio);
  tree->SetBranchAddress("ele0_jetCSV",&_ele0_jetCSV);
  tree->SetBranchAddress("ele0_sip3D",&_ele0_sip3D);
  tree->SetBranchAddress("ele0_dxy",&_ele0_dxy);
  tree->SetBranchAddress("ele0_dz",&_ele0_dz);
  tree->SetBranchAddress("ele0_ntMVAeleID",&_ele0_ntMVAeleID);
  tree->SetBranchAddress("ele0_leptonMVA",&_ele0_leptonMVA);



  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);
  
    if(_n_presel_ele==0) continue;


    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_pt<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_eta<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_phi<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_E<<" ";
    out<<(-11*_ele0_charge)<<" ";
    out<<_ele0_charge<<" ";
    out<<_ele0_jetNDauChargedMVASel<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_miniRelIso<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_miniIsoCharged<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_miniIsoNeutral<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_jetPtRel<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_jetCSV<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_jetPtRatio<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_sip3D<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_dxy<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_dz<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_ntMVAeleID<<" ";
    out<<std::fixed<<std::setprecision(5)<<_ele0_leptonMVA<<endl;
 

  }


  return;


}








void write_tau_log(){


  std::ofstream out("tau_8020_ttW.txt");

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_ttW_multilep.root";


  TChain * tree = new TChain("syncTree");
  tree->Add(file);

  ULong64_t _nEvent;
  int _n_presel_tau;
  float _tau0_pt;
  float _tau0_eta;
  float _tau0_phi;
  float _tau0_E;
  int _tau0_charge;
  float _tau0_dxy;
  float _tau0_dz;
  int _tau0_decayModeFindingOldDMs;
  int _tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("n_presel_tau",&_n_presel_tau);
  tree->SetBranchAddress("tau0_pt",&_tau0_pt);
  tree->SetBranchAddress("tau0_eta",&_tau0_eta);
  tree->SetBranchAddress("tau0_phi",&_tau0_phi);
  tree->SetBranchAddress("tau0_E",&_tau0_E);
  tree->SetBranchAddress("tau0_charge",&_tau0_charge);
  tree->SetBranchAddress("tau0_dxy",&_tau0_dxy);
  tree->SetBranchAddress("tau0_dz",&_tau0_dz);
  tree->SetBranchAddress("tau0_decayModeFindingOldDMs",&_tau0_decayModeFindingOldDMs);
  tree->SetBranchAddress("tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT);



  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);
  
    if(_n_presel_tau==0) continue;

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_tau0_pt<<" ";
    out<<std::fixed<<std::setprecision(5)<<_tau0_eta<<" ";
    out<<std::fixed<<std::setprecision(5)<<_tau0_phi<<" ";
    out<<std::fixed<<std::setprecision(5)<<_tau0_E<<" ";
    out<<_tau0_charge<<" ";
    out<<std::fixed<<std::setprecision(5)<<_tau0_dxy<<" ";
    out<<std::fixed<<std::setprecision(5)<<_tau0_dz<<" ";
    out<<_tau0_decayModeFindingOldDMs<<" ";
    out<<_tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT<<endl;

  }


  return;


}








void write_jet_log(){


  std::ofstream out("jet_8020_ttW.txt");

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_ttW_multilep.root";


  TChain * tree = new TChain("syncTree");
  tree->Add(file);

  ULong64_t _nEvent;
  int _n_presel_jet;
  float _jet0_pt;
  float _jet0_eta;
  float _jet0_phi;
  float _jet0_E;
  float _jet0_CSV;
  float _PFMET;
  float _PFMETphi;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("n_presel_jet",&_n_presel_jet);
  tree->SetBranchAddress("jet0_pt",&_jet0_pt);
  tree->SetBranchAddress("jet0_eta",&_jet0_eta);
  tree->SetBranchAddress("jet0_phi",&_jet0_phi);
  tree->SetBranchAddress("jet0_E",&_jet0_E);
  tree->SetBranchAddress("jet0_CSV",&_jet0_CSV);
  tree->SetBranchAddress("PFMET",&_PFMET);
  tree->SetBranchAddress("PFMETphi",&_PFMETphi);

 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);
  
    if(_n_presel_jet==0) continue;

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_pt<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_eta<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_phi<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_E<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_CSV<<" ";
    out<<std::fixed<<std::setprecision(5)<<_PFMET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_PFMETphi<<endl;

  }


  return;


}






void write_2lSS_SR_ee_log(){

  /*std::ofstream out("2lSS_SR_ee.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_SR_ee_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_SR_ee_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";


  TChain * tree = new TChain("syncTree_2lSS_ee");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lSS_lepMVA_CR_ee_log(){

  //std::ofstream out("2lSS_lepMVA_CR_ee.txt");
  //TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";

  /*std::ofstream out("2lSS_lepMVA_CR_ee_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_lepMVA_CR_ee_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";
 
  TChain * tree = new TChain("syncTree_2lSS_lepMVA_CR_ee");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lOS_CR_ee_log(){


  /*std::ofstream out("2lOS_CR_ee.txt");
  TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lOS_CR_ee_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lOS_CR_ee_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lOS_CR_ee");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lSS_SR_mumu_log(){

  /*std::ofstream out("2lSS_SR_mumu.txt");
  TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_SR_mumu_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_SR_mumu_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";


  TChain * tree = new TChain("syncTree_2lSS_mumu");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lSS_lepMVA_CR_mumu_log(){

  /*std::ofstream out("2lSS_lepMVA_CR_mumu.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_lepMVA_CR_mumu_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_lepMVA_CR_mumu_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lSS_lepMVA_CR_mumu");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lOS_CR_mumu_log(){

  /*std::ofstream out("2lOS_CR_mumu.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lOS_CR_mumu_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lOS_CR_mumu_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lOS_CR_mumu");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}






void write_2lSS_SR_emu_log(){

  /*std::ofstream out("2lSS_SR_emu.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_SR_emu_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_SR_emu_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lSS_emu");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lSS_lepMVA_CR_emu_log(){

  /*std::ofstream out("2lSS_lepMVA_CR_emu.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_lepMVA_CR_emu_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_lepMVA_CR_emu_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lSS_lepMVA_CR_emu");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lOS_CR_emu_log(){

  /*std::ofstream out("2lOS_CR_emu.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lOS_CR_emu_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lOS_CR_emu_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lOS_CR_emu");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}








void write_2lSS_SR_tau_log(){

  /*std::ofstream out("2lSS_SR_tau.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_SR_tau_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_SR_tau_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lSS_tau");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lSS_lepMVA_CR_tau_log(){

  /*std::ofstream out("2lSS_lepMVA_CR_tau.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lSS_lepMVA_CR_tau_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lSS_lepMVA_CR_tau_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lSS_lepMVA_CR_tau");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}







void write_2lOS_CR_tau_log(){

  /*std::ofstream out("2lOS_CR_tau.txt");
    TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";*/

  /*std::ofstream out("2lOS_CR_tau_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("2lOS_CR_tau_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_2lOS_CR_tau");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_2lSS_ttV;
  float _MVA_2lSS_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_2lSS_ttV",&_MVA_2lSS_ttV);
  tree->SetBranchAddress("MVA_2lSS_ttbar",&_MVA_2lSS_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MET<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep1<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_2lSS_ttV<<endl;
    
  }


  return;


}








void write_3l_SR_log(){

  //std::ofstream out("3l_SR.txt");
  //TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";

  /*std::ofstream out("3l_SR_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("3l_SR_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_3l");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_3l_ttV;
  float _MVA_3l_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_3l_ttV",&_MVA_3l_ttV);
  tree->SetBranchAddress("MVA_3l_ttbar",&_MVA_3l_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MHT<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep2<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_3l_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_3l_ttV<<endl;
    
  }


  return;


}







void write_3l_lepMVA_CR_log(){

  //std::ofstream out("3l_lepMVA_CR.txt");
  //TString file="/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_06_2016/syncNtuple_event_ttH_multilep.root";

  /*std::ofstream out("3l_lepMVA_CR_80X.txt");
    TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttH_multilep.root";*/

  std::ofstream out("3l_lepMVA_CR_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";

  TChain * tree = new TChain("syncTree_3l_lepMVA_CR");
  tree->Add(file);

  ULong64_t _nEvent;
  float _event_weight_ttH;
  float _max_eta_lep;
  int _n_recoPFJet;
  float _mindR_lep0_recoPFjet;
  float _mindR_lep1_recoPFjet;
  float _MET;
  float _MHT;
  float _avg_dR_jets;
  float _mT_lep0;
  float _pT_lep0;
  float _pT_lep1;
  float _pT_lep2;
  float _MVA_3l_ttV;
  float _MVA_3l_ttbar;

  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree->SetBranchAddress("max_eta_lep",&_max_eta_lep);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("mindR_lep0_recoPFjet",&_mindR_lep0_recoPFjet);
  tree->SetBranchAddress("mindR_lep1_recoPFjet",&_mindR_lep1_recoPFjet);
  tree->SetBranchAddress("MET",&_MET);
  tree->SetBranchAddress("MHT",&_MHT);
  tree->SetBranchAddress("avg_dR_jets",&_avg_dR_jets);
  tree->SetBranchAddress("mT_lep0",&_mT_lep0);
  tree->SetBranchAddress("pT_lep0",&_pT_lep0);
  tree->SetBranchAddress("pT_lep1",&_pT_lep1);
  tree->SetBranchAddress("pT_lep2",&_pT_lep2);
  tree->SetBranchAddress("MVA_3l_ttV",&_MVA_3l_ttV);
  tree->SetBranchAddress("MVA_3l_ttbar",&_MVA_3l_ttbar);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_event_weight_ttH<<" ";
    out<<std::fixed<<std::setprecision(5)<<_max_eta_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_n_recoPFJet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MHT<<" ";
    out<<std::fixed<<std::setprecision(5)<<_avg_dR_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep0_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_mindR_lep1_recoPFjet<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep0<<" ";
    out<<std::fixed<<std::setprecision(5)<<_pT_lep2<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_3l_ttbar<<" ";
    out<<std::fixed<<std::setprecision(5)<<_MVA_3l_ttV<<endl;

    
  }


  return;


}




void write_2lSS_Hjj_BDT_log(){


  std::ofstream out("2lSS_SR_Hjj_BDT_80X_Summer16.txt");
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root";  

   
  TChain * tree = new TChain("syncTree_2lSS");
  tree->Add(file);

  ULong64_t _nEvent;
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


  tree->SetBranchAddress("nEvent",&_nEvent);
  tree->SetBranchAddress("jet0_mindR_lep",&_jet0_mindR_lep);
  tree->SetBranchAddress("jet0_CSVscore",&_jet0_CSVscore);
  tree->SetBranchAddress("jet0_QGdiscr",&_jet0_QGdiscr);
  tree->SetBranchAddress("jet0_maxdR_lep",&_jet0_maxdR_lep);
  tree->SetBranchAddress("jet0_pt",&_jet0_pt);
  tree->SetBranchAddress("jet0_HjBDT",&_jet0_HjBDT);

  tree->SetBranchAddress("jet01_Mjjlep",&_jet01_Mjjlep);
  tree->SetBranchAddress("jet01_SumHjBDT",&_jet01_SumHjBDT);
  tree->SetBranchAddress("jet01_dRjj",&_jet01_dRjj);
  tree->SetBranchAddress("jet01_min_dRjj_jets",&_jet01_min_dRjj_jets);
  tree->SetBranchAddress("jet01_Mjj",&_jet01_Mjj);
  tree->SetBranchAddress("jet01_ratio_dRjj_jets",&_jet01_ratio_dRjj_jets);
  tree->SetBranchAddress("jet01_HjjBDT",&_jet01_HjjBDT);
 


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    out<<_nEvent<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_mindR_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_CSVscore<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_QGdiscr<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_maxdR_lep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_pt<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet0_HjBDT<<" ";

    out<<std::fixed<<std::setprecision(5)<<_jet01_Mjjlep<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet01_SumHjBDT<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet01_dRjj<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet01_min_dRjj_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet01_Mjj<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet01_ratio_dRjj_jets<<" ";
    out<<std::fixed<<std::setprecision(5)<<_jet01_HjjBDT<<endl;

    
  }


  return;


}






void write_all_log(){

  //write_mu_log();
  /*write_ele_log();
  write_tau_log();
  write_jet_log();*/


  write_2lSS_SR_ee_log();
  write_2lSS_lepMVA_CR_ee_log();
  write_2lOS_CR_ee_log();
  write_2lSS_SR_mumu_log();
  write_2lSS_lepMVA_CR_mumu_log();
  write_2lOS_CR_mumu_log();
  write_2lSS_SR_emu_log();
  write_2lSS_lepMVA_CR_emu_log();
  write_2lOS_CR_emu_log();
  write_2lSS_SR_tau_log();
  write_2lSS_lepMVA_CR_tau_log();
  write_2lOS_CR_tau_log();
  write_3l_SR_log();
  write_3l_lepMVA_CR_log();

  

}









void write_sig_1l2tau(){


  std::ofstream out("1l2tau_SR.txt");

  TChain * tree = new TChain("HTauTauTree_1l_2tau");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root");


  ULong64_t _EventNumber;
  int _lumi;
  int _run;
  int _category;
  bool _isTrig_1l;

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("RunNumber",&_run);
  tree->SetBranchAddress("category",&_category);
  tree->SetBranchAddress("isTrig_1l",&_isTrig_1l);


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    if(!(_category==20 && _isTrig_1l)) continue;
    
    out<<_run<<" ";
    out<<_lumi<<" ";
    out<<_EventNumber<<endl;

    
  }


  return;


}








void write_sig_1l2tau_Fake(){


  std::ofstream out("1l2tau_Fake.txt");

  TChain * tree = new TChain("HTauTauTree_1l_2tau_fake_CR");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root");


  ULong64_t _EventNumber;
  int _lumi;
  int _run;
  int _category;
  bool _isTrig_1l;

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("RunNumber",&_run);
  tree->SetBranchAddress("category",&_category);
  tree->SetBranchAddress("isTrig_1l",&_isTrig_1l);


  Long64_t nentries = tree->GetEntries();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);

    if(!(_category==50 && _isTrig_1l)) continue;
    
    out<<_run<<" ";
    out<<_lumi<<" ";
    out<<_EventNumber<<endl;

    
  }


  return;


}


