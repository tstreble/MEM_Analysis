#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include "Helpers.C"


TGraphErrors* get_ROC_CSV(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"-log(1-recoPFJet30_CSVscore)*(recoPFJet30_CSVscore<1) + 13*(recoPFJet30_CSVscore>1)",cut_num_sig,nbin,-3,15);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"-log(1-recoPFJet30_CSVscore)*(recoPFJet30_CSVscore<1) + 13*(recoPFJet30_CSVscore>1)",cut_num_bkg,nbin,-3,15);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,3);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,3);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;


  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=18./nbin;

  int binup_sig=h_sig->FindBin(14);
  int binup_bkg=h_bkg->FindBin(14);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_2lSS_MVA(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"MVA_2lSS_ttbar",cut_num_sig,nbin,-1,1);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"MVA_2lSS_ttbar",cut_num_bkg,nbin,-1,1);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);



  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;


  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=2./nbin;

  int binup_sig=h_sig->FindBin(1.);
  int binup_bkg=h_bkg->FindBin(1.);

  for(int i=0;i<nbin;i++){
    double x=-1.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_2lSS_MVA_ttV(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"MVA_2lSS_ttV",cut_num_sig,nbin,-1,1);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"MVA_2lSS_ttV",cut_num_bkg,nbin,-1,1);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);



  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;


  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=2./nbin;

  int binup_sig=h_sig->FindBin(1.);
  int binup_bkg=h_bkg->FindBin(1.);

  for(int i=0;i<nbin;i++){
    double x=-1.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=max(n_sig_acc/N_sig,0.);
    double bkgfake=max(n_bkg_acc/N_bkg,0.);


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_ttH_weight_category(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)",cut_num_sig,nbin,-100,60);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)",cut_num_bkg,nbin,-100,60);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=160./nbin;

  int binup_sig=h_sig->FindBin(60.);
  int binup_bkg=h_bkg->FindBin(60.);

  for(int i=0;i<nbin;i++){
    double x=-100.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=max(n_sig_acc/N_sig,0.);
    double bkgfake=max(n_bkg_acc/N_bkg,0.);


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_ttH_weight(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){

  vector<TString> cut_num_sig_cat0;
  vector<TString> cut_denom_sig_cat0;
  vector<TString> cut_num_sig_cat1;
  vector<TString> cut_denom_sig_cat1;
  for(unsigned int i=0; i<cut_num_sig.size(); i++){
    cut_num_sig_cat0.push_back(cut_num_sig[i]+"*(integration_type==0)");
    cut_denom_sig_cat0.push_back(cut_denom_sig[i]+"*(integration_type==0)");
    cut_num_sig_cat1.push_back(cut_num_sig[i]+"*(integration_type==1)");
    cut_denom_sig_cat1.push_back(cut_denom_sig[i]+"*(integration_type==1)");
  }

  vector<TString> cut_num_bkg_cat0;
  vector<TString> cut_denom_bkg_cat0;
  vector<TString> cut_num_bkg_cat1;
  vector<TString> cut_denom_bkg_cat1;
  for(unsigned int i=0; i<cut_num_bkg.size(); i++){
    cut_num_bkg_cat0.push_back(cut_num_bkg[i]+"*(integration_type==0)");
    cut_denom_bkg_cat0.push_back(cut_denom_bkg[i]+"*(integration_type==0)");
    cut_num_bkg_cat1.push_back(cut_num_bkg[i]+"*(integration_type==1)");
    cut_denom_bkg_cat1.push_back(cut_denom_bkg[i]+"*(integration_type==1)");
  }
    

  TH1F* h_sig_denom_cat0=single_plot(file_sig,tree_name,"1",cut_denom_sig_cat0,nbin,0,2);
  TH1F* h_sig_denom_cat1=single_plot(file_sig,tree_name,"1",cut_denom_sig_cat1,nbin,0,2);
  TH1F* h_bkg_denom_cat0=single_plot(file_bkg,tree_name,"1",cut_denom_bkg_cat0,nbin,0,2);
  TH1F* h_bkg_denom_cat1=single_plot(file_bkg,tree_name,"1",cut_denom_bkg_cat1,nbin,0,2);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);

  double frac_sig_cat0=h_sig_denom_cat0->Integral()/h_sig_denom->Integral();
  double frac_sig_cat1=h_sig_denom_cat1->Integral()/h_sig_denom->Integral();
  double frac_bkg_cat0=h_bkg_denom_cat0->Integral()/h_bkg_denom->Integral();
  double frac_bkg_cat1=h_bkg_denom_cat1->Integral()/h_bkg_denom->Integral();

  cout<<"frac_sig_cat0="<<frac_sig_cat0<<endl;
  cout<<"frac_sig_cat1="<<frac_sig_cat1<<endl;
  cout<<"frac_bkg_cat0="<<frac_bkg_cat0<<endl;
  cout<<"frac_bkg_cat1="<<frac_bkg_cat1<<endl;

  TGraphErrors* ROC_cat0=get_ROC_ttH_weight_category(file_sig,file_bkg,tree_name,cut_num_sig_cat0,cut_denom_sig_cat0,cut_num_bkg_cat0,cut_denom_bkg_cat0,10*nbin);
  TGraphErrors* ROC_cat1=get_ROC_ttH_weight_category(file_sig,file_bkg,tree_name,cut_num_sig_cat1,cut_denom_sig_cat1,cut_num_bkg_cat1,cut_denom_bkg_cat1,10*nbin);


  TGraphErrors* ROC = new TGraphErrors();
  ROC->SetPoint(0.,0.,0.);
  int i_point = 1;

  for(unsigned int i=0; i<nbin; i++){

    double sig_eff_min = double(i)/double(nbin);
    double sig_eff_max = double(i+1)/double(nbin);
    double lowest_bkg_eff = 1.;
    
    for(unsigned int j=0; j<ROC_cat0->GetN(); j++){
      double sig_eff_cat0, bkg_eff_cat0;
      ROC_cat0->GetPoint(j,sig_eff_cat0,bkg_eff_cat0);

      for(unsigned int k=0; k<ROC_cat1->GetN(); k++){
	double sig_eff_cat1, bkg_eff_cat1;
	ROC_cat1->GetPoint(k,sig_eff_cat1,bkg_eff_cat1);	

	double sig_eff_current = frac_sig_cat0*sig_eff_cat0 + frac_sig_cat1*sig_eff_cat1;
	if(h_sig_denom_cat0->Integral()==0)
	  sig_eff_current = frac_sig_cat1*sig_eff_cat1;
	else if(h_sig_denom_cat1->Integral()==0)
	  sig_eff_current = frac_sig_cat0*sig_eff_cat0;
	
	double bkg_eff_current = frac_bkg_cat0*bkg_eff_cat0 + frac_bkg_cat1*bkg_eff_cat1;
	if(h_bkg_denom_cat0->Integral()==0)
	  bkg_eff_current = frac_bkg_cat1*bkg_eff_cat1;
	else if(h_bkg_denom_cat1->Integral()==0)
	  bkg_eff_current = frac_bkg_cat0*bkg_eff_cat0;
	

	if(sig_eff_current>sig_eff_min && sig_eff_current<sig_eff_max && bkg_eff_current<lowest_bkg_eff){
	  lowest_bkg_eff = bkg_eff_current;

	}
	
      }

    }


    if(lowest_bkg_eff<1){
      cout<<"("<<double(i+0.5)/double(nbin)<<","<<lowest_bkg_eff<<")"<<endl;
      ROC->SetPoint(i_point,double(i+0.5)/double(nbin),lowest_bkg_eff);
      i_point++;
    }

  }

  ROC->SetPoint(i_point,1.,1.);
  
  return ROC;
  
  
}







