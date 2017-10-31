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

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"



using namespace std;





void add_toptag(TString filename_in, TString filename_out, TString treename){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  //Old branches used

  int _n_recoPFJet_btag_loose;

  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_px;
  vector<float> *_recoPFJet_py;
  vector<float> *_recoPFJet_pz;
  vector<float> *_recoPFJet_CSVscore;

  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);


  //Top tag

  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _recoPFJet_best_deltaM_Top_W;
  
  float _recoPFJet_toptag_best_btag_e;
  float _recoPFJet_toptag_best_btag_px;
  float _recoPFJet_toptag_best_btag_py;
  float _recoPFJet_toptag_best_btag_pz;
  float _recoPFJet_toptag_best_btag_pt;
  float _recoPFJet_toptag_best_btag_eta;
  float _recoPFJet_toptag_best_btag_phi;
  float _recoPFJet_toptag_best_btag_CSVscore;

  float _recoPFJet_toptag_best_untag1_e;
  float _recoPFJet_toptag_best_untag1_px;
  float _recoPFJet_toptag_best_untag1_py;
  float _recoPFJet_toptag_best_untag1_pz;
  float _recoPFJet_toptag_best_untag1_pt;
  float _recoPFJet_toptag_best_untag1_eta;
  float _recoPFJet_toptag_best_untag1_phi;
  float _recoPFJet_toptag_best_untag1_CSVscore;

  float _recoPFJet_toptag_best_untag2_e;
  float _recoPFJet_toptag_best_untag2_px;
  float _recoPFJet_toptag_best_untag2_py;
  float _recoPFJet_toptag_best_untag2_pz;
  float _recoPFJet_toptag_best_untag2_pt;
  float _recoPFJet_toptag_best_untag2_eta;
  float _recoPFJet_toptag_best_untag2_phi;
  float _recoPFJet_toptag_best_untag2_CSVscore;

  float _recoPFJet_toptag_other_btag_e;
  float _recoPFJet_toptag_other_btag_px;
  float _recoPFJet_toptag_other_btag_py;
  float _recoPFJet_toptag_other_btag_pz;
  float _recoPFJet_toptag_other_btag_pt;
  float _recoPFJet_toptag_other_btag_eta;
  float _recoPFJet_toptag_other_btag_phi;
  float _recoPFJet_toptag_other_btag_CSVscore;


  tree_new->Branch("recoPFJet_best_deltaM_Top_W",&_recoPFJet_best_deltaM_Top_W,"recoPFJet_best_deltaM_Top_W/F");
  
  tree_new->Branch("recoPFJet_toptag_best_btag_e",&_recoPFJet_toptag_best_btag_e,"recoPFJet_toptag_best_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_px",&_recoPFJet_toptag_best_btag_px,"recoPFJet_toptag_best_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_py",&_recoPFJet_toptag_best_btag_py,"recoPFJet_toptag_best_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pz",&_recoPFJet_toptag_best_btag_pz,"recoPFJet_toptag_best_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pt",&_recoPFJet_toptag_best_btag_pt,"recoPFJet_toptag_best_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_eta",&_recoPFJet_toptag_best_btag_eta,"recoPFJet_toptag_best_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_phi",&_recoPFJet_toptag_best_btag_phi,"recoPFJet_toptag_best_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_CSVscore",&_recoPFJet_toptag_best_btag_CSVscore,"recoPFJet_toptag_best_btag_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag1_e",&_recoPFJet_toptag_best_untag1_e,"recoPFJet_toptag_best_untag1_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_px",&_recoPFJet_toptag_best_untag1_px,"recoPFJet_toptag_best_untag1_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_py",&_recoPFJet_toptag_best_untag1_py,"recoPFJet_toptag_best_untag1_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pz",&_recoPFJet_toptag_best_untag1_pz,"recoPFJet_toptag_best_untag1_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pt",&_recoPFJet_toptag_best_untag1_pt,"recoPFJet_toptag_best_untag1_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_eta",&_recoPFJet_toptag_best_untag1_eta,"recoPFJet_toptag_best_untag1_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_phi",&_recoPFJet_toptag_best_untag1_phi,"recoPFJet_toptag_best_untag1_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_CSVscore",&_recoPFJet_toptag_best_untag1_CSVscore,"recoPFJet_toptag_best_untag1_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag2_e",&_recoPFJet_toptag_best_untag2_e,"recoPFJet_toptag_best_untag2_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_px",&_recoPFJet_toptag_best_untag2_px,"recoPFJet_toptag_best_untag2_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_py",&_recoPFJet_toptag_best_untag2_py,"recoPFJet_toptag_best_untag2_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pz",&_recoPFJet_toptag_best_untag2_pz,"recoPFJet_toptag_best_untag2_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pt",&_recoPFJet_toptag_best_untag2_pt,"recoPFJet_toptag_best_untag2_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_eta",&_recoPFJet_toptag_best_untag2_eta,"recoPFJet_toptag_best_untag2_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_phi",&_recoPFJet_toptag_best_untag2_phi,"recoPFJet_toptag_best_untag2_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_CSVscore",&_recoPFJet_toptag_best_untag2_CSVscore,"recoPFJet_toptag_best_untag2_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_other_btag_e",&_recoPFJet_toptag_other_btag_e,"recoPFJet_toptag_other_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_px",&_recoPFJet_toptag_other_btag_px,"recoPFJet_toptag_other_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_py",&_recoPFJet_toptag_other_btag_py,"recoPFJet_toptag_other_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pz",&_recoPFJet_toptag_other_btag_pz,"recoPFJet_toptag_other_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pt",&_recoPFJet_toptag_other_btag_pt,"recoPFJet_toptag_other_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_eta",&_recoPFJet_toptag_other_btag_eta,"recoPFJet_toptag_other_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_phi",&_recoPFJet_toptag_other_btag_phi,"recoPFJet_toptag_other_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_CSVscore",&_recoPFJet_toptag_other_btag_CSVscore,"recoPFJet_toptag_other_btag_CSVscore/F");





  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _n_recoPFJet_btag_loose = 0;

    _recoPFJet_e = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;
    _recoPFJet_CSVscore = 0;


    _recoPFJet_best_deltaM_Top_W = 0;
   
    _recoPFJet_toptag_best_btag_e = 0;
    _recoPFJet_toptag_best_btag_px = 0;
    _recoPFJet_toptag_best_btag_py = 0;
    _recoPFJet_toptag_best_btag_pz = 0;
    _recoPFJet_toptag_best_btag_pt = 0;
    _recoPFJet_toptag_best_btag_eta = 0;
    _recoPFJet_toptag_best_btag_phi = 0;
    _recoPFJet_toptag_best_btag_CSVscore = 0;

    _recoPFJet_toptag_best_untag1_e = 0;
    _recoPFJet_toptag_best_untag1_px = 0;
    _recoPFJet_toptag_best_untag1_py = 0;
    _recoPFJet_toptag_best_untag1_pz = 0;
    _recoPFJet_toptag_best_untag1_pt = 0;
    _recoPFJet_toptag_best_untag1_eta = 0;
    _recoPFJet_toptag_best_untag1_phi = 0;
    _recoPFJet_toptag_best_untag1_CSVscore = 0;

    _recoPFJet_toptag_best_untag2_e = 0;
    _recoPFJet_toptag_best_untag2_px = 0;
    _recoPFJet_toptag_best_untag2_py = 0;
    _recoPFJet_toptag_best_untag2_pz = 0;
    _recoPFJet_toptag_best_untag2_pt = 0;
    _recoPFJet_toptag_best_untag2_eta = 0;
    _recoPFJet_toptag_best_untag2_phi = 0;
    _recoPFJet_toptag_best_untag2_CSVscore = 0;

    _recoPFJet_toptag_other_btag_e = 0;
    _recoPFJet_toptag_other_btag_px = 0;
    _recoPFJet_toptag_other_btag_py = 0;
    _recoPFJet_toptag_other_btag_pz = 0;
    _recoPFJet_toptag_other_btag_pt = 0;
    _recoPFJet_toptag_other_btag_eta = 0;
    _recoPFJet_toptag_other_btag_phi = 0;
    _recoPFJet_toptag_other_btag_CSVscore = 0;


    tree->GetEntry(i);

    double mW=80.4;
    double mTop=173.2;

    if((*_recoPFJet_e).size()>3 && _n_recoPFJet_btag_loose>0){	
	
      double deltaM_Top_W = -1;
      
      vector<unsigned int> index_TopTag;
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);


      for(unsigned int i_jet1=0; i_jet1<(*_recoPFJet_e).size(); i_jet1++){
	TLorentzVector jet1 ( (*_recoPFJet_px)[i_jet1], (*_recoPFJet_py)[i_jet1], (*_recoPFJet_pz)[i_jet1], (*_recoPFJet_e)[i_jet1] );
	  
	if( (*_recoPFJet_CSVscore)[i_jet1]<0.46 ) continue;
	  
	for(unsigned int i_jet2=0; i_jet2<(*_recoPFJet_e).size()-1; i_jet2++){
	    
	  if(i_jet2==i_jet1) continue;
	    
	  TLorentzVector jet2 ( (*_recoPFJet_px)[i_jet2], (*_recoPFJet_py)[i_jet2], (*_recoPFJet_pz)[i_jet2], (*_recoPFJet_e)[i_jet2] );
	    
	  for(unsigned int i_jet3=i_jet2+1; i_jet3<(*_recoPFJet_e).size(); i_jet3++){
	      
	    if(i_jet3==i_jet1) continue;

	    TLorentzVector jet3 ( (*_recoPFJet_px)[i_jet3], (*_recoPFJet_py)[i_jet3], (*_recoPFJet_pz)[i_jet3], (*_recoPFJet_e)[i_jet3] );

	      
	    float mjj=(jet2+jet3).M();
	    float mjjj=(jet1+jet2+jet3).M();
	    float deltaM = fabs(mjjj-mTop)/mTop + fabs(mjj-mW)/mW;
	    
	    if( deltaM_Top_W<0 || deltaM<deltaM_Top_W){
	      
	      deltaM_Top_W = deltaM;
	      
	      index_TopTag[0] = i_jet1;
	      index_TopTag[1] = i_jet2;
	      index_TopTag[2] = i_jet3;
	      
	    }
	    
	  }
	  
	}
	
      }
      
      
      float max_CSV = -1;
      
      for(unsigned int i_jet4=0; i_jet4<(*_recoPFJet_e).size(); i_jet4++){

	if(i_jet4==index_TopTag[0] || i_jet4==index_TopTag[1] || i_jet4==index_TopTag[2]) continue;
	
	if((*_recoPFJet_CSVscore)[i_jet4]>max_CSV){
 
	  max_CSV = (*_recoPFJet_CSVscore)[i_jet4];
	  index_TopTag[3] = i_jet4;
	  
	}
	
      }
      
      
      _recoPFJet_best_deltaM_Top_W = deltaM_Top_W;
      
      int i_jet1=index_TopTag[0];
      int i_jet2=index_TopTag[1];
      int i_jet3=index_TopTag[2];
      int i_jet4=index_TopTag[3];   

      TLorentzVector jet1((*_recoPFJet_px)[i_jet1],(*_recoPFJet_py)[i_jet1],(*_recoPFJet_pz)[i_jet1],(*_recoPFJet_e)[i_jet1]);
      TLorentzVector jet2((*_recoPFJet_px)[i_jet2],(*_recoPFJet_py)[i_jet2],(*_recoPFJet_pz)[i_jet2],(*_recoPFJet_e)[i_jet2]);
      TLorentzVector jet3((*_recoPFJet_px)[i_jet3],(*_recoPFJet_py)[i_jet3],(*_recoPFJet_pz)[i_jet3],(*_recoPFJet_e)[i_jet3]);
      TLorentzVector jet4((*_recoPFJet_px)[i_jet4],(*_recoPFJet_py)[i_jet4],(*_recoPFJet_pz)[i_jet4],(*_recoPFJet_e)[i_jet4]);
	
      _recoPFJet_toptag_best_btag_e = jet1.E();;
      _recoPFJet_toptag_best_btag_px = jet1.Px();
      _recoPFJet_toptag_best_btag_py = jet1.Py();
      _recoPFJet_toptag_best_btag_pz = jet1.Pz();
      _recoPFJet_toptag_best_btag_pt = jet1.Pt();
      _recoPFJet_toptag_best_btag_eta = jet1.Eta();
      _recoPFJet_toptag_best_btag_phi = jet1.Phi();
      _recoPFJet_toptag_best_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet1];
      
      _recoPFJet_toptag_best_untag1_e = jet2.E();;
      _recoPFJet_toptag_best_untag1_px = jet2.Px();
      _recoPFJet_toptag_best_untag1_py = jet2.Py();
      _recoPFJet_toptag_best_untag1_pz = jet2.Pz();
      _recoPFJet_toptag_best_untag1_pt = jet2.Pt();
      _recoPFJet_toptag_best_untag1_eta = jet2.Eta();
      _recoPFJet_toptag_best_untag1_phi = jet2.Phi();
      _recoPFJet_toptag_best_untag1_CSVscore = (*_recoPFJet_CSVscore)[i_jet2];
      
      _recoPFJet_toptag_best_untag2_e = jet3.E();;
      _recoPFJet_toptag_best_untag2_px = jet3.Px();
      _recoPFJet_toptag_best_untag2_py = jet3.Py();
      _recoPFJet_toptag_best_untag2_pz = jet3.Pz();
      _recoPFJet_toptag_best_untag2_pt = jet3.Pt();
      _recoPFJet_toptag_best_untag2_eta = jet3.Eta();
      _recoPFJet_toptag_best_untag2_phi = jet3.Phi();
      _recoPFJet_toptag_best_untag2_CSVscore = (*_recoPFJet_CSVscore)[i_jet3];
      
      _recoPFJet_toptag_other_btag_e = jet4.E();;
      _recoPFJet_toptag_other_btag_px = jet4.Px();
      _recoPFJet_toptag_other_btag_py = jet4.Py();
      _recoPFJet_toptag_other_btag_pz = jet4.Pz();
      _recoPFJet_toptag_other_btag_pt = jet4.Pt();
      _recoPFJet_toptag_other_btag_eta = jet4.Eta();
      _recoPFJet_toptag_other_btag_phi = jet4.Phi();
      _recoPFJet_toptag_other_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet4];
	
    }

    tree_new->Fill();

  }

  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}





