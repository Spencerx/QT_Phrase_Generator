#include "markovui.h"
#include "ui_markovui.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QRandomGenerator>

MarkovUI::MarkovUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MarkovUI)
{
    ui->setupUi(this);
}

MarkovUI::~MarkovUI()
{
    delete ui;
}

/**************************************
 * INIT_FILE
 * Upon opening a file, or needing a
 * significant change to file contents,
 * such as changing slider value,
 * begin the block calculation process.
 **************************************/
void MarkovUI::init_file()
{
    // Disable any potential means of the user
    //  changing necessary values during the
    //  initialization process
    ui->openFile->setEnabled(false);
    ui->generatePhrase->setEnabled(false);
    ui->countSlider->setEnabled(false);

    QFile f(filename);

    f.open(QIODevice::ReadOnly);

    QFileInfo fileInfo(f.fileName());
    ui->currFile->setText(fileInfo.fileName());

    QTextStream stream(&f);
    fileContents = stream.readAll();

    stream.seek(0);

    calc_blocks(stream);
    f.close();

    // If all things went well,
    //  re-enable all user's options.
    ui->openFile->setEnabled(true);
    ui->generatePhrase->setEnabled(true);
    ui->countSlider->setEnabled(true);
}

/**************************************************
 * CALC_BLOCKS
 * Reads a file from passed-in stream, and
 * determines the beginnings of potential
 * phrases based on the first countSlider->value()
 * characters in a line in the stream, and the
 * potential next values based on blocks of the
 * same size, stored in a one-to-many map.
 *
 * NOTE:
 * Text files are assumed to have been formatted
 * such that each sentence is on its own line)
 **************************************************/
void MarkovUI::calc_blocks(QTextStream &stream)
{
    // Empty mappings and vectors to not have
    //   any overlap from old file's data to
    //   data from a new file.
    if(!beginnings.isEmpty()){
        beginnings.clear();
        patterns.clear();
    }

    int ngram_size = ui->countSlider->value();

    // Reading the file stream, determing potential beginnings
    //   of phrases, of size determined by slider.
    //   For example, a file containing:
    //
    // Hello World!
    // This is an example sentence.
    // My name is Tyler.
    //
    // and with a slider value of 5, would generate beginnings of
    // {"Hello", "This ", "My na"}
    QString temp;
    while(!stream.atEnd()){
        temp = stream.readLine();
        beginnings.push_back(temp.mid(0,ngram_size));
    }

    // One-to-many map of each n-gram of size determined by slider
    //   For example, n-gram mappings of size 5 on the line "Hello World"
    //   include:
    // {"Hello" => ' ',
    //  "ello " => 'W',
    //  "llo W" => 'o'.
    //  ...
    //  " Worl" => 'd'}
    for(int i = 0; i < fileContents.size()-ngram_size; i++){
        patterns[fileContents.mid(i,ngram_size)].push_back(fileContents.mid(i+ngram_size,1));
    }
}

void MarkovUI::generate_phrase(int count, QString gram, QMap<QString, QVector<QString> > &patterns)
{
    QString result = gram;
    int pos=0;
    QVector<QString> possibilities;
    QRandomGenerator *generator = QRandomGenerator::system();

    while(result.mid(result.size()-1, 1)!="." && result.mid(result.size()-1, 1)!="!" && result.size()<500){

        if(patterns.find(gram)!=patterns.end()){
            possibilities = patterns[gram];
        }else{ break; }

        if(possibilities.size()>1){
            pos = (*generator).bounded(possibilities.size()-1);
        }else { pos=0; }

        result += possibilities[pos];
        gram = result.mid(result.size()-count, count);
    }
    ui->textBrowser->append(result + "\n");
}

void MarkovUI::on_openFile_clicked()
{
    QString temp = filename; // For comparison

    // Prompt for text-file input
    filename = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "....",
                "Text file (*.txt);;");

    //Start the initialization process
    //  provided the user actually selected
    //  a file, and only if it's different than
    //  what's open currently (if applicable)
    if(filename!=temp&&filename!=NULL){
        ui->openFile->setEnabled(false);
        init_file();
    }
}

void MarkovUI::on_countSlider_sliderMoved(int position)
{
    ui->countLabel->setText("Block size: " + QString::number(position));
}

void MarkovUI::on_generatePhrase_clicked()
{
    // Randomly select a place to start (from the beginnings vector),
    QRandomGenerator *generator = QRandomGenerator::system();
    int start = (*generator).bounded(beginnings.size()-1);
    QString init = beginnings[start];

    //   and continue the rest of the phrase from there.
    generate_phrase(ui->countSlider->value(), init, patterns);
}

void MarkovUI::on_countSlider_sliderReleased()
{
    if(filename!=NULL&&lastVal!=ui->countSlider->value()){
        lastVal=ui->countSlider->value();
        init_file();
    }

}
