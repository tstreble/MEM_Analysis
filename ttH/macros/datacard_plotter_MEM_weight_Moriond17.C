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
#include <TGraphAsymmErrors.h>

//float luminosity = 36800; //12.9 fb-1
float luminosity = 35900;

using namespace std;


void plot_2lSS(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_flips = *(TH1F*)f->Get("x_flips_data");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("x_fakes_data") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);


  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  //h_Rares.Add( (TH1F*)f->Get("x_WWss") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

 

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get("x_EWK") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  h_flips.Scale(1/h_ttW.Integral());
  h_flips_lines.Scale(1/h_ttW.Integral());
  h_fakes.Scale(1/h_ttW.Integral());
  h_fakes_lines.Scale(1/h_ttW.Integral());
  h_Rares.Scale(1/h_ttW.Integral());
  h_WZ.Scale(1/h_ttW.Integral());
  h_ttZ.Scale(1/h_ttW.Integral());
  h_ttW.Scale(1/h_ttW.Integral());




  TH1F h_ttH_boson = *(TH1F*)f->Get("x_ttH_hww");
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz") );
  h_ttH_boson.SetLineWidth(3);
  h_ttH_boson.SetLineColor(kOrange);
  h_ttH_boson.Scale(1/h_ttH_boson.Integral());

  TH1F h_ttH_tt = *(TH1F*)f->Get("x_ttH_htt");  
  h_ttH_tt.SetLineWidth(3);
  h_ttH_tt.SetLineColor(kRed); 
  h_ttH_tt.Scale(1/h_ttH_tt.Integral());


/*TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(3);
  h_ttH_only.Scale(1/h_ttH_only.Integral());*/

  /*TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);*/

  /*TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);*/

  //f->Close();


  TLegend* leg=new TLegend(0.25,0.5,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_data_obs,"Data");
  //leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  //leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"EWK");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  //leg->AddEntry(&h_ttH_only,"ttH signal");
  leg->AddEntry(&h_ttH_boson,"ttH, H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttH_tt,"ttH, H#rightarrow#tau#tau");
  
  h_ttW.GetXaxis()->SetTitle(varname);
  h_ttW.GetYaxis()->SetTitle("a.u.");
  h_ttW.GetYaxis()->SetTitleOffset(1.65);
  h_ttW.SetTitle("");
  h_ttW.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gPad->SetTicks();

  //h_ttW.SetMaximum(1.5*max(h_ttW.GetMaximum(),h_ttH_only.GetMaximum()));
  h_ttW.SetMaximum(1.5*max(h_ttW.GetMaximum(),max(h_ttH_boson.GetMaximum(),h_ttH_tt.GetMaximum())));
  h_ttW.SetMinimum(0);
  //h_ttW.SetMaximum(1.5*max(h_ttW.GetMaximum(),h_ttH_only.GetMaximum()));
  //(&h_ttH)->Draw("hist");
  //(&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("hist");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 
//(&h_ttH_only)->Draw("same");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttH_tt)->Draw("histsame");

  
  //(&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("esame");
  //(&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  //h_ttW.GetYaxis()->SetRangeUser(0,1.3*h_ttW.GetMaximum());

  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.65,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  h_ttW.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttW.GetBinLowEdge(1), 0.01, h_ttW.GetBinLowEdge(1), h_ttW.GetMaximum(), 0.01, h_ttW.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}







