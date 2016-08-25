#include <TFile.h>
#include <TH1F.h>
#include <TChain.h>
#include "Helpers.C"


void make_bTagEfficiencies(TString file){
  
  TChain* tree=new TChain("HTauTauTree","HTauTauTree");
  tree->Add(file);

  vector<float> *_jets_pt;
  vector<float> *_jets_eta;
  vector<int> *_jets_Flavour;
  vector<int> *_PFjetID;
  vector<float> *_bCSVscore;

  tree->SetBranchAddress("jets_pt",&_jets_pt);
  tree->SetBranchAddress("jets_eta",&_jets_eta);
  tree->SetBranchAddress("jets_Flavour",&_jets_Flavour);
  tree->SetBranchAddress("PFjetID",&_PFjetID);
  tree->SetBranchAddress("bCSVscore",&_bCSVscore);

  TFile* f = TFile::Open("bTagEfficiencies.root");
  if(f!=0){
    cout<<"bTagEfficiencies.root already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f = TFile::Open("bTagEfficiencies.root","RECREATE");

  double pt_bins[10] = {20.,30.,40.,50.,70.,100.,150.,200.,300.,640.};
  double eta_bins[5] = {0.,0.6,1.2,2.1,2.4};
  
  TH2F* h2_BTaggingEff_Denom_b = new TH2F("h2_BTaggingEff_Denom_b","pT-eta distribution of b jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Denom_c = new TH2F("h2_BTaggingEff_Denom_c","pT-eta distribution of c jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Denom_udsg = new TH2F("h2_BTaggingEff_Denom_udsg","pT-eta distribution of udsg jets",9,pt_bins,4,eta_bins);

  TH2F* h2_BTaggingEff_Num_b_L = new TH2F("h2_BTaggingEff_Num_b_L","pT-eta distribution of loose b jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Num_b_M = new TH2F("h2_BTaggingEff_Num_b_M","pT-eta distribution of medium b jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Num_b_T = new TH2F("h2_BTaggingEff_Num_b_T","pT-eta distribution of tight b jets",9,pt_bins,4,eta_bins);

  TH2F* h2_BTaggingEff_Num_c_L = new TH2F("h2_BTaggingEff_Num_c_L","pT-eta distribution of loose c jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Num_c_M = new TH2F("h2_BTaggingEff_Num_c_M","pT-eta distribution of medium c jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Num_c_T = new TH2F("h2_BTaggingEff_Num_c_T","pT-eta distribution of tight c jets",9,pt_bins,4,eta_bins);

  TH2F* h2_BTaggingEff_Num_udsg_L = new TH2F("h2_BTaggingEff_Num_udsg_L","pT-eta distribution of loose udsg jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Num_udsg_M = new TH2F("h2_BTaggingEff_Num_udsg_M","pT-eta distribution of medium udsg jets",9,pt_bins,4,eta_bins);
  TH2F* h2_BTaggingEff_Num_udsg_T = new TH2F("h2_BTaggingEff_Num_udsg_T","pT-eta distribution of tight udsg jets",9,pt_bins,4,eta_bins);

  TH1F* h_pT_b = new TH1F("h_pT_b","pT distribution of b jets",9,pt_bins);
  TH1F* h_pT_c = new TH1F("h_pT_c","pT distribution of c jets",9,pt_bins);
  TH1F* h_pT_udsg = new TH1F("h_pT_udsg","pT distribution of udsg jets",9,pt_bins);
  
  TH1F* h_eta_b = new TH1F("h_eta_b","eta distribution of b jets",4,eta_bins);
  TH1F* h_eta_c = new TH1F("h_eta_c","eta distribution of c jets",4,eta_bins);
  TH1F* h_eta_udsg = new TH1F("h_eta_udsg","eta distribution of udsg jets",4,eta_bins);

  TH1F* h_CSV_b = new TH1F("h_CSV_b","CSV distribution of b jets",120,0,1.2);
  TH1F* h_CSV_c = new TH1F("h_CSV_c","CSV distribution of c jets",120,0,1.2);
  TH1F* h_CSV_udsg = new TH1F("h_CSV_udsg","CSV distribution of udsg jets",120,0,1.2);


  Long64_t nentries = tree->GetEntries();

  cout<<"nentries="<<tree->GetEntries()<<endl;

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _jets_pt = 0;
    _jets_eta = 0;
    _jets_Flavour = 0;
    _PFjetID = 0;
    _bCSVscore = 0;

    tree->GetEntry(i);

    for(unsigned int j=0; j<(*_jets_pt).size(); j++){
    
      float pT=(*_jets_pt)[j];
      float eta=fabs((*_jets_eta)[j]);
      float CSV=(*_bCSVscore)[j];    
      int flavour = abs((*_jets_Flavour)[j]);    

      if(!( pT>20 && eta<2.4 && (*_PFjetID)[j]>0 ))
	continue;

      if(flavour==5){

	h2_BTaggingEff_Denom_b->Fill( pT, eta );
	h_pT_b->Fill( pT );
	h_eta_b->Fill( eta );
	h_CSV_b->Fill( CSV );

	if( CSV>0.46 )
	  h2_BTaggingEff_Num_b_L->Fill( pT, eta );
	if( CSV>0.8 )
	  h2_BTaggingEff_Num_b_M->Fill( pT, eta );
	if( CSV>0.935 )
	  h2_BTaggingEff_Num_b_T->Fill( pT, eta );

      }


      else if(flavour==4){

	h2_BTaggingEff_Denom_c->Fill( pT, eta );
	h_pT_c->Fill( pT );
	h_eta_c->Fill( eta );
	h_CSV_c->Fill( CSV );

	if( CSV>0.46 )
	  h2_BTaggingEff_Num_c_L->Fill( pT, eta );
	if( CSV>0.8 )
	  h2_BTaggingEff_Num_c_M->Fill( pT, eta );
	if( CSV>0.935 )
	  h2_BTaggingEff_Num_c_T->Fill( pT, eta );

      }

      else{

	h2_BTaggingEff_Denom_udsg->Fill( pT, eta );
	h_pT_udsg->Fill( pT );
	h_eta_udsg->Fill( eta );
	h_CSV_udsg->Fill( CSV );

	if( CSV>0.46 )
	  h2_BTaggingEff_Num_udsg_L->Fill( pT, eta );
	if( CSV>0.8 )
	  h2_BTaggingEff_Num_udsg_M->Fill( pT, eta );
	if( CSV>0.935 )
	  h2_BTaggingEff_Num_udsg_T->Fill( pT, eta );

      }

    }


  }

  
  
  h2_BTaggingEff_Denom_b->Write();
  h2_BTaggingEff_Denom_c->Write();
  h2_BTaggingEff_Denom_udsg->Write();
   
  h2_BTaggingEff_Num_b_L->Write();
  h2_BTaggingEff_Num_b_M->Write();
  h2_BTaggingEff_Num_b_T->Write();

  h2_BTaggingEff_Num_c_L->Write();
  h2_BTaggingEff_Num_c_M->Write();
  h2_BTaggingEff_Num_c_T->Write();

  h2_BTaggingEff_Num_udsg_L->Write();
  h2_BTaggingEff_Num_udsg_M->Write();
  h2_BTaggingEff_Num_udsg_T->Write();
   
  h_pT_b->Write();
  h_pT_c->Write();
  h_pT_udsg->Write();

  h_eta_b->Write();
  h_eta_c->Write();
  h_eta_udsg->Write();

  h_CSV_b->Write();
  h_CSV_c->Write();
  h_CSV_udsg->Write();
   

  TH2F* eff_b_L = h2_BTaggingEff_Num_b_L;
  TH2F* eff_b_M = h2_BTaggingEff_Num_b_M;
  TH2F* eff_b_T = h2_BTaggingEff_Num_b_T;
  eff_b_L->Divide(h2_BTaggingEff_Denom_b);
  eff_b_M->Divide(h2_BTaggingEff_Denom_b);
  eff_b_T->Divide(h2_BTaggingEff_Denom_b);
  eff_b_L->SetNameTitle("eff_b_L","eff_b_L");
  eff_b_M->SetNameTitle("eff_b_M","eff_b_M");
  eff_b_T->SetNameTitle("eff_b_T","eff_b_T");
  eff_b_L->Write();
  eff_b_M->Write();
  eff_b_T->Write();

  TH2F* eff_c_L = h2_BTaggingEff_Num_c_L;
  TH2F* eff_c_M = h2_BTaggingEff_Num_c_M;
  TH2F* eff_c_T = h2_BTaggingEff_Num_c_T;
  eff_c_L->Divide(h2_BTaggingEff_Denom_c);
  eff_c_M->Divide(h2_BTaggingEff_Denom_c);
  eff_c_T->Divide(h2_BTaggingEff_Denom_c);
  eff_c_L->SetNameTitle("eff_c_L","eff_c_L");
  eff_c_M->SetNameTitle("eff_c_M","eff_c_M");
  eff_c_T->SetNameTitle("eff_c_T","eff_c_T");
  eff_c_L->Write();
  eff_c_M->Write();
  eff_c_T->Write();

  TH2F* eff_udsg_L = h2_BTaggingEff_Num_udsg_L;
  TH2F* eff_udsg_M = h2_BTaggingEff_Num_udsg_M;
  TH2F* eff_udsg_T = h2_BTaggingEff_Num_udsg_T;
  eff_udsg_L->Divide(h2_BTaggingEff_Denom_udsg);
  eff_udsg_M->Divide(h2_BTaggingEff_Denom_udsg);
  eff_udsg_T->Divide(h2_BTaggingEff_Denom_udsg);
  eff_udsg_L->SetNameTitle("eff_udsg_L","eff_udsg_L");
  eff_udsg_M->SetNameTitle("eff_udsg_M","eff_udsg_M");
  eff_udsg_T->SetNameTitle("eff_udsg_T","eff_udsg_T");
  eff_udsg_L->Write();
  eff_udsg_M->Write();
  eff_udsg_T->Write();

  f->Close();

}
