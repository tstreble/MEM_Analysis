#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include "Helpers.C"

using namespace std;



void plot2D_Ejet_eq(){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>2.5"; 
  TH2F* h=single_plot2D(file_VBF,"HTauTauTree","genpart_e[recoPFJet30_i_closest_genpart]","recoPFJet30_e",cut,200,0,2000,200,0,2000);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h->SetStats(0);
  h->GetXaxis()->SetTitle("E_{gen} [GeV]");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("E_{reco} [GeV]") ;
  h->GetYaxis()->SetTitleOffset(1.7);
  h->SetTitle("|#eta(reco)|>2.5");

  h->Draw("colz");

  TString filename="2DEjet_Eq_VBF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;
}
