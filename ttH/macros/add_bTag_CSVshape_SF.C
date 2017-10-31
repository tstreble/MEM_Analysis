#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include "bTagSF_CSVshape.cc"

using namespace std;

void add_bTag_CSVshape_SF(TString filein, TString fileout, vector<TString> treename){

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
    
    
    TTree* tree_new=tree->GetTree()->CloneTree(0);

    //New branches
    float _bTagSF_CSVshape_weight;
    float _bTagSF_CSVshape_weight_JESUp;
    float _bTagSF_CSVshape_weight_JESDown;
    float _bTagSF_CSVshape_weight_LFUp;
    float _bTagSF_CSVshape_weight_LFDown;
    float _bTagSF_CSVshape_weight_HFUp;
    float _bTagSF_CSVshape_weight_HFDown;
    float _bTagSF_CSVshape_weight_HFStats1Up;
    float _bTagSF_CSVshape_weight_HFStats1Down;
    float _bTagSF_CSVshape_weight_HFStats2Up;
    float _bTagSF_CSVshape_weight_HFStats2Down;
    float _bTagSF_CSVshape_weight_LFStats1Up;
    float _bTagSF_CSVshape_weight_LFStats1Down;
    float _bTagSF_CSVshape_weight_LFStats2Up;
    float _bTagSF_CSVshape_weight_LFStats2Down;
    float _bTagSF_CSVshape_weight_CFErr1Up;
    float _bTagSF_CSVshape_weight_CFErr1Down;
    float _bTagSF_CSVshape_weight_CFErr2Up;
    float _bTagSF_CSVshape_weight_CFErr2Down;
    
    //vector<int> _recoPFJet_hadronFlavour;
    
    
    tree_new->Branch("bTagSF_CSVshape_weight_v2",&_bTagSF_CSVshape_weight,"bTagSF_CSVshape_weight_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_JESUp_v2",&_bTagSF_CSVshape_weight_JESUp,"bTagSF_CSVshape_weight_JESUp_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_JESDown_v2",&_bTagSF_CSVshape_weight_JESDown,"bTagSF_CSVshape_weight_JESDown_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFUp_v2",&_bTagSF_CSVshape_weight_LFUp,"bTagSF_CSVshape_weight_LFUp_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFDown_v2",&_bTagSF_CSVshape_weight_LFDown,"bTagSF_CSVshape_weight_LFDown_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFUp_v2",&_bTagSF_CSVshape_weight_HFUp,"bTagSF_CSVshape_weight_HFUp_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFDown_v2",&_bTagSF_CSVshape_weight_HFDown,"bTagSF_CSVshape_weight_HFDown_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats1Up_v2",&_bTagSF_CSVshape_weight_HFStats1Up,"bTagSF_CSVshape_weight_HFStats1Up_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats1Down_v2",&_bTagSF_CSVshape_weight_HFStats1Down,"bTagSF_CSVshape_weight_HFStats1Down_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats2Up_v2",&_bTagSF_CSVshape_weight_HFStats2Up,"bTagSF_CSVshape_weight_HFStats2Up_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats2Down_v2",&_bTagSF_CSVshape_weight_HFStats2Down,"bTagSF_CSVshape_weight_HFStats2Down_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats1Up_v2",&_bTagSF_CSVshape_weight_LFStats1Up,"bTagSF_CSVshape_weight_LFStats1Up_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats1Down_v2",&_bTagSF_CSVshape_weight_LFStats1Down,"bTagSF_CSVshape_weight_LFStats1Down_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats2Up_v2",&_bTagSF_CSVshape_weight_LFStats2Up,"bTagSF_CSVshape_weight_LFStats2Up_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats2Down_v2",&_bTagSF_CSVshape_weight_LFStats2Down,"bTagSF_CSVshape_weight_LFStats2Down_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr1Up_v2",&_bTagSF_CSVshape_weight_CFErr1Up,"bTagSF_CSVshape_weight_CFErr1Up_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr1Down_v2",&_bTagSF_CSVshape_weight_CFErr1Down,"bTagSF_CSVshape_weight_CFErr1Down_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr2Up_v2",&_bTagSF_CSVshape_weight_CFErr2Up,"bTagSF_CSVshape_weight_CFErr2Up_v2/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr2Down_v2",&_bTagSF_CSVshape_weight_CFErr2Down,"bTagSF_CSVshape_weight_CFErr2Down_v2/F");
    
    //tree_new->Branch("recoPFJet_hadronFlavour",&_recoPFJet_hadronFlavour);
  


    //Old branches
    vector<float>* _recoPFJet_px;
    vector<float>* _recoPFJet_py;
    vector<float>* _recoPFJet_pz;
    vector<float>* _recoPFJet_e;
    vector<float>* _recoPFJet_CSVscore;
    vector<int>* _recoPFJet_hadronFlavour;    

    /*vector<float>* _jets_px;
    vector<float>* _jets_py;
    vector<float>* _jets_pz;
    vector<float>* _jets_e;
    vector<int>* _jets_HadronFlavour;*/
    
    tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
    tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
    tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
    tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
    tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);
    tree->SetBranchAddress("recoPFJet_hadronFlavour",&_recoPFJet_hadronFlavour);
    
    /*tree->SetBranchAddress("jets_px",&_jets_px);
    tree->SetBranchAddress("jets_py",&_jets_py);
    tree->SetBranchAddress("jets_pz",&_jets_pz);
    tree->SetBranchAddress("jets_e",&_jets_e);
    tree->SetBranchAddress("jets_HadronFlavour",&_jets_HadronFlavour);*/
    
    
    //bTagSF_CSVshape* bTagSF_computer = new bTagSF_CSVshape("bTagSF_weights/CSVv2_ichep.csv");
    bTagSF_CSVshape* bTagSF_computer = new bTagSF_CSVshape("bTagSF_weights/CSVv2Moriond17_2017_1_26_BtoH.csv");

    //nentries = 10;    

    for(int i=0;i<nentries;i++){

      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _bTagSF_CSVshape_weight = 0;
      _bTagSF_CSVshape_weight_JESUp = 0;
      _bTagSF_CSVshape_weight_JESDown = 0;
      _bTagSF_CSVshape_weight_LFUp = 0;
      _bTagSF_CSVshape_weight_LFDown = 0;
      _bTagSF_CSVshape_weight_HFUp = 0;
      _bTagSF_CSVshape_weight_HFDown = 0;
      _bTagSF_CSVshape_weight_HFStats1Up = 0;
      _bTagSF_CSVshape_weight_HFStats1Down = 0;
      _bTagSF_CSVshape_weight_HFStats2Up = 0;
      _bTagSF_CSVshape_weight_HFStats2Down = 0;
      _bTagSF_CSVshape_weight_LFStats1Up = 0;
      _bTagSF_CSVshape_weight_LFStats1Down = 0;
      _bTagSF_CSVshape_weight_LFStats2Up = 0;
      _bTagSF_CSVshape_weight_LFStats2Down = 0;
      _bTagSF_CSVshape_weight_CFErr1Up = 0;
      _bTagSF_CSVshape_weight_CFErr1Down = 0;
      _bTagSF_CSVshape_weight_CFErr2Up = 0;
      _bTagSF_CSVshape_weight_CFErr2Down = 0;
      
      //_recoPFJet_hadronFlavour.clear();
      
      _recoPFJet_px = 0;
      _recoPFJet_py = 0;
      _recoPFJet_pz = 0;
      _recoPFJet_e = 0;
      _recoPFJet_CSVscore = 0;
      _recoPFJet_hadronFlavour = 0;
      
      /*_jets_px = 0;
      _jets_py = 0;
      _jets_pz = 0;
      _jets_e = 0;
      _jets_HadronFlavour = 0;*/
      
      
      tree->GetEntry(i);
      
      vector<TLorentzVector> jets_tlv;
      
      for(unsigned int i_PFjet=0;i_PFjet<(*_recoPFJet_px).size();i_PFjet++){
	
	TLorentzVector PFJet((*_recoPFJet_px)[i_PFjet], (*_recoPFJet_py)[i_PFjet], (*_recoPFJet_pz)[i_PFjet], (*_recoPFJet_e)[i_PFjet]);
	jets_tlv.push_back(PFJet);
	
	/*for(unsigned int i_jet=0;i_jet<(*_jets_px).size();i_jet++){
	  
	  TLorentzVector jet((*_jets_px)[i_jet], (*_jets_py)[i_jet], (*_jets_pz)[i_jet], (*_jets_e)[i_jet]);
	  
	  if(jet.DeltaR(PFJet)<0.01){
	    _recoPFJet_hadronFlavour.push_back((*_jets_HadronFlavour)[i_jet]);
	    break;
	  }
	  
	  }*/
	
	}
      
      _bTagSF_CSVshape_weight = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::central);
      _bTagSF_CSVshape_weight_JESUp = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::JESUp);
      _bTagSF_CSVshape_weight_JESDown = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::JESDown);
      _bTagSF_CSVshape_weight_LFUp = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::LFUp);
      _bTagSF_CSVshape_weight_LFDown = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::LFDown);
      _bTagSF_CSVshape_weight_HFUp = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::HFUp);
      _bTagSF_CSVshape_weight_HFDown = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::HFDown);
      _bTagSF_CSVshape_weight_HFStats1Up = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::HFStats1Up);
      _bTagSF_CSVshape_weight_HFStats1Down = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::HFStats1Down);
      _bTagSF_CSVshape_weight_HFStats2Up = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::HFStats2Up);
      _bTagSF_CSVshape_weight_HFStats2Down = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::HFStats2Down);
      _bTagSF_CSVshape_weight_LFStats1Up = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::LFStats1Up);
      _bTagSF_CSVshape_weight_LFStats1Down = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::LFStats1Down);
      _bTagSF_CSVshape_weight_LFStats2Up = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::LFStats2Up);
      _bTagSF_CSVshape_weight_LFStats2Down = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::LFStats2Down);
      _bTagSF_CSVshape_weight_CFErr1Up = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::CFErr1Up);
      _bTagSF_CSVshape_weight_CFErr1Down = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::CFErr1Down);
      _bTagSF_CSVshape_weight_CFErr2Up = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::CFErr2Up);
      _bTagSF_CSVshape_weight_CFErr2Down = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, (*_recoPFJet_hadronFlavour), bTagSF_CSVshape::CFErr2Down);
      
      tree_new->Fill();    
      
    }
    
    f_new->cd();
    
    tree_new->Write();

  }

  f_new->Close();
  
    
  return;
  
}
  
  






