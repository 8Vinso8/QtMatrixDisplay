#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]){
    ifstream fin("sequence.txt");
    int n;
    fin >> n;
    auto *sequence = new string[n];
    for (int i = 0; i < n; i++){ fin >> sequence[i]; }
    fin.close();
    QApplication app(argc,argv);
    QWidget window;
    string bnum;
    for (int j = 0; j < n; j++){
        for (int i = 0; i < sequence[j].size(); i++){
            bnum = sequence[j][i];
            QString qbnum = QString::fromStdString(bnum);
            auto* button = new QPushButton(qbnum, &window);
            button->setGeometry(31 * i, 31 * j, 30, 30);
            QObject::connect(button, &QPushButton::clicked, [i, button, j, sequence](){
                string a = sequence[j][i] == '0' ? "1" : "0";
                sequence[j][i] = a[0];
                button->setText(QString::fromStdString(a));
            });
        }
    }
    auto *save = new QPushButton("Сохранить", &window);
    save->setGeometry(0, 30 * n, 80, 30);
    QObject::connect(save, &QPushButton::clicked, [n, sequence](){
        ofstream fout("sequence.txt");
        fout << n << endl;
        for (int i = 0; i < n; i++){ fout << sequence[i] << endl; }
        fout.close();
    });
    window.show();
    return QApplication::exec();
}