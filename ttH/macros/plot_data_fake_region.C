#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLatex.h>
#include "Helpers.C"

using namespace std;



void plot2D_n_fake(){

  vector<TString> file;
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root");

  TH2F* h = single_plot2D(file,"HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","category==41 && isTrig",3,0,3,2,0,2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztext");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_Data";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}





void plot2D_n_fake_weighted(){


  vector<TString> file;
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root");


  TH2F* h = single_plot2D(file,"HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*(category==41 && isTrig)",3,0,3,2,0,2);

  double error = 0;
  h->IntegralAndError(0,3,0,2,error);
  cout<<"h->Integral()="<<h->Integral(0,3,0,2)<<"+/-"<<error<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Weighted number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_Data_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_3l(){

  vector<TString> file;
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root");
 
  

  TH2F* h = single_plot2D(file,"HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","category==46 && isTrig_3l",4,0,4,2,0,2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztext");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_Data_3l";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}





void plot2D_n_fake_weighted_3l(){

  vector<TString> file;
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root");
  file.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root");

  TH2F* h = single_plot2D(file,"HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*(category==46 && isTrig_3l)",4,0,4,2,0,2);

  double error = 0;
  h->IntegralAndError(0,4,0,2,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Weighted number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_Data_3l_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_2lSS(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==11 && isTrig)",3,0,3,2,0,2);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig)",3,0,3,2,0,2));

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_2lSS_genmatch(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==11 && isTrig && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0])",3,0,3,2,0,2);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0])",3,0,3,2,0,2));


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_genmatch";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}




void plot2D_n_fake_ttH_2lSS_genmatch_lep(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==11 && isTrig && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1])",3,0,3,1,0,1);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1])",3,0,3,1,0,1));


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_genmatch_lep";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}





void plot2D_n_fake_ttH_2lSS_genmatch_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0])",3,0,3,2,0,2);


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,2,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_genmatch_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}




void plot2D_n_fake_ttH_2lSS_genmatch_lep_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1])",3,0,3,1,0,1);


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());
  
  double error = 0;
  h->IntegralAndError(0,2,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_genmatch_lep_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_2lSS_fakes(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==11 && isTrig && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0]))",3,0,3,2,0,2);
    h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0]))",3,0,3,2,0,2));


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,2,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_fakes";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}




void plot2D_n_fake_ttH_2lSS_fakes_lep(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==11 && isTrig && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]))",3,0,3,1,0,1);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]))",3,0,3,1,0,1));


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_fakes_lep";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}


void plot2D_n_fake_ttH_2lSS_fakes_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0]))",3,0,3,2,0,2);


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,2,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_fakes_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_2lSS_fakes_lep_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_2lSS_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && isTrig && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]))",3,0,3,1,0,1);


  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());
  
  double error = 0;
  h->IntegralAndError(0,2,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_2lSS_fakes_lep_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_3l(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==16 && isTrig)",4,0,4,2,0,2);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l)",4,0,4,2,0,2));

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_3l_genmatch(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==16 && isTrig_3l && (recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && recotauh_sel_isGenMatched[0]))",4,0,4,2,0,2);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && (recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && recotauh_sel_isGenMatched[0]))",4,0,4,2,0,2));

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_genmatch";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_3l_genmatch_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && (recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && recotauh_sel_isGenMatched[0]))",4,0,4,2,0,2);

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,4,0,2,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_genmatch_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}









void plot2D_n_fake_ttH_3l_fakes(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==16 && isTrig_3l && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && recotauh_sel_isGenMatched[0]))",4,0,4,2,0,2);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && recotauh_sel_isGenMatched[0]))",4,0,4,2,0,2));

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_fakes";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_3l_fakes_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && recotauh_sel_isGenMatched[0]))",4,0,4,2,0,2);

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,4,0,2,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_fakes_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}





void plot2D_n_fake_ttH_3l_genmatch_lep(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==16 && isTrig_3l && (recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2]))",4,0,4,1,0,1);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && (recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2]))",4,0,4,1,0,1));

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_genmatch_lep";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_3l_fakes_lep(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==16 && isTrig_3l && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2]))",4,0,4,1,0,1);
  h->Add(single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2]))",4,0,4,1,0,1));

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_fakes";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}







void plot2D_n_fake_ttH_3l_genmatch_lep_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && (recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2]))",4,0,4,1,0,1);

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,4,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_genmatch_lep_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}






void plot2D_n_fake_ttH_3l_fakes_lep_weighted(){

  TH2F* h = single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root","HTauTauTree_3l_lepMVA_CR","n_fake_lep","n_fake_tau","event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==46 && isTrig_3l && !(recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2]))",4,0,4,1,0,1);

  TH1F* h_MC_norm = single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root",
				"HTauTauTree",
				"1",
				"MC_weight*PU_weight_ICHEP",
				3,0,3);

  h->Scale(12900*0.2586/h_MC_norm->Integral());

  double error = 0;
  h->IntegralAndError(0,4,0,1,error);
  
  cout<<"h->Integral()="<<h->Integral()<<"+/-"<<error<<endl;

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.2);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("N(fake lep)");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("N(fake #tau_{h})") ;
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetZaxis()->SetTitle("Number of events") ;
  h->GetZaxis()->SetTitleOffset(1.5);
  h->SetTitle("");

  h->Draw("colztexte");

  TLatex *texl = new TLatex(0.02,2.02,"CMS Preliminary, 12.9 fb^{-1} #sqrt{s}=13 TeV,  Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="2D_n_fake_ttH_3l_fakes_weighted";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}


