#include <fstream>
#include <iostream>
#include <sstream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TLatex.h>
#include "Helpers.C"


void compar(){

  TString log_file = "data_mu.txt";
  std::ifstream infile(log_file);

  TChain * tree = new TChain("HTauTauTree_1l_2tau");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_Single*BDT_1l2tau.root");
  int nEntries = tree->GetEntries();

  int _RunNumber;
  int _lumi;
  ULong64_t _EventNumber;
  int _category;
  int _NBadMu;
  bool _isTrig_1l;

  tree->SetBranchAddress("RunNumber",&_RunNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("category",&_category);
  tree->SetBranchAddress("NBadMu",&_NBadMu);
  tree->SetBranchAddress("isTrig_1l",&_isTrig_1l);


  int iEntry=0;
  string line;
  while(getline(infile,line)){

    vector<long> var;
    for(unsigned int j=0;j<3;j++)
      var.push_back(-1);

    //size_t pos1= line.find(":");
    size_t pos1= 0;
    size_t pos2= line.find(":",pos1+1);
    size_t pos3= line.find(":",pos2+1);

    //std::istringstream iss1(line.substr(pos1+1,pos2-pos1));
    std::istringstream iss1(line.substr(pos1,pos2-pos1));
    iss1 >> var[0];
    std::istringstream iss2(line.substr(pos2+1,pos3-pos2));
    iss2 >> var[1];
    std::istringstream iss3(line.substr(pos3+1,line.length()-pos3));
    iss3 >> var[2];


    tree->GetEntry(iEntry);
    

    bool full_loop = false;
    
    //while(!(_RunNumber==long(var[0]) && _lumi==long(var[1]) && (_EventNumber==long(var[2]) || var[2]<=0 ) ) ){
    while(!(_RunNumber==long(var[0]) && _lumi==long(var[1]) ) ){

      //cout<<"LLR "<<_RunNumber<<":"<<_lumi<<":"<<_EventNumber<<endl;

      iEntry++;
      if(iEntry>nEntries){
	if(full_loop){
	  cout<<"ND "<<var[0]<<":"<<var[1]<<":"<<var[2]<<endl;
	  cout<<"Problem"<<endl;
	  return;
	}
	iEntry = 0;
	full_loop = true;
      }
      tree->GetEntry(iEntry);
    }

    if(_EventNumber!=long(var[2])){
      cout<<"ND "<<var[0]<<":"<<var[1]<<":"<<var[2]<<endl;
      cout<<"Found same run lumi but LLR EventNumber="<<_EventNumber<<endl;
    }




  }


}






void compar2(){

  TString log_file = "data_mu.txt";
  std::ifstream infile(log_file);

  TChain * tree = new TChain("HTauTauTree_1l_2tau");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_Single*massveto.root");
  int nEntries = tree->GetEntries();

  int _RunNumber;
  int _lumi;
  ULong64_t _EventNumber;
  int _category;
  int _NBadMu;
  bool _isTrig_1l_v2;
  vector<float>* _recotauh_sel_pt;
  vector<float>* _recolep_sel_eta;
  vector<float>* _recolep_sel_pt;


  tree->SetBranchAddress("RunNumber",&_RunNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("category",&_category);
  tree->SetBranchAddress("NBadMu",&_NBadMu);
  tree->SetBranchAddress("isTrig_1l_v2",&_isTrig_1l_v2);
  tree->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
  tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
  tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);


  string line;

  for(unsigned int i=0;i<nEntries;i++){

    _RunNumber = 0;
    _lumi = 0;
    _EventNumber = 0;
    _category = 0;
    _NBadMu = 0;
    _isTrig_1l_v2 = 0;
    _recotauh_sel_pt = 0;
    _recolep_sel_eta = 0;
    _recolep_sel_pt = 0;


    tree->GetEntry(i);

    if(!(_isTrig_1l_v2 && (*_recotauh_sel_pt)[0]>30 && fabs((*_recolep_sel_eta)[0])<2.1 && _NBadMu==0)) continue;


    bool found_event=false;
    while(getline(infile,line) && !found_event){
      
      vector<long> var;
      for(unsigned int j=0;j<3;j++)
	var.push_back(-1);

    size_t pos1= 0;
    size_t pos2= line.find(":",pos1+1);
    size_t pos3= line.find(":",pos2+1);

    //std::istringstream iss1(line.substr(pos1+1,pos2-pos1));
    std::istringstream iss1(line.substr(pos1,pos2-pos1));
    iss1 >> var[0];
    std::istringstream iss2(line.substr(pos2+1,pos3-pos2));
    iss2 >> var[1];
    std::istringstream iss3(line.substr(pos3+1,line.length()-pos3));
    iss3 >> var[2];
      
  

      if(_RunNumber==long(var[0]) && _lumi==long(var[1]))
	found_event=true;

    }

    if(!found_event){
      cout<<_RunNumber<<":"<<_lumi<<":"<<_EventNumber<<endl;
    }

    infile.clear();
    infile.seekg(0, ios::beg);

  }


}