void add_toptag1p5(TString filename_in, TString filename_out, TString treename){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  //Old branches used

  int _n_recoPFJet_btag_loose;

  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_px;
  vector<float> *_recoPFJet_py;
  vector<float> *_recoPFJet_pz;
  vector<float> *_recoPFJet_CSVscore;

  vector<float> *_recoPFJet_btag_e;
  vector<float> *_recoPFJet_btag_px;
  vector<float> *_recoPFJet_btag_py;
  vector<float> *_recoPFJet_btag_pz;
  vector<float> *_recoPFJet_btag_CSVscore;

  vector<float> *_recoPFJet_untag_Wtag_e;
  vector<float> *_recoPFJet_untag_Wtag_px;
  vector<float> *_recoPFJet_untag_Wtag_py;
  vector<float> *_recoPFJet_untag_Wtag_pz;
  vector<float> *_recoPFJet_untag_Wtag_CSVscore;

  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);

  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);
  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree->SetBranchAddress("recoPFJet_btag_CSVscore",&_recoPFJet_btag_CSVscore);

  tree->SetBranchAddress("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_CSVscore",&_recoPFJet_untag_Wtag_CSVscore);


  //Top tag

  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _recoPFJet_best_deltaM_Top_W;
  
  float _recoPFJet_toptag_best_btag_e;
  float _recoPFJet_toptag_best_btag_px;
  float _recoPFJet_toptag_best_btag_py;
  float _recoPFJet_toptag_best_btag_pz;
  float _recoPFJet_toptag_best_btag_pt;
  float _recoPFJet_toptag_best_btag_eta;
  float _recoPFJet_toptag_best_btag_phi;
  float _recoPFJet_toptag_best_btag_CSVscore;

  float _recoPFJet_toptag_best_untag1_e;
  float _recoPFJet_toptag_best_untag1_px;
  float _recoPFJet_toptag_best_untag1_py;
  float _recoPFJet_toptag_best_untag1_pz;
  float _recoPFJet_toptag_best_untag1_pt;
  float _recoPFJet_toptag_best_untag1_eta;
  float _recoPFJet_toptag_best_untag1_phi;
  float _recoPFJet_toptag_best_untag1_CSVscore;

  float _recoPFJet_toptag_best_untag2_e;
  float _recoPFJet_toptag_best_untag2_px;
  float _recoPFJet_toptag_best_untag2_py;
  float _recoPFJet_toptag_best_untag2_pz;
  float _recoPFJet_toptag_best_untag2_pt;
  float _recoPFJet_toptag_best_untag2_eta;
  float _recoPFJet_toptag_best_untag2_phi;
  float _recoPFJet_toptag_best_untag2_CSVscore;

  float _recoPFJet_toptag_other_btag_e;
  float _recoPFJet_toptag_other_btag_px;
  float _recoPFJet_toptag_other_btag_py;
  float _recoPFJet_toptag_other_btag_pz;
  float _recoPFJet_toptag_other_btag_pt;
  float _recoPFJet_toptag_other_btag_eta;
  float _recoPFJet_toptag_other_btag_phi;
  float _recoPFJet_toptag_other_btag_CSVscore;


  tree_new->Branch("recoPFJet_best_deltaM_Top_W",&_recoPFJet_best_deltaM_Top_W,"recoPFJet_best_deltaM_Top_W/F");
  
  tree_new->Branch("recoPFJet_toptag_best_btag_e",&_recoPFJet_toptag_best_btag_e,"recoPFJet_toptag_best_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_px",&_recoPFJet_toptag_best_btag_px,"recoPFJet_toptag_best_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_py",&_recoPFJet_toptag_best_btag_py,"recoPFJet_toptag_best_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pz",&_recoPFJet_toptag_best_btag_pz,"recoPFJet_toptag_best_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pt",&_recoPFJet_toptag_best_btag_pt,"recoPFJet_toptag_best_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_eta",&_recoPFJet_toptag_best_btag_eta,"recoPFJet_toptag_best_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_phi",&_recoPFJet_toptag_best_btag_phi,"recoPFJet_toptag_best_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_CSVscore",&_recoPFJet_toptag_best_btag_CSVscore,"recoPFJet_toptag_best_btag_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag1_e",&_recoPFJet_toptag_best_untag1_e,"recoPFJet_toptag_best_untag1_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_px",&_recoPFJet_toptag_best_untag1_px,"recoPFJet_toptag_best_untag1_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_py",&_recoPFJet_toptag_best_untag1_py,"recoPFJet_toptag_best_untag1_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pz",&_recoPFJet_toptag_best_untag1_pz,"recoPFJet_toptag_best_untag1_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pt",&_recoPFJet_toptag_best_untag1_pt,"recoPFJet_toptag_best_untag1_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_eta",&_recoPFJet_toptag_best_untag1_eta,"recoPFJet_toptag_best_untag1_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_phi",&_recoPFJet_toptag_best_untag1_phi,"recoPFJet_toptag_best_untag1_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_CSVscore",&_recoPFJet_toptag_best_untag1_CSVscore,"recoPFJet_toptag_best_untag1_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag2_e",&_recoPFJet_toptag_best_untag2_e,"recoPFJet_toptag_best_untag2_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_px",&_recoPFJet_toptag_best_untag2_px,"recoPFJet_toptag_best_untag2_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_py",&_recoPFJet_toptag_best_untag2_py,"recoPFJet_toptag_best_untag2_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pz",&_recoPFJet_toptag_best_untag2_pz,"recoPFJet_toptag_best_untag2_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pt",&_recoPFJet_toptag_best_untag2_pt,"recoPFJet_toptag_best_untag2_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_eta",&_recoPFJet_toptag_best_untag2_eta,"recoPFJet_toptag_best_untag2_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_phi",&_recoPFJet_toptag_best_untag2_phi,"recoPFJet_toptag_best_untag2_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_CSVscore",&_recoPFJet_toptag_best_untag2_CSVscore,"recoPFJet_toptag_best_untag2_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_other_btag_e",&_recoPFJet_toptag_other_btag_e,"recoPFJet_toptag_other_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_px",&_recoPFJet_toptag_other_btag_px,"recoPFJet_toptag_other_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_py",&_recoPFJet_toptag_other_btag_py,"recoPFJet_toptag_other_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pz",&_recoPFJet_toptag_other_btag_pz,"recoPFJet_toptag_other_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pt",&_recoPFJet_toptag_other_btag_pt,"recoPFJet_toptag_other_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_eta",&_recoPFJet_toptag_other_btag_eta,"recoPFJet_toptag_other_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_phi",&_recoPFJet_toptag_other_btag_phi,"recoPFJet_toptag_other_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_CSVscore",&_recoPFJet_toptag_other_btag_CSVscore,"recoPFJet_toptag_other_btag_CSVscore/F");





  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _n_recoPFJet_btag_loose = 0;

    _recoPFJet_e = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;
    _recoPFJet_CSVscore = 0;

    _recoPFJet_btag_e = 0;
    _recoPFJet_btag_px = 0;
    _recoPFJet_btag_py = 0;
    _recoPFJet_btag_pz = 0;
    _recoPFJet_btag_CSVscore = 0;

    _recoPFJet_untag_Wtag_e = 0;
    _recoPFJet_untag_Wtag_px = 0;
    _recoPFJet_untag_Wtag_py = 0;
    _recoPFJet_untag_Wtag_pz = 0;
    _recoPFJet_untag_Wtag_CSVscore = 0;


    _recoPFJet_best_deltaM_Top_W = 0;
   
    _recoPFJet_toptag_best_btag_e = 0;
    _recoPFJet_toptag_best_btag_px = 0;
    _recoPFJet_toptag_best_btag_py = 0;
    _recoPFJet_toptag_best_btag_pz = 0;
    _recoPFJet_toptag_best_btag_pt = 0;
    _recoPFJet_toptag_best_btag_eta = 0;
    _recoPFJet_toptag_best_btag_phi = 0;
    _recoPFJet_toptag_best_btag_CSVscore = 0;

    _recoPFJet_toptag_best_untag1_e = 0;
    _recoPFJet_toptag_best_untag1_px = 0;
    _recoPFJet_toptag_best_untag1_py = 0;
    _recoPFJet_toptag_best_untag1_pz = 0;
    _recoPFJet_toptag_best_untag1_pt = 0;
    _recoPFJet_toptag_best_untag1_eta = 0;
    _recoPFJet_toptag_best_untag1_phi = 0;
    _recoPFJet_toptag_best_untag1_CSVscore = 0;

    _recoPFJet_toptag_best_untag2_e = 0;
    _recoPFJet_toptag_best_untag2_px = 0;
    _recoPFJet_toptag_best_untag2_py = 0;
    _recoPFJet_toptag_best_untag2_pz = 0;
    _recoPFJet_toptag_best_untag2_pt = 0;
    _recoPFJet_toptag_best_untag2_eta = 0;
    _recoPFJet_toptag_best_untag2_phi = 0;
    _recoPFJet_toptag_best_untag2_CSVscore = 0;

    _recoPFJet_toptag_other_btag_e = 0;
    _recoPFJet_toptag_other_btag_px = 0;
    _recoPFJet_toptag_other_btag_py = 0;
    _recoPFJet_toptag_other_btag_pz = 0;
    _recoPFJet_toptag_other_btag_pt = 0;
    _recoPFJet_toptag_other_btag_eta = 0;
    _recoPFJet_toptag_other_btag_phi = 0;
    _recoPFJet_toptag_other_btag_CSVscore = 0;


    tree->GetEntry(i);

    double mW=80.4;
    double mTop=173.2;

    if((*_recoPFJet_e).size()>3 && _n_recoPFJet_btag_loose<=2){	

      TLorentzVector jet1((*_recoPFJet_btag_px)[0],(*_recoPFJet_btag_py)[0],(*_recoPFJet_btag_pz)[0],(*_recoPFJet_btag_e)[0]);
      TLorentzVector jet2((*_recoPFJet_untag_Wtag_px)[0],(*_recoPFJet_untag_Wtag_py)[0],(*_recoPFJet_untag_Wtag_pz)[0],(*_recoPFJet_untag_Wtag_e)[0]);
      TLorentzVector jet3((*_recoPFJet_untag_Wtag_px)[1],(*_recoPFJet_untag_Wtag_py)[1],(*_recoPFJet_untag_Wtag_pz)[1],(*_recoPFJet_untag_Wtag_e)[1]);
      TLorentzVector jet4((*_recoPFJet_btag_px)[1],(*_recoPFJet_btag_py)[1],(*_recoPFJet_btag_pz)[1],(*_recoPFJet_btag_e)[1]);

      /*jet1.Print();
      jet2.Print();
      jet3.Print();
      jet4.Print();*/
      
	
      _recoPFJet_toptag_best_btag_e = jet1.E();;
      _recoPFJet_toptag_best_btag_px = jet1.Px();
      _recoPFJet_toptag_best_btag_py = jet1.Py();
      _recoPFJet_toptag_best_btag_pz = jet1.Pz();
      _recoPFJet_toptag_best_btag_pt = jet1.Pt();
      _recoPFJet_toptag_best_btag_eta = jet1.Eta();
      _recoPFJet_toptag_best_btag_phi = jet1.Phi();
      _recoPFJet_toptag_best_btag_CSVscore = (*_recoPFJet_btag_CSVscore)[0];
      
      _recoPFJet_toptag_best_untag1_e = jet2.E();;
      _recoPFJet_toptag_best_untag1_px = jet2.Px();
      _recoPFJet_toptag_best_untag1_py = jet2.Py();
      _recoPFJet_toptag_best_untag1_pz = jet2.Pz();
      _recoPFJet_toptag_best_untag1_pt = jet2.Pt();
      _recoPFJet_toptag_best_untag1_eta = jet2.Eta();
      _recoPFJet_toptag_best_untag1_phi = jet2.Phi();
      _recoPFJet_toptag_best_untag1_CSVscore = (*_recoPFJet_untag_Wtag_CSVscore)[0];
      
      _recoPFJet_toptag_best_untag2_e = jet3.E();;
      _recoPFJet_toptag_best_untag2_px = jet3.Px();
      _recoPFJet_toptag_best_untag2_py = jet3.Py();
      _recoPFJet_toptag_best_untag2_pz = jet3.Pz();
      _recoPFJet_toptag_best_untag2_pt = jet3.Pt();
      _recoPFJet_toptag_best_untag2_eta = jet3.Eta();
      _recoPFJet_toptag_best_untag2_phi = jet3.Phi();
      _recoPFJet_toptag_best_untag2_CSVscore = (*_recoPFJet_untag_Wtag_CSVscore)[1];
      
      _recoPFJet_toptag_other_btag_e = jet4.E();;
      _recoPFJet_toptag_other_btag_px = jet4.Px();
      _recoPFJet_toptag_other_btag_py = jet4.Py();
      _recoPFJet_toptag_other_btag_pz = jet4.Pz();
      _recoPFJet_toptag_other_btag_pt = jet4.Pt();
      _recoPFJet_toptag_other_btag_eta = jet4.Eta();
      _recoPFJet_toptag_other_btag_phi = jet4.Phi();
      _recoPFJet_toptag_other_btag_CSVscore = (*_recoPFJet_btag_CSVscore)[1];




    }


    else if((*_recoPFJet_e).size()>3 && _n_recoPFJet_btag_loose>2){	
	
      double deltaM_Top_W = -1;
      
      vector<unsigned int> index_TopTag;
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);


      for(unsigned int i_jet1=0; i_jet1<(*_recoPFJet_e).size(); i_jet1++){
	TLorentzVector jet1 ( (*_recoPFJet_px)[i_jet1], (*_recoPFJet_py)[i_jet1], (*_recoPFJet_pz)[i_jet1], (*_recoPFJet_e)[i_jet1] );
	  
	if( (*_recoPFJet_CSVscore)[i_jet1]<0.46 ) continue;
	  
	for(unsigned int i_jet2=0; i_jet2<(*_recoPFJet_e).size()-1; i_jet2++){
	    
	  if(i_jet2==i_jet1) continue;
	    
	  TLorentzVector jet2 ( (*_recoPFJet_px)[i_jet2], (*_recoPFJet_py)[i_jet2], (*_recoPFJet_pz)[i_jet2], (*_recoPFJet_e)[i_jet2] );
	    
	  for(unsigned int i_jet3=i_jet2+1; i_jet3<(*_recoPFJet_e).size(); i_jet3++){
	      
	    if(i_jet3==i_jet1) continue;

	    TLorentzVector jet3 ( (*_recoPFJet_px)[i_jet3], (*_recoPFJet_py)[i_jet3], (*_recoPFJet_pz)[i_jet3], (*_recoPFJet_e)[i_jet3] );

	      
	    float mjj=(jet2+jet3).M();
	    float mjjj=(jet1+jet2+jet3).M();
	    float deltaM = fabs(mjjj-mTop)/mTop + fabs(mjj-mW)/mW;
	    
	    if( deltaM_Top_W<0 || deltaM<deltaM_Top_W){
	      
	      deltaM_Top_W = deltaM;
	      
	      index_TopTag[0] = i_jet1;
	      index_TopTag[1] = i_jet2;
	      index_TopTag[2] = i_jet3;
	      
	    }
	    
	  }
	  
	}
	
      }
      
      
      float max_CSV = -1;
      
      for(unsigned int i_jet4=0; i_jet4<(*_recoPFJet_e).size(); i_jet4++){

	if(i_jet4==index_TopTag[0] || i_jet4==index_TopTag[1] || i_jet4==index_TopTag[2]) continue;
	
	if((*_recoPFJet_CSVscore)[i_jet4]>max_CSV){
 
	  max_CSV = (*_recoPFJet_CSVscore)[i_jet4];
	  index_TopTag[3] = i_jet4;
	  
	}
	
      }
      
      
      _recoPFJet_best_deltaM_Top_W = deltaM_Top_W;
      
      int i_jet1=index_TopTag[0];
      int i_jet2=index_TopTag[1];
      int i_jet3=index_TopTag[2];
      int i_jet4=index_TopTag[3];   

      TLorentzVector jet1((*_recoPFJet_px)[i_jet1],(*_recoPFJet_py)[i_jet1],(*_recoPFJet_pz)[i_jet1],(*_recoPFJet_e)[i_jet1]);
      TLorentzVector jet2((*_recoPFJet_px)[i_jet2],(*_recoPFJet_py)[i_jet2],(*_recoPFJet_pz)[i_jet2],(*_recoPFJet_e)[i_jet2]);
      TLorentzVector jet3((*_recoPFJet_px)[i_jet3],(*_recoPFJet_py)[i_jet3],(*_recoPFJet_pz)[i_jet3],(*_recoPFJet_e)[i_jet3]);
      TLorentzVector jet4((*_recoPFJet_px)[i_jet4],(*_recoPFJet_py)[i_jet4],(*_recoPFJet_pz)[i_jet4],(*_recoPFJet_e)[i_jet4]);
	
      _recoPFJet_toptag_best_btag_e = jet1.E();;
      _recoPFJet_toptag_best_btag_px = jet1.Px();
      _recoPFJet_toptag_best_btag_py = jet1.Py();
      _recoPFJet_toptag_best_btag_pz = jet1.Pz();
      _recoPFJet_toptag_best_btag_pt = jet1.Pt();
      _recoPFJet_toptag_best_btag_eta = jet1.Eta();
      _recoPFJet_toptag_best_btag_phi = jet1.Phi();
      _recoPFJet_toptag_best_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet1];
      
      _recoPFJet_toptag_best_untag1_e = jet2.E();;
      _recoPFJet_toptag_best_untag1_px = jet2.Px();
      _recoPFJet_toptag_best_untag1_py = jet2.Py();
      _recoPFJet_toptag_best_untag1_pz = jet2.Pz();
      _recoPFJet_toptag_best_untag1_pt = jet2.Pt();
      _recoPFJet_toptag_best_untag1_eta = jet2.Eta();
      _recoPFJet_toptag_best_untag1_phi = jet2.Phi();
      _recoPFJet_toptag_best_untag1_CSVscore = (*_recoPFJet_CSVscore)[i_jet2];
      
      _recoPFJet_toptag_best_untag2_e = jet3.E();;
      _recoPFJet_toptag_best_untag2_px = jet3.Px();
      _recoPFJet_toptag_best_untag2_py = jet3.Py();
      _recoPFJet_toptag_best_untag2_pz = jet3.Pz();
      _recoPFJet_toptag_best_untag2_pt = jet3.Pt();
      _recoPFJet_toptag_best_untag2_eta = jet3.Eta();
      _recoPFJet_toptag_best_untag2_phi = jet3.Phi();
      _recoPFJet_toptag_best_untag2_CSVscore = (*_recoPFJet_CSVscore)[i_jet3];
      
      _recoPFJet_toptag_other_btag_e = jet4.E();;
      _recoPFJet_toptag_other_btag_px = jet4.Px();
      _recoPFJet_toptag_other_btag_py = jet4.Py();
      _recoPFJet_toptag_other_btag_pz = jet4.Pz();
      _recoPFJet_toptag_other_btag_pt = jet4.Pt();
      _recoPFJet_toptag_other_btag_eta = jet4.Eta();
      _recoPFJet_toptag_other_btag_phi = jet4.Phi();
      _recoPFJet_toptag_other_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet4];
	
    }

    tree_new->Fill();

  }

  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}










