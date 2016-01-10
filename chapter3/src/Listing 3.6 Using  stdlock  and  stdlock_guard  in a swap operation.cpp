#include <mutex>

class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);

class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const& sd) :some_detail(sd) {}

	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs)
			return;
		std::lock(lhs.m, rhs.m); // lhs�� rhs�� ���� ������ �ִ� mutex�� lock�� ��
		//lhs.m�� lock�� �ɾ�����, rhs.m�� lock�� ������ �� ������ ����ó�� ��.
		//std::lock�� all-or-nothing semantics��
		//http://en.cppreference.com/w/cpp/thread/lock

		// make sure both already-locked mutexes are unlocked at the end of scope 
		//std::adopt_lock http://www.cplusplus.com/reference/mutex/adopt_lock/, http://en.cppreference.com/w/cpp/thread/lock_tag
		//The value is a compile - time constant that carries no state, and is merely used to disambiguate between constructor signatures.
		//
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // �ν��Ͻ� ����
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); // �ν��Ͻ� ����

		swap(lhs.some_detail, rhs.some_detail);
	}
};