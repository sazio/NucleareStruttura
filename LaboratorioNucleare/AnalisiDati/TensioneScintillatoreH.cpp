//
//  TensioneScintillatoreH.cpp
//  
//
//  Created by Simone Azeglio on 18/02/17.
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

using namespace std;

void TensioneScintillatoreH(){

    //Impostazioni della HV di alimentazione e delle soglie dei discriminatori
    
    
    
    // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: HV = tensione di lavoro , sHV = incertezza tensione, LogN =  logaritmo dei conteggi , sLogN = incertezza logaritmo dei conteggi
    // tutti gli scintillatori sono stati divisi in due parti per fare un fit con due rette, in modo da trovare il "ginocchio " che identifica il punto di lavoro}
    
    //Scintillatore H
    
    const int nmisure0_H1 = 5;
    const int nmisure0_H2 = 6 ;
    
    
    //Prima Parte
    
    float HV_H1[]  = {1396, 1436, 1476, 1517, 1557};
    float sHV_H1[] = {1, 1, 1, 1, 1};
    
    
    float N_H1[] = {189, 394, 711, 1204, 1987} ;
    
    
    float LogN_H1[nmisure0_H1] ;
    for(int i = 0 ; i <nmisure0_H1; i++)
        LogN_H1[i] =  log10(N_H1[i]) ;
    
    float sLogN_H1[nmisure0_H1] ;
    for(int i = 0 ; i <nmisure0_H1; i++)
        sLogN_H1[i] = sqrt(N_H1[i])/N_H1[i] ;
    
    
    // Seconda Parte
    
    float HV_H2[]  = {1596, 1637, 1677, 1717, 1757, 1797};
    float sHV_H2[] = { 1, 1, 1, 1, 1, 1};
    
    
    float N_H2[] = {3050, 4490, 6566, 9627, 14039,22857} ;
    
    
    float LogN_H2[nmisure0_H2] ;
    for(int i = 0 ; i <nmisure0_H2; i++)
        LogN_H2[i] =  log10(N_H2[i]) ;
    
    float sLogN_H2[nmisure0_H2] ;
    for(int i = 0 ; i <nmisure0_H2; i++)
        sLogN_H2[i] = sqrt(N_H2[i])/N_H2[i] ;
    
    
    // --------------------- Grafico LogN(HV) - Logaritmo conteggi in funzione di tensione di lavoro ------------------------------ //
    
    // Scintillatore H1
    
    
    TGraphErrors *gHV_LogN_H1 = new TGraphErrors(nmisure0_H1,HV_H1,LogN_H1,sHV_H1,sLogN_H1);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_H1->SetMarkerSize(0.6);
    gHV_LogN_H1->SetMarkerStyle(21);
    
    
    // Scintillatore H2
    
    
    TGraphErrors *gHV_LogN_H2 = new TGraphErrors(nmisure0_H2,HV_H2,LogN_H2,sHV_H2,sLogN_H2);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_H2->SetMarkerSize(0.6);
    gHV_LogN_H2->SetMarkerStyle(21);
    
    
/*
 
 
 
 // Scintillatore H
 
 // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
 TCanvas *cHV_LogN_H = new TCanvas("cHV_LogN_H","LogN(HV)  -- Scintillatore H",200,10,600,400);
 // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
 cHV_LogN_H ->SetFillColor(0);
 // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
 cHV_LogN_H->cd();
 // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
 // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
 // array delle  rispettive incertezze
 TGraphErrors *gHV_LogN_H = new TGraphErrors(nmisure0_H,HV_H,LogN_H,sHV_H,sLogN_H);
 // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
 // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
 gHV_LogN_H ->SetMarkerSize(0.6);
 gHV_LogN_H ->SetMarkerStyle(21);
 // Facile, titolo del grafico
 gHV_LogN_H ->SetTitle("LogN(HV)");
 // Titoli degli assi
 gHV_LogN_H ->GetXaxis()->SetTitle("HV [mV]");
 gHV_LogN_H ->GetYaxis()->SetTitle("LogN []");
 // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
 // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
 // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
 gHV_LogN_H ->Draw("AP");
 // ----------------------------------------------------------------- //
 
 

*/
    
    
    
    //// -_- - - - - - --  - -   Fit  Scintillatore H_1 - - - - -  - -  - --- -  //
    
    TCanvas *cHV_LogN_H = new TCanvas("cHV_LogN_H","LogN(HV) -- Scintillatore H ",200,10,600,400);
 	
    TF1 *ScintillatoreH1_Salita = new TF1("ScintillatoreH1_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_H1 ->Fit(ScintillatoreH1_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreH1_Salita->GetParameter(1) << " +- " << ScintillatoreH1_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreH1_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreH1_Salita->GetNDF() << " (Probability: " << ScintillatoreH1_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    //// -_- - - - - - --  - -   Fit  Scintillatore H_2 - - - - -  - -  - --- -  //
    
    
    TF1 *ScintillatoreH2_Salita = new TF1("ScintillatoreH2_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_H2 ->Fit(ScintillatoreH2_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreH2_Salita->GetParameter(1) << " +- " << ScintillatoreH2_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreH2_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreH2_Salita->GetNDF() << " (Probability: " << ScintillatoreH2_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    // Troviamo intersezione rette utilizzando i parametri forniti dal best fit di root
    cout << "Intersezione rette: " << (ScintillatoreH1_Salita->GetParameter(0)-ScintillatoreH2_Salita->GetParameter(0))/ (ScintillatoreH2_Salita->GetParameter(1)-ScintillatoreH1_Salita->GetParameter(1)) << endl ;
    
    
    
    //---- - -- - - - -  - Unisco i  Grafici
    
    
    TMultiGraph *MergedGraphs3 = new TMultiGraph();
    MergedGraphs3->Add( gHV_LogN_H1);
    MergedGraphs3->Add( gHV_LogN_H2);
    
    
    
    MergedGraphs3->Draw("AP");

MergedGraphs3->GetXaxis()->SetTitle("HV[V]");
  MergedGraphs3->GetYaxis()->SetTitle("Log(N)");

gPad->Modified();

    
    


}


