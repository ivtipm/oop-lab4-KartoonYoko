#include "database.h"

Database::Database(QObject* parent):QAbstractTableModel( parent ) { }


int Database::rowCount( const QModelIndex& parent ) const{

    Q_UNUSED(parent)
    return _data.count();
}
int Database::columnCount( const QModelIndex& parent ) const {

    Q_UNUSED(parent)
    return LAST_COLUMN;
}


QVariant Database::headerData( int section, Qt::Orientation orientation, int role ) const{

    if (role != Qt::DisplayRole)
        return QVariant();

    if ( orientation == Qt::Vertical ) {
           return section;
       }

    if ( orientation == Qt::Horizontal ) {
       switch( section ) {
       case FIRST_COLUMN:
           return ( "Фамилия" ); break;
       case SECOND_COLUMN:
           return ( "Имя" ); break;
       case THIRD_COLUMN:
           return ( "Отчество" ); break;
       case FOURTH_COLUMN:
           return ( "Номер страхования" ); break;
       }
      }
}

QVariant Database::data( const QModelIndex& index, int role ) const{

    if (!index.isValid() || _data.count() <= index.row() ||
            (role != Qt::DisplayRole && role != Qt::EditRole)) {
            return QVariant();
        }

       return _data[ index.row() ][ Column( index.column() ) ];
}

bool Database::checkNumber(const QString& str, double min, double max){

    double buf = str.toDouble();
    if (buf < min || buf > max){
        return false;
    }
    else
        return true;
}

bool Database::setData( const QModelIndex& index, const QVariant& value, int role ){

    if (index.isValid() && role == Qt::EditRole) {

            _data[ index.row() ][ Column( index.column() ) ] = value;

            emit dataChanged(index, index);
            return true;
        }
        return false;
}

Qt::ItemFlags Database::flags( const QModelIndex& index ) const{

    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}



void Database::appendData(const QString& first, const QString& second, const QString& third, const QString& fourth){

    typeOfRow record;
    record[FIRST_COLUMN] = first;
    record[SECOND_COLUMN] = second;
    record[THIRD_COLUMN] = third;
    if (!checkNumber(fourth, 1000, 9999))
        throw INVALID_VALUE;
    record[FOURTH_COLUMN] = fourth;

    int row = _data.count();
    beginInsertRows( QModelIndex(), row, row );
    _data.append( record );
    endInsertRows();
    this->beginResetModel();
    this->endResetModel();
}

void Database::removeRows(const QList<QModelIndex> &list){

    int i = 0;
    int amountOfDeleting = 0;
    typeOfData::iterator it = _data.begin();
    while( it != _data.end() && amountOfDeleting < list.count()) {
            if( list.at(amountOfDeleting).row() - amountOfDeleting == i) {
                beginRemoveRows( QModelIndex(), i, i );
                it = _data.erase( it );
                endRemoveRows();
                amountOfDeleting++;
            } else {
                ++i;
                ++it;
            }
        }
    this->beginResetModel();
    this->endResetModel();
}

bool Database::removeRows(int row, int count, const QModelIndex &parent)
 {
    Q_UNUSED(parent)
    int i;
    typeOfData::iterator it = _data.begin();
    if(_data.empty() || _data.count() < row + count)
        return false;
    for(i = 0; i < row; i++){
        it++;
    }
    for (int j = 0; j < count; j++){
        beginRemoveRows( parent, i, i );
        it = _data.erase( it );
        endRemoveRows();
    }

    this->beginResetModel();
    this->endResetModel();

    return true;

 }



Database::typeOfRow* Database::find(const QString& first, const QString& second, const QString& third, const QString& fourth){

    if (_data.empty()){
        throw EMPTY_LIST;
    }

    bool isFirstFound = false;
    bool isSecondFound = false;
    bool isThirdFound = false;
    bool isFourthFound = false;

    bool isResultFound = false;

    typeOfData::iterator it = _data.begin();

    while(it != _data.end() && (!isFirstFound || !isSecondFound || !isThirdFound || !isFourthFound)){
        isFirstFound = false;
        isSecondFound = false;
        isThirdFound = false;
        isFourthFound = false;

        if (first != ""){
            if((*it)[FIRST_COLUMN] == first){
                isFirstFound = true;
            }
        }
        else
            isFirstFound = true;

        if (second != ""){
            if((*it)[SECOND_COLUMN] == second){
                isSecondFound = true;
            }
        }
        else
            isSecondFound = true;

        if (third != ""){
            if((*it)[THIRD_COLUMN] == third){
                isThirdFound = true;
            }
        }
        else
            isThirdFound = true;

        if (fourth != ""){
            if((*it)[FOURTH_COLUMN] == fourth){
                isFourthFound = true;
            }
        }
        else
            isFourthFound = true;


        isResultFound = isFirstFound && isSecondFound && isThirdFound && isFourthFound;
        if(isResultFound)
            break;
        it++;
    }

    if(isResultFound)
        return &(*it);
    else
        return nullptr;
}