void add_toptag2(TString filename_in, TString filename_out, TString treename){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  //Old branches used

  /*int _n_recoPFJet_btag_loose;

  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_px;
  vector<float> *_recoPFJet_py;
  vector<float> *_recoPFJet_pz;
  vector<float> *_recoPFJet_CSVscore;

  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);*/

  vector<float> *_recoPFJet_btag_e;
  vector<float> *_recoPFJet_btag_px;
  vector<float> *_recoPFJet_btag_py;
  vector<float> *_recoPFJet_btag_pz;
  vector<float> *_recoPFJet_btag_CSVscore;

  vector<float> *_recoPFJet_untag_e;
  vector<float> *_recoPFJet_untag_px;
  vector<float> *_recoPFJet_untag_py;
  vector<float> *_recoPFJet_untag_pz;
  vector<float> *_recoPFJet_untag_CSVscore;


  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);
  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree->SetBranchAddress("recoPFJet_btag_CSVscore",&_recoPFJet_btag_CSVscore);

  tree->SetBranchAddress("recoPFJet_untag_e",&_recoPFJet_untag_e);
  tree->SetBranchAddress("recoPFJet_untag_px",&_recoPFJet_untag_px);
  tree->SetBranchAddress("recoPFJet_untag_py",&_recoPFJet_untag_py);
  tree->SetBranchAddress("recoPFJet_untag_pz",&_recoPFJet_untag_pz);
  tree->SetBranchAddress("recoPFJet_untag_CSVscore",&_recoPFJet_untag_CSVscore);


  //Top tag

  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _recoPFJet_best_deltaM_Top_W;
  
  float _recoPFJet_toptag_best_btag_e;
  float _recoPFJet_toptag_best_btag_px;
  float _recoPFJet_toptag_best_btag_py;
  float _recoPFJet_toptag_best_btag_pz;
  float _recoPFJet_toptag_best_btag_pt;
  float _recoPFJet_toptag_best_btag_eta;
  float _recoPFJet_toptag_best_btag_phi;
  float _recoPFJet_toptag_best_btag_CSVscore;

  float _recoPFJet_toptag_best_untag1_e;
  float _recoPFJet_toptag_best_untag1_px;
  float _recoPFJet_toptag_best_untag1_py;
  float _recoPFJet_toptag_best_untag1_pz;
  float _recoPFJet_toptag_best_untag1_pt;
  float _recoPFJet_toptag_best_untag1_eta;
  float _recoPFJet_toptag_best_untag1_phi;
  float _recoPFJet_toptag_best_untag1_CSVscore;

  float _recoPFJet_toptag_best_untag2_e;
  float _recoPFJet_toptag_best_untag2_px;
  float _recoPFJet_toptag_best_untag2_py;
  float _recoPFJet_toptag_best_untag2_pz;
  float _recoPFJet_toptag_best_untag2_pt;
  float _recoPFJet_toptag_best_untag2_eta;
  float _recoPFJet_toptag_best_untag2_phi;
  float _recoPFJet_toptag_best_untag2_CSVscore;

  float _recoPFJet_toptag_other_btag_e;
  float _recoPFJet_toptag_other_btag_px;
  float _recoPFJet_toptag_other_btag_py;
  float _recoPFJet_toptag_other_btag_pz;
  float _recoPFJet_toptag_other_btag_pt;
  float _recoPFJet_toptag_other_btag_eta;
  float _recoPFJet_toptag_other_btag_phi;
  float _recoPFJet_toptag_other_btag_CSVscore;


  tree_new->Branch("recoPFJet_best_deltaM_Top_W",&_recoPFJet_best_deltaM_Top_W,"recoPFJet_best_deltaM_Top_W/F");
  
  tree_new->Branch("recoPFJet_toptag_best_btag_e",&_recoPFJet_toptag_best_btag_e,"recoPFJet_toptag_best_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_px",&_recoPFJet_toptag_best_btag_px,"recoPFJet_toptag_best_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_py",&_recoPFJet_toptag_best_btag_py,"recoPFJet_toptag_best_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pz",&_recoPFJet_toptag_best_btag_pz,"recoPFJet_toptag_best_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pt",&_recoPFJet_toptag_best_btag_pt,"recoPFJet_toptag_best_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_eta",&_recoPFJet_toptag_best_btag_eta,"recoPFJet_toptag_best_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_phi",&_recoPFJet_toptag_best_btag_phi,"recoPFJet_toptag_best_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_CSVscore",&_recoPFJet_toptag_best_btag_CSVscore,"recoPFJet_toptag_best_btag_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag1_e",&_recoPFJet_toptag_best_untag1_e,"recoPFJet_toptag_best_untag1_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_px",&_recoPFJet_toptag_best_untag1_px,"recoPFJet_toptag_best_untag1_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_py",&_recoPFJet_toptag_best_untag1_py,"recoPFJet_toptag_best_untag1_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pz",&_recoPFJet_toptag_best_untag1_pz,"recoPFJet_toptag_best_untag1_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pt",&_recoPFJet_toptag_best_untag1_pt,"recoPFJet_toptag_best_untag1_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_eta",&_recoPFJet_toptag_best_untag1_eta,"recoPFJet_toptag_best_untag1_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_phi",&_recoPFJet_toptag_best_untag1_phi,"recoPFJet_toptag_best_untag1_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_CSVscore",&_recoPFJet_toptag_best_untag1_CSVscore,"recoPFJet_toptag_best_untag1_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag2_e",&_recoPFJet_toptag_best_untag2_e,"recoPFJet_toptag_best_untag2_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_px",&_recoPFJet_toptag_best_untag2_px,"recoPFJet_toptag_best_untag2_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_py",&_recoPFJet_toptag_best_untag2_py,"recoPFJet_toptag_best_untag2_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pz",&_recoPFJet_toptag_best_untag2_pz,"recoPFJet_toptag_best_untag2_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pt",&_recoPFJet_toptag_best_untag2_pt,"recoPFJet_toptag_best_untag2_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_eta",&_recoPFJet_toptag_best_untag2_eta,"recoPFJet_toptag_best_untag2_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_phi",&_recoPFJet_toptag_best_untag2_phi,"recoPFJet_toptag_best_untag2_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_CSVscore",&_recoPFJet_toptag_best_untag2_CSVscore,"recoPFJet_toptag_best_untag2_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_other_btag_e",&_recoPFJet_toptag_other_btag_e,"recoPFJet_toptag_other_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_px",&_recoPFJet_toptag_other_btag_px,"recoPFJet_toptag_other_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_py",&_recoPFJet_toptag_other_btag_py,"recoPFJet_toptag_other_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pz",&_recoPFJet_toptag_other_btag_pz,"recoPFJet_toptag_other_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pt",&_recoPFJet_toptag_other_btag_pt,"recoPFJet_toptag_other_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_eta",&_recoPFJet_toptag_other_btag_eta,"recoPFJet_toptag_other_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_phi",&_recoPFJet_toptag_other_btag_phi,"recoPFJet_toptag_other_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_CSVscore",&_recoPFJet_toptag_other_btag_CSVscore,"recoPFJet_toptag_other_btag_CSVscore/F");





  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _recoPFJet_btag_e = 0;
    _recoPFJet_btag_px = 0;
    _recoPFJet_btag_py = 0;
    _recoPFJet_btag_pz = 0;
    _recoPFJet_btag_CSVscore = 0;

    _recoPFJet_untag_e = 0;
    _recoPFJet_untag_px = 0;
    _recoPFJet_untag_py = 0;
    _recoPFJet_untag_pz = 0;
    _recoPFJet_untag_CSVscore = 0;


    _recoPFJet_best_deltaM_Top_W = 0;
   
    _recoPFJet_toptag_best_btag_e = 0;
    _recoPFJet_toptag_best_btag_px = 0;
    _recoPFJet_toptag_best_btag_py = 0;
    _recoPFJet_toptag_best_btag_pz = 0;
    _recoPFJet_toptag_best_btag_pt = 0;
    _recoPFJet_toptag_best_btag_eta = 0;
    _recoPFJet_toptag_best_btag_phi = 0;
    _recoPFJet_toptag_best_btag_CSVscore = 0;

    _recoPFJet_toptag_best_untag1_e = 0;
    _recoPFJet_toptag_best_untag1_px = 0;
    _recoPFJet_toptag_best_untag1_py = 0;
    _recoPFJet_toptag_best_untag1_pz = 0;
    _recoPFJet_toptag_best_untag1_pt = 0;
    _recoPFJet_toptag_best_untag1_eta = 0;
    _recoPFJet_toptag_best_untag1_phi = 0;
    _recoPFJet_toptag_best_untag1_CSVscore = 0;

    _recoPFJet_toptag_best_untag2_e = 0;
    _recoPFJet_toptag_best_untag2_px = 0;
    _recoPFJet_toptag_best_untag2_py = 0;
    _recoPFJet_toptag_best_untag2_pz = 0;
    _recoPFJet_toptag_best_untag2_pt = 0;
    _recoPFJet_toptag_best_untag2_eta = 0;
    _recoPFJet_toptag_best_untag2_phi = 0;
    _recoPFJet_toptag_best_untag2_CSVscore = 0;

    _recoPFJet_toptag_other_btag_e = 0;
    _recoPFJet_toptag_other_btag_px = 0;
    _recoPFJet_toptag_other_btag_py = 0;
    _recoPFJet_toptag_other_btag_pz = 0;
    _recoPFJet_toptag_other_btag_pt = 0;
    _recoPFJet_toptag_other_btag_eta = 0;
    _recoPFJet_toptag_other_btag_phi = 0;
    _recoPFJet_toptag_other_btag_CSVscore = 0;


    tree->GetEntry(i);

    double mW=80.4;
    double mTop=173.2;

    if((*_recoPFJet_untag_e).size()>1){	
	
      double deltaM_Top_W = -1;

      int index_btag_tophad = -1;
      int index_btag_toplep = -1;
      int index_untag1_tophad = -1;
      int index_untag2_tophad = -1;

      for(unsigned int i_bjet=0; i_bjet<(*_recoPFJet_btag_e).size(); i_bjet++){

	TLorentzVector bjet ( (*_recoPFJet_btag_px)[i_bjet], (*_recoPFJet_btag_py)[i_bjet], (*_recoPFJet_btag_pz)[i_bjet], (*_recoPFJet_btag_e)[i_bjet] );


	for(unsigned int i_jet1=0; i_jet1<(*_recoPFJet_untag_e).size()-1; i_jet1++){
	    	    
	  TLorentzVector jet1 ( (*_recoPFJet_untag_px)[i_jet1], (*_recoPFJet_untag_py)[i_jet1], (*_recoPFJet_untag_pz)[i_jet1], (*_recoPFJet_untag_e)[i_jet1] );
	    
	  for(unsigned int i_jet2=i_jet1+1; i_jet2<(*_recoPFJet_untag_e).size(); i_jet2++){
	      
	    TLorentzVector jet2 ( (*_recoPFJet_untag_px)[i_jet2], (*_recoPFJet_untag_py)[i_jet2], (*_recoPFJet_untag_pz)[i_jet2], (*_recoPFJet_untag_e)[i_jet2] );

	    float mjj=(jet1+jet2).M();
	    float mjjj=(bjet+jet1+jet2).M();
	    float deltaM = fabs(mjjj-mTop) + fabs(mjj-mW);

	    if( deltaM_Top_W<0 || deltaM<deltaM_Top_W){
	      
	      deltaM_Top_W = deltaM;

	      index_btag_tophad = i_bjet;	      
	      index_btag_toplep = (1+i_bjet)%2;
	      index_untag1_tophad = i_jet1;
	      index_untag2_tophad = i_jet2;
	      
	    }

	  }

	}

      }

      
      int i_jet1=index_btag_tophad;
      int i_jet2=index_btag_toplep;
      int i_jet3=index_untag1_tophad;
      int i_jet4=index_untag2_tophad;
      

      TLorentzVector jet1((*_recoPFJet_btag_px)[i_jet1],(*_recoPFJet_btag_py)[i_jet1],(*_recoPFJet_btag_pz)[i_jet1],(*_recoPFJet_btag_e)[i_jet1]);
      TLorentzVector jet2((*_recoPFJet_btag_px)[i_jet2],(*_recoPFJet_btag_py)[i_jet2],(*_recoPFJet_btag_pz)[i_jet2],(*_recoPFJet_btag_e)[i_jet2]);
      TLorentzVector jet3((*_recoPFJet_untag_px)[i_jet3],(*_recoPFJet_untag_py)[i_jet3],(*_recoPFJet_untag_pz)[i_jet3],(*_recoPFJet_untag_e)[i_jet3]);
      TLorentzVector jet4((*_recoPFJet_untag_px)[i_jet4],(*_recoPFJet_untag_py)[i_jet4],(*_recoPFJet_untag_pz)[i_jet4],(*_recoPFJet_untag_e)[i_jet4]);
	
      _recoPFJet_toptag_best_btag_e = jet1.E();;
      _recoPFJet_toptag_best_btag_px = jet1.Px();
      _recoPFJet_toptag_best_btag_py = jet1.Py();
      _recoPFJet_toptag_best_btag_pz = jet1.Pz();
      _recoPFJet_toptag_best_btag_pt = jet1.Pt();
      _recoPFJet_toptag_best_btag_eta = jet1.Eta();
      _recoPFJet_toptag_best_btag_phi = jet1.Phi();
      _recoPFJet_toptag_best_btag_CSVscore = (*_recoPFJet_btag_CSVscore)[i_jet1];
      
      _recoPFJet_toptag_best_untag1_e = jet2.E();;
      _recoPFJet_toptag_best_untag1_px = jet2.Px();
      _recoPFJet_toptag_best_untag1_py = jet2.Py();
      _recoPFJet_toptag_best_untag1_pz = jet2.Pz();
      _recoPFJet_toptag_best_untag1_pt = jet2.Pt();
      _recoPFJet_toptag_best_untag1_eta = jet2.Eta();
      _recoPFJet_toptag_best_untag1_phi = jet2.Phi();
      _recoPFJet_toptag_best_untag1_CSVscore = (*_recoPFJet_btag_CSVscore)[i_jet2];
      
      _recoPFJet_toptag_best_untag2_e = jet3.E();;
      _recoPFJet_toptag_best_untag2_px = jet3.Px();
      _recoPFJet_toptag_best_untag2_py = jet3.Py();
      _recoPFJet_toptag_best_untag2_pz = jet3.Pz();
      _recoPFJet_toptag_best_untag2_pt = jet3.Pt();
      _recoPFJet_toptag_best_untag2_eta = jet3.Eta();
      _recoPFJet_toptag_best_untag2_phi = jet3.Phi();
      _recoPFJet_toptag_best_untag2_CSVscore = (*_recoPFJet_untag_CSVscore)[i_jet3];
      
      _recoPFJet_toptag_other_btag_e = jet4.E();;
      _recoPFJet_toptag_other_btag_px = jet4.Px();
      _recoPFJet_toptag_other_btag_py = jet4.Py();
      _recoPFJet_toptag_other_btag_pz = jet4.Pz();
      _recoPFJet_toptag_other_btag_pt = jet4.Pt();
      _recoPFJet_toptag_other_btag_eta = jet4.Eta();
      _recoPFJet_toptag_other_btag_phi = jet4.Phi();
      _recoPFJet_toptag_other_btag_CSVscore = (*_recoPFJet_untag_CSVscore)[i_jet4];


    }
      

    tree_new->Fill();

  }

  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}









