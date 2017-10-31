#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>

//#include "add_event_weight.C"


using namespace std;



void add_lepSF_v3(TString filein, TString fileout, vector<TString> treename, bool isMC){


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
 

    tree->SetBranchAddress("category",&_category);
    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree->SetBranchAddress("recolep_sel_ismvasel",&_recolep_sel_ismvasel);


    TTree* tree_new=tree->GetTree()->CloneTree(0);
 

    float _leptonSF_ttH_weight_v3;

    tree_new->Branch("leptonSF_ttH_weight_v3",&_leptonSF_ttH_weight_v3,"leptonSF_ttH_weight_v3/F");

 

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _category = 0;

      _recolep_sel_pdg = 0;
      _recolep_sel_ismvasel = 0;
      _recolep_sel_conept = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;

      _leptonSF_ttH_weight_v3 = 0;

      
      tree->GetEntry(i);


      _leptonSF_ttH_weight_v3 = 1;


      if(_category==20 || _category==50){	

	if((*_recolep_sel_ismvasel)[0])
	  _leptonSF_ttH_weight_v3 *= leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3); //No tight-charge criteria for 1l2tau	      
	else
	  _leptonSF_ttH_weight_v3 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3);	
	

      }


      else if(_category==11 || _category==41){

	for(unsigned int i_lep=0;i_lep<2;i_lep++){
	    
	  if((*_recolep_sel_ismvasel)[i_lep])
	    _leptonSF_ttH_weight_v3 *= leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],2);
	  else
	    _leptonSF_ttH_weight_v3 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],2);	
	  
	}
	
      }


      else if(_category==16 || _category==46){

	for(unsigned int i_lep=0;i_lep<3;i_lep++){
	  
	  if((*_recolep_sel_ismvasel)[i_lep])
	    _leptonSF_ttH_weight_v3 *= leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],3);
	  else
	    _leptonSF_ttH_weight_v3 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[i_lep],(*_recolep_sel_pt)[i_lep],(*_recolep_sel_eta)[i_lep],3);	
	    
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



