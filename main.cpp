#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

typedef vector <double>   T_row;
typedef vector <T_row>   T_matr;
typedef T_matr   T_Matrix;

void maximum (string criterion, double matrix[], int k )
{

    cout << "Optimal strategy by criterion " << criterion << " number"<<" ";
    double maximum;
    for (int i = 0; i < k-1; ++i) {
        if (matrix[i] > maximum) {
            maximum = matrix[i];
        }
    }
    for (int i = 0; i < k-1; ++i) {
        if (matrix[i] == maximum) {
            cout << i+1 << " ";
        }
    }
    cout << "\n";
}
void minimum (string criterion, double matrix[], int k )
{
    cout << "Optimal strategy by criterion " << criterion << " number"<<" ";
    double minimum = matrix[0];
    for (int i = 0; i < k - 1; ++i) {
        if (matrix[i] < minimum) {
            minimum = matrix[i];
        }
    }
    for (int i = 0; i < k - 1; ++i) {
        if (matrix[i] == minimum) {
            cout << i+1 << " ";
        }
    }
    cout << "\n";
}

void Bayes_criterion(T_Matrix const &matrix, int n, int m )
{
    double bayes_matrix[n-1];
    cout << "             Bayes criterion " <<"\n";
    for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < m; j++)
                bayes_matrix[i] += matrix[i][j] * matrix[n-1][j];
				cout << bayes_matrix[i]  << "\t";
                cout << "\n";
		}
	cout << "\n";
    maximum ("Bayes ", bayes_matrix, n);
    cout << "\n";
}

void Criterion_Savage(T_Matrix const &matrix, int n, int m )
{
    T_Matrix temp (n, T_row(m));
    double savage_matrix[n-1];
    double max_column[m];


    cout << "            Savage criterion " <<"\n";
    cout << "\n";
    cout << "Maximum value of matrix columns" << "\n";
    for (int j = 0; j < m; j++){
			for (int i = 0; i < n - 1; i++)
                if (matrix[i][j] > max_column[j]) {
                max_column[j] = matrix[i][j];
            }
				cout << max_column[j]  << "\t";
		}
	cout << "\n";
	cout << "\n";
    cout << "Risk Matrix: " <<"\n";
    cout << "\n";
    for (int i = 0; i < n - 1; i++){
			for (int j = 0; j < m; j++) {
				temp[i][j] = max_column[j] - matrix[i][j];
				cout << temp[i][j] << "\t";
			}
			cout << "\n";
		}
	cout << "\n";
	cout << "Savage criterion: " <<"\n";
	cout << "\n";
    for (int i = 0; i < n - 1; i++) {
            savage_matrix[i] = temp[i][0];
			for (int j = 0; j < m; j++){
                if (temp[i][j] > savage_matrix[i]) {
                savage_matrix[i] = temp[i][j];
                }
			}
            cout <<  savage_matrix[i]  << "\t";
            cout << "\n";
    }
    cout << "\n";
    minimum("Savage ", savage_matrix, n);
    cout << "\n";
}

void Criterion_Wald(T_Matrix const &matrix, int n, int m )
{
    double wald_matrix[n-1];

    cout << "             Wald criterion" <<"\n";
    cout << "\n";

    for (int i = 0; i < n - 1; i++) {
            wald_matrix[i] = matrix[i][0];
			for (int j = 0; j < m; j++){
                if (matrix[i][j] < wald_matrix[i]) {
                wald_matrix[i] = matrix[i][j];
                }
			}
            cout <<  wald_matrix[i]  << "\t";
            cout << "\n";
    }
    cout << "\n";
    maximum("Wald ", wald_matrix, n);
    cout << "\n";
}


void Criterion_Hurwitz(T_Matrix const &matrix, int n, int m, double k )
{
   double hurwitz_matrix[n-1];
   double min_row[n-1];
   double max_row[n-1];

    cout << "             Hurwitz criterion " <<"\n";
    cout << "\n";
    cout << "Minimum value of matrix rows" <<"\n";
    cout << "\n";
    for (int i = 0; i < n - 1; i++) {
            min_row[i] = matrix[i][0];
			for (int j = 0; j < m; j++){
                if (matrix[i][j] < min_row[i]) {
                min_row[i] = matrix[i][j];
                }
			}
            cout <<  min_row[i]  << "\t";
            cout << "\n";
    }
    cout << "\n";
    cout << "Maximum value of matrix rows " <<"\n";
    cout << "\n";
    for (int i = 0; i < n - 1; i++) {
            max_row[i] = matrix[i][0];
			for (int j = 0; j < m; j++){
                if (matrix[i][j] > max_row[i]) {
                max_row[i] = matrix[i][j];
                }
			}
            cout <<  max_row[i]  << "\t";
            cout << "\n";
    }
    cout << "\n";
    cout << "Hurwitz criterion: " <<"\n";
    cout << "\n";
    for (int i = 0; i < n - 1; i++) {
                hurwitz_matrix[i] = (k * min_row[i]) + ((1 - k) * max_row[i]);
				cout << hurwitz_matrix[i]  << "\t";
                cout << "\n";
		}
    maximum("Hurwitz at  L  " + to_string(k), hurwitz_matrix, n);
    cout << "\n";
}
int main()
{


    cout<<"Inputed matrix->"<<'\n';

	ifstream in("input.txt");

	if (in.is_open())
	{


		int count = 0;
		double temp;

		while (!in.eof())
		{
			in >> temp;
			count++;
		}





		in.seekg(0, ios::beg);
		in.clear();


		int count_space = 0;
		char symbol;
		while (!in.eof())
		{

			in.get(symbol);
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;
		}



		in.seekg(0, ios::beg);
		in.clear();



		int n = count / (count_space + 1);
		int m = count_space + 1;
		T_Matrix matrix (n, T_row(m));


		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> matrix[i][j];


		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << matrix[i][j] << "\t";
			cout << "\n";
		}

        cout << endl;
        Bayes_criterion(matrix, n, m);
        cout << endl;
        Criterion_Savage(matrix, n, m);
        cout << endl;
        Criterion_Wald(matrix, n, m);
        cout << endl;
        Criterion_Hurwitz(matrix, n, m, 0.5);
        cout << endl;
        Criterion_Hurwitz(matrix, n, m, 0.3);
        cout << endl;

		in.close();
	}
	else
	{

		cout << "File not found.";
	}
}

