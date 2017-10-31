#include <TFile.h>
#include <TH1F.h>
#include <TGraph.h>
#include <iostream>

using namespace std;



void doTransfBDTFile(vector<TString> datacard_file){

  TFile* f_new = TFile::Open("transfBDT.root","RECREATE");
  /*if(f_new!=0){
    cout<<"transfBDT.root already exists, please delete it before converting again"<<endl;
    return;
    }*/


  for(unsigned int i=0;i<datacard_file.size();i++){


    TFile* f = TFile::Open(datacard_file[i]);

    TH1F* h_sig = (TH1F*)f->Get("x_ttH");
    h_sig->SetDirectory(0);
    f->Close();


    int nbins = h_sig->GetNbinsX();
    TH1F* hc = (TH1F*)h_sig->GetCumulative();
    double xq[nbins];
    double yq[nbins];
    for(int j=0; j<nbins; j++)
      xq[j]=double(j+1)/nbins;

    h_sig->GetQuantiles(nbins,yq,xq);

   for(int j=0; j<nbins; j++)
      cout<<"x="<<xq[j]<<" y="<<yq[j]<<endl;

    TGraph* graph_transformation = new TGraph(nbins, yq, xq);

    if(i==0)
      graph_transformation->SetName("graph_transformation_1l2tau");
    else if(i==1)
      graph_transformation->SetName("graph_transformation_2lss1tau_nomiss");
    else if(i==2)
      graph_transformation->SetName("graph_transformation_2lss1tau_missing");
    else if(i==3)
      graph_transformation->SetName("graph_transformation_3l1tau");

    f_new->cd();
    graph_transformation->Write();


  }


  return;

}



void test(){

  vector<TString> datacard;
  datacard.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017_100bins.root");
  datacard.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017_100bins.root");
  datacard.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017_100bins.root");
  datacard.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_syst_nofaketau_35.9fb_022017.root");

  doTransfBDTFile(datacard);


}
