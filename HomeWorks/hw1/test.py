import numpy as np


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


def merge_sort(a):
    pass


def quicksort(a):
    pass


def is_sorted(a):
    for i in range(0, len(a) - 1):
        if a[i + 1] < a[i]:
            return False
        return True


def main():
    ns = np.linspace(10000, 100000, 10)

    for n in ns:
        # create and fill an array with random numbers
        a = [3, 4, 6, 1, 5, 2]

        # call insert_sort and  calculate the time
        sorted_a = insert_sort(a)
        if not is_sorted(sorted_a):
            print("ERROR")

        # # call merge_sort and  calculate the time
        # sorted_a = merge_sort(a)
        # if not is_sorted(sorted_a):
        #     print("ERROR")

        # # call quicksort and  calculate the time
        # sorted_a = quicksort(a)
        # if not is_sorted(sorted_a):
        #     print("ERROR")

        # print("%d %f %f" % (n, t1, t2, t3))


if __name__ == "__main__":
    main()