/*void add_bTag_CSVshape_SF_fromSecondaryFile(TString filein, TString fileout, TString treename, TString filein2, TString treename2){

  TChain * tree = new TChain(treename);
  tree->Add(filein);

  TChain * tree2 = new TChain(treename2);
  tree2->Add(filein2);
  

  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  Long64_t nentries2 = tree2->GetEntries();

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  f_new = TFile::Open(fileout,"RECREATE");


  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  float _bTagSF_CSVshape_weight;
  vector<int> _recoPFJet_hadronFlavour;


  tree_new->Branch("bTagSF_CSVshape_weight",&_bTagSF_CSVshape_weight,"bTagSF_CSVshape_weight/F");
  tree_new->Branch("recoPFJet_hadronFlavour",&_recoPFJet_hadronFlavour);



  //Old branches
  unsigned long long _EventNumber1;
  vector<float>* _recoPFJet_px;
  vector<float>* _recoPFJet_py;
  vector<float>* _recoPFJet_pz;
  vector<float>* _recoPFJet_e;
  vector<float>* _recoPFJet_CSVscore;

  unsigned long long _EventNumber2;
  vector<float>* _jets_px;
  vector<float>* _jets_py;
  vector<float>* _jets_pz;
  vector<float>* _jets_e;
  vector<int>* _jets_HadronFlavour;

  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);
  tree->SetBranchAddress("EventNumber",&_EventNumber1);

  tree2->SetBranchAddress("jets_px",&_jets_px);
  tree2->SetBranchAddress("jets_py",&_jets_py);
  tree2->SetBranchAddress("jets_pz",&_jets_pz);
  tree2->SetBranchAddress("jets_e",&_jets_e);
  tree2->SetBranchAddress("jets_HadronFlavour",&_jets_HadronFlavour);
  tree2->SetBranchAddress("EventNumber",&_EventNumber2);


  bTagSF_CSVshape* bTagSF_computer = new bTagSF_CSVshape("bTagSF_weights/CSVv2_ichep.csv");

  //nentries = 10;

  int i2=0;

  for(int i=0;i<nentries;i++){
    
    if(i%1000==0)
      cout<<"i="<<i<<endl;

    _bTagSF_CSVshape_weight = 0;
    _recoPFJet_hadronFlavour.clear();

    _EventNumber1 = 0;
    _recoPFJet_px = 0;
    _recoPFJet_py = 0;
    _recoPFJet_pz = 0;
    _recoPFJet_e = 0;
    _recoPFJet_CSVscore = 0;

    _EventNumber2 = 0;
    _jets_px = 0;
    _jets_py = 0;
    _jets_pz = 0;
    _jets_e = 0;
    _jets_HadronFlavour = 0;
    

    tree->GetEntry(i);

    tree2->GetEntry(i2);

    while(_EventNumber1 != _EventNumber2 && i2<nentries2){
      i2++;

      _EventNumber2 = 0;
      _jets_px = 0;
      _jets_py = 0;
      _jets_pz = 0;
      _jets_e = 0;
      _jets_HadronFlavour = 0;

      tree2->GetEntry(i2);
    }

    if(i2==nentries2){
      cout<<"Problem"<<endl;
      return;
    }


    vector<TLorentzVector> jets_tlv;

    for(unsigned int i_PFjet=0;i_PFjet<(*_recoPFJet_px).size();i_PFjet++){
 
      TLorentzVector PFJet((*_recoPFJet_px)[i_PFjet], (*_recoPFJet_py)[i_PFjet], (*_recoPFJet_pz)[i_PFjet], (*_recoPFJet_e)[i_PFjet]);
      jets_tlv.push_back(PFJet);

      for(unsigned int i_jet=0;i_jet<(*_jets_px).size();i_jet++){
	
	TLorentzVector jet((*_jets_px)[i_jet], (*_jets_py)[i_jet], (*_jets_pz)[i_jet], (*_jets_e)[i_jet]);

	if(jet.DeltaR(PFJet)<0.01){
	  _recoPFJet_hadronFlavour.push_back((*_jets_HadronFlavour)[i_jet]);
	  break;
	}

      }

    }

    _bTagSF_CSVshape_weight = bTagSF_computer->getEvtWeight((*_recoPFJet_CSVscore), jets_tlv, _recoPFJet_hadronFlavour, bTagSF_CSVshape::central);


    tree_new->Fill();    

  }
  
  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}
      
  
*/



