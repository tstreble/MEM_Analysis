#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include "Helpers.C"
#include <vector>
#include <TLatex.h>
#include <THStack.h>
#include <TGraphErrors.h>

using namespace std;







void plot_MEM_LR_ttbar_nomiss(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");


  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T",var,"MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25 && integration_type==0)",10,0,1.));
  h.push_back(single_plot(file_ttbar_DL,"T",var,"MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==0)",10,0,1));  
  h.push_back(single_plot(files_data_fakes,"T",var,"event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig && integration_type==0)",10,0,1));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.6,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("#splitline{2lSS + 1#tau_{h} category}{No missing jet}");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttbar_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_MEM_LR_ttbar_miss(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");


  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T",var,"MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25 && integration_type==1)",10,0,1.));
  h.push_back(single_plot(file_ttbar_DL,"T",var,"MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==1)",10,0,1));  
  h.push_back(single_plot(files_data_fakes,"T",var,"event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig && integration_type==1)",10,0,1));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.6,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("#splitline{2lSS + 1#tau_{h} category}{Missing jet}");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttbar_miss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}