void add_toptag3(TString filename_in, TString filename_out, TString treename){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  //Old branches used

  int _n_recoPFJet_btag_loose;

  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_px;
  vector<float> *_recoPFJet_py;
  vector<float> *_recoPFJet_pz;
  vector<float> *_recoPFJet_CSVscore;

  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);


  //Top tag

  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _recoPFJet_best_MW;
  float _recoPFJet_best_MTop;
  
  float _recoPFJet_toptag_best_btag_e;
  float _recoPFJet_toptag_best_btag_px;
  float _recoPFJet_toptag_best_btag_py;
  float _recoPFJet_toptag_best_btag_pz;
  float _recoPFJet_toptag_best_btag_pt;
  float _recoPFJet_toptag_best_btag_eta;
  float _recoPFJet_toptag_best_btag_phi;
  float _recoPFJet_toptag_best_btag_CSVscore;

  float _recoPFJet_toptag_best_untag1_e;
  float _recoPFJet_toptag_best_untag1_px;
  float _recoPFJet_toptag_best_untag1_py;
  float _recoPFJet_toptag_best_untag1_pz;
  float _recoPFJet_toptag_best_untag1_pt;
  float _recoPFJet_toptag_best_untag1_eta;
  float _recoPFJet_toptag_best_untag1_phi;
  float _recoPFJet_toptag_best_untag1_CSVscore;

  float _recoPFJet_toptag_best_untag2_e;
  float _recoPFJet_toptag_best_untag2_px;
  float _recoPFJet_toptag_best_untag2_py;
  float _recoPFJet_toptag_best_untag2_pz;
  float _recoPFJet_toptag_best_untag2_pt;
  float _recoPFJet_toptag_best_untag2_eta;
  float _recoPFJet_toptag_best_untag2_phi;
  float _recoPFJet_toptag_best_untag2_CSVscore;

  float _recoPFJet_toptag_other_btag_e;
  float _recoPFJet_toptag_other_btag_px;
  float _recoPFJet_toptag_other_btag_py;
  float _recoPFJet_toptag_other_btag_pz;
  float _recoPFJet_toptag_other_btag_pt;
  float _recoPFJet_toptag_other_btag_eta;
  float _recoPFJet_toptag_other_btag_phi;
  float _recoPFJet_toptag_other_btag_CSVscore;


  tree_new->Branch("recoPFJet_best_MW",&_recoPFJet_best_MW,"recoPFJet_best_MW/F");
  tree_new->Branch("recoPFJet_best_MTop",&_recoPFJet_best_MTop,"recoPFJet_best_MTop/F");
  
  tree_new->Branch("recoPFJet_toptag_best_btag_e",&_recoPFJet_toptag_best_btag_e,"recoPFJet_toptag_best_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_px",&_recoPFJet_toptag_best_btag_px,"recoPFJet_toptag_best_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_py",&_recoPFJet_toptag_best_btag_py,"recoPFJet_toptag_best_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pz",&_recoPFJet_toptag_best_btag_pz,"recoPFJet_toptag_best_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pt",&_recoPFJet_toptag_best_btag_pt,"recoPFJet_toptag_best_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_eta",&_recoPFJet_toptag_best_btag_eta,"recoPFJet_toptag_best_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_phi",&_recoPFJet_toptag_best_btag_phi,"recoPFJet_toptag_best_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_CSVscore",&_recoPFJet_toptag_best_btag_CSVscore,"recoPFJet_toptag_best_btag_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag1_e",&_recoPFJet_toptag_best_untag1_e,"recoPFJet_toptag_best_untag1_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_px",&_recoPFJet_toptag_best_untag1_px,"recoPFJet_toptag_best_untag1_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_py",&_recoPFJet_toptag_best_untag1_py,"recoPFJet_toptag_best_untag1_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pz",&_recoPFJet_toptag_best_untag1_pz,"recoPFJet_toptag_best_untag1_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pt",&_recoPFJet_toptag_best_untag1_pt,"recoPFJet_toptag_best_untag1_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_eta",&_recoPFJet_toptag_best_untag1_eta,"recoPFJet_toptag_best_untag1_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_phi",&_recoPFJet_toptag_best_untag1_phi,"recoPFJet_toptag_best_untag1_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_CSVscore",&_recoPFJet_toptag_best_untag1_CSVscore,"recoPFJet_toptag_best_untag1_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag2_e",&_recoPFJet_toptag_best_untag2_e,"recoPFJet_toptag_best_untag2_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_px",&_recoPFJet_toptag_best_untag2_px,"recoPFJet_toptag_best_untag2_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_py",&_recoPFJet_toptag_best_untag2_py,"recoPFJet_toptag_best_untag2_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pz",&_recoPFJet_toptag_best_untag2_pz,"recoPFJet_toptag_best_untag2_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pt",&_recoPFJet_toptag_best_untag2_pt,"recoPFJet_toptag_best_untag2_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_eta",&_recoPFJet_toptag_best_untag2_eta,"recoPFJet_toptag_best_untag2_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_phi",&_recoPFJet_toptag_best_untag2_phi,"recoPFJet_toptag_best_untag2_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_CSVscore",&_recoPFJet_toptag_best_untag2_CSVscore,"recoPFJet_toptag_best_untag2_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_other_btag_e",&_recoPFJet_toptag_other_btag_e,"recoPFJet_toptag_other_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_px",&_recoPFJet_toptag_other_btag_px,"recoPFJet_toptag_other_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_py",&_recoPFJet_toptag_other_btag_py,"recoPFJet_toptag_other_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pz",&_recoPFJet_toptag_other_btag_pz,"recoPFJet_toptag_other_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pt",&_recoPFJet_toptag_other_btag_pt,"recoPFJet_toptag_other_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_eta",&_recoPFJet_toptag_other_btag_eta,"recoPFJet_toptag_other_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_phi",&_recoPFJet_toptag_other_btag_phi,"recoPFJet_toptag_other_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_CSVscore",&_recoPFJet_toptag_other_btag_CSVscore,"recoPFJet_toptag_other_btag_CSVscore/F");





  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _n_recoPFJet_btag_loose = 0;

    _recoPFJet_e = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;
    _recoPFJet_CSVscore = 0;


    _recoPFJet_best_MW = 0;
    _recoPFJet_best_MTop = 0;
   
    _recoPFJet_toptag_best_btag_e = 0;
    _recoPFJet_toptag_best_btag_px = 0;
    _recoPFJet_toptag_best_btag_py = 0;
    _recoPFJet_toptag_best_btag_pz = 0;
    _recoPFJet_toptag_best_btag_pt = 0;
    _recoPFJet_toptag_best_btag_eta = 0;
    _recoPFJet_toptag_best_btag_phi = 0;
    _recoPFJet_toptag_best_btag_CSVscore = 0;

    _recoPFJet_toptag_best_untag1_e = 0;
    _recoPFJet_toptag_best_untag1_px = 0;
    _recoPFJet_toptag_best_untag1_py = 0;
    _recoPFJet_toptag_best_untag1_pz = 0;
    _recoPFJet_toptag_best_untag1_pt = 0;
    _recoPFJet_toptag_best_untag1_eta = 0;
    _recoPFJet_toptag_best_untag1_phi = 0;
    _recoPFJet_toptag_best_untag1_CSVscore = 0;

    _recoPFJet_toptag_best_untag2_e = 0;
    _recoPFJet_toptag_best_untag2_px = 0;
    _recoPFJet_toptag_best_untag2_py = 0;
    _recoPFJet_toptag_best_untag2_pz = 0;
    _recoPFJet_toptag_best_untag2_pt = 0;
    _recoPFJet_toptag_best_untag2_eta = 0;
    _recoPFJet_toptag_best_untag2_phi = 0;
    _recoPFJet_toptag_best_untag2_CSVscore = 0;

    _recoPFJet_toptag_other_btag_e = 0;
    _recoPFJet_toptag_other_btag_px = 0;
    _recoPFJet_toptag_other_btag_py = 0;
    _recoPFJet_toptag_other_btag_pz = 0;
    _recoPFJet_toptag_other_btag_pt = 0;
    _recoPFJet_toptag_other_btag_eta = 0;
    _recoPFJet_toptag_other_btag_phi = 0;
    _recoPFJet_toptag_other_btag_CSVscore = 0;


    tree->GetEntry(i);

    double mW=80.4;
    double mTop=173.2;

    if((*_recoPFJet_e).size()>3 && _n_recoPFJet_btag_loose>0){	
	
      double deltaM_W = -1;
      
      vector<int> index_TopTag;
      index_TopTag.push_back(-1);
      index_TopTag.push_back(-1);
      index_TopTag.push_back(-1);
      index_TopTag.push_back(-1);


      for(unsigned int i_jet1=0; i_jet1<(*_recoPFJet_e).size()-1; i_jet1++){
	TLorentzVector jet1 ( (*_recoPFJet_px)[i_jet1], (*_recoPFJet_py)[i_jet1], (*_recoPFJet_pz)[i_jet1], (*_recoPFJet_e)[i_jet1] );
	  	  
	for(unsigned int i_jet2=i_jet1+1; i_jet2<(*_recoPFJet_e).size(); i_jet2++){
	    	    
	  TLorentzVector jet2 ( (*_recoPFJet_px)[i_jet2], (*_recoPFJet_py)[i_jet2], (*_recoPFJet_pz)[i_jet2], (*_recoPFJet_e)[i_jet2] );
	    	      
	    float mjj=(jet1+jet2).M();
	    float deltaM = fabs(mjj-mW);
	    
	    if( deltaM_W<0 || deltaM<deltaM_W){
	      
	      deltaM_W = deltaM;
	      
	      index_TopTag[1] = i_jet1;
	      index_TopTag[2] = i_jet2;
	      
	    }
	    
	}

      }

     
      TLorentzVector jet_W1((*_recoPFJet_px)[index_TopTag[1]], (*_recoPFJet_py)[index_TopTag[1]], (*_recoPFJet_pz)[index_TopTag[1]], (*_recoPFJet_e)[index_TopTag[1]]);
      TLorentzVector jet_W2((*_recoPFJet_px)[index_TopTag[2]], (*_recoPFJet_py)[index_TopTag[2]], (*_recoPFJet_pz)[index_TopTag[2]], (*_recoPFJet_e)[index_TopTag[2]]);

      double deltaM_Top = -1;	 
                 
      for(unsigned int i_bjeth=0; i_bjeth<(*_recoPFJet_e).size(); i_bjeth++){

	if( i_bjeth==index_TopTag[1] || i_bjeth==index_TopTag[2]) continue;
	if( (*_recoPFJet_CSVscore)[i_bjeth]<0.46) continue;

	TLorentzVector bjeth((*_recoPFJet_px)[i_bjeth], (*_recoPFJet_py)[i_bjeth], (*_recoPFJet_pz)[i_bjeth], (*_recoPFJet_e)[i_bjeth]);

	float mjjj=(jet_W1+jet_W2+bjeth).M();
	float deltaM = fabs(mjjj-mTop);
	    
	if( deltaM_Top<0 || deltaM<deltaM_Top){
	  
	  deltaM_Top = deltaM;
	  
	  index_TopTag[0] = i_bjeth;
	  
	}
	
      }


      //If light jet from top pass CSVL + b-jet from top does not pass CSVL 
      if(index_TopTag[0]<0){

	for(unsigned int i_bjeth=0; i_bjeth<(*_recoPFJet_e).size(); i_bjeth++){
	  
	  if( i_bjeth==index_TopTag[1] || i_bjeth==index_TopTag[2]) continue;

	  TLorentzVector bjeth((*_recoPFJet_px)[i_bjeth], (*_recoPFJet_py)[i_bjeth], (*_recoPFJet_pz)[i_bjeth], (*_recoPFJet_e)[i_bjeth]);
	  
	  float mjjj=(jet_W1+jet_W2+bjeth).M();
	  float deltaM = fabs(mjjj-mTop);
	  
	  if( deltaM_Top<0 || deltaM<deltaM_Top){
	    
	    deltaM_Top = deltaM;
	    
	    index_TopTag[0] = i_bjeth;
	    
	  }
	  
	}

      }


      float max_CSV = -11.;

      for(unsigned int i_bjetl=0; i_bjetl<(*_recoPFJet_e).size(); i_bjetl++){
	  
	if( i_bjetl==index_TopTag[0] || i_bjetl==index_TopTag[1] || i_bjetl==index_TopTag[2]) continue;
      
	float CSV = (*_recoPFJet_CSVscore)[i_bjetl];

	if(CSV>max_CSV){
	  max_CSV = CSV;
	  index_TopTag[4] = i_bjetl;
	}
	

      }


      int i_jet1=index_TopTag[0];
      int i_jet2=index_TopTag[1];
      int i_jet3=index_TopTag[2];
      int i_jet4=index_TopTag[3];   

      TLorentzVector jet1((*_recoPFJet_px)[i_jet1],(*_recoPFJet_py)[i_jet1],(*_recoPFJet_pz)[i_jet1],(*_recoPFJet_e)[i_jet1]);
      TLorentzVector jet2((*_recoPFJet_px)[i_jet2],(*_recoPFJet_py)[i_jet2],(*_recoPFJet_pz)[i_jet2],(*_recoPFJet_e)[i_jet2]);
      TLorentzVector jet3((*_recoPFJet_px)[i_jet3],(*_recoPFJet_py)[i_jet3],(*_recoPFJet_pz)[i_jet3],(*_recoPFJet_e)[i_jet3]);
      TLorentzVector jet4((*_recoPFJet_px)[i_jet4],(*_recoPFJet_py)[i_jet4],(*_recoPFJet_pz)[i_jet4],(*_recoPFJet_e)[i_jet4]);

      _recoPFJet_best_MW = (jet2+jet3).M();;
      _recoPFJet_best_MTop = (jet1+jet2+jet3).M();      
	
      _recoPFJet_toptag_best_btag_e = jet1.E();;
      _recoPFJet_toptag_best_btag_px = jet1.Px();
      _recoPFJet_toptag_best_btag_py = jet1.Py();
      _recoPFJet_toptag_best_btag_pz = jet1.Pz();
      _recoPFJet_toptag_best_btag_pt = jet1.Pt();
      _recoPFJet_toptag_best_btag_eta = jet1.Eta();
      _recoPFJet_toptag_best_btag_phi = jet1.Phi();
      _recoPFJet_toptag_best_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet1];
      
      _recoPFJet_toptag_best_untag1_e = jet2.E();;
      _recoPFJet_toptag_best_untag1_px = jet2.Px();
      _recoPFJet_toptag_best_untag1_py = jet2.Py();
      _recoPFJet_toptag_best_untag1_pz = jet2.Pz();
      _recoPFJet_toptag_best_untag1_pt = jet2.Pt();
      _recoPFJet_toptag_best_untag1_eta = jet2.Eta();
      _recoPFJet_toptag_best_untag1_phi = jet2.Phi();
      _recoPFJet_toptag_best_untag1_CSVscore = (*_recoPFJet_CSVscore)[i_jet2];
      
      _recoPFJet_toptag_best_untag2_e = jet3.E();;
      _recoPFJet_toptag_best_untag2_px = jet3.Px();
      _recoPFJet_toptag_best_untag2_py = jet3.Py();
      _recoPFJet_toptag_best_untag2_pz = jet3.Pz();
      _recoPFJet_toptag_best_untag2_pt = jet3.Pt();
      _recoPFJet_toptag_best_untag2_eta = jet3.Eta();
      _recoPFJet_toptag_best_untag2_phi = jet3.Phi();
      _recoPFJet_toptag_best_untag2_CSVscore = (*_recoPFJet_CSVscore)[i_jet3];
      
      _recoPFJet_toptag_other_btag_e = jet4.E();;
      _recoPFJet_toptag_other_btag_px = jet4.Px();
      _recoPFJet_toptag_other_btag_py = jet4.Py();
      _recoPFJet_toptag_other_btag_pz = jet4.Pz();
      _recoPFJet_toptag_other_btag_pt = jet4.Pt();
      _recoPFJet_toptag_other_btag_eta = jet4.Eta();
      _recoPFJet_toptag_other_btag_phi = jet4.Phi();
      _recoPFJet_toptag_other_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet4];


    }

    tree_new->Fill();

  }

  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}














