//
//  Diffrazione20kV.cpp
//  
//
//  Created by Simone Azeglio on 08/03/17.
//
//

//
//  Diffrazione.cpp , Con alimentazione a 30kV
//
//
//  Created by Simone Azeglio
//  Valori picchi teorici
//  Theta non thetax2
//  Kalfa 1 = 15.84° ; Kalfa 2 = 33.10°  ; Kalfa 3 = 55.00°
//  Kbeta 1 = 14.16° ; Kbeta 2 = 29.30° ;Kbeta 3 = 47.23°;

// Multi Gaussian function
Double_t MultiGaussianPeaks(Double_t *x, Double_t *par) {
    return (par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0]+
            par[4]*TMath::Exp(-0.5*((x[0]-par[5])*(x[0]-par[5]))/(2*par[6]*par[6]))+
            par[7]*TMath::Exp(-0.5*((x[0]-par[8])*(x[0]-par[8]))/(2*par[9]*par[9]))) ;
}





#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>

void Diffrazione20kV(){
    
    
    //numero misure
    const int nmisure = 76  ;
    
    
    // numero misure senza doppi
    const int nmisure2= 38;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[]  = {63, 80, 174, 198, 227, 221, 201, 181, 231, 203,
                         239, 260, 292, 331, 404, 417, 624, 652, 827, 878,
                         844, 860, 825, 824, 784, 808, 560, 581, 467, 459,
        
                         326, 315, 244, 253, 213, 221, 211, 213, 204, 211,
                         250, 258, 425, 423, 1015, 1064, 2222, 2209, 3120, 3194,
                         3766, 3657, 3650, 3725, 3263, 3311, 2550, 2667, 1645, 1639,
        
                         836, 815, 406, 383, 216, 231, 123, 178, 174, 171,
                         161, 138, 138, 166, 148, 173 };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float ThetaX2[]  = {12, 12, 17, 17, 22, 22, 27, 27, 27.5, 27.5,
                        27.67, 27.67, 27.83, 27.83, 28, 28, 28.167, 28.167, 28.33, 28.33,
                        28.5, 28.5, 28.67, 28.67, 28.83, 28.83, 29, 29, 29.167, 29.167,
        
                        29.33, 29.33, 29.5, 29.5, 29.67, 29.67, 29.83, 29.83, 30, 30,
                        30.5, 30.5, 30.67, 30.67, 30.83, 30.83, 31, 31, 31.167, 31.167,
                        31.33, 31.33, 31.5, 31.5, 31.67, 31.67, 31.83, 31.83, 32, 32,
        
                        32.167, 32.167, 32.33, 32.33, 32.5, 32.5, 32.67, 32.67, 32.83, 32.83,
                        33, 33, 34, 34, 35, 35
        
                        };
    
    
    cout << "Misure ThetaX2:  " << sizeof(ThetaX2)/4 << endl;
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float ThetaX22[nmisure2] ;
    float sThetaX22[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Conteggi_Secondi2[nmisure2];
    float sConteggi_Secondi2[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(ThetaX2[i] == ThetaX2[i+1]){
        ThetaX22[j]= ThetaX2[i] ;
        cout << "ThetaX2" << j <<" : "  <<  ThetaX22[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { ThetaX22[j] = ThetaX2[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.01;
        sThetaX22[i] = 0.0;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    //--------------- FIT Dati -------- //
    
    
    //--------------- FIT Dati -------- //
    
    TCanvas *cThetaX2Conteggi = new TCanvas("cThetaX2Conteggi ","Conteggi(ThetaX2)",700,100,800,500);
    
    
    TGraphErrors *gThetaX2Conteggi = new TGraphErrors(nmisure2 , ThetaX22 ,Conteggi_Secondi2 ,sThetaX22, sConteggi_Secondi2);
    
    
    
    
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gThetaX2Conteggi->SetMarkerSize(0.6);
    gThetaX2Conteggi->SetMarkerStyle(21);
    gThetaX2Conteggi->SetTitle("Rate(ThetaX2)");
    
    gThetaX2Conteggi->GetXaxis()->SetTitle("ThetaX2[gradi]");
    gThetaX2Conteggi->GetYaxis()->SetTitle("Rate [1/s] ");
    
    
    
    
    gThetaX2Conteggi->Draw("AP");
    
    
    
    //--
    // create a TF1 with the range from 0 to 3 and 6 parameters
    TF1 *fitFcn = new TF1("fitFcn",MultiGaussianPeaks, 27, 33, 10);
    
    
    
    
    // Polynomial's parameters from background fitting
    
    fitFcn->SetParameter( 0,  6.045);//, 72.5);
    fitFcn->SetParameter( 1,   -3.82880e-02 );//, -0.38);
    fitFcn->SetParameter( 2,   2.16988e-03 );//, 0.000913);
    fitFcn->SetParameter( 3,   -9.45735e-07);//, -1.75e-07);
    
    
    
    
    // Setting MG parameters from par[4] to par[9]
    
    
    fitFcn->SetParameter(4, 30); // Constant - pol evaluated
    fitFcn->SetParameter(5, 28.43 ); // Mean
    
    fitFcn->SetParameter(7, 5.4 ); // Constant
    fitFcn->SetParameter(8, 31.47 ); // Mean
    
    
    
    fitFcn->SetParameter(6, 0.49 );//, 32.90); // Width - rough order of mag estimate
    fitFcn->SetParameter(9, 0.41 );// , 41.44); // Width - rough order of mag estimate
    
    
    
    
    
    
    // Setting fit 
   
    gThetaX2Conteggi->Fit(fitFcn,"R+");
   
    
    
    cout << "Chi^2:" << fitFcn->GetChisquare() << ", number of DoF: " << fitFcn->GetNDF() << " (Probability: " << fitFcn->GetProb() << ")." << endl;
    
    
    
    

    
}



