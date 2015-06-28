#ifndef MATRIX_H
#define MATRIX_H

#include <QList>
#include <QSize>
#include <QPoint>

template<typename ValueType>
class Matrix
{
public:
    Matrix();
    Matrix(int width, int height, const ValueType& default_value = ValueType());
    explicit Matrix(const QSize& size,const ValueType& default_value = ValueType());

    int width() const;
    int height() const;
    QSize size() const;

    const ValueType& at(int i, int j) const;
    const ValueType& at(const QPoint& point) const;
    const QList<ValueType>& operator[](int i) const;
    QList<ValueType>& operator[](int i);

private:
    QList<QList<ValueType> > m_matrix;
};

////////////////////////////////////////////
/// Implementation
////////////////////////////////////////////

template<typename ValueType>
Matrix<ValueType>::Matrix()
{}

template<typename ValueType>
Matrix<ValueType>::Matrix(int width, int height, const ValueType& default_value)
{
    for (int i = 0; i < width; ++i) {
        QList<ValueType> list;
        for (int j = 0; j < height; ++j) {
            list.append(default_value);
        }
        m_matrix.append(list);
    }
}

template<typename ValueType>
Matrix<ValueType>::Matrix(const QSize& size,const ValueType& default_value)
    : Matrix(size.width(), size.height(),default_value)
{}

template<typename ValueType>
int Matrix<ValueType>::width() const {
    return m_matrix.size();
}

template<typename ValueType>
int Matrix<ValueType>::height() const {
    if (m_matrix.empty()) {
        return 0;
    }
    return m_matrix.at(0).size();
}

template<typename ValueType>
QSize Matrix<ValueType>::size() const {
    return QSize(width(), height());
}

template<typename ValueType>
const ValueType& Matrix<ValueType>::at(int i, int j) const {
    return m_matrix.at(i).at(j);
}

template<typename ValueType>
const ValueType& Matrix<ValueType>::at(const QPoint& point) const {
    return at(point.x(), point.y());
}

template<typename ValueType>
const QList<ValueType>& Matrix<ValueType>::operator[](int i) const {
    return m_matrix[i];
}

template<typename ValueType>
QList<ValueType>    & Matrix<ValueType>::operator[](int i) {
    return m_matrix[i];
}

#endif // MATRIX_H
