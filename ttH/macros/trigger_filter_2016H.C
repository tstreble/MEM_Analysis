#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TH1F.h>
#include <iostream>

using namespace std;


vector<TString> triggerlist_2016H;
vector<TString> triggerlist_2016H_sample;
vector<TString> triggerlist_2016H_veto;
vector<TString> triggerlist_2016H_sample_3l;
vector<TString> triggerlist_2016H_veto_3l;
vector<TString> triggerlist_2016H_sample_1l;
vector<TString> triggerlist_2016H_veto_1l;


void print_triggers_2016H(){

  cout<<endl;
  cout<<"Vetoed triggers"<<endl;
  for(unsigned int j=0;j<triggerlist_2016H_veto.size();j++)	
    cout<<triggerlist_2016H_veto[j]<<endl;

  cout<<"Allowed triggers"<<endl;
  for(unsigned int j=0;j<triggerlist_2016H_sample.size();j++)	
    cout<<triggerlist_2016H_sample[j]<<endl;

  cout<<"Vetoed triggers 3l"<<endl;
  for(unsigned int j=0;j<triggerlist_2016H_veto_3l.size();j++)	
    cout<<triggerlist_2016H_veto_3l[j]<<endl;

  cout<<"Allowed triggers 3l"<<endl;
  for(unsigned int j=0;j<triggerlist_2016H_sample_3l.size();j++)	
    cout<<triggerlist_2016H_sample_3l[j]<<endl;

  cout<<"Vetoed triggers 1l"<<endl;
  for(unsigned int j=0;j<triggerlist_2016H_veto_1l.size();j++)	
    cout<<triggerlist_2016H_veto_1l[j]<<endl;

  cout<<"Allowed triggers 1l"<<endl;
  for(unsigned int j=0;j<triggerlist_2016H_sample_1l.size();j++)	
    cout<<triggerlist_2016H_sample_1l[j]<<endl;

}



