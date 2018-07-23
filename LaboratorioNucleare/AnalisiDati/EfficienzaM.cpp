//
//  EfficienzaM.cpp
//  
//
//  Created by Simone Azeglio on 17/02/17.
//
//

#include <stdio.h>
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

void EfficienzaM()
{
    
    //Numero Misure
    const int nmisure = 8;
    
    
    // Dati
    
    float HV[]  = {1297, 1346, 1396, 1446, 1471, 1496, 1521, 1546};
    float sHV[] = {1, 1, 1, 1, 1, 1, 1, 1};
    
    float N_tripla[] = {31, 90, 198, 338, 428, 463, 492, 533};
    
    float sN_tripla[nmisure] ;
    for(int i = 0 ; i <nmisure ; i++){
        sN_tripla[i] = sqrt(N_tripla[i]); }
    
    float N_doppia[]  ={492, 513, 482, 481, 506, 521, 517, 555  };
    float sN_doppia[nmisure] ;
    for(int i = 0 ; i <nmisure ; i++){
        sN_doppia[i] = sqrt(N_doppia[i]) ;
    }
    
    
    
    
    float Eff[nmisure];
    float sEff[nmisure] ;
    
    for(int i = 0 ; i < nmisure ; i++){
        Eff[i] = N_tripla[i]/N_doppia[i];
        sEff[i] = sqrt(Eff[i]*(1-Eff[i])/N_doppia[i]) ;
        
        cout << "Efficienza: "<< Eff[i] << " +- " << sEff[i] << endl ;
    }
    
    
    
    
    // --------------------- Grafico Rate(Theta) - Rate in funzione dell' angolo ------------------------------ //
    
    
    // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
    TCanvas *cHV_Eff = new TCanvas("cHV_Eff","Eff(V)",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cHV_Eff->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cHV_Eff->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gHV_Eff = new TGraphErrors(nmisure ,HV,Eff, sHV,sEff);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_Eff ->SetMarkerSize(0.6);
    gHV_Eff ->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gHV_Eff->SetTitle("Eff(V)");
    // Titoli degli assi
    gHV_Eff ->GetXaxis()->SetTitle(" HV [V]");
    gHV_Eff->GetYaxis()->SetTitle("Eff");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gHV_Eff ->Draw("AP");
    // ----------------------------------------------------------------- //
    
    
    
}


