#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include "Helpers_ROCcurve.C"


void plot_ROC(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150522.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150522.root");


  vector<TGraphErrors*> ROC;
  for(unsigned int i=0; i<file_sig.size();i++)
    ROC.push_back(get_ROC_LR(file_sig[i],file_bkg[i],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("Full ME");
  leg_entry.push_back("ME v2");
  leg_entry.push_back("ME v3");
  leg_entry.push_back("SVFitmass");
  leg_entry.push_back("SVFitmass + VBF loose");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.77);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}





void plot_ROC_LRmin1(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150522.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150522.root");


  vector<TGraphErrors*> ROC;
  for(unsigned int i=0; i<file_sig.size();i++)
    ROC.push_back(get_ROC_LR(file_sig[i],file_bkg[i],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>0&&IntegralVBF>=0",10000,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("Full ME");
  leg_entry.push_back("ME v2");
  leg_entry.push_back("ME v3");
  leg_entry.push_back("SVFitmass");
  leg_entry.push_back("SVFitmass + VBF loose");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.77);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);
    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves for events with w_{b}>0");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LRmin1";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_force_nonzero_int(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_5D_int_nonzero_150526.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_int_nonzero_150526.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_5D_int_nonzero_150526.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_int_nonzero_150526.root");


  vector<TGraphErrors*> ROC;
  for(unsigned int i=0; i<file_sig.size();i++)
    ROC.push_back(get_ROC_LR(file_sig[i],file_bkg[i],"T","(IntegralDY>=0&&IntegralVBF>=0) && decayMode==0","IntegralDY>=0&&IntegralVBF>=0 && decayMode==0","(IntegralDY>=0&&IntegralVBF>=0) && decayMode==0","IntegralDY>=0&&IntegralVBF>=0 && decayMode==0",10000,plot_log));

  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5  && decayMode==0","IntegralDY>=0&&IntegralVBF>=0  && decayMode==0","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5  && decayMode==0","IntegralDY>=0&&IntegralVBF>=0  && decayMode==0",10000,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("ME v2 5D (1-prong)");
  leg_entry.push_back("ME v2 5D nonzero_int (1-prong)");
  leg_entry.push_back("ME v2 4D nonzero_int (1-prong)");
  leg_entry.push_back("SVFitmass + VBF loose (1-prong)");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.77);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_force_nonzero_int";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_force_nonzero_int_2(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_int_nonzero_150526.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_int_nonzero_150526.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));


  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));

  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));


  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("#splitline{ME v2 4D nonzero_int}{+ VBF very loose}");
  leg_entry.push_back("SVFitmass + VBF very loose");

  leg_entry.push_back("#splitline{ME v2 4D nonzero_int}{+ VBF loose}");
  leg_entry.push_back("SVFitmass + VBF loose");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.77);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_force_nonzero_int_2";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_CIjet(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_int_nonzero_150526.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_CIjet_150530.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_int_nonzero_150526.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_CIjet_150530.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));

  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));

  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("Old E_{jet} int.");
  leg_entry.push_back("New E_{jet} int.");
  leg_entry.push_back("Old E_{jet} int. + VBF very loose");
  leg_entry.push_back("New E_{jet} int. + VBF very loose");
  leg_entry.push_back("Old E_{jet} int. + VBF loose");
  leg_entry.push_back("New E_{jet} int. + VBF loose");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_CIjet";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC3D(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_CIjet_150530.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_CIjet_150530.root");

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("3D cuts");
  leg_entry.push_back("MEM + VBF very loose");
  leg_entry.push_back("3D cuts + VBF very loose");
  leg_entry.push_back("MEM + VBF loose");
  leg_entry.push_back("3D cuts + VBF loose");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_3D";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC2D(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_CIjet_150530.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_CIjet_150530.root");

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_2D_LR_SVfit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_2D_LR_Deta(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_2D_LR_Mjj(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_2D_Deta_Mjj(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("2D MEM + SVfit");
  leg_entry.push_back("2D MEM + #Delta#eta");
  leg_entry.push_back("2D MEM + M_{jj}");
  leg_entry.push_back("2D #Delta#eta + M_{jj}");
 

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_2D";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC3D_2D(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_CIjet_150530.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_CIjet_150530.root");

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_2D_LR_Mjj(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("3D cuts");
  leg_entry.push_back("2D MEM + M_{jj}");
 

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0.0001);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_3D_2D";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}





void plot_ROC_DY5D(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_CIjet_150530.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_CIjet_150530.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 4D");
  leg_entry.push_back("DY 5D [50,130]");
  leg_entry.push_back("DY 5D [50,130] + VBF very loose");
  leg_entry.push_back("DY 5D [50,130] + VBF loose");
  leg_entry.push_back("3D cuts");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_DY5D_combined(bool plot_log=true){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_2D_LR_SVfit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log,0.000001));
  ROC.push_back(get_ROC_2D_LR_Deta(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log,0.000001));
  ROC.push_back(get_ROC_2D_LR_Mjj(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log,0.000001));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));

  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 5D [50,130]");
  leg_entry.push_back("DY 5D [50,130] + SVfitMass");
  leg_entry.push_back("DY 5D [50,130] + #Delta#eta");
  leg_entry.push_back("DY 5D [50,130] + M_{jj}");
  leg_entry.push_back("3D cuts");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_combined";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_DY_2j_Emb(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_4D_CIjet_150530.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_4D_CIjet_150530.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_Emb_MEv2_4D_CIjet_150609.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));

  vector<TString> leg_entry;
  leg_entry.push_back("Bkg = DY+2jets");
  leg_entry.push_back("Bkg = DY Embedded");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY_2j_Emb";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_VBF5D_DY5D(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF5D_115_135_DY5D_50_130_150610.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF5D_115_135_DY5D_50_130_150610.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 



  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF 4D");
  leg_entry.push_back("VBF 5D [115,135]");
  leg_entry.push_back("VBF 4D + VBF very loose");
  leg_entry.push_back("VBF 5D [115,135] + VBF very loose");
  leg_entry.push_back("VBF 4D + VBF loose");
  leg_entry.push_back("VBF 5D [115,135] + VBF loose");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_VBF5D_DY5D";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}









