#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

std::string range;

long long Tran(int a, int b)
{
	std::string t_side = range.substr(a,b);
	long long side = std::stoi(t_side);
	return side;
}

int main()
{
	//part
	LOG("type in the range\nexample:2,100 means [2,100]");
	LOG("Range is required and you can ONLY use \",\" in English");
	long long left=0 ,right = 0 ,length = 0;
	int i = 0, x = 0;
	std::cin >> range;
	length = range.length() - 1;//begin from 0
	while (i <= length)
	{
		if (range[i] == ',')
		{
			x = i;
			break;
		}
		else i++;
	}
	right = Tran(i + 1,length - i);
	left = Tran(0, i);
	if (left > right || left < 2)
	{
		LOG("Maths or logic error.");
		main();
	}

	//enum
	LOG("START\n");
	for (long long j = left; j <= right; j++)
	{
		bool condition = true;
		for (long long k = 2; k < j - 1; k++)
		{
			if (j % k == 0)
			{
				condition = false;
				break;
			}
		}
		if (condition) LOG(j);
	}
	LOG("\nCOMPLETED");
	main();
}