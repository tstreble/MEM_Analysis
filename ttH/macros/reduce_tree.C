#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>



void reduce(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root";
  TString fileout="test_ttZ.root";


    TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }



  f_new = TFile::Open(fileout,"RECREATE");
  
  TChain * tree = new TChain("T");
  tree->Add(filein);
    
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  TTree* tree_new=tree->GetTree()->CloneTree(0);

    
  for(int i=0;i<2395;i++){
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;
    
    tree->GetEntry(i);

    tree_new->Fill();

  }
    
    
    f_new->cd();
    
    tree_new->Write();

  f_new->Close();


  return;


}
