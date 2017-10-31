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
#include <algorithm>

using namespace std;


void add_old_dR_tree(TString filename_in, TString filename_out, TString treename){


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

  vector<float> *_recoPFJet_btag_e = 0;
  vector<float> *_recoPFJet_btag_px = 0;
  vector<float> *_recoPFJet_btag_py = 0;
  vector<float> *_recoPFJet_btag_pz = 0;

  vector<float> *_recoPFJet_untag_Wtag_e = 0;
  vector<float> *_recoPFJet_untag_Wtag_px = 0;
  vector<float> *_recoPFJet_untag_Wtag_py = 0;
  vector<float> *_recoPFJet_untag_Wtag_pz = 0;

  vector<float> *_recoPFJet_e = 0;
  vector<float> *_recoPFJet_px = 0;
  vector<float> *_recoPFJet_py = 0;
  vector<float> *_recoPFJet_pz = 0;


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

  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);
  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);

  tree->SetBranchAddress("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);

  Long64_t nentries = tree->GetEntries();

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");



  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _dR_sum_min;
  int _n_matched_jet;
  int _n_max_matched_jet;

  tree_new->Branch("dR_sum_min_old",&_dR_sum_min,"dR_sum_min_old/F");
  tree_new->Branch("n_matched_jet_old",&_n_matched_jet,"n_matched_jet_old/I");
  tree_new->Branch("n_max_matched_jet",&_n_max_matched_jet,"n_max_matched_jet/I");


  for (int i=0;i<nentries;i++) {
  //for (int i=42;i<43;i++) {

    if(i%10000==0)
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
    
    _recoPFJet_btag_e = 0;
    _recoPFJet_btag_px = 0;
    _recoPFJet_btag_py = 0;
    _recoPFJet_btag_pz = 0;
    
    _recoPFJet_untag_Wtag_e = 0;
    _recoPFJet_untag_Wtag_px = 0;
    _recoPFJet_untag_Wtag_py = 0;
    _recoPFJet_untag_Wtag_pz = 0;


    _dR_sum_min = -1;
    _n_matched_jet = -1;
    _n_max_matched_jet = -1;

    tree->GetEntry(i);

    bool top0_had = (*_gentop_decayMode)[0]==0;
    bool top1_had = (*_gentop_decayMode)[1]==0;
    bool top0_lep = (*_gentop_decayMode)[0]==1 || (*_gentop_decayMode)[0]==2 ;
    bool top1_lep = (*_gentop_decayMode)[1]==1 || (*_gentop_decayMode)[1]==2 ;

    if( ( ( (top0_had && top1_lep) || (top1_had && top0_lep) ) ) ){

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

    float _bjet1_e = (*_recoPFJet_btag_e)[0];
    float _bjet1_px = (*_recoPFJet_btag_px)[0];
    float _bjet1_py = (*_recoPFJet_btag_py)[0];
    float _bjet1_pz = (*_recoPFJet_btag_pz)[0];
    
    TLorentzVector bjet1_tlv(_bjet1_px,_bjet1_py,_bjet1_pz,_bjet1_e);

    float _bjet2_e = (*_recoPFJet_btag_e)[1];
    float _bjet2_px = (*_recoPFJet_btag_px)[1];
    float _bjet2_py = (*_recoPFJet_btag_py)[1];
    float _bjet2_pz = (*_recoPFJet_btag_pz)[1];
    
    TLorentzVector bjet2_tlv(_bjet2_px,_bjet2_py,_bjet2_pz,_bjet2_e);

    float _jet1_e = (*_recoPFJet_untag_Wtag_e)[0];
    float _jet1_px = (*_recoPFJet_untag_Wtag_px)[0];
    float _jet1_py = (*_recoPFJet_untag_Wtag_py)[0];
    float _jet1_pz = (*_recoPFJet_untag_Wtag_pz)[0];
    
    TLorentzVector jet1_tlv(_jet1_px,_jet1_py,_jet1_pz,_jet1_e);

    float _jet2_e = (*_recoPFJet_untag_Wtag_e)[1];
    float _jet2_px = (*_recoPFJet_untag_Wtag_px)[1];
    float _jet2_py = (*_recoPFJet_untag_Wtag_py)[1];
    float _jet2_pz = (*_recoPFJet_untag_Wtag_pz)[1];
    
    TLorentzVector jet2_tlv(_jet2_px,_jet2_py,_jet2_pz,_jet2_e); 
    
    float dR0 = genbh_tlv.DeltaR(bjet1_tlv) + genbl_tlv.DeltaR(bjet2_tlv) + genq1_tlv.DeltaR(jet1_tlv) + genq2_tlv.DeltaR(jet2_tlv);
    float dR1 = genbh_tlv.DeltaR(bjet2_tlv) + genbl_tlv.DeltaR(bjet1_tlv) + genq1_tlv.DeltaR(jet1_tlv) + genq2_tlv.DeltaR(jet2_tlv);
    float dR2 = genbh_tlv.DeltaR(bjet1_tlv) + genbl_tlv.DeltaR(bjet2_tlv) + genq1_tlv.DeltaR(jet2_tlv) + genq2_tlv.DeltaR(jet1_tlv);
    float dR3 = genbh_tlv.DeltaR(bjet2_tlv) + genbl_tlv.DeltaR(bjet1_tlv) + genq1_tlv.DeltaR(jet2_tlv) + genq2_tlv.DeltaR(jet1_tlv);


    _dR_sum_min = min(min(dR0,dR1),min(dR2,dR3));

    _n_matched_jet = 0;
 

    if(bjet1_tlv.DeltaR(genbh_tlv)<0.5 || bjet1_tlv.DeltaR(genbl_tlv)<0.5)
      _n_matched_jet++;
    
    if((bjet2_tlv.DeltaR(genbh_tlv)<0.5 && bjet1_tlv.DeltaR(genbh_tlv)>0.5) || (bjet2_tlv.DeltaR(genbl_tlv)<0.5 && bjet1_tlv.DeltaR(genbl_tlv)>0.5))
      _n_matched_jet++;
    
    if(jet1_tlv.DeltaR(genq1_tlv)<0.5 || jet1_tlv.DeltaR(genq2_tlv)<0.5)
      _n_matched_jet++;

    if((jet2_tlv.DeltaR(genq1_tlv)<0.5 && jet1_tlv.DeltaR(genq1_tlv)>0.5) || (jet2_tlv.DeltaR(genq2_tlv)<0.5 && jet1_tlv.DeltaR(genq2_tlv)>0.5))
      _n_matched_jet++;

	

    /*if(genbh_tlv.DeltaR(bjet1_tlv)<0.5 || genbh_tlv.DeltaR(bjet2_tlv)<0.5){
      _n_matched_jet++;
    }
    if(genbl_tlv.DeltaR(bjet1_tlv)<0.5 || genbl_tlv.DeltaR(bjet2_tlv)<0.5){
      _n_matched_jet++;
    }


    if(genq1_tlv.DeltaR(jet1_tlv)<0.5 || genq1_tlv.DeltaR(jet2_tlv)<0.5){
      _n_matched_jet++;
    }
    if(genq2_tlv.DeltaR(jet1_tlv)<0.5 || genq2_tlv.DeltaR(jet2_tlv)<0.5){
      _n_matched_jet++;
    }*/


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




    }






    tree_new->Fill();

  }

 f_new->cd();

 tree_new->Write();
 f_new->Close();

 
 return;
 
}






