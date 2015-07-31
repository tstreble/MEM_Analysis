#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <Helpers.C>


TGraphErrors* get_ROC_LR(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_SVFit(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,"diTauNSVfitMass",weight_sig+"*("+cut_num_sig+")",nbin,0,400);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"diTauNSVfitMass",weight_bkg+"*("+cut_num_bkg+")",nbin,0,400);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"diTauNSVfitMass",weight_sig+"*("+cut_denom_sig+")",nbin,0,400);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"diTauNSVfitMass",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,400);


  double N_sig=h_sig_denom->Integral(h_sig_denom->FindBin(0),h_sig_denom->FindBin(400));
  //cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral(h_bkg_denom->FindBin(0),h_bkg_denom->FindBin(400));
  //cout<<"N_bkg="<<N_bkg<<endl;

  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=400./nbin;

  int binup_sig=h_sig->FindBin(400);
  int binup_bkg=h_bkg->FindBin(400);

  for(int i=0;i<nbin+1;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    /*if(abs(sigeff-0.2)<0.001){
      cout<<"n_sig_acc="<<n_sig_acc<<endl;
      cout<<"n_bkg_acc="<<n_bkg_acc<<endl;
      cout<<"x="<<x<<endl;
      cout<<"sigeff="<<sigeff<<endl;
      cout<<"bkgfake="<<bkgfake<<endl;

      }*/
  

    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_3D(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig,  TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=80;
  float min1=0;
  float max1=400;

  int nbin2=18;
  float min2=0;
  float max2=9;

  int nbin3=100;
  float min3=0;
  float max3=3000;

  TH3F* h_sig=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_sig+"*("+cut_denom_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_bkg+"*("+cut_denom_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);

  /*int bin1_up_sig=h_sig->GetXaxis()->FindBin(max1);
  int bin2_up_sig=h_sig->GetYaxis()->FindBin(max2);
  int bin3_up_sig=h_sig->GetZaxis()->FindBin(max3);

  int bin1_up_bkg=h_bkg->GetXaxis()->FindBin(max1);
  int bin2_up_bkg=h_bkg->GetYaxis()->FindBin(max2);
  int bin3_up_bkg=h_bkg->GetZaxis()->FindBin(max3);*/

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;
  int bin3_up_sig=nbin3;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;
  int bin3_up_bkg=nbin3;

  for(int i=0;i<=nbin1;i++){    

    cout<<"i="<<i<<endl;

    for(int j=0;j<=nbin2;j++){
    
      for(int k=0;k<=nbin3;k++){

	double n_sig_acc=h_sig->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
	double n_bkg_acc=h_bkg->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);

	double sigeff=n_sig_acc/N_sig;
	double bkgfake=n_bkg_acc/N_bkg;

	//double ex=sqrt(sigeff*(1-sigeff)/N_sig);
	//double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
	
	int bin_eff = abs(sigeff*nbin);
	if(bkgfake < efficiencies[bin_eff].second){
	  efficiencies[bin_eff].first=sigeff;
	  efficiencies[bin_eff].second=bkgfake;
	}

      }

    }

  }

  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}






vector<TGraphErrors*> get_cutvalues_ROC_3D(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=80;
  float min1=0;
  float max1=400;

  int nbin2=36;
  float min2=0;
  float max2=9;

  int nbin3=100;
  float min3=0;
  float max3=3000;

  TH3F* h_sig=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_sig+"*("+cut_denom_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_bkg+"*("+cut_denom_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);
  vector<double> cut_values_SVfit(nbin,0);
  vector<double> cut_values_Deta(nbin,0);
  vector<double> cut_values_Mjj(nbin,0);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;
  int bin3_up_sig=nbin3;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;
  int bin3_up_bkg=nbin3;

  int cut_x_previous=0;
  int cut_y_previous=0;
  int cut_z_previous=0;

  int cut_x_previous_temp=0;
  int cut_y_previous_temp=0;
  int cut_z_previous_temp=0;

  for(int m=nbin-1; m>=0; m--){

    cout<<"m="<<m<<endl;

    double min_sigeff = (double) m / (double) nbin;

    for(int i=cut_x_previous;i<=nbin1;i++){    

      for(int j=cut_y_previous;j<=nbin2;j++){
	
	for(int k=cut_z_previous;k<=nbin3;k++){
	  
	  double n_sig_acc=h_sig->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
	  double n_bkg_acc=h_bkg->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);
	  
	  double sigeff=n_sig_acc/N_sig;
	  double bkgfake=n_bkg_acc/N_bkg;

	  if(sigeff<min_sigeff)
	    break;
	  
	  //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
	  //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
	  
	  int bin_eff = abs(sigeff*nbin);
	  if(bkgfake < efficiencies[bin_eff].second){
	    efficiencies[bin_eff].first=sigeff;
	    efficiencies[bin_eff].second=bkgfake;
	    
	    cut_x_previous_temp=i;
	    cut_y_previous_temp=j;
	    cut_z_previous_temp=k;
 
	    double xlow_sig=h_sig->GetXaxis()->GetBinLowEdge(i);
	    double ylow_sig=h_sig->GetYaxis()->GetBinLowEdge(j);
	    double zlow_sig=h_sig->GetZaxis()->GetBinLowEdge(k);
	    
	    cut_values_SVfit[bin_eff]=xlow_sig;
	    cut_values_Deta[bin_eff]=ylow_sig;
	    cut_values_Mjj[bin_eff]=zlow_sig;
	    
	  }
	  
	}
	
      }
      
    }

    cut_x_previous=cut_x_previous_temp;
    cut_y_previous=cut_y_previous_temp;
    cut_z_previous=cut_z_previous_temp;

  }

  int npoints=0;

  TGraphErrors* plot_SVfit=new TGraphErrors();
  TGraphErrors* plot_Deta=new TGraphErrors();
  TGraphErrors* plot_Mjj=new TGraphErrors();

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    /*if(sigeff<0.2){
      cout<<"sigeff="<<sigeff<<endl;
      cout<<"mistag_rate="<<efficiencies[n].second<<endl;
      }*/

    double SVfit = cut_values_SVfit[n];
    double Deta = cut_values_Deta[n];
    double Mjj = cut_values_Mjj[n];

    //double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      plot_SVfit->SetPoint(npoints,sigeff,SVfit);
      plot_Deta->SetPoint(npoints,sigeff,Deta);
      plot_Mjj->SetPoint(npoints,sigeff,Mjj);            

      npoints++;

    }
  }

  vector<TGraphErrors*> plots;
  plots.push_back(plot_SVfit);
  plots.push_back(plot_Deta);
  plots.push_back(plot_Mjj);  

  return plots;
}
  








