#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TH1F.h>
#include <iostream>

using namespace std;


vector<TString> triggerlist;
vector<TString> triggerlist_sample;
vector<TString> triggerlist_veto;
vector<TString> triggerlist_sample_3l;
vector<TString> triggerlist_veto_3l;


void print_triggers(){

  cout<<endl;
  cout<<"Vetoed triggers"<<endl;
  for(unsigned int j=0;j<triggerlist_veto.size();j++)	
    cout<<triggerlist_veto[j]<<endl;

  cout<<"Allowed triggers"<<endl;
  for(unsigned int j=0;j<triggerlist_sample.size();j++)	
    cout<<triggerlist_sample[j]<<endl;

  cout<<"Vetoed triggers 3l"<<endl;
  for(unsigned int j=0;j<triggerlist_veto_3l.size();j++)	
    cout<<triggerlist_veto_3l[j]<<endl;

  cout<<"Allowed triggers 3l"<<endl;
  for(unsigned int j=0;j<triggerlist_sample_3l.size();j++)	
    cout<<triggerlist_sample_3l[j]<<endl;

}



void produce_triggerlist(TString sample, bool isMC, TH1F* hCounter){

  triggerlist.clear();
  triggerlist_sample.clear();
  triggerlist_veto.clear();
  triggerlist_sample_3l.clear();
  triggerlist_veto_3l.clear();


  for(int itr=1;itr<=hCounter->GetNbinsX();itr++){
    TString binlabel = hCounter->GetXaxis()->GetBinLabel(itr);
    if(binlabel.BeginsWith("HLT"))triggerlist.push_back(hCounter->GetXaxis()->GetBinLabel(itr));
  }

  if(isMC){

    triggerlist_sample.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    triggerlist_sample.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    triggerlist_sample.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_sample.push_back("HLT_IsoMu22_v");
    triggerlist_sample.push_back("HLT_IsoTkMu22_v");
    triggerlist_sample.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

    triggerlist_sample_3l = triggerlist_sample;
    triggerlist_sample_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    triggerlist_sample_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    triggerlist_sample_3l.push_back("HLT_TripleMu_12_10_5_v");
    triggerlist_sample_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    print_triggers();
    return;


  }

  else{

    if(sample.Contains("DoubleMu")){
      triggerlist_sample.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_sample.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

      triggerlist_sample_3l = triggerlist_sample;
      triggerlist_sample_3l.push_back("HLT_TripleMu_12_10_5_v");

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_veto.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

      triggerlist_veto_3l.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_veto_3l.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      triggerlist_veto_3l.push_back("HLT_TripleMu_12_10_5_v");
    }
    
    
    if(sample.Contains("DoubleEG")){
      triggerlist_sample.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_sample_3l = triggerlist_sample;
      triggerlist_sample_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_veto_3l.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_veto_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    }
    
    
    if(sample.Contains("MuonEG")){
      triggerlist_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");

      triggerlist_sample_3l = triggerlist_sample;
      triggerlist_sample_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
      triggerlist_sample_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");  

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");

      triggerlist_veto_3l.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto_3l.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
      triggerlist_veto_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); 
    }
    
    
    if(sample.Contains("SingleMu")){
      triggerlist_sample.push_back("HLT_IsoMu22_v");
      triggerlist_sample.push_back("HLT_IsoTkMu22_v");

      triggerlist_sample_3l = triggerlist_sample;

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_IsoMu22_v");
      triggerlist_veto.push_back("HLT_IsoTkMu22_v");

      triggerlist_veto_3l.push_back("HLT_IsoMu22_v");
      triggerlist_veto_3l.push_back("HLT_IsoTkMu22_v");
    }
    
    
    if(sample.Contains("SingleEle")){
      triggerlist_sample.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

      triggerlist_sample_3l = triggerlist_sample;

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
      triggerlist_veto_3l.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
    }
    
  }
  

}




void produce_triggerlist(TString sample, bool isMC){

  TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X/DoubleMuon/DoubleMu_2016B_02_08_16/160802_163122/0000/HTauTauAnalysis_1.root";

  TFile* f = TFile::Open(filename);
  TH1F* hCounter = (TH1F*)f->Get("HTauTauTree/Counters");

  produce_triggerlist(sample, isMC, hCounter);

}




