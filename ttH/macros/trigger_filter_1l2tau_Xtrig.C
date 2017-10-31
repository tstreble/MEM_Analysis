#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TH1F.h>
#include <iostream>
#include <TGraphAsymmErrors.h>

using namespace std;


vector<TString> triggerlist;
vector<TString> triggerlist_sample;
vector<TString> triggerlist_veto;
vector<TString> triggerlist_sample_3l;
vector<TString> triggerlist_veto_3l;
vector<TString> triggerlist_sample_1l;
vector<TString> triggerlist_veto_1l;

vector<TString> triggerlist_sample_SingleE;
vector<TString> triggerlist_sample_ETau;
vector<TString> triggerlist_sample_SingleMu;
vector<TString> triggerlist_sample_MuTau;


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

  cout<<endl;
  cout<<"Vetoed triggers 1l"<<endl;
  for(unsigned int j=0;j<triggerlist_veto_1l.size();j++)	
    cout<<triggerlist_veto_1l[j]<<endl;

  cout<<"Allowed triggers 1l"<<endl;
  for(unsigned int j=0;j<triggerlist_sample_1l.size();j++)	
    cout<<triggerlist_sample_1l[j]<<endl;

}



void produce_triggerlist(TString sample, bool isMC, TH1F* hCounter){

  triggerlist.clear();
  triggerlist_sample.clear();
  triggerlist_veto.clear();
  triggerlist_sample_3l.clear();
  triggerlist_veto_3l.clear();
  triggerlist_sample_1l.clear();
  triggerlist_veto_1l.clear();

  triggerlist_sample_SingleE.clear();
  triggerlist_sample_ETau.clear();
  triggerlist_sample_SingleMu.clear();
  triggerlist_sample_MuTau.clear();


  for(int itr=1;itr<=hCounter->GetNbinsX();itr++){
    TString binlabel = hCounter->GetXaxis()->GetBinLabel(itr);
    if(binlabel.BeginsWith("HLT"))triggerlist.push_back(hCounter->GetXaxis()->GetBinLabel(itr));
  }

  if(isMC){

    triggerlist_sample.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    triggerlist_sample.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    triggerlist_sample.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");

    triggerlist_sample.push_back("HLT_IsoMu22_v");
    triggerlist_sample.push_back("HLT_IsoTkMu22_v");
    triggerlist_sample.push_back("HLT_IsoMu22_eta2p1_v");
    triggerlist_sample.push_back("HLT_IsoTkMu22_eta2p1_v");
    triggerlist_sample.push_back("HLT_IsoMu24_v");
    triggerlist_sample.push_back("HLT_IsoTkMu24_v");
    triggerlist_sample.push_back("HLT_Ele27_WPTight_Gsf_v");
    triggerlist_sample.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
    triggerlist_sample.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

    triggerlist_sample_3l = triggerlist_sample;
    triggerlist_sample_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
    triggerlist_sample_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    triggerlist_sample_3l.push_back("HLT_TripleMu_12_10_5_v");
    triggerlist_sample_3l.push_back("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v");

    triggerlist_sample_1l.push_back("HLT_IsoMu22_v");
    triggerlist_sample_1l.push_back("HLT_IsoTkMu22_v"); 
    triggerlist_sample_1l.push_back("HLT_IsoMu22_eta2p1_v");
    triggerlist_sample_1l.push_back("HLT_IsoTkMu22_eta2p1_v");
    triggerlist_sample_1l.push_back("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v");

    triggerlist_sample_1l.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
    triggerlist_sample_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v");
    triggerlist_sample_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v");
    triggerlist_sample_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v");
    
    triggerlist_sample_SingleMu.push_back("HLT_IsoMu22_v");
    triggerlist_sample_SingleMu.push_back("HLT_IsoTkMu22_v"); 
    triggerlist_sample_SingleMu.push_back("HLT_IsoMu22_eta2p1_v");
    triggerlist_sample_SingleMu.push_back("HLT_IsoTkMu22_eta2p1_v");

    triggerlist_sample_MuTau.push_back("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v");

    triggerlist_sample_SingleE.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
    
    triggerlist_sample_ETau.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v");
    triggerlist_sample_ETau.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v");
    triggerlist_sample_ETau.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v");

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
      triggerlist_sample.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_sample.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");


      triggerlist_sample_3l = triggerlist_sample;
      triggerlist_sample_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
      triggerlist_sample_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");  

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_veto.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");

      triggerlist_veto_3l.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto_3l.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_veto_3l.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
      triggerlist_veto_3l.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
      triggerlist_veto_3l.push_back("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v");
      triggerlist_veto_3l.push_back("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"); 
    }
    

   
    if(sample.Contains("SingleMu")){
      triggerlist_sample.push_back("HLT_IsoMu22_v");
      triggerlist_sample.push_back("HLT_IsoTkMu22_v");
      triggerlist_sample.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_sample.push_back("HLT_IsoTkMu22_eta2p1_v");
      triggerlist_sample.push_back("HLT_IsoMu24_v");
      triggerlist_sample.push_back("HLT_IsoTkMu24_v");
      triggerlist_sample_3l = triggerlist_sample;

      triggerlist_sample_1l.push_back("HLT_IsoMu22_v");
      triggerlist_sample_1l.push_back("HLT_IsoTkMu22_v"); 
      triggerlist_sample_1l.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_sample_1l.push_back("HLT_IsoTkMu22_eta2p1_v");
      triggerlist_sample_1l.push_back("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v");

      print_triggers();
      return;
    }
    else{
      triggerlist_veto.push_back("HLT_IsoMu22_v");
      triggerlist_veto.push_back("HLT_IsoTkMu22_v");
      triggerlist_veto.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_veto.push_back("HLT_IsoTkMu22_eta2p1_v");
      triggerlist_veto.push_back("HLT_IsoMu24_v");
      triggerlist_veto.push_back("HLT_IsoTkMu24_v");

      triggerlist_veto_3l.push_back("HLT_IsoMu22_v");
      triggerlist_veto_3l.push_back("HLT_IsoTkMu22_v");
      triggerlist_veto_3l.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_veto_3l.push_back("HLT_IsoTkMu22_eta2p1_v");
      triggerlist_veto_3l.push_back("HLT_IsoMu24_v");
      triggerlist_veto_3l.push_back("HLT_IsoTkMu24_v");

      triggerlist_veto_1l.push_back("HLT_IsoMu22_v");
      triggerlist_veto_1l.push_back("HLT_IsoTkMu22_v"); 
      triggerlist_veto_1l.push_back("HLT_IsoMu22_eta2p1_v");
      triggerlist_veto_1l.push_back("HLT_IsoTkMu22_eta2p1_v");
      triggerlist_veto_1l.push_back("HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v");
      
    }
    
    
    if(sample.Contains("SingleEle")){
 
      triggerlist_sample.push_back("HLT_Ele27_WPTight_Gsf_v");
      triggerlist_sample.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
      triggerlist_sample.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
      triggerlist_sample_3l = triggerlist_sample;

      triggerlist_sample_1l.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
      triggerlist_sample_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v");
      triggerlist_sample_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v");
      triggerlist_sample_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v");

      print_triggers();
      return;
    }
    else{

      triggerlist_veto.push_back("HLT_Ele27_WPTight_Gsf_v");
      triggerlist_veto.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
      triggerlist_veto.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

      triggerlist_veto_3l.push_back("HLT_Ele27_WPTight_Gsf_v");
      triggerlist_veto_3l.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
      triggerlist_veto_3l.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");

      triggerlist_veto_1l.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
      triggerlist_veto_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_v");
      triggerlist_veto_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v");
      triggerlist_veto_1l.push_back("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v");
 
      
    }
    
  }
  

}




