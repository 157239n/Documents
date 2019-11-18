
Color& operator++(Color& col) {
    switch (col) {
        case Color::red: return col = Color::green;
        case Color::green: return col = Color::blue;
        case Color::blue: return col = Color::red;
   }
}
