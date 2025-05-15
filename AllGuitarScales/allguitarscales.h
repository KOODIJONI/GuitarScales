#ifndef ALLGUITARSCALES_H
#define ALLGUITARSCALES_H

#include <QMainWindow>
#include "fretboard.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class AllGuitarScales;
}
QT_END_NAMESPACE

class AllGuitarScales : public QMainWindow
{
    Q_OBJECT

public:
    AllGuitarScales(QWidget *parent = nullptr);
    ~AllGuitarScales();

private:
    Ui::AllGuitarScales *ui;
    FretBoard *fretboardWidget_;
    QVector<QString> generateScale(const QString &rootNote, const QString &scaleType);
    QLabel *MainLabel = new QLabel("Guitar Scales", this);

};
#endif // ALLGUITARSCALES_H
