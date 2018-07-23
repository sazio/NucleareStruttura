//
//  FitLineareCoincidenze.cpp
//  
//
//  Created by Simone Azeglio on 17/02/17.
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
#include <math.h>

using namespace std;

void FitLineareCoincidenze(){

    
    //DATI
    
    //Salita
    
    float deltaT1[]  = { -33.5, -33, -32.5, -32 , -31.5 , -31 , -30.5,  -30, -29 , -28 };
    float sdeltaT1[] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 , 0.5};
    float Rmis1[]  = { 1.18, 1.42 , 1.705, 2.365, 4.35, 5.15, 6.54 , 7.91, 9.59, 10.99};
    float sRmis1[] = {0.062 , 0.068 , 0.092, 0.109, 0.149, 0.162, 0.213, 0.292 ,0.324,  0.349};
    
    //Piatto
    
    float deltaT2[]  = { -23 ,-22, -20 , -16 , -12, -8 , -4, 0, 4, 8, 12, 16};
    float sdeltaT2[] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
    float Rmis2[]  = {12.18, 12.40, 12.10, 11.35, 12.05 , 11.53, 12.40 ,11.54, 12.21, 12.00, 11.70, 12.29};
    float sRmis2[] = { 0.369 , 0.373, 0.368, 0.355, 0.367 ,0.359, 0.373 ,0.369474,  0.3701, 0.366 , 0.361509, 0.369474};
    
    //Discesa
    
    float deltaT3[]  = {24, 24.5, 25, 25.5, 26, 26.5, 27, 27.5, 28 , 28.5, 29, 29.5, 30 };
    float sdeltaT3[] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 , 0.5, 0.5, 0.5, 0.5};
    float Rmis3[]  = {7.72, 8.84, 6.933, 6.15, 4.595, 3.8, 2.66, 1.862 , 1.262, 0.95, 0.772, 0.527 , 0.502};
    float sRmis3[] = { 0.2499, 0.2199, 0.2057 , 0.1780,  0.1533, 0.1242, 0.094, 0.068, 0.056, 0.048, 0.043, 0.036 , 0.035};

//Numero Misure
    int nmisure1 = 10;
    int nmisure2 = 12 ;
    int nmisure3 = 13 ;

    //--------------- FIT Dati -------- //
    
    
    
//Salita
    TGraphErrors *gdeltaT_Rmis1 = new TGraphErrors(nmisure1,deltaT1,Rmis1,sdeltaT1,sRmis1);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gdeltaT_Rmis1->SetMarkerSize(0.6);
    gdeltaT_Rmis1->SetMarkerStyle(21);

    
    // Piatto
    TGraphErrors *gdeltaT_Rmis2 = new TGraphErrors(nmisure2,deltaT2,Rmis2,sdeltaT2,sRmis2);
    gdeltaT_Rmis2->SetMarkerSize(0.6);
    gdeltaT_Rmis2->SetMarkerStyle(21);

    
    
    //Discesa
    TGraphErrors *gdeltaT_Rmis3 = new TGraphErrors(nmisure3,deltaT3,Rmis3,sdeltaT3,sRmis3);
    gdeltaT_Rmis3->SetMarkerSize(0.6);
    gdeltaT_Rmis3->SetMarkerStyle(21);

    

    
    //// -_- - - - - - --  - -   Fit Lineare Salita - - - - -  - -  - --- -  //
    
     TCanvas *cCoincidenzeLinear = new TCanvas("cCoincidenzeLinear","Curva di coincidenza --- Fit Lineari ",200,10,600,400);
    
    TF1 *LinearSalita = new TF1("LinearSalita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    gdeltaT_Rmis1 ->Fit(LinearSalita);
    cout << "Angular coefficient: " << LinearSalita->GetParameter(1) << " +- " << LinearSalita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
   cout << "Chi^2:" << LinearSalita->GetChisquare() << ", number of DoF: " << LinearSalita->GetNDF() << " (Probability: " << LinearSalita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    //// -_- - - - - - --  - -   Fit Lineare Piatto - - - - -  - -  - --- -  //
    
    TF1 *LinearPiatto = new TF1("LinearPiatto", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gdeltaT_Rmis2 ->Fit(LinearPiatto);
    LinearPiatto->SetLineColor(4);
    
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << LinearPiatto->GetParameter(1) << " +- " << LinearPiatto->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << LinearPiatto->GetChisquare() << ", number of DoF: " << LinearPiatto->GetNDF() << " (Probability: " << LinearPiatto->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    //// -_- - - - - - --  - -   Fit Lineare Discesa - - - - -  - -  - --- -  //
    
    TF1 *LinearDiscesa = new TF1("LinearDiscesa", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gdeltaT_Rmis3 ->Fit(LinearDiscesa);
    LinearDiscesa->SetLineColor(5);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << LinearDiscesa->GetParameter(1) << " +- " << LinearDiscesa->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
   cout << "Chi^2:" << LinearDiscesa->GetChisquare() << ", number of DoF: " << LinearDiscesa->GetNDF() << " (Probability: " << LinearDiscesa->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    
    
    //---- - -- - - - -  - Unisco i  Grafici
    
    TMultiGraph *MergedGraphs = new TMultiGraph();
    MergedGraphs->Add( gdeltaT_Rmis1);
    MergedGraphs->Add( gdeltaT_Rmis2);
    MergedGraphs->Add( gdeltaT_Rmis3);
    
    
    
    
    MergedGraphs->Draw("AP");
    

    
    


}