void add_new_dR_tree(TString filename_in, TString filename_out, TString treename){


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

  float _recoPFJet_toptag_best_btag_e;
  float _recoPFJet_toptag_best_btag_px;
  float _recoPFJet_toptag_best_btag_py;
  float _recoPFJet_toptag_best_btag_pz;

  float _recoPFJet_toptag_best_untag1_e;
  float _recoPFJet_toptag_best_untag1_px;
  float _recoPFJet_toptag_best_untag1_py;
  float _recoPFJet_toptag_best_untag1_pz;

  float _recoPFJet_toptag_best_untag2_e;
  float _recoPFJet_toptag_best_untag2_px;
  float _recoPFJet_toptag_best_untag2_py;
  float _recoPFJet_toptag_best_untag2_pz;

  float _recoPFJet_toptag_other_btag_e;
  float _recoPFJet_toptag_other_btag_px;
  float _recoPFJet_toptag_other_btag_py;
  float _recoPFJet_toptag_other_btag_pz;


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

  tree->SetBranchAddress("recoPFJet_toptag_best_btag_e",&_recoPFJet_toptag_best_btag_e);
  tree->SetBranchAddress("recoPFJet_toptag_best_btag_px",&_recoPFJet_toptag_best_btag_px);
  tree->SetBranchAddress("recoPFJet_toptag_best_btag_py",&_recoPFJet_toptag_best_btag_py);
  tree->SetBranchAddress("recoPFJet_toptag_best_btag_pz",&_recoPFJet_toptag_best_btag_pz);
       
  tree->SetBranchAddress("recoPFJet_toptag_best_untag1_e",&_recoPFJet_toptag_best_untag1_e);
  tree->SetBranchAddress("recoPFJet_toptag_best_untag1_px",&_recoPFJet_toptag_best_untag1_px);
  tree->SetBranchAddress("recoPFJet_toptag_best_untag1_py",&_recoPFJet_toptag_best_untag1_py);
  tree->SetBranchAddress("recoPFJet_toptag_best_untag1_pz",&_recoPFJet_toptag_best_untag1_pz);
       
  tree->SetBranchAddress("recoPFJet_toptag_best_untag2_e",&_recoPFJet_toptag_best_untag2_e);
  tree->SetBranchAddress("recoPFJet_toptag_best_untag2_px",&_recoPFJet_toptag_best_untag2_px);
  tree->SetBranchAddress("recoPFJet_toptag_best_untag2_py",&_recoPFJet_toptag_best_untag2_py);
  tree->SetBranchAddress("recoPFJet_toptag_best_untag2_pz",&_recoPFJet_toptag_best_untag2_pz);
       
  tree->SetBranchAddress("recoPFJet_toptag_other_btag_e",&_recoPFJet_toptag_other_btag_e);
  tree->SetBranchAddress("recoPFJet_toptag_other_btag_px",&_recoPFJet_toptag_other_btag_px);
  tree->SetBranchAddress("recoPFJet_toptag_other_btag_py",&_recoPFJet_toptag_other_btag_py);
  tree->SetBranchAddress("recoPFJet_toptag_other_btag_pz",&_recoPFJet_toptag_other_btag_pz);



  Long64_t nentries = tree->GetEntries();

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");



  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _dR_sum_min;
  int _n_matched_jet;

  tree_new->Branch("dR_sum_min_new",&_dR_sum_min,"dR_sum_min_new/F");
  tree_new->Branch("n_matched_jet_new",&_n_matched_jet,"n_matched_jet_new/I");



  for (int i=0;i<nentries;i++) {
  
    if(i%10000==0)
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

    _recoPFJet_toptag_best_btag_e = 0;
    _recoPFJet_toptag_best_btag_px = 0;
    _recoPFJet_toptag_best_btag_py = 0;
    _recoPFJet_toptag_best_btag_pz = 0;
    
    _recoPFJet_toptag_best_untag1_e = 0;
    _recoPFJet_toptag_best_untag1_px = 0;
    _recoPFJet_toptag_best_untag1_py = 0;
    _recoPFJet_toptag_best_untag1_pz = 0;
    
    _recoPFJet_toptag_best_untag2_e = 0;
    _recoPFJet_toptag_best_untag2_px = 0;
    _recoPFJet_toptag_best_untag2_py = 0;
    _recoPFJet_toptag_best_untag2_pz = 0;
    
    _recoPFJet_toptag_other_btag_e = 0;
    _recoPFJet_toptag_other_btag_px = 0;
    _recoPFJet_toptag_other_btag_py = 0;
    _recoPFJet_toptag_other_btag_pz = 0;


    _dR_sum_min = -1;
    _n_matched_jet = -1;

    tree->GetEntry(i);

    bool top0_had = (*_gentop_decayMode)[0]==0;
    bool top1_had = (*_gentop_decayMode)[1]==0;
    bool top0_lep = (*_gentop_decayMode)[0]==1 || (*_gentop_decayMode)[0]==2 ;
    bool top1_lep = (*_gentop_decayMode)[1]==1 || (*_gentop_decayMode)[1]==2 ;

    if( ( ( (top0_had && top1_lep) || (top1_had && top0_lep) ) ) ){

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

    float _bjeth_e = _recoPFJet_toptag_best_btag_e;
    float _bjeth_px = _recoPFJet_toptag_best_btag_px;
    float _bjeth_py = _recoPFJet_toptag_best_btag_py;
    float _bjeth_pz = _recoPFJet_toptag_best_btag_pz;
    
    TLorentzVector bjeth_tlv(_bjeth_px,_bjeth_py,_bjeth_pz,_bjeth_e);

    float _bjetl_e = _recoPFJet_toptag_other_btag_e;
    float _bjetl_px = _recoPFJet_toptag_other_btag_px;
    float _bjetl_py = _recoPFJet_toptag_other_btag_py;
    float _bjetl_pz = _recoPFJet_toptag_other_btag_pz;
    
    TLorentzVector bjetl_tlv(_bjetl_px,_bjetl_py,_bjetl_pz,_bjetl_e);

    float _jet1_e = _recoPFJet_toptag_best_untag1_e;
    float _jet1_px = _recoPFJet_toptag_best_untag1_px;
    float _jet1_py = _recoPFJet_toptag_best_untag1_py;
    float _jet1_pz = _recoPFJet_toptag_best_untag1_pz;
    
    TLorentzVector jet1_tlv(_jet1_px,_jet1_py,_jet1_pz,_jet1_e);

    float _jet2_e = _recoPFJet_toptag_best_untag2_e;
    float _jet2_px = _recoPFJet_toptag_best_untag2_px;
    float _jet2_py = _recoPFJet_toptag_best_untag2_py;
    float _jet2_pz = _recoPFJet_toptag_best_untag2_pz;
    
    TLorentzVector jet2_tlv(_jet2_px,_jet2_py,_jet2_pz,_jet2_e); 
    
    float dR0 = genbh_tlv.DeltaR(bjeth_tlv) + genbl_tlv.DeltaR(bjetl_tlv) + genq1_tlv.DeltaR(jet1_tlv) + genq2_tlv.DeltaR(jet2_tlv);
    float dR1 = genbh_tlv.DeltaR(bjeth_tlv) + genbl_tlv.DeltaR(bjetl_tlv) + genq1_tlv.DeltaR(jet2_tlv) + genq2_tlv.DeltaR(jet1_tlv);

    _dR_sum_min = min(dR0,dR1);

    _n_matched_jet = 0;

    if(bjeth_tlv.DeltaR(genbh_tlv)<0.5 || bjeth_tlv.DeltaR(genbl_tlv)<0.5)
      _n_matched_jet++;
    
    if((bjetl_tlv.DeltaR(genbh_tlv)<0.5 && bjeth_tlv.DeltaR(genbh_tlv)>0.5) || (bjetl_tlv.DeltaR(genbl_tlv)<0.5 && bjeth_tlv.DeltaR(genbl_tlv)>0.5))
      _n_matched_jet++;
    
    if(jet1_tlv.DeltaR(genq1_tlv)<0.5 || jet1_tlv.DeltaR(genq2_tlv)<0.5)
      _n_matched_jet++;

    if((jet2_tlv.DeltaR(genq1_tlv)<0.5 && jet1_tlv.DeltaR(genq1_tlv)>0.5) || (jet2_tlv.DeltaR(genq2_tlv)<0.5 && jet1_tlv.DeltaR(genq2_tlv)>0.5))
      _n_matched_jet++;


    /*if(genbh_tlv.DeltaR(bjeth_tlv)<0.5 || genbh_tlv.DeltaR(bjetl_tlv)<0.5)
      _n_matched_jet++;
    if(genbl_tlv.DeltaR(bjetl_tlv)<0.5 || genbh_tlv.DeltaR(bjeth_tlv)<0.5)
      _n_matched_jet++;
    if(genq1_tlv.DeltaR(jet1_tlv)<0.5 || genq1_tlv.DeltaR(jet2_tlv)<0.5)
      _n_matched_jet++;
    if(genq2_tlv.DeltaR(jet1_tlv)<0.5 || genq2_tlv.DeltaR(jet2_tlv)<0.5)
    _n_matched_jet++;*/

    }
    
    tree_new->Fill();
    
  }
  
  f_new->cd();
  
  tree_new->Write();
  f_new->Close();
  
  
  return;
 
}