float recoPFJet_MW;
float recoPFJet_MTop;
float recoPFJet_bh_CSVscore;
float recoPFJet_dR_Whad;
float recoPFJet_dR_bWhad;
float recoPFJet_Whad_pt;
float recoPFJet_top_pt;


TMVA::Reader* Book_TopTag_MVAReader()
{

    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    reader->AddVariable("recoPFJet_MW", &recoPFJet_MW      );
    reader->AddVariable("recoPFJet_MTop", &recoPFJet_MTop      );
    reader->AddVariable("recoPFJet_bh_CSVscore", &recoPFJet_bh_CSVscore      );
    reader->AddVariable("recoPFJet_dR_Whad", &recoPFJet_dR_Whad      );
    reader->AddVariable("recoPFJet_dR_bWhad", &recoPFJet_dR_bWhad      );
    reader->AddVariable("recoPFJet_Whad_pt", &recoPFJet_Whad_pt      );
    reader->AddVariable("recoPFJet_top_pt", &recoPFJet_top_pt      );

    reader->BookMVA("BDT method", "weights/TMVAClassification_7D_BDT.weights.xml");

    return reader;
}








void add_toptag_MVA(TString filename_in, TString filename_out, TString treename){


  vector<TString> list;
  list.push_back(filename_in);


  TChain * tree = new TChain(treename);
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }

  TMVA::Reader* MVA_TopTag_reader = Book_TopTag_MVAReader();

  //Old branches used

  int _n_recoPFJet_btag_loose;

  vector<float> *_recoPFJet_e;
  vector<float> *_recoPFJet_px;
  vector<float> *_recoPFJet_py;
  vector<float> *_recoPFJet_pz;
  vector<float> *_recoPFJet_CSVscore;

  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);


  //Top tag

  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;


  TFile* f_new = TFile::Open(filename_out);
  if(f_new!=0){
    cout<<filename_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(filename_out,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  float _recoPFJet_best_TopTag_MVA;
  float _recoPFJet_best_TopTag_MW;
  float _recoPFJet_best_TopTag_MTop;
  
  float _recoPFJet_toptag_best_btag_e;
  float _recoPFJet_toptag_best_btag_px;
  float _recoPFJet_toptag_best_btag_py;
  float _recoPFJet_toptag_best_btag_pz;
  float _recoPFJet_toptag_best_btag_pt;
  float _recoPFJet_toptag_best_btag_eta;
  float _recoPFJet_toptag_best_btag_phi;
  float _recoPFJet_toptag_best_btag_CSVscore;

  float _recoPFJet_toptag_best_untag1_e;
  float _recoPFJet_toptag_best_untag1_px;
  float _recoPFJet_toptag_best_untag1_py;
  float _recoPFJet_toptag_best_untag1_pz;
  float _recoPFJet_toptag_best_untag1_pt;
  float _recoPFJet_toptag_best_untag1_eta;
  float _recoPFJet_toptag_best_untag1_phi;
  float _recoPFJet_toptag_best_untag1_CSVscore;

  float _recoPFJet_toptag_best_untag2_e;
  float _recoPFJet_toptag_best_untag2_px;
  float _recoPFJet_toptag_best_untag2_py;
  float _recoPFJet_toptag_best_untag2_pz;
  float _recoPFJet_toptag_best_untag2_pt;
  float _recoPFJet_toptag_best_untag2_eta;
  float _recoPFJet_toptag_best_untag2_phi;
  float _recoPFJet_toptag_best_untag2_CSVscore;

  float _recoPFJet_toptag_other_btag_e;
  float _recoPFJet_toptag_other_btag_px;
  float _recoPFJet_toptag_other_btag_py;
  float _recoPFJet_toptag_other_btag_pz;
  float _recoPFJet_toptag_other_btag_pt;
  float _recoPFJet_toptag_other_btag_eta;
  float _recoPFJet_toptag_other_btag_phi;
  float _recoPFJet_toptag_other_btag_CSVscore;


  tree_new->Branch("recoPFJet_best_TopTag_MVA",&_recoPFJet_best_TopTag_MVA,"recoPFJet_best_TopTag_MVA/F");
  tree_new->Branch("recoPFJet_best_TopTag_MW",&_recoPFJet_best_TopTag_MW,"recoPFJet_best_TopTag_MW/F");
  tree_new->Branch("recoPFJet_best_TopTag_MTop",&_recoPFJet_best_TopTag_MTop,"recoPFJet_best_TopTag_MTop/F");
  
  tree_new->Branch("recoPFJet_toptag_best_btag_e",&_recoPFJet_toptag_best_btag_e,"recoPFJet_toptag_best_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_px",&_recoPFJet_toptag_best_btag_px,"recoPFJet_toptag_best_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_py",&_recoPFJet_toptag_best_btag_py,"recoPFJet_toptag_best_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pz",&_recoPFJet_toptag_best_btag_pz,"recoPFJet_toptag_best_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_pt",&_recoPFJet_toptag_best_btag_pt,"recoPFJet_toptag_best_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_eta",&_recoPFJet_toptag_best_btag_eta,"recoPFJet_toptag_best_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_phi",&_recoPFJet_toptag_best_btag_phi,"recoPFJet_toptag_best_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_btag_CSVscore",&_recoPFJet_toptag_best_btag_CSVscore,"recoPFJet_toptag_best_btag_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag1_e",&_recoPFJet_toptag_best_untag1_e,"recoPFJet_toptag_best_untag1_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_px",&_recoPFJet_toptag_best_untag1_px,"recoPFJet_toptag_best_untag1_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_py",&_recoPFJet_toptag_best_untag1_py,"recoPFJet_toptag_best_untag1_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pz",&_recoPFJet_toptag_best_untag1_pz,"recoPFJet_toptag_best_untag1_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_pt",&_recoPFJet_toptag_best_untag1_pt,"recoPFJet_toptag_best_untag1_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_eta",&_recoPFJet_toptag_best_untag1_eta,"recoPFJet_toptag_best_untag1_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_phi",&_recoPFJet_toptag_best_untag1_phi,"recoPFJet_toptag_best_untag1_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag1_CSVscore",&_recoPFJet_toptag_best_untag1_CSVscore,"recoPFJet_toptag_best_untag1_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_best_untag2_e",&_recoPFJet_toptag_best_untag2_e,"recoPFJet_toptag_best_untag2_e/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_px",&_recoPFJet_toptag_best_untag2_px,"recoPFJet_toptag_best_untag2_px/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_py",&_recoPFJet_toptag_best_untag2_py,"recoPFJet_toptag_best_untag2_py/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pz",&_recoPFJet_toptag_best_untag2_pz,"recoPFJet_toptag_best_untag2_pz/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_pt",&_recoPFJet_toptag_best_untag2_pt,"recoPFJet_toptag_best_untag2_pt/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_eta",&_recoPFJet_toptag_best_untag2_eta,"recoPFJet_toptag_best_untag2_eta/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_phi",&_recoPFJet_toptag_best_untag2_phi,"recoPFJet_toptag_best_untag2_phi/F");
  tree_new->Branch("recoPFJet_toptag_best_untag2_CSVscore",&_recoPFJet_toptag_best_untag2_CSVscore,"recoPFJet_toptag_best_untag2_CSVscore/F");
  
  tree_new->Branch("recoPFJet_toptag_other_btag_e",&_recoPFJet_toptag_other_btag_e,"recoPFJet_toptag_other_btag_e/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_px",&_recoPFJet_toptag_other_btag_px,"recoPFJet_toptag_other_btag_px/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_py",&_recoPFJet_toptag_other_btag_py,"recoPFJet_toptag_other_btag_py/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pz",&_recoPFJet_toptag_other_btag_pz,"recoPFJet_toptag_other_btag_pz/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_pt",&_recoPFJet_toptag_other_btag_pt,"recoPFJet_toptag_other_btag_pt/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_eta",&_recoPFJet_toptag_other_btag_eta,"recoPFJet_toptag_other_btag_eta/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_phi",&_recoPFJet_toptag_other_btag_phi,"recoPFJet_toptag_other_btag_phi/F");
  tree_new->Branch("recoPFJet_toptag_other_btag_CSVscore",&_recoPFJet_toptag_other_btag_CSVscore,"recoPFJet_toptag_other_btag_CSVscore/F");





  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _n_recoPFJet_btag_loose = 0;

    _recoPFJet_e = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;
    _recoPFJet_CSVscore = 0;


    _recoPFJet_best_TopTag_MVA = 0;
    _recoPFJet_best_TopTag_MW = 0;
    _recoPFJet_best_TopTag_MTop = 0;
   
    _recoPFJet_toptag_best_btag_e = 0;
    _recoPFJet_toptag_best_btag_px = 0;
    _recoPFJet_toptag_best_btag_py = 0;
    _recoPFJet_toptag_best_btag_pz = 0;
    _recoPFJet_toptag_best_btag_pt = 0;
    _recoPFJet_toptag_best_btag_eta = 0;
    _recoPFJet_toptag_best_btag_phi = 0;
    _recoPFJet_toptag_best_btag_CSVscore = 0;

    _recoPFJet_toptag_best_untag1_e = 0;
    _recoPFJet_toptag_best_untag1_px = 0;
    _recoPFJet_toptag_best_untag1_py = 0;
    _recoPFJet_toptag_best_untag1_pz = 0;
    _recoPFJet_toptag_best_untag1_pt = 0;
    _recoPFJet_toptag_best_untag1_eta = 0;
    _recoPFJet_toptag_best_untag1_phi = 0;
    _recoPFJet_toptag_best_untag1_CSVscore = 0;

    _recoPFJet_toptag_best_untag2_e = 0;
    _recoPFJet_toptag_best_untag2_px = 0;
    _recoPFJet_toptag_best_untag2_py = 0;
    _recoPFJet_toptag_best_untag2_pz = 0;
    _recoPFJet_toptag_best_untag2_pt = 0;
    _recoPFJet_toptag_best_untag2_eta = 0;
    _recoPFJet_toptag_best_untag2_phi = 0;
    _recoPFJet_toptag_best_untag2_CSVscore = 0;

    _recoPFJet_toptag_other_btag_e = 0;
    _recoPFJet_toptag_other_btag_px = 0;
    _recoPFJet_toptag_other_btag_py = 0;
    _recoPFJet_toptag_other_btag_pz = 0;
    _recoPFJet_toptag_other_btag_pt = 0;
    _recoPFJet_toptag_other_btag_eta = 0;
    _recoPFJet_toptag_other_btag_phi = 0;
    _recoPFJet_toptag_other_btag_CSVscore = 0;


    tree->GetEntry(i);

    double mW=80.4;
    double mTop=173.2;

    if((*_recoPFJet_e).size()>3 && _n_recoPFJet_btag_loose>0){	
	
      double best_TopTag_MVA = -10;
      
      vector<unsigned int> index_TopTag;
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);
      index_TopTag.push_back(0);


      for(unsigned int i_jet1=0; i_jet1<(*_recoPFJet_e).size(); i_jet1++){
	TLorentzVector jet1 ( (*_recoPFJet_px)[i_jet1], (*_recoPFJet_py)[i_jet1], (*_recoPFJet_pz)[i_jet1], (*_recoPFJet_e)[i_jet1] );
	  
	if( (*_recoPFJet_CSVscore)[i_jet1]<0.46 ) continue;
	  
	for(unsigned int i_jet2=0; i_jet2<(*_recoPFJet_e).size()-1; i_jet2++){
	    
	  if(i_jet2==i_jet1) continue;
	    
	  TLorentzVector jet2 ( (*_recoPFJet_px)[i_jet2], (*_recoPFJet_py)[i_jet2], (*_recoPFJet_pz)[i_jet2], (*_recoPFJet_e)[i_jet2] );
	    
	  for(unsigned int i_jet3=i_jet2+1; i_jet3<(*_recoPFJet_e).size(); i_jet3++){
	      
	    if(i_jet3==i_jet1) continue;

	    TLorentzVector jet3 ( (*_recoPFJet_px)[i_jet3], (*_recoPFJet_py)[i_jet3], (*_recoPFJet_pz)[i_jet3], (*_recoPFJet_e)[i_jet3] );

	      
	    recoPFJet_MW = (jet2+jet3).M();
	    recoPFJet_MTop = (jet1+jet2+jet3).M();
	    recoPFJet_bh_CSVscore = (*_recoPFJet_CSVscore)[i_jet1];
	    recoPFJet_dR_Whad = jet2.DeltaR(jet3);
	    recoPFJet_dR_bWhad = jet1.DeltaR(jet2+jet3);
	    recoPFJet_Whad_pt = (jet2+jet3).Pt();
	    recoPFJet_top_pt = (jet1+jet2+jet3).Pt();


	    float TopTag_MVA = MVA_TopTag_reader->EvaluateMVA("BDT method");
	    
	    if( best_TopTag_MVA<-9 || TopTag_MVA>best_TopTag_MVA){
	      
	      best_TopTag_MVA = TopTag_MVA;
	      
	      index_TopTag[0] = i_jet1;
	      index_TopTag[1] = i_jet2;
	      index_TopTag[2] = i_jet3;
	      
	    }
	    
	  }
	  
	}
	
      }
      
      
      float max_CSV = -1;
      
      for(unsigned int i_jet4=0; i_jet4<(*_recoPFJet_e).size(); i_jet4++){

	if(i_jet4==index_TopTag[0] || i_jet4==index_TopTag[1] || i_jet4==index_TopTag[2]) continue;
	
	if((*_recoPFJet_CSVscore)[i_jet4]>max_CSV){
 
	  max_CSV = (*_recoPFJet_CSVscore)[i_jet4];
	  index_TopTag[3] = i_jet4;
	  
	}
	
      }
      
      
      _recoPFJet_best_TopTag_MVA = best_TopTag_MVA;
      
      int i_jet1=index_TopTag[0];
      int i_jet2=index_TopTag[1];
      int i_jet3=index_TopTag[2];
      int i_jet4=index_TopTag[3];   

      TLorentzVector jet1((*_recoPFJet_px)[i_jet1],(*_recoPFJet_py)[i_jet1],(*_recoPFJet_pz)[i_jet1],(*_recoPFJet_e)[i_jet1]);
      TLorentzVector jet2((*_recoPFJet_px)[i_jet2],(*_recoPFJet_py)[i_jet2],(*_recoPFJet_pz)[i_jet2],(*_recoPFJet_e)[i_jet2]);
      TLorentzVector jet3((*_recoPFJet_px)[i_jet3],(*_recoPFJet_py)[i_jet3],(*_recoPFJet_pz)[i_jet3],(*_recoPFJet_e)[i_jet3]);
      TLorentzVector jet4((*_recoPFJet_px)[i_jet4],(*_recoPFJet_py)[i_jet4],(*_recoPFJet_pz)[i_jet4],(*_recoPFJet_e)[i_jet4]);
	
      _recoPFJet_toptag_best_btag_e = jet1.E();;
      _recoPFJet_toptag_best_btag_px = jet1.Px();
      _recoPFJet_toptag_best_btag_py = jet1.Py();
      _recoPFJet_toptag_best_btag_pz = jet1.Pz();
      _recoPFJet_toptag_best_btag_pt = jet1.Pt();
      _recoPFJet_toptag_best_btag_eta = jet1.Eta();
      _recoPFJet_toptag_best_btag_phi = jet1.Phi();
      _recoPFJet_toptag_best_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet1];
      
      _recoPFJet_toptag_best_untag1_e = jet2.E();;
      _recoPFJet_toptag_best_untag1_px = jet2.Px();
      _recoPFJet_toptag_best_untag1_py = jet2.Py();
      _recoPFJet_toptag_best_untag1_pz = jet2.Pz();
      _recoPFJet_toptag_best_untag1_pt = jet2.Pt();
      _recoPFJet_toptag_best_untag1_eta = jet2.Eta();
      _recoPFJet_toptag_best_untag1_phi = jet2.Phi();
      _recoPFJet_toptag_best_untag1_CSVscore = (*_recoPFJet_CSVscore)[i_jet2];
      
      _recoPFJet_toptag_best_untag2_e = jet3.E();;
      _recoPFJet_toptag_best_untag2_px = jet3.Px();
      _recoPFJet_toptag_best_untag2_py = jet3.Py();
      _recoPFJet_toptag_best_untag2_pz = jet3.Pz();
      _recoPFJet_toptag_best_untag2_pt = jet3.Pt();
      _recoPFJet_toptag_best_untag2_eta = jet3.Eta();
      _recoPFJet_toptag_best_untag2_phi = jet3.Phi();
      _recoPFJet_toptag_best_untag2_CSVscore = (*_recoPFJet_CSVscore)[i_jet3];
      
      _recoPFJet_toptag_other_btag_e = jet4.E();;
      _recoPFJet_toptag_other_btag_px = jet4.Px();
      _recoPFJet_toptag_other_btag_py = jet4.Py();
      _recoPFJet_toptag_other_btag_pz = jet4.Pz();
      _recoPFJet_toptag_other_btag_pt = jet4.Pt();
      _recoPFJet_toptag_other_btag_eta = jet4.Eta();
      _recoPFJet_toptag_other_btag_phi = jet4.Phi();
      _recoPFJet_toptag_other_btag_CSVscore = (*_recoPFJet_CSVscore)[i_jet4];
	
      _recoPFJet_best_TopTag_MW = (jet2+jet3).M();
      _recoPFJet_best_TopTag_MTop = (jet1+jet2+jet3).M();


    }

    tree_new->Fill();

  }

  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}







