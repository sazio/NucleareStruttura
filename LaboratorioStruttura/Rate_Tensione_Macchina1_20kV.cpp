//
//  ConteggiS_20kV.cpp
//  
//
//  Created by Simone Azeglio on 06/03/17.
//
// Primo giorno di laboratorio-- prima macchina 

#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>

using namespace std;

void Rate_Tensione_Macchina1_20kV(){
    
    
    //numero misure
    const int nmisure = 64 ;
    
    
    // numero misure senza doppi
    const int nmisure2= 32 ;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[]  = { 10 , 7, 23, 22, 30, 33, 56, 56, 62, 192, 609, 595, 1132, 1031, 1742, 1529, 2446, 2357, 3528, 3238, 4115, 4124, 4823, 4906, 5487, 5542, 6196, 5638, 6789, 6781, 7267, 7231, 8089, 7946, 9089,8920 , 10410, 10443, 12134, 12119, 12090, 13638, 14751, 14822, 15949, 15990, 17038, 16971 , 17032, 17431, 16553, 17210,  16508, 16863, 17416, 16673, 16552, 15864, 16390, 17325, 17819, 18087, 17286, 16658 };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float Tensione[]  = {394, 394, 397, 397, 399, 399, 402, 402, 404, 404, 406, 406, 409, 409, 411, 411, 413, 413, 416, 416, 418, 418 , 421, 421, 423, 423, 425, 425, 428, 428, 430, 430, 432, 432, 435, 435,  437, 437, 440, 440, 442, 442, 444, 444, 447, 447, 449 ,449 , 451, 451, 454, 454, 456, 456, 459, 459, 463, 463 , 468, 468, 473, 473, 478 , 478};

    
    cout << "Misure Tensione:  " << sizeof(Tensione)/4 << endl;
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float Tensione2[nmisure2] ;
    float sTensione2[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Conteggi_Secondi2[nmisure2];
    float sConteggi_Secondi2[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(Tensione[i] == Tensione[i+1]){
        Tensione2[j]= Tensione[i] ;
        cout << "Tensione" << j <<" : "  <<  Tensione2[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { Tensione2[j] = Tensione[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.001;
        sTensione2[i] = 0;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    
    
    
    
    
    
    
    //--------------- FIT Dati -------- //
    
     TCanvas *cConteggiTensione = new TCanvas("cConteggiTensione ","Conteggi/s(Tensione)",200,10,600,400);
    
    
    TGraphErrors *gConteggiTensione = new TGraphErrors(nmisure2 , Tensione2 ,Conteggi_Secondi2 ,sTensione2, sConteggi_Secondi2);
    
    
    
    
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gConteggiTensione->SetMarkerSize(0.6);
    gConteggiTensione->SetMarkerStyle(21);
    gConteggiTensione->SetTitle("Conteggi/Secondi(Tensione)");
    
    gConteggiTensione->GetXaxis()->SetTitle("Tensione [V]");
    gConteggiTensione->GetYaxis()->SetTitle("Conteggi/Secondi [1/s] ");
    

    
    
    gConteggiTensione->Draw("AP");
    
    
    
  
    cout << "\n\n --- Sigmoide--- \n" <<endl;
    
    TF1 *sigmoid= new TF1("sigmoid","[0]*(1/(1+exp(-x+[1])))");
    
    
    
    
    sigmoid->SetParameter(0, 840);
    sigmoid->GetParError(0);
    
    
    sigmoid->GetParameter(1);
    sigmoid->GetParError(1);
    
    
    sigmoid->SetLineColor(9);
    
    
    
    
    gConteggiTensione->Fit(sigmoid,"R+");
    
    cout << "Chi^2:" << sigmoid->GetChisquare() << ", number of DoF: " << sigmoid->GetNDF() << " (Probability: " << sigmoid->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    
    
    
    
    

    
}

    