TGraphErrors* get_ROC_2D_LR_SVfit(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=100;
  float min1=0;
  float max1=27;

  int nbin2=80;
  float min2=0;
  float max2=400;


  TH2F* h_sig=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"diTauNSVfitMass",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"diTauNSVfitMass",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+")",3,0,3,3,0,3);
  TH2F* h_bkg_denom=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+")",3,0,3,3,0,3);

  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;

  double step_x=25./nbin1;

  for(int i=0;i<=nbin1;i++){    

    if(i%10==0)
      cout<<"i="<<i<<endl;

    double x=i*step_x;
    int binlow_x_sig=h_sig->GetXaxis()->FindBin(x);
    int binlow_x_bkg=h_bkg->GetXaxis()->FindBin(x);

    for(int j=0;j<=nbin2;j++){
    

      double n_sig_acc=h_sig->Integral(binlow_x_sig,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg->Integral(binlow_x_sig,bin1_up_bkg,j,bin2_up_bkg);

      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;
      }      

    }

  }

  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}






TGraphErrors* get_ROC_2D_LR_Deta(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true,float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=100;
  float min1=0;
  float max1=27;

  int nbin2=18;
  float min2=0;
  float max2=9;


  TH2F* h_sig=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Deta",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Deta",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2);


  TH2F* h_sig_denom=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+")",3,0,3,3,0,3);
  TH2F* h_bkg_denom=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+")",3,0,3,3,0,3);


  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;

 double step_x=25./nbin1;

  for(int i=0;i<=nbin1;i++){    
    
    if(i%10==0)
      cout<<"i="<<i<<endl;

    double x=i*step_x;
    int binlow_x_sig=h_sig->GetXaxis()->FindBin(x);
    int binlow_x_bkg=h_bkg->GetXaxis()->FindBin(x);

    for(int j=0;j<=nbin2;j++){
    

      double n_sig_acc=h_sig->Integral(binlow_x_sig,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg->Integral(binlow_x_bkg,bin1_up_bkg,j,bin2_up_bkg);

      
      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;
      }      

    }

  }

  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}






TGraphErrors* get_ROC_2D_LR_Mjj(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=100;
  float min1=0;
  float max1=27;

  int nbin2=100;
  float min2=0;
  float max2=3000;

  TH2F* h_sig=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Mjj",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Mjj",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+")",3,0,3,3,0,3);
  TH2F* h_bkg_denom=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+")",3,0,3,3,0,3);


  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;


  double step_x=25./nbin1;

  for(int i=0;i<=nbin1;i++){    

    cout<<"i="<<i<<endl;

    double x=i*step_x;
    int binlow_x_sig=h_sig->GetXaxis()->FindBin(x);
    int binlow_x_bkg=h_bkg->GetXaxis()->FindBin(x);

    for(int j=0;j<=nbin2;j++){
    

      double n_sig_acc=h_sig->Integral(binlow_x_sig,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg->Integral(binlow_x_bkg,bin1_up_bkg,j,bin2_up_bkg);

      
      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;
      }      

    }

  }

  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}







TGraphErrors* get_ROC_2D_Deta_Mjj(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){


  int nbin1=18;
  float min1=0;
  float max1=9;

  int nbin2=100;
  float min2=0;
  float max2=3000;

  TH2F* h_sig=single_plot2D(file_sig,tree_name,"Deta","Mjj",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg=single_plot2D(file_bkg,tree_name,"Deta","Mjj",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+")",3,0,3,3,0,3);
  TH2F* h_bkg_denom=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+")",3,0,3,3,0,3);

  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;

  for(int i=0;i<=nbin1;i++){    

    cout<<"i="<<i<<endl;

    for(int j=0;j<=nbin2;j++){
    
      double n_sig_acc=h_sig->Integral(i,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg->Integral(i,bin1_up_bkg,j,bin2_up_bkg);
      
      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;
      }      

    }

  }

  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}








