#ifndef ALGORITHMS
#define ALGORITHMS

enum { Bubble, Quick, Merge, Combined };

template<class T>
inline void swap(T& x, T& y)
{
	T t = x;
	x = y;
	y = t;
}

template<class T>
size_t partition(std::vector<T>& arr, const int& left, const int& right)
{
	size_t mid = left + (right - left) / 2;
	if (arr[left] < arr[mid])
		swap(arr[left], arr[mid]);

	if (arr[right] > arr[left])
		swap(arr[right], arr[left]);

	if (arr[right] > arr[mid])
		swap(arr[right], arr[mid]);

	T pivot = arr[mid];
	int i = left, j = right;
	while (true)
	{
		do
		{
			++i;
		} while (arr[i] > pivot);
		do
		{
			--j;
		} while (arr[j] < pivot);

		if (i >= j) return j;
		swap(arr[i], arr[j]);
	}
}

template<class T>
void quick_sort(std::vector<T>& arr, const int& left, const int& right)
{
	if (left < right)
	{
		int pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot);
		quick_sort(arr, pivot + 1, right);
	}
}

template<class T>
void bubble_sort(std::vector<T>& arr, const size_t& left, const size_t& right)
{
	bool swaped;
	size_t i = left;

	while (true)
	{
		i++;
		swaped = false;

		for (size_t j = right; i <= j; --j)
		{
			if (arr[j - 1] < arr[j])
			{
				swap(arr[j - 1], arr[j]);
				swaped = true;
			}
		}
		if (!swaped) return;
	}
}



template<class T>
void bubble_sort(std::vector<T>& arr, const size_t& size)
{
	bool swaped;
	size_t i = 0;

	while (true)
	{
		i++;
		swaped = false;

		for (size_t j = size - 1 ; i <= j; --j)
		{
			if (arr[j - 1] < arr[j])
			{
				swap (arr[j - 1], arr[j]);
				swaped = true;
			}
		}
		if (!swaped) return;
	}
}



template<class T>
void merge_sort(T* ptr_arr, const size_t& size)
{
	if (size > 1)
	{
		size_t i = size / 2;
		merge_sort(ptr_arr, i);
		merge_sort(ptr_arr + i, size - i);
		merge(ptr_arr, i, size);
	};
}

//template<class T>
//void merge_sort(std::vector<T>& arr, const size_t& left, const size_t& right)
//{
//	size_t size = right - left + 1;
//	if (size > 1)
//	{
//		size_t i = size / 2;
//		merge_sort(&arr[0], i);
//		merge_sort(&arr[0] + i, size - i);
//		merge(&arr[0], i, size);
//	};
//}

template<class T>
void merge(T* ptr_arr, const size_t& partition, const size_t& size)
{
	T* pa = new T[size];
	for (size_t i = 0; i < size; i++)
	{ pa[i] = ptr_arr[i]; }
	
	size_t i = 0, j = 0, k = partition;
	for (; i < size && j < partition && k < size; i++)
	{ 
		ptr_arr[i] = (pa[j] > pa[k] ? pa[j++] : pa[k++]);
	}

	while (j < partition)
	{ ptr_arr[i++] = pa[j++]; }
	
	while (k < size)
	{ ptr_arr[i++] = pa[k++]; }

	delete[] pa;
}

template<class T>
void combined_sort(std::vector<T>& arr, const int& left, const int& right)
{
	if (left < right)
	{
		if (right - left <= 10) 
		{
			bubble_sort(arr, left, right);
			return;
		}

		int pivot = partition(arr, left, right);
		combined_sort(arr, left, pivot);
		combined_sort(arr, pivot + 1, right);
	}
}

#endif /* ALGORITHMS */