#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>


using namespace std;


void event_dumper(TString filename, TString treename, vector<int> events){

  TChain * tree = new TChain(treename);
  tree->Add(filename);

  vector<float> * _recolep_sel_px = 0;
  vector<float> * _recolep_sel_py = 0;
  vector<float> * _recolep_sel_pz = 0;
  vector<float> * _recolep_sel_e  = 0;
  vector<int> * _recolep_sel_pdg  = 0;

  vector<float> * _recotauh_sel_px = 0;
  vector<float> * _recotauh_sel_py = 0;
  vector<float> * _recotauh_sel_pz = 0;
  vector<float> * _recotauh_sel_e  = 0;
  vector<int> * _recotauh_sel_decayMode  = 0;

  float _PFMET = 0;
  float _PFMET_phi = 0;
  float _PFMETCov00 = 0;
  float _PFMETCov01 = 0;
  float _PFMETCov10 = 0;
  float _PFMETCov11 = 0;

  vector<float> * _recoPFJet_btag_px = 0;
  vector<float> * _recoPFJet_btag_py = 0;
  vector<float> * _recoPFJet_btag_pz = 0;
  vector<float> * _recoPFJet_btag_e = 0;

  int _n_recoPFJet_untag = 0;
  vector<float> * _recoPFJet_untag_px = 0;
  vector<float> * _recoPFJet_untag_py = 0;
  vector<float> * _recoPFJet_untag_pz = 0;
  vector<float> * _recoPFJet_untag_e = 0;

  int _n_pair_Wtag_recoPFJet_untag = 0;
  vector<float> * _recoPFJet_untag_Wtag_px = 0;
  vector<float> * _recoPFJet_untag_Wtag_py = 0;
  vector<float> * _recoPFJet_untag_Wtag_pz = 0;
  vector<float> * _recoPFJet_untag_Wtag_e = 0;

  tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
  tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
  tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
  tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
  tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);

  tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
  tree->SetBranchAddress("recotauh_sel_decayMode",&_recotauh_sel_decayMode);

  tree->SetBranchAddress("PFMET",&_PFMET);
  tree->SetBranchAddress("PFMET_phi",&_PFMET_phi);
  tree->SetBranchAddress("PFMETCov00",&_PFMETCov00);
  tree->SetBranchAddress("PFMETCov01",&_PFMETCov01);
  tree->SetBranchAddress("PFMETCov10",&_PFMETCov10);
  tree->SetBranchAddress("PFMETCov11",&_PFMETCov11);

  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);

  tree->SetBranchAddress("n_recoPFJet_untag",&_n_recoPFJet_untag);
  tree->SetBranchAddress("recoPFJet_untag_px",&_recoPFJet_untag_px);
  tree->SetBranchAddress("recoPFJet_untag_py",&_recoPFJet_untag_py);
  tree->SetBranchAddress("recoPFJet_untag_pz",&_recoPFJet_untag_pz);
  tree->SetBranchAddress("recoPFJet_untag_e",&_recoPFJet_untag_e);

  tree->SetBranchAddress("n_pair_Wtag_recoPFJet_untag",&_n_pair_Wtag_recoPFJet_untag);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);

  std::ofstream out("EventDump_ttH.py");
  out<<std::setprecision(9);


  out<<"\"\"\"Event list"<<'\n';
  out<<"Per event :"<<'\n';
  out<<" - leptons"<<'\n';
  out<<" - tau"<<'\n';
  out<<" - MET"<<'\n';
  out<<" - MET Cov. matrix"<<'\n';
  out<<" - 2 b-jets"<<'\n';
  out<<" - Untagged jets"<<'\n';
  out<<" - W-tagged jets"<<'\n';
  out<<"\"\"\""<<'\n';
  out<<'\n';
  out<<"Events = ["<<'\n';

  for(unsigned int i=0; i<events.size(); i++){

    tree->GetEntry(events[i]);



    out<<" {"<<'\n';

    out<<"  '_recolep_sel_px': ["<<(*_recolep_sel_px)[0]<<","<<(*_recolep_sel_px)[1]<<"],"<<'\n';
    out<<"  '_recolep_sel_py': ["<<(*_recolep_sel_py)[0]<<","<<(*_recolep_sel_py)[1]<<"],"<<'\n';
    out<<"  '_recolep_sel_pz': ["<<(*_recolep_sel_pz)[0]<<","<<(*_recolep_sel_pz)[1]<<"],"<<'\n';
    out<<"  '_recolep_sel_e': ["<<(*_recolep_sel_e)[0]<<","<<(*_recolep_sel_e)[1]<<"],"<<'\n';
    out<<"  '_recolep_sel_pdg': ["<<(*_recolep_sel_pdg)[0]<<","<<(*_recolep_sel_pdg)[1]<<"],"<<'\n';

    out<<"  '_recotauh_sel_px': ["<<(*_recotauh_sel_px)[0]<<"],"<<'\n';
    out<<"  '_recotauh_sel_py': ["<<(*_recotauh_sel_py)[0]<<"],"<<'\n';
    out<<"  '_recotauh_sel_pz': ["<<(*_recotauh_sel_pz)[0]<<"],"<<'\n';
    out<<"  '_recotauh_sel_e': ["<<(*_recotauh_sel_e)[0]<<"],"<<'\n';
    out<<"  '_recotauh_sel_decayMode': ["<<(*_recotauh_sel_decayMode)[0]<<"],"<<'\n';

    out<<"  '_PFMET': "<<_PFMET<<", '_PFMET_phi': "<<_PFMET_phi<<","<<'\n';
    out<<"  '_PFMETCov00': "<<_PFMETCov00<<", '_PFMETCov11': "<<_PFMETCov11<<","<<'\n';
    out<<"  '_PFMETCov01': "<<_PFMETCov01<<", '_PFMETCov10': "<<_PFMETCov10<<","<<'\n';


    out<<"  '_recoPFJet_btag_px': ["<<(*_recoPFJet_btag_px)[0]<<","<<(*_recoPFJet_btag_px)[1]<<"],"<<'\n';
    out<<"  '_recoPFJet_btag_py': ["<<(*_recoPFJet_btag_py)[0]<<","<<(*_recoPFJet_btag_py)[1]<<"],"<<'\n';
    out<<"  '_recoPFJet_btag_pz': ["<<(*_recoPFJet_btag_pz)[0]<<","<<(*_recoPFJet_btag_pz)[1]<<"],"<<'\n';
    out<<"  '_recoPFJet_btag_e': ["<<(*_recoPFJet_btag_e)[0]<<","<<(*_recoPFJet_btag_e)[1]<<"],"<<'\n';



    out<<"  '_n_recoPFJet_untag': "<<_n_recoPFJet_untag<<","<<'\n';
    out<<"  '_recoPFJet_untag_px': [";
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_untag_px).size();i_jet++){
      out<<(*_recoPFJet_untag_px)[i_jet];
      if(i_jet<(*_recoPFJet_untag_px).size()-1)
	out<<",";
    }
    out<<"],"<<'\n';
    out<<"  '_recoPFJet_untag_py': [";
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_untag_py).size();i_jet++){
      out<<(*_recoPFJet_untag_py)[i_jet];
      if(i_jet<(*_recoPFJet_untag_py).size()-1)
	out<<",";
    }
    out<<"],"<<'\n';
