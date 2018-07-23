//
//  Rumore_Picchi.cpp a 30kV
//  
//
//  Created by Simone Azeglio on 07/03/17.
//
//

#include <math.h>

void Rumore_Picchi(){
    
    
    //numero misure
    const int nmisure = 66   ;
    
    
    // numero misure senza doppi
    const int nmisure2= 33 ;
    //----- DATI ------


    float ThetaX2[] = { 12, 12, 13, 13, 14, 14, 15, 15, 16, 16,
                   17, 17, 18, 18, 19, 19, 20, 20, 21, 21,
                   22, 22, 23, 23, 24, 24, 25, 25, 26, 26, //30
        
       
        
        33, 33, 38, 38, 43, 43, 48, 48, 53, 53, 54, 54, 55, 55, //44
        
        61, 61, 63, 63, //48
        
        73, 73, 78, 78, 83, 83, 88, 88, // 56
        
         101, 101, 106, 106, // 60
        
         112, 112, 117, 117, 120, 120 // 66
        
        
       
        
        
    };



    float Conteggi[] = {138, 139, 136, 118, 120, 100, 122, 104, 107, 115,
                  121, 117, 116, 117, 106, 89, 115, 131, 109, 134,
                  116, 136, 124, 117, 139, 131, 137, 133, 136, 134, //30
        
        
        
                  168, 177, 158, 145, 176, 162, 183, 200, 188, 193, 193,  205, 225, 198, // 44
        
                  200, 230, 215, 226, // 48
        
                  283, 285, 331, 299, 347, 349, 394, 375, // 56
        
                  505, 493, 534, 499, //60
        
                  548, 570, 543, 577, 619, 613 // 66
        
        
        
     };
    

    
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
        sSecondi2[i] = 0.001;
        sThetaX22[i] = 0.167;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    




    //--------------- FIT Dati -------- //
    
    TCanvas *cThetaX2Conteggi = new TCanvas("cThetaX2Conteggi ","Conteggi(ThetaX2)",200,10,800,500);
    
    
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