void produce_triggerlist_2016H(TString sample, bool isMC, TH1F* hCounter){

  triggerlist_2016H.clear();
  triggerlist_2016H_sample.clear();
  triggerlist_2016H_veto.clear();
  triggerlist_2016H_sample_3l.clear();
  triggerlist_2016H_veto_3l.clear();
  triggerlist_2016H_sample_1l.clear();
  triggerlist_2016H_veto_1l.clear();


  for(int itr=1;itr<=hCounter->GetNbinsX();itr++){
    TString binlabel = hCounter->GetXaxis()->GetBinLabel(itr);
    if(binlabel.BeginsWith("HLT"))triggerlist_2016H.push_back(hCounter->GetXaxis()->GetBinLabel(itr));
  }

  if(isMC){

    triggerlist_2016H_sample.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    triggerlist_2016H_sample.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    triggerlist_2016H_sample.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_2016H_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_2016H_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    //triggerlist_2016H_sample.push_back("HLT_IsoMu22_v");
    //triggerlist_2016H_sample.push_back("HLT_IsoTkMu22_v");
    triggerlist_2016H_sample.push_back("HLT_IsoMu24_v");
    triggerlist_2016H_sample.push_back("HLT_IsoTkMu24_v");
    triggerlist_2016H_sample.push_back("HLT_IsoMu22_eta2p1_v");
    triggerlist_2016H_sample.push_back("HLT_IsoTkMu22_eta2p1_v");
    //triggerlist_2016H_sample.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
    triggerlist_2016H_sample.push_back("HLT_Ele27_WPTight_Gsf_v");

    triggerlist_2016H_sample_3l = triggerlist_2016H_sample;
    triggerlist_2016H_sample_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    triggerlist_2016H_sample_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    triggerlist_2016H_sample_3l.push_back("HLT_TripleMu_12_10_5_v");
    triggerlist_2016H_sample_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    //triggerlist_2016H_sample_1l.push_back("HLT_IsoMu22_v");
    //triggerlist_2016H_sample_1l.push_back("HLT_IsoTkMu22_v");
    triggerlist_2016H_sample_1l.push_back("HLT_IsoMu24_v");
    triggerlist_2016H_sample_1l.push_back("HLT_IsoTkMu24_v");
    triggerlist_2016H_sample_1l.push_back("HLT_IsoMu22_eta2p1_v");
    triggerlist_2016H_sample_1l.push_back("HLT_IsoTkMu22_eta2p1_v");
    //triggerlist_2016H_sample_1l.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
    triggerlist_2016H_sample_1l.push_back("HLT_Ele27_WPTight_Gsf_v");

    print_triggers_2016H();
    return;


  }

  else{

    if(sample.Contains("DoubleMu")){
      triggerlist_2016H_sample.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_2016H_sample.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

      triggerlist_2016H_sample_3l = triggerlist_2016H_sample;
      triggerlist_2016H_sample_3l.push_back("HLT_TripleMu_12_10_5_v");

      print_triggers_2016H();
      return;
    }
    else{
      triggerlist_2016H_veto.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_2016H_veto.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

      triggerlist_2016H_veto_3l.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_2016H_veto_3l.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      triggerlist_2016H_veto_3l.push_back("HLT_TripleMu_12_10_5_v");
    }
    
    
    if(sample.Contains("DoubleEG")){
      triggerlist_2016H_sample.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_2016H_sample_3l = triggerlist_2016H_sample;
      triggerlist_2016H_sample_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

      print_triggers_2016H();
      return;
    }
    else{
      triggerlist_2016H_veto.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_2016H_veto_3l.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_2016H_veto_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    }
    
    
    if(sample.Contains("MuonEG")){
      triggerlist_2016H_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_2016H_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_2016H_sample_3l = triggerlist_2016H_sample;
      triggerlist_2016H_sample_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
      triggerlist_2016H_sample_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");  

      print_triggers_2016H();
      return;
    }
    else{
      triggerlist_2016H_veto.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_2016H_veto.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_2016H_veto_3l.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_2016H_veto_3l.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_2016H_veto_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
      triggerlist_2016H_veto_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); 
    }
    
    
    if(sample.Contains("SingleMu")){
      //triggerlist_2016H_sample.push_back("HLT_IsoMu22_v");
      //triggerlist_2016H_sample.push_back("HLT_IsoTkMu22_v");
      triggerlist_2016H_sample.push_back("HLT_IsoMu24_v");
      triggerlist_2016H_sample.push_back("HLT_IsoTkMu24_v");
      triggerlist_2016H_sample.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_2016H_sample.push_back("HLT_IsoTkMu22_eta2p1_v");
      triggerlist_2016H_sample_3l = triggerlist_2016H_sample;

      triggerlist_2016H_sample_1l = triggerlist_2016H_sample;

      print_triggers_2016H();
      return;
    }
    else{
      /*triggerlist_2016H_veto.push_back("HLT_IsoMu22_v");
      triggerlist_2016H_veto.push_back("HLT_IsoTkMu22_v");

      triggerlist_2016H_veto_3l.push_back("HLT_IsoMu22_v");
      triggerlist_2016H_veto_3l.push_back("HLT_IsoTkMu22_v");

      triggerlist_2016H_veto_1l.push_back("HLT_IsoMu22_v");
      triggerlist_2016H_veto_1l.push_back("HLT_IsoTkMu22_v");*/
      triggerlist_2016H_veto.push_back("HLT_IsoMu24_v");
      triggerlist_2016H_veto.push_back("HLT_IsoTkMu24_v");
      triggerlist_2016H_veto.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_2016H_veto.push_back("HLT_IsoTkMu22_eta2p1_v");

      triggerlist_2016H_veto_3l.push_back("HLT_IsoMu24_v");
      triggerlist_2016H_veto_3l.push_back("HLT_IsoTkMu24_v");
      triggerlist_2016H_veto_3l.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_2016H_veto_3l.push_back("HLT_IsoTkMu22_eta2p1_v");

      triggerlist_2016H_veto_1l.push_back("HLT_IsoMu24_v");
      triggerlist_2016H_veto_1l.push_back("HLT_IsoTkMu24_v");
      triggerlist_2016H_veto_1l.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_2016H_veto_1l.push_back("HLT_IsoTkMu22_eta2p1_v");

      
    }
    
    
    if(sample.Contains("SingleEle")){
      //triggerlist_2016H_sample.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
      triggerlist_2016H_sample.push_back("HLT_Ele27_WPTight_Gsf_v");

      triggerlist_2016H_sample_3l = triggerlist_2016H_sample;

      triggerlist_2016H_sample_1l = triggerlist_2016H_sample;

      print_triggers_2016H();
      return;
    }
    else{
      /*triggerlist_2016H_veto.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
      triggerlist_2016H_veto_3l.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
      triggerlist_2016H_veto_1l.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");*/
      triggerlist_2016H_veto.push_back("HLT_Ele27_WPTight_Gsf_v");
      triggerlist_2016H_veto_3l.push_back("HLT_Ele27_WPTight_Gsf_v");
      triggerlist_2016H_veto_1l.push_back("HLT_Ele27_WPTight_Gsf_v");
      
    }
    
  }
  

}




