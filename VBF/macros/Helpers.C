#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>

#include <TSystem.h>

using namespace std;

//gSystem->Load("/home/llr/cms/strebler/MG5_aMC_v2_2_1/ExRootAnalysis/libExRootAnalysis.so") before compilation in Root

float binning(TH1F* h){

  float max=h->GetBinLowEdge(h->GetNbinsX()+1);
  float min=h->GetBinLowEdge(1);
  float bin=(max-min)/h->GetNbinsX();
  return bin;
}


TH1F* single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH1F* g=new TH1F("g","g",nbin,min,max);
  g->Sumw2();

  //tree->Draw(var+">>g","puWeight*HLTweightTau*HLTweightMu*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*("+cut+")","goff");
  tree->Draw(var+">>g",cut,"goff");

  //TH1F* g=(TH1F*) ((TH1F*)gDirectory->Get("h"))->Clone();
  //g=(TH1F*) ((TH1F*)gDirectory->Get("h"))->Clone();


  return g;
}






TH2F* single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2){


  TChain * tree = new TChain(tree_name);
  tree->Add(file);


  TH2F* g=new TH2F("g","g",nbin1,min1,max1,nbin2,min2,max2);
  g->Sumw2();

  tree->Draw(var2+":"+var1+">>g",cut,"goff");
  //tree->Draw(var2+":"+var1+">>g","puWeight*HLTweightTau*HLTweightMu*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*("+cut+")","goff");
  return g;
}




TH3F* single_plot3D(TString file, TString tree_name, TString var1, TString var2, TString var3, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2, int nbin3, float min3, float max3){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);


  TH3F* g=new TH3F("g","g",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  g->Sumw2();

  //tree->Draw(var3+":"+var2+":"+var1+">>g","puWeight*HLTweightTau*HLTweightMu*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*("+cut+")","goff");
  tree->Draw(var3+":"+var2+":"+var1+">>g",cut,"goff");


  return g;
}




std::vector<TH1F*> sort_histo(std::vector<TH1F*> h){
  
  float max=0;
  unsigned int imax=0;
  for(unsigned int i=0;i<h.size();i++){
    float m=h[i]->GetMaximum();
    if(m>max){
      max=m;
      imax=i;
    }
  }
  vector<TH1F*> new_h;
  new_h.push_back(h[imax]);
  for(unsigned int i=0;i<h.size();i++){
    if(i!=imax)
      new_h.push_back(h[i]);
  }

  return new_h;
}


