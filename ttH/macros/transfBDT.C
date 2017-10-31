#include "TFile.h"
#include "TGraph.h"

static TGraph* g1l2tau = 0;

float transfBDT_1l2tau(float val){
  if(g1l2tau==0){
    TFile* f = new TFile("transfBDT.root","READ");
    g1l2tau = (TGraph*)f->Get("graph_transformation_1l2tau");
  }
  //  g->Print();
  return g1l2tau->Eval(val);


}





static TGraph* g2lSS1tau_nomiss = 0;

float transfBDT_2lSS1tau_nomiss(float val){
  if(g2lSS1tau_nomiss==0){
    TFile* f = new TFile("transfBDT.root","READ");
    g2lSS1tau_nomiss = (TGraph*)f->Get("graph_transformation_2lss1tau_nomiss");
  }
  //  g->Print();
  return g2lSS1tau_nomiss->Eval(val);


}




static TGraph* g2lSS1tau_missing = 0;

float transfBDT_2lSS1tau_missing(float val){
  if(g2lSS1tau_missing==0){
    TFile* f = new TFile("transfBDT.root","READ");
    g2lSS1tau_missing = (TGraph*)f->Get("graph_transformation_2lss1tau_missing");
  }
  //  g->Print();
  return g2lSS1tau_missing->Eval(val);


}



