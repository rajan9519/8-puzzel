// ordered priority queue using binary heap
// array index start from 1

#include <bits/stdc++.h>
using namespace std;

class board
{
public:
    int arr[3][3],manhattan;
    int dist(int arr[3][3])
    {
        int sum = 0;
        int ans[3][3] = {{1,2,3},
                         {4,5,6},
                         {7,8,0}};

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(arr[i][j]==1)
                {
                    sum+=(i+j);
                }
                else if(arr[i][j]==2)
                {
                    sum+=(i+abs(j-1));
                }
                else if(arr[i][j]==3)
                {
                    sum+=(i+abs(j-2));
                }
                else if(arr[i][j]==4)
                {
                    sum+=(abs(i-1)+j);
                }
                else if(arr[i][j]==5)
                {
                    sum+=(abs(i-1)+abs(j-1));
                }
                else if(arr[i][j]==6)
                {
                    sum+=(abs(i-1)+abs(j-2));
                }
                else if(arr[i][j]==7)
                {
                    sum+=(abs(i-2)+j);
                }
                else if(arr[i][j]==8)
                {
                    sum+=(abs(i-2)+abs(j-1));
                }
            }
        }
        return sum;
    }
    board()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j]=0;
            }
        }
        manhattan = 0;
    }
    board(int arr1[3][3])
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j]=arr1[i][j];
            }
        }
        manhattan = dist(arr1);
    }
    bool operator==(const board& that)
    {
        if(manhattan == that.manhattan)
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    if(arr[i][j] != that.arr[i][j])
                        return false;
                }
            }
            return true;
        }
        return false;
    }
    // custom assignment operator
    board & operator=(const board& that)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j]=that.arr[i][j];
            }
        }
        manhattan = that.manhattan;
        return *this;
    }
    // custom copy constructor
    board(board & that)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                arr[i][j]=that.arr[i][j];
            }
        }
        manhattan = that.manhattan;
    }
    void print()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                cout<<arr[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
};

template<class T,class compare>
class ordered_pq
{
private:
    T* key;
    int capacity;
    void exch(int i,int j);
    void increase();
    void swim(int k); // child key become larger than its parents key
    void sink(int k); // parents key become smaller than one or both of its children
                      // exchange that key with the max of children
public:
    int N;
    ordered_pq();
    ordered_pq(int length);
    bool isEmpty();
    void insert(T item); // insert item at the end and swim it up
    T delMin();
    void print();
};

template<class T,class compare>
void ordered_pq<T,compare>::sink(int k)
{
    compare cmp;
    while(2*k <= N)
    {
        int j = 2*k;
        if(j < N && cmp(key[j],key[j+1]))
            j++;
        if(cmp(key[k],key[j]))
            exch(k,j);
        else
            break;
        k = j;
    }
}
template<class T,class compare>
void ordered_pq<T,compare>::swim(int k)
{
    compare cmp;
    while(k>1 && cmp(key[k/2],key[k]))
    {
        exch(k,k/2);
        k = k/2;
    }
}

template<class T,class compare>
ordered_pq<T,compare>::ordered_pq()
{
    capacity = 2;
    N=0;
    key = new T[capacity+1];
}

template<class T,class compare>
ordered_pq<T,compare>::ordered_pq(int length)
{
    capacity = length;
    N=0;
    key = new T[capacity+1];
}

template<class T,class compare>
void ordered_pq<T,compare>::exch(int i,int j)
{
    T temp = key[i];
    key[i] = key[j];
    key[j] = temp;
}

template<class T,class compare>
bool ordered_pq<T,compare>::isEmpty()
{
    if(N)
        return false;
    return true;
}

template<class T,class compare>
void ordered_pq<T,compare>::insert(T item)
{
    if(N == capacity)
        increase();
    key[++N] = item;
    swim(N);
}

template<class T,class compare>
T ordered_pq<T,compare>::delMin()
{
    exch(1,N--);
    sink(1);
    return key[N+1];
}

template<class T,class compare>
void ordered_pq<T,compare>::increase()
{
    capacity *= 2;
    T* newkey = new T[capacity+1];
    for(int i=1;i<=N;i++)
    {
        newkey[i] = key[i];
    }
    delete[] key;
    key = newkey;
}

// container will contain an array of board which will be in ascending order
// in which the indexes should be moved
class container
{
public:
    container();
    board* store;
    int priority,N,capacity,moves,manhattan;
    void insert(board b);
    board get();
    void increase();
    void print();
    void remove();


