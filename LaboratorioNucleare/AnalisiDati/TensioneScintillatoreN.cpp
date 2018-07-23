//
//  TensioneScintillatoreN.cpp
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

void TensioneScintillatoreN(){

    //Impostazioni della HV di alimentazione e delle soglie dei discriminatori
    
    // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: HV = tensione di lavoro , sHV = incertezza tensione, LogN =  logaritmo dei conteggi , sLogN = incertezza logaritmo dei conteggi
    // tutti gli scintillatori sono stati divisi in due parti per fare un fit con due rette, in modo da trovare il "ginocchio " che identifica il punto di lavoro
    
    //Scintillatore N
    
    const int nmisure0_N_1 = 6 ;
    const int nmisure0_N_2 = 6 ;
    
    // Prima Parte
    
    float HV_N1[]  = {1395, 1435, 1475, 1516, 1556, 1595};
    float sHV_N1[] = {1, 1, 1, 1, 1, 1 };
    
    
    float N_N1[] = {89, 188, 355, 595, 969, 1560} ;
    
    
    float LogN_N1[nmisure0_N_1] ;
    for(int i = 0 ; i <nmisure0_N_1; i++)
        LogN_N1[i] =  log10(N_N1[i]) ;
    
    float sLogN_N1[nmisure0_N_1] ;
    for(int i = 0 ; i <nmisure0_N_1; i++)
        sLogN_N1[i] = sqrt(N_N1[i])/N_N1[i] ;
    
    
    // Seconda Parte
    
    float HV_N2[]  = { 1646, 1686, 1726, 1766, 1806, 1846};
    float sHV_N2[] = { 1, 1, 1, 1, 1, 1 };
    
    
    float N_N2[] = { 2483, 3645, 5029, 6998, 9122, 12076} ;
    
    
    float LogN_N2[nmisure0_N_2] ;
    for(int i = 0 ; i <nmisure0_N_2; i++)
        LogN_N2[i] =  log10(N_N2[i]) ;
    
    float sLogN_N2[nmisure0_N_2] ;
    for(int i = 0 ; i <nmisure0_N_2; i++)
        sLogN_N2[i] = sqrt(N_N2[i])/N_N2[i] ;
    
    
    
    // --------------------- Grafico LogN(HV) - Logaritmo conteggi in funzione di tensione di lavoro ------------------------------ //
    
    
    
    
    // Scintillatore N1
    
    
    TGraphErrors *gHV_LogN_N1 = new TGraphErrors(nmisure0_N_1,HV_N1,LogN_N1,sHV_N1,sLogN_N1);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_N1->SetMarkerSize(0.6);
    gHV_LogN_N1->SetMarkerStyle(21);
    
    // Scintillatore N2
    
    
    TGraphErrors *gHV_LogN_N2 = new TGraphErrors(nmisure0_N_2,HV_N2,LogN_N2,sHV_N2,sLogN_N2);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_N2->SetMarkerSize(0.6);
    gHV_LogN_N2->SetMarkerStyle(21);
    
  
    
    /*
    // Modelli per il fit non TMultigraph --- Eventualmente da utilizzare per polinomio
    
    
    //Scintillatore N
    
    // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
    TCanvas *cHV_LogN_N = new TCanvas("cHV_LogN_N","LogN(HV) -- Scintillatore N ",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cHV_LogN_N ->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cHV_LogN_N->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gHV_LogN_N = new TGraphErrors(nmisure0_N,HV_N,LogN_N,sHV_N,sLogN_N);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_N ->SetMarkerSize(0.6);
    gHV_LogN_N ->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gHV_LogN_N ->SetTitle("LogN(HV)");
    // Titoli degli assi
    gHV_LogN_N ->GetXaxis()->SetTitle("HV [mV]");
    gHV_LogN_N ->GetYaxis()->SetTitle("LogN []");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gHV_LogN_N ->Draw("AP");
    // ----------------------------------------------------------------- //

    
    
*/
    //--------------- FIT Dati -------- //
    
    
    TCanvas *cHV_LogN_N = new TCanvas("cHV_LogN_N","LogN(HV) -- Scintillatore N ",200,10,600,400);
    
    //// -_- - - - - - --  - -   Fit  Scintillatore N_1 - - - - -  - -  - --- -  //
    
    
    TF1 *ScintillatoreN1_Salita = new TF1("ScintillatoreN1_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_N1 ->Fit(ScintillatoreN1_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreN1_Salita->GetParameter(1) << " +- " << ScintillatoreN1_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreN1_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreN1_Salita->GetNDF() << " (Probability: " << ScintillatoreN1_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    //// -_- - - - - - --  - -   Fit  Scintillatore N_2 - - - - -  - -  - --- -  //
    
    
    TF1 *ScintillatoreN2_Salita = new TF1("ScintillatoreN2_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_N2 ->Fit(ScintillatoreN2_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreN2_Salita->GetParameter(1) << " +- " << ScintillatoreN2_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreN2_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreN2_Salita->GetNDF() << " (Probability: " << ScintillatoreN2_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    // Troviamo intersezione rette utilizzando i parametri forniti dal best fit di root
    cout << "Intersezione rette: " << (ScintillatoreN1_Salita->GetParameter(0)-ScintillatoreN2_Salita->GetParameter(0))/ (ScintillatoreN2_Salita->GetParameter(1)-ScintillatoreN1_Salita->GetParameter(1)) << endl ;
    
    //---- - -- - - - -  - Unisco i  Grafici
    
    
    
    
    TMultiGraph *MergedGraphs = new TMultiGraph();
    MergedGraphs->Add( gHV_LogN_N1);
    MergedGraphs->Add(  gHV_LogN_N2);
    
    
    
    
    MergedGraphs->Draw("AP");

    MergedGraphs->GetXaxis()->SetTitle("HV[V]");
  MergedGraphs->GetYaxis()->SetTitle("Log(N)");

gPad->Modified();
    




}
