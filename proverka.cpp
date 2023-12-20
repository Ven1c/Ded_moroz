
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
struct savescam
{
    float Happy;
    int child;
    int lootbox;
};
int findM1(int** M1, int child, int gift);
int findM2(int** M2, int child, int gift);
float Happy_local(int** M1, int** M2, int gift, int child);
int** CSVscan(const string filename, int svert, int shoriz);
int main()
{
    float sum = 0;
    savescam* forall = new savescam[184000];
    int** M1 = CSVscan("kids_wish.csv", 184000, 101);
    int** M2 = CSVscan("ded_moroz_wish.csv", 1000, 185);
    int** M3 = CSVscan("solution_example.csv", 184000, 2);

    for (int i = 0; i < 184000; i++) {
        forall[i].child = i;
        forall[i].lootbox = M3[i][1];
        forall[i].Happy = Happy_local(M1, M2, M3[i][1], i);
        
        sum += forall[i].Happy;
    }
    int k = 0;

    printf("summa = %lf\n", sum / 184000);
    sum = 0;
    int** numgifts = CSVscan("numgfts_3ed.csv", 1000, 2);
    int b = 0;
    int temp = 0;
    int happyb;
    int happyk;
    int bbbbb = 0;
    int bbbb = 0;
    for (int i = 0;i<1000;i++) {
        for (int j = 0;j<184000;j++) {
            if (forall[j].lootbox == i) {
                bbbbb++;
            }
        }
        printf("%d %d\n", i, 250 - bbbbb);
        if ((250 - bbbbb) < 0) { bbbb++; }
        bbbbb = 0;
    }
    printf("%d\n", bbbb);
   
    printf("summa = %lf\n", sum / 184000);
    sum = 0;

}
int** CSVscan(const string filename, int svert, int shoriz) {
    ifstream work_file(filename);
    char delimiter = ',';
    string strInt;
    string show;
    int** temp = (int**)malloc(sizeof(int*) * svert);
    for (int i = 0; i < svert; i++) {
        temp[i] = (int*)malloc(sizeof(int) * shoriz);
        getline(work_file, show);
        stringstream stream(show);
        printf("%d\n", i);
        for (int j = 0; j < shoriz; j++) {
            getline(stream, strInt, delimiter);
            temp[i][j] = stoi(strInt);

        }

    }
    work_file.close();
    return temp;
}
float Happy_local(int** M1, int** M2, int gift, int child) {
    float happy = -2;
    int jchild = findM2(M2, child, gift);
    int jgift = findM1(M1, child, gift);



    if (jgift != -1 && jchild != -1) {
        happy = 2 * (184 - jchild) + 2 * (100 - jgift);
    }
    else if (jgift == -1 && jchild != -1) {
        happy = 2 * (184 - jchild) - 1;

    }
    else if (jchild == -1 && jgift != -1) {
        happy = 2 * (100 - jgift) - 1;
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
