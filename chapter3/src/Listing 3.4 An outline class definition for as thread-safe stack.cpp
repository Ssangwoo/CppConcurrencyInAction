#include <exception>
#include <memory> // for std::shared_ptr<>

struct empty_stack: std::exception
{
    const char* what() const throw();
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack&);
    // Assignment operator is deleted
	// �׸��� swap �Լ��� ���, ������ ������ �Ҵ�� �� ����
    threadsafe_stack& operator=(const threadsafe-stack&) = delete;

    void push(T new_value);
	// pop �����ε� 2��
    std::shared_ptr<T> pop();	//return std::shard_ptr<>
    void pop(T& value);			//���� reference�� ����
    bool empty() const;
};