#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include "PUReweight.cc"


using namespace std;





void create_PUtree(TString filein, TString fileout, TString treename){

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain(treename);
  //for(unsigned int i=0;i<filein.size();i++)
  //  tree->Add(filein[i]);
  tree->Add(filein);

  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  TTree* tree_new=new TTree(treename,treename);

  //New branches
  unsigned long long _EventNumber = -1;
  int _RunNumber = -1, _lumi = -1;

  float _npu;
  float _MC_weight;
  float _MC_weight_tHq_SM_457;
  float _PU_weight_ICHEP;
  float _PU_weight_2016;
  float _PU_weight_MCSummer2016;


  tree_new->Branch("EventNumber",&_EventNumber,"EventNumber/l");
  tree_new->Branch("RunNumber",&_RunNumber,"RunNumber/I");
  tree_new->Branch("lumi",&_lumi,"lumi/I");

  tree_new->Branch("npu",&_npu,"npu/F");
  tree_new->Branch("MC_weight",&_MC_weight,"MC_weight/F");
  tree_new->Branch("MC_weight_tHq_SM_457",&_MC_weight_tHq_SM_457,"MC_weight_tHq_SM_457/F");
  tree_new->Branch("PU_weight_ICHEP",&_PU_weight_ICHEP,"PU_weight_ICHEP/F");
  tree_new->Branch("PU_weight_2016",&_PU_weight_2016,"PU_weight_2016/F");
  tree_new->Branch("PU_weight_MCSummer2016",&_PU_weight_MCSummer2016,"PU_weight_MCSummer2016/F");

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("RunNumber",&_RunNumber);
  tree->SetBranchAddress("lumi",&_lumi);
  tree->SetBranchAddress("npu",&_npu);
  tree->SetBranchAddress("MC_weight",&_MC_weight);
  tree->SetBranchAddress("MC_weight_tHq_SM_457",&_MC_weight_tHq_SM_457);
  

  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _npu = 0;
      _MC_weight = 0;
      _MC_weight_tHq_SM_457 = 0;
      _PU_weight_ICHEP = 0;
      _PU_weight_2016 = 0;      
      _PU_weight_MCSummer2016 = 0;      
      
      tree->GetEntry(i);

      _PU_weight_ICHEP = puw2016_nTrueInt_13fb(abs(_npu));
      _PU_weight_2016 = puw2016_nTrueInt_36fb(abs(_npu));
      _PU_weight_MCSummer2016 = puw2016_MCSummer16_nTrueInt_36fb(abs(_npu));

      tree_new->Fill();

  }


  f_new->cd();
    
  tree_new->Write();

  f_new->Close();


  return;

}






void add_PUweight(TString filein, TString fileout, vector<TString> treename){


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
    
    float _npu;
    tree->SetBranchAddress("npu",&_npu);

    
    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _PU_weight_MCSummer2016;
    tree_new->Branch("PU_weight_MCSummer2016",&_PU_weight_MCSummer2016,"PU_weight_MCSummer2016/F");

    //float _PU_weight_ICHEP;
    //tree_new->Branch("PU_weight_ICHEP",&_PU_weight_ICHEP,"PU_weight_ICHEP/F");


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _PU_weight_MCSummer2016 = 0;
      //_PU_weight_ICHEP = 0;

      _npu = 0;

      tree->GetEntry(i);

      _PU_weight_MCSummer2016 = puw2016_MCSummer16_nTrueInt_36fb(abs(_npu));
      //_PU_weight_ICHEP = puw2016_nTrueInt_13fb(abs(_npu));

      tree_new->Fill();

    }
    
    
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}
      




/*void test(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/EWK/ntuple_WZ_*";

  TString filout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/EWK/PU_ntuple_WZ.root";
  
  TString treename = "HTauTauTree";

  create_PUtree(filein,filout,treename);


  }*/





void test2(){

  /*vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_2lSS");
  //treename.push_back("HTauTauTree_2lOS_CR");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");*/

  /*TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_160110.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);*/

  /*TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root";
  add_PUweight(filein,fileout,treename);*/

  /*TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_tZq_split_JECup.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_tZq_split_JECup_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_tZq_split_JECdown.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_tZq_split_JECdown_PU.root";
  add_PUweight(filein,fileout,treename);*/

  /*filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_tZq_split_TESup.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_tZq_split_TESup_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_tZq_split_TESdown.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_tZq_split_TESdown_PU.root";
  add_PUweight(filein,fileout,treename);*/

  /*TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_PU.root";
  add_PUweight(filein,fileout,treename);


  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_PU.root";
  add_PUweight(filein,fileout,treename);*/

  vector<TString> treename;
  treename.push_back("T");  

  /*vector<TString> syst;
  syst.push_back("JECup");
  syst.push_back("JECdown");
  syst.push_back("TESup");
  syst.push_back("TESdown");

  for(unsigned int i=0;i<4;i++){
    TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst[i]+"/Rares/tZq_split_*16*.root";
    TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst[i]+"/Rares/tZq_split_"+syst[i]+"_2lSS_MEM_PU.root";
    add_PUweight(filein,fileout,treename);
  }*/

  TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttG_split_2lSS_lepMVA_CR_MEM_1*.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttG_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);
  
  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWW_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWW_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

 filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/tZq_split_2lSS_lepMVA_CR_MEM_1*.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/tZq_split_2lSS_lepMVA_CR_MEM_PU.root";
  add_PUweight(filein,fileout,treename);

}
