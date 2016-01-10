#include <list>
#include <mutex>
#include <algorithm>

class modified_example
{
private:
	std::list<int> some_list;
	std::mutex some_mutex;

public:
	void add_to_list(int new_value)
	{
		std::lock_guard<std::mutex> guard(some_mutex);	//��ȣ���� �Ǿ����� �ǹ�
		some_list.push_back(new_value);
	}
	bool list_contains(int value_to_find)
	{
		std::lock_guard<std::mutex> guard(some_mutex);	//��ȣ���� �Ǿ����� �ǹ�
		return std::find(some_list.begin(), some_list.end(), value_to_find)
			!= some_list.end();
	}
};
