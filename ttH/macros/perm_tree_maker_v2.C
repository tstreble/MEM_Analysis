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




void make_perm_tree(TString filename_in, TString filename_out, TString treename){

  
  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }

  //Old branches used
  
  vector<float> *_gentop_e = 0;
  vector<float> *_gentop_px = 0;
  vector<float> *_gentop_py = 0;
  vector<float> *_gentop_pz = 0;
  vector<int> *_gentop_decayMode = 0;

  vector<float> *_genW_e = 0;
  vector<float> *_genW_px = 0;
  vector<float> *_genW_py = 0;
  vector<float> *_genW_pz = 0;
  vector<int> *_genW_TopMothInd = 0;

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
  vector<int> *_genq_TopMothInd = 0;
  vector<int> *_genq_WMothInd = 0;
  vector<int> *_genq_flags = 0;

  vector<float> *_recoPFJet_e = 0;
  vector<float> *_recoPFJet_px = 0;
  vector<float> *_recoPFJet_py = 0;
  vector<float> *_recoPFJet_pz = 0;
  vector<float> *_recoPFJet_CSVscore = 0;


  tree->SetBranchAddress("gentop_e",&_gentop_e);
  tree->SetBranchAddress("gentop_px",&_gentop_px);
  tree->SetBranchAddress("gentop_py",&_gentop_py);
  tree->SetBranchAddress("gentop_pz",&_gentop_pz);
  tree->SetBranchAddress("gentop_decayMode",&_gentop_decayMode);

  tree->SetBranchAddress("genW_e",&_genW_e);
  tree->SetBranchAddress("genW_px",&_genW_px);
  tree->SetBranchAddress("genW_py",&_genW_py);
  tree->SetBranchAddress("genW_pz",&_genW_pz);
  tree->SetBranchAddress("genW_TopMothInd",&_genW_TopMothInd);

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
  tree->SetBranchAddress("genq_WMothInd",&_genq_WMothInd);
  tree->SetBranchAddress("genq_TopMothInd",&_genq_TopMothInd);
  tree->SetBranchAddress("genq_flags",&_genq_flags);


  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);



  Long64_t nentries = tree->GetEntries();

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");


  TTree* tree_new=tree->GetTree()->CloneTree(0);

  int _n_max_matched_jet;
  bool _isGoodPerm;

  float _recoPFJet_bh_e;
  float _recoPFJet_bh_px;
  float _recoPFJet_bh_py;
  float _recoPFJet_bh_pz;
  float _recoPFJet_bh_pt;
  float _recoPFJet_bh_eta;
  float _recoPFJet_bh_phi;
  float _recoPFJet_bh_CSVscore;

  float _recoPFJet_bl_e;
  float _recoPFJet_bl_px;
  float _recoPFJet_bl_py;
  float _recoPFJet_bl_pz;
  float _recoPFJet_bl_pt;
  float _recoPFJet_bl_eta;
  float _recoPFJet_bl_phi;
  float _recoPFJet_bl_CSVscore;

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

  float _recoPFJet_MW;
  float _recoPFJet_MTop;
  float _recoPFJet_top_pt;
  float _recoPFJet_Whad_pt;
  float _recoPFJet_dR_Whad;
  float _recoPFJet_dR_bWhad;
  float _recoPFJet_top_ME;
  

  tree_new->Branch("n_max_matched_jet",&_n_max_matched_jet,"n_max_matched_jet/I");
  tree_new->Branch("isGoodPerm",            &_isGoodPerm,            "isGoodPerm/O");

  tree_new->Branch("recoPFJet_bh_e",        &_recoPFJet_bh_e,        "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_px",       &_recoPFJet_bh_px,       "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_py",       &_recoPFJet_bh_py,       "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_pz",       &_recoPFJet_bh_pz,       "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_pt",       &_recoPFJet_bh_pt,       "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_eta",      &_recoPFJet_bh_eta,      "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_phi",      &_recoPFJet_bh_phi,      "recoPFJet_bh_e/F");
  tree_new->Branch("recoPFJet_bh_CSVscore", &_recoPFJet_bh_CSVscore, "recoPFJet_bh_e/F");
  	  
  tree_new->Branch("recoPFJet_q1_e",        &_recoPFJet_q1_e,        "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_px",       &_recoPFJet_q1_px,       "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_py",       &_recoPFJet_q1_py,       "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_pz",       &_recoPFJet_q1_pz,       "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_pt",       &_recoPFJet_q1_pt,       "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_eta",      &_recoPFJet_q1_eta,      "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_phi",      &_recoPFJet_q1_phi,      "recoPFJet_q1_e/F");
  tree_new->Branch("recoPFJet_q1_CSVscore", &_recoPFJet_q1_CSVscore, "recoPFJet_q1_e/F");
  	  
  tree_new->Branch("recoPFJet_q2_e",        &_recoPFJet_q2_e,        "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_px",       &_recoPFJet_q2_px,       "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_py",       &_recoPFJet_q2_py,       "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_pz",       &_recoPFJet_q2_pz,       "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_pt",       &_recoPFJet_q2_pt,       "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_eta",      &_recoPFJet_q2_eta,      "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_phi",      &_recoPFJet_q2_phi,      "recoPFJet_q2_e/F");
  tree_new->Branch("recoPFJet_q2_CSVscore", &_recoPFJet_q2_CSVscore, "recoPFJet_q2_e/F");
  	  
  tree_new->Branch("recoPFJet_bl_e",        &_recoPFJet_bl_e,        "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_px",       &_recoPFJet_bl_px,       "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_py",       &_recoPFJet_bl_py,       "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_pz",       &_recoPFJet_bl_pz,       "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_pt",       &_recoPFJet_bl_pt,       "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_eta",      &_recoPFJet_bl_eta,      "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_phi",      &_recoPFJet_bl_phi,      "recoPFJet_bl_e/F");
  tree_new->Branch("recoPFJet_bl_CSVscore", &_recoPFJet_bl_CSVscore, "recoPFJet_bl_e/F");

  tree_new->Branch("recoPFJet_MW",      &_recoPFJet_MW,      "recoPFJet_MW/F");
  tree_new->Branch("recoPFJet_MTop",    &_recoPFJet_MTop,    "recoPFJet_MTop/F");
  tree_new->Branch("recoPFJet_top_pt",  &_recoPFJet_top_pt,  "recoPFJet_top_pt/F");
  tree_new->Branch("recoPFJet_Whad_pt", &_recoPFJet_Whad_pt, "recoPFJet_Whad_pt/F");
  tree_new->Branch("recoPFJet_dR_Whad",  &_recoPFJet_dR_Whad,  "recoPFJet_dR_Whad/F");
  tree_new->Branch("recoPFJet_dR_bWhad", &_recoPFJet_dR_bWhad, "recoPFJet_dR_bWhad/F");


  for (int i=0;i<nentries;i++) {

    if(i%1000==0)
      cout<<"i="<<i<<endl;
    
    
    _gentop_e = 0;
    _gentop_px = 0;
    _gentop_py = 0;
    _gentop_pz = 0;
    _gentop_decayMode = 0;
    
    _genW_e = 0;
    _genW_px = 0;
    _genW_py = 0;
    _genW_pz = 0;
    _genW_TopMothInd = 0;
    
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
    _genq_TopMothInd = 0;
    _genq_WMothInd = 0;
    _genq_flags = 0;
    
    _recoPFJet_e = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;


    _n_max_matched_jet = -1;
    _isGoodPerm = false;

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

    _recoPFJet_MW = -9999;
    _recoPFJet_MTop = -9999;
    _recoPFJet_top_pt = -9999;
    _recoPFJet_Whad_pt = -9999;
    _recoPFJet_dR_Whad = -9999;
    _recoPFJet_dR_bWhad = -9999;
    _recoPFJet_top_ME = -9999;

    tree->GetEntry(i);


    bool top0_had = (*_gentop_decayMode)[0]==0;
    bool top1_had = (*_gentop_decayMode)[1]==0;
    bool top0_lep = (*_gentop_decayMode)[0]==1 || (*_gentop_decayMode)[0]==2 ;
    bool top1_lep = (*_gentop_decayMode)[1]==1 || (*_gentop_decayMode)[1]==2 ;

    if( ! ( ( (top0_had && top1_lep) || (top1_had && top0_lep) ) ) )
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

    for(int ib=0; ib<(*_genb_e).size(); ib++){

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
    
    
    float _genbl_e = (*_genb_e)[ibl];
    float _genbl_px = (*_genb_px)[ibl];
    float _genbl_py = (*_genb_py)[ibl];
    float _genbl_pz = (*_genb_pz)[ibl];

    TLorentzVector genbl_tlv(_genbl_px,_genbl_py,_genbl_pz,_genbl_e);
    
    float _genbh_e = (*_genb_e)[ibh];
    float _genbh_px = (*_genb_px)[ibh];
    float _genbh_py = (*_genb_py)[ibh];
    float _genbh_pz = (*_genb_pz)[ibh];

    TLorentzVector genbh_tlv(_genbh_px,_genbh_py,_genbh_pz,_genbh_e);


    //W
    int iWh = -1;

    for(unsigned int iW=0; iW<(*_genW_TopMothInd).size(); iW++){

      if( (*_genW_TopMothInd)[iW]==itop_th ){
	iWh = iW;  
	break;
      }

    }


    //Light quarks

    int iq1=-1;
    int iq2=-1;

    for(int iq=0; iq<(*_genq_e).size(); iq++){

      bool isFromHardProcess = ( (*_genq_flags)[iq] >> 8 ) & 1;
      int WMothInd = (*_genq_TopMothInd)[iq];

      if( !( WMothInd==iWh && isFromHardProcess ) )
	continue;
     
      if(iq1==-1)
	iq1=iq;
      else
	iq2=iq;

    }    

    float _genq1_e = (*_genq_e)[iq1];
    float _genq1_px = (*_genq_px)[iq1];
    float _genq1_py = (*_genq_py)[iq1];
    float _genq1_pz = (*_genq_pz)[iq1];    

    TLorentzVector genq1_tlv(_genq1_px,_genq1_py,_genq1_pz,_genq1_e);

    float _genq2_e = (*_genq_e)[iq2];
    float _genq2_px = (*_genq_px)[iq2];
    float _genq2_py = (*_genq_py)[iq2];
    float _genq2_pz = (*_genq_pz)[iq2];

    TLorentzVector genq2_tlv(_genq2_px,_genq2_py,_genq2_pz,_genq2_e);

    
    _n_max_matched_jet = 0;

    int i_jet_genbh = -1;
    float dR_jet_genbh = -1;
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_e).size();i_jet++){

      TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
      float dR=jet.DeltaR(genbh_tlv);
      if(dR<0.5 && (dR<dR_jet_genbh || i_jet_genbh<0)){
	dR_jet_genbh = dR;
	i_jet_genbh = i_jet;
      }

    }
    if(i_jet_genbh>=0) 	_n_max_matched_jet++;


    int i_jet_genbl = -1;
    float dR_jet_genbl = -1;
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_e).size();i_jet++){

      if(i_jet==i_jet_genbh) continue;

      TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
      float dR=jet.DeltaR(genbl_tlv);
      if(dR<0.5 && (dR<dR_jet_genbl || i_jet_genbl<0)){
	dR_jet_genbl = dR;
	i_jet_genbl = i_jet;
      }

    }
    if(i_jet_genbl>=0) 	_n_max_matched_jet++;


    int i_jet_genq1 = -1;
    float dR_jet_genq1 = -1;
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_e).size();i_jet++){

      if(i_jet==i_jet_genbh || i_jet==i_jet_genbl) continue;

      TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
      float dR=jet.DeltaR(genq1_tlv);
      if(dR<0.5 && (dR<dR_jet_genq1 || i_jet_genq1<0)){
	dR_jet_genq1 = dR;
	i_jet_genq1 = i_jet;
      }

    }
    if(i_jet_genq1>=0) 	_n_max_matched_jet++;


    int i_jet_genq2 = -1;
    float dR_jet_genq2 = -1;
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_e).size();i_jet++){

      if(i_jet==i_jet_genbh || i_jet==i_jet_genbl || i_jet==i_jet_genq1) continue;

      TLorentzVector jet((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
      float dR=jet.DeltaR(genq2_tlv);
      if(dR<0.5 && (dR<dR_jet_genq2 || i_jet_genq2<0)){
	dR_jet_genq2 = dR;
	i_jet_genq2 = i_jet;
      }

    }
    if(i_jet_genq2>=0) 	_n_max_matched_jet++;




    for(unsigned int i_jet1 = 0; i_jet1<(*_recoPFJet_e).size(); i_jet1++){

      TLorentzVector jet_bh((*_recoPFJet_px)[i_jet1], (*_recoPFJet_py)[i_jet1], (*_recoPFJet_pz)[i_jet1], (*_recoPFJet_e)[i_jet1]);

      _recoPFJet_bh_e = jet_bh.E();
      _recoPFJet_bh_px = jet_bh.Px();
      _recoPFJet_bh_py = jet_bh.Py();
      _recoPFJet_bh_pz = jet_bh.Pz();
      _recoPFJet_bh_pt = jet_bh.Pt(); 
      _recoPFJet_bh_eta = jet_bh.Eta();
      _recoPFJet_bh_phi = jet_bh.Phi();
      _recoPFJet_bh_CSVscore = (*_recoPFJet_CSVscore)[i_jet1];

      for(unsigned int i_jet2 = 0; i_jet2<(*_recoPFJet_e).size(); i_jet2++){

	if(i_jet2==i_jet1) continue;

	TLorentzVector jet_q1((*_recoPFJet_px)[i_jet2], (*_recoPFJet_py)[i_jet2], (*_recoPFJet_pz)[i_jet2], (*_recoPFJet_e)[i_jet2]);

	_recoPFJet_q1_e = jet_q1.E();
	_recoPFJet_q1_px = jet_q1.Px();
	_recoPFJet_q1_py = jet_q1.Py();
	_recoPFJet_q1_pz = jet_q1.Pz();
	_recoPFJet_q1_pt = jet_q1.Pt(); 
	_recoPFJet_q1_eta = jet_q1.Eta();
	_recoPFJet_q1_phi = jet_q1.Phi();
	_recoPFJet_q1_CSVscore = (*_recoPFJet_CSVscore)[i_jet2];
      
	for(unsigned int i_jet3 = 0; i_jet3<(*_recoPFJet_e).size(); i_jet3++){

	if(i_jet3==i_jet1 || i_jet3<=i_jet2) continue;


	  TLorentzVector jet_q2((*_recoPFJet_px)[i_jet3], (*_recoPFJet_py)[i_jet3], (*_recoPFJet_pz)[i_jet3], (*_recoPFJet_e)[i_jet3]);

	  _recoPFJet_q2_e = jet_q2.E();
	  _recoPFJet_q2_px = jet_q2.Px();
	  _recoPFJet_q2_py = jet_q2.Py();
	  _recoPFJet_q2_pz = jet_q2.Pz();
	  _recoPFJet_q2_pt = jet_q2.Pt(); 
	  _recoPFJet_q2_eta = jet_q2.Eta();
	  _recoPFJet_q2_phi = jet_q2.Phi();
	  _recoPFJet_q2_CSVscore = (*_recoPFJet_CSVscore)[i_jet3];

	  for(unsigned int i_jet4 = 0; i_jet4<(*_recoPFJet_e).size(); i_jet4++){

	    if(i_jet4==i_jet1 || i_jet4==i_jet2 || i_jet4==i_jet3) continue;

	    TLorentzVector jet_bl((*_recoPFJet_px)[i_jet4], (*_recoPFJet_py)[i_jet4], (*_recoPFJet_pz)[i_jet4], (*_recoPFJet_e)[i_jet4]);

	    _recoPFJet_bl_e = jet_bl.E();
	    _recoPFJet_bl_px = jet_bl.Px();
	    _recoPFJet_bl_py = jet_bl.Py();
	    _recoPFJet_bl_pz = jet_bl.Pz();
	    _recoPFJet_bl_pt = jet_bl.Pt(); 
	    _recoPFJet_bl_eta = jet_bl.Eta();
	    _recoPFJet_bl_phi = jet_bl.Phi();
	    _recoPFJet_bl_CSVscore = (*_recoPFJet_CSVscore)[i_jet4];


	    if(jet_bh.DeltaR(genbh_tlv)<0.5 && jet_bl.DeltaR(genbl_tlv)<0.5
	       && jet_q1.DeltaR(genq1_tlv)<0.5 && jet_q2.DeltaR(genq2_tlv)<0.5)
	      _isGoodPerm = true;
	    else
	      _isGoodPerm = false;

	    TLorentzVector jets_top = jet_bh+jet_q1+jet_q2;
	    TLorentzVector jets_Wh = jet_q1+jet_q2;

	    _recoPFJet_MW = jets_Wh.M();
	    _recoPFJet_MTop = jets_top.M();	    
	    _recoPFJet_top_pt = jets_top.Pt();
	    _recoPFJet_Whad_pt = jets_Wh.Pt();
	    _recoPFJet_dR_Whad = jet_q1.DeltaR(jet_q2);
	    _recoPFJet_dR_bWhad = jet_bh.DeltaR(jets_Wh);
	    _recoPFJet_top_ME = (jet_bh.Dot(jet_q1))*(jets_top.Dot(jet_q2)) + (jet_bh.Dot(jet_q2))*(jets_top.Dot(jet_q1));
	    
	    tree_new->Fill();


	  }

	}

      }

    }


  }


  tree_new->Write();

  f_new->Close();


  return;


}
