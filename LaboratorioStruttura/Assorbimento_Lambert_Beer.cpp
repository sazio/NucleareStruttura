//
//  Plotintegralesp4.cpp
//  
//
//  Created by Simone Azeglio on 17/06/16.
//
//

#include <stdio.h>
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video


using namespace std;




void Assorbimento_Lambert_Beer(){
    
    
    
    // Numero misure
    
           const  int nmisure =38  ;
    
    const int nmisure2 = 19 ;

   // Dati
    
    // Spessore in mm
    
    float Spessore[] = {0.0, 0.0, 0.1, 0.1, 0.25, 0.25, 0.35, 0.35, 0.5, 0.5,
                        0.6, 0.6, 0.75, 0.75, 0.85, 0.85, 1.00, 1.00, 1.10, 1.10,
                        1.25, 1.25, 1.35, 1.35, 1.5, 1.5, 1.6, 1.6, 1.75, 1.75,
        
                        2, 2, 2.5, 2.5, 3, 3, 3.5, 3.5};
    float sSpessore[nmisure] ;
    
       cout << "Misure Spessore:  " << sizeof(Spessore)/4 << endl;
    
    float Conteggi[] = {21921, 21877, 14734, 14828, 5078, 5184, 2958, 2983, 1836, 1905,
                        1501, 1599, 1206, 1272, 1014, 1040, 749, 791, 658, 667,
                        613, 623, 486, 535, 493, 465, 381, 414, 326, 382,
        
                        256, 293, 182, 181, 127, 127, 85.5, 83.5};
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    

    
    
    // Intensità  = Conteggi/s = Rate

    
 
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float Spessore2[nmisure2] ;
    float sSpessore2[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Intensità[nmisure2];
    float sIntensità[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(Spessore[i] == Spessore[i+1]){
        Spessore2[j]= Spessore[i] ;
        cout << "Spessore" << j <<" : "  <<  Spessore2[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { Spessore2[j] = Spessore[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.001;
        sSpessore2[i] = 0.05;
        
        Intensità[i] = Conteggi2[i]/Secondi2[i];
        sIntensità[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    float LogaritmoIntensità[nmisure2];
    float sLogaritmoIntensità[nmisure2];

    
    
    for(int i = 0 ; i < nmisure2 ; i++){
     
        LogaritmoIntensità[i] = log(Intensità[i]/Intensità[0]) ;
        sLogaritmoIntensità[i] = sIntensità[i]/Intensità[i] ;
    
    }
    
   // numero misure

    
    
   //--------- Grafico
    
    TCanvas *cISpessore = new TCanvas("cISpessore","I(x)", 200,10,600,400);
    
    cISpessore-> SetFillColor(0);
    
    cISpessore->cd();
    
    TGraphErrors *gISpessore = new TGraphErrors(nmisure2, Spessore2, Intensità, sSpessore2, sIntensità);
    
    gISpessore->SetMarkerSize(0.6);
    gISpessore->SetMarkerStyle(21) ;
    gISpessore-> SetTitle("I(x)");
    
    gISpessore->GetXaxis()->SetTitle("x[mm]");
    gISpessore->GetYaxis()->SetTitle("I[Hz]");
    
    gISpessore->Draw("AP");
    


    
    // Fit con esp normale
    
    TF1 *exp_normale = new TF1("exp_normale","[0]*(TMath::Exp(-[1]*x))") ;
    
    exp_normale->SetParLimits(0, 1084.45, 1110.45);
    exp_normale->GetParameter(1);
    
    exp_normale->SetLineColor(3);
    
    gISpessore->Fit(exp_normale, "M+");
    
    
    cout << "Chi^2:" << exp_normale->GetChisquare() << ", number of DoF: " << exp_normale->GetNDF() << " (Probability: " << exp_normale->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;


    

    
    // Fit Logaritmo
    
    
 /*   TF1 *logaritmo = new TF1("logaritmo" , "[0]+ [1]*x");
    
   logaritmo->GetParameter(0);
    logaritmo->GetParameter(1);
    
    logaritmo->SetLineColor(3);
    
    glogaritmoIntensità->Fit(logaritmo, "M+");
    
    
    cout << "Chi^2:" << logaritmo->GetChisquare() << ", number of DoF: " << logaritmo->GetNDF() << " (Probability: " << logaritmo->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    */
    
    TCanvas *clogaritmoIntensità = new TCanvas("clogaritmoIntensità ","ln(I/I0)", 200,10,600,400);
    
    // Scintillatore H1
    
    const int nmisure2_primi3 = 3 ;
    
    float Spessore2_primi3[nmisure2_primi3];
    float sSpessore2_primi3[nmisure2_primi3];
    float LogaritmoIntensità_primi3[nmisure2_primi3];
    float sLogaritmoIntensità_primi3[nmisure2_primi3];
    
    for(int i = 0 ; i < nmisure2_primi3 ; i++){
    
        Spessore2_primi3[i] = Spessore2[i+1];
        sSpessore2_primi3[i] = sSpessore2[i+1];
        LogaritmoIntensità_primi3[i] = LogaritmoIntensità[i+1];
        sLogaritmoIntensità_primi3[i] = sLogaritmoIntensità[i+1];
        
}
    
    
    
    TGraphErrors *glogaritmoIntensità1 = new TGraphErrors(nmisure2_primi3, Spessore2_primi3, LogaritmoIntensità_primi3, sSpessore2_primi3, sLogaritmoIntensità_primi3);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    glogaritmoIntensità1->SetMarkerSize(0.6);
    glogaritmoIntensità1->SetMarkerStyle(21);
    
    
    
    
    

    
    
    // Scintillatore H2
    
    
    const int nmisure2_ultimi = 6;
    
    float Spessore2_ultimi[nmisure2_ultimi];
    float sSpessore2_ultimi[nmisure2_ultimi];
    float LogaritmoIntensità_ultimi[nmisure2_ultimi];
    float sLogaritmoIntensità_ultimi[nmisure2_ultimi];
    
    for(int i = 0 ; i < nmisure2_ultimi ; i++){
        
        Spessore2_ultimi[i] = Spessore2[nmisure2-nmisure2_ultimi+i];
        sSpessore2_ultimi[i] = sSpessore2[nmisure2-nmisure2_ultimi+i];
        LogaritmoIntensità_ultimi[i] = LogaritmoIntensità[nmisure2-nmisure2_ultimi + i];
        sLogaritmoIntensità_ultimi[i] = sLogaritmoIntensità[nmisure2- nmisure2_ultimi +i ];
        
    }

    
    TGraphErrors *glogaritmoIntensità2 = new TGraphErrors(nmisure2_ultimi, Spessore2_ultimi, LogaritmoIntensità_ultimi, sSpessore2_ultimi, sLogaritmoIntensità_ultimi);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    glogaritmoIntensità2->SetMarkerSize(0.6);
    glogaritmoIntensità2->SetMarkerStyle(21);
    
    
    
    
    //// -_- - - - - - --  - -   Fit  primo mu - - - - -  - -  - --- -  //
    
   
    
    TF1 *LogaritmoIntensità1 = new TF1("LogaritmoIntensità1", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    glogaritmoIntensità1 ->Fit(LogaritmoIntensità1);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << LogaritmoIntensità1->GetParameter(1) << " +- " << LogaritmoIntensità1->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << LogaritmoIntensità1->GetChisquare() << ", number of DoF: " << LogaritmoIntensità1->GetNDF() << " (Probability: " << LogaritmoIntensità1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    //// -_- - - - - - --  - -   Fit  secondo mu  - - - - -  - -  - --- -  //
    
    
    TF1 *LogaritmoIntensità2 = new TF1("LogaritmoIntensità2", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    glogaritmoIntensità2 ->Fit(LogaritmoIntensità2);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << LogaritmoIntensità2->GetParameter(1) << " +- " << LogaritmoIntensità2->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << LogaritmoIntensità2->GetChisquare() << ", number of DoF: " << LogaritmoIntensità2->GetNDF() << " (Probability: " << LogaritmoIntensità2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    //---- - -- - - - -  - Unisco i  Grafici
    
    
    TMultiGraph *MergedGraphs3 = new TMultiGraph();
    MergedGraphs3->Add( glogaritmoIntensità1);
    MergedGraphs3->Add( glogaritmoIntensità2);
    
    
    
    MergedGraphs3->Draw("AP");
    
    MergedGraphs3->GetXaxis()->SetTitle("x[mm]");
    MergedGraphs3->GetYaxis()->SetTitle("Ln(I/I0)");
    
    gPad->Modified();
    
    
        
        }
    
    

    
    



