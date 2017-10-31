#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>


using namespace std;



void add_MEM_syst(TString filein, TString fileout, TString treename){
  
  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");
      
  TChain * tree = new TChain(treename);
  tree->Add(filein);
  
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;
  
  TTree* tree_new=tree->GetTree()->CloneTree(0);
  
  //New branches
  float _StdErr_ttH;
  float _StdErr_ttZ;
  float _StdErr_ttZ_Zll;
  float _StdErr_ttbar_DL_fakelep_tlep;
  float _StdErr_ttbar_DL_fakelep_ttau;
    
  
  tree_new->Branch("StdErr_ttH",&_StdErr_ttH,"StdErr_ttH/F");
  tree_new->Branch("StdErr_ttZ",&_StdErr_ttZ,"StdErr_ttZ/F");
  tree_new->Branch("StdErr_ttZ_Zll",&_StdErr_ttZ_Zll,"StdErr_ttZ_Zll/F");
  tree_new->Branch("StdErr_ttbar_DL_fakelep_tlep",&_StdErr_ttbar_DL_fakelep_tlep,"StdErr_ttbar_DL_fakelep_tlep/F");
  tree_new->Branch("StdErr_ttbar_DL_fakelep_ttau",&_StdErr_ttbar_DL_fakelep_ttau,"StdErr_ttbar_DL_fakelep_ttau/F");
  
  
  //Old branches
  vector<int>* _include_perm_ttH;
  vector<int>* _include_perm_ttZ;
  vector<int>* _include_perm_ttZ_Zll;
  vector<int>* _include_perm_ttbar_DL_fakelep_tlep;
  vector<int>* _include_perm_ttbar_DL_fakelep_ttau;
  
  vector<float>* _StdErr_perm_ttH;
  vector<float>* _StdErr_perm_ttZ;
  vector<float>* _StdErr_perm_ttZ_Zll;
  vector<float>* _StdErr_perm_ttbar_DL_fakelep_tlep;
  vector<float>* _StdErr_perm_ttbar_DL_fakelep_ttau;
  
  tree->SetBranchAddress("include_perm_ttH",&_include_perm_ttH);
  tree->SetBranchAddress("include_perm_ttZ",&_include_perm_ttZ);
  tree->SetBranchAddress("include_perm_ttZ_Zll",&_include_perm_ttZ_Zll);
  tree->SetBranchAddress("include_perm_ttbar_DL_fakelep_tlep",&_include_perm_ttbar_DL_fakelep_tlep);
  tree->SetBranchAddress("include_perm_ttbar_DL_fakelep_ttau",&_include_perm_ttbar_DL_fakelep_ttau);
  
  tree->SetBranchAddress("StdErr_perm_ttH",&_StdErr_perm_ttH);
  tree->SetBranchAddress("StdErr_perm_ttZ",&_StdErr_perm_ttZ);
  tree->SetBranchAddress("StdErr_perm_ttZ_Zll",&_StdErr_perm_ttZ_Zll);
  tree->SetBranchAddress("StdErr_perm_ttbar_DL_fakelep_tlep",&_StdErr_perm_ttbar_DL_fakelep_tlep);
  tree->SetBranchAddress("StdErr_perm_ttbar_DL_fakelep_ttau",&_StdErr_perm_ttbar_DL_fakelep_ttau);
  
  
  
  for(int i=0;i<nentries;i++){
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _include_perm_ttH = 0;
    _include_perm_ttZ = 0;
    _include_perm_ttZ_Zll = 0;
    _include_perm_ttbar_DL_fakelep_tlep = 0;
    _include_perm_ttbar_DL_fakelep_ttau = 0;
    
    _StdErr_perm_ttH = 0;
    _StdErr_perm_ttZ = 0;
    _StdErr_perm_ttZ_Zll = 0;
    _StdErr_perm_ttbar_DL_fakelep_tlep = 0;
    _StdErr_perm_ttbar_DL_fakelep_ttau = 0;
    
    _StdErr_ttH = 0;
    _StdErr_ttZ = 0;
    _StdErr_ttZ_Zll = 0;
    _StdErr_ttbar_DL_fakelep_tlep = 0;
    _StdErr_ttbar_DL_fakelep_ttau = 0;
    
    tree->GetEntry(i);
    
    double var_ttH = 0;
    double var_ttZ = 0;
    double var_ttZ_Zll = 0;
    double var_ttbar_DL_fakelep_tlep = 0;
    double var_ttbar_DL_fakelep_ttau = 0;
    
    for(unsigned int i_perm=0; i_perm<(*_include_perm_ttH).size();i_perm++){
      if((*_include_perm_ttH)[i_perm])
	var_ttH += pow((*_StdErr_perm_ttH)[i_perm],2);
      if((*_include_perm_ttZ)[i_perm])
	var_ttZ += pow((*_StdErr_perm_ttZ)[i_perm],2);
      if((*_include_perm_ttZ_Zll)[i_perm])
	var_ttZ_Zll += pow((*_StdErr_perm_ttZ_Zll)[i_perm],2);
      if((*_include_perm_ttbar_DL_fakelep_tlep)[i_perm])
	var_ttbar_DL_fakelep_tlep += pow((*_StdErr_perm_ttbar_DL_fakelep_tlep)[i_perm],2);
      if((*_include_perm_ttbar_DL_fakelep_ttau)[i_perm])
	var_ttbar_DL_fakelep_ttau += pow((*_StdErr_perm_ttbar_DL_fakelep_ttau)[i_perm],2);

    }
    
    _StdErr_ttH = sqrt(var_ttH);
    _StdErr_ttZ = sqrt(var_ttZ);
    _StdErr_ttZ_Zll = sqrt(var_ttZ_Zll);
    _StdErr_ttbar_DL_fakelep_tlep = sqrt(var_ttbar_DL_fakelep_tlep);
    _StdErr_ttbar_DL_fakelep_ttau = sqrt(var_ttbar_DL_fakelep_ttau);
    
    
    tree_new->Fill();
    
  }
  
  f_new->cd();
  
  tree_new->Write();
  

  f_new->Close();


  return;

}
     


    
void test(){

  TString filename_in = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root";
  TString filename_out = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205_MEMsyst.root";
  TString treename = "T";

  add_MEM_syst(filename_in,filename_out,treename);

  filename_in = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205.root";
  filename_out = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205_MEMsyst.root";

  add_MEM_syst(filename_in,filename_out,treename);


}
