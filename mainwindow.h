#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(void);

  private slots:
    void on_push_button_generar_clicked(void);
    void on_radio_button_manual_clicked(void);
    void on_radio_button_aleatorio_clicked(void);
    void on_radio_button_fichero_clicked(void);
    void on_check_box_salida_clicked(void);

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
