#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include "Helpers_convert_VBF.C"




void convert_tree_VBF(){

  TString sample="VBF";
  convert_tree(sample);
  return;

}



void convert_tree_DY(){

  TString sample="DY";
  convert_tree(sample);
  return;

}



void convert_tree_jet_forward_VBF(){

  //TString sample_in="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_jet_eta_150619.root";
  //TString sample_out="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_jet_eta_150619_converted.root";

  //TString sample_in="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root";
  //TString sample_out="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616_converted.root";

  TString sample_in="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719.root";
  TString sample_out="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root";

  convert_tree_jet_forward(sample_in,sample_out);

}



void convert_tree_jet_forward_DY(){

  //TString sample_in="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_jet_eta_150619.root";
  //TString sample_out="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_jet_eta_150619_converted.root";

  //TString sample_in="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616.root";
  //TString sample_out="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_50_130_diTauVisMass_150616_converted.root";

  TString sample_in="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_Emb_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719.root";
  TString sample_out="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_Emb_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719_converted.root";

  convert_tree_jet_forward(sample_in,sample_out);

}
