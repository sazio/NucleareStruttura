//
//  Poisson.cpp
//  
// Distribuzione di Poisson come suggerito da Professoressa Marcello
//  Created by Simone Azeglio on 20/02/17.
//
//

#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include <math.h>
#include  <iostream>

using namespace std ;

void Poisson2_7(){
    
    /*
     
     Valori di riferimento per i range -- Inutili nel codice ma solo come controllo
     
     double X_g1_Begin = -186.16 ;
     double X_g1_End = 276.84 ;
     
     double X_g2_Begin = 280.03;
     double X_g2_End = 737.03 ;
     
     double X_g3_Begin = 734.604 ;
     double X_g3_End = 1195.644 ;
     
     double X_g4_Begin = 1197.35;
     double X_g4_End = 1655.35;
     
     double X_g5_Begin = 1655.71 ;
     double X_g5_End = 2105.171  ;
     

    */
    
    
    
    // Conteggi prima Gaussiana
    
   Float_t Conteggi_1[] = {4, 5, 9, 12, 14, 13, 18, 18, 26, 37, 53, 54, 76, 97, 136, 178, 258, 386, 542, 845, 1372, 2134, 3186, 4579, 5885, 7190, 8409, 9208, 9649, 9557, 9020, 7710, 6638, 5043, 3823, 2597, 1768, 1129, 767, 509, 377, 321, 284, 232, 240, 256, 234, 200, 202, 193, 199, 186, 212, 205, 173, 202, 165, 158};
    
    Float_t somma1 = 0  ;
    
    // Calcolo somma dei conteggi nel range della prima Gaussiana in modo da fare
    // un nuovo istogramma
    
    
    // N.B. sizeof() mi da il valore in  bit --> essendo un float tipicamente di 4 bit , per avere
    // il numero di elementi sono costretto a fare sizeof()/4
    for(int index = 0 ; index < sizeof(Conteggi_1)/4; index++){
        somma1 = somma1 + Conteggi_1[index] ;
    }
    
    // Ripeto la procedura per le Gaussiane rimanenti
    
   Float_t Conteggi_2[] = {184, 202, 171, 190, 224, 219, 205, 247, 290, 315, 312, 396, 401, 526, 623, 815, 1058, 1398, 1955, 2601, 3584, 4815, 6333, 7853, 9541, 10857, 12123, 13116, 13435, 13400, 12501, 11405, 9945, 8195, 6700, 5128, 3899, 2852, 2118, 1607, 1216, 1030, 926, 874, 800, 786, 837, 821, 800, 794, 844, 797, 778, 819, 842, 857, 849};
    
    Float_t somma2 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_2)/4 ; index++){
        somma2 = somma2 + Conteggi_2[index] ;
    }

    
   Float_t Conteggi_3[] = {882, 935, 950, 934, 880, 1002, 929, 1060, 1024, 1111, 1179, 1205, 1330, 1427, 1593, 1754, 2090, 2584, 3012, 3744, 4545, 5483, 6709, 7755, 9092, 10178, 11379, 12103, 12535, 12469, 12058, 11365, 10546, 9305, 7971, 6596, 5419, 4362, 3592, 2825, 2270, 1913, 1702, 1563, 1458, 1477, 1417, 1453, 1447, 1508, 1541, 1496, 1554, 1578, 1553, 1667, 1697, 1587};
    
    
   Float_t somma3 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_3)/4 ; index++){
        somma3 = somma3 + Conteggi_3[index] ;
    }

    
    Float_t Conteggi_4[] = {1753, 1673, 1637, 1701, 1779, 1820, 1875, 1992, 1901, 2011, 2187, 2244, 2345, 2519, 2863, 2952, 3325, 3902, 4260, 4765, 5585, 6147, 6826, 7651, 8580, 8957, 9648, 9777, 9912, 9955, 9354, 8823, 8085, 7230, 6287, 5436, 4693, 3817, 3421, 2848, 2492, 2224, 2008, 2007, 1892, 1907, 1920, 1874, 2015, 1849, 2045, 2018, 2036, 2021, 2086, 2145, 2152};
    
    
  Float_t somma4 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_4)/4 ; index++){
        somma4 = somma4 + Conteggi_4[index] ;
    }
    

    
  Float_t Conteggi_5[] = {2138, 2158, 2188, 2372, 2302, 2401, 2366, 2479, 2495, 2548, 2690, 2793, 2928, 3008, 3134, 3433, 3554, 3933, 4153, 4477, 4902, 5390, 5736, 6175, 6502, 6826, 7227, 7143, 7190, 7135, 6933, 6425, 6118, 5547, 5070, 4627, 4131, 3475, 3225, 2928, 2556, 2451, 2224, 2137, 2124, 2101, 2145, 2046, 2089, 2143, 2211, 2166, 2201, 2177, 2266, 2352};
    
    
   Float_t somma5 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_5)/4 ; index++){
        somma5 = somma5 + Conteggi_5[index] ;
    }
    
    

    // A questo punto definisco il numero di bin per l' istogramma
    // i dati sono le somme dei conteggi per ogni gaussiana
    const Int_t np = 5 ;
    Float_t x[np] = {somma1, somma2, somma3, somma4, somma5};
    
    Float_t x_error[np] ;
    
    for(int i = 0 ; i < np ; i++)
    { x_error[i] = sqrt(x[i]);
    }
    
    
    
    
    // Istanzio l' istogramma
    //
    //CERCARE OPZIONI EDITING IN MODO DA FARLO PIU' CARINO
    
    TH1F *h = new TH1F("h","Poisson",np,0,5);
    h->SetMaximum(300000);
    h->GetXaxis()->SetTitle("X");
    h->GetYaxis()->SetTitle("Y");
    h->Draw();
    
    for (int i=0;i<np;i++) {
        h->SetBinContent(i+1,x[i]);
    }
    
    
    
  
    

    
    // Definisco la Distribuzione di Poisson tramite funzione gamma per esprimere l'esponenziale
    
    TF1 *f1 = new TF1("f1","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)", 0, 5); // "xmin" = 0, "xmax" = 5
    f1->SetParameters(1, 2.75, 1); // you MUST set non-zero initial values for parameters
    h->Fit("f1", "R"); // "R" = fit between "xmin" and "xmax" of the "f1"
    f1 ->SetLineColor(4);
     
  
     
    

   
    
    
    
}

