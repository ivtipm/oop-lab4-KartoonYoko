#ifndef DATABASE_H
#define DATABASE_H
#include <list>
#include <string>
#include <iterator>
#include <fstream>
#include <QAbstractTableModel>
#include <QDebug>
#include <QDir>

/*
        Класс "База данных".
    Позволяет производить следующие действия над БД:
        • Одна таблица с 4+ полями.
        • Добавление, проверка, изменение, удаление данных
        • Поиск, сортировка (как минимум по одному полю).
*/

using namespace std;

class Database : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum Column {
            FIRST_COLUMN = 0,
            SECOND_COLUMN,
            THIRD_COLUMN,
            FOURTH_COLUMN,
            LAST_COLUMN
        };

    // тип записи(строки) - словарь с ключами, представляющие собой нумерацию колонок
    typedef QHash< Column, QVariant > typeOfRow;
    // тип бд - список из записей
    typedef QList< typeOfRow > typeOfData;

    enum exception_database { INVALID_VALUE , EMPTY_FILE, EMPTY_LIST, FILE_DOESNT_EXIST };

    Database(QObject* parent = 0);

    // переопределение для отображения
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;    
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    // переопределение для изменения
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()); // удаление данных
    // удаляет из модели те данные, которые стоят на позициях, передаваемых в списке list
    void removeRows(const QList<QModelIndex> &list); // удаление данных

    // функции работы с бд
    void appendData(const QString& first, const QString& second, const QString& third, const QString& fourth);
    // вернет false если не попадает в радиус min - max
    bool checkNumber(const QString& str, double min, double max);
    // найдет элемент
    typeOfRow* find(const QString& first = "", const QString& second = "", const QString& third = "", const QString& fourth = "");
    // для обновления модели
    void resetModel();
    // сортировать по number - столбцу
    void sort(Column number, Qt::SortOrder direction);

    // работа с фалами
    // сохранить БД в файл
    void saveToFile(const QString& name);// todo:
    void readFromFile(const QString& name);// todo:

    bool empty();

private:

    typeOfData _data;

};
#endif // DATABASE_H
