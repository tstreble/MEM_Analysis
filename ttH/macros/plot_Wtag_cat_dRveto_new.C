#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>

using namespace std;




void plot_btag_Wtag_cat(){

  TString filename_ttH="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_12_2015/ntuple_ttH_dRveto_gen_iso70.root";

  TH1F* h_norm=(single_plot(filename_ttH,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0&&recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet30>2)",3,0,3));

  vector<TH1F*> h;


  //Cat.1 - 2 CSVM
  TH1F* h_2CSVM=single_plot(filename_ttH,"HTauTauTree","0","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0&& recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag>0)",9,0,9);
  //Cat.1 - 1 CSVM + 1 CSVL
  TH1F* h_CSVM_CSVL=single_plot(filename_ttH,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag>0)",9,0,9);
  //Cat.1 - Others
  TH1F* h_Others=single_plot(filename_ttH,"HTauTauTree","2","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0 && ((recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423)||recoPFJet30_CSVsort_CSVscore[0]<0.814) && n_pair_Wtag_recoPFJet30_untag>0)",9,0,9);

  //Cat.2 - 2 CSVM
  h_2CSVM->Add(single_plot(filename_ttH,"HTauTauTree","3","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0&&recolep_charge[0]*recotauh_charge[0]<0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1)",9,0,9));

  //Cat.2 - 1 CSVM + 1 CSVL
  h_CSVM_CSVL->Add( single_plot(filename_ttH,"HTauTauTree","4","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recolep_charge[0]*recotauh_charge[0]<0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1)",9,0,9) );

  //Cat.2 - Others
  h_Others->Add(single_plot(filename_ttH,"HTauTauTree","5","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0 && ((recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423)||recoPFJet30_CSVsort_CSVscore[0]<0.814) && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1)",9,0,9));

  //Cat.3 - 2 CSVM
  h_2CSVM->Add(single_plot(filename_ttH,"HTauTauTree","6","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1)",9,0,9));

  //Cat.3 - 1 CSVM + 1 CSVL
  h_CSVM_CSVL->Add( single_plot(filename_ttH,"HTauTauTree","7","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0  &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1)",9,0,9) );

  //Cat.3 - Others
  h_Others->Add(single_plot(filename_ttH,"HTauTauTree","8","MC_weight*PUReweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&recolep_charge[0]*recotauh_charge[0]<0 && ((recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423)||recoPFJet30_CSVsort_CSVscore[0]<0.814) && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1)",9,0,9));


  h.push_back(h_2CSVM);
  h.push_back(h_CSVM_CSVL);
  h.push_back(h_Others);
  
  vector<TString> leg_entry;
  leg_entry.push_back("2 CSVM");
  leg_entry.push_back("1 CSVM + 1CSVL");
  leg_entry.push_back("Others");


  TLegend* leg=new TLegend(0.6,0.7,0.85,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    h[i]->Scale(1/h_norm->Integral());
    cout<<"h[i]->Integral()="<<h[i]->Integral()<<endl;
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.15);
  h[0]->SetMaximum(1.6*h[0]->GetMaximum());
  h[0]->SetMinimum(0);

  h[0]->GetYaxis()->SetTitle("Fraction of events with 2 SS lep., #geq 1 #tau_{h}, #geq 3 jets");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->GetXaxis()->SetLabelSize(0);
  h[0]->GetXaxis()->SetRangeUser(0,9);
  h[0]->GetXaxis()->SetNdivisions(-3);
  h[0]->SetTitle("");


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();      


  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");      

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  vector<TString> cat;
  cat.push_back("Cat.1");
  cat.push_back("Cat.2");
  cat.push_back("Cat.3");

 
  Float_t x, y;
  y = gPad->GetUymin()-0.001;
  TLatex t;

  t.SetTextAngle(60);
  t.SetTextSize(0.03);
  t.SetTextAlign(33);
  for (unsigned int i=0;i<cat.size();i++) {
    x = h[0]->GetXaxis()->GetBinCenter(3*i+2);
    t.DrawLatex(x,y,cat[i]);
  }



  TString filename="btag_Wtag_cat_ttH_dRveto_new";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