void plot_2lSS_split(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_ttZ_Ztautau = *(TH1F*)f->Get("x_ttZ_Ztautau");
  h_ttZ_Ztautau.SetLineColor(kRed);
  h_ttZ_Ztautau.SetLineWidth(2);
  h_ttZ_Ztautau.Scale(1/h_ttZ_Ztautau.Integral());

  TH1F h_ttZ_Zll = *(TH1F*)f->Get("x_ttZ_Zll");
  h_ttZ_Zll.SetLineColor(kGreen);
  h_ttZ_Zll.SetLineWidth(2);
  h_ttZ_Zll.Scale(1/h_ttZ_Zll.Integral());

  TH1F h_ttbar = *(TH1F*)f->Get("x_fakes_data");
  h_ttbar.SetLineColor(kBlue);
  h_ttbar.SetLineWidth(2);
  h_ttbar.Scale(1/h_ttbar.Integral());

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH_htt");
  h_ttH_only.SetLineColor(kBlack);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(1/h_ttH_only.Integral());

  TLegend* leg=new TLegend(0.25,0.5,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_ttH_only,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttZ_Ztautau,"ttZ Z#rightarrow#tau#tau");
  leg->AddEntry(&h_ttZ_Zll,"ttZ Z#rightarrowll");
  leg->AddEntry(&h_ttbar,"t#bar{t} DL");

  
  h_ttH_only.GetXaxis()->SetTitle(varname);
  h_ttH_only.GetYaxis()->SetTitle("a.u.");
  h_ttH_only.GetYaxis()->SetTitleOffset(1.65);
  h_ttH_only.SetTitle("");
  h_ttH_only.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gPad->SetTicks();

  h_ttH_only.SetMaximum(1.5*max(max(h_ttH_only.GetMaximum(),h_ttZ_Ztautau.GetMaximum()),max(h_ttZ_Zll.GetMaximum(),h_ttbar.GetMaximum())));
  h_ttH_only.SetMinimum(0);
  (&h_ttH_only)->Draw("hist");
  (&h_ttZ_Ztautau)->Draw("histsame");
  (&h_ttZ_Zll)->Draw("histsame");
  (&h_ttbar)->Draw("histsame");
 
  leg->Draw("same");

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.65,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  h_ttH_only.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH_only.GetBinLowEdge(1), 0.01, h_ttH_only.GetBinLowEdge(1), h_ttH_only.GetMaximum(), 0.01, h_ttH_only.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}







void plot_MEM_ttH_weight_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_weight_2lSS_nomiss_nofaketau_36.8fb.root",
	    "log(w(ttH H#rightarrow#tau#tau))",
	    "2lss1tau_Moriond/MEM_ttH_weight_2lSS_nomiss_MEMplots_36.8fb_122016");

}




void plot_MEM_ttH_weight_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_weight_2lSS_missing_nofaketau_36.8fb.root",
	    "log(w(ttH H#rightarrow#tau#tau))",
	    "2lss1tau_Moriond/MEM_ttH_weight_2lSS_missing_MEMplots_36.8fb_122016");

}





void plot_MEM_ttZ_weight_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttZ_weight_2lSS_nomiss_nofaketau_36.8fb.root",
	    "log(w(ttZ Z#rightarrow#tau#tau))",
	    "2lss1tau_Moriond/MEM_ttZ_weight_2lSS_nomiss_MEMplots_36.8fb_122016");

}





void plot_MEM_ttZ_weight_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttZ_weight_2lSS_missing_nofaketau_36.8fb.root",
	    "log(w(ttZ Z#rightarrow#tau#tau))",
	    "2lss1tau_Moriond/MEM_ttZ_weight_2lSS_missing_MEMplots_36.8fb_122016");

}






void plot_MEM_ttZ_Zll_weight_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttZ_Zll_weight_2lSS_nomiss_nofaketau_36.8fb.root",
	    "log(w(ttZ Z#rightarrowll))",
	    "2lss1tau_Moriond/MEM_ttZ_Zll_weight_2lSS_nomiss_MEMplots_36.8fb_122016");

}





void plot_MEM_ttZ_Zll_weight_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttZ_Zll_weight_2lSS_missing_nofaketau_36.8fb.root",
	    "log(w(ttZ Z#rightarrowll))",
	    "2lss1tau_Moriond/MEM_ttZ_Zll_weight_2lSS_missing_MEMplots_36.8fb_122016");

}






void plot_MEM_ttbar_fakelep_weight_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttbar_fakelep_weight_2lSS_nomiss_nofaketau_36.8fb.root",
	    "log(w(t#bar{t} l+#tau))",
	    "2lss1tau_Moriond/MEM_ttbar_fakelep_weight_2lSS_nomiss_MEMplots_36.8fb_122016");

}





void plot_MEM_ttbar_fakelep_weight_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttbar_fakelep_weight_2lSS_missing_nofaketau_36.8fb.root",
	    "log(w(t#bar{t} l+#tau))",
	    "2lss1tau_Moriond/MEM_ttbar_fakelep_weight_2lSS_missing_MEMplots_36.8fb_122016");

}












