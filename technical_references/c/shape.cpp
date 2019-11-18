class Shape {
public:
    virtual Point center() const = 0;
    virtual void move(Point to) = 0;

    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;

    virtual ~Shape() {}
}

void rotate_all(vector<Shape*>& v, int angle) {
    for (auto p : v)
        p->rotate(angle);
}

class Circle : public Shape {
public:
    Circle(Point p, int rr);

    Point center() const { return x; }
    void move(Point to) { x = to; }
    void draw() const;
    void rotate(int) {} // empty haha
private:
    Point x;
    int r;
}

class Smiley : public Circle {
public:
    Smiley(Point p, int r) : Circle {p, r}, mouth {nullptr} {}
    ~Smiley() {
        delete mouth;
        for (auto p : eyes)
            delete p;
    }

    void move(Point to);

    void draw() const;
    void rotate(int);

    void add_eye(Shape* s) { eyes.push_back(s); }
    void set_mouth(Shape* s);
    virtual void wink(int i);
private:
    vector<Shape*> eyes;
    Shape* mouth;
}

void Smiley::draw() {
    Circle::draw();
    for (auto p : eyes)
        p->draw();
    mouth->draw();
}

unique_ptr<Shape> read_shape(istream& is) { // this is to prevent having to return a naked pointer, which will cause memory leaks
    // read shape header from is and find its Kind k
    switch(k) {
        case Kind::circle:
            return unique_ptr<Shape> {new Circle{p, r}};
    }
}