TGraphErrors* get_ROC_LR_BDTrootfiles(TString file_sig, TString file_bkg, TString tree_name, int nbin=100, bool mistag_rate=true, TString cut="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,"-log(1-LR)","classID==0 &&" + cut,nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"-log(1-LR)","classID==1 &&" + cut,nbin,0,27);


  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1","classID==0 &&" + cut,nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1","classID==1 &&" + cut,nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  int binup_sig=h_sig->FindBin(27);
  int binup_bkg=h_bkg->FindBin(27);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;
 

    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}








TGraphErrors* get_ROC_BDT_BDTrootfiles(TString file_sig, TString file_bkg, TString tree_name, int nbin=100, bool mistag_rate=true, TString cut="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,"BDT","classID==0 &&" + cut,nbin,-1,1);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,"BDT","classID==1 &&" + cut,nbin,-1,1);


  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"0","classID==0 &&" + cut,nbin,-1,1);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"0","classID==1 &&" + cut,nbin,-1,1);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=2./nbin;

  int binup_sig=h_sig->FindBin(1);
  int binup_bkg=h_bkg->FindBin(1);

  for(int i=0;i<=nbin;i++){
    double x=-1+i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  ROC->SetPoint(n,0,0);


  return ROC;


}





TGraphErrors* get_ROC_3D_forw_jets(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=80;
  float min1=0;
  float max1=400;

  int nbin2=18;
  float min2=0;
  float max2=9;

  int nbin3=100;
  float min3=0;
  float max3=3000;

  TH3F* h_sig=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta_forw_jet","Mjj_forw_jet",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta_forw_jet","Mjj_forw_jet",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta_forw_jet","Mjj_forw_jet",weight_sig+"*("+cut_denom_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta_forw_jet","Mjj_forw_jet",weight_bkg+"*("+cut_denom_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);

  /*int bin1_up_sig=h_sig->GetXaxis()->FindBin(max1);
  int bin2_up_sig=h_sig->GetYaxis()->FindBin(max2);
  int bin3_up_sig=h_sig->GetZaxis()->FindBin(max3);

  int bin1_up_bkg=h_bkg->GetXaxis()->FindBin(max1);
  int bin2_up_bkg=h_bkg->GetYaxis()->FindBin(max2);
  int bin3_up_bkg=h_bkg->GetZaxis()->FindBin(max3);*/

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;
  int bin3_up_sig=nbin3;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;
  int bin3_up_bkg=nbin3;

  for(int i=0;i<=nbin1;i++){    

    cout<<"i="<<i<<endl;

    for(int j=0;j<=nbin2;j++){
    
      for(int k=0;k<=nbin3;k++){

	double n_sig_acc=h_sig->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
	double n_bkg_acc=h_bkg->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);

	double sigeff=n_sig_acc/N_sig;
	double bkgfake=n_bkg_acc/N_bkg;

	//double ex=sqrt(sigeff*(1-sigeff)/N_sig);
	//double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
	
	int bin_eff = abs(sigeff*nbin);
	if(bkgfake < efficiencies[bin_eff].second){
	  efficiencies[bin_eff].first=sigeff;
	  efficiencies[bin_eff].second=bkgfake;
	}

      }

    }

  }

  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}








