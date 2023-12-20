#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>
using namespace System;
using namespace std;

struct savescam
{
    double Happy;
    int child;
    int lootbox;
};
savescam* forall;
int** M1;
int** M2;
int findM1(int** M1, int child, int gift);
int findM2(int** M2, int child, int gift);
double Happy_local(int** M1, int** M2, int gift, int child);
int** CSVscan(const string filename, int svert, int shoriz);
void main()
{   
    cout << sizeof(unsigned short) <<"---" << sizeof(char) << endl;
  
    int* numgfts = (int*)malloc(sizeof(int) * 1001);
    for (int i = 0; i < 1000; i++) {
        numgfts[i] = 250;
    }
    numgfts[1000] = 0;
    forall = new savescam[184000];
    double sum = 0;
   
    int** M3 = (int**)malloc(sizeof(int*) * 184000);
    for (int i = 0; i < 184000; i++){ 
        M3[i] = (int*)malloc(sizeof(int) * 2);
        M3[i][0] = i;
        M3[i][1] = -1;
   
    }
    bool* checkfinal = (bool*)malloc(sizeof(bool) * 184000);
    for (int i = 0; i < 184000; i++) { checkfinal[i] = false; }
    M1 = CSVscan("kids_wish.csv", 184000, 101);
    cout << "First complite" << endl;
    M2 = CSVscan("ded_moroz_wish.csv", 1000, 185);
    cout << "Second complite" << endl;
    int some = sizeof(savescam);
   
    for (int i = 0; i < 184000; i++) {
        forall[i].Happy = -10000;
        forall[i].child = -1;
        forall[i].lootbox = -1;
    }


    for (int i = 0; i < 1001; i++) {
        cout << "kol vo podarkov "<< i<<"===="<< numgfts[i] << endl;
    }
  
    bool flag = false;

    sum = 0;
    for (int k = 0; k < 184000; k++) {
        

        for (int o = 1; o < 101; o++) {
            if ( k % 2==0 && k < 5520 && ((Happy_local(M1, M2, M1[k][o], k)+ Happy_local(M1, M2, M1[k][o], k+1))> forall[k].Happy+ forall[k+1].Happy)) {
                forall[k].Happy = Happy_local(M1, M2, M1[k][o], k);
                forall[k+1].Happy = Happy_local(M1, M2, M1[k][o], k+1);
                forall[k].child = k;
                forall[k+1].child = k+1;
                forall[k].lootbox = M1[k][o];
                forall[k+1].lootbox = M1[k][o];
            }
            if ( k>5519 && (Happy_local(M1, M2, M1[k][o], k) > forall[k].Happy) && (numgfts[M1[k][o]] > 0)) {
                forall[k].Happy = Happy_local(M1, M2, M1[k][o], k);
                forall[k].child = k;
                forall[k].lootbox = M1[k][o];
                cout << "proverka urovnia " << k << " ===== " << forall[k].Happy << endl;;
                
            }
        }
        if (k % 2 == 0 && k < 5520) {
            numgfts[forall[k].lootbox]--;
            numgfts[forall[k].lootbox]--;
        }
        else{
            numgfts[forall[k].lootbox]--;
        }
        M3[k][1] = forall[k].lootbox;
        
        sum += forall[k].Happy;
    }
    std::ofstream bout("numgfts.txt");
    for (int i = 0; i < 1000; i++) {
        bout << i << ","<< numgfts[i] << endl;
    }
    int b = 0;
    int temp = 0;
    int temp1 = 0;
    int happyb;
    int happyk;
    int happyb1;
    int happyk1;
   
    for (int k = 0; k < 1000; k++) {
        for (int o = 1; o < 185; o++) {

            if (M2[k][o]>5520 && (Happy_local(M1, M2, k, M2[k][o]) > forall[M2[k][o]].Happy) && (numgfts[k] > 0)) {
                forall[M2[k][o]].Happy = Happy_local(M1, M2, k,M2[k][o]);
                numgfts[forall[M2[k][o]].lootbox]++;
                forall[M2[k][o]].lootbox = k;
                numgfts[k]--;
                M3[M2[k][o]][1] = forall[M2[k][o]].lootbox;
                cout<<"proverka dedovskogo urovnia "<< M2[k][o] <<" ===== "<< forall[M2[k][o]].Happy<<endl;

            }
        }
        
    }
    float pp;


    for (int i = 0; i < 184000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (i % 2 == 0 && i < 5520 && ((Happy_local(M1, M2, j, i) + Happy_local(M1, M2, j, i + 1)) > forall[i].Happy + forall[i + 1].Happy) && numgfts[j] > 1) {
                numgfts[forall[i].lootbox]++;
                numgfts[forall[i+1].lootbox]++;
                forall[i].lootbox = j;
                forall[i+1].lootbox = j;
                numgfts[j]--;
                numgfts[j]--;
            }
            if (i > 5519 && (forall[i].Happy < Happy_local(M1, M2, j, i)) && numgfts[j] > 0) {
                
                numgfts[forall[i].lootbox]++;
                forall[i].lootbox = j;
                numgfts[j]--;
                forall[i].Happy = Happy_local(M1, M2, j, i);
              
            }
        }
        sum += forall[i].Happy;
        M3[i][1] = forall[i].lootbox;
    }
    for (int k = 0; k < 5520; k++) {
        b = k;
        cout << "perestanovka=" << k << endl;
        while (b < 5520) {
            if (k % 2 == 0 && b % 2 == 0) {
                happyb = Happy_local(M1, M2, forall[k].lootbox, b + 1) + Happy_local(M1, M2, forall[k].lootbox, b);
                happyk = Happy_local(M1, M2, forall[b].lootbox, k + 1) + Happy_local(M1, M2, forall[b].lootbox, k);
                if ((forall[k].Happy + forall[b].Happy+forall[k+1].Happy + forall[b+1].Happy) < (happyb + happyk)) {
                    pp = (happyb + happyk) - (forall[k].Happy + forall[b].Happy);
                    forall[k].Happy = Happy_local(M1, M2, forall[b].lootbox, k);
                    forall[b].Happy = Happy_local(M1, M2, forall[k].lootbox, b);
                    forall[k+1].Happy = Happy_local(M1, M2, forall[b].lootbox, k + 1);
                    forall[b + 1].Happy = Happy_local(M1, M2, forall[k].lootbox, b + 1);
                    temp = forall[b].lootbox;
                    forall[b].lootbox = forall[k].lootbox;
                    forall[b+1].lootbox = forall[k+1].lootbox;
                    forall[k].lootbox = temp;
                    forall[k + 1].lootbox = temp;
                    M3[k][1] = forall[k].lootbox;
                    M3[k+1][1] = forall[k+1].lootbox;
                    M3[b][1] = forall[b].lootbox;
                    M3[b+1][1] = forall[b+1].lootbox;
                    cout << "proizvedeno +++" << pp << endl;
                }
            }
            b++;
        }
    }





    for (int k = 5520; k < 184000; k++) {

        b = k;
        printf("perestanovka = %d\n", k);
        while (b < 184000) {
            happyb = Happy_local(M1, M2, forall[k].lootbox, b);
            happyk = Happy_local(M1, M2, forall[b].lootbox, k);
            if ((forall[k].Happy + forall[b].Happy) < (happyb + happyk)) {
                pp = (happyb + happyk) - (forall[k].Happy + forall[b].Happy);
                forall[k].Happy = happyk;
                forall[b].Happy = happyb;
                temp = forall[b].lootbox;
                forall[b].lootbox = forall[k].lootbox;
                forall[k].lootbox = temp;
                M3[k][1] = forall[k].lootbox;
                M3[b][1] = forall[b].lootbox;

                printf("proizvedeno +++%lf\n", pp);
            }
            b++;
        }
    }

   




    for (int i = 0; i < 184000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (i % 2 == 0 && i < 5520 && ((Happy_local(M1, M2, j, i) + Happy_local(M1, M2, j, i + 1)) > forall[i].Happy + forall[i + 1].Happy) && numgfts[j] > 1) {
                numgfts[forall[i].lootbox]++;
                numgfts[forall[i + 1].lootbox]++;
                forall[i].lootbox = j;
                forall[i + 1].lootbox = j;
                numgfts[j]--;
                numgfts[j]--;

            }
            if (i > 5519 && (forall[i].Happy < Happy_local(M1, M2, j, i)) && numgfts[j] > 0) {

                numgfts[forall[i].lootbox]++;
                forall[i].lootbox = j;
                numgfts[j]--;
                forall[i].Happy = Happy_local(M1, M2, j, i);

            }
        }
        sum += forall[i].Happy;
        M3[i][1] = forall[i].lootbox;
    }


    sum = 0;
    for (int k = 0; k < 184000; k++) {
        sum += forall[k].Happy;
    }
    cout<<"summa ="<< sum/1000000<<endl;
    std::ofstream out("Bratchikov_Agapov-2.csv");
    out << "ChildId,GiftId" << endl;
    for (int i = 0; i < 184000; i++) {
        out << M3[i][0] << "," << M3[i][1] << endl;
    }

}
int** CSVscan(const string filename,int svert, int shoriz) {
    ifstream work_file(filename);
    char delimiter = ',';
    string strInt;
    string show;
    int** temp = (int**)malloc(sizeof(int*) * svert);
    for (int i = 0; i < svert; i++) {
        temp[i] = (int*)malloc(sizeof(int) * shoriz);
        getline(work_file, show);
        stringstream stream(show);
        cout << i << endl;
        for (int j = 0; j < shoriz; j++) {
            getline(stream, strInt, delimiter);
            temp[i][j] = stoi(strInt);
            
        }
        
    }
    work_file.close();
    return temp;
}
double Happy_local(int** M1, int** M2, int gift, int child) {
    double happy = -2;
    double jchild = findM2(M2, child, gift);
    double jgift = findM1(M1, child, gift);



    if (jgift != -1 && jchild != -1) {
        happy = 2 *(184 - jchild) * 10000 /250 + 2 * (100 - jgift) * 10000 /184;
    }
    else if (jgift == -1 && jchild != -1) {
        happy = (2 * (184 - jchild) - 1) * 10000 / 250;

    }
    else if (jchild == -1 && jgift != -1) {
        happy =( 2 * (100 - jgift) - 1 ) * 10000 / 184;
    }

    return happy;
}

int findM1(int** M1, int child, int gift) {
    for (int i = 0; i < 101; i++) {
        if (M1[child][i] == gift) {
            i--;
            return i;
        }
    }
    return -1;
}
int findM2(int** M2, int child, int gift) {
    for (int i = 0; i < 185; i++) {
        if (M2[gift][i] == child) {
            i--;
            return i;
        }
    }
    return -1;
}
