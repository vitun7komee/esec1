#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Функция создания матрицы с заданным количеством столбцов
vector<vector<char>> createMatrix(const string& text, int cols) {
    int rows = (text.length() + cols - 1) / cols; // Рассчитываем необходимое количество строк
    vector<vector<char>> matrix(rows, vector<char>(cols, '_')); // Заполняем пустые ячейки '_'
    int idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (idx < text.length()) {
                matrix[i][j] = text[idx++];
            }
        }
    }
    return matrix;
}

// Перестановка строк в матрице по ключу
vector<vector<char>> transposeRows(const vector<vector<char>>& matrix, const vector<int>& key) {
    vector<vector<char>> transposedMatrix(matrix.size(), vector<char>(matrix[0].size()));
    for (int i = 0; i < key.size(); i++) {
        transposedMatrix[i] = matrix[key[i] - 1];
    }
    return transposedMatrix;
}

// Перестановка столбцов в матрице по ключу
vector<vector<char>> transposeColumns(const vector<vector<char>>& matrix, const vector<int>& key) {
    vector<vector<char>> transposedMatrix(matrix.size(), vector<char>(matrix[0].size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < key.size(); j++) {
            transposedMatrix[i][j] = matrix[i][key[j] - 1];
        }
    }
    return transposedMatrix;
}

// Функция шифрования по двойной перестановке
string encrypt(const string& text, const vector<int>& k1, const vector<int>& k2) {
    int cols = k1.size();
    vector<vector<char>> matrix = createMatrix(text, cols);
    vector<vector<char>> rowTransposed = transposeRows(matrix, k1);
    vector<vector<char>> colTransposed = transposeColumns(rowTransposed, k2);
    string encryptedText;
    for (const auto& row : colTransposed) {
        for (char c : row) {
            encryptedText += c;
        }
    }
    return encryptedText;
}

// Функция расшифровки по двойной перестановке
string decrypt(const string& encryptedText, const vector<int>& k1, const vector<int>& k2) {
    int cols = k1.size();
    int rows = encryptedText.length() / cols;
    vector<vector<char>> matrix = createMatrix(encryptedText, cols);

    // Обратная перестановка столбцов
    vector<int> invK2(k2.size());
    for (int i = 0; i < k2.size(); i++) invK2[k2[i] - 1] = i + 1;
    vector<vector<char>> colTransposed = transposeColumns(matrix, invK2);

    // Обратная перестановка строк
    vector<int> invK1(k1.size());
    for (int i = 0; i < k1.size(); i++) invK1[k1[i] - 1] = i + 1;
    vector<vector<char>> rowTransposed = transposeRows(colTransposed, invK1);

    // Формирование расшифрованного текста
    string decryptedText;
    for (const auto& row : rowTransposed) {
        for (char c : row) {
            if (c != '_') decryptedText += c;
        }
    }
    return decryptedText;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string openText = "ШИФРОВАНИЕ_ПЕРЕСТАНОВКОЙ";
    vector<int> k1 = { 3, 1, 2, 5, 4 };
    vector<int> k2 = { 4, 5, 2, 1, 3 };

    string encryptedText = encrypt(openText, k1, k2);
    string decryptedText = decrypt(encryptedText, k1, k2);

    cout << "Открытый текст: " << openText << endl;
    cout << "Зашифрованный текст: " << encryptedText << endl;
    cout << "Расшифрованный текст: " << decryptedText << endl;

    return 0;
}