out<<"  '_recoPFJet_untag_pz': [";
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_untag_pz).size();i_jet++){
      out<<(*_recoPFJet_untag_pz)[i_jet];
      if(i_jet<(*_recoPFJet_untag_pz).size()-1)
	out<<",";
    }
    out<<"],"<<'\n';
    out<<"  '_recoPFJet_untag_e': [";
    for(unsigned int i_jet=0;i_jet<(*_recoPFJet_untag_e).size();i_jet++){
      out<<(*_recoPFJet_untag_e)[i_jet];
      if(i_jet<(*_recoPFJet_untag_e).size()-1)
	out<<",";
    }
    out<<"],"<<'\n';


    out<<"  '_n_pair_Wtag_recoPFJet_untag': "<<_n_pair_Wtag_recoPFJet_untag<<","<<'\n';
    out<<"  '_recoPFJet_untag_Wtag_px': ["<<(*_recoPFJet_untag_Wtag_px)[0]<<","<<(*_recoPFJet_untag_Wtag_px)[1]<<"],"<<'\n';
    out<<"  '_recoPFJet_untag_Wtag_py': ["<<(*_recoPFJet_untag_Wtag_py)[0]<<","<<(*_recoPFJet_untag_Wtag_py)[1]<<"],"<<'\n';
    out<<"  '_recoPFJet_untag_Wtag_pz': ["<<(*_recoPFJet_untag_Wtag_pz)[0]<<","<<(*_recoPFJet_untag_Wtag_pz)[1]<<"],"<<'\n';
    out<<"  '_recoPFJet_untag_Wtag_e': ["<<(*_recoPFJet_untag_Wtag_e)[0]<<","<<(*_recoPFJet_untag_Wtag_e)[1]<<"]"<<'\n';

    out<<" }";
    if(i<events.size()-1)
      out<<",";
    out<<'\n';



  }

  out<<"]";


  return;


}




void test(){

  TString filename = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root";
  
  vector<int> events;
  events.push_back(14);
  events.push_back(17);
  

  event_dumper(filename,"T",events);
  return;

}