TGraphErrors* get_ROC_3D_smooth(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=80;
  float min1=0;
  float max1=400;

  int nbin2=36;
  float min2=0;
  float max2=9;

  int nbin3=100;
  float min3=0;
  float max3=3000;

  TH3F* h_sig=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_sig+"*("+cut_num_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_bkg+"*("+cut_num_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_sig+"*("+cut_denom_sig+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj",weight_bkg+"*("+cut_denom_bkg+")",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  double N_sig=h_sig_denom->Integral();
  double N_bkg=h_bkg_denom->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);


  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;
  int bin3_up_sig=nbin3;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;
  int bin3_up_bkg=nbin3;


  int cut_x_previous=0;
  int cut_y_previous=0;
  int cut_z_previous=0;

  int cut_x_previous_temp=0;
  int cut_y_previous_temp=0;
  int cut_z_previous_temp=0;

  for(int m=nbin-1; m>=0; m--){

    cout<<"m="<<m<<endl;

    double min_sigeff = (double) m / (double) nbin;

    for(int i=cut_x_previous;i<=nbin1;i++){    

      for(int j=cut_y_previous;j<=nbin2;j++){
	
	for(int k=cut_z_previous;k<=nbin3;k++){
	  
	  double n_sig_acc=h_sig->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
	  double n_bkg_acc=h_bkg->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);
	  
	  double sigeff=n_sig_acc/N_sig;
	  double bkgfake=n_bkg_acc/N_bkg;

	  if(sigeff<min_sigeff)
	    break;
	  
	  //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
	  //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
	  
	  int bin_eff = abs(sigeff*nbin);
	  if(bkgfake < efficiencies[bin_eff].second){
	    efficiencies[bin_eff].first=sigeff;
	    efficiencies[bin_eff].second=bkgfake;
	    
	    cut_x_previous_temp=i;
	    cut_y_previous_temp=j;
	    cut_z_previous_temp=k;
	    
	  }
	  
	}
	
      }
      
    }

    cut_x_previous=cut_x_previous_temp;
    cut_y_previous=cut_y_previous_temp;
    cut_z_previous=cut_z_previous_temp;

  }


  int npoints=0;

  for(int n=0;n<nbin;n++){
    	
    double sigeff = efficiencies[n].first;
    double bkgfake = efficiencies[n].second;

    if(sigeff>0){

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}











TGraphErrors* get_ROC_3D_smooth_unbiased(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=80;
  float min1=0;
  float max1=400;

  int nbin2=36;
  float min2=0;
  float max2=9;

  int nbin3=100;
  float min3=0;
  float max3=3000;

  TH3F* h_sig_optim=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_num_sig + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_optim=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_num_bkg + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom_optim=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_denom_sig + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom_optim=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_denom_bkg + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  double N_sig=h_sig_denom_optim->Integral();
  double N_bkg=h_bkg_denom_optim->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);
  vector<double> cut_values_SVfit(nbin,0);
  vector<double> cut_values_Deta(nbin,0);
  vector<double> cut_values_Mjj(nbin,0);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;
  int bin3_up_sig=nbin3;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;
  int bin3_up_bkg=nbin3;

  int cut_x_previous=0;
  int cut_y_previous=0;
  int cut_z_previous=0;

  int cut_x_previous_temp=0;
  int cut_y_previous_temp=0;
  int cut_z_previous_temp=0;

  for(int m=nbin-1; m>=0; m--){

    cout<<"m="<<m<<endl;

    double min_sigeff = (double) m / (double) nbin;

    for(int i=cut_x_previous;i<=nbin1;i++){    

      for(int j=cut_y_previous;j<=nbin2;j++){
	
	for(int k=cut_z_previous;k<=nbin3;k++){
	  
	  double n_sig_acc=h_sig_optim->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
	  double n_bkg_acc=h_bkg_optim->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);
	  
	  double sigeff=n_sig_acc/N_sig;
	  double bkgfake=n_bkg_acc/N_bkg;

	  if(sigeff<min_sigeff)
	    break;
	  
	  //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
	  //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
	  
	  int bin_eff = abs(sigeff*nbin);
	  if(bkgfake < efficiencies[bin_eff].second){
	    efficiencies[bin_eff].first=sigeff;
	    efficiencies[bin_eff].second=bkgfake;
	    
	    cut_x_previous_temp=i;
	    cut_y_previous_temp=j;
	    cut_z_previous_temp=k;
 
	    double xlow_sig=h_sig_optim->GetXaxis()->GetBinLowEdge(i);
	    double ylow_sig=h_sig_optim->GetYaxis()->GetBinLowEdge(j);
	    double zlow_sig=h_sig_optim->GetZaxis()->GetBinLowEdge(k);
	    
	    cut_values_SVfit[bin_eff]=xlow_sig;
	    cut_values_Deta[bin_eff]=ylow_sig;
	    cut_values_Mjj[bin_eff]=zlow_sig;
	    
	  }
	  
	}
	
      }
      
    }

    cut_x_previous=cut_x_previous_temp;
    cut_y_previous=cut_y_previous_temp;
    cut_z_previous=cut_z_previous_temp;

  }


  TH3F* h_sig_appl=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_num_sig + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_appl=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_num_bkg + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom_appl=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_denom_sig + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom_appl=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_denom_bkg + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  N_sig=h_sig_denom_appl->Integral();
  N_bkg=h_bkg_denom_appl->Integral();
 
  ROC->SetPoint(0,0,0);
  int npoints=1;

  for(int n=0;n<nbin;n++){

    double SVfit = cut_values_SVfit[n];
    double Deta = cut_values_Deta[n];
    double Mjj = cut_values_Mjj[n];

    int i=h_sig_appl->GetXaxis()->FindBin(SVfit);
    int j=h_sig_appl->GetYaxis()->FindBin(Deta);
    int k=h_sig_appl->GetZaxis()->FindBin(Mjj);

    double n_sig_acc=h_sig_appl->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
    double n_bkg_acc=h_bkg_appl->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);
	  
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;
 

    if(sigeff>0 && sigeff<1){
  
      cout<<endl;
      cout<<"SVfit>"<<SVfit<<"; Deta>"<<Deta<<"; Mjj>"<<Mjj<<endl;
      cout<<"i="<<i<<"; j="<<j<<"; k="<<k<<endl;
      cout<<"sigeff="<<sigeff<<"; bkgfake="<<bkgfake<<endl;

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}



