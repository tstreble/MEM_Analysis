#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include "Helpers.C"
#include <vector>
#include "TLatex.h"

using namespace std;






void plot_rel_error_ttH_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.2%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttH_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttH_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttH","category==11 && integration_type==0 && Integral_perm_ttH>0",100,0,20));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttH_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_rel_error_ttH_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttH/Integral_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,50));


  vector<TString> leg_entry;
  leg_entry.push_back("2k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points");
  leg_entry.push_back("20k points (nominal)");
  leg_entry.push_back("40k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.5%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttH_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttH_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttH","category==11 && integration_type==1 && Integral_perm_ttH>0",100,0,40));


  vector<TString> leg_entry;
  leg_entry.push_back("2k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points");
  leg_entry.push_back("20k points (nominal)");
  leg_entry.push_back("40k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttH_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_rel_error_ttZ_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,10));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.1%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttZ_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttZ_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==0 && Integral_perm_ttZ>0",100,0,20));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttZ_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_rel_error_ttZ_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttZ/Integral_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,50));


  vector<TString> leg_entry;
  leg_entry.push_back("2k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points");
  leg_entry.push_back("20k points (nominal)");
  leg_entry.push_back("40k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.5%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttZ_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttZ_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttZ","category==11 && integration_type==1 && Integral_perm_ttZ>0",100,0,40));


  vector<TString> leg_entry;
  leg_entry.push_back("2k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points");
  leg_entry.push_back("20k points (nominal)");
  leg_entry.push_back("40k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttZ_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_rel_error_ttZ_Zll_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,10));


  vector<TString> leg_entry;
  leg_entry.push_back("500 points");
  leg_entry.push_back("1.25k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points (nominal)");
  leg_entry.push_back("10k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.1%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttZ_Zll_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttZ_Zll_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==0 && Integral_perm_ttZ_Zll>0",100,0,20));


  vector<TString> leg_entry;
  leg_entry.push_back("500 points");
  leg_entry.push_back("1.25k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points (nominal)");
  leg_entry.push_back("10k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttZ_Zll_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_rel_error_ttZ_Zll_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttZ_Zll/Integral_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,50));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.5%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttZ_Zll_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttZ_Zll_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttZ_Zll","category==11 && integration_type==1 && Integral_perm_ttZ_Zll>0",100,0,40));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttZ_Zll_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_rel_error_ttbar_DL_fakelep_tlep_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttbar_DL_fakelep_tlep/Integral_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttbar_DL_fakelep_tlep/Integral_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttbar_DL_fakelep_tlep/Integral_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttbar_DL_fakelep_tlep/Integral_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttbar_DL_fakelep_tlep/Integral_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,50));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.5%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttbar_DL_fakelep_tlep_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttbar_DL_fakelep_tlep_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_tlep>0",100,0,40));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttbar_DL_fakelep_tlep_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_rel_error_ttbar_DL_fakelep_ttau_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","100*StdErr_perm_ttbar_DL_fakelep_ttau/Integral_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","100*StdErr_perm_ttbar_DL_fakelep_ttau/Integral_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","100*StdErr_perm_ttbar_DL_fakelep_ttau/Integral_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","100*StdErr_perm_ttbar_DL_fakelep_ttau/Integral_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","100*StdErr_perm_ttbar_DL_fakelep_ttau/Integral_perm_ttbar_DL_fakelep_tlep","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,50));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average error:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<5%:"<<h[i]->Integral(0,h[i]->FindBin(5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Rel. error [%]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.5%");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Rel_error_ttbar_DL_fakelep_ttau_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_chi2_ttbar_DL_fakelep_ttau_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","ChiSquare_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","ChiSquare_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","ChiSquare_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","ChiSquare_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,40));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","ChiSquare_perm_ttbar_DL_fakelep_ttau","category==11 && Integral_perm_ttbar_DL_fakelep_ttau>0",100,0,40));


  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.3,0.5,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral(0,h[i]->GetNbinsX()+1));
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average #chi2:"<<h[i]->GetMean()<<endl;
    cout<<"Fraction<2.5:"<<h[i]->Integral(0,h[i]->FindBin(2.5))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#chi^{2}/dof");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="Chi2_ttbar_DL_fakelep_ttau_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}