void produce_triggerlist(TString sample, bool isMC){

  //TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_reHLT/ttHToNonbb_M125_13TeV_powheg_pythia8/ttH_11_11_16/161111_095210/0000/HTauTauAnalysis_1.root";
  //TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_Moriond17/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/ttH_13_12_16/161213_175450/0000/HTauTauAnalysis_1.root";
TString filename="root://polgrid4.in2p3.fr//store/user/tstreble/ttH_prod_80X_Moriond17_2/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/ttH_25_01_16/170124_235258/0000/HTauTauAnalysis_1.root";

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




bool IsTriggerFired(Long64_t triggerbit, int triggernumber){ 
  if(triggernumber>=0 && triggernumber<triggerlist.size()) return triggerbit & (long(1) << triggernumber);
  return false;
}


bool IsTriggerFired(Long64_t triggerbit, TString triggername){
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

  /*cout<<"Trigger veto"<<endl;
  for(unsigned int i=0;i<triggerlist_veto_3l.size();i++)  
    cout<<triggerlist_veto_3l[i]<<" "<<IsTriggerFired(triggerbit,triggerlist_veto_3l[i])<<endl;
  cout<<"Trigger accepted"<<endl;
  for(unsigned int i=0;i<triggerlist_sample_3l.size();i++)  
  cout<<triggerlist_sample_3l[i]<<" "<<IsTriggerFired(triggerbit,triggerlist_sample_3l[i])<<endl;*/


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




bool pass_trigger_1l(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_veto_1l.size();i++){  
    if(IsTriggerFired(triggerbit,triggerlist_veto_1l[i])){
      return false;
    }
  }

  for(unsigned int i=0;i<triggerlist_sample_1l.size();i++){    
    if(IsTriggerFired(triggerbit,triggerlist_sample_1l[i])){
      return true;
    }
  }

  return false;

}






bool pass_trigger_SingleMu(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_sample_SingleMu.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_sample_SingleMu[i])){
      return true;
    }
  }

  return false;

}