void plot_ROC_test_Luca(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/Batch/Run_1_DY2Jets/Htautau_ntuples_09_06_15_Embedded8TeV_MuTau_MEv2_10k.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5","IntegralDY>0&&IntegralVBF>=0&&Mjj>150&&Deta>1.5",10000,plot_log,0.000001));

  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5","IntegralDY>0&&IntegralVBF>=0&&Mjj>350&&Deta>2.5",10000,plot_log,0.000001));



  
  vector<TString> leg_entry;
  leg_entry.push_back("SVfit + VBF very loose");
  leg_entry.push_back("DY 5D + VBF very loose");
  leg_entry.push_back("SVfit + VBF loose");
  leg_entry.push_back("DY 5D + VBF loose");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.45,0.1,0.9,0.4);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_test_Luca";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_DY5D_2(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_70_110_150610.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_70_110_150610.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 



  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 5D [50,130]");
  leg_entry.push_back("DY 5D [70,110]");
  leg_entry.push_back("DY 5D [50,130] + VBF very loose");
  leg_entry.push_back("DY 5D [70,110] + VBF very loose");
  leg_entry.push_back("DY 5D [50,130] + VBF loose");
  leg_entry.push_back("DY 5D [70,110] + VBF loose");
 

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_2";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}









void plot_ROC_DY5D_testBDT(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DY2jets.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DY2jets.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[2],file_bkg[2],"TestTree",10000,plot_log));
  ROC.push_back(get_ROC_2D_LR_Mjj(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log,0.000001));
  
  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  //leg_entry.push_back("MEM BDT outputfile");
  leg_entry.push_back("BDT 3D");
  leg_entry.push_back("BDT 4D");
  leg_entry.push_back("2D cut-based MEM + M_{jj}");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_testBDT";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_DY5D_diTauVisMass(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));

  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 5D [50,130]");
  leg_entry.push_back("+ use_diTauVisMass");
  leg_entry.push_back("DY 5D [50,130] + VBF very loose");
  leg_entry.push_back("+ use_diTauVisMass");
  leg_entry.push_back("DY 5D [50,130] + VBF loose");
  leg_entry.push_back("+ use_diTauVisMass");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_diTauVisMass";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_DY5D_3(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_70_110_150610.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_70_110_diTauBound130_150617.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_70_110_150610.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_70_110_diTauBound130_150617.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 



  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 5D [70,110]");
  leg_entry.push_back("+ modif.");
  leg_entry.push_back("DY 5D [70,110] + VBF very loose");
  leg_entry.push_back("+ modif.");
  leg_entry.push_back("DY 5D [70,110] + VBF loose");
  leg_entry.push_back("+ modif.");
   

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_3";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}





