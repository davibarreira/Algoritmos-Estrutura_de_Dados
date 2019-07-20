import numpy as np
import time


def insert_sort(a):
    a = list(a)
    for i in range(len(a)):
        cur = a[i]
        j = i - 1
        while j >= 0 and a[j] > cur:
            a[j + 1] = a[j]
            j = j - 1
            a[j + 1] = cur
    return a


def merge(a, b):
    result = []
    while len(a) > 0 and len(b) > 0:
        if a[0] < b[0]:
            result.append(a[0])
            a.pop(0)
        else:
            result.append(b[0])
            b.pop(0)
    result.extend(a)
    result.extend(b)
    return result


def merge_sort(a):
    if len(a) <= 1:
        return a
    i = int(len(a) / 2)
    left = a[0:i]
    right = a[i:]
    return merge(merge_sort(left), merge_sort(right))


def quicksort(a):
    if len(a) <= 1:
        return a
    l,e,r =[],[],[]
    p = a[np.random.randint(0,len(a)-1)]
    for x in a:
        if x < p:    l.append(x)
        elif x == p: e.append(x)
        else:        r.append(x) 
            
    return quicksort(l)+e+quicksort(r)


def is_sorted(a):
    for i in range(0, len(a) - 1):
        if a[i + 1] < a[i]:
            return False
        return True


def main():
    min_size = 10000
    ns = np.linspace(min_size, min_size*10, 10)
    res = []

    for i in range(3):

        for n in ns:
            # create and fill an array with random numbers
            if i == 0:
                a = list(np.random.randint(0,n,size = int(n)))

            elif i == 1:
                a = list(np.arange(0,int(n),1))

            elif i == 2:
                a = list(np.arange(int(n),0,-1))

            # call insert_sort and  calculate the time
            start_time = time.time()
            sorted_a = insert_sort(a)
            t1 = time.time() - start_time
            if not is_sorted(sorted_a):
                print("ERROR")

            # # call merge_sort and  calculate the time
            start_time = time.time()
            sorted_a = merge_sort(a)
            t2 = time.time() - start_time
            if not is_sorted(sorted_a):
                print("ERROR")

            # # call quicksort and  calculate the time
            start_time = time.time()
            sorted_a = quicksort(a)
            t3 = time.time() - start_time
            if not is_sorted(sorted_a):
                print("ERROR")

            # print("%d %f %f" % (n, t2, t3))
            print("%d %f %f %f" % (n, t1, t2, t3))
            res.append([n,t1,t2,t3])

        if i == 0:
            with open('sort_python_random.txt', 'w') as f:
                f.write(repr(res))  

        elif i == 1:
            with open('sort_python_ascend.txt', 'w') as f:
                f.write(repr(res))  

        elif i == 2:
            with open('sort_python_descend.txt', 'w') as f:
                f.write(repr(res))  

if __name__ == "__main__":
    main()
