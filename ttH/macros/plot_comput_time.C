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



void plot_time_total(){

  TH1F* h=single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttbar_SL+CompTime_ttbar_DL)/3600.","category==41",42,0,7);
  h->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttbar_SL+CompTime_ttbar_DL)/3600.","category==41",42,0,7));
  h->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root","T","(CompTime_ttH+CompTime_ttZ+CompTime_ttbar_SL+CompTime_ttbar_DL)/3600.","category==41",42,0,7));

  h->SetLineColor(1);
  h->SetLineWidth(2);
  h->Sumw2();
  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("Comp. time [h]");
  h->GetYaxis()->SetTitle("Fraction of events / 10 min");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw();

  cout<<"Average time:"<<h->GetMean()<<endl;
  cout<<"Max value:"<<h->GetXaxis()->GetBinCenter(h->FindLastBinAbove(0))<<endl;

  TLatex *texl = new TLatex(0.01,1.01*h->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_total";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_time_total2(){

  TH1F* h=single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","(CompTime_ttH+CompTime_ttW+CompTime_ttbar_DL)/3600.","category==11",18,0,3);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  h->Sumw2();
  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("Comp. time [h]");
  h->GetYaxis()->SetTitle("Fraction of events / 10 min");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw();

  cout<<"Average time:"<<h->GetMean()<<endl;
  cout<<"Max value:"<<h->GetXaxis()->GetBinCenter(h->FindLastBinAbove(0))<<endl;

  TLatex *texl = new TLatex(0.01,1.01*h->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_total2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_time_per_weight(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttH)/3600.","category==41",30,0,5));
  h[0]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttH)/3600.","category==41",30,0,5));
  h[0]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root","T","(CompTime_ttH)/3600.","category==41",30,0,5));

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttZ)/3600.","category==41",30,0,5));
  h[1]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttZ)/3600.","category==41",30,0,5));
  h[1]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root","T","(CompTime_ttZ)/3600.","category==41",30,0,5));

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttbar_SL)/3600.","category==41",30,0,5));
  h[2]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttbar_SL)/3600.","category==41",30,0,5));
  h[2]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root","T","(CompTime_ttbar_SL)/3600.","category==41",30,0,5));

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttbar_DL)/3600.","category==41",30,0,5));
  h[3]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root","T","(CompTime_ttbar_DL)/3600.","category==41",30,0,5));
  h[3]->Add(single_plot("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root","T","(CompTime_ttbar_DL)/3600.","category==41",30,0,5));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("ttZ weight");
  leg_entry.push_back("t#bar{t} l+jets weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");


  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);

    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [h]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 10 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_per_weight";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_time_per_weight2(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","(CompTime_ttH)/3600.","category==11",18,0,3));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","(CompTime_ttbar_DL)/3600.","category==11",18,0,3));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","(CompTime_ttW)/3600.","category==11",18,0,3));
 

  vector<TString> leg_entry;
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("ttW weight");


  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);

    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [h]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 10 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_per_weight2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttH(){

  vector<TString> ttbar_files;
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");


  TH2F* h=single_plot2D(ttbar_files,"T","Sum$(include_perm_ttH)","CompTime_ttH/60.","category==41",25,0,25,150,0,150);

  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h->GetXaxis()->SetTitle("#perm");
  h->GetYaxis()->SetTitle("Comp. time [min]");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw("colz");

  TLatex *texl = new TLatex(0.01,151,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_time_ttH2(){



  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","Sum$(include_perm_ttH)","CompTime_ttH/60.","category==11",25,0,25,150,0,150);

  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetXaxis()->SetTitle("#perm");
  h->GetYaxis()->SetTitle("Comp. time [min]");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw("colz");

  TLatex *texl = new TLatex(0.01,151,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_ttH2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_time_ttbar_SL(){

  vector<TString> ttbar_files;
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");


  TH2F* h=single_plot2D(ttbar_files,"T","Sum$(include_perm_ttbar_SL)","CompTime_ttbar_SL/60.","category==41",25,0,25,80,0,80);

  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetXaxis()->SetTitle("#perm");
  h->GetYaxis()->SetTitle("Comp. time [min]");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw("colz");

  TLatex *texl = new TLatex(0.01,81,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_ttbar_SL";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_time_ttbar_DL(){

  vector<TString> ttbar_files;
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  ttbar_files.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");


  TH2F* h=single_plot2D(ttbar_files,"T","Sum$(include_perm_ttbar_DL)","CompTime_ttbar_DL/60.","category==41",7,0,7,10,0,10);

  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetXaxis()->SetTitle("#perm");
  h->GetYaxis()->SetTitle("Comp. time [min]");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw("colz");

  TLatex *texl = new TLatex(0.01,12.25,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_ttbar_SL";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_time_ttbar_DL2(){



  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","Sum$(include_perm_ttbar_DL)","CompTime_ttbar_DL/60.","category==11",7,0,7,10,0,10);

  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetXaxis()->SetTitle("#perm");
  h->GetYaxis()->SetTitle("Comp. time [min]");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw("colz");

  TLatex *texl = new TLatex(0.01,10.25,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_ttbar_DL2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_time_ttW(){



  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root","T","Sum$(include_perm_ttW)","CompTime_ttW/60.","category==11",7,0,7,10,0,10);

  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetXaxis()->SetTitle("#perm");
  h->GetYaxis()->SetTitle("Comp. time [min]");
  h->GetYaxis()->SetTitleOffset(1.7);

  h->Draw("colz");

  TLatex *texl = new TLatex(0.01,10.25,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttH_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttH/60.","category==11 && integration_type==0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttH/60.","category==11 && integration_type==0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttH/60.","category==11 && integration_type==0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttH/60.","category==11 && integration_type==0",100,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttH/60.","category==11 && integration_type==0",100,0,10));

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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [min]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.1 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttH_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttH_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttH/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttH/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttH/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttH/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttH/60.","category==11 && integration_type==1",100,0,100));

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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [min]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 1 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttH_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttZ_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttZ/60.","category==11 && integration_type==0",100,0,30));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttZ/60.","category==11 && integration_type==0",100,0,30));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttZ/60.","category==11 && integration_type==0",100,0,30));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttZ/60.","category==11 && integration_type==0",100,0,30));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttZ/60.","category==11 && integration_type==0",100,0,30));

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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [min]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 0.3 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttZ_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttZ_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttZ/60.","category==11 && integration_type==1",100,0,200));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttZ/60.","category==11 && integration_type==1",100,0,200));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttZ/60.","category==11 && integration_type==1",100,0,200));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttZ/60.","category==11 && integration_type==1",100,0,200));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttZ/60.","category==11 && integration_type==1",100,0,200));

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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<60*h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [min]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 2 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttZ_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttZ_Zll_nomiss_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==0",100,0,25));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==0",100,0,25));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==0",100,0,25));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==0",100,0,25));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==0",100,0,25));

  vector<TString> leg_entry;
  leg_entry.push_back("500 points");
  leg_entry.push_back("1.25k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points (nominal)");
  leg_entry.push_back("10k points");

  TLegend* leg=new TLegend(0.5,0.5,0.85,0.85);
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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<60*h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [min]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 2.5 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttZ_nomiss_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttZ_Zll_missing_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==1",100,0,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttZ_Zll/60.","category==11 && integration_type==1",100,0,100));

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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<60*h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [min]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 1 min");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttZ_Zll_missing_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_time_ttbar_fakelep_from_tlep_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttbar_DL_fakelep_tlep","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttbar_DL_fakelep_tlep","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttbar_DL_fakelep_tlep","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttbar_DL_fakelep_tlep","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttbar_DL_fakelep_tlep","category==11",100,0,150));

  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.5,0.5,0.8,0.85);
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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [s]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 15 s");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttbar_DL_fakelep_tlep_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_time_ttbar_fakelep_from_ttau_122016(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T","CompTime_ttbar_DL_fakelep_ttau","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T","CompTime_ttbar_DL_fakelep_ttau","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T","CompTime_ttbar_DL_fakelep_ttau","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T","CompTime_ttbar_DL_fakelep_ttau","category==11",100,0,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T","CompTime_ttbar_DL_fakelep_ttau","category==11",100,0,150));

  vector<TString> leg_entry;
  leg_entry.push_back("1k points");
  leg_entry.push_back("2.5k points");
  leg_entry.push_back("5k points");
  leg_entry.push_back("10k points (nominal)");
  leg_entry.push_back("20k points");

  TLegend* leg=new TLegend(0.5,0.5,0.8,0.85);
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
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    cout<<leg_entry[i]<<endl;
    cout<<"Average time:"<<h[i]->GetMean()<<endl;
    cout<<"Max value:"<<h[i]->GetXaxis()->GetBinCenter(h[i]->FindLastBinAbove(0))<<endl;
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetTitle("");
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Comp. time [s]");
  h[0]->GetYaxis()->SetTitle("Fraction of events / 15 s");
  h[0]->GetYaxis()->SetTitleOffset(1.7);

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");

 

  TString filename="CompTime_ttbar_DL_fakelep_ttau_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