void plot_ROC_DY5D_4(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_70_110_150610.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_70_110_int_nonzero_150618.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_70_110_150610.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_70_110_int_nonzero_150618.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 



  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 5D [70,110]");
  leg_entry.push_back("+ modif.");
  leg_entry.push_back("DY 5D [70,110] + VBF very loose");
  leg_entry.push_back("+ modif.");
  leg_entry.push_back("DY 5D [70,110] + VBF loose");
  leg_entry.push_back("+ modif.");
   

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_4";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_DY5D_5(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_70_110_int_nonzero_150618.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_70_110_int_nonzero_150618.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>150&&Deta>1.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0 &&Mjj>350&&Deta>2.5","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log,0.000001)); 



  
  vector<TString> leg_entry;
  leg_entry.push_back("DY 5D [50,130]");
  leg_entry.push_back("DY 5D [70,110]");
  leg_entry.push_back("DY 5D [50,130] + VBF very loose");
  leg_entry.push_back("DY 5D [70,110] + VBF very loose");
  leg_entry.push_back("DY 5D [50,130] + VBF loose");
  leg_entry.push_back("DY 5D [70,110] + VBF loose");
 

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_5";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_jet_eta(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_jet_eta_150619.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_jet_eta_150619.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>0&&IntegralVBF>=0",10000,plot_log,0.000001));




  
  vector<TString> leg_entry;
  leg_entry.push_back("2 leading jets");
  leg_entry.push_back("2 most forward jets");
 

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_jet_eta";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_jet_eta2(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_jet_eta_150619_converted.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_jet_eta_150619_converted.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>0&&IntegralVBF>=0 && nJets30>=3",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3",50,plot_log));
  ROC.push_back(get_ROC_3D_forw_jets(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3",50,plot_log));


  vector<TString> leg_entry;
  leg_entry.push_back("MEM 2 leading jets");
  leg_entry.push_back("MEM 2 forward jets");
  leg_entry.push_back("#splitline{3D cut-based}{2 leading jets}");
  leg_entry.push_back("#splitline{3D cut-based}{2 forward jets}");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.18,0.6,0.55,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves for events with nJets30#geq3");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_jet_eta2";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}





void plot_ROC_jet_eta3(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616_converted.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_jet_eta_150619_converted.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616_converted.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_jet_eta_150619_converted.root");


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0",10000,plot_log,0.000001));
  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0",50,plot_log));
  ROC.push_back(get_ROC_3D_forw_jets(file_sig[1],file_bkg[1],"T","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0","IntegralDY>=0&&IntegralVBF>=0 && nJets30>=3 && lead_forw_jet_flag==0",50,plot_log));


  vector<TString> leg_entry;
  leg_entry.push_back("MEM 2 leading jets");
  leg_entry.push_back("MEM 2 forward jets");
  leg_entry.push_back("#splitline{3D cut-based}{2 leading jets}");
  leg_entry.push_back("#splitline{3D cut-based}{2 forward jets}");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.18,0.6,0.55,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves for events with different lead. and forw. jets");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_jet_eta3";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_3D_smooth(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root");


  vector<TGraphErrors*> ROC;

  ROC.push_back(get_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_3D_smooth(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_3D_smooth_unbiased(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50,plot_log));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log));

  vector<TString> leg_entry;
  leg_entry.push_back("3D cut-based old");
  leg_entry.push_back("3D cut-based smooth");
  leg_entry.push_back("#splitline{3D cut-based smooth}{unbiased}");
  leg_entry.push_back("BDT");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.18,0.6,0.55,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_3D_smooth";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_test_Luca2(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");


  TString cut_sig = "pt1>30 && pt2>30 && ptL1>20 && (isPFMuon && isTightMuon)  && ptL2>30  && tightestHPSMVA3oldDMwLTWP>2 &&                   decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1) && Mjj>150 && Deta>1.5";
  TString cut_bkg = "pt1>30 && pt2>30 && ptL1>20 && (isPFMuon && isTightMuon)  && ptL2>30  && tightestHPSMVA3oldDMwLTWP>2 &&                   decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5) && Mjj>150 && Deta>1.5";


  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T",cut_sig,cut_sig,cut_bkg,cut_bkg,10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_sig,cut_sig,cut_bkg,cut_bkg,10000,plot_log,0.000001));

  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T",cut_sig + "&& Mjj>350 && Deta>2.8",cut_sig + "&& Mjj>350 && Deta>2.8",cut_bkg + "&& Mjj>350 && Deta>2.5",cut_bkg + "&& Mjj>350 && Deta>2.8",10000,plot_log));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_sig + "&& Mjj>350 && Deta>2.8",cut_sig + "&& Mjj>350 && Deta>2.8",cut_bkg + "&& Mjj>350 && Deta>2.8",cut_bkg + "&& Mjj>350 && Deta>2.8",10000,plot_log,0.000001));


  
  vector<TString> leg_entry;
  leg_entry.push_back("SVfit + VBF very loose");
  leg_entry.push_back("DY 5D + VBF very loose");
  leg_entry.push_back("SVfit + VBF loose");
  leg_entry.push_back("DY 5D + VBF loose");
  leg_entry.push_back("SVfit + VBF very loose");
  leg_entry.push_back("DY 5D + VBF very loose");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.45,0.1,0.9,0.4);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_test_Luca2";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_DY5D_BDT3D_VBF_veryloose(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY,10000,plot_log,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_3D_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log,"Mjj>150 && Deta>1.5"));
  

  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("Cut-based SVFitMass");
  leg_entry.push_back("Cut-based 3D");
  leg_entry.push_back("BDT 3D");



  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.25,0.8,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_BDT3D_VBF_veryloose";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_DY5D_BDT3D_VBF_loose(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>350 && Deta>2.8";
  TString cut_denom_VBF=cut_VBF + " && Mjj>350 && Deta>2.8";
  TString cut_num_DY=cut_DY + " && Mjj>350 && Deta>2.8";
  TString cut_denom_DY=cut_DY + " && Mjj>350 && Deta>2.8";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_SVFit(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY,10000,plot_log,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_3D_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log,"Mjj>350 && Deta>2.8"));
  

  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("Cut-based SVFitMass");
  leg_entry.push_back("Cut-based 3D");
  leg_entry.push_back("BDT 3D");



  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.25,0.8,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>350 GeV, #Delta#eta>2.8");


  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_BDT3D_VBF_loose";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_ROC_testk(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
   ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000001,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.00001,weight_VBF,weight_DY));
   ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.01,weight_VBF,weight_DY));

  

  vector<TString> leg_entry;
  leg_entry.push_back("k=0.000002");
  leg_entry.push_back("k=0.000001");
  leg_entry.push_back("k=0.00001");
  leg_entry.push_back("k=0.01");



  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.25,0.8,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");


  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_testk";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_ROC_DY5D_optim_info_VBF_veryloose(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_SVfit(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_Deta_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_Mjj_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log,"Mjj>150 && Deta>1.5"));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[2],file_bkg[2],"TestTree",10000,plot_log,"Mjj>150 && Deta>1.5"));

  

  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("#splitline{Cut-based MEM}{+ SVFitMass}");
  leg_entry.push_back("Cut-based MEM + #Delta#eta");
  leg_entry.push_back("Cut-based MEM + M_{jj}");
  leg_entry.push_back("BDT 4D with MEM");
  leg_entry.push_back("BDT 3D without MEM");



  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.15,0.85,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_optim_info_VBF_veryloose";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_DY5D_optim_info_VBF_loose(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>350 && Deta>2.8";
  TString cut_denom_VBF=cut_VBF + " && Mjj>350 && Deta>2.8";
  TString cut_num_DY=cut_DY + " && Mjj>350 && Deta>2.8";
  TString cut_denom_DY=cut_DY + " && Mjj>350 && Deta>2.8";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_SVfit_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_Deta_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_Mjj_unbiased(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log,"Mjj>350 && Deta>2.8"));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[2],file_bkg[2],"TestTree",10000,plot_log,"Mjj>350 && Deta>2.8"));

  
  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("#splitline{Cut-based MEM}{+ SVFitMass}");
  leg_entry.push_back("Cut-based MEM + #Delta#eta");
  leg_entry.push_back("Cut-based MEM + M_{jj}");
  leg_entry.push_back("BDT 4D with MEM");
  leg_entry.push_back("BDT 3D without MEM");



  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.15,0.85,0.5);

  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>350 GeV, #Delta#eta>2.8");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_optim_info_VBF_loose";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}