void produce_triggerlist_2016H(TString sample, bool isMC){

  //TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_reHLT/ttHToNonbb_M125_13TeV_powheg_pythia8/ttH_11_11_16/161111_095210/0000/HTauTauAnalysis_1.root";
  //TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_Moriond17/MuonEG/MuonEG_2016Hv2_17_01_16/170117_165627/0000/HTauTauAnalysis_1.root";
  TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_Moriond17_2/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/ttH_25_01_16/170124_235258/0000/HTauTauAnalysis_1.root";

  TFile* f = TFile::Open(filename);
  TH1F* hCounter = (TH1F*)f->Get("HTauTauTree/Counters");

  produce_triggerlist_2016H(sample, isMC, hCounter);

}




int FindTriggerNumber_2016H(TString triggername){
  
  for(unsigned int it=0;it<triggerlist_2016H.size();it++){ 	
  	if(triggerlist_2016H.at(it).CompareTo(triggername.Data())==0)return it;
  	else {
  	    TString newName=triggername.Data();
  	    newName.Prepend("HLT_");
  	    newName.Append("_v1");
  	    if(triggerlist_2016H.at(it).CompareTo(newName.Data())==0)return it;
  	}
  }
  return -1;

}




bool IsTriggerFired_2016H(Long64_t triggerbit, int triggernumber){ 
  if(triggernumber>=0 && triggernumber<triggerlist_2016H.size()) return triggerbit & (long(1) << triggernumber);
  return false;
}


bool IsTriggerFired_2016H(Long64_t triggerbit, TString triggername){
  return IsTriggerFired_2016H(triggerbit,FindTriggerNumber_2016H(triggername));
}



bool pass_trigger_2016H(Long64_t triggerbit){
  for(unsigned int i=0;i<triggerlist_2016H_veto.size();i++){  
    if(IsTriggerFired_2016H(triggerbit,triggerlist_2016H_veto[i])){
      return false;
    }
  }

  for(unsigned int i=0;i<triggerlist_2016H_sample.size();i++){
    if(IsTriggerFired_2016H(triggerbit,triggerlist_2016H_sample[i])){
      return true;
    }
  }

  return false;

}




bool pass_trigger_3l_2016H(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_2016H_veto_3l.size();i++){  
    if(IsTriggerFired_2016H(triggerbit,triggerlist_2016H_veto_3l[i])){
      return false;
    }
  }

  for(unsigned int i=0;i<triggerlist_2016H_sample_3l.size();i++){
    if(IsTriggerFired_2016H(triggerbit,triggerlist_2016H_sample_3l[i])){
      return true;
    }
  }

  return false;

}





bool pass_trigger_1l_2016H(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_2016H_veto_1l.size();i++){  
    if(IsTriggerFired_2016H(triggerbit,triggerlist_2016H_veto_1l[i])){
      return false;
    }
  }

  for(unsigned int i=0;i<triggerlist_2016H_sample_1l.size();i++){
    if(IsTriggerFired_2016H(triggerbit,triggerlist_2016H_sample_1l[i])){
      return true;
    }
  }

  return false;

}




void add_trigger_filter_2016H(TString file_in, TString file_out, vector<TString> treename, bool isMC){

  produce_triggerlist_2016H(file_in,isMC);


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
    nentries=10;
        
    //Old branches
    Long64_t _triggerbit;
    tree->SetBranchAddress("triggerbit",&_triggerbit);
   
    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    bool _isTrig_1l_v2;
    bool _isTrig_v2;
    bool _isTrig_3l_v2;

    
    tree_new->Branch("isTrig_1l_v2",&_isTrig_1l_v2,"isTrig_1l_v2/O");
    tree_new->Branch("isTrig_v2",&_isTrig_v2,"isTrig_v2/O");
    tree_new->Branch("isTrig_3l_v2",&_isTrig_3l_v2,"isTrig_3l_v2/O");

    
    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _triggerbit = 0;
      
      _isTrig_1l_v2 = 0;
      _isTrig_v2 = 0;
      _isTrig_3l_v2 = 0;
      
      int entry_ok = tree->GetEntry(i);      

      _isTrig_1l_v2 = pass_trigger_1l_2016H(_triggerbit);
      _isTrig_v2 = pass_trigger_2016H(_triggerbit);
      _isTrig_3l_v2 = pass_trigger_3l_2016H(_triggerbit);

      cout<<"isTrig_1l_v2="<<_isTrig_1l_v2<<endl;
      

      tree_new->Fill();
      
    }

    f_new->cd();

    tree_new->Write();

  }


  f_new->Close();


  return;
    

}



