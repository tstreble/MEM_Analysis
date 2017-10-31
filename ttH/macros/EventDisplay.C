#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLorentzVector.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TLatex.h>
#include <iostream>

using namespace std;



void event_display(TString filename, TString treename, int event_number, bool draw_leg=false){


  TChain * tree = new TChain(treename);
  tree->Add(filename);

  vector<float> *_gentop_e = 0;
  vector<float> *_gentop_px = 0;
  vector<float> *_gentop_py = 0;
  vector<float> *_gentop_pz = 0;
  vector<int> *_gentop_decayMode = 0;


  vector<float> *_genH_e = 0;
  vector<float> *_genH_px = 0;
  vector<float> *_genH_py = 0;
  vector<float> *_genH_pz = 0;

  vector<float> *_genZ_e = 0;
  vector<float> *_genZ_px = 0;
  vector<float> *_genZ_py = 0;
  vector<float> *_genZ_pz = 0;
  vector<int> *_genZ_decayMode = 0;

  vector<float> *_genW_e = 0;
  vector<float> *_genW_px = 0;
  vector<float> *_genW_py = 0;
  vector<float> *_genW_pz = 0;
  vector<int> *_genW_TopMothInd = 0;


  vector<float> *_genb_e = 0;
  vector<float> *_genb_px = 0;
  vector<float> *_genb_py = 0;
  vector<float> *_genb_pz = 0;
  vector<int> *_genb_TopMothInd = 0;
  vector<int> *_genb_WMothInd = 0;
  vector<int> *_genb_flags = 0;

  vector<float> *_genq_e = 0;
  vector<float> *_genq_px = 0;
  vector<float> *_genq_py = 0;
  vector<float> *_genq_pz = 0;
  vector<int> *_genq_TopMothInd = 0;
  vector<int> *_genq_WMothInd = 0;
  vector<int> *_genq_flags = 0;

  vector<int> *_gentau_flags = 0;
  vector<int> *_gentau_HMothInd = 0;
  vector<int> *_gentau_ZMothInd = 0;
  vector<int> *_gentau_WMothInd = 0;
  vector<int> *_gentau_TopMothInd = 0;
  vector<int> *_gentau_decayMode = 0;

  vector<float> *_genlep_e = 0;
  vector<float> *_genlep_px = 0;
  vector<float> *_genlep_py = 0;
  vector<float> *_genlep_pz = 0;
  vector<int> *_genlep_TopMothInd = 0;
  vector<int> *_genlep_WMothInd = 0;
  vector<int> *_genlep_TauMothInd = 0;
  vector<int> *_genlep_ZMothInd = 0;
  vector<int> *_genlep_flags = 0;
  vector<int> *_genlep_pdg = 0;
  
  vector<float> *_gentauh_e = 0;
  vector<float> *_gentauh_px = 0;
  vector<float> *_gentauh_py = 0;
  vector<float> *_gentauh_pz = 0;
  vector<int> *_gentauh_TauMothInd = 0;
  vector<int> *_gentauh_flags = 0;

  vector<float> *_recoPFJet_e = 0;
  vector<float> *_recoPFJet_px = 0;
  vector<float> *_recoPFJet_py = 0;
  vector<float> *_recoPFJet_pz = 0;
  vector<float> *_recoPFJet_CSVscore = 0;

  vector<float> *_recolep_e = 0;
  vector<float> *_recolep_px = 0;
  vector<float> *_recolep_py = 0;
  vector<float> *_recolep_pz = 0;
  vector<int> *_recolep_pdg = 0;

  vector<float> *_recotauh_e = 0;
  vector<float> *_recotauh_px = 0;
  vector<float> *_recotauh_py = 0;
  vector<float> *_recotauh_pz = 0;

  tree->SetBranchAddress("gentop_e",&_gentop_e);
  tree->SetBranchAddress("gentop_px",&_gentop_px);
  tree->SetBranchAddress("gentop_py",&_gentop_py);
  tree->SetBranchAddress("gentop_pz",&_gentop_pz);
  tree->SetBranchAddress("gentop_decayMode",&_gentop_decayMode);

  tree->SetBranchAddress("genH_e",&_genH_e);
  tree->SetBranchAddress("genH_px",&_genH_px);
  tree->SetBranchAddress("genH_py",&_genH_py);
  tree->SetBranchAddress("genH_pz",&_genH_pz);

  /*tree->SetBranchAddress("genZ_e",&_genZ_e);
  tree->SetBranchAddress("genZ_px",&_genZ_px);
  tree->SetBranchAddress("genZ_py",&_genZ_py);
  tree->SetBranchAddress("genZ_pz",&_genZ_pz);
  tree->SetBranchAddress("genZ_decayMode",&_genZ_decayMode);*/


  tree->SetBranchAddress("genW_e",&_genW_e);
  tree->SetBranchAddress("genW_px",&_genW_px);
  tree->SetBranchAddress("genW_py",&_genW_py);
  tree->SetBranchAddress("genW_pz",&_genW_pz);
  tree->SetBranchAddress("genW_TopMothInd",&_genW_TopMothInd);

  tree->SetBranchAddress("genb_e",&_genb_e);
  tree->SetBranchAddress("genb_px",&_genb_px);
  tree->SetBranchAddress("genb_py",&_genb_py);
  tree->SetBranchAddress("genb_pz",&_genb_pz);
  tree->SetBranchAddress("genb_WMothInd",&_genb_WMothInd);
  tree->SetBranchAddress("genb_TopMothInd",&_genb_TopMothInd);
  tree->SetBranchAddress("genb_flags",&_genb_flags);

  tree->SetBranchAddress("genq_e",&_genq_e);
  tree->SetBranchAddress("genq_px",&_genq_px);
  tree->SetBranchAddress("genq_py",&_genq_py);
  tree->SetBranchAddress("genq_pz",&_genq_pz);
  tree->SetBranchAddress("genq_WMothInd",&_genq_WMothInd);
  tree->SetBranchAddress("genq_TopMothInd",&_genq_TopMothInd);
  tree->SetBranchAddress("genq_flags",&_genq_flags);

  tree->SetBranchAddress("gentau_flags",&_gentau_flags);
  tree->SetBranchAddress("gentau_HMothInd",&_gentau_HMothInd);
  tree->SetBranchAddress("gentau_WMothInd",&_gentau_WMothInd);
  //tree->SetBranchAddress("gentau_ZMothInd",&_gentau_ZMothInd);
  tree->SetBranchAddress("gentau_TopMothInd",&_gentau_TopMothInd);
  tree->SetBranchAddress("gentau_decayMode",&_gentau_decayMode);

  tree->SetBranchAddress("genlep_e",&_genlep_e);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  //tree->SetBranchAddress("genlep_ZMothInd",&_genlep_ZMothInd);
  tree->SetBranchAddress("genlep_WMothInd",&_genlep_WMothInd);
  tree->SetBranchAddress("genlep_TopMothInd",&_genlep_TopMothInd);
  tree->SetBranchAddress("genlep_TauMothInd",&_genlep_TauMothInd);
  tree->SetBranchAddress("genlep_flags",&_genlep_flags);
  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);

  tree->SetBranchAddress("gentauh_e",&_gentauh_e);
  tree->SetBranchAddress("gentauh_px",&_gentauh_px);
  tree->SetBranchAddress("gentauh_py",&_gentauh_py);
  tree->SetBranchAddress("gentauh_pz",&_gentauh_pz);
  tree->SetBranchAddress("gentauh_TauMothInd",&_gentauh_TauMothInd);
  tree->SetBranchAddress("gentauh_flags",&_gentauh_flags);

  tree->SetBranchAddress("recoPFJet_e",&_recoPFJet_e);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_CSVscore",&_recoPFJet_CSVscore);

  tree->SetBranchAddress("recolep_e",&_recolep_e);
  tree->SetBranchAddress("recolep_px",&_recolep_px);
  tree->SetBranchAddress("recolep_py",&_recolep_py);
  tree->SetBranchAddress("recolep_pz",&_recolep_pz);
  tree->SetBranchAddress("recolep_pdg",&_recolep_pdg);

  tree->SetBranchAddress("recotauh_e",&_recotauh_e);
  tree->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree->SetBranchAddress("recotauh_pz",&_recotauh_pz);

  tree->GetEntry(event_number);

  //Gen info
  
  vector<TGraphErrors*> gentop;
  vector<TGraphErrors*> genW;
  vector<TGraphErrors*> genHiggs;
  vector<TGraphErrors*> genZ;
  vector<TGraphErrors*> genb;
  vector<TGraphErrors*> genq;
  vector<TGraphErrors*> genlep;
  vector<TGraphErrors*> gentauh;

  vector<TLatex*> genpt;

  for(unsigned int i_top=0;i_top<(*_gentop_e).size();i_top++){

    TLorentzVector top_tlv( (*_gentop_px)[i_top], (*_gentop_py)[i_top], (*_gentop_pz)[i_top], (*_gentop_e)[i_top]);

    TGraphErrors* top_gr = new TGraphErrors();
    top_gr->SetPoint(0,top_tlv.Eta(),top_tlv.Phi());
    top_gr->SetMarkerStyle(28);
    top_gr->SetMarkerColor(i_top+2);
    top_gr->SetMarkerSize(2);
    gentop.push_back(top_gr);
    
    
    if((*_gentop_decayMode)[i_top]==0){  // Hadronic top

	int i_bh = -1;
	int i_q1 = -1;
	int i_q2 = -1;

	for(unsigned int i_b=0; i_b<(*_genb_e).size(); i_b++){

	  bool isFromHardProcess = ( (*_genb_flags)[i_b] >> 8 ) & 1;
	  int TopMothInd = (*_genb_TopMothInd)[i_b];
	  int WMothInd = (*_genb_WMothInd)[i_b];

	  if( !( TopMothInd==i_top && WMothInd==-1 && isFromHardProcess ) )
	    continue;

	  i_bh = i_b;

	}

	for(unsigned int i_q=0; i_q<(*_genq_e).size(); i_q++){

	  bool isFromHardProcess = ( (*_genq_flags)[i_q] >> 8 ) & 1;
	  int TopMothInd = (*_genq_TopMothInd)[i_q];
	  int WMothInd = (*_genq_WMothInd)[i_q];

	  if( !( TopMothInd==i_top && WMothInd>=0 && isFromHardProcess ) )
	    continue;

	  if(i_q1==-1)
	    i_q1=i_q;
	  else
	    i_q2=i_q;
	  
	}

	
	TLorentzVector bh_tlv((*_genb_px)[i_bh],(*_genb_py)[i_bh],(*_genb_pz)[i_bh],(*_genb_e)[i_bh]);
	TLorentzVector q1_tlv((*_genq_px)[i_q1],(*_genq_py)[i_q1],(*_genq_pz)[i_q1],(*_genq_e)[i_q1]);
	TLorentzVector q2_tlv((*_genq_px)[i_q2],(*_genq_py)[i_q2],(*_genq_pz)[i_q2],(*_genq_e)[i_q2]);

	TGraphErrors* bh_gr = new TGraphErrors();
	bh_gr->SetPoint(0,bh_tlv.Eta(),bh_tlv.Phi());
	bh_gr->SetMarkerStyle(24);
	bh_gr->SetMarkerColor(i_top+2);
	bh_gr->SetMarkerSize(2);
	genb.push_back(bh_gr);

	TLatex *bh_pt = new TLatex(bh_tlv.Eta()+0.1,bh_tlv.Phi()+0.1,Form("%.0f GeV",bh_tlv.Pt()));
	bh_pt->SetTextSize(0.03);
	genpt.push_back(bh_pt);

	TGraphErrors* q1_gr = new TGraphErrors();
	q1_gr->SetPoint(0,q1_tlv.Eta(),q1_tlv.Phi());
	q1_gr->SetMarkerStyle(25);
	q1_gr->SetMarkerColor(i_top+2);
	q1_gr->SetMarkerSize(2);
	genq.push_back(q1_gr);

	TLatex *q1_pt = new TLatex(q1_tlv.Eta()+0.15,q1_tlv.Phi()+0.15,Form("%.0f GeV",q1_tlv.Pt()));
	q1_pt->SetTextSize(0.03);
	genpt.push_back(q1_pt);

	TGraphErrors* q2_gr = new TGraphErrors();
	q2_gr->SetPoint(0,q2_tlv.Eta(),q2_tlv.Phi());
	q2_gr->SetMarkerStyle(25);
	q2_gr->SetMarkerColor(i_top+2);
	q2_gr->SetMarkerSize(2);
	genq.push_back(q2_gr);

	TLatex *q2_pt = new TLatex(q2_tlv.Eta()+0.15,q2_tlv.Phi()+0.15,Form("%.0f GeV",q2_tlv.Pt()));
	q2_pt->SetTextSize(0.03);
	genpt.push_back(q2_pt);
    
    }


    else{


      int i_bl = -1;
      int i_lt = -1;
      int ipi = -1;
      
      for(int i_b=0; i_b<(*_genb_e).size(); i_b++){
	
	bool isFromHardProcess = ( (*_genb_flags)[i_b] >> 8 ) & 1;
	int TopMothInd = (*_genb_TopMothInd)[i_b];
	int WMothInd = (*_genb_WMothInd)[i_b];
	
	if( !( TopMothInd==i_top && WMothInd==-1 && isFromHardProcess ) )
	  continue;
	
	i_bl = i_b;
	
      }

      for(int i_lep=0; i_lep<(*_genlep_e).size(); i_lep++){
	
	bool isFromHardProcess = ( (*_genlep_flags)[i_lep] >> 8 ) & 1;
	int TopMothInd = (*_genlep_TopMothInd)[i_lep];
	int WMothInd = (*_genlep_WMothInd)[i_lep];
     
	if( !(TopMothInd == i_top && WMothInd>=0 && isFromHardProcess)) continue;

	i_lt = i_lep;

      }


      if(i_lt==-1){

	for(int itau=0; itau<(*_gentau_flags).size(); itau++){

	  bool isFromHardProcess = ( (*_gentau_flags)[itau] >> 8 ) & 1;
	  int TopMothInd = (*_gentau_TopMothInd)[itau];
	  int decayMode = (*_gentau_decayMode)[itau];
	  bool isLastCopy = ( (*_gentau_flags)[itau] >> 13 ) & 1;


	  if( !( TopMothInd == i_top && isFromHardProcess && isLastCopy) )
	    continue;
	  
	  if(decayMode==0 || decayMode==1){
	
	    for(int ilep=0; ilep<(*_genlep_e).size(); ilep++){
	  
	      bool isDirectTauDecayProduct = ( (*_genlep_flags)[ilep] >> 4) & 1;
	      bool isHardProcessTauDecayProduct = ( (*_genlep_flags)[ilep] >> 9) & 1;
	      int TauMothInd = (*_genlep_TauMothInd)[ilep];
     
	      if( TauMothInd == itau && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
		i_lt = ilep;

	    }

	  }

	  else{

	    for(int itauh=0; itauh<(*_gentauh_e).size(); itauh++){

	      int flag_Mother = (*_gentau_flags)[(*_gentauh_TauMothInd)[itauh]];
	      bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
	      bool isMotherLastCopy = (flag_Mother >> 13) & 1;
	      int TauMothInd = (*_gentauh_TauMothInd)[itauh];
	      
	      if( TauMothInd == itau && isMotherFromHardProcess && isMotherLastCopy)
		ipi = itauh;
	  
	    } 

	    TLorentzVector tauh_tlv((*_gentauh_px)[ipi], (*_gentauh_py)[ipi], (*_gentauh_pz)[ipi], (*_gentauh_e)[ipi]);

	    TGraphErrors* tauh_gr = new TGraphErrors();
	    tauh_gr->SetPoint(0,tauh_tlv.Eta(),tauh_tlv.Phi());
	    tauh_gr->SetMarkerStyle(27);    
	    tauh_gr->SetMarkerColor(i_top+2);
	    tauh_gr->SetMarkerSize(2);
	    gentauh.push_back(tauh_gr);

	    TLatex *tauh_pt = new TLatex(tauh_tlv.Eta()+0.1,tauh_tlv.Phi()+0.1,Form("%.0f GeV",tauh_tlv.Pt()));
	    tauh_pt->SetTextSize(0.03);
	    genpt.push_back(tauh_pt);   

	  }
	
	}

      }

      TLorentzVector bl_tlv((*_genb_px)[i_bl],(*_genb_py)[i_bl],(*_genb_pz)[i_bl],(*_genb_e)[i_bl]);

      TGraphErrors* bl_gr = new TGraphErrors();
      bl_gr->SetPoint(0,bl_tlv.Eta(),bl_tlv.Phi());
      bl_gr->SetMarkerStyle(24);
      bl_gr->SetMarkerColor(i_top+2);
      bl_gr->SetMarkerSize(2);
      genb.push_back(bl_gr);

      TLatex *bl_pt = new TLatex(bl_tlv.Eta()+0.1,bl_tlv.Phi()+0.1,Form("%.0f GeV",bl_tlv.Pt()));
      bl_pt->SetTextSize(0.03);
      genpt.push_back(bl_pt);
      
      
      if(i_lt>=0){
	TLorentzVector lt_tlv((*_genlep_px)[i_lt],(*_genlep_py)[i_lt],(*_genlep_pz)[i_lt],(*_genlep_e)[i_lt]);
	
	TGraphErrors* lt_gr = new TGraphErrors();
	lt_gr->SetPoint(0,lt_tlv.Eta(),lt_tlv.Phi());
	if(abs((*_genlep_pdg)[i_lt])==11)
	  lt_gr->SetMarkerStyle(26);
	else if(abs((*_genlep_pdg)[i_lt])==13)
	  lt_gr->SetMarkerStyle(32);      
	lt_gr->SetMarkerColor(i_top+2);
	lt_gr->SetMarkerSize(2);
	genlep.push_back(lt_gr);
	
	TLatex *lt_pt = new TLatex(lt_tlv.Eta()+0.15,lt_tlv.Phi()+0.15,Form("%.0f GeV",lt_tlv.Pt()));
	lt_pt->SetTextSize(0.03);
	genpt.push_back(lt_pt);      

      }

    }


  }


  for(unsigned int i_W=0;i_W<(*_genW_e).size();i_W++){

    if((*_genW_TopMothInd)[i_W]>=0) continue;

    TLorentzVector W_tlv( (*_genW_px)[i_W], (*_genW_py)[i_W], (*_genW_pz)[i_W], (*_genW_e)[i_W]);
    TGraphErrors* W_gr = new TGraphErrors();
    W_gr->SetPoint(0,W_tlv.Eta(),W_tlv.Phi());
    W_gr->SetMarkerStyle(31);
    W_gr->SetMarkerColor(i_W+(*_gentop_e).size()+2);
    W_gr->SetMarkerSize(2);
    genW.push_back(W_gr);

    int i_lW = -1;

    for(int i_lep=0; i_lep<(*_genlep_e).size(); i_lep++){
	
      bool isFromHardProcess = ( (*_genlep_flags)[i_lep] >> 8 ) & 1;
      int WMothInd = (*_genlep_WMothInd)[i_lep];
     
      if( !(WMothInd==i_W && isFromHardProcess)) continue;

      i_lW = i_lep;

    }


    if(i_lW==-1){

      for(int itau=0; itau<(*_gentau_flags).size(); itau++){
	
	bool isFromHardProcess = ( (*_gentau_flags)[itau] >> 8 ) & 1;
	int WMothInd = (*_gentau_WMothInd)[itau];
	int decayMode = (*_gentau_decayMode)[itau];
	bool isLastCopy = ( (*_gentau_flags)[itau] >> 13 ) & 1;
	  
	
	if( !( WMothInd==i_W && isFromHardProcess && isLastCopy) )
	  continue;
	
	if(decayMode==0 || decayMode==1){
	  
	  for(int ilep=0; ilep<(*_genlep_e).size(); ilep++){
	    
	    bool isDirectTauDecayProduct = ( (*_genlep_flags)[ilep] >> 4) & 1;
	    bool isHardProcessTauDecayProduct = ( (*_genlep_flags)[ilep] >> 9) & 1;
	    int TauMothInd = (*_genlep_TauMothInd)[ilep];
	    
	    if( TauMothInd == itau && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
	      i_lW = ilep;

	  }
	  
	}
	
	else{
	  
	  int ipi=-1;

	  for(int itauh=0; itauh<(*_gentauh_e).size(); itauh++){
	    
	    int flag_Mother = (*_gentau_flags)[(*_gentauh_TauMothInd)[itauh]];
	    bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
	    bool isMotherLastCopy = (flag_Mother >> 13) & 1;
	    int TauMothInd = (*_gentauh_TauMothInd)[itauh];
	    
	    if( TauMothInd == itau && isMotherFromHardProcess && isMotherLastCopy)
	      ipi = itauh;
	    
	  } 
	  
	  TLorentzVector tauh_tlv((*_gentauh_px)[ipi], (*_gentauh_py)[ipi], (*_gentauh_pz)[ipi], (*_gentauh_e)[ipi]);
	  
	  TGraphErrors* tauh_gr = new TGraphErrors();
	  tauh_gr->SetPoint(0,tauh_tlv.Eta(),tauh_tlv.Phi());
	  tauh_gr->SetMarkerStyle(27);      
	  tauh_gr->SetMarkerColor(i_W+(*_gentop_e).size()+2);
	  tauh_gr->SetMarkerSize(2);
	  gentauh.push_back(tauh_gr);
	  
	  TLatex *tauh_pt = new TLatex(tauh_tlv.Eta()+0.1,tauh_tlv.Phi()+0.1,Form("%.0f GeV",tauh_tlv.Pt()));
	  tauh_pt->SetTextSize(0.03);
	  genpt.push_back(tauh_pt);   
	  
	}
	
      }
      
    }

    if(i_lW>=0){
      TLorentzVector lW_tlv((*_genlep_px)[i_lW],(*_genlep_py)[i_lW],(*_genlep_pz)[i_lW],(*_genlep_e)[i_lW]);
	
      TGraphErrors* lW_gr = new TGraphErrors();
      lW_gr->SetPoint(0,lW_tlv.Eta(),lW_tlv.Phi());
      if(abs((*_genlep_pdg)[i_lW])==11)
	lW_gr->SetMarkerStyle(26);
      else if(abs((*_genlep_pdg)[i_lW])==13)
	lW_gr->SetMarkerStyle(32);      
      lW_gr->SetMarkerColor(i_W+(*_gentop_e).size()+2);
      lW_gr->SetMarkerSize(2);
      genlep.push_back(lW_gr);
	
      TLatex *lW_pt = new TLatex(lW_tlv.Eta()+0.15,lW_tlv.Phi()+0.15,Form("%.0f GeV",lW_tlv.Pt()));
      lW_pt->SetTextSize(0.03);
      genpt.push_back(lW_pt);      

    }
    
    int i_q1 = -1;
    int i_q2 = -1;   

    for(unsigned int i_q=0; i_q<(*_genq_e).size(); i_q++){

      bool isFromHardProcess = ( (*_genq_flags)[i_q] >> 8 ) & 1;
      int WMothInd = (*_genq_WMothInd)[i_q];

      if( !( WMothInd==i_W && isFromHardProcess ) )
	    continue;

      if(i_q1==-1)
	i_q1=i_q;
      else
	i_q2=i_q;
      
    }


    if(i_q2>=0){

      TLorentzVector q1_tlv((*_genq_px)[i_q1],(*_genq_py)[i_q1],(*_genq_pz)[i_q1],(*_genq_e)[i_q1]);
      TLorentzVector q2_tlv((*_genq_px)[i_q2],(*_genq_py)[i_q2],(*_genq_pz)[i_q2],(*_genq_e)[i_q2]);
      
      TGraphErrors* q1_gr = new TGraphErrors();
      q1_gr->SetPoint(0,q1_tlv.Eta(),q1_tlv.Phi());
      q1_gr->SetMarkerStyle(25);
      q1_gr->SetMarkerColor(i_W+(*_gentop_e).size()+2);
      q1_gr->SetMarkerSize(2);
      genq.push_back(q1_gr);
      
      TLatex *q1_pt = new TLatex(q1_tlv.Eta()+0.15,q1_tlv.Phi()+0.15,Form("%.0f GeV",q1_tlv.Pt()));
      q1_pt->SetTextSize(0.03);
      genpt.push_back(q1_pt);
      
      TGraphErrors* q2_gr = new TGraphErrors();
      q2_gr->SetPoint(0,q2_tlv.Eta(),q2_tlv.Phi());
      q2_gr->SetMarkerStyle(25);
      q2_gr->SetMarkerColor(i_W+(*_gentop_e).size()+2);
      q2_gr->SetMarkerSize(2);
      genq.push_back(q2_gr);
      
      TLatex *q2_pt = new TLatex(q2_tlv.Eta()+0.15,q2_tlv.Phi()+0.15,Form("%.0f GeV",q2_tlv.Pt()));
      q2_pt->SetTextSize(0.03);
      genpt.push_back(q2_pt);

    }

  }



  for(unsigned int i_H=0;i_H<(*_genH_e).size();i_H++){

    if(i_H==1) break;

    TLorentzVector H_tlv( (*_genH_px)[i_H], (*_genH_py)[i_H], (*_genH_pz)[i_H], (*_genH_e)[i_H]);

    TGraphErrors* H_gr = new TGraphErrors();
    H_gr->SetPoint(0,H_tlv.Eta(),H_tlv.Phi());
    H_gr->SetMarkerStyle(30);
    H_gr->SetMarkerColor(i_H+genW.size()+(*_gentop_e).size()+2);
    H_gr->SetMarkerSize(2);
    genHiggs.push_back(H_gr);


    for(int itau=0; itau<(*_gentau_flags).size(); itau++){

      bool isFromHardProcess = ( (*_gentau_flags)[itau] >> 8 ) & 1;
      int HMothInd = (*_gentau_HMothInd)[itau];
      int decayMode = (*_gentau_decayMode)[itau];
      bool isLastCopy = ( (*_gentau_flags)[itau] >> 13 ) & 1;

      if( !( HMothInd==1 && isFromHardProcess && isLastCopy) )
	continue;
     
      if(decayMode==0 || decayMode==1){
	
	int ilep_tau = -1;

	for(int ilep=0; ilep<(*_genlep_e).size(); ilep++){
	  
	  bool isDirectTauDecayProduct = ( (*_genlep_flags)[ilep] >> 4) & 1;
	  bool isHardProcessTauDecayProduct = ( (*_genlep_flags)[ilep] >> 9) & 1;
	  int TauMothInd = (*_genlep_TauMothInd)[ilep];
     
	  if( TauMothInd == itau && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
	    ilep_tau = ilep;

	}

	
	TLorentzVector ltau_tlv((*_genlep_px)[ilep_tau], (*_genlep_py)[ilep_tau], (*_genlep_pz)[ilep_tau], (*_genlep_e)[ilep_tau]);
	
	TGraphErrors* ltau_gr = new TGraphErrors();
	ltau_gr->SetPoint(0,ltau_tlv.Eta(),ltau_tlv.Phi());
	if(abs((*_genlep_pdg)[ilep_tau])==11)
	  ltau_gr->SetMarkerStyle(26);
	else if(abs((*_genlep_pdg)[ilep_tau])==13)
	  ltau_gr->SetMarkerStyle(32);      
	ltau_gr->SetMarkerColor(i_H+(*_gentop_e).size()+2);
	ltau_gr->SetMarkerSize(2);
	genlep.push_back(ltau_gr);

	TLatex *ltau_pt = new TLatex(ltau_tlv.Eta()+0.15,ltau_tlv.Phi()+0.15,Form("%.0f GeV",ltau_tlv.Pt()));
	ltau_pt->SetTextSize(0.03);
	genpt.push_back(ltau_pt);   
    
      }

      else{

	int ipi=-1;

	for(int itauh=0; itauh<(*_gentauh_e).size(); itauh++){

	  int flag_Mother = (*_gentau_flags)[(*_gentauh_TauMothInd)[itauh]];
	  bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
	  bool isMotherLastCopy = (flag_Mother >> 13) & 1;
	  int TauMothInd = (*_gentauh_TauMothInd)[itauh];
	  
	  if( TauMothInd == itau && isMotherFromHardProcess && isMotherLastCopy)
	    ipi = itauh;
	  
	} 

	TLorentzVector tauh_tlv((*_gentauh_px)[ipi], (*_gentauh_py)[ipi], (*_gentauh_pz)[ipi], (*_gentauh_e)[ipi]);


	TGraphErrors* tauh_gr = new TGraphErrors();
	tauh_gr->SetPoint(0,tauh_tlv.Eta(),tauh_tlv.Phi());
	tauh_gr->SetMarkerStyle(27);      
	tauh_gr->SetMarkerColor(i_H+(*_gentop_e).size()+2);
	tauh_gr->SetMarkerSize(2);
	gentauh.push_back(tauh_gr);

	TLatex *tauh_pt = new TLatex(tauh_tlv.Eta()+0.1,tauh_tlv.Phi()+0.1,Form("%.0f GeV",tauh_tlv.Pt()));
	tauh_pt->SetTextSize(0.03);
	genpt.push_back(tauh_pt);   

      }


    }


  }


  /*for(unsigned int i_Z=0;i_Z<(*_genZ_e).size();i_Z++){

    TLorentzVector Z_tlv( (*_genZ_px)[i_Z], (*_genZ_py)[i_Z], (*_genZ_pz)[i_Z], (*_genZ_e)[i_Z]);


    TGraphErrors* Z_gr = new TGraphErrors();
    Z_gr->SetPoint(0,Z_tlv.Eta(),Z_tlv.Phi());
    Z_gr->SetMarkerStyle(30);
    Z_gr->SetMarkerColor(i_Z+genHiggs.size()+genW.size()+(*_gentop_e).size()+2);
    Z_gr->SetMarkerSize(2);
    genZ.push_back(Z_gr);

    if((*_genZ_decayMode)[i_Z]<=5){

      for(int itau=0; itau<(*_gentau_flags).size(); itau++){
	
	bool isFromHardProcess = ( (*_gentau_flags)[itau] >> 8 ) & 1;
	int ZMothInd = (*_gentau_ZMothInd)[itau];
	int decayMode = (*_gentau_decayMode)[itau];
	
	if( !( ZMothInd==i_Z && isFromHardProcess ) )
	  continue;
	

	if(decayMode==0 || decayMode==1){
	  
	  int ilep_tau = -1;
	  
	  for(int ilep=0; ilep<(*_genlep_e).size(); ilep++){
	    
	    bool isDirectTauDecayProduct = ( (*_genlep_flags)[ilep] >> 4) & 1;
	    bool isHardProcessTauDecayProduct = ( (*_genlep_flags)[ilep] >> 9) & 1;
	    int TauMothInd = (*_genlep_TauMothInd)[ilep];
	    
	    if( TauMothInd == itau && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
	      ilep_tau = ilep;
	    
	  }
	  
	  
	  TLorentzVector ltau_tlv((*_genlep_px)[ilep_tau], (*_genlep_py)[ilep_tau], (*_genlep_pz)[ilep_tau], (*_genlep_e)[ilep_tau]);
	  
	  TGraphErrors* ltau_gr = new TGraphErrors();
	  ltau_gr->SetPoint(0,ltau_tlv.Eta(),ltau_tlv.Phi());
	  if(abs((*_genlep_pdg)[ilep_tau])==11)
	    ltau_gr->SetMarkerStyle(26);
	  else if(abs((*_genlep_pdg)[ilep_tau])==13)
	    ltau_gr->SetMarkerStyle(32);      
	  ltau_gr->SetMarkerColor(i_Z+genHiggs.size()+(*_gentop_e).size()+2);
	  ltau_gr->SetMarkerSize(2);
	  genlep.push_back(ltau_gr);
	  
	  TLatex *ltau_pt = new TLatex(ltau_tlv.Eta()+0.15,ltau_tlv.Phi()+0.15,Form("%.0f GeV",ltau_tlv.Pt()));
	  ltau_pt->SetTextSize(0.03);
	  genpt.push_back(ltau_pt);   
	  
	}
	
	else{
	  
	  int ipi=-1;
	  
	  for(int itauh=0; itauh<(*_gentauh_e).size(); itauh++){
	    
	    int flag_Mother = (*_gentau_flags)[(*_gentauh_TauMothInd)[itauh]];
	    bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;
	    int TauMothInd = (*_gentauh_TauMothInd)[itauh];
	    
	    if( TauMothInd == itau && isMotherFromHardProcess )
	      ipi = itauh;
	    
	  } 
	  
	  TLorentzVector tauh_tlv((*_gentauh_px)[ipi], (*_gentauh_py)[ipi], (*_gentauh_pz)[ipi], (*_gentauh_e)[ipi]);
	  
	  
	  TGraphErrors* tauh_gr = new TGraphErrors();
	  tauh_gr->SetPoint(0,tauh_tlv.Eta(),tauh_tlv.Phi());
	  tauh_gr->SetMarkerStyle(27);      
	  tauh_gr->SetMarkerColor(i_Z+genHiggs.size()+(*_gentop_e).size()+2);
	  tauh_gr->SetMarkerSize(2);
	  gentauh.push_back(tauh_gr);
	  
	  TLatex *tauh_pt = new TLatex(tauh_tlv.Eta()+0.1,tauh_tlv.Phi()+0.1,Form("%.0f GeV",tauh_tlv.Pt()));
	tauh_pt->SetTextSize(0.03);
	genpt.push_back(tauh_pt);   
	
	}
	
	
      }

    }


    else if((*_genZ_decayMode)[i_Z]==6 || (*_genZ_decayMode)[i_Z]==7){

      for(int ilep=0; ilep<(*_genlep_e).size(); ilep++){
	
	bool isFromHardProcess = ( (*_genlep_flags)[ilep] >> 8 ) & 1;
	int ZMothInd = (*_genlep_ZMothInd)[ilep];
	
	if( !( ZMothInd==i_Z && isFromHardProcess ) )
	  continue;
	

	TLorentzVector lZ_tlv((*_genlep_px)[ilep], (*_genlep_py)[ilep], (*_genlep_pz)[ilep], (*_genlep_e)[ilep]);
	  
	TGraphErrors* lZ_gr = new TGraphErrors();
	lZ_gr->SetPoint(0,lZ_tlv.Eta(),lZ_tlv.Phi());
	if(abs((*_genlep_pdg)[ilep])==11)
	  lZ_gr->SetMarkerStyle(26);
	else if(abs((*_genlep_pdg)[ilep])==13)
	  lZ_gr->SetMarkerStyle(32);      
	lZ_gr->SetMarkerColor(i_Z+genHiggs.size()+(*_gentop_e).size()+2);
	lZ_gr->SetMarkerSize(2);
	genlep.push_back(lZ_gr);
	
	TLatex *lZ_pt = new TLatex(lZ_tlv.Eta()+0.15,lZ_tlv.Phi()+0.15,Form("%.0f GeV",lZ_tlv.Pt()));
	lZ_pt->SetTextSize(0.03);
	genpt.push_back(lZ_pt);


      }

    }


    }*/




  //Reco info
  
  vector<TGraphErrors*> recobjet;
  vector<TGraphErrors*> recojet;
  vector<TGraphErrors*> recolep;
  vector<TGraphErrors*> recotauh;


  for(unsigned int i_jet=0;i_jet<(*_recoPFJet_e).size();i_jet++){

    TLorentzVector jet_tlv((*_recoPFJet_px)[i_jet],(*_recoPFJet_py)[i_jet],(*_recoPFJet_pz)[i_jet],(*_recoPFJet_e)[i_jet]);
 
    TGraphErrors* jet_gr = new TGraphErrors();
    jet_gr->SetPoint(0,jet_tlv.Eta(),jet_tlv.Phi());
    if((*_recoPFJet_CSVscore)[i_jet]>0.46)
      jet_gr->SetMarkerStyle(20);
    else
      jet_gr->SetMarkerStyle(21);
    recojet.push_back(jet_gr); 

  }


  for(unsigned int i_lep=0;i_lep<(*_recolep_e).size();i_lep++){

    TLorentzVector lep_tlv((*_recolep_px)[i_lep],(*_recolep_py)[i_lep],(*_recolep_pz)[i_lep],(*_recolep_e)[i_lep]);
 
    TGraphErrors* lep_gr = new TGraphErrors();
    lep_gr->SetPoint(0,lep_tlv.Eta(),lep_tlv.Phi());
    if(abs((*_recolep_pdg)[i_lep])==11)
      lep_gr->SetMarkerStyle(22);
    else if(abs((*_recolep_pdg)[i_lep])==13)
      lep_gr->SetMarkerStyle(23);
    recolep.push_back(lep_gr); 

  }


  for(unsigned int i_tauh=0;i_tauh<(*_recotauh_e).size();i_tauh++){

    TLorentzVector tauh_tlv((*_recotauh_px)[i_tauh],(*_recotauh_py)[i_tauh],(*_recotauh_pz)[i_tauh],(*_recotauh_e)[i_tauh]);
 
    TGraphErrors* tauh_gr = new TGraphErrors();
    tauh_gr->SetPoint(0,tauh_tlv.Eta(),tauh_tlv.Phi());
    tauh_gr->SetMarkerStyle(33);
    recotauh.push_back(tauh_gr); 

  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGridx();
  c->SetGridy();

  for(unsigned int i=0; i<gentop.size(); i++){
    if(i==0){
      gentop[i]->GetXaxis()->SetLimits(-3.2,3.2);
      gentop[i]->GetYaxis()->SetRangeUser(-3.2,3.2);
      gentop[i]->GetXaxis()->SetTitle("#eta");
      gentop[i]->GetYaxis()->SetTitle("#phi");
      gentop[i]->Draw("AP");
    }
    else
      gentop[i]->Draw("P");
  }

  for(unsigned int i=0; i<genHiggs.size(); i++)
    genHiggs[i]->Draw("P");

  for(unsigned int i=0; i<genZ.size(); i++)
    genZ[i]->Draw("P");

  for(unsigned int i=0; i<genW.size(); i++)
    genW[i]->Draw("P");

  for(unsigned int i=0; i<genb.size(); i++)
    genb[i]->Draw("P");

  for(unsigned int i=0; i<genq.size(); i++)
    genq[i]->Draw("P");

  for(unsigned int i=0; i<genlep.size(); i++)
    genlep[i]->Draw("P");

  for(unsigned int i=0; i<gentauh.size(); i++)
    gentauh[i]->Draw("P");

  for(unsigned int i=0; i<recojet.size(); i++)
    recojet[i]->Draw("P");

  for(unsigned int i=0; i<recolep.size(); i++)
    recolep[i]->Draw("P");

  for(unsigned int i=0; i<recotauh.size(); i++)
    recotauh[i]->Draw("P");

  for(unsigned int i=0; i<genpt.size(); i++)
    genpt[i]->Draw("same");


  if(draw_leg){

    TCanvas* c2=new TCanvas("c2","c2",200,400);
    
    TLegend* leg=new TLegend(0.1,0.1,0.9,0.9);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.1);
    leg->SetFillColor(0);
    

    
    if(gentop.size()>0){
      TGraphErrors* top_gr = new TGraphErrors();
      top_gr->SetMarkerStyle(28);
      top_gr->SetFillColor(0);
      top_gr->SetLineColor(0);
      top_gr->SetMarkerSize(2);
      leg->AddEntry(top_gr,"gen. top");
    }
    if(genW.size()>0){
      TGraphErrors* W_gr = new TGraphErrors();
      W_gr->SetMarkerStyle(31);
      W_gr->SetFillColor(0);
      W_gr->SetLineColor(0);
      W_gr->SetMarkerSize(2);
      leg->AddEntry(W_gr,"gen. W");
    }
    if(genHiggs.size()>0){
      TGraphErrors* H_gr = new TGraphErrors();
      H_gr->SetMarkerStyle(30);
      H_gr->SetFillColor(0);
      H_gr->SetLineColor(0);
      H_gr->SetMarkerSize(2);
      leg->AddEntry(H_gr,"gen. H");
    }
    if(genZ.size()>0){
      TGraphErrors* Z_gr = new TGraphErrors();
      Z_gr->SetMarkerStyle(30);
      Z_gr->SetFillColor(0);
      Z_gr->SetLineColor(0);
      Z_gr->SetMarkerSize(2);
      leg->AddEntry(Z_gr,"gen. Z");
    }
    if(genb.size()>0){
      TGraphErrors* b_gr = new TGraphErrors();
      b_gr->SetMarkerStyle(24);
      b_gr->SetFillColor(0);
      b_gr->SetLineColor(0);
      b_gr->SetMarkerSize(2);
      leg->AddEntry(b_gr,"gen. b");
    }
    if(genq.size()>0){
      TGraphErrors* q_gr = new TGraphErrors();
      q_gr->SetMarkerStyle(25);
      q_gr->SetFillColor(0);
      q_gr->SetLineColor(0);
      q_gr->SetMarkerSize(2);
      leg->AddEntry(q_gr,"gen. q");
    }
    if(genlep.size()>0){
      TGraphErrors* ele_gr = new TGraphErrors();
      ele_gr->SetMarkerStyle(26);
      ele_gr->SetFillColor(0);
      ele_gr->SetLineColor(0);
      ele_gr->SetMarkerSize(2);
      leg->AddEntry(ele_gr,"gen. e");
      
      TGraphErrors* mu_gr = new TGraphErrors();
      mu_gr->SetMarkerStyle(32);
      mu_gr->SetFillColor(0);
      mu_gr->SetLineColor(0);
      mu_gr->SetMarkerSize(2);
      leg->AddEntry(mu_gr,"gen. #mu");
    }
    if(gentauh.size()>0){
      TGraphErrors* tauh_gr = new TGraphErrors();
      tauh_gr->SetMarkerStyle(27);
      tauh_gr->SetFillColor(0);
      tauh_gr->SetLineColor(0);
      tauh_gr->SetMarkerSize(2);
      leg->AddEntry(tauh_gr,"gen. #tau_{h}");
    }
    
    
    if(recojet.size()>0){
      TGraphErrors* bjet_gr = new TGraphErrors();
      bjet_gr->SetMarkerStyle(20);
      bjet_gr->SetFillColor(0);
      bjet_gr->SetLineColor(0);
      bjet_gr->SetMarkerSize(2);
      leg->AddEntry(bjet_gr,"b-jet loose");
      
      TGraphErrors* jet_gr = new TGraphErrors();
      jet_gr->SetMarkerStyle(21);
      jet_gr->SetFillColor(0);
      jet_gr->SetLineColor(0);
      jet_gr->SetMarkerSize(2);
      leg->AddEntry(jet_gr,"light jet");
    }
    
    if(recolep.size()>0){
      TGraphErrors* ele_gr = new TGraphErrors();
      ele_gr->SetMarkerStyle(22);
      ele_gr->SetFillColor(0);
      ele_gr->SetLineColor(0);
      ele_gr->SetMarkerSize(2);
      leg->AddEntry(ele_gr,"reco. e");
      
      TGraphErrors* mu_gr = new TGraphErrors();
      mu_gr->SetMarkerStyle(23);
      mu_gr->SetFillColor(0);
      mu_gr->SetLineColor(0);
      mu_gr->SetMarkerSize(2);
      leg->AddEntry(mu_gr,"reco. #mu");
    }
    
    if(recotauh.size()>0){
      TGraphErrors* tauh_gr = new TGraphErrors();
      tauh_gr->SetMarkerStyle(33);
      tauh_gr->SetFillColor(0);
      tauh_gr->SetLineColor(0);
      tauh_gr->SetMarkerSize(2);
      leg->AddEntry(tauh_gr,"reco. #tau_{h}");
    }
    
    leg->Draw();

  }
  

  return;

}