TGraphErrors* get_ROC_3D_unbiased(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=80;
  float min1=0;
  float max1=400;

  int nbin2=36;
  float min2=0;
  float max2=9;

  int nbin3=100;
  float min3=0;
  float max3=3000;

  TH3F* h_sig_optim=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_num_sig + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_optim=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_num_bkg + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom_optim=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_denom_sig + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom_optim=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_denom_bkg + "&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  double N_sig=h_sig_denom_optim->Integral();
  double N_bkg=h_bkg_denom_optim->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);
  vector<double> cut_values_SVfit(nbin,0);
  vector<double> cut_values_Deta(nbin,0);
  vector<double> cut_values_Mjj(nbin,0);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;
  int bin3_up_sig=nbin3;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;
  int bin3_up_bkg=nbin3;

  for(int i=0;i<=nbin1;i++){    
    
    cout<<"i="<<i<<endl;

    for(int j=0;j<=nbin2;j++){
	
      for(int k=0;k<=nbin3;k++){
	  
	double n_sig_acc=h_sig_optim->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
	double n_bkg_acc=h_bkg_optim->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);
	
	double sigeff=n_sig_acc/N_sig;
	double bkgfake=n_bkg_acc/N_bkg;
	
	
	//double ex=sqrt(sigeff*(1-sigeff)/N_sig);
	//double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
	
	int bin_eff = abs(sigeff*nbin);
	if(bkgfake < efficiencies[bin_eff].second){
	  efficiencies[bin_eff].first=sigeff;
	  efficiencies[bin_eff].second=bkgfake;
 
	  double xlow_sig=h_sig_optim->GetXaxis()->GetBinLowEdge(i);
	  double ylow_sig=h_sig_optim->GetYaxis()->GetBinLowEdge(j);
	  double zlow_sig=h_sig_optim->GetZaxis()->GetBinLowEdge(k);
	  
	  cut_values_SVfit[bin_eff]=xlow_sig;
	  cut_values_Deta[bin_eff]=ylow_sig;
	  cut_values_Mjj[bin_eff]=zlow_sig;
	  
	}
	
      }
      
    }
    
  }


  TH3F* h_sig_appl=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_num_sig + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_appl=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_num_bkg + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  TH3F* h_sig_denom_appl=single_plot3D(file_sig,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_sig + "*(" + cut_denom_sig + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);
  TH3F* h_bkg_denom_appl=single_plot3D(file_bkg,tree_name,"diTauNSVfitMass","Deta","Mjj", weight_bkg + "*(" + cut_denom_bkg + "&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3);

  N_sig=h_sig_denom_appl->Integral();
  N_bkg=h_bkg_denom_appl->Integral();
 
  ROC->SetPoint(0,0,0);
  int npoints=1;

  for(int n=0;n<nbin;n++){

    double SVfit = cut_values_SVfit[n];
    double Deta = cut_values_Deta[n];
    double Mjj = cut_values_Mjj[n];

    int i=h_sig_appl->GetXaxis()->FindBin(SVfit);
    int j=h_sig_appl->GetYaxis()->FindBin(Deta);
    int k=h_sig_appl->GetZaxis()->FindBin(Mjj);

    double n_sig_acc=h_sig_appl->Integral(i,bin1_up_sig,j,bin2_up_sig,k,bin3_up_sig);
    double n_bkg_acc=h_bkg_appl->Integral(i,bin1_up_bkg,j,bin2_up_bkg,k,bin3_up_bkg);
	  
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;
 

    if(sigeff>0 && sigeff<1){
  
      cout<<endl;
      cout<<"SVfit>"<<SVfit<<"; Deta>"<<Deta<<"; Mjj>"<<Mjj<<endl;
      cout<<"i="<<i<<"; j="<<j<<"; k="<<k<<endl;
      cout<<"sigeff="<<sigeff<<"; bkgfake="<<bkgfake<<endl;

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}








TGraphErrors* get_ROC_2D_LR_SVfit_unbiased(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=100;
  float min1=0;
  float max1=27;

  int nbin2=80;
  float min2=0;
  float max2=400;


  TH2F* h_sig_optim=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"diTauNSVfitMass",weight_sig+"*("+cut_num_sig+"&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg_optim=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"diTauNSVfitMass",weight_bkg+"*("+cut_num_bkg+"&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom_optim=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+"&& event%2==0)",3,0,3,3,0,3);
  TH2F* h_bkg_denom_optim=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+"&& event%2==0)",3,0,3,3,0,3);


  double N_sig=h_sig_denom_optim->Integral();
  double N_bkg=h_bkg_denom_optim->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);
  vector<double> cut_values_LR(nbin,0);
  vector<double> cut_values_SVfit(nbin,0);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;


  double step_x=25./nbin1;

  for(int i=0;i<=nbin1;i++){    

    if(i%10==0)
      cout<<"i="<<i<<endl;

    double x=i*step_x;
    int binlow_x_sig=h_sig_optim->GetXaxis()->FindBin(x);
    int binlow_x_bkg=h_bkg_optim->GetXaxis()->FindBin(x);

    for(int j=0;j<=nbin2;j++){
    

      double n_sig_acc=h_sig_optim->Integral(binlow_x_sig,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg_optim->Integral(binlow_x_bkg,bin1_up_bkg,j,bin2_up_bkg);

      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;      
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;

	double xlow_sig=x;
	double ylow_sig=h_sig_optim->GetYaxis()->GetBinLowEdge(j);
	
	cut_values_LR[bin_eff]=xlow_sig;
	cut_values_SVfit[bin_eff]=ylow_sig;
	
      }	  	
      
    }
    
  }


  TH2F* h_sig_appl=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"diTauNSVfitMass",weight_sig+"*("+cut_num_sig+"&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg_appl=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"diTauNSVfitMass",weight_bkg+"*("+cut_num_bkg+"&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom_appl=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+"&& event%2==1)",3,0,3,3,0,3);
  TH2F* h_bkg_denom_appl=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+"&& event%2==1)",3,0,3,3,0,3);


  N_sig=h_sig_denom_appl->Integral();
  N_bkg=h_bkg_denom_appl->Integral();
 
  ROC->SetPoint(0,0,0);
  int npoints=1;

  for(int n=0;n<nbin;n++){

    double LR = cut_values_LR[n];
    double SVfit = cut_values_SVfit[n];

    int i=h_sig_appl->GetXaxis()->FindBin(LR);
    int j=h_sig_appl->GetYaxis()->FindBin(SVfit);

    double n_sig_acc=h_sig_appl->Integral(i,bin1_up_sig,j,bin2_up_sig);
    double n_bkg_acc=h_bkg_appl->Integral(i,bin1_up_bkg,j,bin2_up_bkg);
	  
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;
 
    if(sigeff>0 && sigeff<1){
  
      cout<<endl;
      cout<<"LR>"<<LR<<"; SVfit>"<<SVfit<<endl;
      cout<<"sigeff="<<sigeff<<"; bkgfake="<<bkgfake<<endl;

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}











TGraphErrors* get_ROC_2D_LR_Deta_unbiased(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=100;
  float min1=0;
  float max1=27;

  int nbin2=36;
  float min2=0;
  float max2=9;


  TH2F* h_sig_optim=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Deta",weight_sig+"*("+cut_num_sig+"&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg_optim=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Deta",weight_bkg+"*("+cut_num_bkg+"&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom_optim=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+"&& event%2==0)",3,0,3,3,0,3);
  TH2F* h_bkg_denom_optim=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+"&& event%2==0)",3,0,3,3,0,3);


  double N_sig=h_sig_denom_optim->Integral();
  double N_bkg=h_bkg_denom_optim->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);
  vector<double> cut_values_LR(nbin,0);
  vector<double> cut_values_Deta(nbin,0);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;


  double step_x=25./nbin1;

  for(int i=0;i<=nbin1;i++){    

    if(i%10==0)
      cout<<"i="<<i<<endl;

    double x=i*step_x;
    int binlow_x_sig=h_sig_optim->GetXaxis()->FindBin(x);
    int binlow_x_bkg=h_bkg_optim->GetXaxis()->FindBin(x);

    for(int j=0;j<=nbin2;j++){
    

      double n_sig_acc=h_sig_optim->Integral(binlow_x_sig,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg_optim->Integral(binlow_x_bkg,bin1_up_bkg,j,bin2_up_bkg);

      
      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;      
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;

	double xlow_sig=x;
	double ylow_sig=h_sig_optim->GetYaxis()->GetBinLowEdge(j);
	
	cut_values_LR[bin_eff]=xlow_sig;
	cut_values_Deta[bin_eff]=ylow_sig;
	
      }	  	
      
    }
    
  }


  TH2F* h_sig_appl=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Deta",weight_sig+"*("+cut_num_sig+"&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg_appl=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Deta",weight_bkg+"*("+cut_num_bkg+"&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom_appl=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+"&& event%2==1)",3,0,3,3,0,3);
  TH2F* h_bkg_denom_appl=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+"&& event%2==1)",3,0,3,3,0,3);


  N_sig=h_sig_denom_appl->Integral();
  N_bkg=h_bkg_denom_appl->Integral();
 
  ROC->SetPoint(0,0,0);
  int npoints=1;

  for(int n=0;n<nbin;n++){

    double LR = cut_values_LR[n];
    double Deta = cut_values_Deta[n];

    int i=h_sig_appl->GetXaxis()->FindBin(LR);
    int j=h_sig_appl->GetYaxis()->FindBin(Deta);

    double n_sig_acc=h_sig_appl->Integral(i,bin1_up_sig,j,bin2_up_sig);
    double n_bkg_acc=h_bkg_appl->Integral(i,bin1_up_bkg,j,bin2_up_bkg);
	  
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;
 
    if(sigeff>0 && sigeff<1){
  
      cout<<endl;
      cout<<"LR>"<<LR<<"; Deta>"<<Deta<<endl;
      cout<<"sigeff="<<sigeff<<"; bkgfake="<<bkgfake<<endl;

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}









TGraphErrors* get_ROC_2D_LR_Mjj_unbiased(TString file_sig, TString file_bkg, TString tree_name, TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){

  int nbin1=100;
  float min1=0;
  float max1=27;

  int nbin2=100;
  float min2=0;
  float max2=3000;


  TH2F* h_sig_optim=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Mjj",weight_sig+"*("+cut_num_sig+"&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg_optim=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Mjj",weight_bkg+"*("+cut_num_bkg+"&& event%2==0)",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom_optim=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+"&& event%2==0)",3,0,3,3,0,3);
  TH2F* h_bkg_denom_optim=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+"&& event%2==0)",3,0,3,3,0,3);


  double N_sig=h_sig_denom_optim->Integral();
  double N_bkg=h_bkg_denom_optim->Integral();

  TGraphErrors* ROC=new TGraphErrors();
  pair<double,double> dummy=make_pair(0.,1.);
  vector<pair<double,double> > efficiencies(nbin,dummy);
  vector<double> cut_values_LR(nbin,0);
  vector<double> cut_values_Mjj(nbin,0);

  int bin1_up_sig=nbin1;
  int bin2_up_sig=nbin2;

  int bin1_up_bkg=nbin1;
  int bin2_up_bkg=nbin2;

  double step_x=25./nbin1;

  for(int i=0;i<=nbin1;i++){    

    if(i%10==0)
      cout<<"i="<<i<<endl;

    double x=i*step_x;
    int binlow_x_sig=h_sig_optim->GetXaxis()->FindBin(x);
    int binlow_x_bkg=h_bkg_optim->GetXaxis()->FindBin(x);

    for(int j=0;j<=nbin2;j++){
    

      double n_sig_acc=h_sig_optim->Integral(binlow_x_sig,bin1_up_sig,j,bin2_up_sig);
      double n_bkg_acc=h_bkg_optim->Integral(binlow_x_bkg,bin1_up_bkg,j,bin2_up_bkg);
      
      double sigeff=n_sig_acc/N_sig;
      double bkgfake=n_bkg_acc/N_bkg;      
      
      //double ex=sqrt(sigeff*(1-sigeff)/N_sig);
      //double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);
      
      int bin_eff = abs(sigeff*nbin);
      if(bkgfake < efficiencies[bin_eff].second){
	efficiencies[bin_eff].first=sigeff;
	efficiencies[bin_eff].second=bkgfake;

	double xlow_sig=x;
	double ylow_sig=h_sig_optim->GetYaxis()->GetBinLowEdge(j);
	
	cut_values_LR[bin_eff]=xlow_sig;
	cut_values_Mjj[bin_eff]=ylow_sig;
	
      }	  	
      
    }
    
  }


  TH2F* h_sig_appl=single_plot2D(file_sig,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Mjj",weight_sig+"*("+cut_num_sig+"&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2);
  TH2F* h_bkg_appl=single_plot2D(file_bkg,tree_name,Form("-log(1-IntegralVBF/(IntegralVBF+%f*IntegralDY))*(IntegralDY>0)+26*(IntegralDY==0&&IntegralVBF>0)-(IntegralDY==0&&IntegralVBF==0)",k),"Mjj",weight_bkg+"*("+cut_num_bkg+"&& event%2==1)",nbin1,min1,max1,nbin2,min2,max2);

  TH2F* h_sig_denom_appl=single_plot2D(file_sig,tree_name,"1","1",weight_sig+"*("+cut_denom_sig+"&& event%2==1)",3,0,3,3,0,3);
  TH2F* h_bkg_denom_appl=single_plot2D(file_bkg,tree_name,"1","1",weight_bkg+"*("+cut_denom_bkg+"&& event%2==1)",3,0,3,3,0,3);


  N_sig=h_sig_denom_appl->Integral();
  N_bkg=h_bkg_denom_appl->Integral();
 
  ROC->SetPoint(0,0,0);
  int npoints=1;

  for(int n=0;n<nbin;n++){

    double LR = cut_values_LR[n];
    double Mjj = cut_values_Mjj[n];

    int i=h_sig_appl->GetXaxis()->FindBin(LR);
    int j=h_sig_appl->GetYaxis()->FindBin(Mjj);

    double n_sig_acc=h_sig_appl->Integral(i,bin1_up_sig,j,bin2_up_sig);
    double n_bkg_acc=h_bkg_appl->Integral(i,bin1_up_bkg,j,bin2_up_bkg);
	  
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;
 
    if(sigeff>0 && sigeff<1){
  
      cout<<endl;
      cout<<"LR>"<<LR<<"; Mjj>"<<Mjj<<endl;
      cout<<"sigeff="<<sigeff<<"; bkgfake="<<bkgfake<<endl;

      if(mistag_rate)
	ROC->SetPoint(npoints,sigeff,bkgfake);
      else
	ROC->SetPoint(npoints,sigeff,1-bkgfake);
      
      npoints++;

    }
  }

  return ROC;


}



TGraphErrors* get_ROC_LR_perm0(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-IntegralVBF_perm[0]/(IntegralVBF_perm[0]+%f*IntegralDY_perm[0]))*(IntegralDY_perm[0]>0)+26*(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]>0)-(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]==0)",k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-IntegralVBF_perm[0]/(IntegralVBF_perm[0]+%f*IntegralDY_perm[0]))*(IntegralDY_perm[0]>0)+26*(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]>0)-(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]==0)",k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_LR_perm1(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-IntegralVBF_perm[1]/(IntegralVBF_perm[1]+%f*IntegralDY_perm[1]))*(IntegralDY_perm[1]>0)+26*(IntegralDY_perm[1]==0&&IntegralVBF_perm[1]>0)-(IntegralDY_perm[1]==0&&IntegralVBF_perm[1]==0)",k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-IntegralVBF_perm[1]/(IntegralVBF_perm[1]+%f*IntegralDY_perm[1]))*(IntegralDY_perm[1]>0)+26*(IntegralDY_perm[1]==0&&IntegralVBF_perm[1]>0)-(IntegralDY_perm[1]==0&&IntegralVBF_perm[1]==0)",k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_LR_perm_maxLR(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-Max$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm)))*(Max$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))<1)+26*(Max$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))==1)-(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]==0)",k,k,k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-Max$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm)))*(Max$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))<1)+26*(Max$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))==1)-(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]==0)",k,k,k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}