    // custom assignment operator
    container & operator=(const container& that)
    {
        priority = that.priority;
        moves = that.moves;
        manhattan = that.manhattan;
        N = that.N;
        capacity = that.capacity;
        store = new board[capacity+1];
        for(int i=0;i<N;i++)
        {
            store[i] = that.store[i];
        }
        return *this;
    }
    // custom copy constructor
    container(container & that)
    {
        priority = that.priority;
        moves = that.moves;
        manhattan = that.manhattan;
        N = that.N;
        capacity = that.capacity;
        store = new board[capacity+1];
        for(int i=0;i<N;i++)
        {
            store[i] = that.store[i];
        }
    }
};
container::container()
{
    priority = INT_MAX;
    moves = 0;
    manhattan = INT_MAX;
    capacity = 2;
    N = 0;
    store = new board[capacity+1];
}
void container::increase()
{
    capacity = capacity*2;
    board* temp = new board[capacity+1];
    for(int i=0;i<N;i++)
    {
        temp[i] = store[i];
    }
    delete[] store;
    store = temp;
}
void container::insert(board b)
{
    if(N>=capacity)
        increase();
    store[N++] = b;
    moves++;
    manhattan = b.manhattan;
    priority = moves+manhattan;
}
board container::get()
{
    return store[N-1];
}
void container::print()
{
    for(int i=0;i<N;i++)
    {
        store[i].print();
        cout<<"\n";
    }
}
void container::remove()
{
    moves--;
    manhattan = store[--N].manhattan;
    priority = moves+manhattan;
}

class comp1
{
  public:
      bool operator() (container* c1,container* c2)
        {
            if(c1->priority>c2->priority)
            {
                return true;
            }
            if(c1->priority<c2->priority)
            {
                return false;
            }
            return c1->manhattan>c2->manhattan;
        }
};

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("output.txt","w",stdout);
    ordered_pq<container*,comp1> game;
    int arr[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>arr[i][j];
        }
    }
    container* cont = new container;
    board b1(arr);
    cont->insert(b1);
    game.insert(cont);
    while(b1.manhattan)
    {
        cont = game.delMin();
        while(!game.isEmpty())
        {
            container* cont2 = game.delMin();
            if(!(cont2->get() == cont->get()))
            {
                game.insert(cont2);
                break;
            }
        }
        b1 = cont->get();
        int k,l;
        bool flag=false;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(b1.arr[i][j] == 0)
                {
                    k=i;
                    l=j;
                    flag=true;
                    break;
                }
            }
            if(flag)
                break;
        }
        if(k-1 >= 0)
        {
            container* cont1 = new container((*cont));
            b1.arr[k][l] = b1.arr[k-1][l];
            b1.arr[k-1][l] = 0;
            board temp(b1.arr);
            cont1->insert(temp);
            game.insert(cont1);
            b1.arr[k-1][l] = b1.arr[k][l];
            b1.arr[k][l] = 0;
        }
        if(k+1 <= 2)
        {
            container* cont1 = new container((*cont));
            b1.arr[k][l] = b1.arr[k+1][l];
            b1.arr[k+1][l] = 0;
            board temp(b1.arr);
            cont1->insert(temp);
            game.insert(cont1);
            b1.arr[k+1][l] = b1.arr[k][l];
            b1.arr[k][l] = 0;
        }
        if(l-1 >= 0)
        {
            container* cont1 = new container((*cont));
            b1.arr[k][l] = b1.arr[k][l-1];
            b1.arr[k][l-1] = 0;
            board temp(b1.arr);
            cont1->insert(temp);
            game.insert(cont1);
            b1.arr[k][l-1] = b1.arr[k][l];
            b1.arr[k][l] = 0;
        }
        if(l+1 <= 2)
        {
            container* cont1 = new container((*cont));
            b1.arr[k][l] = b1.arr[k][l+1];
            b1.arr[k][l+1] = 0;
            board temp(b1.arr);
            cont1->insert(temp);
            game.insert(cont1);
            b1.arr[k][l+1] = b1.arr[k][l];
            b1.arr[k][l] = 0;
        }

    }
    cout<<"ANS\n";
    cout<<game.N<<"\n";
    cout<<"priority = "<<cont->priority<<", manhattan = "<<cont->manhattan<<", moves ="<<cont->moves<<"\n";
    cont->print();
    return 0;
}