void plot_MEM_LR_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_missing_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_LR_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrow#tau#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_2lSS_nomiss_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_LR_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrow#tau#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_2lSS_missing_MEMplots_36.8fb_122016");

}




void plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_Zll_LR_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrowll)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_Zll_2lSS_nomiss_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_Zll_LR_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrowll)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_Zll_2lSS_missing_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttbar_fakelep_LR_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs t#bar{t} l+#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nomiss_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttbar_fakelep_LR_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs t#bar{t} l+#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttbar_fakelep_2lSS_missing_MEMplots_36.8fb_122016");

}





void plot_MEM_LR_ttH_vs_full_bkg_2lSS_nofaketau_nomiss_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_full_bkg_2lSS_nomiss_MEMplots_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_full_bkg_2lSS_nofaketau_missing_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_full_bkg_2lSS_missing_MEMplots_36.8fb_122016");

}




void plot_all(){


  /*plot_MEM_ttH_weight_2lSS_nofaketau_nomiss_122016();
  plot_MEM_ttH_weight_2lSS_nofaketau_missing_122016();
  plot_MEM_ttZ_weight_2lSS_nofaketau_nomiss_122016();
  plot_MEM_ttZ_weight_2lSS_nofaketau_missing_122016();
  plot_MEM_ttZ_Zll_weight_2lSS_nofaketau_nomiss_122016();
  plot_MEM_ttZ_Zll_weight_2lSS_nofaketau_missing_122016();
  plot_MEM_ttbar_fakelep_weight_2lSS_nofaketau_nomiss_122016();
  plot_MEM_ttbar_fakelep_weight_2lSS_nofaketau_missing_122016();*/

  plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_nomiss_122016();
  plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_missing_122016();
  plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_nomiss_122016();
  plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_missing_122016();
  plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_nomiss_122016();
  plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_missing_122016();


}









void plot_MEM_LR_2lSS_nofaketau_nomiss_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_MEMplots_split_36.8fb_122016");

}






void plot_MEM_LR_2lSS_nofaketau_missing_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_missing_MEMplots_split_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_nomiss_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_LR_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrow#tau#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_2lSS_nomiss_MEMplots_split_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_missing_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_LR_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrow#tau#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_2lSS_missing_MEMplots_split_36.8fb_122016");

}




void plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_nomiss_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_Zll_LR_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrowll)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_Zll_2lSS_nomiss_MEMplots_split_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_missing_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttZ_Zll_LR_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs ttZ,Z#rightarrowll)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttZ_Zll_2lSS_missing_MEMplots_split_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_nomiss_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttbar_fakelep_LR_2lSS_nomiss_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs t#bar{t} l+#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nomiss_MEMplots_split_36.8fb_122016");

}






void plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_missing_split_122016(){

  plot_2lSS_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MEM_ttH_vs_ttbar_fakelep_LR_2lSS_missing_nofaketau_36.8fb.root",
	    "MEM_LR(ttH,H#rightarrow#tau#tau vs t#bar{t} l+#tau)",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_ttbar_fakelep_2lSS_missing_MEMplots_split_36.8fb_122016");

}






void plot_all_split(){


  plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_nomiss_split_122016();
  plot_MEM_LR_ttH_vs_ttZ_2lSS_nofaketau_missing_split_122016();
  plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_nomiss_split_122016();
  plot_MEM_LR_ttH_vs_ttZ_Zll_2lSS_nofaketau_missing_split_122016();
  plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_nomiss_split_122016();
  plot_MEM_LR_ttH_vs_ttbar_fakelep_2lSS_nofaketau_missing_split_122016();


}







void plot_MEM_LR_ttH_vs_full_bkg_2lSS_nofaketau_nomiss_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_full_bkg_2lSS_nomiss_MEMplots_35.9fb_022017");

}






void plot_MEM_LR_ttH_vs_full_bkg_2lSS_nofaketau_missing_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_ttH_vs_full_bkg_2lSS_missing_MEMplots_35.9fb_022017");

}