TGraphErrors* get_ROC_ttH_weight_sumcategory(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"log(200*Integral_ttH*(integration_type==0)+Integral_ttH*(integration_type==1))*(Integral_ttH>0) -99*(Integral_ttH==0)",cut_num_sig,nbin,-100,60);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"log(200*Integral_ttH*(integration_type==0)+Integral_ttH*(integration_type==1))*(Integral_ttH>0) -99*(Integral_ttH==0)",cut_num_bkg,nbin,-100,60);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=160./nbin;

  int binup_sig=h_sig->FindBin(60.);
  int binup_bkg=h_bkg->FindBin(60.);

  for(int i=0;i<nbin;i++){
    double x=-100.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}







TGraphErrors* get_ROC_ttbar_SL_weight(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"log(Integral_ttbar_SL)*(Integral_ttbar_SL>0) -99*(Integral_ttbar_SL==0)",cut_num_sig,nbin,-120,60);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"log(Integral_ttbar_SL)*(Integral_ttbar_SL>0) -99*(Integral_ttbar_SL==0)",cut_num_bkg,nbin,-120,60);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=180./nbin;

  int binlow_sig=h_sig->FindBin(-120.);
  int binlow_bkg=h_bkg->FindBin(-120.);

  for(int i=0;i<nbin;i++){
    double x=-120.+i*step;

    int binup_sig=h_sig->FindBin(x);
    int binup_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_ttbar_DL_weight(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)",cut_num_sig,nbin,-120,60);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)",cut_num_bkg,nbin,-120,60);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=180./nbin;

  int binlow_sig=h_sig->FindBin(-120.);
  int binlow_bkg=h_bkg->FindBin(-120.);

  for(int i=0;i<nbin;i++){
    double x=-120.+i*step;
    int binup_sig=h_sig->FindBin(x);
    int binup_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_ttW_weight(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"log(Integral_ttW)*(Integral_ttW>0) -99*(Integral_ttW==0)",cut_num_sig,nbin,-120,60);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"log(Integral_ttW)*(Integral_ttW>0) -99*(Integral_ttW==0)",cut_num_bkg,nbin,-120,60);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=180./nbin;

  int binlow_sig=h_sig->FindBin(-120.);
  int binlow_bkg=h_bkg->FindBin(-120.);

  for(int i=0;i<nbin;i++){
    double x=-120.+i*step;
    int binup_sig=h_sig->FindBin(x);
    int binup_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}







