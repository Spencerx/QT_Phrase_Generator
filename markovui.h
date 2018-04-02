#ifndef MARKOVUI_H
#define MARKOVUI_H

#include <QMainWindow>
#include <QTextStream>
#include <QVector>
#include <QMap>

namespace Ui {
class MarkovUI;
}

class MarkovUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MarkovUI(QWidget *parent = 0);
    ~MarkovUI();
    void generate_phrase(int count, QString gram, QMap<QString, QVector<QString> > &patterns);
    void init_file();
    void calc_blocks(QTextStream &stream);

private slots:
    void on_openFile_clicked();

    void on_countSlider_sliderMoved(int position);

    void on_generatePhrase_clicked();

    void on_countSlider_sliderReleased();

private:
    Ui::MarkovUI *ui;
    QString fileContents;
    QVector<QString> beginnings;
    QMap<QString, QVector<QString> > patterns;
    QString filename;
    int lastVal;
};

#endif // MARKOVUI_H
