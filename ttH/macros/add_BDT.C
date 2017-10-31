#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TH2F.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


float tt_deltaR;
float ntags_loose;
float njets_inclusive;
float jet_deltaRavg;
float jet_deltaRmax;
float tau1_pt;
float ht;
float tau2_pt;
float tt_visiblemass;
float tt_sumpt;


TMVA::Reader* Book_1l2tau_TT_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("ht", &ht );
    reader->AddVariable("tt_deltaR", &tt_deltaR );
    reader->AddVariable("tt_visiblemass", &tt_visiblemass  );   
    reader->AddVariable("tau1_pt", &tau1_pt );
    reader->AddVariable("tau2_pt", &tau2_pt );  
    reader->AddVariable("jet_deltaRavg", &jet_deltaRavg );
    reader->AddVariable("njets_inclusive", &njets_inclusive );
    reader->AddVariable("ntags_loose", &ntags_loose );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}




TMVA::Reader* Book_1l2tau_TTZ_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("ht", &ht );
    reader->AddVariable("tt_deltaR", &tt_deltaR );
    reader->AddVariable("tt_visiblemass", &tt_visiblemass  );
    reader->AddVariable("tt_sumpt", &tt_sumpt  );   
    reader->AddVariable("jet_deltaRmax", &jet_deltaRmax );
    reader->AddVariable("jet_deltaRavg", &jet_deltaRavg );
    reader->AddVariable("njets_inclusive", &njets_inclusive );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}