TGraphErrors* get_ROC_ttH_ttbar_SL_LR(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=1e-8){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*Integral_ttbar_SL))*(Integral_ttbar_SL>0) + 40*(Integral_ttbar_SL==0 && Integral_ttH>0) - (Integral_ttbar_SL==0 && Integral_ttH==0)",k),cut_num_sig,nbin,-2,41);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*Integral_ttbar_SL))*(Integral_ttbar_SL>0) + 40*(Integral_ttbar_SL==0 && Integral_ttH>0) - (Integral_ttbar_SL==0 && Integral_ttH==0)",k),cut_num_bkg,nbin,-2,41);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*Integral_ttbar_SL))*(Integral_ttbar_SL>0) + 40*(Integral_ttbar_SL==0 && Integral_ttH>0) - (Integral_ttbar_SL==0 && Integral_ttH==0)",k),cut_denom_sig,nbin,-2,41);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*Integral_ttbar_SL))*(Integral_ttbar_SL>0) + 40*(Integral_ttbar_SL==0 && Integral_ttH>0) - (Integral_ttbar_SL==0 && Integral_ttH==0)",k),cut_denom_bkg,nbin,-2,41);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;


  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=43./nbin;

  int binup_sig=h_sig->FindBin(41.);
  int binup_bkg=h_bkg->FindBin(41.);

  for(int i=0;i<nbin;i++){
    double x=-2.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}








