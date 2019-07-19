# include <iostream>
# include <vector>

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
    vector<float> a;
    a = {0,3,2,1};
    vector<float> v_insertsort;
    vector<float> v_mergesort;

    v_insertsort = insertion_sort(a);
    v_mergesort  = merge_sort(a);

    print_vector(a);
    print_vector(v_mergesort);
    print_vector(v_insertsort);
    cout << is_sorted(a) << endl;
    cout << is_sorted(v_insertsort) << endl;


	
	return 0;
}
