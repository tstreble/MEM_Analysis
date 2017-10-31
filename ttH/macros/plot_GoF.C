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
#include <TArrow.h>

#include "Helpers.C"


using namespace std;



void plot_Gof(TString obs_filename, TString toy_filename, TString plotname){

  TH1F* h_toys = single_plot(toy_filename,
			     "limit",
			     "limit",
			     "1.",
			     100,0,50);

  TLegend* leg=new TLegend(0.5,0.6,0.85,0.7);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_toys,"Expected (from toys)");


  h_toys->GetXaxis()->SetTitle("Goodness of fit");
  h_toys->GetYaxis()->SetTitle("Number of toys");
  h_toys->GetYaxis()->SetTitleOffset(1.65);
  h_toys->SetTitle("");
  h_toys->SetStats(0);
  h_toys->SetLineColor(kBlack);
  h_toys->SetLineWidth(2);


  double x[100];
  double y[100];
  for (Int_t i=0;i<100;i++) x[i] = Float_t(i+1)/100;
  h_toys->GetQuantiles(100,y,x);

  TH1F* h_obs = single_plot(obs_filename,
			    "limit",
			    "limit",
			    "1.",
			    100,0,50);
  float mean = h_obs->GetMean();

  TArrow* arrow = new TArrow(mean,0,mean,50,0.02,"<|");
  arrow->SetLineWidth(3);
  arrow->SetLineColor(kBlue);
  arrow->SetFillColor(kBlue);

  for(unsigned int i=0;i<100;i++)
    cout<<y[i]<<endl;

  for(unsigned int i=0;i<100;i++){
    if(mean<y[i]){
      cout<<"Obs. in "<<i<<"th centile"<<endl;
      break;
      }
  }

  float max_x=h_toys->GetBinCenter(h_toys->GetMaximumBin());

  for(unsigned int i=0;i<100;i++){
    if(max_x<y[i]){
      cout<<"Max. in "<<i<<"th centile"<<endl;
      break;
      }
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gPad->SetTicks();
  gPad->SetGrid();

  h_toys->Draw("hist");
  arrow->Draw("");
  leg->Draw("same");

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.65,0.91,"#bf{35.9 fb^{-1} (13 TeV)}");

  
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");


}




void plot_1l2tau(){

  TString obs_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/1l2tau/higgsCombineTest.GoodnessOfFit.mH125.root";
  TString toys_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/1l2tau/higgsCombineTest.GoodnessOfFit.mH125_toys.root";

  plot_Gof(obs_file,toys_file,"1l2tau_Moriond/GoF_1l2tau");
  

}







void plot_3l1tau(){

  TString obs_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/3l1tau/higgsCombineTest.GoodnessOfFit.mH125.root";
  TString toys_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/3l1tau/higgsCombineTest.GoodnessOfFit.mH125_toys.root";

  plot_Gof(obs_file,toys_file,"3l1tau_Moriond/GoF_3l1tau");
  

}






void plot_2lss1tau_nomiss(){

  TString obs_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/2lss1tau_nomiss/higgsCombineTest.GoodnessOfFit.mH125.root";
  TString toys_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/2lss1tau_nomiss/higgsCombineTest.GoodnessOfFit.mH125_toys.root";

  plot_Gof(obs_file,toys_file,"2lss1tau_Moriond/GoF_2lss1tau_nomiss");
  

}







void plot_2lss1tau_missing(){

  TString obs_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/2lss1tau_missing/higgsCombineTest.GoodnessOfFit.mH125.root";
  TString toys_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/2lss1tau_missing/higgsCombineTest.GoodnessOfFit.mH125_toys.root";

  plot_Gof(obs_file,toys_file,"2lss1tau_Moriond/GoF_2lss1tau_missing");
  

}




void plot_2lss1tau_missing_normonly(){

  TString obs_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/2lss1tau_missing_norm_only/higgsCombineTest.GoodnessOfFit.mH125.root";
  TString toys_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/2lss1tau_missing_norm_only/higgsCombineTest.GoodnessOfFit.mH125_toys.root";

  plot_Gof(obs_file,toys_file,"GoF_2lss1tau_missing_norm_only");
  

}







void plot_combined(){

  TString obs_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/combined/higgsCombineTest.GoodnessOfFit.mH125.root";
  TString toys_file="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/GoF_tests/combined/higgsCombineTest.GoodnessOfFit.mH125_toys.root";

  plot_Gof(obs_file,toys_file,"GoF_combined");
  

}