int FindTriggerNumber(TString triggername){
  
  for(unsigned int it=0;it<triggerlist.size();it++){ 	
  	if(triggerlist.at(it).CompareTo(triggername.Data())==0)return it;
  	else {
  	    TString newName=triggername.Data();
  	    newName.Prepend("HLT_");
  	    newName.Append("_v1");
  	    if(triggerlist.at(it).CompareTo(newName.Data())==0)return it;
  	}
  }
  return -1;

}




bool IsTriggerFired(int triggerbit, int triggernumber){ 
  if(triggernumber>=0 && triggernumber<triggerlist.size()) return triggerbit & (1 << triggernumber);
  return false;
}


bool IsTriggerFired(int triggerbit, TString triggername){
  return IsTriggerFired(triggerbit,FindTriggerNumber(triggername));
}



bool pass_trigger(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_veto.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_veto[i])){
      return false;
    }
  }

  for(unsigned int i=0;i<triggerlist_sample.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_sample[i])){
      return true;
    }
  }

  return false;

}




bool pass_trigger_3l(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_veto_3l.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_veto_3l[i])){
      return false;
    }
  }

  for(unsigned int i=0;i<triggerlist_sample_3l.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_sample_3l[i])){
      return true;
    }
  }

  return false;

}



void add_trigger_filter(TString file_in, TString file_out, vector<TString> treename){

  produce_triggerlist(file_in,false);


  TFile* f_new = TFile::Open(file_out);
  if(f_new!=0){
    cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(file_out,"RECREATE");
 
  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){
    
    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(file_in);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;
        
   
    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    bool _isTrig;
    tree_new->Branch("isTrig",&_isTrig,"isTrig/O");
    
    //Old branches
    Long64_t _triggerbit;
    tree->SetBranchAddress("triggerbit",&_triggerbit);
    
    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _triggerbit = 0;
      
      _isTrig = 0;
      
      int entry_ok = tree->GetEntry(i);      


      _isTrig = pass_trigger(_triggerbit);
      
      tree_new->Fill();
      
    }

    f_new->cd();

    tree_new->Write();

  }


  f_new->Close();


  return;
    

}






void add_trigger_filter_fromSecondaryFile(TString file_in, TString file_out, TString treename, TString SecondaryFile, TString SecondaryTreename){


  TFile* f_new = TFile::Open(file_out);
  if(f_new!=0){
    cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(file_out,"RECREATE");
     
  TChain * tree = new TChain(treename);
  tree->Add(file_in);
  
  TChain * tree2 = new TChain(SecondaryTreename);
  tree2->Add(SecondaryFile);
  
  
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;
  
  
  TTree* tree_new=tree->GetTree()->CloneTree(0);
  
  //New branches
  bool _isTrig;
  tree_new->Branch("isTrig",&_isTrig,"isTrig/O");
  
  //Old branches
  bool _isTrigOld;
  tree2->SetBranchAddress("isTrig",&_isTrigOld);
  
  for(int i=0;i<nentries;i++){
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;
        
    _isTrig = 0;
    _isTrigOld = 0;
    
    int entry_ok = tree->GetEntry(i);
    entry_ok = tree2->GetEntry(i);      
          
    _isTrig = _isTrigOld;
    
    tree_new->Fill();
    
  }
  
  f_new->cd();
  
  tree_new->Write();
  
  f_new->Close();


  return;
    

}





void test(){

  TString file_in="/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810.root";
  TString file_out="/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root";
  TString treename="T";

  TString SecondaryFile="/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016B_split_trig_filt.root";
  TString SecondaryTree="HTauTauTree_2lOS_CR";

  /*TString file_in="/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split.root";
  TString file_out="/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split_trig_filt.root";

  vector<TString> treename;
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lOS_CR");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");*/
  
  add_trigger_filter_fromSecondaryFile(file_in,file_out,treename,SecondaryFile,SecondaryTree);
  //add_trigger_filter(file_in,file_out,treename);

}
