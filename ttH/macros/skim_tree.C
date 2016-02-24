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

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;



void skim(){

  TString dir_in;
  TString dir_out;
  TString file;    

  vector<TString> list;

  file="ntuple_ttH_dRveto_gen_iso70_1kevt.root";
  dir_in="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  dir_out="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  list.push_back(dir_in+"ntuple_ttH_dRveto_gen_iso70.root");

  TChain * tree = new TChain("HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  Long64_t nentries = 1000;

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");

  cout<<"tree->GetEntries()="<<tree->GetEntries()<<endl;

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  for (int i=0;i<nentries;i++) {
    tree->GetEntry(i);
    tree_new->Fill();
  }

  tree_new->Write();
  f_new->Close();


  return;    


}