void add_1l2tau_BDT(TString filein, TString fileout, vector<TString> treename){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");


  TMVA::Reader* MVA_1l2tau_ttbar_reader = Book_1l2tau_TT_MVAReader("1l2tauMVA_weights","/1l2tau_ttbar_BDTG.weights.xml");
  TMVA::Reader* MVA_1l2tau_ttbar_reader_v2 = Book_1l2tau_TT_MVAReader("1l2tauMVA_weights","/sklearn_tt.weights.xml");
  TMVA::Reader* MVA_1l2tau_ttZ_reader_v2 = Book_1l2tau_TTZ_MVAReader("1l2tauMVA_weights","/sklearn_ttZ.weights.xml");


  TFile* f_MVA_2Dbin = TFile::Open("1l2tauMVA_weights/mapping.root");
  TH2F* h_MVA_2Dbin = (TH2F*)f_MVA_2Dbin->Get("hTargetBinning");
  h_MVA_2Dbin->SetDirectory(0);
  f_MVA_2Dbin->Close();    
  
  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filein);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;

    int _category;
    vector<float>* _recotauh_sel_px;
    vector<float>* _recotauh_sel_py;
    vector<float>* _recotauh_sel_pz;
    vector<float>* _recotauh_sel_e;
    vector<float>* _recolep_pt;
    vector<float>* _recotauh_pt;
    vector<float>* _recoPFJet_pt;
    int _n_recoPFJet;
    int _n_recoPFJet_btag_loose;
    vector<float>* _recoPFJet_px;
    vector<float>* _recoPFJet_py;
    vector<float>* _recoPFJet_pz;
    vector<float>* _recoPFJet_e;
    float _avg_dr_jet;
    //float _HTmiss;
    
    tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
    tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
    tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
    tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
    tree->SetBranchAddress("recolep_pt",&_recolep_pt);
    tree->SetBranchAddress("recotauh_pt",&_recotauh_pt);
    tree->SetBranchAddress("recoPFJet_pt",&_recoPFJet_pt);
    tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
    tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);
    tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
    tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
    tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
    tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
    tree->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
    //tree->SetBranchAddress("HTmiss",&_HTmiss);
    tree->SetBranchAddress("category",&_category);


    TTree* tree_new=tree->GetTree()->CloneTree(0);

    float _deltaR_tautau;
    float _mvis_tautau;    
    float _HT;
    float _sumpT_tautau;
    float _deltaRmax_jet;    
    float _MVA_1l2tau_ttbar;
    float _MVA_1l2tau_ttbar_v2;
    float _MVA_1l2tau_ttZ_v2;
    int _MVA_1l2tau_2Dbin_v2;

    
    tree_new->Branch("deltaR_tautau",&_deltaR_tautau,"deltaR_tautau/F");
    tree_new->Branch("mvis_tautau",&_mvis_tautau,"mvis_tautau/F");
    tree_new->Branch("HT",&_HT,"HT/F");
    tree_new->Branch("sumpT_tautau",&_sumpT_tautau,"sumpT_tautau/F");
    tree_new->Branch("deltaRmax_jet",&_deltaRmax_jet,"deltaRmax_jet/F");
    tree_new->Branch("MVA_1l2tau_ttbar",&_MVA_1l2tau_ttbar,"MVA_1l2tau_ttbar/F");
    tree_new->Branch("MVA_1l2tau_ttbar_v2",&_MVA_1l2tau_ttbar_v2,"MVA_1l2tau_ttbar_v2/F");
    tree_new->Branch("MVA_1l2tau_ttZ_v2",&_MVA_1l2tau_ttZ_v2,"MVA_1l2tau_ttZ_v2/F");
    tree_new->Branch("MVA_1l2tau_2Dbin_v2",&_MVA_1l2tau_2Dbin_v2,"MVA_1l2tau_2Dbbin_v2/I");


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _deltaR_tautau = 0;
      _mvis_tautau = 0;
      _HT = 0;
      _sumpT_tautau = 0;
      _deltaRmax_jet = 0;    
      _MVA_1l2tau_ttbar = 0;
      _MVA_1l2tau_ttbar_v2 = 0;
      _MVA_1l2tau_ttZ_v2 = 0;
      _MVA_1l2tau_2Dbin_v2 = 0;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      _recolep_pt = 0;
      _recotauh_pt = 0;
      _recoPFJet_pt = 0;
      _n_recoPFJet = 0;
      _n_recoPFJet_btag_loose = 0;
      _recoPFJet_px = 0;
      _recoPFJet_py = 0;
      _recoPFJet_pz = 0;
      _recoPFJet_e = 0;
      _avg_dr_jet = 0;
      //_HTmiss = 0;
      _category = 0;

      tree->GetEntry(i);

      if(_category==20 || _category==50){

	TLorentzVector tau1((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]);
	TLorentzVector tau2((*_recotauh_sel_px)[1],(*_recotauh_sel_py)[1],(*_recotauh_sel_pz)[1],(*_recotauh_sel_e)[1]);
	
	_deltaR_tautau = tau1.DeltaR(tau2);
	_mvis_tautau = (tau1+tau2).M();


	_HT = 0;
	for(unsigned int i_lep=0;i_lep<(*_recolep_pt).size();i_lep++)
	  _HT += (*_recolep_pt)[i_lep];
	for(unsigned int i_tau=0;i_tau<(*_recotauh_pt).size();i_tau++)
	  _HT += (*_recotauh_pt)[i_tau];
	for(unsigned int i_jet=0;i_jet<(*_recoPFJet_pt).size();i_jet++)
	  _HT += (*_recoPFJet_pt)[i_jet];
	
	_sumpT_tautau = (tau1+tau2).Pt();
	

	_deltaRmax_jet = -1;

	for(unsigned int i_jet=0;i_jet<(*_recoPFJet_pt).size()-1;i_jet++){
	  TLorentzVector jet1((*_recoPFJet_px)[i_jet], (*_recoPFJet_py)[i_jet], (*_recoPFJet_pz)[i_jet], (*_recoPFJet_e)[i_jet]);

	  for(unsigned int i_jet2=i_jet+1;i_jet2<(*_recoPFJet_pt).size();i_jet2++){
	    TLorentzVector jet2((*_recoPFJet_px)[i_jet2], (*_recoPFJet_py)[i_jet2], (*_recoPFJet_pz)[i_jet2], (*_recoPFJet_e)[i_jet2]);
	    
	    float dR = jet1.DeltaR(jet2);
	    if(_deltaRmax_jet<0 || dR>_deltaRmax_jet){
	      _deltaRmax_jet = dR;
	    }

	  }
	}
	

	tt_deltaR = _deltaR_tautau;
	njets_inclusive = _n_recoPFJet;
	ntags_loose = _n_recoPFJet_btag_loose;
	jet_deltaRavg = _avg_dr_jet;
	jet_deltaRmax = _deltaRmax_jet;
	tau1_pt = tau1.Pt();
	ht = _HT;
	tau2_pt = tau2.Pt();
	tt_visiblemass = _mvis_tautau;
	tt_sumpt = _sumpT_tautau;

	_MVA_1l2tau_ttbar = MVA_1l2tau_ttbar_reader->EvaluateMVA("BDTG method");
	_MVA_1l2tau_ttbar_v2 = MVA_1l2tau_ttbar_reader_v2->EvaluateMVA("BDTG method");
	_MVA_1l2tau_ttZ_v2 = MVA_1l2tau_ttZ_reader_v2->EvaluateMVA("BDTG method");

	int i_bin = h_MVA_2Dbin->FindBin(_MVA_1l2tau_ttbar_v2,_MVA_1l2tau_ttbar_v2);
	_MVA_1l2tau_2Dbin_v2 = int(h_MVA_2Dbin->GetBinContent(i_bin))/2;

      }

      
       tree_new->Fill();

    }
    
    
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}