void plot_ROC_DY5D_BDT2D_MEM_VBF_veryloose(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_2DMEM_log_DY5D_VBF_DYEmb.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_5DMEM_log_DY5D_VBF_DYEmb.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_2DMEM_log_DY5D_VBF_DYEmb.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_5DMEM_log_DY5D_VBF_DYEmb.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[1],file_bkg[1],"TestTree",10000,plot_log));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[2],file_bkg[2],"TestTree",10000,plot_log));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[3],file_bkg[3],"TestTree",10000,plot_log));

  

  vector<TString> leg_entry;
  leg_entry.push_back("MEM");
  leg_entry.push_back("BDT 2D MEM");
  leg_entry.push_back("BDT 4D MEM");
  leg_entry.push_back("BDT 5D MEM");



  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.25,0.8,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY5D_BDT2D_MEM_VBF_veryloose";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_ChiSquare_VBF_veryloose(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF + "&& ChiSquareVBF<2.5 && ChiSquareDY<2.5",cut_denom_VBF + "&& ChiSquareVBF<2.5 && ChiSquareDY<2.5",cut_num_DY + "&& ChiSquareVBF<2.5 && ChiSquareDY<2.5",cut_denom_DY + "&& ChiSquareVBF<2.5 && ChiSquareDY<2.5", 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF + "&& !(ChiSquareVBF<2.5 && ChiSquareDY<2.5)",cut_denom_VBF + "&& !(ChiSquareVBF<2.5 && ChiSquareDY<2.5)",cut_num_DY + "&& !(ChiSquareVBF<2.5 && ChiSquareDY<2.5)",cut_denom_DY + "&& !(ChiSquareVBF<2.5 && ChiSquareDY<2.5)", 10000,plot_log,0.000002,weight_VBF,weight_DY));


  

  vector<TString> leg_entry;
  leg_entry.push_back("Inclusive");
  leg_entry.push_back("#chi^{2}_{VBF}<2.5 and #chi^{2}_{DY}<2.5");
  leg_entry.push_back("!(#chi^{2}_{VBF}<2.5 and #chi^{2}_{DY}<2.5)");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.25,0.8,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_ChiSquare_VBF_veryloose";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_DY_0_180(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_sig.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_bkg.push_back("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_BDT_BDTrootfiles(file_sig[2],file_bkg[2],"TestTree",10000,plot_log,"Mjj>150 && Deta>1.5"));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_Deta_unbiased(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_Mjj_unbiased(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_2D_LR_SVfit_unbiased(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 50,plot_log,0.000002,weight_VBF,weight_DY));



  
  vector<TString> leg_entry;
  leg_entry.push_back("m_{DY} [50,130]");
  leg_entry.push_back("BDT 3D");
  leg_entry.push_back("m_{DY} [m_{vis}(#tau#tau),180]");
  leg_entry.push_back("+ #Delta#eta");
  leg_entry.push_back("+ M_{jj}");
  leg_entry.push_back("+ SVfit");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY_0_180";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_DY_0_300(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_300_diTauVisMass_150708.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_130_diTauVisMass_150709.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_180_diTauVisMass_150709.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_300_diTauVisMass_150708.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_0_130_diTauVisMass_150709.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_180_diTauVisMass_150709.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[2],file_bkg[2],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[3],file_bkg[3],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[4],file_bkg[4],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;
  leg_entry.push_back("m_{DY} [0,180]");
  leg_entry.push_back("m_{DY} [0,300]");
  leg_entry.push_back("m_{DY} [50,130]");
  leg_entry.push_back("m_{DY} [0,130]");
  leg_entry.push_back("m_{DY} [50,180]");

  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  

  TString filename="ROC_LR_DY_0_300";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_upper_m2DY(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_130_diTauVisMass_150709.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_250_diTauVisMass_150714.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_300_diTauVisMass_150708.root");

 


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_0_130_diTauVisMass_150709.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_250_diTauVisMass_150714.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_300_diTauVisMass_150708.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[2],file_bkg[2],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[3],file_bkg[3],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;
  leg_entry.push_back("m_{DY}^{up}=130");
  leg_entry.push_back("m_{DY}^{up}=180");
  leg_entry.push_back("m_{DY}^{up}=250");
  leg_entry.push_back("m_{DY}^{up}=300");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_upper_m2DY";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_upper_m2DY_2(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150_diTauVisMass_150714.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_210_diTauVisMass_150714.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_230_diTauVisMass_150714.root");
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_250_diTauVisMass_150714.root");

 


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150_diTauVisMass_150714.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_210_diTauVisMass_150714.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_230_diTauVisMass_150714.root");
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_250_diTauVisMass_150714.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[1],file_bkg[1],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[2],file_bkg[2],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[3],file_bkg[3],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[4],file_bkg[4],"T",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));

  
  vector<TString> leg_entry;
  leg_entry.push_back("m_{DY}^{up}=150");
  leg_entry.push_back("m_{DY}^{up}=180");
  leg_entry.push_back("m_{DY}^{up}=210");
  leg_entry.push_back("m_{DY}^{up}=230");
  leg_entry.push_back("m_{DY}^{up}=250");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.5,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_upper_m2DY_2";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_3jet_perm(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + " && Mjj>150 && Deta>1.5 && nJets30>2";
  TString cut_denom_VBF=cut_VBF + " && Mjj>150 && Deta>1.5 && nJets30>2";
  TString cut_num_DY=cut_DY + " && Mjj>150 && Deta>1.5 && nJets30>2";
  TString cut_denom_DY=cut_DY + " && Mjj>150 && Deta>1.5 && nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.4,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5, nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}









