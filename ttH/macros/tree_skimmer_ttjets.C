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


#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;




void skim_tree(TString sample){

  TString file_in;
  TString file_out;  
  TString dir;

  if(sample=="TTJets_1"){
    file_in="ntuple_TTJets_dRveto_gen_1_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_1_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_2"){
    file_in="ntuple_TTJets_dRveto_gen_2_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_2_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_3"){
    file_in="ntuple_TTJets_dRveto_gen_3_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_3_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_4"){
    file_in="ntuple_TTJets_dRveto_gen_4_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_4_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_5"){
    file_in="ntuple_TTJets_dRveto_gen_5_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_5_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_6"){
    file_in="ntuple_TTJets_dRveto_gen_6_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_6_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_7"){
    file_in="ntuple_TTJets_dRveto_gen_7_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_7_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_8"){
    file_in="ntuple_TTJets_dRveto_gen_8_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_8_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_9"){
    file_in="ntuple_TTJets_dRveto_gen_9_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_9_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_10"){
    file_in="ntuple_TTJets_dRveto_gen_10_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_10_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_11"){
    file_in="ntuple_TTJets_dRveto_gen_11_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_11_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_12"){
    file_in="ntuple_TTJets_dRveto_gen_12_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_12_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_13"){
    file_in="ntuple_TTJets_dRveto_gen_13_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_13_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_14"){
    file_in="ntuple_TTJets_dRveto_gen_14_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_14_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_15"){
    file_in="ntuple_TTJets_dRveto_gen_15_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_15_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_16"){
    file_in="ntuple_TTJets_dRveto_gen_16_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_16_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }
  else if(sample=="TTJets_17"){
    file_in="ntuple_TTJets_dRveto_gen_17_iso70.root";
    file_out="ntuple_TTJets_dRveto_gen_17_iso70_skimmed.root";
    dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
  }



  TChain * tree = new TChain("HTauTauTree");
  tree->Add(dir+file_in);

  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir+file_out);
  if(f_new!=0){
    cout<<dir+file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir+file_out,"RECREATE");



  //Old branches used
  int _n_recolep;
  int _n_recotauh;
  vector<int>* _recolep_charge;
  vector<int>* _recotauh_charge;
  int _n_recoPFJet30;
  vector<float>* _recoPFJet30_CSVsort_CSVscore;

  tree->SetBranchAddress("n_recolep",&_n_recolep);
  tree->SetBranchAddress("n_recotauh",&_n_recotauh);
  tree->SetBranchAddress("recolep_charge",&_recolep_charge);
  tree->SetBranchAddress("recotauh_charge",&_recotauh_charge);
  tree->SetBranchAddress("n_recoPFJet30",&_n_recoPFJet30);
  tree->SetBranchAddress("recoPFJet30_CSVsort_CSVscore",&_recoPFJet30_CSVsort_CSVscore);

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  cout<<"nentries="<<nentries<<endl;


  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _n_recolep = 0;
    _n_recotauh = 0;
    _recolep_charge = 0;
    _recotauh_charge = 0;
    _n_recoPFJet30 = 0;
    _recoPFJet30_CSVsort_CSVscore = 0;
    
    tree->GetEntry(i);

    if( !(
	  _n_recolep==2
	  && _n_recotauh>=1
	  && (*_recolep_charge)[0]*(*_recolep_charge)[1]>0
	  && (*_recolep_charge)[0]*(*_recotauh_charge)[0]<0
	  && _n_recoPFJet30>=3
	  && (*_recoPFJet30_CSVsort_CSVscore)[0]>0.814 && (*_recoPFJet30_CSVsort_CSVscore)[1]>0.423
	  ) )

      continue;

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}
