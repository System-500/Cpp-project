#include <iostream>
#include <iomanip> 
#include <cmath>
using namespace std;

void wyswetlmacierze(double* a[], double* b, int w) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            cout << setw(10) << a[i][j];
        }
        cout << setw(10) << " | " << b[i] << "  " << endl;
    }
}

bool GausPodst(double* a[], double* b, int w, double* x) {
    double eps = 1e-7;
    for (int i = 0; i < w; i++) {
        if (fabs(a[i][i]) < eps) {
            cout << "BLAD: na przekotnej w tracie obliczen wystepuje 0  "; 
            return false;
        }

        for (int j = i + 1; j < w; j++) {
            double p = a[j][i] / a[i][i];
            for (int l = i; l < w; l++) {
                a[j][l] -= p * a[i][l];
            }
            b[j] -= p * b[i];
        }
    }

    for (int i = w - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < w; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }

 cout << "Macierz po eliminacji: "<<endl;
    cout << "=====================" << endl;
   
    wyswetlmacierze(a, b, w);
    cout << "=====================" << endl;

    return true;
}

bool GaussMaxKol(double* a[], double* b, int w, double* x) {
    double eps = 1e-7;

    for (int i = 0; i < w; i++) {
        int maxe = i;

        if (fabs(a[maxe][i]) < eps) {
            cout << "BLAD: na przekotnej w tracie obliczen wystepuje 0  "; 
            return false;
        }

        for (int j = i; j < w; j++) {
            if (abs(a[j][i]) > abs(a[maxe][i])) {
                maxe = j;
            }
        }

        for (int k = 0; k < w; k++) {
            swap(a[i][k], a[maxe][k]);
        }
        swap(b[i], b[maxe]);

        for (int r = i + 1; r < w; r++) {
            double p = a[r][i] / a[i][i];
            for (int o = i; o < w; o++) {
                a[r][o] -= p * a[i][o];
            }
            b[r] -= p * b[i];
        }
    }

    for (int i = w - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < w; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }


cout << "Macierz po eliminacji: "<<endl;
    cout << "=====================" << endl;
      
    wyswetlmacierze(a, b, w);
    cout << "=====================" << endl;

    return true;
}
bool GaussMaxWsz(double* a[], double* b, int n, double* x) {
    double eps = 1e-7;
    int* columnOrder = new int[n]; 
    for (int i = 0; i < n; i++) {
        columnOrder[i] = i; 
    }
    for (int k = 0; k < n - 1; k++) {
        int maxRow = k, maxCol = k;
        for (int i = k; i < n; i++) {
            for (int j = k; j < n; j++) {
                if (fabs(a[i][j]) > fabs(a[maxRow][maxCol])) {
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
        if (maxRow != k) {
            for (int j = 0; j < n; j++) {
                swap(a[k][j], a[maxRow][j]);
            }
            swap(b[k], b[maxRow]);
        }

    
        if (maxCol != k) {
            for (int i = 0; i < n; i++) {
                swap(a[i][k], a[i][maxCol]);
            }
            swap(columnOrder[k], columnOrder[maxCol]);
        }

     
        for (int i = k + 1; i < n; i++) {
            double factor = a[i][k] / a[k][k];
            b[i] -= factor * b[k];
            for (int j = k; j < n; j++) {
                a[i][j] -= factor * a[k][j];
            }
        }
    }
  for (int i = 0; i < n; i++) {
        if (fabs(a[i][i]) < eps) {
            cout << "BLAD: na przekotnej w tracie obliczen wystepuje 0  "; 
            delete[] columnOrder;
            return false;
        }
    }
 
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
    double* tmpX = new double[n];
    for (int i = 0; i < n; i++) {
        tmpX[columnOrder[i]] = x[i];
    }
    for (int i = 0; i < n; i++) {
        x[i] = tmpX[i];
    }
    delete[] columnOrder;
    delete[] tmpX;


    cout << "Macierz po eliminacji:  "<<endl;
    cout << "=====================" << endl;
      
    wyswetlmacierze(a, b, n);
    cout << "=====================" << endl;

    return true;
}
void wyniki(double* x, int n) {
    cout << "\nWynik: x = [ ";
    for (int i = 0; i < n; i++) {
        cout << x[i] << "  ";
    }
    cout << "]" << endl;
}

int main() {
    int menu, dane, n;
    cout << "Wybierz metode Gaussa:\nPodstawowa -1\nZ wyborem maksymalnej kolumny -2\nPelny wybor elementu maksumalnego -3\nWybor: ";
    cin >> menu;
     while ((menu != 1 && menu != 2 && menu != 3)) {
        cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
        cout << "Wybierz metode Gaussa:\nPodstawowa -1\nZ wyborem maksymalnej kolumny -2\nPelny wybor elementu maksumalnego -3\nWybor: ";
        cin >> menu;
    }

    cout << "Wpisac dane recznie -1\nWpisane dane  -2\nWybor: ";
    cin >> dane;
    while(dane!=1 && dane!=2){
         cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
         cout << "Wpisac dane recznie -1\nWpisane dane  -2\nWybor: ";
        cin >> dane;
    }

    if (dane == 1) {
        cout << "Wpisz illosc kolumn i wierszy macierzy  N x N :";
        cin >> n;
        if (n < 2) {
            while (n < 2) {
                cout << " ---- n musi byc wieksze lub rowne od 2 ----" << endl;
                cout << "Wpisz illosc kolumn i wierszy macierzy  N x N :";
                cin >> n; 
            }
        }

        double** A = new double*[n];
        for (int i = 0; i < n; i++) {
            A[i] = new double[n];
        }
        double* B = new double[n];
        double* x = new double[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
                cin >> A[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            cout << "B[" << i+1 << "] = ";
            cin >> B[i];
        }
     cout << "Podana macierz A|B: "<<endl;
        wyswetlmacierze(A, B, n);

        if (menu == 1) {
            if (!GausPodst(A, B, n, x)) {
                cout << endl;
            } else {
                wyniki(x, n);
            }
        }

        if (menu == 2) {
            if (!GaussMaxKol(A, B, n, x)) {
                cout<< endl;
            } else {
                wyniki(x, n);
            }
        }

        if (menu == 3) {
            if (!GaussMaxWsz(A, B, n, x)) {
                cout<< endl;
            } else {
                wyniki(x, n);
            }
        }
       
        for (int i = 0; i < n; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] B;
        delete[] x;
    }

    if (dane == 2) {
        double a[4][4] = {
            {1, 1, 0, -3},
            {1, 4, -1, -4 },
            {0.5, 0.5, -3, -5.5},
            {1.5, 3, -5, -9}
        };
        double b[4] = {1, -2, 1.5, -0.5};

        double* A[4];
        for (int i = 0; i < 4; i++) {
            A[i] = a[i];
        }
          cout << "Podana macierz A|B: "<<endl;
        wyswetlmacierze(A, b, 4);

        double* x = new double[4]; 

        if (menu == 1) {
            if (!GausPodst(A, b, 4, x)) {
                cout << "Brak obliczen" << endl;
            } else {
                wyniki(x, 4);
            }
        } else if (menu == 2) {
            if (!GaussMaxKol(A, b, 4, x)) {
                cout << "Brak obliczen" << endl;
            } else {
                wyniki(x, 4);
            }
        }

        else if (menu == 3) {
            if (!GaussMaxWsz(A, b, 4, x)) {
                cout << "Brak obliczen" << endl;
            } else {
                wyniki(x, 4);
            }
        }

        delete[] x;
    }

    return 0;
}