void Database::resetModel(){

    this->beginResetModel();
    this->endResetModel();
}



void Database::sort(Column number, Qt::SortOrder direction){

    if (_data.empty()){
        throw EMPTY_LIST;
    }
    if ((number >=0) && (number < _data[0].size())){

            if (direction == Qt::AscendingOrder) {
                // по возрастанию
                // индекс наименьшего элемента на каждом проходе
                int n = this->_data.count();
                int smallIndex;
                int i, j;
                for (i = 0; i < n - 1; i++) {
                    // начать проход с индекса i; установить smallIndex в i
                    smallIndex = i;
                    for (j = i + 1; j < n; j++) {
                        // обновить smallIndex если найден наименьший элемент
                        if (_data[j][number] < _data[smallIndex][number])
                            smallIndex = j;
                    }

                    std::swap(_data[i], _data[smallIndex]);
                }
              }

            } else
                if (direction == Qt::DescendingOrder) {
                //по убыванию
                    // индекс наименьшего элемента на каждом проходе
                    int n = this->_data.count();
                    int smallIndex;
                    int i, j;
                    for (i = 0; i < n - 1; i++) {
                        // начать проход с индекса i; установить smallIndex в i
                        smallIndex = i;
                        for (j = i + 1; j < n; j++) {
                            // обновить smallIndex если найден наименьший элемент
                            if (_data[j][number] > _data[smallIndex][number])
                                smallIndex = j;
                        }

                        std::swap(_data[i], _data[smallIndex]);
                    }

            }
            this->resetModel();
}





void Database::saveToFile(const QString& name){

    ofstream f;
    f.open("database.txt"); //QDir::homePath().toStdString() +
    //f.open("C:/Users/Jarvis/Desktop/oop/Term 4/Lab 4/database.txt");
    if( f.is_open() ) qDebug() << "Файл создан" << endl;
        else {
            qDebug() << "Файл не создан";
    }
    typeOfData::iterator it = _data.begin();
    f << (*it)[FIRST_COLUMN].toString().toStdString() << " ";
    f << (*it)[SECOND_COLUMN].toString().toStdString() << " ";
    f << (*it)[THIRD_COLUMN].toString().toStdString() << " ";
    f << (*it)[FOURTH_COLUMN].toString().toStdString();
    it++;

    while(it != _data.end()){
        f << endl << (*it)[FIRST_COLUMN].toString().toStdString() << " ";
        f << (*it)[SECOND_COLUMN].toString().toStdString() << " ";
        f << (*it)[THIRD_COLUMN].toString().toStdString() << " ";
        f << (*it)[FOURTH_COLUMN].toString().toStdString();
        it++;
        qDebug() << "Одна запись есть!";
    }
    f.close();
}
void Database::readFromFile(const QString& name){

    ifstream f;
    f.open("database.txt");
    //f.open("C:/Users/Jarvis/Desktop/oop/Term 4/Lab 4/database.txt");
    if( f.is_open() ) qDebug() << "Файл создан" << endl;
        else {
            qDebug() << "Файл не создан";
            throw FILE_DOESNT_EXIST;
    }
    typeOfRow it;
    QString first;
    QString second;
    QString third;
    QString fourth;
    string buf;
    if (f){
    while(!f.eof()){
        f >> buf;
        if (buf == "" || buf == " " || buf == "\n") {
            throw EMPTY_FILE;
            qDebug() << "Here!";
            exit(-1);
        }
        first = QString::fromStdString(buf);

        f >> buf;
        second = QString::fromStdString(buf);
        f >> buf;
        third = QString::fromStdString(buf);
        f >> buf;
        fourth = QString::fromStdString(buf);
        appendData(first, second, third, fourth);
    }
    }

    f.close();
    resetModel();
}




bool Database::empty(){

    return _data.empty();
}














