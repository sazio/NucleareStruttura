//
//  EsempioMultifit.cpp
//  
//
//  Created by Simone Azeglio on 14/02/17.
//
//

#include <stdio.h>
#include "TH1.h"
#include "TF1.h"
#include <math.h>

void EsempioMultifit() {

    const Int_t np = 2000 ;
    Float_t x[np] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 6, 6, 1, 5, 4, 5, 9, 12, 14, 13, 18, 18, 26, 37, 53, 54, 76, 97, 136, 178, 258, 386, 542, 845, 1372, 2134, 3186, 4579, 5885, 7190, 8409, 9208, 9649, 9557, 9020, 7710, 6638, 5043, 3823, 2597, 1768, 1129, 767, 509, 377, 321, 284, 232, 240, 256, 234, 200, 202, 193, 199, 186, 212, 205, 173, 202, 165, 158, 184, 202, 171, 190, 224, 219, 205, 247, 290, 315, 312, 396, 401, 526, 623, 815, 1058, 1398, 1955, 2601, 3584, 4815, 6333, 7853, 9541, 10857, 12123, 13116, 13435, 13400, 12501, 11405, 9945, 8195, 6700, 5128, 3899, 2852, 2118, 1607, 1216, 1030, 926, 874, 800, 786, 837, 821, 800, 794, 844, 797, 778, 819, 842, 857, 849, 882, 935, 950, 934, 880, 1002, 929, 1060, 1024, 1111, 1179, 1205, 1330, 1427, 1593, 1754, 2090, 2584, 3012, 3744, 4545, 5483, 6709, 7755, 9092, 10178, 11379, 12103, 12535, 12469, 12058, 11365, 10546, 9305, 7971, 6596, 5419, 4362, 3592, 2825, 2270, 1913, 1702, 1563, 1458, 1477, 1417, 1453, 1447, 1508, 1541, 1496, 1554, 1578, 1553, 1667, 1697, 1587, 1753, 1673, 1637, 1701, 1779, 1820, 1875, 1992, 1901, 2011, 2187, 2244, 2345, 2519, 2863, 2952, 3325, 3902, 4260, 4765, 5585, 6147, 6826, 7651, 8580, 8957, 9648, 9777, 9912, 9955, 9354, 8823, 8085, 7230, 6287, 5436, 4693, 3817, 3421, 2848, 2492, 2224, 2008, 2007, 1892, 1907, 1920, 1874, 2015, 1849, 2045, 2018, 2036, 2021, 2086, 2145, 2152, 2138, 2158, 2188, 2372, 2302, 2401, 2366, 2479, 2495, 2548, 2690, 2793, 2928, 3008, 3134, 3433, 3554, 3933, 4153, 4477, 4902, 5390, 5736, 6175, 6502, 6826, 7227, 7143, 7190, 7135, 6933, 6425, 6118, 5547, 5070, 4627, 4131, 3475, 3225, 2928, 2556, 2451, 2224, 2137, 2124, 2101, 2145, 2046, 2089, 2143, 2211, 2166, 2201, 2177, 2266, 2352, 2259, 2354, 2362, 2487, 2341, 2448, 2494, 2570, 2724, 2656, 2700, 2729, 2970, 2883, 2852, 3039, 3221, 3233, 3526, 3717, 3883, 4103, 4285, 4417, 4576, 4894, 4827, 5001, 5011, 4921, 4998, 4821, 4536, 4330, 4032, 3887, 3542, 3311, 2978, 2850, 2632, 2394, 2335, 2297, 2035, 1969, 2059, 1994, 2015, 2011, 1995, 2084, 2072, 2179, 2103, 2171, 2193, 2199, 2304, 2227, 2206, 2296, 2327, 2363, 2270, 2352, 2451, 2483, 2525, 2516, 2542, 2570, 2752, 2678, 2886, 2837, 2989, 3058, 3134, 3193, 3289, 3358, 3406, 3344, 3476, 3484, 3452, 3322, 3363, 3047, 3085, 2959, 2932, 2569, 2437, 2358, 2133, 2198, 2034, 1992, 1862, 1875, 1785, 1817, 1763, 1790, 1789, 1820, 1900, 1776, 1899, 1871, 1784, 1847, 1890, 1913, 1912, 1920, 1945, 1951, 1891, 2022, 2040, 2001, 2047, 2016, 2036, 2091, 2076, 2119, 2097, 2254, 2250, 2337, 2248, 2379, 2402, 2441, 2474, 2425, 2536, 2453, 2438, 2405, 2365, 2320, 2191, 2192, 2070, 1984, 2012, 1836, 1800, 1702, 1707, 1579, 1565, 1544, 1452, 1494, 1488, 1459, 1458, 1458, 1515, 1447, 1497, 1519, 1488, 1558, 1581, 1469, 1544, 1529, 1515, 1533, 1587, 1603, 1572, 1545, 1599, 1594, 1558, 1601, 1599, 1628, 1718, 1559, 1683, 1650, 1698, 1684, 1711, 1615, 1781, 1656, 1625, 1679, 1642, 1646, 1599, 1656, 1553, 1575, 1567, 1508, 1382, 1371, 1408, 1332, 1239, 1295, 1245, 1207, 1180, 1154, 1147, 1116, 1164, 1137, 1133, 1126, 1145, 1171, 1123, 1097, 1158, 1188, 1174, 1200, 1150, 1135, 1121, 1204, 1164, 1123, 1168, 1136, 1148, 1162, 1193, 1246, 1199, 1166, 1139, 1152, 1213, 1200, 1216, 1141, 1229, 1200, 1181, 1161, 1167, 1157, 1119, 1079, 1070, 1034, 1067, 1008, 1015, 996, 976, 989, 978, 971, 890, 885, 870, 901, 870, 881, 893, 817, 893, 843, 844, 884, 880, 786, 874, 847, 845, 872, 872, 836, 879, 853, 885, 808, 830, 792, 843, 831, 824, 837, 854, 858, 844, 806, 816, 883, 786, 853, 855, 818, 877, 804, 832, 779, 720, 747, 793, 786, 759, 732, 769, 664, 720, 711, 700, 676, 657, 660, 675, 644, 619, 632, 628, 616, 614, 637, 642, 607, 621, 607, 571, 654, 576, 595, 589, 579, 591, 596, 587, 588, 626, 568, 579, 581, 577, 563, 552, 558, 576, 576, 570, 543, 602, 519, 549, 589, 552, 556, 556, 563, 536, 525, 521, 517, 536, 495, 486, 519, 489, 494, 480, 484, 494, 451, 475, 478, 500, 418, 465, 437, 435, 425, 459, 443, 466, 436, 446, 448, 463, 434, 419, 428, 421, 426, 395, 443, 417, 421, 437, 408, 355, 403, 401, 405, 390, 379, 377, 371, 409, 355, 382, 380, 394, 377, 381, 378, 350, 355, 349, 325, 359, 375, 354, 338, 368, 318, 330, 337, 299, 335, 304, 328, 353, 284, 304, 321, 323, 283, 322, 315, 329, 297, 319, 313, 301, 311, 270, 296, 288, 266, 305, 292, 317, 315, 277, 289, 239, 294, 283, 269, 268, 271, 270, 260, 253, 241, 248, 257, 253, 232, 239, 230, 227, 233, 237, 199, 233, 234, 217, 230, 210, 226, 237, 237, 212, 216, 219, 220, 204, 208, 228, 200, 215, 209, 223, 190, 179, 194, 183, 210, 198, 185, 214, 186, 209, 195, 178, 209, 174, 190, 193, 178, 195, 184, 171, 177, 170, 162, 161, 176, 198, 199, 155, 171, 166, 172, 172, 150, 169, 155, 153, 169, 140, 150, 156, 147, 158, 174, 137, 153, 142, 171, 150, 141, 124, 138, 145, 140, 152, 135, 126, 142, 138, 130, 135, 113, 124, 118, 122, 138, 129, 134, 130, 121, 124, 94, 119, 116, 133, 127, 110, 96, 99, 95, 123, 104, 120, 133, 108, 116, 95, 91, 98, 114, 110, 94, 104, 98, 76, 115, 105, 91, 89, 101, 92, 114, 91, 94, 76, 86, 89, 90, 85, 76, 83, 85, 90, 89, 95, 98, 86, 77, 81, 74, 83, 96, 80, 97, 79, 80, 95, 74, 80, 77, 81, 70, 85, 86, 87, 76, 55, 68, 65, 72, 63, 60, 75, 70, 78, 62, 90, 78, 66, 70, 67, 56, 60, 56, 58, 66, 72, 70, 49, 61, 59, 57, 39, 59, 61, 67, 52, 67, 62, 58, 41, 67, 44, 63, 55, 59, 55, 50, 55, 44, 40, 49, 41, 55, 45, 64, 52, 40, 49, 46, 40, 33, 42, 38, 45, 49, 48, 40, 51, 40, 45, 55, 52, 41, 41, 48, 44, 41, 47, 36, 36, 34, 27, 43, 36, 40, 38, 37, 37, 42, 38, 30, 36, 37, 29, 27, 32, 25, 32, 33, 35, 36, 37, 33, 29, 36, 45, 32, 34, 38, 40, 35, 39, 26, 37, 28, 35, 30, 33, 32, 36, 36, 30, 22, 27, 24, 31, 26, 21, 29, 27, 24, 36, 32, 26, 26, 27, 22, 25, 24, 23, 25, 20, 27, 33, 24, 25, 17, 20, 26, 22, 27, 21, 24, 16, 18, 21, 19, 22, 22, 17, 22, 20, 28, 19, 32, 21, 15, 20, 23, 17, 23, 22, 10, 20, 17, 23, 13, 24, 14, 21, 16, 19, 18, 12, 19, 27, 13, 15, 19, 19, 16, 13, 18, 22, 14, 16, 11, 19, 14, 18, 16, 17, 17, 17, 12, 12, 10, 12, 14, 14, 13, 13, 13, 12, 14, 18, 12, 13, 9, 9, 8, 9, 10, 10, 10, 13, 14, 12, 12, 13, 12, 13, 14, 12, 8, 8, 9, 7, 13, 16, 9, 15, 6, 8, 11, 9, 8, 14, 10, 15, 9, 13, 6, 11, 14, 8, 11, 8, 9, 10, 13, 10, 11, 4, 8, 5, 12, 14, 6, 8, 9, 8, 7, 14, 5, 7, 3, 3, 6, 8, 7, 5, 10, 8, 6, 6, 7, 2, 4, 6, 2, 10, 7, 6, 5, 6, 2, 6, 4, 4, 9, 10, 3, 7, 5, 6, 7, 6, 3, 4, 8, 7, 2, 7, 11, 5, 7, 10, 7, 2, 5, 3, 6, 4, 8, 2, 1, 2, 5, 7, 1, 7, 5, 3, 4, 5, 2, 6, 4, 6, 3, 4, 3, 4, 7, 0, 4, 2, 0, 5, 2, 3, 12, 4, 5, 3, 1, 4, 5, 5, 4, 5, 2, 2, 4, 4, 2, 0, 4, 6, 2, 3, 4, 2, 4, 5, 4, 6, 5, 7, 2, 4, 2, 2, 2, 1, 5, 3, 1, 2, 3, 6, 1, 4, 5, 3, 3, 4, 7, 0, 0, 3, 2, 4, 2, 1, 2, 1, 3, 3, 3, 3, 4, 2, 3, 4, 2, 1, 0, 1, 5, 4, 0, 0, 2, 2, 3, 1, 1, 1, 3, 1, 2, 3, 0, 1, 1, 1, 0, 2, 2, 2, 3, 5, 3, 4, 2, 0, 3, 3, 3, 2, 1, 2, 2, 1, 0, 0, 1, 2, 3, 2, 3, 2, 3, 0, 0, 2, 1, 1, 0, 4, 1, 1, 2, 0, 0, 1, 1, 1, 1, 0, 2, 1, 2, 1, 1, 0, 2, 0, 0, 1, 0, 1, 1, 1, 0, 4, 0, 1, 0, 0, 0, 1, 0, 2, 1, 1, 2, 0, 0, 0, 1, 2, 0, 2, 1, 2, 1, 3, 1, 2, 0, 1, 1, 1, 1, 1, 0, 1, 0, 2, 1, 1, 2, 2, 1, 2, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 4, 0, 1, 0, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 1, 3, 1, 0, 2, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 2, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    Float_t x_error[np] ;
    
    for(int i = 0 ; i < np ; i++)
    { x_error[i] = sqrt(x[i]);
        }
    
    
    
    
    
    
    TH1F *h = new TH1F("h","Example of several fits in subranges",np,-996.500,14957.000);
    h->SetMaximum(14000);
    h->GetXaxis()->SetTitle("X");
    h->GetYaxis()->SetTitle("Y");
    
    for (int i=0;i<np;i++) {
        h->SetBinContent(i+1,x[i]);
        }
    
    Double_t par[15];
    TF1 *g1    = new TF1("g1","gaus",-186.16,276.84);
    TF1 *g2    = new TF1("g2","gaus",280.03,737.03);
    TF1 *g3    = new TF1("g3","gaus",734.644,1195.644);
    TF1 *g4    = new TF1("g4","gaus",1197.35,1655.35);
    TF1 *g5    = new TF1("g5","gaus",1655.71,2105.71);
    //TF1 *g6    = new TF1("g6","gaus",25.61,29.40);
   // TF1 *g7   = new TF1("g7","gaus",29.41,32.80);
  
    TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)",-186.16,2015.71);
    
    
  
    
    
    total->SetLineColor(3);
    h->Fit(g1,"R");
    h->Fit(g2,"R+");
    h->Fit(g3,"R+");
    h->Fit(g4,"R+");
    h->Fit(g5,"R+");
   // h->Fit(g6,"R+");
   // h->Fit(g7,"R+");
    g1->GetParameters(&par[0]);
    g2->GetParameters(&par[3]);
    g3->GetParameters(&par[6]);
    g4->GetParameters(&par[9]);
    g5->GetParameters(&par[12]);
   // g6->GetParameters(&par[15]);
  // g7->GetParameters(&par[18]);
    total->SetParameters(par);
    h->Fit(total,"R+");

cout << "1---Chi^2:" << g1->GetChisquare() << ", number of DoF: " << g1->GetNDF() << " (Probability: " << g1->GetProb() << ")." << endl;
cout << "2---Chi^2:" << g2->GetChisquare() << ", number of DoF: " << g2->GetNDF() << " (Probability: " << g2->GetProb() << ")." << endl;
cout << "3---Chi^2:" << g3->GetChisquare() << ", number of DoF: " << g3->GetNDF() << " (Probability: " << g3->GetProb() << ")." << endl;
cout << "4---Chi^2:" << g4->GetChisquare() << ", number of DoF: " << g4->GetNDF() << " (Probability: " << g4->GetProb() << ")." << endl;
cout << "5---Chi^2:" << g5->GetChisquare() << ", number of DoF: " << g5->GetNDF() << " (Probability: " << g5->GetProb() << ")." << endl;
//cout << "6---Chi^2:" << g6->GetChisquare() << ", number of DoF: " << g6->GetNDF() << " (Probability: " << g6->GetProb() << ")." << endl;
//cout << "7---Chi^2:" << g7->GetChisquare() << ", number of DoF: " << g7->GetNDF() << " (Probability: " << g7->GetProb() << ")." << endl;


    
    
    
    
}