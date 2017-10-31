#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>

#include "leptonSF_M17.cc"


using namespace std;



float fakerate_from_TGraph(TGraphAsymmErrors* graph, float pt){

  int n = graph->GetN();

  double x, y;
  graph->GetPoint(0,x,y);
  if(pt<x)
    return y;

  graph->GetPoint(n-1,x,y);
  if(pt>x)
    return y;
  

  for(int i=0; i<n;i++){

    graph->GetPoint(i,x,y);
    double err_low_x = graph->GetErrorXlow(i);
    double err_high_x = graph->GetErrorXhigh(i);

    if( (x-err_low_x) < pt && pt < (x+err_high_x) )
      return y;

  }

  return -1.;

}




void add_event_weight(TString filein, TString fileout, vector<TString> treename, bool isMC){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");
  
  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filein);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;

    int _category;
    
    vector<int> *_recolep_sel_pdg;    
    vector<float> *_recolep_sel_conept;
    vector<float> *_recolep_sel_pt;
    vector<float> *_recolep_sel_eta;
    vector<bool> *_recolep_sel_ismvasel;
    vector<int> *_recolep_sel_charge;    

    vector<int> *_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
    vector<int> *_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT;
    /*vector<float> *_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
      vector<float> *_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;*/
    vector<float> *_recotauh_sel_pt;
    vector<float> *_recotauh_sel_eta;
    vector<bool> *_recotauh_sel_isGenMatched;
    vector<int> *_recotauh_sel_charge; 

    tree->SetBranchAddress("category",&_category);
    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree->SetBranchAddress("recolep_sel_ismvasel",&_recolep_sel_ismvasel);
    tree->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);

    tree->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree->SetBranchAddress("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
    /*tree->SetBranchAddress("recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
      tree->SetBranchAddress("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);*/
    tree->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
    tree->SetBranchAddress("recotauh_sel_eta",&_recotauh_sel_eta);
    tree->SetBranchAddress("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);
    tree->SetBranchAddress("recotauh_sel_charge",&_recotauh_sel_charge);

    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    vector<float> _recolep_sel_fakerate_v2;     
    vector<float> _recolep_sel_QFrate_v2;

    float _event_weight_ttH_v2;
    float _event_weight_ttH_ele_FR_QCD_MC_v2;
    float _event_weight_ttH_ele_FR_TT_MC_v2;
    float _event_weight_ttH_mu_FR_QCD_MC_v2;
    float _event_weight_ttH_mu_FR_TT_MC_v2;

    float _event_weight_ttH_ele_up_v2;
    float _event_weight_ttH_ele_down_v2;
    float _event_weight_ttH_ele_pt1_v2;
    float _event_weight_ttH_ele_pt2_v2;
    float _event_weight_ttH_ele_b1_v2;
    float _event_weight_ttH_ele_b2_v2;
    float _event_weight_ttH_ele_ec1_v2;
    float _event_weight_ttH_ele_ec2_v2;

    float _event_weight_ttH_mu_up_v2;
    float _event_weight_ttH_mu_down_v2;
    float _event_weight_ttH_mu_pt1_v2;
    float _event_weight_ttH_mu_pt2_v2;
    float _event_weight_ttH_mu_b1_v2;
    float _event_weight_ttH_mu_b2_v2;
    float _event_weight_ttH_mu_ec1_v2;
    float _event_weight_ttH_mu_ec2_v2;

    float _event_weight_ttH_tauNormUp_v2;
    float _event_weight_ttH_tauNormDown_v2;
    float _event_weight_ttH_tauShapeUp_v2;
    float _event_weight_ttH_tauShapeDown_v2;

    float _leptonSF_ttH_weight_v2;

    float _tauSF_weight_v2;
    float _tauSF_weight_tauNormUp_v2;
    float _tauSF_weight_tauNormDown_v2;
    float _tauSF_weight_tauShapeUp_v2;
    float _tauSF_weight_tauShapeDown_v2;

    tree_new->Branch("recolep_sel_fakerate_v2",&_recolep_sel_fakerate_v2);
    tree_new->Branch("recolep_sel_QFrate_v2",&_recolep_sel_QFrate_v2);

    tree_new->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");

    tree_new->Branch("event_weight_ttH_ele_FR_QCD_MC_v2",&_event_weight_ttH_ele_FR_QCD_MC_v2,"event_weight_ttH_ele_FR_QCD_MC_v2/F");
    tree_new->Branch("event_weight_ttH_ele_FR_TT_MC_v2",&_event_weight_ttH_ele_FR_TT_MC_v2,"event_weight_ttH_ele_FR_TT_MC_v2/F");
    tree_new->Branch("event_weight_ttH_mu_FR_QCD_MC_v2",&_event_weight_ttH_mu_FR_QCD_MC_v2,"event_weight_ttH_mu_FR_QCD_MC_v2/F");
    tree_new->Branch("event_weight_ttH_mu_FR_TT_MC_v2",&_event_weight_ttH_mu_FR_TT_MC_v2,"event_weight_ttH_mu_FR_TT_MC_v2/F");

    tree_new->Branch("event_weight_ttH_ele_up_v2",&_event_weight_ttH_ele_up_v2,"event_weight_ttH_ele_up_v2/F");
    tree_new->Branch("event_weight_ttH_ele_down_v2",&_event_weight_ttH_ele_down_v2,"event_weight_ttH_ele_down_v2/F");
    tree_new->Branch("event_weight_ttH_ele_pt1_v2",&_event_weight_ttH_ele_pt1_v2,"event_weight_ttH_ele_pt1_v2/F");
    tree_new->Branch("event_weight_ttH_ele_pt2_v2",&_event_weight_ttH_ele_pt2_v2,"event_weight_ttH_ele_pt2_v2/F");
    tree_new->Branch("event_weight_ttH_ele_b1_v2",&_event_weight_ttH_ele_b1_v2,"event_weight_ttH_ele_b1_v2/F");
    tree_new->Branch("event_weight_ttH_ele_b2_v2",&_event_weight_ttH_ele_b2_v2,"event_weight_ttH_ele_b2_v2/F");
    tree_new->Branch("event_weight_ttH_ele_ec1_v2",&_event_weight_ttH_ele_ec1_v2,"event_weight_ttH_ele_ec1_v2/F");
    tree_new->Branch("event_weight_ttH_ele_ec2_v2",&_event_weight_ttH_ele_ec2_v2,"event_weight_ttH_ele_ec2_v2/F");

    tree_new->Branch("event_weight_ttH_mu_up_v2",&_event_weight_ttH_mu_up_v2,"event_weight_ttH_mu_up_v2/F");
    tree_new->Branch("event_weight_ttH_mu_down_v2",&_event_weight_ttH_mu_down_v2,"event_weight_ttH_mu_down_v2/F");
    tree_new->Branch("event_weight_ttH_mu_pt1_v2",&_event_weight_ttH_mu_pt1_v2,"event_weight_ttH_mu_pt1_v2/F");
    tree_new->Branch("event_weight_ttH_mu_pt2_v2",&_event_weight_ttH_mu_pt2_v2,"event_weight_ttH_mu_pt2_v2/F");
    tree_new->Branch("event_weight_ttH_mu_b1_v2",&_event_weight_ttH_mu_b1_v2,"event_weight_ttH_mu_b1_v2/F");
    tree_new->Branch("event_weight_ttH_mu_b2_v2",&_event_weight_ttH_mu_b2_v2,"event_weight_ttH_mu_b2_v2/F");
    tree_new->Branch("event_weight_ttH_mu_ec1_v2",&_event_weight_ttH_mu_ec1_v2,"event_weight_ttH_mu_ec1_v2/F");
    tree_new->Branch("event_weight_ttH_mu_ec2_v2",&_event_weight_ttH_mu_ec2_v2,"event_weight_ttH_mu_ec2_v2/F");

    tree_new->Branch("event_weight_ttH_tauNormUp_v2",&_event_weight_ttH_tauNormUp_v2,"event_weight_ttH_tauNormUp_v2/F");
    tree_new->Branch("event_weight_ttH_tauNormDown_v2",&_event_weight_ttH_tauNormDown_v2,"event_weight_ttH_tauNormDown_v2/F");
    tree_new->Branch("event_weight_ttH_tauShapeUp_v2",&_event_weight_ttH_tauShapeUp_v2,"event_weight_ttH_tauShapeUp_v2/F");
    tree_new->Branch("event_weight_ttH_tauShapeDown_v2",&_event_weight_ttH_tauShapeDown_v2,"event_weight_ttH_tauShapeDown_v2/F");

    tree_new->Branch("leptonSF_ttH_weight_v2",&_leptonSF_ttH_weight_v2,"leptonSF_ttH_weight_v2/F");
  
    tree_new->Branch("tauSF_weight_v2",&_tauSF_weight_v2,"tauSF_weight_v2/F");
    tree_new->Branch("tauSF_weight_tauNormUp_v2",&_tauSF_weight_tauNormUp_v2,"tauSF_weight_tauNormUp_v2/F");
    tree_new->Branch("tauSF_weight_tauNormDown_v2",&_tauSF_weight_tauNormDown_v2,"tauSF_weight_tauNormDown_v2/F");
    tree_new->Branch("tauSF_weight_tauShapeUp_v2",&_tauSF_weight_tauShapeUp_v2,"tauSF_weight_tauShapeUp_v2/F");
    tree_new->Branch("tauSF_weight_tauShapeDown_v2",&_tauSF_weight_tauShapeDown_v2,"tauSF_weight_tauShapeDown_v2/F");

 
    TFile* f_fakerate = TFile::Open("fake_rate_weights/FR_data_ttH_mva_M17b.root");
    TH2F* h_fakerate_mu = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb");
    h_fakerate_mu->SetDirectory(0);
    TH2F* h_fakerate_el = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb");
    h_fakerate_el->SetDirectory(0);
    
    TH2F* h_fakerate_mu_QCD = (TH2F*)f_fakerate->Get("FR_mva075_mu_QCD");
    h_fakerate_mu_QCD->SetDirectory(0);
    TH2F* h_fakerate_el_QCD = (TH2F*)f_fakerate->Get("FR_mva075_el_QCD");
    h_fakerate_el_QCD->SetDirectory(0);
    
    TH2F* h_fakerate_mu_TT = (TH2F*)f_fakerate->Get("FR_mva075_mu_TT");
    h_fakerate_mu_TT->SetDirectory(0);
    TH2F* h_fakerate_el_TT = (TH2F*)f_fakerate->Get("FR_mva075_el_TT");
    h_fakerate_el_TT->SetDirectory(0);
    
    TH2F* h_fakerate_mu_data_up = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_up");
    h_fakerate_mu_data_up->SetDirectory(0);
    TH2F* h_fakerate_el_data_up = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_up");
    h_fakerate_el_data_up->SetDirectory(0);

    TH2F* h_fakerate_mu_data_down = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_down");
    h_fakerate_mu_data_down->SetDirectory(0);
    TH2F* h_fakerate_el_data_down = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_down");
    h_fakerate_el_data_down->SetDirectory(0);

    TH2F* h_fakerate_mu_data_pt1 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_pt1");
    h_fakerate_mu_data_pt1->SetDirectory(0);
    TH2F* h_fakerate_el_data_pt1 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_pt1");
    h_fakerate_el_data_pt1->SetDirectory(0);

    TH2F* h_fakerate_mu_data_pt2 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_pt2");
    h_fakerate_mu_data_pt2->SetDirectory(0);
    TH2F* h_fakerate_el_data_pt2 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_pt2");
    h_fakerate_el_data_pt2->SetDirectory(0);

    TH2F* h_fakerate_mu_data_b1 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_b1");
    h_fakerate_mu_data_b1->SetDirectory(0);
    TH2F* h_fakerate_el_data_b1 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_b1");
    h_fakerate_el_data_b1->SetDirectory(0);

    TH2F* h_fakerate_mu_data_b2 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_b2");
    h_fakerate_mu_data_b2->SetDirectory(0);
    TH2F* h_fakerate_el_data_b2 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_b2");
    h_fakerate_el_data_b2->SetDirectory(0);

    TH2F* h_fakerate_mu_data_ec1 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_ec1");
    h_fakerate_mu_data_ec1->SetDirectory(0);
    TH2F* h_fakerate_el_data_ec1 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_ec1");
    h_fakerate_el_data_ec1->SetDirectory(0);

    TH2F* h_fakerate_mu_data_ec2 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_ec2");
    h_fakerate_mu_data_ec2->SetDirectory(0);
    TH2F* h_fakerate_el_data_ec2 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_ec2");
    h_fakerate_el_data_ec2->SetDirectory(0);

    f_fakerate->Close();
    


    TFile* f_fakerate_tau = TFile::Open("fake_rate_weights/FR_tau_2016_M17.root");
    
    TGraphAsymmErrors* gr_fakerate_tau_medium_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");

    TGraphAsymmErrors* gr_fakerate_tau_medium_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");

    TGraphAsymmErrors* gr_fakerate_tau_tight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");

    TGraphAsymmErrors* gr_fakerate_tau_tight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");


    vector<TString> FR_tau_syst;
    FR_tau_syst.push_back("");
    FR_tau_syst.push_back("_par1Up");
    FR_tau_syst.push_back("_par1Down");
    FR_tau_syst.push_back("_par2Up");
    FR_tau_syst.push_back("_par2Down");

    vector<TF1*> f_dataMC_fakerate_tau_medium_barrel;
    vector<TF1*> f_dataMC_fakerate_tau_medium_endcaps;
    vector<TF1*> f_dataMC_fakerate_tau_tight_barrel;
    vector<TF1*> f_dataMC_fakerate_tau_tight_endcaps;
   

    for(unsigned int i=0;i<FR_tau_syst.size();i++){
     
      f_dataMC_fakerate_tau_medium_barrel.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );

  f_dataMC_fakerate_tau_medium_endcaps.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );      
 
      f_dataMC_fakerate_tau_tight_barrel.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );
  
      f_dataMC_fakerate_tau_tight_endcaps.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );  
   

    }
  
    f_fakerate_tau->Close();
    
    TFile* f_QFrate = TFile::Open("charge_flip_weights/QF_data_el_M17.root");
    TH2F* h_QFrate_el = (TH2F*)f_QFrate->Get("chargeMisId");
    h_QFrate_el->SetDirectory(0);
    f_QFrate->Close();

    vector<float> _recolep_sel_fakerate_QCD_v2;
    vector<float> _recolep_sel_fakerate_TT_v2; 
    vector<float> _recolep_sel_fakerate_up_v2;
    vector<float> _recolep_sel_fakerate_down_v2;
    vector<float> _recolep_sel_fakerate_pt1_v2;
    vector<float> _recolep_sel_fakerate_pt2_v2;
    vector<float> _recolep_sel_fakerate_b1_v2;
    vector<float> _recolep_sel_fakerate_b2_v2;
    vector<float> _recolep_sel_fakerate_ec1_v2;
    vector<float> _recolep_sel_fakerate_ec2_v2;

    vector<float> _recotauh_sel_fakerate_byMedium;
    vector<float> _recotauh_sel_fakerate_byTight;
    vector<float> _recotauh_sel_fakerate_byTight_tauNormUp;
    vector<float> _recotauh_sel_fakerate_byTight_tauNormDown;
    vector<float> _recotauh_sel_fakerate_byTight_tauShapeUp;
    vector<float> _recotauh_sel_fakerate_byTight_tauShapeDown;
    
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF;
    vector<float> _recotauh_sel_jetToTau_FR_byTight_SF;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown;
    


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _category = 0;

      _recolep_sel_pdg = 0;
      _recolep_sel_ismvasel = 0;
      _recolep_sel_conept = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;
      _recolep_sel_charge = 0;

      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      //_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      //_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_pt = 0;
      _recotauh_sel_eta = 0;
      _recotauh_sel_isGenMatched = 0;
      _recotauh_sel_charge = 0;

      _recolep_sel_fakerate_v2.clear();
      _recolep_sel_fakerate_QCD_v2.clear();
      _recolep_sel_fakerate_TT_v2.clear();      

      _recolep_sel_fakerate_up_v2.clear();
      _recolep_sel_fakerate_down_v2.clear();
      _recolep_sel_fakerate_pt1_v2.clear();
      _recolep_sel_fakerate_pt2_v2.clear();
      _recolep_sel_fakerate_b1_v2.clear();
      _recolep_sel_fakerate_b2_v2.clear();
      _recolep_sel_fakerate_ec1_v2.clear();
      _recolep_sel_fakerate_ec2_v2.clear();

      _recolep_sel_QFrate_v2.clear();

      _recotauh_sel_fakerate_byMedium.clear();
      _recotauh_sel_fakerate_byTight.clear();
      _recotauh_sel_fakerate_byTight_tauNormUp.clear();
      _recotauh_sel_fakerate_byTight_tauNormDown.clear();
      _recotauh_sel_fakerate_byTight_tauShapeUp.clear();
      _recotauh_sel_fakerate_byTight_tauShapeDown.clear();
     
      _recotauh_sel_jetToTau_FR_byMedium_SF.clear();
      _recotauh_sel_jetToTau_FR_byTight_SF.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown.clear();

      _event_weight_ttH_v2 = 0;
      _event_weight_ttH_ele_FR_QCD_MC_v2 = 0;
      _event_weight_ttH_ele_FR_TT_MC_v2 = 0;
      _event_weight_ttH_mu_FR_QCD_MC_v2 = 0;
      _event_weight_ttH_mu_FR_TT_MC_v2 = 0;

      _event_weight_ttH_ele_up_v2 = 0;
      _event_weight_ttH_ele_down_v2 = 0;
      _event_weight_ttH_ele_pt1_v2 = 0;
      _event_weight_ttH_ele_pt2_v2 = 0;
      _event_weight_ttH_ele_b1_v2 = 0;
      _event_weight_ttH_ele_b2_v2 = 0;
      _event_weight_ttH_ele_ec1_v2 = 0;
      _event_weight_ttH_ele_ec2_v2 = 0;

      _event_weight_ttH_mu_up_v2 = 0;
      _event_weight_ttH_mu_down_v2 = 0;
      _event_weight_ttH_mu_pt1_v2 = 0;
      _event_weight_ttH_mu_pt2_v2 = 0;
      _event_weight_ttH_mu_b1_v2 = 0;
      _event_weight_ttH_mu_b2_v2 = 0;
      _event_weight_ttH_mu_ec1_v2 = 0;
      _event_weight_ttH_mu_ec2_v2 = 0;
      
      _event_weight_ttH_tauNormUp_v2 = 0;
      _event_weight_ttH_tauNormDown_v2 = 0;
      _event_weight_ttH_tauShapeUp_v2 = 0;
      _event_weight_ttH_tauShapeDown_v2 = 0;

      _leptonSF_ttH_weight_v2 = 0;

      _tauSF_weight_v2 = 0;
      _tauSF_weight_tauNormUp_v2 = 0;
      _tauSF_weight_tauNormDown_v2 = 0;
      _tauSF_weight_tauShapeUp_v2 = 0;
      _tauSF_weight_tauShapeDown_v2 = 0;

      
      tree->GetEntry(i);


      for(unsigned int i_lep=0;i_lep<(*_recolep_sel_pdg).size();i_lep++){

	float FR = 0;
	float conept = (*_recolep_sel_conept)[i_lep];

	if(abs((*_recolep_sel_pdg)[i_lep])==11){

	  int bin_FR = h_fakerate_el->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_el->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_v2.push_back(FR);

	  bin_FR = h_fakerate_el_QCD->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_el_QCD->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_QCD_v2.push_back(FR);

	  bin_FR = h_fakerate_el_TT->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_el_TT->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_TT_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_up->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_up->GetBinContent(bin_FR);
          _recolep_sel_fakerate_up_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_down->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_down->GetBinContent(bin_FR);
          _recolep_sel_fakerate_down_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_pt1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_pt1->GetBinContent(bin_FR);
          _recolep_sel_fakerate_pt1_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_pt2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_pt2->GetBinContent(bin_FR);
          _recolep_sel_fakerate_pt2_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_b1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_b1->GetBinContent(bin_FR);
          _recolep_sel_fakerate_b1_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_b2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_b2->GetBinContent(bin_FR);
          _recolep_sel_fakerate_b2_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_ec1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_ec1->GetBinContent(bin_FR);
          _recolep_sel_fakerate_ec1_v2.push_back(FR);

          bin_FR = h_fakerate_el_data_ec2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_el_data_ec2->GetBinContent(bin_FR);
          _recolep_sel_fakerate_ec2_v2.push_back(FR);
	  
	  int bin_QF = h_QFrate_el->FindBin(min((*_recolep_sel_pt)[i_lep],float(999.)), abs((*_recolep_sel_eta)[i_lep]));
	  float QF = h_QFrate_el->GetBinContent(bin_QF);
	  _recolep_sel_QFrate_v2.push_back(QF);  

	}

	else if(abs((*_recolep_sel_pdg)[i_lep])==13){

	  int bin_FR = h_fakerate_mu->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_mu->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_v2.push_back(FR);

	  bin_FR = h_fakerate_mu_QCD->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_mu_QCD->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_QCD_v2.push_back(FR);

	  bin_FR = h_fakerate_mu_TT->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_mu_TT->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_TT_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_up->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_up->GetBinContent(bin_FR);
          _recolep_sel_fakerate_up_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_down->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_down->GetBinContent(bin_FR);
          _recolep_sel_fakerate_down_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_pt1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_pt1->GetBinContent(bin_FR);
          _recolep_sel_fakerate_pt1_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_pt2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_pt2->GetBinContent(bin_FR);
          _recolep_sel_fakerate_pt2_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_b1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_b1->GetBinContent(bin_FR);
          _recolep_sel_fakerate_b1_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_b2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_b2->GetBinContent(bin_FR);
          _recolep_sel_fakerate_b2_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_ec1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_ec1->GetBinContent(bin_FR);
          _recolep_sel_fakerate_ec1_v2.push_back(FR);

          bin_FR = h_fakerate_mu_data_ec2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
          FR = h_fakerate_mu_data_ec2->GetBinContent(bin_FR);
          _recolep_sel_fakerate_ec2_v2.push_back(FR);
	  	
	  _recolep_sel_QFrate_v2.push_back(0.);  

	}


      }


      for(unsigned int i_tau=0;i_tau<(*_recotauh_sel_pt).size();i_tau++){

	  float fakerate_byMedium = 0;
	  float fakerate_byTight = 0;
	  float fakerate_byTight_tauNormUp = 0;
	  float fakerate_byTight_tauNormDown = 0;
	  float fakerate_byTight_tauShapeUp = 0;
	  float fakerate_byTight_tauShapeDown = 0;
	  
	  float jetToTau_FR_byMedium_SF = 0;
	  float jetToTau_FR_byTight_SF = 0;
	  float jetToTau_FR_byMedium_SF_tauNormUp = 0;
	  float jetToTau_FR_byMedium_SF_tauNormDown = 0;
	  float jetToTau_FR_byMedium_SF_tauShapeUp = 0;
	  float jetToTau_FR_byMedium_SF_tauShapeDown = 0;

	  float tau_pt = (*_recotauh_sel_pt)[i_tau];

	  if(fabs((*_recotauh_sel_eta)[i_tau])<1.479){


	    fakerate_byMedium = fakerate_from_TGraph(gr_fakerate_tau_medium_barrel,tau_pt);
	    fakerate_byMedium *= f_dataMC_fakerate_tau_medium_barrel[0]->Eval(tau_pt);

	    float FR_MC_tight = fakerate_from_TGraph(gr_fakerate_tau_tight_barrel,tau_pt);

	    fakerate_byTight = FR_MC_tight * f_dataMC_fakerate_tau_tight_barrel[0]->Eval(tau_pt);

	    fakerate_byTight_tauNormUp = FR_MC_tight * f_dataMC_fakerate_tau_tight_barrel[1]->Eval(tau_pt);

	    fakerate_byTight_tauNormDown = FR_MC_tight * f_dataMC_fakerate_tau_tight_barrel[2]->Eval(tau_pt);

	    fakerate_byTight_tauShapeUp = FR_MC_tight * f_dataMC_fakerate_tau_tight_barrel[3]->Eval(tau_pt);

	    fakerate_byTight_tauShapeDown = FR_MC_tight * f_dataMC_fakerate_tau_tight_barrel[4]->Eval(tau_pt);


	    jetToTau_FR_byMedium_SF = f_dataMC_fakerate_tau_medium_barrel[0]->Eval(tau_pt);
	    jetToTau_FR_byTight_SF = f_dataMC_fakerate_tau_tight_barrel[0]->Eval(tau_pt); 
	    jetToTau_FR_byMedium_SF_tauNormUp = f_dataMC_fakerate_tau_medium_barrel[1]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauNormDown = f_dataMC_fakerate_tau_medium_barrel[2]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeUp = f_dataMC_fakerate_tau_medium_barrel[3]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeDown = f_dataMC_fakerate_tau_medium_barrel[4]->Eval(tau_pt);	    	    

	  }

	  else{

	    fakerate_byMedium = fakerate_from_TGraph(gr_fakerate_tau_medium_endcaps,tau_pt);
	    fakerate_byMedium *= f_dataMC_fakerate_tau_medium_endcaps[0]->Eval(tau_pt);

	    float FR_MC_tight = fakerate_from_TGraph(gr_fakerate_tau_tight_endcaps,tau_pt);
	    fakerate_byTight = FR_MC_tight * f_dataMC_fakerate_tau_tight_endcaps[0]->Eval(tau_pt);
	    fakerate_byTight_tauNormUp = FR_MC_tight * f_dataMC_fakerate_tau_tight_endcaps[1]->Eval(tau_pt);
	    fakerate_byTight_tauNormDown = FR_MC_tight * f_dataMC_fakerate_tau_tight_endcaps[2]->Eval(tau_pt);
	    fakerate_byTight_tauShapeUp = FR_MC_tight * f_dataMC_fakerate_tau_tight_endcaps[3]->Eval(tau_pt);
	    fakerate_byTight_tauShapeDown = FR_MC_tight * f_dataMC_fakerate_tau_tight_endcaps[4]->Eval(tau_pt);

	    jetToTau_FR_byMedium_SF = f_dataMC_fakerate_tau_medium_endcaps[0]->Eval(tau_pt);
	    jetToTau_FR_byTight_SF = f_dataMC_fakerate_tau_tight_endcaps[0]->Eval(tau_pt); 
	    jetToTau_FR_byMedium_SF_tauNormUp = f_dataMC_fakerate_tau_medium_endcaps[1]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauNormDown = f_dataMC_fakerate_tau_medium_endcaps[2]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeUp = f_dataMC_fakerate_tau_medium_endcaps[3]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeDown = f_dataMC_fakerate_tau_medium_endcaps[4]->Eval(tau_pt);	    	    

	  }

	  _recotauh_sel_fakerate_byMedium.push_back(fakerate_byMedium);
	  _recotauh_sel_fakerate_byTight.push_back(fakerate_byTight);
	  _recotauh_sel_fakerate_byTight_tauNormUp.push_back(fakerate_byTight_tauNormUp);
	  _recotauh_sel_fakerate_byTight_tauNormDown.push_back(fakerate_byTight_tauNormDown);
	  _recotauh_sel_fakerate_byTight_tauShapeUp.push_back(fakerate_byTight_tauShapeUp);
	  _recotauh_sel_fakerate_byTight_tauShapeDown.push_back(fakerate_byTight_tauShapeDown);
	  
	  _recotauh_sel_jetToTau_FR_byMedium_SF.push_back(jetToTau_FR_byMedium_SF);
	  _recotauh_sel_jetToTau_FR_byTight_SF.push_back(jetToTau_FR_byTight_SF);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp.push_back(jetToTau_FR_byMedium_SF_tauNormUp);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown.push_back(jetToTau_FR_byMedium_SF_tauNormDown);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp.push_back(jetToTau_FR_byMedium_SF_tauShapeUp);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown.push_back(jetToTau_FR_byMedium_SF_tauShapeDown);      

      }



      _event_weight_ttH_v2 = 1;
      _event_weight_ttH_ele_FR_QCD_MC_v2 = 1;
      _event_weight_ttH_ele_FR_TT_MC_v2 = 1;
      _event_weight_ttH_mu_FR_QCD_MC_v2 = 1;
      _event_weight_ttH_mu_FR_TT_MC_v2 = 1;

      _event_weight_ttH_ele_up_v2 = 1;
      _event_weight_ttH_ele_down_v2 = 1;
      _event_weight_ttH_ele_pt1_v2 = 1;
      _event_weight_ttH_ele_pt2_v2 = 1;
      _event_weight_ttH_ele_b1_v2 = 1;
      _event_weight_ttH_ele_b2_v2 = 1;
      _event_weight_ttH_ele_ec1_v2 = 1;
      _event_weight_ttH_ele_ec2_v2 = 1;

      _event_weight_ttH_mu_up_v2 = 1;
      _event_weight_ttH_mu_down_v2 = 1;
      _event_weight_ttH_mu_pt1_v2 = 1;
      _event_weight_ttH_mu_pt2_v2 = 1;
      _event_weight_ttH_mu_b1_v2 = 1;
      _event_weight_ttH_mu_b2_v2 = 1;
      _event_weight_ttH_mu_ec1_v2 = 1;
      _event_weight_ttH_mu_ec2_v2 = 1;
      
      _event_weight_ttH_tauNormUp_v2 = 1;
      _event_weight_ttH_tauNormDown_v2 = 1;
      _event_weight_ttH_tauShapeUp_v2 = 1;
      _event_weight_ttH_tauShapeDown_v2 = 1;

      _leptonSF_ttH_weight_v2 = 1;

      _tauSF_weight_v2 = 1;
      _tauSF_weight_tauNormUp_v2 = 1;
      _tauSF_weight_tauNormDown_v2 = 1;
      _tauSF_weight_tauShapeUp_v2 = 1;
      _tauSF_weight_tauShapeDown_v2 = 1;

      if(_category==-11){

	if(abs((*_recolep_sel_pdg)[0])==11 && (*_recolep_sel_charge)[0]*(*_recotauh_sel_charge)[0]>0)
	  _event_weight_ttH_v2 = _recolep_sel_QFrate_v2[0];
	else if(abs((*_recolep_sel_pdg)[1])==11 && (*_recolep_sel_charge)[1]*(*_recotauh_sel_charge)[0]>0)
	  _event_weight_ttH_v2 = _recolep_sel_QFrate_v2[1];
	else
	  _event_weight_ttH_v2 = 0;

	tree_new->Fill();
	continue;
      }

      
      else if(_category==20 || _category==50){	

	if((*_recolep_sel_ismvasel)[0])
	  _leptonSF_ttH_weight_v2 = leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3); //No tight-charge criteria for 1l2tau	      
	else
	  _leptonSF_ttH_weight_v2 = _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3);	

	if(isMC){
	  if(!(*_recotauh_sel_isGenMatched)[0])	    
	    _tauSF_weight_v2 *= _recotauh_sel_jetToTau_FR_byTight_SF[0];
	  if(!(*_recotauh_sel_isGenMatched)[1])	    
	    _tauSF_weight_v2 *= _recotauh_sel_jetToTau_FR_byTight_SF[1];
	}

	_tauSF_weight_tauNormUp_v2 = _tauSF_weight_v2;
	_tauSF_weight_tauNormDown_v2 = _tauSF_weight_v2;
	_tauSF_weight_tauShapeUp_v2 = _tauSF_weight_v2;
	_tauSF_weight_tauShapeDown_v2 = _tauSF_weight_v2;

	
	int n_fake = 0;

	if(!(*_recolep_sel_ismvasel)[0]){
	  
	  float lep_weight = _recolep_sel_fakerate_v2[0]/(1-_recolep_sel_fakerate_v2[0]);

	  _event_weight_ttH_v2 *= lep_weight;
	  _event_weight_ttH_tauNormUp_v2 *= lep_weight;
	  _event_weight_ttH_tauNormDown_v2 *= lep_weight;
	  _event_weight_ttH_tauShapeUp_v2 *= lep_weight;
	  _event_weight_ttH_tauShapeDown_v2 *= lep_weight;
	  
	  if(abs((*_recolep_sel_pdg)[0])==11){
	    _event_weight_ttH_ele_FR_QCD_MC_v2 *= _recolep_sel_fakerate_QCD_v2[0]/(1-_recolep_sel_fakerate_QCD_v2[0]);
	    _event_weight_ttH_ele_FR_TT_MC_v2 *= _recolep_sel_fakerate_TT_v2[0]/(1-_recolep_sel_fakerate_TT_v2[0]);
	    _event_weight_ttH_mu_FR_QCD_MC_v2 *= lep_weight;
	    _event_weight_ttH_mu_FR_TT_MC_v2 *= lep_weight;

	    _event_weight_ttH_ele_up_v2 *= _recolep_sel_fakerate_up_v2[0]/(1-_recolep_sel_fakerate_up_v2[0]);
	    _event_weight_ttH_ele_down_v2 *= _recolep_sel_fakerate_down_v2[0]/(1-_recolep_sel_fakerate_down_v2[0]);
	    _event_weight_ttH_ele_pt1_v2 *= _recolep_sel_fakerate_pt1_v2[0]/(1-_recolep_sel_fakerate_pt1_v2[0]);
	    _event_weight_ttH_ele_pt2_v2 *= _recolep_sel_fakerate_pt2_v2[0]/(1-_recolep_sel_fakerate_pt2_v2[0]);
	    _event_weight_ttH_ele_b1_v2 *= _recolep_sel_fakerate_b1_v2[0]/(1-_recolep_sel_fakerate_b1_v2[0]);
	    _event_weight_ttH_ele_b2_v2 *= _recolep_sel_fakerate_b2_v2[0]/(1-_recolep_sel_fakerate_b2_v2[0]);
	    _event_weight_ttH_ele_ec1_v2 *= _recolep_sel_fakerate_ec1_v2[0]/(1-_recolep_sel_fakerate_ec1_v2[0]);
	    _event_weight_ttH_ele_ec2_v2 *= _recolep_sel_fakerate_ec2_v2[0]/(1-_recolep_sel_fakerate_ec2_v2[0]);

	    _event_weight_ttH_mu_up_v2 *= lep_weight;
	    _event_weight_ttH_mu_down_v2 *= lep_weight;
	    _event_weight_ttH_mu_pt1_v2 *= lep_weight;
	    _event_weight_ttH_mu_pt2_v2 *= lep_weight;
	    _event_weight_ttH_mu_b1_v2 *= lep_weight;
	    _event_weight_ttH_mu_b2_v2 *= lep_weight;
	    _event_weight_ttH_mu_ec1_v2 *= lep_weight;
	    _event_weight_ttH_mu_ec2_v2 *= lep_weight;

	  }
	  
	  else if(abs((*_recolep_sel_pdg)[0])==13){
	    _event_weight_ttH_ele_FR_QCD_MC_v2 *= lep_weight;
	    _event_weight_ttH_ele_FR_TT_MC_v2 *= lep_weight;
	    _event_weight_ttH_mu_FR_QCD_MC_v2 *= _recolep_sel_fakerate_QCD_v2[0]/(1-_recolep_sel_fakerate_QCD_v2[0]);
	    _event_weight_ttH_mu_FR_TT_MC_v2 *= _recolep_sel_fakerate_TT_v2[0]/(1-_recolep_sel_fakerate_TT_v2[0]);

            _event_weight_ttH_ele_up_v2 *= lep_weight;
            _event_weight_ttH_ele_down_v2 *= lep_weight;
            _event_weight_ttH_ele_pt1_v2 *= lep_weight;
            _event_weight_ttH_ele_pt2_v2 *= lep_weight;
            _event_weight_ttH_ele_b1_v2 *= lep_weight;
            _event_weight_ttH_ele_b2_v2 *= lep_weight;
            _event_weight_ttH_ele_ec1_v2 *= lep_weight;
            _event_weight_ttH_ele_ec2_v2 *= lep_weight;

            _event_weight_ttH_mu_up_v2 *= _recolep_sel_fakerate_up_v2[0]/(1-_recolep_sel_fakerate_up_v2[0]);
            _event_weight_ttH_mu_down_v2 *= _recolep_sel_fakerate_down_v2[0]/(1-_recolep_sel_fakerate_down_v2[0]);
            _event_weight_ttH_mu_pt1_v2 *= _recolep_sel_fakerate_pt1_v2[0]/(1-_recolep_sel_fakerate_pt1_v2[0]);
            _event_weight_ttH_mu_pt2_v2 *= _recolep_sel_fakerate_pt2_v2[0]/(1-_recolep_sel_fakerate_pt2_v2[0]);
            _event_weight_ttH_mu_b1_v2 *= _recolep_sel_fakerate_b1_v2[0]/(1-_recolep_sel_fakerate_b1_v2[0]);
            _event_weight_ttH_mu_b2_v2 *= _recolep_sel_fakerate_b2_v2[0]/(1-_recolep_sel_fakerate_b2_v2[0]);
            _event_weight_ttH_mu_ec1_v2 *= _recolep_sel_fakerate_ec1_v2[0]/(1-_recolep_sel_fakerate_ec1_v2[0]);
            _event_weight_ttH_mu_ec2_v2 *= _recolep_sel_fakerate_ec2_v2[0]/(1-_recolep_sel_fakerate_ec2_v2[0]);

	  }

	  n_fake++;
	}


	for(int i_tau=0; i_tau<2; i_tau++){
	  if(!(*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]){
	    float weight_tau = _recotauh_sel_fakerate_byTight[i_tau]/(1-_recotauh_sel_fakerate_byTight[i_tau]);
	    _event_weight_ttH_v2 *= weight_tau;
	    _event_weight_ttH_ele_FR_QCD_MC_v2 *= weight_tau;
	    _event_weight_ttH_ele_FR_TT_MC_v2 *= weight_tau;
	    _event_weight_ttH_mu_FR_TT_MC_v2 *= weight_tau;
	    _event_weight_ttH_mu_FR_TT_MC_v2 *= weight_tau;

	    _event_weight_ttH_ele_up_v2 *= weight_tau;
	    _event_weight_ttH_ele_down_v2 *= weight_tau;
	    _event_weight_ttH_ele_pt1_v2 *= weight_tau;
	    _event_weight_ttH_ele_pt2_v2 *= weight_tau;
	    _event_weight_ttH_ele_b1_v2 *= weight_tau;
	    _event_weight_ttH_ele_b2_v2 *= weight_tau;
	    _event_weight_ttH_ele_ec1_v2 *= weight_tau;
	    _event_weight_ttH_ele_ec2_v2 *= weight_tau;

	    _event_weight_ttH_mu_up_v2 *= weight_tau;
	    _event_weight_ttH_mu_down_v2 *= weight_tau;
	    _event_weight_ttH_mu_pt1_v2 *= weight_tau;
	    _event_weight_ttH_mu_pt2_v2 *= weight_tau;
	    _event_weight_ttH_mu_b1_v2 *= weight_tau;
	    _event_weight_ttH_mu_b2_v2 *= weight_tau;
	    _event_weight_ttH_mu_ec1_v2 *= weight_tau;
	    _event_weight_ttH_mu_ec2_v2 *= weight_tau;
	    
	    float weight_tauNormUp = _recotauh_sel_fakerate_byTight_tauNormUp[0]/(1-_recotauh_sel_fakerate_byTight_tauNormUp[i_tau]);
	    float weight_tauNormDown = _recotauh_sel_fakerate_byTight_tauNormDown[0]/(1-_recotauh_sel_fakerate_byTight_tauNormDown[i_tau]);
	    float weight_tauShapeUp = _recotauh_sel_fakerate_byTight_tauShapeUp[0]/(1-_recotauh_sel_fakerate_byTight_tauShapeUp[i_tau]);
	    float weight_tauShapeDown = _recotauh_sel_fakerate_byTight_tauShapeDown[0]/(1-_recotauh_sel_fakerate_byTight_tauShapeDown[i_tau]);

	    _event_weight_ttH_tauNormUp_v2 *= weight_tauNormUp;
	    _event_weight_ttH_tauNormDown_v2 *= weight_tauNormDown;
	    _event_weight_ttH_tauShapeUp_v2 *= weight_tauShapeUp;
	    _event_weight_ttH_tauShapeDown_v2 *= weight_tauShapeDown;
	    
	    n_fake++;
	  }
	}

	if(n_fake>0 && n_fake%2==0){

	  _event_weight_ttH_v2 *=-1;	  
	  _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
	  _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

	  _event_weight_ttH_ele_up_v2 *= -1;
	  _event_weight_ttH_ele_down_v2 *= -1;
	  _event_weight_ttH_ele_pt1_v2 *= -1;
	  _event_weight_ttH_ele_pt2_v2 *= -1;
	  _event_weight_ttH_ele_b1_v2 *= -1;
	  _event_weight_ttH_ele_b2_v2 *= -1;
	  _event_weight_ttH_ele_ec1_v2 *= -1;
	  _event_weight_ttH_ele_ec2_v2 *= -1;

	  _event_weight_ttH_mu_up_v2 *= -1;
	  _event_weight_ttH_mu_down_v2 *= -1;
	  _event_weight_ttH_mu_pt1_v2 *= -1;
	  _event_weight_ttH_mu_pt2_v2 *= -1;
	  _event_weight_ttH_mu_b1_v2 *= -1;
	  _event_weight_ttH_mu_b2_v2 *= -1;
	  _event_weight_ttH_mu_ec1_v2 *= -1;
	  _event_weight_ttH_mu_ec2_v2 *= -1;

	  _event_weight_ttH_tauNormUp_v2 *= -1;
	  _event_weight_ttH_tauNormDown_v2 *= -1;
	  _event_weight_ttH_tauShapeUp_v2 *= -1;
	  _event_weight_ttH_tauShapeDown_v2 *= -1;
	  
	}
	

      }


      
      else if(_category==11 || _category==41 || _category==16 || _category==46){

	if(_category==11 || _category==41){

	  for(unsigned int i_lep=0;i_lep<2;i_lep++){
	    
	    if((*_recolep_sel_ismvasel)[i_lep])
	      _leptonSF_ttH_weight_v2 = leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],2);
	    else
	      _leptonSF_ttH_weight_v2 = _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],2);	
	    
	  }

	}

	else{

	  for(unsigned int i_lep=0;i_lep<3;i_lep++){
	    
	    if((*_recolep_sel_ismvasel)[i_lep])
	      _leptonSF_ttH_weight_v2 = leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],3);
	    else
	      _leptonSF_ttH_weight_v2 = _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],3);	
	    
	  }

	}


	if(isMC){
	  if(!(*_recotauh_sel_isGenMatched)[0]){	    
	    _tauSF_weight_v2 *= _recotauh_sel_jetToTau_FR_byMedium_SF[0];
	    _tauSF_weight_tauNormUp_v2 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp[0];
	    _tauSF_weight_tauNormDown_v2 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown[0];
	    _tauSF_weight_tauShapeUp_v2 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp[0];
	    _tauSF_weight_tauShapeDown_v2 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown[0];
	  }
	}

       
	int n_fake = 0;

	for(unsigned int i_lep=0;i_lep<_recolep_sel_fakerate_v2.size();i_lep++){

	  if(!(*_recolep_sel_ismvasel)[i_lep]){
	  
	    float lep_weight = _recolep_sel_fakerate_v2[i_lep]/(1-_recolep_sel_fakerate_v2[i_lep]);

	    _event_weight_ttH_v2 *= lep_weight;
	    _event_weight_ttH_tauNormUp_v2 *= lep_weight;
	    _event_weight_ttH_tauNormDown_v2 *= lep_weight;
	    _event_weight_ttH_tauShapeUp_v2 *= lep_weight;
	    _event_weight_ttH_tauShapeDown_v2 *= lep_weight;
	  
	    if(abs((*_recolep_sel_pdg)[i_lep])==11){
	      _event_weight_ttH_ele_FR_QCD_MC_v2 *= _recolep_sel_fakerate_QCD_v2[i_lep]/(1-_recolep_sel_fakerate_QCD_v2[i_lep]);
	      _event_weight_ttH_ele_FR_TT_MC_v2 *= _recolep_sel_fakerate_TT_v2[i_lep]/(1-_recolep_sel_fakerate_TT_v2[i_lep]);
	      _event_weight_ttH_mu_FR_QCD_MC_v2 *= lep_weight;
	      _event_weight_ttH_mu_FR_TT_MC_v2 *= lep_weight;

            _event_weight_ttH_ele_up_v2 *= _recolep_sel_fakerate_up_v2[i_lep]/(1-_recolep_sel_fakerate_up_v2[i_lep]);
            _event_weight_ttH_ele_down_v2 *= _recolep_sel_fakerate_down_v2[i_lep]/(1-_recolep_sel_fakerate_down_v2[i_lep]);
            _event_weight_ttH_ele_pt1_v2 *= _recolep_sel_fakerate_pt1_v2[i_lep]/(1-_recolep_sel_fakerate_pt1_v2[i_lep]);
            _event_weight_ttH_ele_pt2_v2 *= _recolep_sel_fakerate_pt2_v2[i_lep]/(1-_recolep_sel_fakerate_pt2_v2[i_lep]);
            _event_weight_ttH_ele_b1_v2 *= _recolep_sel_fakerate_b1_v2[i_lep]/(1-_recolep_sel_fakerate_b1_v2[i_lep]);
            _event_weight_ttH_ele_b2_v2 *= _recolep_sel_fakerate_b2_v2[i_lep]/(1-_recolep_sel_fakerate_b2_v2[i_lep]);
            _event_weight_ttH_ele_ec1_v2 *= _recolep_sel_fakerate_ec1_v2[i_lep]/(1-_recolep_sel_fakerate_ec1_v2[i_lep]);
            _event_weight_ttH_ele_ec2_v2 *= _recolep_sel_fakerate_ec2_v2[i_lep]/(1-_recolep_sel_fakerate_ec2_v2[i_lep]);

            _event_weight_ttH_mu_up_v2 *= lep_weight;
            _event_weight_ttH_mu_down_v2 *= lep_weight;
            _event_weight_ttH_mu_pt1_v2 *= lep_weight;
            _event_weight_ttH_mu_pt2_v2 *= lep_weight;
            _event_weight_ttH_mu_b1_v2 *= lep_weight;
            _event_weight_ttH_mu_b2_v2 *= lep_weight;
            _event_weight_ttH_mu_ec1_v2 *= lep_weight;
            _event_weight_ttH_mu_ec2_v2 *= lep_weight;

	    }
	    
	    else if(abs((*_recolep_sel_pdg)[i_lep])==13){
	      _event_weight_ttH_ele_FR_QCD_MC_v2 *= lep_weight;
	      _event_weight_ttH_ele_FR_TT_MC_v2 *= lep_weight;
	      _event_weight_ttH_mu_FR_QCD_MC_v2 *= _recolep_sel_fakerate_QCD_v2[i_lep]/(1-_recolep_sel_fakerate_QCD_v2[i_lep]);
	      _event_weight_ttH_mu_FR_TT_MC_v2 *= _recolep_sel_fakerate_TT_v2[i_lep]/(1-_recolep_sel_fakerate_TT_v2[i_lep]);

            _event_weight_ttH_ele_up_v2 *= lep_weight;
            _event_weight_ttH_ele_down_v2 *= lep_weight;
            _event_weight_ttH_ele_pt1_v2 *= lep_weight;
            _event_weight_ttH_ele_pt2_v2 *= lep_weight;
            _event_weight_ttH_ele_b1_v2 *= lep_weight;
            _event_weight_ttH_ele_b2_v2 *= lep_weight;
            _event_weight_ttH_ele_ec1_v2 *= lep_weight;
            _event_weight_ttH_ele_ec2_v2 *= lep_weight;
 
            _event_weight_ttH_mu_up_v2 *= _recolep_sel_fakerate_up_v2[i_lep]/(1-_recolep_sel_fakerate_up_v2[i_lep]);
            _event_weight_ttH_mu_down_v2 *= _recolep_sel_fakerate_down_v2[i_lep]/(1-_recolep_sel_fakerate_down_v2[i_lep]);
            _event_weight_ttH_mu_pt1_v2 *= _recolep_sel_fakerate_pt1_v2[i_lep]/(1-_recolep_sel_fakerate_pt1_v2[i_lep]);
            _event_weight_ttH_mu_pt2_v2 *= _recolep_sel_fakerate_pt2_v2[i_lep]/(1-_recolep_sel_fakerate_pt2_v2[i_lep]);
            _event_weight_ttH_mu_b1_v2 *= _recolep_sel_fakerate_b1_v2[i_lep]/(1-_recolep_sel_fakerate_b1_v2[i_lep]);
            _event_weight_ttH_mu_b2_v2 *= _recolep_sel_fakerate_b2_v2[i_lep]/(1-_recolep_sel_fakerate_b2_v2[i_lep]);
            _event_weight_ttH_mu_ec1_v2 *= _recolep_sel_fakerate_ec1_v2[i_lep]/(1-_recolep_sel_fakerate_ec1_v2[i_lep]);
            _event_weight_ttH_mu_ec2_v2 *= _recolep_sel_fakerate_ec2_v2[i_lep]/(1-_recolep_sel_fakerate_ec2_v2[i_lep]);

	  }
	    
	    n_fake++;
	  }
	  
	}

	if(!(*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]){
	  float weight_tau = _recotauh_sel_fakerate_byMedium[0]/(1-_recotauh_sel_fakerate_byMedium[0]);
	  _event_weight_ttH_v2 *= weight_tau;
	  _event_weight_ttH_ele_FR_QCD_MC_v2 *= weight_tau;
	  _event_weight_ttH_ele_FR_TT_MC_v2 *= weight_tau;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= weight_tau;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= weight_tau;
	 
            _event_weight_ttH_ele_up_v2 *= weight_tau;
            _event_weight_ttH_ele_down_v2 *= weight_tau;
            _event_weight_ttH_ele_pt1_v2 *= weight_tau;
            _event_weight_ttH_ele_pt2_v2 *= weight_tau;
            _event_weight_ttH_ele_b1_v2 *= weight_tau;
            _event_weight_ttH_ele_b2_v2 *= weight_tau;
            _event_weight_ttH_ele_ec1_v2 *= weight_tau;
            _event_weight_ttH_ele_ec2_v2 *= weight_tau;

            _event_weight_ttH_mu_up_v2 *= weight_tau;
            _event_weight_ttH_mu_down_v2 *= weight_tau;
            _event_weight_ttH_mu_pt1_v2 *= weight_tau;
            _event_weight_ttH_mu_pt2_v2 *= weight_tau;
            _event_weight_ttH_mu_b1_v2 *= weight_tau;
            _event_weight_ttH_mu_b2_v2 *= weight_tau;
            _event_weight_ttH_mu_ec1_v2 *= weight_tau;
            _event_weight_ttH_mu_ec2_v2 *= weight_tau;

	  _event_weight_ttH_tauNormUp_v2 *= weight_tau;
	  _event_weight_ttH_tauNormDown_v2 *= weight_tau;
	  _event_weight_ttH_tauShapeUp_v2 *= weight_tau;
	  _event_weight_ttH_tauShapeDown_v2 *= weight_tau;
	  
	  n_fake++;
	}
	

	if(n_fake>0 && n_fake%2==0){

	  _event_weight_ttH_v2 *=-1;	  
	  _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
	  _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

          _event_weight_ttH_ele_up_v2 *= -1;
          _event_weight_ttH_ele_down_v2 *= -1;
          _event_weight_ttH_ele_pt1_v2 *= -1;
          _event_weight_ttH_ele_pt2_v2 *= -1;
          _event_weight_ttH_ele_b1_v2 *= -1;
          _event_weight_ttH_ele_b2_v2 *= -1;
          _event_weight_ttH_ele_ec1_v2 *= -1;
          _event_weight_ttH_ele_ec2_v2 *= -1;

          _event_weight_ttH_mu_up_v2 *= -1;
          _event_weight_ttH_mu_down_v2 *= -1;
          _event_weight_ttH_mu_pt1_v2 *= -1;
          _event_weight_ttH_mu_pt2_v2 *= -1;
          _event_weight_ttH_mu_b1_v2 *= -1;
          _event_weight_ttH_mu_b2_v2 *= -1;
          _event_weight_ttH_mu_ec1_v2 *= -1;
          _event_weight_ttH_mu_ec2_v2 *= -1;

	  _event_weight_ttH_tauNormUp_v2 *= -1;
	  _event_weight_ttH_tauNormDown_v2 *= -1;
	  _event_weight_ttH_tauShapeUp_v2 *= -1;
	  _event_weight_ttH_tauShapeDown_v2 *= -1;
	  
	}
	

      }           	



     
      else if(treename[i_tree]=="HTauTauTree_3l_ttZ_lepMVA_CR"){
	
	
	int n_fake = 0;
	
	for(unsigned int i_lep=0;i_lep<_recolep_sel_fakerate_v2.size();i_lep++){
	  
	  if(!(*_recolep_sel_ismvasel)[i_lep]){
	  
	    float lep_weight = _recolep_sel_fakerate_v2[i_lep]/(1-_recolep_sel_fakerate_v2[i_lep]);

	    _event_weight_ttH_v2 *= lep_weight;
	    _event_weight_ttH_tauNormUp_v2 *= lep_weight;
	    _event_weight_ttH_tauNormDown_v2 *= lep_weight;
	    _event_weight_ttH_tauShapeUp_v2 *= lep_weight;
	    _event_weight_ttH_tauShapeDown_v2 *= lep_weight;
	  
	    if(abs((*_recolep_sel_pdg)[i_lep])==11){
	      _event_weight_ttH_ele_FR_QCD_MC_v2 *= _recolep_sel_fakerate_QCD_v2[i_lep]/(1-_recolep_sel_fakerate_QCD_v2[i_lep]);
	      _event_weight_ttH_ele_FR_TT_MC_v2 *= _recolep_sel_fakerate_TT_v2[i_lep]/(1-_recolep_sel_fakerate_TT_v2[i_lep]);
	      _event_weight_ttH_mu_FR_QCD_MC_v2 *= lep_weight;
	      _event_weight_ttH_mu_FR_TT_MC_v2 *= lep_weight;
	    }
	    
	    else if(abs((*_recolep_sel_pdg)[i_lep])==13){
	      _event_weight_ttH_ele_FR_QCD_MC_v2 *= lep_weight;
	      _event_weight_ttH_ele_FR_TT_MC_v2 *= lep_weight;
	      _event_weight_ttH_mu_FR_QCD_MC_v2 *= _recolep_sel_fakerate_QCD_v2[i_lep]/(1-_recolep_sel_fakerate_QCD_v2[i_lep]);
	      _event_weight_ttH_mu_FR_TT_MC_v2 *= _recolep_sel_fakerate_TT_v2[i_lep]/(1-_recolep_sel_fakerate_TT_v2[i_lep]);
	  }
	    
	    n_fake++;
	  }
	  
	}
	
	if(n_fake>0 && n_fake%2==0){

	  _event_weight_ttH_v2 *=-1;	  
	  _event_weight_ttH_ele_FR_QCD_MC_v2 *= -1;
	  _event_weight_ttH_ele_FR_TT_MC_v2 *= -1;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;
	  _event_weight_ttH_mu_FR_TT_MC_v2 *= -1;

	  _event_weight_ttH_tauNormUp_v2 *= -1;
	  _event_weight_ttH_tauNormDown_v2 *= -1;
	  _event_weight_ttH_tauShapeUp_v2 *= -1;
	  _event_weight_ttH_tauShapeDown_v2 *= -1;
	  
	}
	

      }           	
	
      
      tree_new->Fill();

    }

   
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}






