#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>
#include <TGaxis.h>

float luminosity = 36800; //12.9 fb-1

using namespace std;



void plot_bbb_fakes(){


  TString datacardname = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_mvis_1l2tau_syst_36.8fb_122016.root";

  TFile* f = TFile::Open(datacardname);


  TH1F* h_fakes = (TH1F*)f->Get("x_fakes_data");
  h_fakes->SetFillColor(10);
  h_fakes->SetLineColor(kBlack);
  TH1F* h_fakes_lines = h_fakes;
  h_fakes_lines->SetFillColor(kBlack);
  h_fakes_lines->SetFillStyle(3004);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_fakes->SetMaximum(1.5*h_fakes->GetMaximum());
  h_fakes->Draw("hist");
  h_fakes_lines->Draw("histsame");
  
  for(unsigned int i=2; i<20;i++){

    TH1F* h = (TH1F*)f->Get(Form("x_fakes_data_CMS_ttHt_templstat_1l_2tau_fakes_bin%iUp",i));
    h->SetLineColor(kRed);
    h->SetLineWidth(2);
    h->Draw("histsame");

    TH1F* h2 = (TH1F*)f->Get(Form("x_fakes_data_CMS_ttHt_templstat_1l_2tau_fakes_bin%iDown",i));
    h2->SetLineColor(kBlue);
    h2->SetLineWidth(2);
    h2->Draw("histsame");

  }


}





void plot_JES_TTZ_fakes_MVA(){


  TString datacardname = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MVA_2lSS_allcat_syst_nofaketau_36.8fb.root";

  TFile* f = TFile::Open(datacardname);


  TH1F* h_ttH = (TH1F*)f->Get("x_ttG");
  h_ttH->SetFillColor(10);
  h_ttH->SetLineColor(kBlack);
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.5*h_ttH->GetMaximum());
  h_ttH->Draw("hist");
  h_ttH->Draw("histsame");
  
  TH1F* h = (TH1F*)f->Get("x_ttG_CMS_ttHt_JESUp");
  h->SetLineColor(kRed);
  h->SetLineWidth(2);
  h->Draw("histsame");

  TH1F* h2 = (TH1F*)f->Get("x_ttG_CMS_ttHt_JESDown");
  h2->SetLineColor(kBlue);
  h2->SetLineWidth(2);
  h2->Draw("histsame");


}






void plot_JES_TTW_MEM(){


  TString datacardname = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_36.8fb.root";

  TFile* f = TFile::Open(datacardname);


  TH1F* h_ttH = (TH1F*)f->Get("x_TTW");
  h_ttH->SetFillColor(10);
  h_ttH->SetLineColor(kBlack);
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.5*h_ttH->GetMaximum());
  h_ttH->Draw("hist");
  h_ttH->Draw("histsame");
  
  TH1F* h = (TH1F*)f->Get("x_TTW_CMS_ttHt_JESUp");
  h->SetLineColor(kRed);
  h->SetLineWidth(2);
  h->Draw("histsame");

  TH1F* h2 = (TH1F*)f->Get("x_TTW_CMS_ttHt_JESDown");
  h2->SetLineColor(kBlue);
  h2->SetLineWidth(2);
  h2->Draw("histsame");


}






void plot_JES_TTZ_fakes_MEM_nomiss(){


  TString datacardname = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_36.8fb.root";

  TFile* f = TFile::Open(datacardname);


  TH1F* h_ttH = (TH1F*)f->Get("x_TTZ");
  h_ttH->SetFillColor(10);
  h_ttH->SetLineColor(kBlack);
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.5*h_ttH->GetMaximum());
  h_ttH->Draw("hist");
  h_ttH->Draw("histsame");
  
  TH1F* h = (TH1F*)f->Get("x_TTZ_CMS_ttHt_JESUp");
  h->SetLineColor(kRed);
  h->SetLineWidth(2);
  h->Draw("histsame");

  TH1F* h2 = (TH1F*)f->Get("x_TTZ_CMS_ttHt_JESDown");
  h2->SetLineColor(kBlue);
  h2->SetLineWidth(2);
  h2->Draw("histsame");


}





void plot_JES_TTW_MEM_missing(){


  TString datacardname = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_36.8fb.root";

  TFile* f = TFile::Open(datacardname);


  TH1F* h_ttH = (TH1F*)f->Get("x_TTW");
  h_ttH->SetFillColor(10);
  h_ttH->SetLineColor(kBlack);
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.5*h_ttH->GetMaximum());
  h_ttH->Draw("hist");
  h_ttH->Draw("histsame");
  
  TH1F* h = (TH1F*)f->Get("x_TTW_CMS_ttHt_JESUp");
  h->SetLineColor(kRed);
  h->SetLineWidth(2);
  h->Draw("histsame");

  TH1F* h2 = (TH1F*)f->Get("x_TTW_CMS_ttHt_JESDown");
  h2->SetLineColor(kBlue);
  h2->SetLineWidth(2);
  h2->Draw("histsame");


}