float njet;
float mindr_lep1_jet;
float mindr_lep2_jet;
float mindr_lep3_jet;
float avg_dr_jet;
float max_lep_eta;
//float ptmiss;
float mT_lep1;
float mT_lep3;
//float htmiss;
float dr_leps;
float tau_pt;
float abs_tau_eta;
float dr_lep1_tau;
float dr_lep2_tau;
float dr_lep3_tau;
float lep1_pt;
float lep2_pt;
float lep3_pt;
float mTauTauVis1;
float mTauTauVis2;
float mindr_tau_jet;



TMVA::Reader* Book_2lSS1tau_TT_noMEM_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("nJet", &njet );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))", &max_lep_eta );
    reader->AddVariable("lep2_conePt", &lep2_pt );
    reader->AddVariable("dr_leps", &dr_leps );
    reader->AddVariable("tau_pt", &tau_pt );
    reader->AddVariable("dr_lep1_tau", &dr_lep1_tau );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}



TMVA::Reader* Book_2lSS1tau_TTV_noMEM_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("mindr_lep2_jet", &mindr_lep2_jet );
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))", &max_lep_eta );
    reader->AddVariable("lep1_conePt", &lep1_pt );
    reader->AddVariable("lep2_conePt", &lep2_pt );
    reader->AddVariable("mT_lep1", &mT_lep1 );
    reader->AddVariable("dr_leps", &dr_leps );
    reader->AddVariable("mTauTauVis1", &mTauTauVis1 );
    reader->AddVariable("mTauTauVis2", &mTauTauVis2 );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}



float memOutput_LR;



TMVA::Reader* Book_2lSS1tau_TT_MEM_LR_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("nJet", &njet );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    //reader->AddVariable("mindr_lep2_jet", &mindr_lep2_jet );
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))", &max_lep_eta );
    //reader->AddVariable("max_lep_eta", &max_lep_eta );
    reader->AddVariable("lep2_conePt", &lep2_pt );    
    //reader->AddVariable("ptmiss", &ptmiss );
    //reader->AddVariable("mT_lep1", &mT_lep1 );
    //reader->AddVariable("htmiss", &htmiss );
    reader->AddVariable("dr_leps", &dr_leps );
    reader->AddVariable("tau_pt", &tau_pt );
    reader->AddVariable("dr_lep1_tau", &dr_lep1_tau );
    reader->AddVariable("memOutput_LR", &memOutput_LR );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}




TMVA::Reader* Book_2lSS1tau_TTV_MEM_LR_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("mindr_lep2_jet", &mindr_lep2_jet );
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    //reader->AddVariable("lep1_pt", &lep1_pt );
    //reader->AddVariable("lep2_pt", &lep2_pt );
    reader->AddVariable("TMath::Max(TMath::Abs(lep1_eta),TMath::Abs(lep2_eta))", &max_lep_eta );
    //reader->AddVariable("max_lep_eta", &max_lep_eta );
    reader->AddVariable("lep1_conePt", &lep1_pt );
    reader->AddVariable("lep2_conePt", &lep2_pt );
    reader->AddVariable("mT_lep1", &mT_lep1 );
    reader->AddVariable("dr_leps", &dr_leps );
    reader->AddVariable("mTauTauVis1", &mTauTauVis1 );
    reader->AddVariable("mTauTauVis2", &mTauTauVis2 );
    reader->AddVariable("memOutput_LR", &memOutput_LR );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}






TMVA::Reader* Book_3l1tau_TTV_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("nJet", &njet );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("lep1_conePt", &lep1_pt );
    reader->AddVariable("lep2_conePt", &lep2_pt );
    reader->AddVariable("lep3_conePt", &lep3_pt );
    reader->AddVariable("mindr_tau_jet", &mindr_tau_jet );
    reader->AddVariable("mT_lep3", &mT_lep3 );
    reader->AddVariable("tau_pt", &tau_pt );
    reader->AddVariable("dr_lep1_tau", &dr_lep1_tau );
    reader->AddVariable("dr_lep2_tau", &dr_lep2_tau );
    reader->AddVariable("dr_lep3_tau", &dr_lep3_tau );
    reader->AddVariable("mTauTauVis2", &mTauTauVis2 );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}






TMVA::Reader* Book_3l1tau_TT_MVAReader(std::string basePath, std::string weightFileName)
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("nJet", &njet );
    reader->AddVariable("mindr_lep1_jet", &mindr_lep1_jet );
    reader->AddVariable("mindr_lep2_jet", &mindr_lep2_jet );
    reader->AddVariable("mindr_lep3_jet", &mindr_lep3_jet );
    reader->AddVariable("avg_dr_jet", &avg_dr_jet );
    reader->AddVariable("mindr_tau_jet", &mindr_tau_jet );
    reader->AddVariable("tau_pt", &tau_pt );
    reader->AddVariable("TMath::Abs(tau_eta)", &abs_tau_eta );
    reader->AddVariable("dr_lep1_tau", &dr_lep1_tau );
    reader->AddVariable("dr_lep2_tau", &dr_lep2_tau );
    reader->AddVariable("dr_lep3_tau", &dr_lep3_tau );
    reader->AddVariable("mTauTauVis2", &mTauTauVis2 );

    reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

    return reader;
}





