#include <iostream>
using namespace std;
class BankerAlgo
{
public:
    int ProcessNo;
    int *Max;
    int *Allocated;
    int *Need;
    int *CurrentAvailable;
    bool flag;

    BankerAlgo() {
        flag=false;
    }
    void init(int i,int AR);
};
void BankerAlgo::init(int i,int AR)
{
    ProcessNo=i;
    Allocated=new int[AR];
    for (int i = 0; i < AR; ++i) {
        Allocated[i]=0;
    }
    Max= new int[AR];
    for (int i = 0; i < AR; ++i) {
        Max[i]=0;
    }
    Need=new int[AR];
    for (int i = 0; i < AR; ++i) {
        Need[i]=0;
    }
    CurrentAvailable=new int[AR];
    for (int i = 0; i < AR; ++i) {
        CurrentAvailable[i]=0;
    }
}
BankerAlgo Values(BankerAlgo P[],int P1,int A)
{
    for (int i = 0; i < P1; ++i) {
        cout<<endl;
        cout<<"Enter Allocated Values of P["<<i<<"] : " <<endl;
        cout<<endl;
        for (int j = 0; j < A; ++j) {
            cout<<"Enter Allocate Value of A["<<j<<"] : ";
            cin>>P[i].Allocated[j];
            cout<<endl;
        }
        cout<<endl;
    }
    for (int i = 0; i < P1; ++i) {
        cout<<endl;
        cout<<"Enter Max Values of P["<<i<<"] : " <<endl;
        cout<<endl;
        for (int j = 0; j < A; ++j) {
            cout<<"Enter Max Value of M["<<j<<"] : ";
            cin>>P[i].Max[j];
            cout<<endl;
        }
        cout<<endl;
    }
    return *P;
}

BankerAlgo Print(BankerAlgo P[],int P1,int A) {
    cout<<endl;
    cout << "Process No " << "         " << "Allocated Resources" << "         "<< "Max Resources" <<"          "<<"Need"<<"             "<<"CurrentAvailable"<< endl;
    for (int i = 0; i < P1; ++i) {
        cout << P[i].ProcessNo << "                      ";
        for (int j = 0; j < A; ++j) {
            cout << P[i].Allocated[j] << " ";
        }
        cout<<"                    ";
        for (int x = 0; x < A; ++x) {
            cout << P[i].Max[x] << " ";
        }
        cout <<"              ";
        for (int z = 0; z < A; ++z) {
            cout << P[i].Need[z] << " ";
        }
        cout <<"              ";
        if(i==0) {
            for (int j = 0; j < A; ++j) {
                cout << P[i].CurrentAvailable[j] << " ";
            }
        }
        cout<<endl;
    }
    return *P;
}
BankerAlgo Need(BankerAlgo P[],int P1,int A)
{
    int N=0;
    for (int i = 0; i < P1; ++i) {
        for (int j = 0; j < A; ++j) {
            P[i].Need[j]=P[i].Max[j]-P[i].Allocated[j];
        }
    }
   return *P;
}
BankerAlgo Available(BankerAlgo P[],int A)
{
    for (int i = 0; i < 1; ++i) {
        cout<<"Enter Available Resources : "<<endl;
        for (int j = 0; j < A; ++j) {
            cout<<"Enter Value of Available Resource A["<<j<<"] : ";
            cin>>P[i].CurrentAvailable[j];
        }
    }
    return *P;
}
int Process(BankerAlgo *P, int P1, int A)
{
    int count=0,RP=0,N=0;
    for (int i = 0; i < P1; ++i) {
        if (!P[i].flag) {
            for (int j = 0; j < A; ++j) {
                if(P[N].CurrentAvailable[j]>=P[i].Need[j])
                {
                    RP=i;
                    count++;
                }
                else
                {
                    break;
                }
            }
        }
        if(count==A)
        {
            break;
        }
        else
        {
            count=0;
        }
    }
    return RP;
}
BankerAlgo Sequence(BankerAlgo P[],int P1,int A)
{
    bool flag= false;
    int Release=0,Pre_balance=0,Sequence[A],CA[A],FinalAva[A],N=0;
    int count=0,Pr=0;
        for (int i = 0; i < A; ++i) {
            FinalAva[i] = 0;
        }
        for (int i = 0; i < P1; ++i) {
            for (int j = 0; j < A; ++j) {
                FinalAva[j] = FinalAva[j] + P[i].Allocated[j];
            }
        }
        for (int i = 0; i < A; ++i) {
            FinalAva[i] = FinalAva[i] + P[count].CurrentAvailable[i];
        }
        for (int i = 0; i < P1; ++i) {
            Pr = Process(P, P1, A);
            Sequence[i] = Pr;
            P[Pr].flag = true;
            for (int j = 0; j < A; ++j) {
                Release = P[Pr].Allocated[j] + P[Pr].Need[j];
                Pre_balance = P[count].CurrentAvailable[j] - P[Pr].Need[j];
                CA[j] = Release + Pre_balance;
                P[count].CurrentAvailable[j] = CA[j];

            }
        }
        for (int i = 0; i < A; ++i) {
            if (FinalAva[i] == P[count].CurrentAvailable[i]) {
                flag = true;
            } else {
                flag = false;
                break;
            }
        }
        cout << endl;
        if (flag == true) {
            cout << "Your Safe Sequence is : " << endl;
            for (int i = 0; i < P1; ++i) {
                cout << "P[" << Sequence[i] << "]" << " ";
            }
        } else {
            cout << "No Safe Sequence" << endl;
        }
        cout << endl;
      //  Print(P,P1,A);
    return *P;
}
int main() {
    int P,AR,MR,Available1;
    cout<<"Enter Number of Processes: ";
    cin>>P;
    cout<<"Enter Number of Allocated Resources: ";
    cin>>AR;
    cout<<"Enter Number of Max Resources: ";
    cin>>MR;
    cout<<"Enter Number of Available Resources: ";
    cin>>Available1;
    BankerAlgo B[P];
    for (int i = 0; i < P; ++i) {
        B[i].init(i,AR);
    }
    Available(B,Available1);
    Values(B,P,AR);
    Need(B,P,AR);
    Print(B,P,AR);
    Sequence(B,P,AR);
    Print(B,P,AR);

    return 0;
}