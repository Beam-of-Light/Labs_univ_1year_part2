#include "pch.h"
#include "date_time.h"
#include "algorithms.h"

void demo();
void benchmark();
void benchmark_sort(std::vector<date_time> arr, std::ofstream& fout, const size_t& sort_kind);

int main()
{
	//std::vector<date_time> a;
	//a.reserve(40);
	//a.resize(29);
	//a.push_back(date_time(1000, April, 12, 22, 40));
	//a.push_back(date_time());
	//a.push_back(date_time());
	//a.push_back(date_time());
	//a.push_back(date_time());
	//a.push_back(date_time(1000, April, 12, 22, 40));
	//a.push_back(date_time());
	//a.push_back(date_time());
	//a.push_back(date_time());
	//a.push_back(date_time());
	//a.push_back(date_time(1000, April, 12, 22, 40));
	//date_time* p = &a[0];

	//bubble_sort (a, 0, 10);
	//merge_sort(p, 11);
	//quick_sort (a, 0, 10);
	//combined_sort(a, 0, 39);
	
	try
	{
		srand(time(NULL));
		size_t number;
		while (true)
		{
			std::cout << "Write number 1-2:\n1 - Demo\n2 - Benchmark\n";
			write_num(number);

			if (number == 1) demo();
			else if (number == 2) benchmark();
			else
			{
				std::cout << "\n\nWrong input, please enter a number again: ";
				continue;
			}
			break;
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}

void demo()
{
}

void benchmark()
{
	std::ofstream fout;	/* file for result */
	fout.open("benchmark_result.txt");
	if (!fout.is_open()) { throw std::exception("File isn't open"); }

	std::vector<date_time> test;
	test.resize(10000);

	fout << "------------------ Random array ------------------\n\nBubble sort:\n";
	benchmark_sort(test, fout, Bubble);
	fout << "\nQuick sort:\n";
	benchmark_sort(test, fout, Quick);
	fout << "\nMerge sort:\n";
	benchmark_sort(test, fout, Merge);
	fout << "\nCombined sort(Quick & Bubble):\n";
	benchmark_sort(test, fout, Combined);


	test.clear();
	test.reserve(10000);
	for (size_t i = 0; i < 10000; i++)
	{
		test.push_back(date_time(i / 2, i % 12 + 1, rand() % 28 + 1, rand() % 24, rand() % 60));
	}
	swap(test[120], test[500]);

	fout << "------------------ Almost not sorted array ------------------\n\nBubble sort:\n";
	benchmark_sort(test, fout, Bubble);
	fout << "\nQuick sort:\n";
	benchmark_sort(test, fout, Quick);
	fout << "\nMerge sort:\n";
	benchmark_sort(test, fout, Merge);
	fout << "\nCombined sort(Quick & Bubble):\n";
	benchmark_sort(test, fout, Combined);

	for (size_t i = 0; i < 5000; i++)
	{
		swap(test[i], test[10000 - i - 1]);
	}
	

	fout << "------------------ Almost sorted array ------------------\n\nBubble sort:\n";
	benchmark_sort(test, fout, Bubble);
	fout << "\nQuick sort:\n";
	benchmark_sort(test, fout, Quick);
	fout << "\nMerge sort:\n";
	benchmark_sort(test, fout, Merge);
	fout << "\nCombined sort(Quick & Bubble):\n";
	benchmark_sort(test, fout, Combined);

	fout.close();
	std::cout << "\nBenchmark is complited\n";
}


void benchmark_sort(std::vector<date_time> arr, std::ofstream& fout, const size_t& sort_kind)
{
	simple_timer t; /* check start */
	switch (sort_kind)
	{
	case Bubble:
		bubble_sort(arr, 10000);
		break;
	case Quick:
		quick_sort(arr, 0, 9999);
		break;
	case Merge:
		merge_sort(&arr[0], 10000);
		break;
	case Combined:
		combined_sort(arr, 0, 9999);
		break;
	}
	double check_time = t.get_duration(); /* check finish */

	fout << "For " << 10000 << " elements:\tTime - " << check_time << std::endl;
}
