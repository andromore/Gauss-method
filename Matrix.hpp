class Matrix
{
    private:
    double* pointer;
    int rows;
    int columns;
    public:
    Matrix(int rows, int columns);
    Matrix(const Matrix& matrix);
    ~Matrix(void);
    double get_element(int rows, int columns) const;
    int get_rows(void) const;
    int get_columns(void) const;
    void set_element(int rows, int columns, double value);
    void set_row(int row, double value);
    void set_column(int column, double value);
    void set_all(double value);
    void print_matrix(void) const;
    void transparent_matrix(void);
    void swap_elements(int row1, int column1, int row2, int column2);
    void swap_rows(int row1, int row2);
    void swap_columns(int column1, int column2);
    void multiply_row(int row, double multiplier);
    void multiply_column(int column, double multiplier);
    void multiply_matrix(double multiplier);
    void add_row_to_row(int row1, int row2);
    void add_row_to_row(int row1, int row2, double multiplier);
    void add_column_to_column(int column1, int column2);
    void add_column_to_column(int column1, int column2, double multiplier);
    void add_matrix(const Matrix& summand);
};