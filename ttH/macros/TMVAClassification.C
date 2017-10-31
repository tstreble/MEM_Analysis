
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"


#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif




void TMVAClassification_3D( TString filename_sig, TString filename_bkg, TString outfileName ){

   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;


   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

 
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_3D", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   factory->AddVariable( "log(Integral_ttH)",'F' );
   factory->AddVariable( "log(Integral_ttZ)",'F' );
   //factory->AddVariable( "log(Integral_ttZ_Zll)",'F' );


   TFile *sinput = TFile::Open( filename_sig );
   TFile *binput = TFile::Open( filename_bkg );

   std::cout << "--- TMVAClassification       : Using sig input file: " << sinput->GetName() << std::endl;
   std::cout << "--- TMVAClassification       : Using bkg input file: " << binput->GetName() << std::endl;
   
   TTree *signal     = (TTree*)sinput->Get("T");
   TTree *background = (TTree*)binput->Get("T");

   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   factory->AddTree(signal, "Signal", signalWeight, "EventNumber%2==0", "train");
   factory->AddTree(signal, "Signal", signalWeight, "EventNumber%2==1", "test");
   factory->AddTree(background, "Background", backgroundWeight, "EventNumber%2==0", "train");
   factory->AddTree(background, "Background", backgroundWeight, "EventNumber%2==1", "test");


   TString weight_ttH = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight";
   TString weight_ttZ = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight";

   factory->SetSignalWeightExpression    (weight_ttH);
   factory->SetBackgroundWeightExpression(weight_ttZ);

   TCut sig_cuts = "category==11 && isTrig && isGenMatched && integration_type==0" ;
   TCut bkg_cuts = "category==11 && isTrig && isGenMatched && integration_type==0" ;

   factory->PrepareTrainingAndTestTree( sig_cuts, bkg_cuts,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Alternate:NormMode=EqualNumEvents:!V" );
   
   if (Use["BDT"])  // Adaptive Boost
     factory->BookMethod( TMVA::Types::kBDT, "BDT",
			  "!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
   
   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

}





