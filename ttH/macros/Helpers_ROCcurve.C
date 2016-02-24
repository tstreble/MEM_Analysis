#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <Helpers.C>


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










TGraphErrors* get_ROC_LR_ttjets(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=1e-9, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.15f*Integral_ttjets))*(Integral_ttH>0)+26*(Integral_ttjets==0&&Integral_ttH>0)-(Integral_ttH==0&&Integral_ttjets==0)",k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-Integral_ttH/(Integral_ttH+%.15f*Integral_ttjets))*(Integral_ttH>0)+26*(Integral_ttjets==0&&Integral_ttH>0)-(Integral_ttjets==0&&Integral_ttH==0)",k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);



  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

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