bool pass_trigger_MuTau(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_sample_MuTau.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_sample_MuTau[i])){
      return true;
    }
  }

  return false;

}


bool pass_trigger_SingleEle(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_sample_SingleE.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_sample_SingleE[i])){
      return true;
    }
  }

  return false;

}


bool pass_trigger_ETau(Long64_t triggerbit){

  for(unsigned int i=0;i<triggerlist_sample_ETau.size();i++){
    if(IsTriggerFired(triggerbit,triggerlist_sample_ETau[i])){
      return true;
    }
  }

  return false;

}



float efficiency_from_TGraph(TGraphAsymmErrors* graph, float pt){

  return graph->Eval(pt);
  /*int n = graph->GetN();

  double x, y;
  graph->GetPoint(0,x,y);
  if(pt<x)
    return y;

  graph->GetPoint(n-1,x,y);
  if(pt>x)
    return y;


  for(int i=0; i<n;i++){

    graph->GetPoint(i,x,y);
    double err_low_x = graph->GetErrorXlow(i);
    double err_high_x = graph->GetErrorXhigh(i);
    if( (x-err_low_x) < pt && pt < (x+err_high_x) )
      return y;

  }

  return -1.;*/

}




void add_trigger_filter_1l2tau_Xtrig(TString file_in, TString file_out, vector<TString> treename, bool isMC){

  /*cout<<endl;
  cout<<file_in<<endl;
  cout<<endl;*/

  produce_triggerlist(file_in,isMC);


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
        
    //Old branches
    Long64_t _triggerbit;
    int _category;
    vector<int> *_recolep_sel_pdg;    
    vector<float> *_recolep_sel_pt;
    vector<float> *_recolep_sel_eta;
    vector<float> *_recotauh_sel_pt;
    vector<float> *_recotauh_sel_eta;
    vector<int> *_recotauh_sel_decayMode;

    ULong64_t _EventNumber;
    int _lumi;
    int _RunNumber;

    tree->SetBranchAddress("triggerbit",&_triggerbit);
    tree->SetBranchAddress("category",&_category);
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
    tree->SetBranchAddress("recotauh_sel_eta",&_recotauh_sel_eta);   
    tree->SetBranchAddress("recotauh_sel_decayMode",&_recotauh_sel_decayMode);

    tree->SetBranchAddress("EventNumber",&_EventNumber);   
    tree->SetBranchAddress("lumi",&_lumi);   
    tree->SetBranchAddress("RunNumber",&_RunNumber);   


    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    bool _isTrig_1l_v2;
    bool _isTrig_v2;
    bool _isTrig_3l_v2;

    float _triggerSF_weight_v2;

    
    tree_new->Branch("isTrig_1l_v2",&_isTrig_1l_v2,"isTrig_1l_v2/O");
    tree_new->Branch("isTrig_v2",&_isTrig_v2,"isTrig_v2/O");
    tree_new->Branch("isTrig_3l_v2",&_isTrig_3l_v2,"isTrig_3l_v2/O");

    tree_new->Branch("triggerSF_weight_v2",&_triggerSF_weight_v2,"triggerSF_weight_v2/F");

    TFile* f_Ele25_eff = TFile::Open("trigger_SF/Electron_Ele25WPTight_eff.root");    
    TGraphAsymmErrors* SingleE_eff_data_b = (TGraphAsymmErrors*) f_Ele25_eff->Get("ZMassEtaLt1p48_Data");
    //SingleE_eff_data_b->SetDirectory(0);
    TGraphAsymmErrors* SingleE_eff_data_e = (TGraphAsymmErrors*) f_Ele25_eff->Get("ZMassEta1p48to2p1_Data");
    //SingleE_eff_data_e->SetDirectory(0);
    TGraphAsymmErrors* SingleE_eff_MC_b = (TGraphAsymmErrors*) f_Ele25_eff->Get("ZMassEtaLt1p48_MC");
    //SingleE_eff_MC_b->SetDirectory(0);
    TGraphAsymmErrors* SingleE_eff_MC_e = (TGraphAsymmErrors*) f_Ele25_eff->Get("ZMassEta1p48to2p1_MC");
    //SingleE_eff_MC_e->SetDirectory(0);
    f_Ele25_eff->Close();

    vector<TGraphAsymmErrors*> SingleE_eff_data;
    SingleE_eff_data.push_back(SingleE_eff_data_b);
    SingleE_eff_data.push_back(SingleE_eff_data_e);
    vector<TGraphAsymmErrors*> SingleE_eff_MC;
    SingleE_eff_MC.push_back(SingleE_eff_MC_b);
    SingleE_eff_MC.push_back(SingleE_eff_MC_e);

    TFile* f_Ele24_eff = TFile::Open("trigger_SF/Electron_Ele24_eff.root");
    TGraphAsymmErrors* ETau_ele_eff_data_b = (TGraphAsymmErrors*) f_Ele24_eff->Get("ZMassEtaLt1p48_Data");
    //ETau_ele_eff_data_b->SetDirectory(0);
    TGraphAsymmErrors* ETau_ele_eff_data_e = (TGraphAsymmErrors*) f_Ele24_eff->Get("ZMassEta1p48to2p1_Data");
    //ETau_ele_eff_data_e->SetDirectory(0);
    TGraphAsymmErrors* ETau_ele_eff_MC_b = (TGraphAsymmErrors*) f_Ele24_eff->Get("ZMassEtaLt1p48_MC");
    //ETau_ele_eff_MC_b->SetDirectory(0);
    TGraphAsymmErrors* ETau_ele_eff_MC_e = (TGraphAsymmErrors*) f_Ele24_eff->Get("ZMassEta1p48to2p1_MC");
    //ETau_ele_eff_MC_e->SetDirectory(0);
    f_Ele24_eff->Close();    

    vector<TGraphAsymmErrors*> ETau_ele_eff_data;
    ETau_ele_eff_data.push_back(ETau_ele_eff_data_b);
    ETau_ele_eff_data.push_back(ETau_ele_eff_data_e);
    vector<TGraphAsymmErrors*> ETau_ele_eff_MC;
    ETau_ele_eff_MC.push_back(ETau_ele_eff_MC_b);
    ETau_ele_eff_MC.push_back(ETau_ele_eff_MC_e);


    TFile* f_ETau_tau_eff = TFile::Open("trigger_SF/trigger_sf_et_thomas.root");
    TGraphAsymmErrors* ETau_tau_eff_data_0 = (TGraphAsymmErrors*) f_ETau_tau_eff->Get("data_genuine_barrel_TightIso_dm0");
    //ETau_tau_eff_data_0->SetDirectory->(0);
    TGraphAsymmErrors* ETau_tau_eff_data_1 = (TGraphAsymmErrors*) f_ETau_tau_eff
->Get("data_genuine_barrel_TightIso_dm1");
    //ETau_tau_eff_data_1->SetDirectory->(0);
    TGraphAsymmErrors* ETau_tau_eff_data_2 = (TGraphAsymmErrors*) f_ETau_tau_eff
->Get("data_genuine_barrel_TightIso_dm10");
    //ETau_tau_eff_data_2->SetDirectory->(0);
    TGraphAsymmErrors* ETau_tau_eff_data_3 = (TGraphAsymmErrors*) f_ETau_tau_eff
->Get("data_genuine_endcap_TightIso_dm0");
    //ETau_tau_eff_data_3->SetDirectory->(0);
    TGraphAsymmErrors* ETau_tau_eff_data_4 = (TGraphAsymmErrors*) f_ETau_tau_eff
->Get("data_genuine_endcap_TightIso_dm1");
    //ETau_tau_eff_data_4->SetDirectory->(0);
    TGraphAsymmErrors* ETau_tau_eff_data_5 = (TGraphAsymmErrors*) f_ETau_tau_eff
->Get("data_genuine_endcap_TightIso_dm10");
    //ETau_tau_eff_data_5->SetDirectory->(0);

    TGraphAsymmErrors* ETau_tau_eff_MC_0 = (TGraphAsymmErrors*) f_ETau_tau_eff->Get("mc_genuine_barrel_TightIso");
    //ETau_tau_eff_MC_0->SetDirectory->(0);
    TGraphAsymmErrors* ETau_tau_eff_MC_1 = (TGraphAsymmErrors*) f_ETau_tau_eff
->Get("mc_genuine_endcap_TightIso");
    //ETau_tau_eff_MC_1->SetDirectory->(0);
    f_ETau_tau_eff->Close();

    vector<TGraphAsymmErrors*> ETau_tau_eff_data;
    ETau_tau_eff_data.push_back(ETau_tau_eff_data_0);
    ETau_tau_eff_data.push_back(ETau_tau_eff_data_1);
    ETau_tau_eff_data.push_back(ETau_tau_eff_data_2);
    ETau_tau_eff_data.push_back(ETau_tau_eff_data_3);
    ETau_tau_eff_data.push_back(ETau_tau_eff_data_4);
    ETau_tau_eff_data.push_back(ETau_tau_eff_data_5);
    vector<TGraphAsymmErrors*> ETau_tau_eff_MC;
    ETau_tau_eff_MC.push_back(ETau_tau_eff_MC_0);
    ETau_tau_eff_MC.push_back(ETau_tau_eff_MC_1);


    TFile* f_Mu22_eff = TFile::Open("trigger_SF/Muon_Mu22OR_eta2p1_eff.root");
    TGraphAsymmErrors* SingleMu_eff_data_0 = (TGraphAsymmErrors*) f_Mu22_eff->Get("ZMassEtaLt0p9_Data");
    //SingleMu_eff_data_0->SetDirectory(0);
    TGraphAsymmErrors* SingleMu_eff_data_1 = (TGraphAsymmErrors*) f_Mu22_eff->Get("ZMassEta0p9to1p2_Data");
    //SingleMu_eff_data_1->SetDirectory(0);
    TGraphAsymmErrors* SingleMu_eff_data_2 = (TGraphAsymmErrors*) f_Mu22_eff->Get("ZMassEta1p2to2p1_Data");
    //SingleMu_eff_data_2->SetDirectory(0);
    TGraphAsymmErrors* SingleMu_eff_MC_0 = (TGraphAsymmErrors*) f_Mu22_eff->Get("ZMassEtaLt0p9_MC");
    //SingleMu_eff_MC_0->SetDirectory(0);
    TGraphAsymmErrors* SingleMu_eff_MC_1 = (TGraphAsymmErrors*) f_Mu22_eff->Get("ZMassEta0p9to1p2_MC");
    //SingleMu_eff_MC_1->SetDirectory(0);
    TGraphAsymmErrors* SingleMu_eff_MC_2 = (TGraphAsymmErrors*) f_Mu22_eff->Get("ZMassEta1p2to2p1_MC");
    //SingleMu_eff_MC_2->SetDirectory(0);
    f_Mu22_eff->Close();

    vector<TGraphAsymmErrors*> SingleMu_eff_data;
    SingleMu_eff_data.push_back(SingleMu_eff_data_0);
    SingleMu_eff_data.push_back(SingleMu_eff_data_1);
    SingleMu_eff_data.push_back(SingleMu_eff_data_2);
    vector<TGraphAsymmErrors*> SingleMu_eff_MC;
    SingleMu_eff_MC.push_back(SingleMu_eff_MC_0);
    SingleMu_eff_MC.push_back(SingleMu_eff_MC_1);
    SingleMu_eff_MC.push_back(SingleMu_eff_MC_2);


    TFile* f_Mu19_eff = TFile::Open("trigger_SF/Muon_Mu19leg_2016BtoH_eff.root");
    TGraphAsymmErrors* MuTau_mu_eff_data_0 = (TGraphAsymmErrors*) f_Mu19_eff->Get("ZMassEtaLt0p9_Data");
    //MuTau_mu_eff_data_0->SetDirectory(0);
    TGraphAsymmErrors* MuTau_mu_eff_data_1 = (TGraphAsymmErrors*) f_Mu19_eff->Get("ZMassEta0p9to1p2_Data");
    //MuTau_mu_eff_data_1->SetDirectory(0);
    TGraphAsymmErrors* MuTau_mu_eff_data_2 = (TGraphAsymmErrors*) f_Mu19_eff->Get("ZMassEta1p2to2p1_Data");
    //MuTau_mu_eff_data_2->SetDirectory(0);
    TGraphAsymmErrors* MuTau_mu_eff_MC_0 = (TGraphAsymmErrors*) f_Mu19_eff->Get("ZMassEtaLt0p9_MC");
    //MuTau_mu_eff_MC_0->SetDirectory(0);
    TGraphAsymmErrors* MuTau_mu_eff_MC_1 = (TGraphAsymmErrors*) f_Mu19_eff->Get("ZMassEta0p9to1p2_MC");
    //MuTau_mu_eff_MC_1->SetDirectory(0);
    TGraphAsymmErrors* MuTau_mu_eff_MC_2 = (TGraphAsymmErrors*) f_Mu19_eff->Get("ZMassEta1p2to2p1_MC");
    //MuTau_mu_eff_MC_2->SetDirectory(0);
    f_Mu19_eff->Close();

    vector<TGraphAsymmErrors*> MuTau_mu_eff_data;
    MuTau_mu_eff_data.push_back(MuTau_mu_eff_data_0);
    MuTau_mu_eff_data.push_back(MuTau_mu_eff_data_1);
    MuTau_mu_eff_data.push_back(MuTau_mu_eff_data_2);
    vector<TGraphAsymmErrors*> MuTau_mu_eff_MC;
    MuTau_mu_eff_MC.push_back(MuTau_mu_eff_MC_0);
    MuTau_mu_eff_MC.push_back(MuTau_mu_eff_MC_1);
    MuTau_mu_eff_MC.push_back(MuTau_mu_eff_MC_2);

    TFile* f_MuTau_tau_eff = TFile::Open("trigger_SF/trigger_sf_mt_thomas.root");
    TGraphAsymmErrors* MuTau_tau_eff_data_0 = (TGraphAsymmErrors*) f_MuTau_tau_eff->Get("data_genuine_barrel_TightIso");
    //MuTau_tau_eff_data_0->SetDirectory->(0);
    TGraphAsymmErrors* MuTau_tau_eff_data_1 = (TGraphAsymmErrors*) f_MuTau_tau_eff->Get("data_genuine_endcap_TightIso");
    //MuTau_tau_eff_data_1->SetDirectory->(0);
    TGraphAsymmErrors* MuTau_tau_eff_MC_0 = (TGraphAsymmErrors*) f_MuTau_tau_eff->Get("mc_genuine_barrel_TightIso");
    //MuTau_tau_eff_MC_0->SetDirectory->(0);
    TGraphAsymmErrors* MuTau_tau_eff_MC_1 = (TGraphAsymmErrors*) f_MuTau_tau_eff->Get("mc_genuine_endcap_TightIso");
    //MuTau_tau_eff_MC_1->SetDirectory->(0);
    f_MuTau_tau_eff->Close();

    vector<TGraphAsymmErrors*> MuTau_tau_eff_data;
    MuTau_tau_eff_data.push_back(MuTau_tau_eff_data_0);
    MuTau_tau_eff_data.push_back(MuTau_tau_eff_data_1);
    vector<TGraphAsymmErrors*> MuTau_tau_eff_MC;
    MuTau_tau_eff_MC.push_back(MuTau_tau_eff_MC_0);
    MuTau_tau_eff_MC.push_back(MuTau_tau_eff_MC_1);

    //nentries = 10;
    for(int i=0;i<nentries;i++){


      if(i%10000==0)
	cout<<"i="<<i<<endl;
      
      _triggerbit = 0;
      _category = 0;
      _recolep_sel_pdg = 0;    
      _recolep_sel_eta = 0;
      _recolep_sel_pt = 0;  
      _recotauh_sel_eta = 0;
      _recotauh_sel_pt = 0;
      _recotauh_sel_decayMode = 0;

      _RunNumber = 0;
      _lumi = 0;
      _EventNumber = 0;

      _isTrig_1l_v2 = 0;
      _isTrig_v2 = 0;
      _isTrig_3l_v2 = 0;

      _triggerSF_weight_v2 = 0;
      
      int entry_ok = tree->GetEntry(i);    

      _isTrig_1l_v2 = pass_trigger_1l(_triggerbit);
      _isTrig_v2 = pass_trigger(_triggerbit);

      //cout<<endl;
      //cout<<_RunNumber<<":"<<_lumi<<":"<<_EventNumber<<endl;
      _isTrig_3l_v2 = pass_trigger_3l(_triggerbit);

      _triggerSF_weight_v2 = 1.;

      if(_category==11 || _category==41){

	if(abs((*_recolep_sel_pdg)[0])==11 || abs((*_recolep_sel_pdg)[1])==11)
	  _triggerSF_weight_v2 = 1.01;

      }

      else if(_category==20 || _category==50){

	if(abs((*_recolep_sel_eta)[0])>2.1) _triggerSF_weight_v2 = 0.;

	else{

	bool isTrig_SingleMu = pass_trigger_SingleMu(_triggerbit);
	bool isTrig_MuTau = pass_trigger_MuTau(_triggerbit);
	bool isTrig_SingleEle = pass_trigger_SingleEle(_triggerbit);
	bool isTrig_ETau = pass_trigger_ETau(_triggerbit);

	float pt_lep = (*_recolep_sel_pt)[0];
	float pt_tau0 = (*_recotauh_sel_pt)[0];
        float pt_tau1 = (*_recotauh_sel_pt)[1];
	float eta_lep = (*_recolep_sel_eta)[0];
        float eta_tau0 = (*_recotauh_sel_eta)[0];
        float eta_tau1 = (*_recotauh_sel_eta)[1];
	int DM_tau0 = (*_recotauh_sel_decayMode)[0];
        int DM_tau1 = (*_recotauh_sel_decayMode)[1];


	if(abs((*_recolep_sel_pdg)[0])==13){

	   int i_lep = -1;
	   if(abs(eta_lep)<0.9) i_lep = 0;
	   else if (abs(eta_lep)<1.2) i_lep = 1;
	   else if (abs(eta_lep)<2.1) i_lep = 2;

           float eff_L_mu_data = efficiency_from_TGraph(SingleMu_eff_data[i_lep],pt_lep);
	   float eff_l_mu_data = efficiency_from_TGraph(MuTau_mu_eff_data[i_lep],pt_lep);

           float eff_L_mu_MC = efficiency_from_TGraph(SingleMu_eff_MC[i_lep],pt_lep);
           float eff_l_mu_MC = efficiency_from_TGraph(MuTau_mu_eff_MC[i_lep],pt_lep);

	   int i_tau0 = -1;
	   if(abs(eta_tau0)<1.479) i_tau0 = 0;
           else i_tau0 = 1;

           float eff_tau0_data = efficiency_from_TGraph(MuTau_tau_eff_data[i_tau0],pt_tau0);
           float eff_tau0_MC = efficiency_from_TGraph(MuTau_tau_eff_MC[i_tau0],pt_tau0);

           int i_tau1 = -1;
           if(abs(eta_tau1)<1.479) i_tau1 = 0;
           else i_tau1 = 1;

           float eff_tau1_data = efficiency_from_TGraph(MuTau_tau_eff_data[i_tau1],pt_tau1);
           float eff_tau1_MC = efficiency_from_TGraph(MuTau_tau_eff_MC[i_tau1],pt_tau1);

	   float eff_num_data = 0.;
           float eff_denom_MC = 1.;

	   if(isTrig_SingleMu && isTrig_MuTau){
	     //eff_num_data = eff_L_mu_data*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     //eff_denom_MC = eff_L_mu_MC*(1. - (1.-eff_tau0_MC)*(1.-eff_tau1_MC));
	     eff_num_data = TMath::Min(eff_L_mu_data,eff_l_mu_data)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     eff_denom_MC = TMath::Min(eff_L_mu_MC,eff_l_mu_MC)*(1. - (1.-eff_tau0_MC)*(1.-eff_tau1_MC));
	   }
	   else if(isTrig_SingleMu && !isTrig_MuTau){	   
	     //eff_num_data = eff_L_mu_data*(1.-eff_tau0_data)*(1.-eff_tau1_data);
	     //eff_denom_MC = eff_L_mu_MC*(1.-eff_tau0_MC)*(1.-eff_tau1_MC);

	     eff_num_data = TMath::Max(1e-2,eff_L_mu_data - TMath::Min(eff_L_mu_data,eff_l_mu_data)*(1-(1.-eff_tau0_data)*(1.-eff_tau1_data)));
	     eff_denom_MC = TMath::Max(1e-2,eff_L_mu_MC - TMath::Min(eff_L_mu_MC,eff_l_mu_MC)*(1-(1.-eff_tau0_MC)*(1.-eff_tau1_MC)));

	   }
           else if(!isTrig_SingleMu && isTrig_MuTau){
	     //eff_num_data = (eff_l_mu_data-eff_L_mu_data)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     //eff_denom_MC = (eff_l_mu_MC-eff_L_mu_MC)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     eff_num_data = TMath::Max(1.e-2, (eff_l_mu_data-eff_L_mu_data)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data)));
	     eff_denom_MC = TMath::Max(1.e-2, (eff_l_mu_MC-eff_L_mu_MC)*(1. - (1.-eff_tau0_MC)*(1.-eff_tau1_MC)));

           }

	   /*cout<<"isTrig_SingleMu="<<isTrig_SingleMu<<" isTrig_MuTau="<<isTrig_MuTau<<endl;
	   cout<<"eff_L_mu_data="<<eff_L_mu_data<<endl;
	   cout<<"eff_l_mu_data="<<eff_l_mu_data<<endl;
	   cout<<"eff_tau0_data="<<eff_tau0_data<<endl;
	   cout<<"eff_tau1_data="<<eff_tau1_data<<endl;
	   cout<<"eff_L_mu_MC="<<eff_L_mu_MC<<endl;
	   cout<<"eff_l_mu_MC="<<eff_l_mu_MC<<endl;
	   cout<<"eff_tau0_MC="<<eff_tau0_MC<<endl;
	   cout<<"eff_tau1_MC="<<eff_tau1_MC<<endl;
	   cout<<"eff_num_data="<<eff_num_data<<endl;
	   cout<<"eff_denom_MC="<<eff_denom_MC<<endl;
	   cout<<"SF="<<eff_num_data/eff_denom_MC<<endl;*/


	   _triggerSF_weight_v2 = eff_num_data/eff_denom_MC;
	   
        }

	else if(abs((*_recolep_sel_pdg)[0])==11){

           int i_lep = -1;
           if(abs(eta_lep)<1.48) i_lep = 0;
           else if (abs(eta_lep)<2.1) i_lep = 1;

           float eff_L_ele_data = efficiency_from_TGraph(SingleE_eff_data[i_lep],pt_lep);
           float eff_l_ele_data = efficiency_from_TGraph(ETau_ele_eff_data[i_lep],pt_lep);

           float eff_L_ele_MC = efficiency_from_TGraph(SingleE_eff_MC[i_lep],pt_lep);
           float eff_l_ele_MC = efficiency_from_TGraph(ETau_ele_eff_MC[i_lep],pt_lep);


           int i_tau0_MC = -1;
	   int i_tau0_data = -1;
           if(abs(eta_tau0)<1.479){
	       i_tau0_MC = 0;
	       i_tau0_data = 0;
	   }
           else{
	       i_tau0_MC = 1;
	       i_tau0_data = 3;
	   }
	   if(DM_tau0==1) i_tau0_data +=1;
	   else if(DM_tau0==10) i_tau0_data +=2;

	   
           float eff_tau0_data = efficiency_from_TGraph(ETau_tau_eff_data[i_tau0_data],pt_tau0);
           float eff_tau0_MC = efficiency_from_TGraph(ETau_tau_eff_MC[i_tau0_MC],pt_tau0);

           int i_tau1_MC = -1;
           int i_tau1_data = -1;
           if(abs(eta_tau1)<1.479){
               i_tau1_MC = 0;
               i_tau1_data = 0;
           }
           else{
               i_tau1_MC = 1;
               i_tau1_data = 3;
           }
           if(DM_tau1==1) i_tau1_data +=1;
           else if(DM_tau1==10) i_tau1_data +=2;


           float eff_tau1_data = efficiency_from_TGraph(ETau_tau_eff_data[i_tau1_data],pt_tau1);
           float eff_tau1_MC = efficiency_from_TGraph(ETau_tau_eff_MC[i_tau1_MC],pt_tau1);

           float eff_num_data = 0.;
           float eff_denom_MC = 1.;

           if(isTrig_SingleEle && isTrig_ETau){
	     //eff_num_data = eff_L_ele_data*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     //eff_denom_MC = eff_L_ele_MC*(1. - (1.-eff_tau0_MC)*(1.-eff_tau1_MC));
	     eff_num_data = TMath::Min(eff_L_ele_data,eff_l_ele_data)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     eff_denom_MC = TMath::Min(eff_L_ele_MC,eff_l_ele_MC)*(1. - (1.-eff_tau0_MC)*(1.-eff_tau1_MC));
	   }
	   else if(isTrig_SingleEle &&!isTrig_ETau){
	     //eff_num_data = eff_L_ele_data*(1.-eff_tau0_data)*(1.-eff_tau1_data);
	     //eff_denom_MC = eff_L_ele_MC*(1.-eff_tau0_MC)*(1.-eff_tau1_MC);
	     eff_num_data = TMath::Max(1e-2,eff_L_ele_data - TMath::Min(eff_L_ele_data,eff_l_ele_data)*(1-(1.-eff_tau0_data)*(1.-eff_tau1_data)));
	     eff_denom_MC = TMath::Max(1e-2,eff_L_ele_MC - TMath::Min(eff_L_ele_MC,eff_l_ele_MC)*(1-(1.-eff_tau0_MC)*(1.-eff_tau1_MC)));
	   }
	   else if(!isTrig_SingleEle && isTrig_ETau){
	     //eff_num_data = (eff_l_ele_data-eff_L_ele_data)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     //eff_denom_MC = (eff_l_ele_MC-eff_L_ele_MC)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data));
	     eff_num_data = TMath::Max(1.e-2, (eff_l_ele_data-eff_L_ele_data)*(1. - (1.-eff_tau0_data)*(1.-eff_tau1_data)));
	     eff_denom_MC = TMath::Max(1.e-2, (eff_l_ele_MC-eff_L_ele_MC)*(1. - (1.-eff_tau0_MC)*(1.-eff_tau1_MC)));
	     
	   }

	   /*cout<<"isTrig_SingleEle="<<isTrig_SingleEle<<" isTrig_ETau="<<isTrig_ETau<<endl;
	   cout<<"eff_L_ele_data="<<eff_L_ele_data<<endl;
	       cout<<"eff_tau0_data="<<eff_tau0_data<<endl;
	       cout<<"eff_tau1_data="<<eff_tau1_data<<endl;
	       cout<<"eff_L_ele_MC="<<eff_L_ele_MC<<endl;
	       cout<<"eff_tau0_MC="<<eff_tau0_MC<<endl;
	       cout<<"eff_tau1_MC="<<eff_tau1_MC<<endl;
	       cout<<"eff_num_data="<<eff_num_data<<endl;
	       cout<<"eff_denom_MC="<<eff_denom_MC<<endl;
	       cout<<"SF="<<eff_num_data/eff_denom_MC<<endl;*/

           _triggerSF_weight_v2 = eff_num_data/eff_denom_MC;


        }
	}

      }

      
      tree_new->Fill();
      
    }

    f_new->cd();

    tree_new->Write();

  }


  f_new->Close();


  return;
    

}



void test_1l2tau_Xtrig(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_BDT_1l2tau.root";

  vector<TString> treename;
  treename.push_back("HTauTauTree_3l");
  
  add_trigger_filter_1l2tau_Xtrig(filein,"test.root",treename,false);  


}
