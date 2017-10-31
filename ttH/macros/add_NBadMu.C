#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <iostream>

void add_NBadMu_fromSecondary(TString file_in, TString file_out, TString treename, TString filein_secondary, TString treename_secondary){

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
  int _NBadMu;
  tree2->SetBranchAddress("EventNumber",&_EventNumber2);
  tree2->SetBranchAddress("NBadMu",&_NBadMu);

  TTree* tree_new=tree1->GetTree()->CloneTree(0);
  //New branches
  tree_new->Branch("NBadMu",&_NBadMu,"NBadMu/I");
  
  int iEntry2 = 0;  

  for(int i=0;i<nentries1;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _EventNumber1 = 0;
      _EventNumber2 = 0;
      _NBadMu = 0;

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




void test_NBadMu(){

  TString file_MEM="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lOS_CR_MEM_160205.root";
  TString file_out="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lOS_CR_MEM_NBadMu.root";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root";

  add_NBadMu_fromSecondary(file_MEM,file_out,"T",file,"HTauTauTree_2lOS_CR");


}
