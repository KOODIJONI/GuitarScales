#include "FretBoard.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QMap>

// Helper function to get the note name for a given string and fret
QString noteAt(int stringIndex, int fret, const QStringList& tuning) {
    static const QStringList notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    static const QMap<QString, int> noteValues = {
        {"C", 0}, {"C#", 1}, {"Db", 1}, {"D", 2}, {"D#", 3}, {"Eb", 3}, {"E", 4}, {"F", 5},
        {"F#", 6}, {"Gb", 6}, {"G", 7}, {"G#", 8}, {"Ab", 8}, {"A", 9}, {"A#", 10}, {"Bb", 10}, {"B", 11}
    };

    if (stringIndex < 0 || stringIndex >= tuning.size()) return "";
    QString baseNote = tuning[stringIndex];
    if (!noteValues.contains(baseNote)) return "";
    int baseValue = noteValues[baseNote];
    int noteValue = (baseValue + fret) % 12;
    return notes[noteValue];
}

FretBoard::FretBoard(QWidget *parent, int numFrets, const QVector<QPair<int, int>>& initialNotes)
    : QWidget(parent), numFrets_(numFrets), notes_(initialNotes), rootNote_("") {
    stringNames_ = {"E", "B", "G", "D", "A", "E"};
    setWindowTitle("Guitar Fretboard");
    setGeometry(100, 100, 600, 200);

}

void FretBoard::setRootNote(const QString& rootNote) {
    rootNote_ = rootNote;
    update();
}

void FretBoard::setNotesByName(const QVector<QString>& noteNames) {
    QVector<QPair<int, int>> foundNotes;
    for (int stringIndex = 0; stringIndex < stringNames_.size(); ++stringIndex) {
        for (int fret = 0; fret <= numFrets_; ++fret) {
            QString note = noteAt(stringIndex, fret, stringNames_);
            if (noteNames.contains(note)) {
                foundNotes.append(qMakePair(stringIndex, fret));
            }
        }
    }
    setNotes(foundNotes);
}

void FretBoard::setNotes(const QVector<QPair<int, int>>& notes) {
    notes_ = notes;
    update();
}

void FretBoard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();
    int numStrings = stringNames_.size();
    int padding = 15;

    double availableHeight = height - 2 * padding;
    double fretWidth = static_cast<double>(width) / (numFrets_ + 1);
    double stringSpacing = (numStrings > 1 && availableHeight > 0) ? static_cast<double>(availableHeight) / (numStrings - 1) : (availableHeight > 0 ? static_cast<double>(availableHeight) / 2 : 0);
    double startY = padding;

    QPen fretPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(fretPen);
    for (int i = 0; i <= numFrets_; ++i) {
        double x = i * fretWidth;
        double lineWidth = 2.0;
        if (i == 1) lineWidth = 4.0;
        fretPen.setWidthF(lineWidth);
        painter.setPen(fretPen);
        painter.drawLine(QPointF(x, startY), QPointF(x, height - padding));
        fretPen.setWidthF(2.0);
        painter.setPen(fretPen);
    }

    QPen stringPen(Qt::black, 1, Qt::SolidLine);
    painter.setPen(stringPen);
    for (int i = 0; i < numStrings; ++i) {
        double y = startY + i * stringSpacing;
        painter.drawLine(QPointF(0, y), QPointF(width, y));
    }

    QFont font("Arial", 10);
    painter.setFont(font);
    for (int i = 0; i < numStrings; ++i) {
        double y = startY + i * stringSpacing + 5;
        painter.drawText(QPointF(5, y), stringNames_[i]);
    }

    drawFretMarkers(painter, fretWidth, startY, availableHeight);

    QFont noteFont("Arial", 10);
    painter.setFont(noteFont);
    double noteRadius = 10;

    for (const auto& notePair : notes_) {
        int stringIndex = notePair.first;
        int fret = notePair.second;

        if (stringIndex >= 0 && stringIndex < numStrings && fret >= 0 && fret <= numFrets_) {
            QString currentNote = noteAt(stringIndex, fret, stringNames_);
            double xCenter = (fret + 0.5) * fretWidth;
            double yCenter = startY + stringIndex * stringSpacing;

            // Draw the note ball
            QColor ballColor = Qt::blue;
            if (currentNote == rootNote_ && !rootNote_.isEmpty()) {
                ballColor = Qt::red; // Highlight the root note
            }
            painter.setBrush(QBrush(ballColor));
            painter.drawEllipse(QPointF(xCenter, yCenter), noteRadius, noteRadius);

            // Draw the note label
            painter.setPen(Qt::white);
            QRectF textRect(xCenter - noteRadius, yCenter - noteRadius, 2 * noteRadius, 2 * noteRadius);
            painter.drawText(textRect, Qt::AlignCenter, currentNote);
            painter.setPen(Qt::black); // Reset pen color
        }
    }

    painter.end();
}

