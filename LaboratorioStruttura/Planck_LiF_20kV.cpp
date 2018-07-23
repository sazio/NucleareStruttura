//
//  Planck_LiF_20kV.cpp
//  
//
//  Created by Simone Azeglio on 09/03/17.
//
//

#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>

void Planck_LiF_20kV(){
    
    
    //numero misure
    const int nmisure = 88;
    
    
    // numero misure senza doppi
    const int nmisure2= 44;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[] = {54.4, 44.8, 49.5, 50, 50, 50.5, 65.5, 60.5, 82.5, 82,
                        96, 101.5, 106, 96, 136, 102, 112, 128, 144, 127,
                        158, 173, 193, 194, 220, 206, 215, 225, 269, 258,
        
                        258, 249, 299, 291, 333, 323, 355, 316, 355, 325,
                        394, 395, 394, 405, 424, 416, 419, 448, 482, 458,
                        478, 460, 450, 464, 475, 494, 507, 515, 517, 471,
        
                        515, 559, 531, 560, 538, 539, 543, 577, 538, 536,
                        589, 567, 593, 591, 621, 622, 557, 557, 592, 552,
                        609, 553, 609, 588, 679, 652, 745, 725
        
        
        
        
        
    };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float ThetaX2[]  = {12, 12, 13, 13, 14, 14, 15, 15, 16, 16,
                        16.5, 16.5, 16.67, 16.67, 16.83, 16.83, 17, 17, 17.167, 17.167,
                        17.33, 17.33, 17.5, 17.5, 17.67, 17.67, 17.83, 17.83, 18, 18,
        
                        18.167, 18.167, 18.33, 18.33, 18.5, 18.5, 18.67, 18.67, 18.83, 18.83,
                        19, 19, 19.167, 19.167, 19.33, 19.33, 19.5, 19.5, 19.67, 19.67,
                        19.83, 19.83, 20, 20, 20.167, 20.167, 20.33, 20.33, 20.5, 20.5,
        
                        20.67, 20.67, 20.83, 20.83, 21, 21, 21.167, 21.167, 21.33, 21.33,
                        21.5, 21.5, 21.67, 21.67, 21.83, 21.83, 22, 22, 22.167, 22.167,
                        22.33, 22.33, 23, 23, 24, 24, 25, 25
        
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
    
}
