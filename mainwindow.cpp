#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.hpp"

MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
  {
    ui->setupUi(this);
    this->setWindowTitle("Coche Autónomo");
  }

MainWindow::~MainWindow(void)
{
  delete ui;
}

void MainWindow::on_push_button_generar_clicked(void)
{
  undefined=0;
  Filas=ui->line_edit_filas->text().toInt();
  Columnas=ui->line_edit_columnas->text().toInt();
  if(ui->radio_button_manual->isChecked())
    Opcion=OpcionManual;
  else
    if(ui->radio_button_aleatorio->isChecked())
    {
      Opcion=OpcionAleatoria;
      Porcentaje=(ui->line_edit_dato_radio_button->text().toDouble())/100;
      numero_paradas=ui->line_edit_numero_paradas->text().toInt();
    }
    else
      if(ui->radio_button_fichero->isChecked())
      {
        Opcion=OpcionFichero;
        nombre_fichero_entrada=ui->line_edit_dato_radio_button->text().toStdString();
      }
  Salida=ui->check_box_salida->isChecked();
  if(Salida)
    nombre_fichero_salida=ui->line_edit_salida->text().toStdString();
  this->close();
}

void MainWindow::on_radio_button_manual_clicked(void)
{
  ui->line_edit_filas->setEnabled(1);
  ui->line_edit_columnas->setEnabled(1);
  ui->line_edit_numero_paradas->setEnabled(0);
  ui->line_edit_dato_radio_button->setEnabled(0);
  ui->label_3->setText("");
}

void MainWindow::on_radio_button_aleatorio_clicked(void)
{
  ui->line_edit_filas->setEnabled(1);
  ui->line_edit_columnas->setEnabled(1);
  ui->line_edit_numero_paradas->setEnabled(1);
  ui->line_edit_dato_radio_button->setEnabled(1);
  ui->label_3->setText("Porcentaje");
}

void MainWindow::on_radio_button_fichero_clicked(void)
{
  ui->line_edit_filas->setEnabled(0);
  ui->line_edit_columnas->setEnabled(0);
  ui->line_edit_numero_paradas->setEnabled(0);
  ui->line_edit_dato_radio_button->setEnabled(1);
  ui->label_3->setText("Ruta");
}

void MainWindow::on_check_box_salida_clicked(void)
{
  ui->line_edit_salida->setEnabled(!ui->line_edit_salida->isEnabled());
}
