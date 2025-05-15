#ifndef FRETBOARDWIDGET_H
#define FRETBOARDWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QVector>
#include <QPair>

class FretBoard : public QWidget {
    Q_OBJECT

public:
    FretBoard(QWidget *parent = nullptr, int numFrets = 12, const QVector<QPair<int, int>>& notes = {});
public slots:
    void setNotes(const QVector<QPair<int, int>> &notes);
    void setNotesByName(const QVector<QString> &noteNames); // Accept note names like "A", "C#", etc.
    void setTuning(const int stepsDown);
    void setRootNote(const QString&);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int numFrets_;
    QVector<QPair<int, int>> notes_;
    QStringList stringNames_;
    QString rootNote_;
    void drawFretMarkers(QPainter& painter, double fretWidth, double startY, double availableHeight);
    void drawNoteHighlights(QPainter& painter, double fretWidth, double startY, double stringSpacing, const QString& noteToHighlight);

};

#endif // FRETBOARDWIDGET_H