void add_bTag_CSVshape_SF_fromSecondaryFile(TString filein, TString fileout, TString treename, TString filein2, TString treename2){

  TChain * tree = new TChain(treename);
  tree->Add(filein);

  //Old branches
  unsigned long long _EventNumber1;
  tree->SetBranchAddress("EventNumber",&_EventNumber1);


  TChain * tree2 = new TChain(treename2);
  tree2->Add(filein2);
  

  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  Long64_t nentries2 = tree2->GetEntries();

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  f_new = TFile::Open(fileout,"RECREATE");


  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  float _bTagSF_CSVshape_weight_v2;

  tree_new->Branch("bTagSF_CSVshape_weight_v2",&_bTagSF_CSVshape_weight_v2,"bTagSF_CSVshape_weight_v2/F");
 
  unsigned long long _EventNumber2;
  tree2->SetBranchAddress("EventNumber",&_EventNumber2);
  tree2->SetBranchAddress("bTagSF_CSVshape_weight_v2",&_bTagSF_CSVshape_weight_v2);


  int iEntry2=0;

  for(int i=0;i<nentries;i++){
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;  

    _EventNumber1 = 0;
    _EventNumber2 = 0;
    _bTagSF_CSVshape_weight_v2 = 0;
    

    tree->GetEntry(i);

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





void test_bTag(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_2lOS_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");

  TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split_btagSF_new.root";

  add_bTag_CSVshape_SF(filein,
		       fileout,
		       treename);



}
