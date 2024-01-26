//Vector, More

#include <iostream>
#include <vector>

class Cat
{
public:
    Cat() { std::cout << "Cat created\n"; }
    Cat(const int id) {

        m_id = id;
        std::cout << m_id << " Cat created with id\n";
    }
    Cat(const Cat& rhs) {

        m_id = rhs.m_id;
        std::cout << m_id << " Cat created by copying\n";
    }


    Cat(Cat&& rhs) noexcept {

        m_id = rhs.m_id;
        std::cout << m_id << " Cat created by moving\n";
    }

    ~Cat()
    {
        static int cnt;
        std::cout << m_id << " Cat destroyed " << ++cnt << " is Total. \n";
    }

    void Speak() const { std::cout << m_id << "  Meow\n"; }

    // assignment operators
    Cat& operator=(const Cat& rhs) { m_id = rhs.m_id; std::cout << m_id << " Cat assigned by copying\n"; return *this; }
    Cat& operator=(Cat&& rhs) noexcept { m_id = rhs.m_id;  std::cout << m_id << " Cat assigned by moving\n"; return *this; }


private:

    int m_id = 0;
};


void Test_Reserve()
{
    // 결과를 예상해 봅시다.  
    std::vector<Cat> v;
    v.reserve(3);
    //v.reserve(6);

    //v[0] = Cat(1); //가능할까요 ?

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(400);
    v.push_back(500);
    v.push_back(600);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    for (const auto& cat : v)
    {
        cat.Speak();
    }

    std::cout << "\n --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n ";
}

void Test_Resize()
{
    // 결과를 예상해 봅시다.  
    std::vector<Cat> v;
    v.resize(3);
    //v.resize(6);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    v.push_back(400);
    v.push_back(500);
    v.push_back(600);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    for (const auto& cat : v)
    {
        cat.Speak();
    }

    std::cout << "\n --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n ";
}

void Test_Resize_2()
{
    // 결과를 예상해 봅시다.  
    std::vector<Cat> v;
    v.resize(3);
    //v.resize(6);

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    for (int i = 0; i < 3; ++i)
    {
        v[i] = Cat(100 * (i + 1));
    }

    std::cout << " \n capacity: " << v.capacity() << " size : " << v.size() << " \n  \n";

    //v[3] = Cat(100 * (i + 1)); 가능할까요?

    for (const auto& cat : v)
    {
        cat.Speak();
    }

    std::cout << "\n --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- \n ";
}

template <typename T>
class CustomAllocator : public std::allocator<T>
{
public:
    using value_type = T;

    // 기본 생성자
    CustomAllocator() noexcept = default;

    // 복사 생성자
    template <typename U>
    constexpr CustomAllocator(const CustomAllocator<U>&) noexcept {}

    // 할당
    [[nodiscard]] T* allocate(std::size_t n) {
        std::cout << "CustomAllocator: allocate " << n << " elements\n";
        return std::allocator<T>::allocate(n);
    }

    // 해제
    void deallocate(T* p, std::size_t n) {
        std::cout << "CustomAllocator: deallocate " << n << " elements\n";
        std::allocator<T>::deallocate(p, n);
    }
};

int main()
{
    std::vector<int> a;
    std::vector<Cat, CustomAllocator<Cat>> vec;

    vec.push_back(Cat(100));

    system("pause");

    return 0;
}