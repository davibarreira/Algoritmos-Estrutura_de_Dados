#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
#include <chrono>
#include <iomanip>

using namespace std;


// INSERTION SORT /////////////////////////////////
template <class T>
vector <T> insertion_sort(vector <T> a){
	T cur;	
	int j;
	for (int i = 0; i < a.size(); ++i)
	{
		cur = a[i];
		j   = i - 1;
		while(j >=0 and a[j]>cur){
			a[j+1] = a[j];
            j      = j - 1;
            a[j+1] = cur;
		}
	}
    return a;
}
///////////////////////////////////////////////////


// IS_SORTED //////////////////////////////////////
template <class T>
bool is_sorted(vector <T> a){
    for (int i = 0; i < a.size()-1; ++i)
    {
        if (a[i+1] < a[i])
        {
            return false;
        }
    }
    return true;
}
///////////////////////////////////////////////////

// MERGE_SORT //////////////////////////////////////
template <class T>
vector <T> merge(vector <T> a, vector <T> b){
    vector <T> result;
    while (a.size() > 0 and b.size() > 0){
        if (a[0] < b[0])
        {
            result.push_back(a[0]);
            a.erase(a.begin());
        }
        else
        {
            result.push_back(b[0]);
            b.erase(b.begin());
        }
    }
    result.insert(result.end(), a.begin(),a.end());
    result.insert(result.end(), b.begin(),b.end());

    return result;

}

template <class T>
vector <T> merge_sort(vector <T> a){
    int m = a.size()/2;
    vector <T> left;
    vector <T> right;
    if (a.size() <= 1)
    {
        return a;
    }
    for (int i = 0; i < m; ++i){left.push_back(a[i]);}
    for (int i = m; i < a.size(); ++i){right.push_back(a[i]);}

    return merge(merge_sort(left),merge_sort(right));
}
///////////////////////////////////////////////////

// QUICKSORT /////////////////////////////////////////
template <class T>
vector <T> quicksort(vector <T> a){
    if (a.size() <= 1)
    {
        return a;
    }
    vector<T> left;
    vector<T> right;
    vector<T> equal;
    vector<T> v;

    vector<T> pivot;
    pivot.push_back(a[rand() % (a.size()-1)]);
    for (auto i: a)
    {
        if (i<pivot[0])
        {
            left.push_back(i);
        }
        if (i == pivot[0])
        {
            equal.push_back(i);
        }
        if (i>pivot[0])
        {
            right.push_back(i);
        }
    }

    left  = quicksort(left);
    right = quicksort(right);

    v.insert(v.end(), left.begin() ,left.end());
    v.insert(v.end(), equal.begin(),equal.end());
    v.insert(v.end(), right.begin(),right.end());

    return v;

}
////////////////////////////////////////////////////

// EXTRAS /////////////////////////////////////////
template <class T>
void print_vector(vector <T> a){
    for (auto i: a)
    {
        cout << i << " ";
    }
    cout << endl;
}
///////////////////////////////////////////////////


// MAIN ///////////////////////////////////////////
int	main()
{


    srand((unsigned)time(NULL));
    int r;
    int min_size = 10000; // menor tamanho do vetor

    for (int i = 0; i < 3; ++i)
    {
        ofstream out;
        if (i==0){out.open("sort_cpp_random.txt");}
        if (i==1){out.open("sort_cpp_ascend.txt");}
        if (i==2){out.open("sort_cpp_descend.txt");}

        for (int n = 1; n < 11; ++n)
        {
            vector<int> v;
            vector<int> v_sorted;

            // Gerar o vetor a depender do loop
            // i = 0 -> Loop com vetor aleatorio
            // i = 1 -> Loop com vetor ascendente
            // i = 2 -> Loop com vetor descendente

            if (i==0)
            {
                for (int i = 0; i < n*min_size; ++i)
                {
                    r = rand() % (n*min_size);
                    v.push_back(r);
                }
            }

            if (i==1)
            {
                for (int i = 0; i < n*min_size; ++i)
                {
                    v.push_back(i);
                }
            }

            if (i==2)
            {
                for (int i = n*min_size - 1; i >= 0; --i)
                {
                    v.push_back(i);
                }
            }


            auto start_time = chrono::steady_clock::now();

            v_sorted        = insertion_sort(v);

            auto end_time   = chrono::steady_clock::now();
            auto diff       = end_time - start_time;
            auto diff_msec  = chrono::duration_cast<chrono::milliseconds>(diff);

            float t1  = (float)diff_msec.count()/1000;


            if (not is_sorted(v_sorted))
            {
                cout << "ERROR" << endl;
            }

            start_time = chrono::steady_clock::now();
            v_sorted = merge_sort(v);
            end_time   = chrono::steady_clock::now();
            diff       = end_time - start_time;
            diff_msec  = chrono::duration_cast<chrono::milliseconds>(diff);
            float t2  = (float)diff_msec.count()/1000;

            if (not is_sorted(v_sorted))
            {
                cout << "ERROR" << endl;
            }


            start_time = chrono::steady_clock::now();
            v_sorted = quicksort(v);
            end_time   = chrono::steady_clock::now();
            diff       = end_time - start_time;
            diff_msec  = chrono::duration_cast<chrono::milliseconds>(diff);
            float t3  = (float)diff_msec.count()/1000;
            if (not is_sorted(v_sorted))
            {
                cout << "ERROR" << endl;
            }

            cout << setprecision(4) << fixed;
            out  << n << "," << t1 << ","<< t2 << "," << t3 <<endl; 
            cout << n << endl;

        }

        out.close();
    }

	
	return 0;
}
