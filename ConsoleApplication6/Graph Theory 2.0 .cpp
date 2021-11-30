#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

#define MAX 100 //so dinh toi da cua do thi
#define VoCuc - 1 
#define VOCUC 1000

struct Graph {
    int sodinh;//so dinh do thi
    int a[MAX][MAX];//ma tran ke
	int visited[MAX];
};

void nhapmatranke(Graph& g);
void docmatran(Graph &g);
void xuatmatran(Graph& g);
//bool kiemtra(Graph  g);
void prim(Graph& g);
void fordbellman(int S, int F, Graph&g);
void menu(Graph& g);

int main()
{
	Graph h;
	menu(h);
	return 0;
}

void nhapmatranke(Graph& g)
{
    ofstream Matran("Matrix.txt");
    cout << "So dinh cua do thi: ";
	cin >> g.sodinh;
    Matran << setw(4) << g.sodinh << endl;
    cout << "Nhap ma tran ke: " << endl;
    for (int i = 0; i < g.sodinh; i++)
    {
        for (int j = 0; j < g.sodinh; j++)
        {
			cin >> g.a[i][j];
			if (j != g.sodinh-1)  Matran << setw(4) << g.a[i][j];
			else Matran << setw(4) << g.a[i][j] << endl;
        }
    }
    Matran.close();
}

void docmatran(Graph& g)
{
    fstream f;
    f.open("Matrix.txt", ios::in);
    f >> g.sodinh;
    for (int i = 0; i < g.sodinh; i++)
        for (int j = 0; j < g.sodinh; j++)
            f >> g.a[i][j];
}

void docmatranfile(Graph& g, string tenfile)
{
	fstream f;
	f.open(tenfile, ios::in);
	f >> g.sodinh;
	for (int i = 0; i < g.sodinh; i++)
		for (int j = 0; j < g.sodinh; j++)
			f >> g.a[i][j];
}
void xuatmatran(Graph& g)
{
    cout << "So dinh cua do thi: "<< g.sodinh << endl;
    for (int i = 0; i < g.sodinh; i++)
    {
        for (int j = 0; j < g.sodinh; j++)
            cout << setw(4) << g.a[i][j];
        cout << endl;
    }
}
bool kiemtra(Graph  &g)
{
	for (int i = 0; i < g.sodinh; i++)
	{
		if (g.a[i][i] != 0)
			return 0;
		return 1;
	}
}
struct CANH
{
	int u;//Dinh thu nhat
	int v;//Dinh thu hai
	int trongso;
};
int nSoMienLienThong;
void visit(Graph g, int i, int nLabel)
{
	g.visited[i] = nLabel;
	for (int j = 0; j < g.sodinh; j++)
		if ((g.visited[j] == 0) && (g.a[i][j] != 0))
			visit(g, j, nLabel);
}
bool XetLienThong(Graph& g)
{
	for (int i = 0; i < g.sodinh; i++)
		g.visited[i] = 0;
	nSoMienLienThong = 0;
	for (int i = 0; i < g.sodinh; i++)
		if (g.visited[i] == 0) {
			nSoMienLienThong++;
			visit(g, i, nSoMienLienThong);
		}
	if (nSoMienLienThong > 1)
		return 0;
	return 1;
}

CANH T[MAX];
void prim(Graph& g)
{
	int nT = 0;
	for (int i = 0; i < g.sodinh; i++)
		g.visited[i] = 0;

	g.visited[0] = 1;

	while (nT < g.sodinh - 1)
	{
		CANH canhnhonhat;
		int min = -1;	
		for (int i = 0; i < g.sodinh; i++)
			if (g.visited[i] == 0) 
			{
				for (int j = 0; j < g.sodinh; j++)
					if (g.visited[j] == 1 && (g.a[i][j] != 0)) {
						if (min == -1 || g.a[i][j] < min) {
							min = g.a[i][j];
							canhnhonhat.u = i;
							canhnhonhat.v = j;
							canhnhonhat.trongso = g.a[i][j];
						}
					}
			}

		T[nT] = canhnhonhat;
		nT++;

		g.visited[canhnhonhat.u] = 1;

	}
	//Tổng trọng số của cây khung
	int sum = 0;
	cout << "Cay khung nho nhat cua do thi la: " << endl;
	for (int i = 0; i < nT; i++)
	{
		cout << "(" << T[i].v << ", " << T[i].u << ") ";
		sum += T[i].trongso;
	}
	cout << endl;
	cout << "Tong gia tri cua cay la: " << sum << endl;
}

int LuuVet[MAX];//<1>
int ChuaXet[MAX];//<2>
int DoDaiDuongDiToi[MAX];//<3>

int TimDuongDiNhoNhat(Graph g) {
	int min = -1;
	float p = VOCUC;
	//begin <4>
	for (int i = 0; i < g.sodinh; i++)
	{
		if (ChuaXet[i] == 0 && DoDaiDuongDiToi[i] < p)
		{
			p = DoDaiDuongDiToi[i];
			min = i;
		}
	}
	return min;
}

