#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include "bTagSF_CSVshape.cc"

using namespace std;

void add_dummy_branch(TString filein, TString fileout, vector<TString> treename){
  
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
    vector<int> _genpart_TauGenDetailedDecayMode;
    
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
    
    vector<int> _recoPFJet_hadronFlavour;

    tree_new->Branch("bTagSF_CSVshape_weight",&_bTagSF_CSVshape_weight,"bTagSF_CSVshape_weight/F");
    tree_new->Branch("bTagSF_CSVshape_weight_JESUp",&_bTagSF_CSVshape_weight_JESUp,"bTagSF_CSVshape_weight_JESUp/F");
    tree_new->Branch("bTagSF_CSVshape_weight_JESDown",&_bTagSF_CSVshape_weight_JESDown,"bTagSF_CSVshape_weight_JESDown/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFUp",&_bTagSF_CSVshape_weight_LFUp,"bTagSF_CSVshape_weight_LFUp/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFDown",&_bTagSF_CSVshape_weight_LFDown,"bTagSF_CSVshape_weight_LFDown/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFUp",&_bTagSF_CSVshape_weight_HFUp,"bTagSF_CSVshape_weight_HFUp/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFDown",&_bTagSF_CSVshape_weight_HFDown,"bTagSF_CSVshape_weight_HFDown/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats1Up",&_bTagSF_CSVshape_weight_HFStats1Up,"bTagSF_CSVshape_weight_HFStats1Up/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats1Down",&_bTagSF_CSVshape_weight_HFStats1Down,"bTagSF_CSVshape_weight_HFStats1Down/F");
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats2Up",&_bTagSF_CSVshape_weight_HFStats2Up);
    tree_new->Branch("bTagSF_CSVshape_weight_HFStats2Down",&_bTagSF_CSVshape_weight_HFStats2Down,"bTagSF_CSVshape_weight_HFStats2Down/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats1Up",&_bTagSF_CSVshape_weight_LFStats1Up,"bTagSF_CSVshape_weight_LFStats1Up/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats1Down",&_bTagSF_CSVshape_weight_LFStats1Down,"bTagSF_CSVshape_weight_LFStats1Down/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats2Up",&_bTagSF_CSVshape_weight_LFStats2Up,"bTagSF_CSVshape_weight_LFStats2Up/F");
    tree_new->Branch("bTagSF_CSVshape_weight_LFStats2Down",&_bTagSF_CSVshape_weight_LFStats2Down,"bTagSF_CSVshape_weight_LFStats2Down/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr1Up",&_bTagSF_CSVshape_weight_CFErr1Up,"bTagSF_CSVshape_weight_CFErr1Up/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr1Down",&_bTagSF_CSVshape_weight_CFErr1Down,"bTagSF_CSVshape_weight_CFErr1Down/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr2Up",&_bTagSF_CSVshape_weight_CFErr2Up,"bTagSF_CSVshape_weight_CFErr2Up/F");
    tree_new->Branch("bTagSF_CSVshape_weight_CFErr2Down",&_bTagSF_CSVshape_weight_CFErr2Down,"bTagSF_CSVshape_weight_CFErr2Down/F");
    
    tree_new->Branch("recoPFJet_hadronFlavour",&_recoPFJet_hadronFlavour);

    tree_new->Branch("genpart_TauGenDetailedDecayMode",&_genpart_TauGenDetailedDecayMode);
    
    
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

    _recoPFJet_hadronFlavour.clear();
      
      _genpart_TauGenDetailedDecayMode.clear();
      
      tree->GetEntry(i);
      
      tree_new->Fill();
      
    }
    
    f_new->cd();
    
    tree_new->Write();
    
  }



  f_new->Close();


  return;

}
     
    


void test(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_2lOS_CR");

  add_dummy_branch("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root",
		   "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_2lSS.root",
		   treename);
 

}
