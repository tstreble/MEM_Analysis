#include <TGraphErrors.h>
#include <TH1F.h>
#include <TCanvas.h>
#include "PUReweight.cc"
#include "PUReweight_KLUB.cc"
#include "Helpers.C"
#include <TFile.h>


void plot_PUweight(){

  TH1F* h_CMG = new TH1F("h_CMG","h_CMG",60,0,60);
  TH1F* h_KLUB = new TH1F("h_CMG","h_CMG",60,0,60);

  for(unsigned int i=0;i<60;i++){

    h_CMG->Fill(i,puw2016_nTrueInt_13fb(i));
    h_KLUB->Fill(i,puw2016_nTrueInt_13fb_KLUB(i));
    
  }

  h_CMG->Scale(1/h_CMG->Integral());
  h_KLUB->Scale(1/h_KLUB->Integral());

  h_CMG->SetLineColor(kBlack);
  h_KLUB->SetLineColor(kRed);

  h_KLUB->Draw("hist");
  h_CMG->Draw("histsame");

  return;

}



void plot_myPUweight_ICHEP(){

  TH1F* h_PU_MC=single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*","HTauTauTree","npu","",60,0,60);
  h_PU_MC->Scale(1/h_PU_MC->Integral());

  TFile* f = TFile::Open("/home/llr/cms/strebler/CMSSW_8_0_20_old/src/RecoLuminosity/LumiDB/scripts/MyDataPileupHistogram_ICHEP.root");
  TH1F* h_PU_data = (TH1F*)f->Get("pileup");
  h_PU_data->Scale(1/h_PU_data->Integral());

  TH1F h_ratio=(*h_PU_data);
  h_ratio.Divide(h_PU_MC);
  (&h_ratio)->Draw();


  for(unsigned int i=0;i<61;i++)
    cout<<"npuString16_12c9fb["<<i<<"] = "<<h_ratio.GetBinContent(i+1)<<";"<<endl;

  for(unsigned int i=0;i<61;i++)
    cout<<h_ratio.GetBinContent(i+1)<<",";
  cout<<endl;

  TFile* f_new = TFile::Open("PU_weights/PU_weights_2016_271036_276811.root","RECREATE");
  h_PU_MC->SetNameTitle("h_MC_ttH","h_MC_ttH");
  h_PU_MC->Write();
  h_PU_data->SetNameTitle("h_data_271036_276811","h_data_271036_276811");
  h_PU_data->Write();
  h_ratio.SetNameTitle("h_ratio_data_MC","h_ratio_data_MC");
  (&h_ratio)->Write();

  return;

}




void plot_myPUweight_2016(){

  TH1F* h_PU_MC=single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*","HTauTauTree","npu","",60,0,60);
  h_PU_MC->Scale(1/h_PU_MC->Integral());

  TFile* f = TFile::Open("/home/llr/cms/strebler/CMSSW_8_0_20/src/RecoLuminosity/LumiDB/scripts/MyDataPileupHistogram_2016.root");
  TH1F* h_PU_data = (TH1F*)f->Get("pileup");
  h_PU_data->Scale(1/h_PU_data->Integral());

  TH1F h_ratio=(*h_PU_data);
  h_ratio.Divide(h_PU_MC);
  (&h_ratio)->Draw();

  for(unsigned int i=0;i<61;i++)
    cout<<"npuString16_36c4fb["<<i<<"] = "<<h_ratio.GetBinContent(i+1)<<";"<<endl; 
  for(unsigned int i=0;i<61;i++)
    cout<<h_ratio.GetBinContent(i+1)<<",";
  cout<<endl;


  TFile* f_new = TFile::Open("PU_weights/PU_weights_2016_271036_284044.root","RECREATE");
  h_PU_MC->SetNameTitle("h_MC_ttH","h_MC_ttH");
  h_PU_MC->Write();
  h_PU_data->SetNameTitle("h_data_271036_284044","h_data_271036_284044");
  h_PU_data->Write();
  h_ratio.SetNameTitle("h_ratio_data_MC","h_ratio_data_MC");
  (&h_ratio)->Write();

  return;

}







void plot_myPUweight_Moriond17(){

  TH1F* h_PU_MC=single_plot("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*","HTauTauTree","npu","",60,0,60);
  h_PU_MC->Scale(1/h_PU_MC->Integral());

  TFile* f = TFile::Open("/home/llr/cms/strebler/CMSSW_8_0_20_old/src/RecoLuminosity/LumiDB/scripts/MyDataPileupHistogram_2016.root");
  TH1F* h_PU_data = (TH1F*)f->Get("pileup");
  h_PU_data->Scale(1/h_PU_data->Integral());

  TH1F h_ratio=(*h_PU_data);
  h_ratio.Divide(h_PU_MC);
  (&h_ratio)->Draw();

  for(unsigned int i=0;i<61;i++)
    cout<<"npuString16_36c4fb_MCSummer16["<<i<<"] = "<<h_ratio.GetBinContent(i+1)<<";"<<endl; 
  for(unsigned int i=0;i<61;i++)
    cout<<h_ratio.GetBinContent(i+1)<<",";
  cout<<endl;


  TFile* f_new = TFile::Open("PU_weights/PU_weights_MCSummer2016_271036_284044.root","RECREATE");
  h_PU_MC->SetNameTitle("h_MC_ttH_MCSummer16","h_MC_ttH_MCSummer16");
  h_PU_MC->Write();
  h_PU_data->SetNameTitle("h_data_271036_284044","h_data_271036_284044");
  h_PU_data->Write();
  h_ratio.SetNameTitle("h_ratio_data_MC","h_ratio_data_MC");
  (&h_ratio)->Write();

  return;

}
