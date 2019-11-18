template <typename T, int N> // this means typename has value of T, and just think of it as a variable. Also here, N is also a variable
struct Buffer {
    using value_type = T;
    constexpr int size() {return N;}
    T[N];
}