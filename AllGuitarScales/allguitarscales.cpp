#include "allguitarscales.h"
#include "./ui_allguitarscales.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QDebug>
#include <QPushButton>
#include <QRandomGenerator>
AllGuitarScales::AllGuitarScales(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AllGuitarScales)
{
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // --- Add Note and Scale selection ---
    QHBoxLayout *selectorLayout = new QHBoxLayout;

    QLabel *noteLabel = new QLabel("Note:");
    QComboBox *noteCombo = new QComboBox;
    noteCombo->addItems({"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"});

    QLabel *scaleLabel = new QLabel("Scale:");
    QComboBox *scaleCombo = new QComboBox;
    scaleCombo->addItems({
        "Major", "Minor", "Pentatonic", "Minor Pentatonic", "Blues", "Major Blues",
        "Harmonic Minor", "Melodic Minor", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Locrian",
        "Whole Tone", "Chromatic", "Enigmatic", "Neapolitan Minor", "Neapolitan Major",
        "Hungarian Minor", "Double Harmonic", "Spanish Gypsy", "Flamenco", "Gypsy Major",
        "Gypsy Minor", "Persian", "Byzantine", "Arabian", "Egyptian", "Oriental", "Japanese (In Sen)",
        "Hirajoshi", "Iwato", "Kumoi", "Pelog", "Balinese", "Super Locrian", "Lydian Dominant",
        "Lydian Augmented", "Bebop Major", "Bebop Minor", "Bebop Dominant", "Acoustic Scale",
        "Ukrainian Dorian", "Romanian Minor", "Maqam Hijaz", "Prometheus", "Prometheus Neapolitan",
        "Six Tone Symmetric", "Augmented Scale", "Tritone Scale"
    });


    enum Tuning {
        EStandard,
        DSharpStandard,
        DStandard,
        CSharpStandard,
        CStandard,
        BStandard
    };

    QLabel *tuningLabel = new QLabel("tuning:");
    QComboBox *tuningCombo = new QComboBox;

    QPushButton *Randomize = new QPushButton(this);
    Randomize->setText("Randomize");

    connect(Randomize, &QPushButton::clicked, this, [this,scaleCombo,noteCombo]() {
        int count = scaleCombo->count();
        if (count > 0) {
            int randomIndex = QRandomGenerator::global()->bounded(count);
            scaleCombo->setCurrentIndex(randomIndex);
        }
        count = noteCombo->count();
        if (count > 0) {
            int randomIndex = QRandomGenerator::global()->bounded(count);
            noteCombo->setCurrentIndex(randomIndex);
        }
        this->MainLabel->setText(noteCombo->currentText() +" " + scaleCombo->currentText());
    });

    tuningCombo->addItem("E Standard", EStandard);
    tuningCombo->addItem("D# Standard", DSharpStandard);
    tuningCombo->addItem("D Standard", DStandard);
    tuningCombo->addItem("C# Standard", CSharpStandard);
    tuningCombo->addItem("C Standard", CStandard);
    tuningCombo->addItem("B Standard", BStandard);

    selectorLayout->addWidget(noteLabel);
    selectorLayout->addWidget(noteCombo);
    selectorLayout->addWidget(scaleLabel);
    selectorLayout->addWidget(scaleCombo);

    selectorLayout->addWidget(tuningLabel);
    selectorLayout->addWidget(tuningCombo);
    selectorLayout->addWidget(Randomize);
    layout->addLayout(selectorLayout);
    // ------------------------------------

    QVector<QPair<int, int>> exampleNotes = {
        {2, 1}, {3, 3}, {4, 5}, {5, 7}, {1, 8}, {0, 10}
    };

    fretboardWidget_ = new FretBoard(this, 24, exampleNotes);
    layout->addWidget(fretboardWidget_,4);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowTitle("Guitar App");
    setGeometry(100, 100, 800, 300); // Adjust main window size

    QHBoxLayout *labelLayout = new QHBoxLayout;

    MainLabel->setAlignment(Qt::AlignCenter); // Center the text

    // Make the font much larger
    QFont labelFont = MainLabel->font();
    labelFont.setPointSize(20); // Adjust as needed
    MainLabel->setFont(labelFont);

    // Set height to minimum size hint + 20 pixels
    MainLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    labelLayout->setSizeConstraint(QLayout::SetMinimumSize);


    labelLayout->addWidget(MainLabel);
    layout->addLayout(labelLayout,1);


    connect(noteCombo, &QComboBox::currentTextChanged, this, [=](const QString &) {
        QString note = noteCombo->currentText();
        QString scale = scaleCombo->currentText();
        QVector<QString> scaleNotes = generateScale(note, scale);
        fretboardWidget_->setRootNote(note);
        fretboardWidget_->setNotesByName(scaleNotes); // Update fretboard
        this->MainLabel->setText(noteCombo->currentText() +" " + scaleCombo->currentText());


    });

    connect(scaleCombo, &QComboBox::currentTextChanged, this, [=](const QString &) {
        QString note = noteCombo->currentText();
        QString scale = scaleCombo->currentText();
        QVector<QString> scaleNotes = generateScale(note, scale);

        fretboardWidget_->setNotesByName(scaleNotes); // Update fretboard
        this->MainLabel->setText(noteCombo->currentText() +" " + scaleCombo->currentText());

    });

    connect(tuningCombo, &QComboBox::currentTextChanged, this, [=](const QString &) {
        int enumValue = tuningCombo->currentData().toInt();

        qDebug() << QString::number(enumValue);
        fretboardWidget_->setTuning(enumValue);
        QString note = noteCombo->currentText();
        QString scale = scaleCombo->currentText();
        QVector<QString> scaleNotes = generateScale(note, scale);
        fretboardWidget_->setRootNote(note);
        fretboardWidget_->setNotesByName(scaleNotes);
        this->MainLabel->setText(noteCombo->currentText() +" " + scaleCombo->currentText());

    });
}
QVector<QString> AllGuitarScales::generateScale(const QString &rootNote, const QString &scaleType)
{
    QVector<QString> notes = {"C", "C#", "D", "D#", "E", "F",
                              "F#", "G", "G#", "A", "A#", "B"};

    QMap<QString, QVector<int>> scalePatterns = {
        {"Major",                {2, 2, 1, 2, 2, 2, 1}},
        {"Minor",                {2, 1, 2, 2, 1, 2, 2}},
        {"Pentatonic",           {2, 2, 3, 2, 3}},
        {"Minor Pentatonic",     {3, 2, 2, 3, 2}},
        {"Blues",                {3, 2, 1, 1, 3, 2}},    // Hexatonic Blues
        {"Major Blues",          {2, 1, 1, 3, 2, 3}},
        {"Harmonic Minor",       {2, 1, 2, 2, 1, 3, 1}},
        {"Melodic Minor",        {2, 1, 2, 2, 2, 2, 1}},
        {"Dorian",               {2, 1, 2, 2, 2, 1, 2}},
        {"Phrygian",             {1, 2, 2, 2, 1, 2, 2}},
        {"Lydian",               {2, 2, 2, 1, 2, 2, 1}},
        {"Mixolydian",           {2, 2, 1, 2, 2, 1, 2}},
        {"Locrian",              {1, 2, 2, 1, 2, 2, 2}},
        {"Whole Tone",           {2, 2, 2, 2, 2, 2}},
        {"Chromatic",            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
        {"Enigmatic",            {1, 3, 2, 2, 2, 1, 1}},
        {"Neapolitan Minor",     {1, 2, 2, 2, 1, 3, 1}},
        {"Neapolitan Major",     {1, 2, 2, 2, 2, 2, 1}},
        {"Hungarian Minor",      {2, 1, 3, 1, 1, 3, 1}},
        {"Double Harmonic",      {1, 3, 1, 2, 1, 3, 1}},
        {"Spanish Gypsy",        {1, 3, 1, 2, 1, 2, 2}},  // Same as Phrygian Dominant
        {"Flamenco",             {1, 3, 1, 2, 1, 2, 2}},  // Alias
        {"Gypsy Major",          {1, 3, 1, 2, 1, 3, 1}},
        {"Gypsy Minor",          {2, 1, 3, 1, 1, 3, 1}},  // Same as Hungarian Minor
        {"Persian",              {1, 3, 1, 1, 2, 3, 1}},
        {"Byzantine",            {1, 3, 1, 2, 1, 3, 1}},  // Similar to Double Harmonic
        {"Arabian",              {2, 2, 1, 2, 1, 3, 1}},
        {"Egyptian",             {2, 3, 2, 2, 3}},        // Pentatonic variant
        {"Oriental",             {1, 3, 1, 1, 3, 1, 2}},
        {"Japanese (In Sen)",    {1, 4, 2, 3, 2}},
        {"Hirajoshi",            {2, 1, 4, 1, 4}},
        {"Iwato",                {1, 4, 1, 4, 2}},
        {"Kumoi",                {2, 1, 4, 2, 3}},
        {"Pelog",                {1, 2, 4, 1, 4}},
        {"Balinese",             {1, 2, 4, 1, 4}},
        {"Super Locrian",        {1, 2, 1, 2, 2, 2, 2}},  // Altered scale
        {"Lydian Dominant",      {2, 2, 2, 1, 2, 1, 2}},
        {"Lydian Augmented",     {2, 2, 2, 2, 1, 2, 1}},
        {"Bebop Major",          {2, 2, 1, 2, 1, 2, 2}},  // Major + extra note
        {"Bebop Minor",          {2, 1, 2, 2, 1, 1, 2, 1}},
        {"Bebop Dominant",       {2, 2, 1, 2, 1, 2, 1, 1}},
        {"Acoustic Scale",       {2, 2, 1, 2, 1, 2, 2}},  // Lydian Dominant variant
        {"Ukrainian Dorian",     {2, 1, 3, 1, 2, 1, 2}},
        {"Romanian Minor",       {2, 1, 3, 1, 2, 1, 2}},
        {"Maqam Hijaz",          {1, 3, 1, 2, 1, 2, 2}},  // Similar to Phrygian Dom.
        {"Prometheus",           {2, 2, 2, 1, 3, 1}},
        {"Prometheus Neapolitan",{1, 2, 2, 2, 3, 2}},
        {"Six Tone Symmetric",   {1, 3, 1, 3, 1, 3}},     // Symmetrical scale
        {"Augmented Scale",      {3, 1, 3, 1, 3, 1}},     // Hexatonic
        {"Tritone Scale",        {1, 3, 1, 3, 1, 3}}      // Another symmetric scale
    };


    QVector<QString> scale;
    int rootIndex = notes.indexOf(rootNote);

    if (rootIndex == -1 || !scalePatterns.contains(scaleType))
        return scale; // Invalid root note or scale type

    scale.append(notes[rootIndex]);

    int currentIndex = rootIndex;
    for (int interval : scalePatterns[scaleType]) {
        currentIndex = (currentIndex + interval) % 12;
        scale.append(notes[currentIndex]);
    }

    return scale;
}
AllGuitarScales::~AllGuitarScales()
{
    delete ui;
}
