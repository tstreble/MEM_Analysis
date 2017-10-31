#include "trigger_filter_2016H.C"


void test(){


  vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_2lOS_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");

  vector<TString> dataset;
  //dataset.push_back("MuonEG");
  dataset.push_back("SingleMu");
  dataset.push_back("SingleEle");

  vector<TString> era;
  era.push_back("2016Hv2");
  //era.push_back("2016Hv3");
  
  for(unsigned int i=0; i<dataset.size();i++){
    for(unsigned int j=0; j<era.size();j++){
      
      TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_"+era[j]+"_split.root";
      TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_"+era[j]+"_split_newtrig.root";
      add_trigger_filter_2016H(filein,fileout,treename,false);

    }
  }



}






void add_trigger_filter_fromSecondary(TString file_in, TString file_out, TString treename, TString filein_secondary, TString treename_secondary){

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
  bool _isTrig_v2;
  tree2->SetBranchAddress("EventNumber",&_EventNumber2);
  tree2->SetBranchAddress("isTrig_v2",&_isTrig_v2);

  TTree* tree_new=tree1->GetTree()->CloneTree(0);
  //New branches
  tree_new->Branch("isTrig_v2",&_isTrig_v2,"isTrig_v2/O");
  
  int iEntry2 = 0;  

  for(int i=0;i<nentries1;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _EventNumber1 = 0;
      _EventNumber2 = 0;
      _isTrig_v2 = 0;

      tree1->GetEntry(i);
      tree2->GetEntry(iEntry2);

      /*if(_EventNumber1!=_EventNumber2){
	cout<<"Problem"<<endl;
	return;
	}*/

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
	tree2->GetEntry(iEntry2);
      }


       
      tree_new->Fill();
      
    }

  f_new->cd();
  
  tree_new->Write();

  f_new->Close();


  return;
    


}




void test2(){

  /*TString filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lSS_MEM_160103.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lSS_MEM_newtrig.root";
  TString treename="T";
  
  TString filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv2_split_newtrig.root";
  TString treename_secondary="HTauTauTree_2lSS";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lSS_lepMVA_CR_MEM_161224.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lSS_lepMVA_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lSS_lepMVA_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lOS_CR_MEM_161224.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lOS_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lOS_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);



  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv3_split_2lSS_lepMVA_CR_MEM_161225.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv3_split_2lSS_lepMVA_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv3_split_newtrig.root";
  treename_secondary="HTauTauTree_2lSS_lepMVA_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv3_split_2lOS_CR_MEM_161225.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/MuonEG_2016Hv3_split_2lOS_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv3_split_newtrig.root";
  treename_secondary="HTauTauTree_2lOS_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);*/


  TString filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lSS_MEM_160103.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lSS_MEM_newtrig.root";
  TString treename="T";
  
  TString filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_newtrig.root";
  TString treename_secondary="HTauTauTree_2lSS";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lSS_lepMVA_CR_MEM_161224.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lSS_lepMVA_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lSS_lepMVA_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lOS_CR_MEM_161224.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lOS_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lOS_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);



  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv3_split_2lSS_lepMVA_CR_MEM_161226.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv3_split_2lSS_lepMVA_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv3_split_newtrig.root";
  treename_secondary="HTauTauTree_2lSS_lepMVA_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv3_split_2lOS_CR_MEM_161226.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleEle_2016Hv3_split_2lOS_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv3_split_newtrig.root";
  treename_secondary="HTauTauTree_2lOS_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);
  

  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lSS_MEM_160103.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lSS_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lSS";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lSS_lepMVA_CR_MEM_161225.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lSS_lepMVA_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lSS_lepMVA_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lOS_CR_MEM_161225.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lOS_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_newtrig.root";
  treename_secondary="HTauTauTree_2lOS_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);



   filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv3_split_2lSS_lepMVA_CR_MEM_161226.root";
   fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv3_split_2lSS_lepMVA_CR_MEM_newtrig.root";
   treename="T";
  
   filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv3_split_newtrig.root";
   treename_secondary="HTauTauTree_2lSS_lepMVA_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);


  filein1 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv3_split_2lOS_CR_MEM_161226.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/SingleMu_2016Hv3_split_2lOS_CR_MEM_newtrig.root";
  treename="T";
  
  filein_secondary="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv3_split_newtrig.root";
  treename_secondary="HTauTauTree_2lOS_CR";

  add_trigger_filter_fromSecondary(filein1,fileout,treename,filein_secondary,treename_secondary);

  

}
