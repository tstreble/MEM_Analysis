#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>

using namespace std;


void test(){

  //TChain* tree=new TChain("HTauTauTree/HTauTauTree");
  TString dir_in="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_Moriond17_2/DoubleMuon/DoubleMu_2016B_04_02_17/170204_210418/";


  //TChain* tree=new TChain("HTauTauTree/HTauTauTree");

  for(unsigned int i=1;i<8257;i++){

    int i_dir = i/1000;
    TString file = dir_in + Form("000%i/",i_dir) + Form("HTauTauAnalysis_%i.root",i);
    cout<<file<<endl;
    TChain* tree=new TChain("HTauTauTree/HTauTauTree");
    tree->Add(file);
    cout<<tree->GetEntries()<<endl;
    int n=tree->GetEntries("RunNumber==274387 && lumi==343 && EventNumber==582971095");
    cout<<n<<endl;
    if(n>0) return;
    delete tree;

  }
    


}