void plot_ROC_3jet_perm2(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + "&& nJets30>2";
  TString cut_denom_VBF=cut_VBF + "&& nJets30>2";
  TString cut_num_DY=cut_DY + "&& nJets30>2";
  TString cut_denom_DY=cut_DY + "&& nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.45,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm2";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_3jet_perm3(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF;
  TString cut_denom_VBF=cut_VBF;
  TString cut_num_DY=cut_DY;
  TString cut_denom_DY=cut_DY;

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.2,0.5,0.6,0.85);
  //if(plot_log)
  //leg=new TLegend(0.45,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  //leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm3";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_3jet_perm4(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + "&& nJets30==2";
  TString cut_denom_VBF=cut_VBF + "&& nJets30==2";
  TString cut_num_DY=cut_DY + "&& nJets30==2";
  TString cut_denom_DY=cut_DY + "&& nJets30==2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.2,0.5,0.6,0.85);
  //if(plot_log)
  //leg=new TLegend(0.45,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30=2");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm4";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_ROC_3jet_perm5(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + "&& nJets30>2";
  TString cut_denom_VBF=cut_VBF + "&& nJets30>2";
  TString cut_num_DY=cut_DY + "&& nJets30>2";
  TString cut_denom_DY=cut_DY + "&& nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));

  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("Default + VBF very loose");
  leg_entry.push_back("#splitline{3 jets perm sum weights}{+ VBF very loose}");


  TLegend* leg=new TLegend(0.2,0.5,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm5";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_3jet_perm6(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF;
  TString cut_denom_VBF=cut_VBF;
  TString cut_num_DY=cut_DY;
  TString cut_denom_DY=cut_DY;

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));

  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("Default + VBF very loose");
  leg_entry.push_back("3 jets perm +VBF very loose");


  TLegend* leg=new TLegend(0.17,0.55,0.65,0.87);
  //if(plot_log)
  //  leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  //leg->SetHeader("nJets30>2");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm6";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_3jet_perm7(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF+" && Mjj>350 && Deta>2.5 && nJets30>2";
  TString cut_denom_VBF=cut_VBF+" && Mjj>350 && Deta>2.5 && nJets30>2";
  TString cut_num_DY=cut_DY+" && Mjj>350 && Deta>2.5 && nJets30>2";
  TString cut_denom_DY=cut_DY+" && Mjj>350 && Deta>2.5 && nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.17,0.55,0.65,0.87);
  if(plot_log)
    leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30>2, M_{jj}>350, #Delta#eta>2.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm7";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}









