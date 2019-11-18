// type names and templates here, they're pretty messed up, so don't believe them much.

template<typename T>
class Vector {
public:
    explicit Vector(int s) :elem {new double[s]}, sz {s}; // explicit means Vector v = 1 will raise an error
    Vector(std::initializer_list<double>);
    double& operator[] (int i) {return elem[i];}
    int size() {return sz;}
    ~Vector() {delete[] elem;} // destructor
    Vector operator + (const Vector& a, const Vector& b) {
        if (a.size() != b.size())
            throw Vector_size_mismatch{};

        Vector res(a.size());
        for (int i = 0; i != a.size(); ++i) {
            res[i] = a[i] + b[i];
        }
        return res;
    }

    Vector(const Vector& a); // copy constructor
    Vector& operator = (const Vector& a); // copy assignment

    Vector(Vector&& a); // move constructor. Compiler sees this, and will move the innards of Vector to the outside scope and not copying it. As I understand it, only the system use this, not another programmer/function.
    Vector& operator = (Vector&& a); // move assignment. Also Vector&& meaning rvalue reference. Lvalue references can be assigned to, but not this. I don't get the point tho, like why would you want this?
private:
    double* elem;
    int sz;
}

template<typename T>
Vector::Vector(std::initializer_list<double> lst) : elem {new double[lst.size()]}, sz {static_cast<int>(lst.size())} {
    copy(lst.begin(), lst.end(), elem);
}

template<typename T>
Vector<T>::Vector(const Vector<T>& a) : elem {new double[a.sz]}, sz {a.sz} { // copy constructor
    for (int i = 0; i != sz; ++i)
        elem[i] = a.elem[i];
}

template<typename T>
Vector::Vector& operator = (const Vector& a) { // copy assignment
    T* p = new T[a.sz];
    for (int i = 0; i != a.sz; ++i)
        p[i] = a.elem[i];
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}

template<typename T>
Vector<T>::Vector(Vector&& a) : elem {a.elem}, sz {a.sz} {
    a.elem = nullptr;
    a.sz = 0;
}

class Container {
public:
    virtual double& operator[](int) = 0; // pure virtual function
    virtual int size() const = 0; // const member function
    virtual ~Container() {} // destructor
}

// "virtual" means may be redefined later in a class derived from this one. Think "abstract" in java
// "=0" meaning it's pure virtual, meaning derived class must define the function

class Vector_container : public Container {
    Vector v;
public:
    Vector_container(int s) : v(s) {}
    ~Vector_container() {}

    double& operator[](int i) {return v[i];}
    int size() const {return v.size();}
}

class List_container : public Container {
    std::list<double> ld; // list of doubles
public:
    List_container() {}
    List_container(initializer_list<double> il) : ld {il} {}
    ~List_container() {}

    double& operator[](int i);
    int size() const {return ld.size();}
};

double& List_container::operator[](int i) {
    for (auto& x : ld) {
        if (i == 0) return x;
        --i;
    }
    throw out_of_range("List container");
}

Vector read(istream& is) {
    Vector v;
    for (double d; is >> d) { // terminates loop when stream have a format error, or end of file. d's scope is limited to the loop
        v.push_back(d);
    }
    return v;
}

void use(Container& c) {
    const int sz = c.size();

    for (int i = 0; i != sz; ++i) {
        cout << c[i] << "\n";
    }
}

void use1() {
    Vector v(6);
}