TGraphErrors* get_ROC_ttbar_DL_fakelep_weight(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true){


  TH1F* h_sig=single_plot(file_sig,tree_name,"log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)",cut_num_sig,nbin,-120,100);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)",cut_num_bkg,nbin,-120,100);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=180./nbin;

  int binlow_sig=h_sig->FindBin(-120.);
  int binlow_bkg=h_bkg->FindBin(-120.);

  for(int i=0;i<nbin;i++){
    double x=-120.+i*step;
    int binup_sig=h_sig->FindBin(x);
    int binup_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    //cout<<"x="<<x<<" (sigeff,bkgfake)=("<<sigeff<<","<<bkgfake<<")"<<endl;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}











TGraphErrors* get_ROC_ttH_ttbar_DL_LR(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=1e-8){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*Integral_ttbar_DL))*(Integral_ttbar_DL>0) + 40*(Integral_ttbar_DL==0 && Integral_ttH>0) - (Integral_ttbar_DL==0 && Integral_ttH==0)",k),cut_num_sig,nbin,-2,41);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*Integral_ttbar_DL))*(Integral_ttbar_DL>0) + 40*(Integral_ttbar_DL==0 && Integral_ttH>0) - (Integral_ttbar_DL==0 && Integral_ttH==0)",k),cut_num_bkg,nbin,-2,41);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);
 


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;


  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=43./nbin;

  int binup_sig=h_sig->FindBin(41.);
  int binup_bkg=h_bkg->FindBin(41.);

  for(int i=0;i<nbin;i++){
    double x=-2.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=max(n_sig_acc/N_sig,0.);
    double bkgfake=max(n_bkg_acc/N_bkg,0.);


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}








TGraphErrors* get_ROC_ttH_ttbar_DL_fakelep_LR(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=1e-8){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)))*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) + 40*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH>0) - ((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH==0)",k),cut_num_sig,nbin,-2,41);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)))*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) + 40*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH>0) - ((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH==0)",k),cut_num_bkg,nbin,-2,41);


  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);
 
  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;


  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=43./nbin;

  int binup_sig=h_sig->FindBin(41.);
  int binup_bkg=h_bkg->FindBin(41.);

  for(int i=0;i<nbin;i++){
    double x=-2.+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=max(n_sig_acc/N_sig,0.);
    double bkgfake=max(n_bkg_acc/N_bkg,0.);

    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}