void CapNhatDuongDi(int u, Graph g)
{
	ChuaXet[u] = 1;
	for (int v = 0; v < g.sodinh; v++)
	{
		if (ChuaXet[v] == 0 &&  g.a[u][v] < VOCUC)
			if (DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v]) {
				DoDaiDuongDiToi[v] = DoDaiDuongDiToi[u] + g.a[u][v];
				LuuVet[v] = u;
			}
	}
}
void fordbellman(int S, int F, Graph& g) {
	int i;
	for (i = 0; i < g.sodinh; i++)
	{
		ChuaXet[i] = 0;
		DoDaiDuongDiToi[i] = VOCUC;
		LuuVet[i] = -1;
	}
	DoDaiDuongDiToi[S] = 0;

	while (ChuaXet[F] == 0) 
	{
	int u = TimDuongDiNhoNhat(g); 
	if (u == -1) break;
	CapNhatDuongDi(u,g); 
	}
		if (ChuaXet[F] == 1) 
		{
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n\t",S,F);
		i = F;
		printf("%d ", F);
		while (LuuVet[i] != S)
		{
		printf("<-%d", LuuVet[i]);
		i = LuuVet[i];
		}
		printf("<-%d\n", LuuVet[i]);
		printf("\tVoi do dai la %d\n",DoDaiDuongDiToi[F]);
		}
		else
		{
			printf("Khong co duong di tu dinh %d den dinh %d \n", S, F);
		}
}
	
void menu(Graph& g)
{
	int x;
menu:
	cout << " ______________________________________________________________________________________ " << endl;
	cout << "|                                                                                      |" << endl;
	cout << "|******************************-WELCOME TO GRAPH THEORY 2.0-***************************|" << endl;
	cout << "|                                                                                      |" << endl;
	cout << "|_______________________________________ MENU _________________________________________|" << endl;
	cout << "|                                                                                      |" << endl;
	cout << "|                       CHUONG TRINH TINH TOAN MOT SO BAI TOAN CO BAN                  |" << endl;
	cout << "|                                  1. Prim                                             |" << endl;
	cout << "|                                  2. Ford-Bellman                                     |" << endl;
	cout << "|                                  3. Ket thuc!!!!                                     |" << endl;
	cout << "|                                                                                      |" << endl;
	cout << "|              DE GIAI BAI TOAN, MOI BAN NHAN PHIM 0 DE NHAP MA TRAN                   |" << endl;
	cout << "|              NEU DA NHAP MA TRAN, MOI BAN TIEP TUC CHON THUAT TOAN CAN GIAI          |" << endl;
	cout << "|                                                                                      |" << endl;
	cout << "|______________________________________________________________________________________|" << endl;
	cout << endl;
	cin >> x;
	x:
	if (x == 0)
	{
		int chon1;
		cout << " ____________________________________NHAP MA TRAN KE __________________________________" << endl;
		cout << "|                                                                                      |" << endl;
		cout << "|                                  1. Nhap tu ban phim                                 |" << endl;
		cout << "|                                  2. Nhap tu file                                     |" << endl;
		cout << "|                                  0. Quay lai!!!!                                     |" << endl;
		cout << "|                                                                                      |" << endl;
		cout << "|______________________________________________________________________________________|" << endl;
		cout << endl;
		cin >> chon1;
		if (chon1 == 1)
		{
			nhapmatranke(g);
			docmatran(g);
			xuatmatran(g);
			int h;
			cout << "Nhap 0 den quay lai MENU ";
			cin >> h;
			if (h == 0) {
				system("cls"); 
				goto menu;
			}
		}
		if (chon1 == 2)
		{
			string ten;
			cout << "Nhap ten file: ";
			cin >> ten;
			docmatranfile(g, ten);
			xuatmatran(g);
			int h;
			cout << "Nhap 0 den quay lai MENU ";
			cin >> h;
			if (h == 0) {
				system("cls"); goto menu;
			}
		}
		if(chon1==0)
		{
			system("cls"); goto menu;
		}
	
		
	}
	if (x == 1)
	{
		if (XetLienThong == 0) cout << "Do thi khong lien thong";
		else {
			if (kiemtra != 0)
			{
				prim(g);
			}
			else cout << "Do thi da nhap khong hop le ";
			int h;
			cout << endl << "Nhap 0 de quay lai ";
			cin >> h;
			if (h == 0) {
				system("cls"); goto menu;
			}
		}
	}
	if (x == 2){
		if (XetLienThong == 0) cout << "Do thi khong lien thong";
		else {
			int S, F;
			cout << "Nhap dinh dau va dinh cuoi ";
			cin >> S >> F;
			fordbellman(S, F, g);
			int h;
			cout << endl << "Nhap 0 de quay lai ";
			cin >> h;
			if (h == 0) {
				system("cls"); goto menu;
			}
		}
	}
	if (x == 3)
	{
		exit(0);
	}
	if (x != 0 || x != 1 || x != 2 || x != 3)
	{
		cout << endl << "Lua chon khong hop le" << endl;
		int h;
		cout << endl<<"Nhap 0 de quay lai ";
		cin >> h;
		if (h == 0) { system("cls"); goto menu; }
	}
	
}
