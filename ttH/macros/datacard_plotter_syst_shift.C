#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>
#include <THStack.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>
#include <TGaxis.h>
#include <TGraphAsymmErrors.h>


float luminosity = 35900;

using namespace std;


void plot_2lSS(TString datacardname,  TString systname, TString sample, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_nominal = *(TH1F*)f->Get("x_"+sample);
  h_nominal.SetLineWidth(2);
  h_nominal.SetLineColor(kBlue);

  TH1F h_Up = *(TH1F*)f->Get("x_"+sample+"_CMS_ttHl_"+systname+"Up");
  h_Up.SetLineWidth(2);
  h_Up.SetLineColor(kRed);

  TH1F h_Down = *(TH1F*)f->Get("x_"+sample+"_CMS_ttHl_"+systname+"Down");
  h_Down.SetLineWidth(2);
  h_Down.SetLineColor(kGreen);


  f->Close();



  TLegend* leg=new TLegend(0.4,0.5,0.7,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader("#bf{"+sample+"}");
  leg->AddEntry(&h_nominal,"Nominal");
  leg->AddEntry(&h_Up,systname+"Up");
  leg->AddEntry(&h_Down,systname+"Down");


  h_nominal.GetXaxis()->SetTitle(varname);
  h_nominal.GetYaxis()->SetTitle("Events");
  h_nominal.GetYaxis()->SetTitleOffset(1.65);
  h_nominal.SetTitle("");
  h_nominal.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_nominal.SetMaximum(1.5*h_nominal.GetMaximum());
  h_nominal.Draw();
  h_Up.Draw("same");
  h_Down.Draw("same");
  leg->Draw("same");

  h_nominal.GetYaxis()->SetRangeUser(0,1.3*h_nominal.GetMaximum());

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
 

  h_nominal.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_nominal.GetBinLowEdge(1), 0.01, h_nominal.GetBinLowEdge(1), h_nominal.GetMaximum(), 0.01, h_nominal.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_nominal.GetBinLowEdge(h_nominal.GetNbinsX()+1)-h_nominal.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_nominal.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratioUp=new TGraphAsymmErrors();
  h_ratioUp->Divide(&h_Up,&h_nominal,"pois");
 
  h_ratioUp->SetLineColor(kRed);
  h_ratioUp->SetMarkerColor(kRed);
  h_ratioUp->SetMinimum(0.);  // Define Y ..
  h_ratioUp->SetMaximum(2.); // .. range
  h_ratioUp->SetLineWidth(2);
  //h_ratioUp->SetMarkerStyle(20);


  h_ratioUp->Draw("ap");       // Draw the ratio plot

  TGraphAsymmErrors *h_ratioDown=new TGraphAsymmErrors();
  h_ratioDown->Divide(&h_Down,&h_nominal,"pois");
 
  h_ratioDown->SetLineColor(kGreen);
  h_ratioDown->SetMarkerColor(kGreen);
  h_ratioDown->SetMinimum(0.);  // Define Y ..
  h_ratioDown->SetMaximum(2.); // .. range
  h_ratioDown->SetLineWidth(2);
  //h_ratioDown->SetMarkerStyle(20);

  h_ratioDown->Draw("psame");       // Draw the ratio plot


  // Y axis histo_emul plot settings
  h_nominal.GetYaxis()->SetTitleSize(20);
  h_nominal.GetYaxis()->SetTitleFont(43);
  h_nominal.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratioUp->SetTitle(""); // Remove the ratio title
  
  h_ratioUp->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_nominal.GetBinLowEdge(1), 0.01, h_nominal.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratioUp->GetYaxis()->SetTitle("Shift./Nomin.");
  h_ratioUp->GetYaxis()->SetNdivisions(505);
  h_ratioUp->GetYaxis()->SetTitleSize(20);
  h_ratioUp->GetYaxis()->SetTitleFont(43);
  h_ratioUp->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratioUp->GetXaxis()->SetTitleSize(20);
  h_ratioUp->GetXaxis()->SetTitleFont(43);
  h_ratioUp->GetXaxis()->SetTitleOffset(4.);
  h_ratioUp->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratioUp->GetXaxis()->SetLabelSize(15);
  h_ratioUp->GetXaxis()->SetTitle(varname);
  h_ratioUp->GetXaxis()->SetLimits(h_nominal.GetBinLowEdge(1),h_nominal.GetBinLowEdge(h_nominal.GetNbinsX()+1));


  TLine* line = new TLine(h_nominal.GetBinLowEdge(1), 1., h_nominal.GetBinLowEdge(h_nominal.GetNbinsX()+1),1.);
  line->Draw("same");


  /*TF1* func_up=new TF1("func_up","[0]*x+[1]",0,1);
  h_ratioUp->Fit("func_up");
  TF1* func_down=new TF1("func_down","[0]*x+[1]",0,1);
  h_ratioDown->Fit("func_down");
  cout<<"RatioUp: [0]="<<func_up->GetParameter(0)<<" +/- "<<func_up->GetParError(0)<<endl;
  cout<<"[1]="<<func_up->GetParameter(1)<<" +/- "<<func_up->GetParError(1)<<endl;
  cout<<"RatioDown: [0]="<<func_down->GetParameter(0)<<" +/- "<<func_down->GetParError(0)<<endl;
  cout<<"[1]="<<func_down->GetParameter(1)<<" +/- "<<func_down->GetParError(1)<<endl;*/


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

a  return;



}





void plot_ttH_htt_TES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="ttH_htt";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_ttH_htt_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_htt_JES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="ttH_htt";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_ttH_htt_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_hww_TES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="ttH_hww";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_ttH_hww_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_hww_JES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="ttH_hww";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_ttH_hww_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}








void plot_TTZ_TES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="TTZ";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_TTZ_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_TTZ_JES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="TTZ";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_TTZ_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}







void plot_TTW_TES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="TTW";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_TTW_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_TTW_JES(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="TTW";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_missing_TTW_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}








void plot_ttH_htt_TES_pt_tau(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_tau_2lss1tau_syst_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="ttH_htt";
  TString varname="p_{T}(#tau_{h})";
  TString plotname="pt_tau_ttH_htt_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_htt_JES_pt_jet(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet1_2lss1tau_syst_35.9fb_012017.root";
  TString systname="JES";
  TString sample="ttH_htt";
  TString varname="p_{T}(lead. jet)";
  TString plotname="pT_jet1_ttH_htt_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}





void plot_TTW_JES_pt_jet(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet1_2lss1tau_syst_35.9fb_012017.root";
  TString systname="JES";
  TString sample="TTW";
  TString varname="p_{T}(lead. jet)";
  TString plotname="pT_jet1_TTW_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}








void plot_ttH_htt_TES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="ttH_htt";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_ttH_htt_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_htt_JES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="ttH_htt";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_ttH_htt_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_hww_TES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="ttH_hww";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_ttH_hww_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_ttH_hww_JES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="ttH_hww";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_ttH_hww_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}








void plot_TTZ_TES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="TTZ";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_TTZ_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_TTZ_JES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="TTZ";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_TTZ_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}







void plot_TTW_TES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="tauES";
  TString sample="TTW";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_TTW_TES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}






void plot_TTW_JES_nomiss(){

  TString datacardname="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root";
  TString systname="JES";
  TString sample="TTW";
  TString varname="MEM_LR";
  TString plotname="MEM_LR_nomiss_TTW_JES";

  plot_2lSS(datacardname,systname,sample,varname,plotname);

}





