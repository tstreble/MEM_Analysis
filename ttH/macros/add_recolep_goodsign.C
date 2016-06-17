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


using namespace std;


void convert_tree(TString sample){


  TString dir_in;
  TString dir_out;
  TString file;    

  vector<TString> list;

  if(sample=="TTJets"){
    file="ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    dir_out=dir_in;
    list.push_back(dir_in+"ntuple_TTJets_dRveto_gen_iso70_skimmed.root");
  }

  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  Long64_t nentries = tree->GetEntries();


  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);

      
  //New branches
  vector<int> _recolep_goodsign;
  tree_new->Branch("recolep_goodsign",&_recolep_goodsign);


  //Old branches used
  vector<float> *_recolep_e;
  vector<float> *_recolep_px;
  vector<float> *_recolep_py;
  vector<float> *_recolep_pz;
  vector<int> *_recolep_ID;

  vector<float> *_genlep_e;
  vector<float> *_genlep_px;
  vector<float> *_genlep_py;
  vector<float> *_genlep_pz;
  vector<int> *_genlep_pdg;

  tree->SetBranchAddress("recolep_e",&_recolep_e);
  tree->SetBranchAddress("recolep_px",&_recolep_px);
  tree->SetBranchAddress("recolep_py",&_recolep_py);
  tree->SetBranchAddress("recolep_pz",&_recolep_pz);
  tree->SetBranchAddress("recolep_ID",&_recolep_ID);

  tree->SetBranchAddress("genlep_e",&_genlep_e);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);


  int skip_entries = 0;
  cout<<"nentries="<<nentries<<endl;

  for (int i=skip_entries;i<skip_entries+nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _recolep_goodsign.clear();

    _recolep_e = 0;
    _recolep_px = 0;
    _recolep_py = 0;
    _recolep_pz = 0;
    _recolep_ID = 0;

    _genlep_e = 0;
    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_pdg = 0;

    tree->GetEntry(i);

    for(unsigned int i_recolep=0; i_recolep<(*_recolep_e).size(); i_recolep++){

      TLorentzVector recolep( (*_recolep_px)[i_recolep], (*_recolep_py)[i_recolep], (*_recolep_pz)[i_recolep], (*_recolep_e)[i_recolep] );

      float dRmin = -1;
      int i_closest_genlep = -1;

      for(unsigned int i_genlep=0; i_genlep<(*_genlep_e).size(); i_genlep++){

	if(abs((*_genlep_pdg)[i_genlep])!=abs((*_recolep_ID)[i_recolep]))
	  continue;

	TLorentzVector genlep( (*_genlep_px)[i_genlep], (*_genlep_py)[i_genlep], (*_genlep_pz)[i_genlep], (*_genlep_e)[i_genlep] );
	float dR = genlep.DeltaR(recolep);

	if(dRmin<0 || dR<dRmin){
	  dRmin = dR;
	  i_closest_genlep = i_genlep;
	}

      }

      int goodsign = 0;
      
      if(i_closest_genlep>=0 && dRmin<0.1){
	if( (*_genlep_pdg)[i_closest_genlep] * (*_recolep_ID)[i_recolep]>0)
	  goodsign = 1;
	else
	  goodsign = -1;
      }

      _recolep_goodsign.push_back(goodsign);

    }

    
    tree_new->Fill();

  }


  tree_new->Write();
  f_new->Close();


  return;

}