TGraphErrors* get_ROC_LR_perm_minLR(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-Min$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm)))*(Min$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))<1)+26*(Min$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))==1)-(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]==0)",k,k,k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-Min$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm)))*(Min$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))<1)+26*(Min$(IntegralVBF_perm/(IntegralVBF_perm+%f*IntegralDY_perm))==1)-(IntegralDY_perm[0]==0&&IntegralVBF_perm[0]==0)",k,k,k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}






TGraphErrors* get_ROC_LR_perm_forwjets(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-IntegralVBF_perm[perm_forw_jet]/(IntegralVBF_perm[perm_forw_jet]+%f*IntegralDY_perm[perm_forw_jet]))*(IntegralDY_perm[perm_forw_jet]>0)+26*(IntegralDY_perm[perm_forw_jet]==0&&IntegralVBF_perm[perm_forw_jet]>0)-(IntegralDY_perm[perm_forw_jet]==0&&IntegralVBF_perm[perm_forw_jet]==0)",k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-IntegralVBF_perm[perm_forw_jet]/(IntegralVBF_perm[perm_forw_jet]+%f*IntegralDY_perm[perm_forw_jet]))*(IntegralDY_perm[perm_forw_jet]>0)+26*(IntegralDY_perm[perm_forw_jet]==0&&IntegralVBF_perm[perm_forw_jet]>0)-(IntegralDY_perm[perm_forw_jet]==0&&IntegralVBF_perm[perm_forw_jet]==0)",k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}