void add_2lSS1tau_MEM_BDT(TString filein, TString fileout, vector<TString> treename){


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
    int _n_recoPFJet;
    vector<float>* _recoPFJet_px;
    vector<float>* _recoPFJet_py;
    vector<float>* _recoPFJet_pz;
    vector<float>* _recoPFJet_e;
    vector<float>* _recolep_sel_px;
    vector<float>* _recolep_sel_py;
    vector<float>* _recolep_sel_pz;
    vector<float>* _recolep_sel_e;
    vector<float>* _recolep_sel_conept;
    vector<float>* _recotauh_sel_px;
    vector<float>* _recotauh_sel_py;
    vector<float>* _recotauh_sel_pz;
    vector<float>* _recotauh_sel_e;
    float _avg_dr_jet;
    float _PFMET;
    float _PFMET_phi;
    float _HTmiss;    

    float _Integral_ttH;
    float _Integral_ttZ;
    float _Integral_ttZ_Zll;
    float _Integral_ttbar_DL_fakelep_tlep;
    float _Integral_ttbar_DL_fakelep_ttau;
    int _integration_type;

    tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
    tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
    tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
    tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
    tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
    tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
    tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
    tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
    tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
    tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
    tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
    tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
    tree->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
    tree->SetBranchAddress("PFMET",&_PFMET);
    tree->SetBranchAddress("PFMET_phi",&_PFMET_phi);
    tree->SetBranchAddress("HTmiss",&_HTmiss);
    tree->SetBranchAddress("category",&_category);

    tree->SetBranchAddress("Integral_ttH",&_Integral_ttH);
    tree->SetBranchAddress("Integral_ttZ",&_Integral_ttZ);
    tree->SetBranchAddress("Integral_ttZ_Zll",&_Integral_ttZ_Zll);
    tree->SetBranchAddress("Integral_ttbar_DL_fakelep_tlep",&_Integral_ttbar_DL_fakelep_tlep);
    tree->SetBranchAddress("Integral_ttbar_DL_fakelep_ttau",&_Integral_ttbar_DL_fakelep_ttau);
    tree->SetBranchAddress("integration_type",&_integration_type);

    TTree* tree_new=tree->GetTree()->CloneTree(0);

    float _mindR_lep1_jet;
    float _mindR_lep2_jet;
    float _mT_lep1;
    float _dR_leps;
    float _mTauTauVis1;
    float _mTauTauVis2;
    float _dR_lep1_tau;  

    float _MVA_2lSS1tau_noMEM_ttbar;
    float _MVA_2lSS1tau_MEM_LR_ttbar;
 
    float _MVA_2lSS1tau_noMEM_ttV;
    float _MVA_2lSS1tau_MEM_LR_ttV;

    int _MVA_2lSS1tau_noMEM_2Dbin;
    int _MVA_2lSS1tau_MEM_LR_2Dbin;

    tree_new->Branch("mindR_lep1_jet",&_mindR_lep1_jet,"mindR_lep1_jet/F");
    tree_new->Branch("mindR_lep2_jet",&_mindR_lep2_jet,"mindR_lep2_jet/F");
    tree_new->Branch("mT_lep1",&_mT_lep1,"mT_lep1/F");
    tree_new->Branch("dR_leps",&_dR_leps,"dR_leps/F");
    tree_new->Branch("mTauTauVis1",&_mTauTauVis1,"mTauTauVis1/F");
    tree_new->Branch("mTauTauVis2",&_mTauTauVis2,"mTauTauVis2/F");
    tree_new->Branch("dR_lep1_tau",&_dR_lep1_tau,"dR_lep1_tau/F");  

    tree_new->Branch("MVA_2lSS1tau_noMEM_ttbar",&_MVA_2lSS1tau_noMEM_ttbar,"MVA_2lSS1tau_noMEM_ttbar/F");
    tree_new->Branch("MVA_2lSS1tau_MEM_LR_ttbar",&_MVA_2lSS1tau_MEM_LR_ttbar,"MVA_2lSS1tau_MEM_LR_ttbar/F");

    tree_new->Branch("MVA_2lSS1tau_noMEM_ttV",&_MVA_2lSS1tau_noMEM_ttV,"MVA_2lSS1tau_noMEM_ttV/F");
    tree_new->Branch("MVA_2lSS1tau_MEM_LR_ttV",&_MVA_2lSS1tau_MEM_LR_ttV,"MVA_2lSS1tau_MEM_LR_ttV/F");
    
    tree_new->Branch("MVA_2lSS1tau_noMEM_2Dbin",&_MVA_2lSS1tau_noMEM_2Dbin,"MVA_2lSS1tau_noMEM_2Dbin/I");
    tree_new->Branch("MVA_2lSS1tau_MEM_LR_2Dbin",&_MVA_2lSS1tau_MEM_LR_2Dbin,"MVA_2lSS1tau_MEM_LR_2Dbin/I");


    TMVA::Reader* MVA_2lSS1tau_TT_noMEM_reader = Book_2lSS1tau_TT_noMEM_MVAReader("2lSS1tau_MVA_weights","/mvaTTHvsTTbar2lss1tau_BDTG.weights.xml");
    TMVA::Reader* MVA_2lSS1tau_TT_MEM_LR_reader = Book_2lSS1tau_TT_MEM_LR_MVAReader("2lSS1tau_MVA_weights","/2lss_1tau_ttbar_BDTGwMEM.weights.xml");

    TMVA::Reader* MVA_2lSS1tau_TTV_noMEM_reader = Book_2lSS1tau_TTV_noMEM_MVAReader("2lSS1tau_MVA_weights","/mvaTTHvsTTV2lss1tau_BDTG.weights.xml");
    TMVA::Reader* MVA_2lSS1tau_TTV_MEM_LR_reader = Book_2lSS1tau_TTV_MEM_LR_MVAReader("2lSS1tau_MVA_weights","/2lss_1tau_ttV_BDTGwMEM.weights.xml");


    TFile* f_MVA_2Dbin = TFile::Open("2lSS1tau_MVA_weights/binning_2l.root");
    TH2F* h_MVA_2Dbin = (TH2F*)f_MVA_2Dbin->Get("hTargetBinning");
    h_MVA_2Dbin->SetDirectory(0);
    f_MVA_2Dbin->Close();    

    TFile* f_MVA_MEM_LR_2Dbin = TFile::Open("2lSS1tau_MVA_weights/2lss_1tau_BDTwMEM_mapping_likelihood.root");
    TH2F* h_MVA_MEM_LR_2Dbin = (TH2F*)f_MVA_MEM_LR_2Dbin->Get("hTargetBinning");
    h_MVA_MEM_LR_2Dbin->SetDirectory(0);
    f_MVA_MEM_LR_2Dbin->Close();    



    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _mindR_lep1_jet = 0;
      _mindR_lep2_jet = 0;
      _mT_lep1 = 0;
      _dR_leps = 0;
      _mTauTauVis1 = 0;
      _mTauTauVis2 = 0;
      _dR_lep1_tau = 0; 
     
      _MVA_2lSS1tau_noMEM_ttbar = 0;
      _MVA_2lSS1tau_MEM_LR_ttbar = 0;    
      
      _MVA_2lSS1tau_noMEM_ttV = 0;
      _MVA_2lSS1tau_MEM_LR_ttV = 0;

      _MVA_2lSS1tau_noMEM_2Dbin = 0;
      _MVA_2lSS1tau_MEM_LR_2Dbin = 0;

      _category = 0;
      _n_recoPFJet = 0;
      _recoPFJet_px = 0;
      _recoPFJet_py = 0;
      _recoPFJet_pz = 0;
      _recoPFJet_e = 0;
      _recolep_sel_px = 0;
      _recolep_sel_py = 0;
      _recolep_sel_pz = 0;
      _recolep_sel_e = 0;
      _recolep_sel_conept = 0;
      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      _avg_dr_jet = 0;
      _PFMET = 0;
      _PFMET_phi = 0;
      _HTmiss = 0;    

      _Integral_ttH = 0;
      _Integral_ttZ = 0;
      _Integral_ttZ_Zll = 0;
      _Integral_ttbar_DL_fakelep_tlep = 0;
      _Integral_ttbar_DL_fakelep_ttau = 0;
      _integration_type = 0;      
 

      tree->GetEntry(i);

      if(_category==11 || _category==41 || _category==-11){

	TLorentzVector lep1((*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
	TLorentzVector lep2((*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);

	_mindR_lep1_jet = -10;
	_mindR_lep2_jet = -10;

	for(unsigned int i_jet=0;i_jet<_n_recoPFJet;i_jet++){

	  TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
	  if(jet.DeltaR(lep1)<_mindR_lep1_jet || _mindR_lep1_jet<0)
	    _mindR_lep1_jet = jet.DeltaR(lep1);
	  if(jet.DeltaR(lep2)<_mindR_lep2_jet || _mindR_lep2_jet<0)
	    _mindR_lep2_jet = jet.DeltaR(lep2);

	}

      

      _mT_lep1=sqrt( 2*(*_recolep_sel_conept)[0]*_PFMET*(1-cos(lep1.Phi()-_PFMET_phi)) );
      _dR_leps = lep1.DeltaR(lep2);      
      
      TLorentzVector tauh((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]);
      _mTauTauVis1 = (tauh+lep1).M();
      _mTauTauVis2 = (tauh+lep2).M();
      _dR_lep1_tau = tauh.DeltaR(lep1);

      njet = _n_recoPFJet;
      mindr_lep1_jet = _mindR_lep1_jet;
      mindr_lep2_jet = _mindR_lep2_jet;
      avg_dr_jet = _avg_dr_jet;
      max_lep_eta = max(abs(lep1.Eta()), abs(lep2.Eta()));
      mT_lep1 = _mT_lep1;
      dr_leps = _dR_leps;
      tau_pt = tauh.Pt();
      lep1_pt = (*_recolep_sel_conept)[0];
      lep2_pt = (*_recolep_sel_conept)[1];
      mTauTauVis1 = _mTauTauVis1;
      mTauTauVis2 = _mTauTauVis2;
      dr_lep1_tau = _dR_lep1_tau;
      
      //memOutput_type = _integration_type;
      if(_integration_type==0){
	float k_ttZ = 5e-2;
	float k_ttZ_Zll = 1e-1;
	float k_ttbar = 1e-17;
	memOutput_LR = _Integral_ttH>0 ? _Integral_ttH / (_Integral_ttH + k_ttZ*_Integral_ttZ + k_ttZ_Zll*_Integral_ttZ_Zll + k_ttbar*(_Integral_ttbar_DL_fakelep_tlep + _Integral_ttbar_DL_fakelep_ttau) ) : 0;
      }
      else{
	float k_ttZ = 5e-2;
	float k_ttZ_Zll = 1;
	float k_ttbar = 1e-14;
	memOutput_LR = _Integral_ttH>0 ? _Integral_ttH / (_Integral_ttH + k_ttZ*_Integral_ttZ + k_ttZ_Zll*_Integral_ttZ_Zll + k_ttbar*(_Integral_ttbar_DL_fakelep_tlep + _Integral_ttbar_DL_fakelep_ttau) ) : 0;
      }
      
      /*log_memOutput_ttH = _Integral_ttH>0 ? log(_Integral_ttH): -100;
      log_memOutput_ttZ = _Integral_ttZ>0 ? log(_Integral_ttZ): -100;
      log_memOutput_ttZ_Zll = _Integral_ttZ_Zll ? log(_Integral_ttZ_Zll) : -100;
      log_memOutput_tt = (_Integral_ttbar_DL_fakelep_tlep + _Integral_ttbar_DL_fakelep_ttau) ? log(_Integral_ttbar_DL_fakelep_tlep + _Integral_ttbar_DL_fakelep_ttau) : -100;*/
      
 

      _MVA_2lSS1tau_noMEM_ttbar = MVA_2lSS1tau_TT_noMEM_reader->EvaluateMVA("BDTG method");
      _MVA_2lSS1tau_MEM_LR_ttbar = MVA_2lSS1tau_TT_MEM_LR_reader->EvaluateMVA("BDTG method");
      /*_MVA_2lSS1tau_MEM_weights_ttbar = MVA_2lSS1tau_TT_MEM_weights_reader->EvaluateMVA("BDTG method");
      _MVA_2lSS1tau_MEM_weights_only_ttbar = MVA_2lSS1tau_TT_MEM_weights_only_reader->EvaluateMVA("BDTG method");*/


      _MVA_2lSS1tau_noMEM_ttV = MVA_2lSS1tau_TTV_noMEM_reader->EvaluateMVA("BDTG method");
      _MVA_2lSS1tau_MEM_LR_ttV = MVA_2lSS1tau_TTV_MEM_LR_reader->EvaluateMVA("BDTG method");
      /*_MVA_2lSS1tau_MEM_weights_ttV = MVA_2lSS1tau_TTV_MEM_weights_reader->EvaluateMVA("BDTG method");
      _MVA_2lSS1tau_MEM_weights_only_ttV = MVA_2lSS1tau_TTV_MEM_weights_only_reader->EvaluateMVA("BDTG method");*/
      }


      int i_bin = h_MVA_2Dbin->FindBin(_MVA_2lSS1tau_noMEM_ttbar,_MVA_2lSS1tau_noMEM_ttV);
      _MVA_2lSS1tau_noMEM_2Dbin = int(h_MVA_2Dbin->GetBinContent(i_bin));

      int i_bin2 = h_MVA_MEM_LR_2Dbin->FindBin(_MVA_2lSS1tau_MEM_LR_ttbar,_MVA_2lSS1tau_MEM_LR_ttV);
      _MVA_2lSS1tau_MEM_LR_2Dbin = int(h_MVA_MEM_LR_2Dbin->GetBinContent(i_bin2));

      tree_new->Fill();

    }
    
    
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}









void add_3l1tau_BDT(TString filein, TString fileout, vector<TString> treename){


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
    int _n_recoPFJet;
    vector<float>* _recoPFJet_px;
    vector<float>* _recoPFJet_py;
    vector<float>* _recoPFJet_pz;
    vector<float>* _recoPFJet_e;
    vector<float>* _recolep_sel_px;
    vector<float>* _recolep_sel_py;
    vector<float>* _recolep_sel_pz;
    vector<float>* _recolep_sel_e;
    vector<float>* _recolep_sel_conept;
    vector<float>* _recotauh_sel_px;
    vector<float>* _recotauh_sel_py;
    vector<float>* _recotauh_sel_pz;
    vector<float>* _recotauh_sel_e;
    float _avg_dr_jet;
    float _PFMET;
    float _PFMET_phi;
    float _HTmiss;    

    tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
    tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
    tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
    tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
    tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
    tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
    tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
    tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
    tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
    tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
    tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
    tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
    tree->SetBranchAddress("avg_dr_jet",&_avg_dr_jet);
    tree->SetBranchAddress("PFMET",&_PFMET);
    tree->SetBranchAddress("PFMET_phi",&_PFMET_phi);
    tree->SetBranchAddress("HTmiss",&_HTmiss);
    tree->SetBranchAddress("category",&_category);


    TTree* tree_new=tree->GetTree()->CloneTree(0);

    float _mindR_lep1_jet;
    float _mindR_lep2_jet;
    float _mindR_lep3_jet;
    float _mindR_tau_jet;
    float _mT_lep3;
    float _mTauTauVis2;
    float _dR_lep1_tau;
    float _dR_lep2_tau;
    float _dR_lep3_tau;

    float _MVA_3l1tau_ttbar;
    float _MVA_3l1tau_ttV;
    int _MVA_3l1tau_2Dbin;


    tree_new->Branch("mindR_lep1_jet",&_mindR_lep1_jet,"mindR_lep1_jet/F");
    tree_new->Branch("mindR_lep2_jet",&_mindR_lep2_jet,"mindR_lep2_jet/F");
    tree_new->Branch("mindR_lep3_jet",&_mindR_lep3_jet,"mindR_lep3_jet/F");
    tree_new->Branch("mindR_tau_jet",&_mindR_tau_jet,"mindR_tau_jet/F");
    tree_new->Branch("mT_lep3",&_mT_lep3,"mT_lep3/F");
    tree_new->Branch("mTauTauVis2",&_mTauTauVis2,"mTauTauVis2/F");
    tree_new->Branch("dR_lep1_tau",&_dR_lep1_tau,"dR_lep1_tau/F");
    tree_new->Branch("dR_lep2_tau",&_dR_lep2_tau,"dR_lep2_tau/F");
    tree_new->Branch("dR_lep3_tau",&_dR_lep3_tau,"dR_lep3_tau/F");

    tree_new->Branch("MVA_3l1tau_ttbar",&_MVA_3l1tau_ttbar,"MVA_3l1tau_ttbar/F");
    tree_new->Branch("MVA_3l1tau_ttV",&_MVA_3l1tau_ttV,"MVA_3l1tau_ttV/F");
    tree_new->Branch("MVA_3l1tau_2Dbin",&_MVA_3l1tau_2Dbin,"MVA_3l1tau_2Dbin/I");

    TMVA::Reader* MVA_3l1tau_TT_reader = Book_3l1tau_TT_MVAReader("3l1tau_MVA_weights","/3l_1tau_ttbar_BDTG.weights.xml");
    TMVA::Reader* MVA_3l1tau_TTV_reader = Book_3l1tau_TTV_MVAReader("3l1tau_MVA_weights","/3l_1tau_ttV_BDTG.weights.xml");


    TFile* f_MVA_2Dbin = TFile::Open("3l1tau_MVA_weights/3l_1tau_BDT_mapping.root");
    TH2F* h_MVA_2Dbin = (TH2F*)f_MVA_2Dbin->Get("hTargetBinning");
    h_MVA_2Dbin->SetDirectory(0);
    f_MVA_2Dbin->Close();    


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _mindR_lep1_jet = 0;
      _mindR_lep2_jet = 0;
      _mindR_lep3_jet = 0;
      _mindR_tau_jet = 0;
      _mT_lep3 = 0;
      _mTauTauVis2 = 0;
      _dR_lep1_tau = 0;
      _dR_lep2_tau = 0;
      _dR_lep3_tau = 0;     

      _MVA_3l1tau_ttbar = 0;
      _MVA_3l1tau_ttV = 0;
      _MVA_3l1tau_2Dbin = 0;

      _category = 0;
      _n_recoPFJet = 0;
      _recoPFJet_px = 0;
      _recoPFJet_py = 0;
      _recoPFJet_pz = 0;
      _recoPFJet_e = 0;
      _recolep_sel_px = 0;
      _recolep_sel_py = 0;
      _recolep_sel_pz = 0;
      _recolep_sel_e = 0;
      _recolep_sel_conept = 0;
      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      _avg_dr_jet = 0;
      _PFMET = 0;
      _PFMET_phi = 0;
      _HTmiss = 0;    

 
      tree->GetEntry(i);

      if(_category==16 || _category==46){

	TLorentzVector lep1((*_recolep_sel_px)[0],(*_recolep_sel_py)[0],(*_recolep_sel_pz)[0],(*_recolep_sel_e)[0]);
	TLorentzVector lep2((*_recolep_sel_px)[1],(*_recolep_sel_py)[1],(*_recolep_sel_pz)[1],(*_recolep_sel_e)[1]);
	TLorentzVector lep3((*_recolep_sel_px)[2],(*_recolep_sel_py)[2],(*_recolep_sel_pz)[2],(*_recolep_sel_e)[2]);

	_mT_lep3=sqrt( 2*(*_recolep_sel_conept)[2]*_PFMET*(1-cos(lep3.Phi()-_PFMET_phi)) );
	
	TLorentzVector tauh((*_recotauh_sel_px)[0],(*_recotauh_sel_py)[0],(*_recotauh_sel_pz)[0],(*_recotauh_sel_e)[0]);
	_mTauTauVis2 = (tauh+lep2).M();
	_dR_lep1_tau = tauh.DeltaR(lep1);
	_dR_lep2_tau = tauh.DeltaR(lep2);
	_dR_lep3_tau = tauh.DeltaR(lep3);
	
	_mindR_lep1_jet = -10;
	_mindR_lep2_jet = -10;
	_mindR_lep3_jet = -10;
	_mindR_tau_jet = -10;


	for(unsigned int i_jet=0;i_jet<_n_recoPFJet;i_jet++){

	  TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
	  if(jet.DeltaR(lep1)<_mindR_lep1_jet || _mindR_lep1_jet<0)
	    _mindR_lep1_jet = jet.DeltaR(lep1);
	  if(jet.DeltaR(lep2)<_mindR_lep2_jet || _mindR_lep2_jet<0)
	    _mindR_lep2_jet = jet.DeltaR(lep2);
	  if(jet.DeltaR(lep3)<_mindR_lep3_jet || _mindR_lep3_jet<0)
	    _mindR_lep3_jet = jet.DeltaR(lep3);
	  if(jet.DeltaR(tauh)<_mindR_tau_jet || _mindR_tau_jet<0)
	    _mindR_tau_jet = jet.DeltaR(tauh);	  

	}      


	njet = _n_recoPFJet;
	mindr_lep1_jet = _mindR_lep1_jet;
	mindr_lep2_jet = _mindR_lep2_jet;
	mindr_lep3_jet = _mindR_lep3_jet;
	mindr_tau_jet = _mindR_tau_jet;
	avg_dr_jet = _avg_dr_jet;
	mT_lep3 = _mT_lep3;
	tau_pt = tauh.Pt();
	abs_tau_eta = abs(tauh.Eta());   
	dr_lep1_tau = _dR_lep1_tau;
	dr_lep2_tau = _dR_lep2_tau;
	dr_lep3_tau = _dR_lep3_tau;       
	lep1_pt = (*_recolep_sel_conept)[0];
	lep2_pt = (*_recolep_sel_conept)[1];
	lep3_pt = (*_recolep_sel_conept)[2];
	mTauTauVis2 = _mTauTauVis2;
            
	_MVA_3l1tau_ttbar = MVA_3l1tau_TT_reader->EvaluateMVA("BDTG method");
	_MVA_3l1tau_ttV = MVA_3l1tau_TTV_reader->EvaluateMVA("BDTG method");

      }

      int i_bin = h_MVA_2Dbin->FindBin(_MVA_3l1tau_ttbar,_MVA_3l1tau_ttV);
      _MVA_3l1tau_2Dbin = int(h_MVA_2Dbin->GetBinContent(i_bin));

      tree_new->Fill();

    }
    
    
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}






void test_BDT(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3_BDT_3l1tau.root";
  vector<TString> tree;
  tree.push_back("HTauTauTree_1l_2tau");
  tree.push_back("HTauTauTree_1l_2tau_fake_CR");
  tree.push_back("HTauTauTree_2lSS");
  tree.push_back("HTauTauTree_2lSS_lepMVA_CR");
  tree.push_back("HTauTauTree_2lOS_CR");
  tree.push_back("HTauTauTree_3l");
  tree.push_back("HTauTauTree_3l_ttZ_CR");
  tree.push_back("HTauTauTree_3l_lepMVA_CR");

  add_3l1tau_BDT(filein,fileout,tree);

  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3_BDT_3l1tau.root";

  vector<TString> tree;
  tree.push_back("T");
  add_2lS_BDT(filein,fileout,tree);*/

}
