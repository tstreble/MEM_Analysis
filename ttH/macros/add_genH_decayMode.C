#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;



void add_genH_decayMode(TString filename_in1, TString filename_in2, TString fileout, vector<TString> treename){

  TChain* HTauTauTree=new TChain("HTauTauTree_2lSS");
  HTauTauTree->Add(filename_in2);

  Long64_t nentries2 = HTauTauTree->GetEntries();
  cout<<"nentries="<<HTauTauTree->GetEntries()<<endl;

  //Old branches
  unsigned long long _EventNumber2 = -1;

  vector<int>* _genH_decayMode;
  int _n_genW = -1;
  int _n_genZ = -1;
  float _MC_weight = 0;

  HTauTauTree->SetBranchAddress("EventNumber",&_EventNumber2);
  HTauTauTree->SetBranchAddress("genH_decayMode",&_genH_decayMode);
  HTauTauTree->SetBranchAddress("n_genW",&_n_genW);
  HTauTauTree->SetBranchAddress("n_genZ",&_n_genZ);
  HTauTauTree->SetBranchAddress("MC_weight",&_MC_weight);


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filename_in1);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;

    //Old branches
    unsigned long long _EventNumber1 = -1;

    tree->SetBranchAddress("EventNumber",&_EventNumber1);

    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    vector<int> _genH_decayMode_new;
    
    tree_new->Branch("genH_decayMode",&_genH_decayMode);
    tree_new->Branch("n_genW",&_n_genW,"n_genW/I");
    tree_new->Branch("n_genZ",&_n_genZ,"n_genZ/I");
    tree_new->Branch("MC_weight2",&_MC_weight,"MC_weight2/F");

    int iEntry2 = 0;

    for(unsigned int iEntry1=0;iEntry1<nentries;iEntry1++){

      if(iEntry1%100==0)
	cout<<"i="<<iEntry1<<endl;

      _EventNumber1 = 0;

      tree->GetEntry(iEntry1);

      _EventNumber2 = 0;
      _genH_decayMode = 0;
      _n_genW = 0;
      _n_genZ = 0;
      _MC_weight = 0;
      
      HTauTauTree->GetEntry(iEntry2);
      
      bool full_loop = false;

      while(_EventNumber1!=_EventNumber2){
	iEntry2++;
	if(iEntry2>nentries2){
	  /*cout<<"EventNumber1="<<_EventNumber1<<endl;
	  cout<<"EventNumber2="<<_EventNumber2<<endl;
	  cout<<"Problem"<<endl;
	  return;*/
	  if(full_loop){
	    cout<<"EventNumber1="<<_EventNumber1<<endl;
	    cout<<"EventNumber2="<<_EventNumber2<<endl;
	    cout<<"Problem"<<endl;
	    return;
	  }
	  iEntry2 = 0;
	  full_loop = true;
	}
	HTauTauTree->GetEntry(iEntry2);
      }
	
      _genH_decayMode_new.clear();

      for(unsigned int i_H=0;i_H<(*_genH_decayMode).size();i_H++)
	_genH_decayMode_new.push_back((*_genH_decayMode)[i_H]);

      
      tree_new->Fill();

    }

  
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}
      




void add_MC_weight2(TString filename_in1, TString filename_in2, TString fileout, vector<TString> treename){

  TChain* HTauTauTree=new TChain("HTauTauTree_2lSS");
  HTauTauTree->Add(filename_in2);

  Long64_t nentries2 = HTauTauTree->GetEntries();
  cout<<"nentries="<<HTauTauTree->GetEntries()<<endl;

  //Old branches
  unsigned long long _EventNumber2 = -1;

  float _MC_weight = 0;

  HTauTauTree->SetBranchAddress("EventNumber",&_EventNumber2);
  HTauTauTree->SetBranchAddress("MC_weight",&_MC_weight);


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filename_in1);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;

    //Old branches
    unsigned long long _EventNumber1 = -1;

    tree->SetBranchAddress("EventNumber",&_EventNumber1);

    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    tree_new->Branch("MC_weight2",&_MC_weight,"MC_weight2/F");

    int iEntry2 = 0;

    for(unsigned int iEntry1=0;iEntry1<nentries;iEntry1++){

      if(iEntry1%100==0)
	cout<<"i="<<iEntry1<<endl;

      _EventNumber1 = 0;

      tree->GetEntry(iEntry1);

      _EventNumber2 = 0;
      _MC_weight = 0;
      
      HTauTauTree->GetEntry(iEntry2);
      
      bool full_loop = false;

      while(_EventNumber1!=_EventNumber2){
	iEntry2++;
	if(iEntry2>nentries2){
	  /*cout<<"EventNumber1="<<_EventNumber1<<endl;
	  cout<<"EventNumber2="<<_EventNumber2<<endl;
	  cout<<"Problem"<<endl;
	  return;*/
	  if(full_loop){
	    cout<<"EventNumber1="<<_EventNumber1<<endl;
	    cout<<"EventNumber2="<<_EventNumber2<<endl;
	    cout<<"Problem"<<endl;
	    return;
	  }
	  iEntry2 = 0;
	  full_loop = true;
	}
	HTauTauTree->GetEntry(iEntry2);
      }
	

      
      tree_new->Fill();

    }

  
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}
      





void test(){

  TString filename_in2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown.root";
  TString filename_in1 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttH/ttH_Hnonbb_split_TESdown_2lSS_MEM_PU.root";			   
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttH/ttH_Hnonbb_split_TESdown_2lSS_MEM_PU_genH.root";

  vector<TString> treename;
  treename.push_back("T");

  //add_genH_decayMode(filename_in1,filename_in2,fileout,treename);


  /*filename_in2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown.root";
  filename_in1 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttZ_split_TESdown_2lSS_MEM_PU.root";			   
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttZ_split_TESdown_2lSS_MEM_PU_MCweight.root";
  add_MC_weight2(filename_in1,filename_in2,fileout,treename);


  filename_in2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_split_TESdown.root";
  filename_in1 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttW_split_TESdown_2lSS_MEM_PU.root";			   
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttW_split_TESdown_2lSS_MEM_PU_MCweight.root";
  add_MC_weight2(filename_in1,filename_in2,fileout,treename);*/


  filename_in2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_ext_split_TESdown.root";
  filename_in1 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttW_ext_split_TESdown_2lSS_MEM_PU.root";			   
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttW_ext_split_TESdown_2lSS_MEM_PU_MCweight.root";
  add_MC_weight2(filename_in1,filename_in2,fileout,treename);


  /*filename_in2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_split_TESdown.root";
  filename_in1 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/EWK/WZ_split_TESdown_2lSS_MEM_PU.root";			   
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/EWK/WZ_split_TESdown_2lSS_MEM_PU_MCweight.root";
  add_MC_weight2(filename_in1,filename_in2,fileout,treename);*/


}
