#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "TMVAClassification.C"




void TrainBDT_3D(){

  TString filename_sig = "/data_CMS/cms/strebler/VBF_Samples/nTupleVBFH125_MuTau_nominal/nTupleVBFH125_MuTau_nominal.root";
  TString filename_bkg = "/data_CMS/cms/strebler/DY_Samples/nTupleDYJets2JetsTauTau_MuTau_nominal/nTupleDYJets2JetsTauTau_MuTau_nominal.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DY2jets.root";

  TMVAClassification_3D(filename_sig, filename_bkg, outfileName);


}




void TrainBDT_4DMEM(){

  TString filename_sig = "/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root";
  TString filename_bkg = "/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DY2jets.root";

  TMVAClassification_4DMEM(filename_sig, filename_bkg, outfileName, "IntegralVBF/(IntegralVBF+0.000001*IntegralDY)");


}





void TrainBDT_3D_Emb(){

  TString filename_sig = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root";
  TString filename_bkg = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root";

  TMVAClassification_3D(filename_sig, filename_bkg, outfileName);


}




void TrainBDT_4DMEM_Emb(){

  TString filename_sig = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root";
  TString filename_bkg = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root";

  TMVAClassification_4DMEM(filename_sig, filename_bkg, outfileName, "IntegralVBF/(IntegralVBF+0.000002*IntegralDY)");


}






void TrainBDT_2DMEM_Emb(){

  TString filename_sig = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root";
  TString filename_bkg = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_2DMEM_DY5D_VBF_DYEmb.root";

  TMVAClassification_2DMEM(filename_sig, filename_bkg, outfileName);


}





void TrainBDT_2DMEM_log_Emb(){

  TString filename_sig = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root";
  TString filename_bkg = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_2DMEM_log_DY5D_VBF_DYEmb.root";

  TMVAClassification_2DMEM_log(filename_sig, filename_bkg, outfileName);


}






void TrainBDT_5DMEM_log_Emb(){

  TString filename_sig = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root";
  TString filename_bkg = "/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root";
  TString outfileName = "/data_CMS/cms/strebler/BDT_rootfiles/BDT_5DMEM_log_DY5D_VBF_DYEmb.root";

  TMVAClassification_5DMEM_log(filename_sig, filename_bkg, outfileName);


}

