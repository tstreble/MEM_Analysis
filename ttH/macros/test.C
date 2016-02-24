#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>

using namespace std;

void test(){


  TChain *treeA = new TChain("HTauTauTree/HTauTauTree");
  treeA->Add("/data_CMS/cms/strebler/ttH_Samples/Htautau_framework_files/MiniAODv2_prod_12_2015/files/HTauTauAnalysis_1.root");

  cout<<"treeA->GetEntries()="<<treeA->GetEntries()<<endl;


  TFile* f= TFile::Open("/data_CMS/cms/strebler/ttH_Samples/Htautau_framework_files/ttH_HToTauTau_pfMET_prod_07072015/HTauTauAnalysis_1.root");
  cout<<"f->GetVersion()="<<f->GetVersion()<<endl;

}