void FretBoard::drawFretMarkers(QPainter& painter, double fretWidth, double startY, double availableHeight) {
    painter.setBrush(QBrush(Qt::black));
    QPen markerPen(Qt::NoPen);
    painter.setPen(markerPen);
    double markerRadius = 5;

    QVector<int> singleMarkers = {3, 5, 7, 9};
    for (int fret : singleMarkers) {
        if (fret <= numFrets_) {
            double x = (1 + fret) * fretWidth - fretWidth/2;
            double y = startY + availableHeight / 2.0;
            painter.drawEllipse(QPointF(x, y), markerRadius, markerRadius);
        }
    }

    if (numFrets_ >= 12) {
        double x1 = (1 +12) * fretWidth  - fretWidth/2;
        double yOffset = availableHeight / 6.0;
        painter.drawEllipse(QPointF(x1, startY + yOffset), markerRadius, markerRadius);
        painter.drawEllipse(QPointF(x1, startY + availableHeight - yOffset), markerRadius, markerRadius);
    }

    if (numFrets_ >= 15) {
        double x = (1 +15) * fretWidth  - fretWidth/2 ;
        double y = startY + availableHeight / 2.0;
        painter.drawEllipse(QPointF(x, y), markerRadius, markerRadius);
    }
    if (numFrets_ >= 17) {
        double x = (1 +17) * fretWidth  - fretWidth/2;
        double y = startY + availableHeight / 2.0;
        painter.drawEllipse(QPointF(x, y), markerRadius, markerRadius);
    }
    if (numFrets_ >= 19) {
        double x = (1 +19) * fretWidth  - fretWidth/2;
        double y = startY + availableHeight / 2.0;
        painter.drawEllipse(QPointF(x, y), markerRadius, markerRadius);
    }
    if (numFrets_ >= 21) {
        double x = (1 +21) * fretWidth- fretWidth/2;
        double y = startY + availableHeight / 2.0;
        painter.drawEllipse(QPointF(x, y), markerRadius, markerRadius);
    }
    if (numFrets_ >= 24) {
        double x = (1 +24) * fretWidth - fretWidth/2 ;
        double yOffset = availableHeight / 6.0;
        painter.drawEllipse(QPointF(x, startY + yOffset), markerRadius, markerRadius);
        painter.drawEllipse(QPointF(x, startY + availableHeight - yOffset), markerRadius, markerRadius);
    }
}
void FretBoard::setTuning(const int stepsDown) {
    static const QStringList chromaticNotes = {
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    };
    static const QMap<QString, int> noteIndices = {
        {"C", 0}, {"C#", 1}, {"D", 2}, {"D#", 3}, {"E", 4}, {"F", 5},
        {"F#", 6}, {"G", 7}, {"G#", 8}, {"A", 9}, {"A#", 10}, {"B", 11}
    };

    QStringList standardTuning = {"E", "B", "G", "D", "A", "E"};
    QStringList newTuning;

    for (const QString& note : standardTuning) {
        int index = noteIndices.value(note, -1);
        if (index == -1) {
            newTuning << note; // Fallback if note not found
            continue;
        }
        int newIndex = (index - stepsDown + 12) % 12;
        newTuning << chromaticNotes[newIndex];
    }

    stringNames_ = newTuning;
    update();
}