TGraphErrors* get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(vector<TString> file_sig, vector<TString> file_bkg, TString tree_name,  vector<TString> cut_num_sig, vector<TString> cut_denom_sig, vector<TString> cut_num_bkg, vector<TString> cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k1=1e-17, float k2=1e-15){

  vector<TString> cut_num_sig_cat0;
  vector<TString> cut_denom_sig_cat0;
  vector<TString> cut_num_sig_cat1;
  vector<TString> cut_denom_sig_cat1;
  for(unsigned int i=0; i<cut_num_sig.size(); i++){
    cut_num_sig_cat0.push_back(cut_num_sig[i]+"*(integration_type==0)");
    cut_denom_sig_cat0.push_back(cut_denom_sig[i]+"*(integration_type==0)");
    cut_num_sig_cat1.push_back(cut_num_sig[i]+"*(integration_type==1)");
    cut_denom_sig_cat1.push_back(cut_denom_sig[i]+"*(integration_type==1)");
  }

  vector<TString> cut_num_bkg_cat0;
  vector<TString> cut_denom_bkg_cat0;
  vector<TString> cut_num_bkg_cat1;
  vector<TString> cut_denom_bkg_cat1;
  for(unsigned int i=0; i<cut_num_bkg.size(); i++){
    cut_num_bkg_cat0.push_back(cut_num_bkg[i]+"*(integration_type==0)");
    cut_denom_bkg_cat0.push_back(cut_denom_bkg[i]+"*(integration_type==0)");
    cut_num_bkg_cat1.push_back(cut_num_bkg[i]+"*(integration_type==1)");
    cut_denom_bkg_cat1.push_back(cut_denom_bkg[i]+"*(integration_type==1)");
  }
    

  TH1F* h_sig_denom_cat0=single_plot(file_sig,tree_name,"1",cut_denom_sig_cat0,nbin,0,2);
  TH1F* h_sig_denom_cat1=single_plot(file_sig,tree_name,"1",cut_denom_sig_cat1,nbin,0,2);
  TH1F* h_bkg_denom_cat0=single_plot(file_bkg,tree_name,"1",cut_denom_bkg_cat0,nbin,0,2);
  TH1F* h_bkg_denom_cat1=single_plot(file_bkg,tree_name,"1",cut_denom_bkg_cat1,nbin,0,2);
  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",cut_denom_sig,nbin,0,2);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",cut_denom_bkg,nbin,0,2);

  double frac_sig_cat0=h_sig_denom_cat0->Integral()/h_sig_denom->Integral();
  double frac_sig_cat1=h_sig_denom_cat1->Integral()/h_sig_denom->Integral();
  double frac_bkg_cat0=h_bkg_denom_cat0->Integral()/h_bkg_denom->Integral();
  double frac_bkg_cat1=h_bkg_denom_cat1->Integral()/h_bkg_denom->Integral();

  cout<<"frac_sig_cat0="<<frac_sig_cat0<<endl;
  cout<<"frac_sig_cat1="<<frac_sig_cat1<<endl;
  cout<<"frac_bkg_cat0="<<frac_bkg_cat0<<endl;
  cout<<"frac_bkg_cat1="<<frac_bkg_cat1<<endl;

  TGraphErrors* ROC_cat0=get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,tree_name,cut_num_sig_cat0,cut_denom_sig_cat0,cut_num_bkg_cat0,cut_denom_bkg_cat0,10*nbin,mistag_rate,k1);
  TGraphErrors* ROC_cat1=get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,tree_name,cut_num_sig_cat1,cut_denom_sig_cat1,cut_num_bkg_cat1,cut_denom_bkg_cat1,10*nbin,mistag_rate,k2);


  TGraphErrors* ROC = new TGraphErrors();
  ROC->SetPoint(0.,0.,0.);
  int i_point = 1;

  for(unsigned int i=0; i<nbin; i++){

    double sig_eff_min = double(i)/double(nbin);
    double sig_eff_max = double(i+1)/double(nbin);
    double lowest_bkg_eff = 1.;
    
    for(unsigned int j=0; j<ROC_cat0->GetN(); j++){
      double sig_eff_cat0, bkg_eff_cat0;
      ROC_cat0->GetPoint(j,sig_eff_cat0,bkg_eff_cat0);

      for(unsigned int k=0; k<ROC_cat1->GetN(); k++){
	double sig_eff_cat1, bkg_eff_cat1;
	ROC_cat1->GetPoint(k,sig_eff_cat1,bkg_eff_cat1);	

	double sig_eff_current = frac_sig_cat0*sig_eff_cat0 + frac_sig_cat1*sig_eff_cat1;
	if(h_sig_denom_cat0->Integral()==0)
	  sig_eff_current = frac_sig_cat1*sig_eff_cat1;
	else if(h_sig_denom_cat1->Integral()==0)
	  sig_eff_current = frac_sig_cat0*sig_eff_cat0;
	
	double bkg_eff_current = frac_bkg_cat0*bkg_eff_cat0 + frac_bkg_cat1*bkg_eff_cat1;
	if(h_bkg_denom_cat0->Integral()==0)
	  bkg_eff_current = frac_bkg_cat1*bkg_eff_cat1;
	else if(h_bkg_denom_cat1->Integral()==0)
	  bkg_eff_current = frac_bkg_cat0*bkg_eff_cat0;
	

	if(sig_eff_current>sig_eff_min && sig_eff_current<sig_eff_max && bkg_eff_current<lowest_bkg_eff){
	  lowest_bkg_eff = bkg_eff_current;

	}
	
      }

    }


    if(lowest_bkg_eff<1){
      cout<<"("<<double(i+0.5)/double(nbin)<<","<<lowest_bkg_eff<<")"<<endl;
      ROC->SetPoint(i_point,double(i+0.5)/double(nbin),lowest_bkg_eff);
      i_point++;
    }

  }

  ROC->SetPoint(i_point,1.,1.);
  
  return ROC;
  
  
}