void plot_ROC_jet_eta4(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF+"&& nJets30>2";
  TString cut_denom_VBF=cut_VBF+"&& nJets30>2";
  TString cut_num_DY=cut_DY+"&& nJets30>2";
  TString cut_denom_DY=cut_DY+"&& nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));

  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj_forw_jet>150 && Deta_forw_jet>1.5",cut_denom_VBF,cut_num_DY+" && Mjj_forw_jet>150 && Deta_forw_jet>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));



  
  vector<TString> leg_entry;
  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm forw jets");

  leg_entry.push_back("Default + VBF very loose");
  leg_entry.push_back("#splitline{3 jets perm forw jets}{+ VBF very loose}");


  TLegend* leg=new TLegend(0.17,0.55,0.65,0.87);
  if(plot_log)
    leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30>2");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_jet_eta4";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_ROC_3jet_perm8(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF+"&& nJets30>2 && Mjj>150 && Deta>1.5 && perm0_VBFvloose && perm1_VBFvloose && perm2_VBFvloose";
  TString cut_denom_VBF=cut_VBF+"&& nJets30>2 && Mjj>150 && Deta>1.5 && perm0_VBFvloose && perm1_VBFvloose && perm2_VBFvloose";
  TString cut_num_DY=cut_DY+"&& nJets30>2 && Mjj>150 && Deta>1.5 && perm0_VBFvloose && perm1_VBFvloose && perm2_VBFvloose";
  TString cut_denom_DY=cut_DY+"&& nJets30>2 && Mjj>150 && Deta>1.5 && perm0_VBFvloose && perm1_VBFvloose && perm2_VBFvloose";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_VBFvloose(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");
  leg_entry.push_back("3 jets perm VBFvloose");


  TLegend* leg=new TLegend(0.17,0.55,0.65,0.87);
  if(plot_log)
    leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30>2, M_{jj}>150, #Delta#eta>1.5");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm8";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_3jet_perm9(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + "&& nJets30>2";
  TString cut_denom_VBF=cut_VBF + "&& nJets30>2";
  TString cut_num_DY=cut_DY + "&& nJets30>2";
  TString cut_denom_DY=cut_DY + "&& nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));

  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("Default + VBF very loose");
  leg_entry.push_back("#splitline{3 jets perm max LR}{+ VBF very loose}");


  TLegend* leg=new TLegend(0.2,0.5,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm9";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_3jet_perm10(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF + "&& nJets30>2";
  TString cut_denom_VBF=cut_VBF + "&& nJets30>2";
  TString cut_num_DY=cut_DY + "&& nJets30>2";
  TString cut_denom_DY=cut_DY + "&& nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm1(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));

  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm1(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF+" && Mjj>150 && Deta>1.5",cut_denom_VBF,cut_num_DY+" && Mjj>150 && Deta>1.5",cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm 1");
  leg_entry.push_back("Default + VBF very loose");
  leg_entry.push_back("3 jets perm 1 + VBF very loose");


  TLegend* leg=new TLegend(0.2,0.5,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.4,0.15,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm10";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}











void plot_ROC_3jet_perm2_DYEmb(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_Emb_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");


  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";


  TString cut_num_VBF=cut_VBF + "&& nJets30>2";
  TString cut_denom_VBF=cut_VBF + "&& nJets30>2";
  TString cut_num_DY=cut_DY + "&& nJets30>2";
  TString cut_denom_DY=cut_DY + "&& nJets30>2";

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.3,0.35,0.6,0.85);
  if(plot_log)
    leg=new TLegend(0.45,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm2_DYEmb";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_ROC_3jet_perm3_DYEmb(bool plot_log=true){

  vector<TString> file_sig;
   file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");



  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_Emb_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  TString cut_num_VBF=cut_VBF;
  TString cut_denom_VBF=cut_VBF;
  TString cut_num_DY=cut_DY;
  TString cut_denom_DY=cut_DY;

  vector<TGraphErrors*> ROC;
  ROC.push_back(get_ROC_LR_perm0(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_maxLR(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));
  ROC.push_back(get_ROC_LR_perm_forwjets(file_sig[0],file_bkg[0],"outTreePtOrd",cut_num_VBF,cut_denom_VBF,cut_num_DY,cut_denom_DY, 10000,plot_log,0.000002,weight_VBF,weight_DY));


  
  vector<TString> leg_entry;

  leg_entry.push_back("Default");
  leg_entry.push_back("3 jets perm sum weights");
  leg_entry.push_back("3 jets perm max LR");
  leg_entry.push_back("3 jets perm forw jets");


  TLegend* leg=new TLegend(0.2,0.6,0.6,0.87);
  //if(plot_log)
  //leg=new TLegend(0.45,0.1,0.8,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  //leg->SetHeader("nJets30#geq3");

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  ROC[0]->SetMinimum(0.0001);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();
  c->SetGrid();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  


  TString filename="ROC_LR_3jet_perm3_DYEmb";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}