TGraphErrors* get_ROC_LR_perm_VBFvloose(TString file_sig, TString file_bkg, TString tree_name,  TString cut_num_sig, TString cut_denom_sig, TString cut_num_bkg, TString cut_denom_bkg, int nbin=100, bool mistag_rate=true, float k=0.00026, TString weight_sig="1", TString weight_bkg="1"){


  TH1F* h_sig=single_plot(file_sig,tree_name,Form("-log(1-IntegralVBF_VBFvloose/(IntegralVBF_VBFvloose+%f*IntegralDY_VBFvloose))*(IntegralDY_VBFvloose>0)+26*(IntegralDY_VBFvloose==0&&IntegralVBF_VBFvloose>0)-(IntegralDY_VBFvloose==0&&IntegralVBF_VBFvloose==0)",k),weight_sig+"*("+cut_num_sig+")",nbin,0,27);
  TH1F* h_bkg=single_plot(file_bkg,tree_name,Form("-log(1-IntegralVBF_VBFvloose/(IntegralVBF_VBFvloose+%f*IntegralDY_VBFvloose))*(IntegralDY_VBFvloose>0)+26*(IntegralDY_VBFvloose==0&&IntegralVBF_VBFvloose>0)-(IntegralDY_VBFvloose==0&&IntegralVBF_VBFvloose==0)",k),weight_bkg+"*("+cut_num_bkg+")",nbin,0,27);

  TH1F* h_sig_denom=single_plot(file_sig,tree_name,"1",weight_sig+"*("+cut_denom_sig+")",nbin,0,27);
  TH1F* h_bkg_denom=single_plot(file_bkg,tree_name,"1",weight_bkg+"*("+cut_denom_bkg+")",nbin,0,27);


  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;



  TGraphErrors* ROC=new TGraphErrors();
  int n=0;
  double step=25./nbin;

  //int binup_sig=h_sig->FindBin(27);
  //int binup_bkg=h_bkg->FindBin(27);
  int binup_sig=h_sig->FindBin(25);
  int binup_bkg=h_bkg->FindBin(25);

  for(int i=0;i<nbin;i++){
    double x=i*step;
    int binlow_sig=h_sig->FindBin(x);
    int binlow_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);

    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;


    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    if(mistag_rate)
      ROC->SetPoint(n,sigeff,bkgfake);
    else
      ROC->SetPoint(n,sigeff,1-bkgfake);
      

    //ROC->SetPointError(n,ex,ey);
    n++;

  }

  return ROC;


}