void test_evt_weight(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_2lOS_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");

  TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_btagSF_new.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_btagSF_lepTauSF_new.root";
  
  add_event_weight(filein,fileout,treename,true);




}







void add_event_weight_fromSecondary(TString file_in, TString file_out, TString treename, TString filein_secondary, TString treename_secondary){

  TFile* f_new = TFile::Open(file_out);
  if(f_new!=0){
    cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(file_out,"RECREATE");

  TChain * tree1 = new TChain(treename);
  tree1->Add(file_in);

  Long64_t nentries1 = tree1->GetEntries();
  cout<<"nentries="<<tree1->GetEntries()<<endl;

  //Old branches
  ULong64_t _EventNumber1;
  tree1->SetBranchAddress("EventNumber",&_EventNumber1);

  TChain * tree2 = new TChain(treename_secondary);
  tree2->Add(filein_secondary);

  Long64_t nentries2 = tree2->GetEntries();
  /*if(nentries1!=nentries2){
    cout<<"Problem"<<endl;
    return;
    }*/

  //Old branches
  ULong64_t _EventNumber2;
  float _event_weight_ttH_v2;
  //float _triggerSF_weight_v2;
  float _leptonSF_ttH_weight_v2;
  float _tauSF_weight_v2;

  tree2->SetBranchAddress("EventNumber",&_EventNumber2);
  tree2->SetBranchAddress("event_weight_ttH_v2",&_event_weight_ttH_v2);
  //tree2->SetBranchAddress("triggerSF_weight_v2",&_triggerSF_weight_v2);
  tree2->SetBranchAddress("leptonSF_ttH_weight_v2",&_leptonSF_ttH_weight_v2);
  tree2->SetBranchAddress("tauSF_weight_v2",&_tauSF_weight_v2);

  TTree* tree_new=tree1->GetTree()->CloneTree(0);
  //New branches
  tree_new->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  //tree_new->Branch("triggerSF_weight_v2",&_triggerSF_weight_v2,"triggerSF_weight_v2/F");
  tree_new->Branch("leptonSF_ttH_weight_v2",&_leptonSF_ttH_weight_v2,"leptonSF_ttH_weight_v2/F");
  tree_new->Branch("tauSF_weight_v2",&_tauSF_weight_v2,"tauSF_weight_v2/F");
  
  int iEntry2 = 0;  

  for(int i=0;i<nentries1;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _EventNumber1 = 0;
      _EventNumber2 = 0;

      _event_weight_ttH_v2 = 0;
      //_triggerSF_weight_v2 = 0;
      _leptonSF_ttH_weight_v2 = 0;
      _tauSF_weight_v2 = 0;


      tree1->GetEntry(i);
      tree2->GetEntry(iEntry2);


      bool full_loop = false;

      while(_EventNumber1!=_EventNumber2){
	iEntry2++;
	if(iEntry2>nentries2){
	  if(full_loop){
	    cout<<"EventNumber1="<<_EventNumber1<<endl;
	    cout<<"EventNumber2="<<_EventNumber2<<endl;
	    cout<<"Problem"<<endl;
	    return;
	  }
	  iEntry2 = 0;
	  full_loop = true;
	}
	tree2->GetEntry(iEntry2);
      }


       
      tree_new->Fill();
      
    }

  f_new->cd();
  
  tree_new->Write();

  f_new->Close();


  return;
    


}










void add_MC_weight_tHq_fromSecondary(TString file_in, TString file_out, vector<TString> treename, TString filein_secondary, TString treename_secondary){

  TFile* f_new = TFile::Open(file_out);
  if(f_new!=0){
    cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(file_out,"RECREATE");

  TChain * tree2 = new TChain(treename_secondary);
  tree2->Add(filein_secondary);

  Long64_t nentries2 = tree2->GetEntries();
  /*if(nentries1!=nentries2){
    cout<<"Problem"<<endl;
    return;
    }*/

  //Old branches
  ULong64_t _EventNumber2;
  float _MC_weight_tHq_SM_457;

  tree2->SetBranchAddress("EventNumber",&_EventNumber2);
  tree2->SetBranchAddress("MC_weight_tHq_SM_457",&_MC_weight_tHq_SM_457);


  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

  TChain * tree1 = new TChain(treename[i_tree]);
  tree1->Add(file_in);

  Long64_t nentries1 = tree1->GetEntries();
  cout<<"nentries="<<tree1->GetEntries()<<endl;

  //Old branches
  ULong64_t _EventNumber1;
  tree1->SetBranchAddress("EventNumber",&_EventNumber1);



  TTree* tree_new=tree1->GetTree()->CloneTree(0);
  //New branches
  tree_new->Branch("MC_weight_tHq_SM_457",&_MC_weight_tHq_SM_457,"MC_weight_tHq_SM_457/F");
  
  int iEntry2 = 0;  

  for(int i=0;i<nentries1;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _EventNumber1 = 0;
      _EventNumber2 = 0;

      _MC_weight_tHq_SM_457 = 0;

      tree1->GetEntry(i);
      tree2->GetEntry(iEntry2);


      bool full_loop = false;

      while(_EventNumber1!=_EventNumber2){
	iEntry2++;
	if(iEntry2>nentries2){
	  if(full_loop){
	    cout<<"EventNumber1="<<_EventNumber1<<endl;
	    cout<<"EventNumber2="<<_EventNumber2<<endl;
	    cout<<"Problem"<<endl;
	    return;
	  }
	  iEntry2 = 0;
	  full_loop = true;
	}
	tree2->GetEntry(iEntry2);
      }


       
      tree_new->Fill();
      
  }


  f_new->cd();
  
  tree_new->Write();


  }

  f_new->Close();


  return;
    


}


